#if 0
void MakeAutoActTbl_NewH(short mode)
{
	mode = mode ;
	
	ActTbl_t HUGE  *a_tbl;
	ProgType_t HUGE	*p_buf ;

	bool 		flag_ZABC[4] = {false ,false ,false,false} ;
	bool 		flag_spd_th = false;
	BYTE  	loop_e_air[MAX_LOOP] ;
	BYTE  	e_air ;
	BYTE   	axis, seq[MAX_AXIS][MAX_AXIS] ;
	WORD   	idx, speed, line ;
	WORD   	air_idx ;
	WORD   	ret_line, loop_no ;
	WORD   	wi ;
	WORD 		bDelay[MAX_AXIS] ;
	WORD 		bspeed ;
	WORD 		bspd ;
	SWORD  	loop_s[MAX_LOOP],	loop_e[MAX_LOOP] ,	zabcend[MAX_AXIS] ;
	DWORD 	ref[MAX_AXIS] ,G1ref[MAX_AXIS] ;
	DWORD 	oref[MAX_AXIS],oG1ref[MAX_AXIS] ;
	DWORD 	spd_th_ref[MAX_AXIS] ;	
	DWORD 	ref_bspeed ;
	SDWORD 	pos, ret_pos, dw[MAX_AXIS], lpos[MAX_AXIS] ;
	SDWORD  sds, sde ;
	long long  	dt, cref ;
	long long  	spd_th_cref ;
	bool		has_WaitNearY=true; //false表示Y軸有移動,要加到定位
	bool		flag_DISABLE_RPAIR_Y=false;
	ept_DWORD ept_oref=
#ifdef Bound_Check
    {&oref[0], &oref[0] ,&oref[MAX_AXIS]}
#else
     oref
#endif
;
	ept_DWORD ept_oG1ref=
#ifdef Bound_Check
    {&oG1ref[0], &oG1ref[0] ,&oG1ref[MAX_AXIS]}
#else
     oG1ref
#endif
;		
	ept_SDWORD	ept_dw=
#ifdef Bound_Check
    {&dw[0],&dw[0],&dw[MAX_AXIS]}
#else
     dw
#endif
;
	ept_SDWORD ept_lpos=
#ifdef Bound_Check
      {&lpos[0],&lpos[0],&lpos[MAX_AXIS]}
#else
     lpos
#endif
;
	ept_bool	ept_flag_ZABC=
#ifdef Bound_Check
    {&flag_ZABC[0],&flag_ZABC[0],&flag_ZABC[4]};
#else
     flag_ZABC;
#endif






	
	PAUSE_Y = false;//初始化Gcode旗標
	
	bspeed = (WORD)BcdToBin(3, MachineStatus.speed[MachineStatus.speed_mode]) ;	// binary speed
		
	cal_ref(&ref_bspeed,bspeed);
	
	for(axis =0 ; axis < MAX_AXIS ; axis++){
		EPT_IDX(axis, bDelay);
		bDelay[axis] = (WORD)BcdToBin(3, MachineStatus.AxisDelay[axis]) ;//各軸參數:延遲
	}

	air_idx= idx   = 0;
	sds=sde=0 ;
	a_tbl =	ActTbl;
	p_buf =	ProgBuf;
	for( axis=0; axis <	MAX_AXIS; axis++ ){		
		EPT_IDX(axis, lpos);
		lpos[axis] = 0;
	}
	WORD no=find_changepoint() ;


	make_virtual_move(lpos)	;
	for(int axis =0 ; axis< MAX_AXIS ; axis++){
		zabcend[axis]=lpos[axis];
	}
	INIT_LOOP();
	//求出各軸的參考時間值(ms)
	cal_ref(ept_oref) ;
	Initidms() ;
	cal_G1ref(ept_oG1ref) ;
	//紀錄所有的G9
	len_g9_struct =0 ;
	for(line = AutoHook.byline ;ProgBuf[line].bygcode; line++ ){
		p_buf= ProgBuf+line ;
		if(p_buf->bygcode == 9){
			SDWORD incy ;
			
			EPT_IDX(len_g9_struct, g9_struct);
			g9_struct[len_g9_struct].startl= (WORD)BcdToBin(3, ProgBuf[line].dval[START_X]);
			g9_struct[len_g9_struct].endl= (WORD)BcdToBin(3, ProgBuf[line].dval[END_X]);
			if(	p_buf->dval[AXIS_Y]!=PROG_VAL_NULL && p_buf->dval[AXIS_Y]!=0 ){
				incy	 = BcdToBin(6, p_buf->dval[AXIS_Y]);
				incy 	*= ((p_buf->bysign[AXIS_Y]&0x7f)==PLUS_SIGN?1:-1);
				TO_GRID_NOT_ROTATE(AXIS_Y,incy) ;
				g9_struct[len_g9_struct].incy= incy;
				len_g9_struct++ ;
			}
		}
		//找到最後一行的汽缸設定
		else if(((p_buf->bygcode >= 1) && (p_buf->bygcode <= 4))|| (p_buf->bygcode == 6)){
			e_air = p_buf->byair ;
		}
	}
	

	//2012_0903探針停軸-----計算各軸格數------------------------------------------------------------------------------------------------	
	//初始化
	T_Stop_idx=0;													//共?組探針
	T_Stop_idxLast=0;											//最後一組探針
	T_Stop_MdyVAL_idx=0;									//目前?組探針
	T_Stop_HaveTouch_Flag=false;					//是否有探到
	T_Stop_Axis=0;												//目前探針停軸狀態
	SDWORD T_Stop_DwG6Last[MAX_AXIS_8];		//各軸G6前最後格數
	int8   T_Stop_G6seq[MAX_AXIS_8];

	if(MachineStatus.Touch_Stop_Flag){
		for(int xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
			T_Stop_G6seq[xaxis]	=-1;	
			T_Stop_Dw[xaxis]		=	0;
			T_Stop_MdyVAL[axis]	= 0;			//補走格數
			T_Stop_Amov_flag		= false;	//Mode==2用
		}
		T_Stop_MdyVAL_Y=0;							//Y_補走格數
		int xT_idx=0;	//多少個探針停軸
    	
		for(line = AutoHook.byline ;ProgBuf[line].bygcode; line++ ){
			p_buf = ProgBuf+line ;
			int xaxis, xGcode=ProgBuf[line].bygcode;
			SDWORD xpos[MAX_AXIS_8]={0,0,0,0,0,0,0,0};	//目前位置
			
			//此行有探針，則紀錄上一行的格數---探針要到此格數後才可以Touch，避免馬達過快，停馬達時讀錯位置
			if(p_buf->byth > TH_NULL){
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
					T_Stop_DwTouch[xT_idx][xaxis] = T_Stop_Dw[xaxis];    //探針行執行前之值
				}
			}
    	
			if(xGcode==1 ||	xGcode==2||	xGcode==3||	xGcode==4||	xGcode==7){
				//開始計算各軸格數
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){					
					if( p_buf->dval[xaxis] != PROG_VAL_NULL ){
						xpos[xaxis] = BcdToBin(6, p_buf->dval[xaxis]);	
						TO_GRID(xaxis, xpos[xaxis]);					
						xpos[xaxis] *= ((p_buf->bysign[xaxis] & 0x7f)==PLUS_SIGN? 1:-1)	;		
						T_Stop_Dw[xaxis]	=	xpos[xaxis];
					}   	
				}
			} 
			else if(xGcode==6){
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
					T_Stop_G6seq[xaxis] = p_buf->byseq[xaxis];	//G6回原點方式
					if(p_buf->byseq[xaxis]!=NULL_ZRT){ //  != " 0->ZERO "
						T_Stop_DwG6Last[xaxis] = T_Stop_Dw[xaxis];	//紀錄G6前，最後未置
						T_Stop_Dw[xaxis] = 0;
					}
				}
			}
			//寫入探針位置
			if(p_buf->byth > TH_NULL){
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){	
					T_Stop_HaveVAL[xT_idx][xaxis] = xpos[xaxis];		//探針行執行後之值
				}
				xT_idx++;
			}
		}
		//修正_T_Stop，(捲取軸||轉芯)最後位置，並判斷正反轉
		for(int xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
			//修正_T_Stop，(捲取軸||轉芯)最後位置
			if(((CHK_SPIN(xaxis))||CHK_ROTQ(xaxis)) && (T_Stop_Dw[xaxis]==0) && (T_Stop_G6seq[xaxis]!=NULL_ZRT) && (virtual_zabc[xaxis].flag==false)){ //最後位置==0,且G6方式!="NULL_ZRT" 沒虛擬原點				
				SDWORD g6lpos=0, g6ldw=0;
				g6lpos = T_Stop_DwG6Last[xaxis];
				if(g6lpos<0){
					g6lpos = -g6lpos;	
				}
				g6ldw = g6lpos%BMOTORGRID(xaxis);
				
				if(((T_Stop_G6seq[xaxis]==SMART_ZRT) &&	(g6ldw>=(BMOTORGRID(xaxis)/2))) || T_Stop_G6seq[xaxis]==PLUS_ZRT){ //回原點方式== (S->ZERO && 大於(3200/2))	||	"+ ->ZERO"					
					if(g6lpos>BMOTORGRID(xaxis) && (!CHK_ROTATE_A(xaxis))){
						T_Stop_Dw[xaxis] = g6lpos+(BMOTORGRID(xaxis)-g6ldw);
					}
					else {
						T_Stop_Dw[xaxis] = BMOTORGRID(xaxis);
					}
				}
				else if(((T_Stop_G6seq[xaxis]==SMART_ZRT)	&& (g6ldw<(BMOTORGRID(xaxis)/2)))	|| T_Stop_G6seq[xaxis]==MINUS_ZRT){	//回原點方式== (S->ZERO && 小於(3200/2))	||	"- ->ZERO"					
					if(g6lpos>BMOTORGRID(xaxis)	&& (!CHK_ROTATE_A(xaxis))){
						T_Stop_Dw[xaxis] = g6lpos-g6ldw;
					}
					else {
						T_Stop_Dw[xaxis] = 0;
					}
				}
			}	
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	
	
	
	ProgCur_Gcode=ProgBuf[0].bygcode; 
	//開始處理所有的命令行
	for( line=AutoHook.byline; ProgBuf[line].bygcode; line++ ){
		p_buf =	ProgBuf+line;
		if(p_buf->bygcode	== ' '){
			if((idx	>= 1) && (a_tbl[idx-1].cmd == UPDATE_LINE)){
				EPT_IDX(idx, ActTbl);
				a_tbl[idx-1].u.line	+=1;
			}
			continue ;
		}
		sds =	BcdToBin_X(	p_buf->dval[START_X]);
		if(GetSign(p_buf,START_X) & 0x7f){
			sds=-sds ;
		}
		sde =	BcdToBin_X(	p_buf->dval[END_X]);
		if(GetSign(p_buf,END_X) & 0x7f){
			sde=-sde ;
		}
		

		if(Has_spd(p_buf)&& (p_buf->bygcode  !=7)){ //G7:SPD當延遲用
			speed=bspd=(WORD)BcdToBin(3, p_buf->wspd) ;
		}
		else{
			speed=bspd= bspeed ;
		}
		
		//決定此行命令的各軸G2速度
		cal_ref(ref,speed) ;
		
		spd_th_ref[AXIS_X] = 0;
		flag_spd_th = false; 
		
		if(MachineStatus.WorkMode == 1){ //生產速率(RATE)
			uint16 tspd 	= (uint16)BcdToBin(3, p_buf->wspd) ; //變速度
			uint16 tRate 	= (uint16)BcdToBin(4, MachineStatus.Rate[AXIS_X]) ; //主軸(X)速度
			uint16 tspeed = (uint16)BcdToBin(3, MachineStatus.speed[MachineStatus.speed_mode]) ; //生產速率
						
			if(Has_spd(p_buf)){ //有變速度
				if (tspd > tRate)tspd = tRate;//變速度max即主軸速度100
				cal_ref(ref,tspd) ; 					//主軸速度=變速度
				Initidms(tspd) ;
			}
			else{ 													//沒有變速度
				cal_ref(ref,tspeed) ; 				//主軸速度=生產速率
				Initidms(tspeed) ;
			}

#ifdef SPD_TOUCH
			if ((CHK_SPD_TOUCH(p_buf) && (!NEED_AIRTBL(p_buf))) || 
				  (line>0 && (Has_spd(p_buf)) && (p_buf->bygcode==2) && NEED_AIRTBL(p_buf-1))){ //自動生產時針對G2: 1.同時設SPD及探針(非汽缸畫面),2.設SPD且探針超前(汽缸畫面),要以全速執行,再由sc8254先降速,後全速
					flag_spd_th = true;
					spd_th_ref[AXIS_X] = ref[AXIS_X]; //測試要變速
					//cal_ref(ref,tspeed) ; 						//自動要全速
			}
#endif
			bool flag_spd_axis = false;
			for(uint8 axis = AXIS_Y ; axis < MachineStatus.axis_no ; axis++){
				ref[axis]   = oref[axis] ; 																			//G2-----其他各軸仍為馬達速度，(同動時若有主軸移動靠主軸限速(能達限速條件是主軸為同動中最慢的軸,不然仍是受同動中最慢軸配速)，若無則以原速度)			
				G1ref[axis] = ref[axis]*tRate/((Has_spd(p_buf))?tspd:tspeed) ; 	//G1-----其他各軸馬達速度依生產速度或變速度做比率配速
				if(MachineStatus.G2Mode == 1){
					ref[axis]   = G1ref[axis] ; //G2-----其他各軸仍為馬達速度，(同動時若有主軸移動靠主軸限速(能達限速條件是主軸為同動中最慢的軸,不然仍是受同動中最慢軸配速)，若無則以原速度)
				}
								
				
				if (axis == ServoCutter_axis){ //伺服切刀G1按照原G2速度，不降速(伺服切刀通常都單獨動且速度一致)
					G1ref[axis] = ref[axis];
				}				
			}
		}
		else { //生產速度(RPM)
			for(BYTE axis=AXIS_Y ; axis < MachineStatus.axis_no ; axis++){    	
				EPT_IDX(axis, ref);
				ref[axis]		= oref[axis]*bspeed/bspd ;
				G1ref[axis]	= oG1ref[axis]*bspeed/bspd ;
								
				//以馬達速度為上限,超過改成馬達上限
				if(ref[axis] < oref[axis]){
					ref[axis]=oref[axis] ;
				}
				if(G1ref[axis] < oref[axis]){
					G1ref[axis]=oref[axis] ;
				}
			}
		}

		//Gcod標記，紀錄送線暫停用
		if((p_buf->align_byte)&0x80){
			PAUSE_Y=(!PAUSE_Y);
		}

		//ini_var
		a_tbl[idx].idms=0;
		a_tbl[idx].spd_th.ref    = 0;
		a_tbl[idx].spd_th.sc8254 = 0;
		a_tbl[idx].loopref       = 0;
		a_tbl[idx].loopmov       = 0;
		a_tbl[idx].break_cnt     = 0;


		bool has_x ;
		bool condx = CHK_ROTW(AXIS_A) && EXT_ENCODER_MDY ;
		modify_a= false ;
		switch(	p_buf->bygcode )
		{
			//  標籤 Generate acttbl
		case 1:	 sds = sde;
		case 2:
			{
				if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
				}
				MOVE2S(p_buf,a_tbl ,dw ,lpos , sds,	idx	,  ref_bspeed ,	 no	,line) ;
				GET_RET_IDX();
				GET_LOOP_POS();
				SET_TOUCH_AIR(p_buf,a_tbl,idx,air_idx,sds,ept_flag_ZABC,e_air) ;
				//計算各軸欲走的格數
				cal_dw_X(ept_dw,ept_lpos,sde,sds,line) ;
				cal_dw_Y(p_buf,dw[AXIS_Y],lpos)	;
				cal_dw_ZABC(p_buf,ept_dw,ept_lpos) ;
				
				//如果使用G2歸零，且有探針停各軸(Mode==2)，A軸在此時機補償
				if(MachineStatus.Touch_Stop_Flag==2	&& T_Stop_idx	){
					if(dw[AXIS_A]!=0 && lpos[AXIS_A]==0	&& CHK_ROTW(AXIS_A)){
						a_tbl[idx].cmd = T_STOP_OFFSETA;
						a_tbl[idx].next	= 0;
						idx++; EPT_IDX(idx, ActTbl);
					}						
				}
				if((ServoCutter_axis!=0)&& (dw[ServoCutter_axis] !=0)){
					EPT_IDX(ServoCutter_axis, lpos);
					EPT_IDX(ServoCutter_axis, dw);
					if(dw[ServoCutter_axis] >0){
						lpos[ServoCutter_axis]=dw[ServoCutter_axis]=BcdToBin(6,MachineStatus.CutDist) ;
					}
					else{
						dw[ServoCutter_axis]=-BcdToBin(6,MachineStatus.CutDist) ;
						lpos[ServoCutter_axis]=0 ;
					}
				}
				//檢查是否只有A軸動,Y軸不動且A為轉線
				bool has_y = (dw[AXIS_Y]) ;
				bool has_a = (dw[AXIS_A]) ;

				bool cond_g2 = condx && (p_buf->bygcode == 2) && (has_y) ;      	
				if(cond_g2){
					//產生 SAVE_Y_MOV
					ADD_SAVE_Y_MOV(a_tbl,idx,has_y? dw[AXIS_Y]: 0 ) ;
					if(has_y && !has_a && MachineStatus.Y_Encoder != 2){
						mdy_dw(dw[AXIS_Y]) ;
					}
				}
				modify_a = condx && (has_y)  ;      	
				//決定各軸中速度最慢的為同動的速度
				if((MachineStatus.speed_mode == FAST)){
					// 以x軸的速度為準
					cref = ref[AXIS_X]*dw[AXIS_X] ;
				}
				else{
					if(p_buf->bygcode !=	1 ){
						uint8 taxis=0 ;
						for( cref=0; taxis <	MachineStatus.axis_no; taxis++ ){
							SDWORD tdw=dw[taxis] < 0 ? -dw[taxis]:dw[taxis] ;
							SDWORD tdw_loop=dw_loop[taxis] < 0 ? -dw_loop[taxis]:dw_loop[taxis] ;
							if((taxis >= AXIS_Z)&&(tdw != tdw_loop)){
							    if(tdw < tdw_loop){
							    	tdw=tdw_loop ;
							  	}
							}
							if(tdw ==0)continue ;
							dt = filltbldt(taxis ,dw , ref,cref) ;
						}
						if(MachineStatus.WorkMode == 1){ //生產速率(RATE)
							uint16 tspd 	= (uint16)BcdToBin(3, p_buf->wspd) ; //變速度
							uint16 tRate 	= (uint16)BcdToBin(4, MachineStatus.Rate[AXIS_X]) ; //主軸(X)速度
							uint16 tspeed = (uint16)BcdToBin(3, MachineStatus.speed[MachineStatus.speed_mode]) ; //生產速率
							if(tspd>tRate)tspd = tRate;
							if (Has_spd(p_buf)&& tspd<tspeed && flag_spd_th == false){
								cref = cref*tspeed/tspd ; //讓降速更明顯
							}
						}
					}
				}
				has_x =	false;
				DWORD xref =0 ;

				if ((p_buf->bygcode ==2)&&dw[AXIS_Y]&&!(PAUSE_Y)&&UseRepairY(AXIS_Y)&&(GetSign(p_buf,AXIS_Y) & 0x80 || MachineStatus.ToPos[AXIS_Y])){
					//同動、Y軸有移動、有壓紅字、有開整定=>整定前要先到定位
					if (has_WaitNearY==false){
						ADD_WaitMotorNear(a_tbl, idx, AXIS_Y,2) ;
						has_WaitNearY=true;
					}
				}
	
				for(int8  axis=0; axis <	MachineStatus.axis_no; axis++ ){
					if((axis==AXIS_Y)&&(PAUSE_Y)){continue;}
					if(	dw[axis] ||dw_loop[axis] ){
						bool cond23=  condx && (p_buf->bygcode == 1) ;
						bool cond_y= cond23  &&  ((axis == AXIS_Y)&& has_y) ;

						if(cond_y ){
							ADD_SAVE_Y_MOV(a_tbl,idx, (axis==AXIS_Y)? dw[AXIS_Y]:0) ;
							if((axis == AXIS_Y)&& (MachineStatus.Y_Encoder != 2)){
								mdy_dw(dw[AXIS_Y]) ;
							}
						}

						if ((p_buf->bygcode ==1)&&(axis==AXIS_Y)&&UseRepairY(axis)&&(GetSign(p_buf,axis) & 0x80 || MachineStatus.ToPos[axis])){
							//定點移動、Y軸有移動、有壓紅字、有開整定=>整定前要先有定位
							if (has_WaitNearY==false){
								ADD_WaitMotorNear(a_tbl, idx, axis,2) ;
								has_WaitNearY=true;
							}
						}

						MFill_BreakCnt
						
						if(	axis ==	AXIS_X ){
							has_x = true;
							a_tbl[idx].cmd = axis +	MOVE_X;
						}
						else{
							a_tbl[idx].cmd = axis +	(p_buf->byth==TH_ERR?MISS_X:MOVE_X);
						}
						SDWORD tdw= dw[axis]<0?-dw[axis]:dw[axis] ;
						SDWORD tdw_loop= dw_loop[axis]<0?-dw_loop[axis]:dw_loop[axis] ;
						a_tbl[idx].ref = (long long)(p_buf->bygcode!=1?cref:G1ref[axis]*(tdw))/(RATIO);
						a_tbl[idx].loopref = (long long)(p_buf->bygcode!=1?cref:G1ref[axis]*(tdw_loop))/(RATIO);
						fill_acttbl_idms(axis,a_tbl,idx,dw) ;
#ifdef SPD_TOUCH
						a_tbl[idx].spd_th.ref =0;
						if (flag_spd_th){
							//a_tbl[idx].spd_th.ref = (long long)spd_th_cref/(RATIO);
						}
#endif
						xref = a_tbl[idx].ref ;
						xref;
						if(axis == AXIS_Y){
							a_tbl[idx].StartWire= (BcdToBin(6, p_buf->dval[AXIS_Y]) >= 30000L)? true : false ;
						}
						a_tbl[idx].mov	  =	dw[axis];
						a_tbl[idx].loopmov=dw_loop[axis] ;
						a_tbl[idx].u.dst_pos = lpos[axis];
						a_tbl[idx].sdchk_pos	 = 0;
						a_tbl[idx].next	  =	p_buf->bygcode!=1?1:0;
						
						
						
						//當同動時,y軸先動
						if(	(has_x) && (axis==AXIS_Y) &&	(p_buf->bygcode!=1) ){
							//X軸命令和Y軸命令對調
							CHG_a_tbl_XY						
						}
						if(axis == AXIS_Y || CHK_ROTATE_A(axis)){
							has_WaitNearY=false;
						}
						if(axis == AXIS_Y){
							ADD_INCY(a_tbl,idx,line) ;
						}
						if(CHK_ROTATE_A(axis)){
							has_a=true  ;
							bool tmodyfy_a=modify_a ;
							if(p_buf->bygcode == 1){
								modify_a=false ;
							}
							ADD_OFFSET_Y(a_tbl ,idx) ;
							modify_a=tmodyfy_a ;
						}
						
						idx++;		EPT_IDX(idx, ActTbl);
						           	
						if((p_buf->bygcode ==1) && bDelay[axis]){
							ADD_Delay_ms(a_tbl,idx,(bDelay[axis]*10)) ;
						}
						if(p_buf->bygcode == 1){
							if (Axis_ToPos && dw[axis]){
								ADD_WaitMotorNear(a_tbl, idx, axis,2) ;//G1各軸CMD之後
								if (UseRepairY(axis)){
									flag_DISABLE_RPAIR_Y=true;//ADD_DisableRepairY(a_tbl, idx);
									
									has_WaitNearY = true;
								}
							}
						}
						
						//y軸修整
						if(cond_y){
							ADD_Modify_y(a_tbl , idx,((p_buf->bygcode ==1)&&axis == AXIS_Y)? 0: has_a) ;//G1G2
						}
					}
				}

				FILL_WAIT_MOTOR_NEAR(sde,a_tbl ,dw ,no ,idx) ;
				CLR_TOUCH_proc(p_buf,a_tbl,idx) ;
            	
				if(cond_g2){
					if(has_a){
						ADD_MDY_GAPY(a_tbl,idx,has_a) ;
					}
					else{
						ADD_Modify_y(a_tbl , idx,has_a) ;//G1G2
					}
				}
				if(p_buf->bygcode == 2){
					bool wait_y=false;
					for(BYTE axis =0 ; axis <MachineStatus.axis_no; axis++){
						if(Axis_ToPos && dw[axis]){
							ADD_WaitMotorNear(a_tbl,idx,axis,2) ;//G2:同動CMD之後
							if (axis==AXIS_Y)wait_y=true;
						}
					}
					if (wait_y&&UseRepairY(AXIS_Y)){
						flag_DISABLE_RPAIR_Y=true;//ADD_DisableRepairY(a_tbl, idx);
						has_WaitNearY = true;
					}
					ADD_Delay(a_tbl,idx ,dw,bDelay) ;
				}
				a_tbl[idx].cmd = p_buf->byth==TH_ERR?MISS_UPDATE_LINE:UPDATE_LINE;
				a_tbl[idx].u.line	 = line+1;
				MDY_UPDATE_LINE ;
				a_tbl[idx].sdchk_pos	= 0;
				a_tbl[idx].next	 = 0;
				idx++;		EPT_IDX(idx, ActTbl);
			}
			break;
		case 3:
		case 4:
      {
      if(flag_DISABLE_RPAIR_Y){
				flag_DISABLE_RPAIR_Y = false;
				ADD_DisableRepairY(a_tbl , idx);
			}		
			MOVE2S(p_buf, a_tbl, dw, lpos, sds,	idx, ref_bspeed, no, line) ;
			
			GET_RET_IDX();
			GET_LOOP_POS();
			SET_TOUCH_AIR(p_buf,a_tbl,idx,air_idx,sds,ept_flag_ZABC,e_air) ;
			
			cal_dw_X(ept_dw,ept_lpos,sde , sds,line);
			cal_dw_Y(p_buf,dw[AXIS_Y],lpos);
			cal_dw_ZABC(p_buf,ept_dw,ept_lpos);
			
			//計算各軸運動的seq
			for(int iseq=0; iseq<MAX_AXIS; iseq++){
				int8 jseq ;
				for(jseq=AXIS_X; jseq<MAX_AXIS; jseq++){
					seq[iseq][jseq] =	0xff;
				}
				jseq = 0;
				//x軸一定是seq=0
				if(iseq == 0){seq[iseq][jseq++] = AXIS_X;}

				for(int8 axis=AXIS_Y; axis<MachineStatus.axis_no;	axis++){
					if((axis==AXIS_Y)&&(PAUSE_Y)){continue;}
					if(p_buf->byseq[axis]==iseq	&& MachineStatus.motor[axis] &&	dw[axis]) seq[iseq][jseq++] = axis;
				}
			}
			
			if ((p_buf->byseq[AXIS_Y]==0)&&dw[AXIS_Y]&&!(PAUSE_Y)&&UseRepairY(AXIS_Y)&&(GetSign(p_buf,AXIS_Y) & 0x80 || MachineStatus.ToPos[AXIS_Y])){
				//同動、Y軸有移動、有壓紅字、有開整定=>整定前要先到定位
				if (has_WaitNearY==false){
					ADD_WaitMotorNear(a_tbl, idx, AXIS_Y,2) ;
					has_WaitNearY=true;
				}
			}
			
			
			int cidx=idx ;
			for(int iseq=0; iseq<MAX_AXIS; iseq++){
				if(iseq==0){
					//檢查是否只有X軸移動,且X軸的移動值為0
					if(dw[AXIS_X]==0){
						seq[0][0]=0xff ;
					}
				}

				bool has_a=false,has_y=false ;
				int jseq ;
				for(cref=0, jseq=0; jseq<MachineStatus.axis_no; jseq++){
					uint8 axis ;
					if((axis=seq[iseq][jseq]) != 0xff){
						if(axis == AXIS_Y){has_y=true;}
						else if(axis == AXIS_A){has_a=true;}
						dt = ((axis==AXIS_X)?ref[axis]:G1ref[axis])*(dw[axis]<0?-dw[axis]:dw[axis]);
						if(	cref < dt )	cref = dt;
					}
				}

				bool cond_y= condx && has_y ;
				modify_a= cond_y ;
      	
				if(cref ){
					has_x = false ;
	    	
					if(cond_y){
						ADD_SAVE_Y_MOV(a_tbl,idx,has_y? dw[AXIS_Y]: 0 ) ;
						if(!has_a&& (MachineStatus.Y_Encoder != 2)){
							mdy_dw(dw[AXIS_Y]) ;
						}
					}
					int jseq ;
					for( dt=0, jseq=0; jseq < MachineStatus.axis_no; jseq++ ){
						if(iseq==0){
							// G4時強迫以0.1秒速為準
							if(p_buf->bygcode==4	&& Has_spd(p_buf)){
								cref= (long long)bspd*100*RATIO ;
							}
						}
      	    
						uint8 axis;
						if((axis=seq[iseq][jseq]) != 0xff){
							
							if ((p_buf->byseq[AXIS_Y]!=0)&&(axis==AXIS_Y)&&(line!=0)&&UseRepairY(axis)&&(GetSign(p_buf,axis) & 0x80 || MachineStatus.ToPos[axis])){
								//定點移動、Y軸有移動、有壓紅字、有開整定=>整定前要先有定位
								if (has_WaitNearY==false){
									ADD_WaitMotorNear(a_tbl, idx, axis,2) ;
									has_WaitNearY=true;
								}
							}



							MFill_BreakCnt
							
							if(axis == AXIS_X){
								a_tbl[idx].cmd = axis +	MOVE_X;
								has_x = true ;
							}
							else{
								a_tbl[idx].cmd = axis +	(p_buf->byth==TH_ERR?MISS_X:MOVE_X);
							}
							if(axis == AXIS_Y){
								a_tbl[idx].StartWire= (BcdToBin(6, p_buf->dval[AXIS_Y]) >= 30000L)? true : false ;
							}
							a_tbl[idx].ref = cref/(RATIO);
							if(NewH){
								fill_acttbl_idms(axis,a_tbl,idx,dw) ;
							}

							a_tbl[idx].mov = dw[axis];
							a_tbl[idx].loopmov=dw_loop[axis] ;
							a_tbl[idx].u.dst_pos = lpos[axis];
							a_tbl[idx].sdchk_pos = 0;
							a_tbl[idx].next	=	1;
							
							
							//當同動時,y軸先動,將X軸命令和Y軸命令對調
							if((has_x) && (axis==AXIS_Y)){									
								CHG_a_tbl_XY
							}
							
							if(axis == AXIS_Y || CHK_ROTATE_A(axis)){
								has_WaitNearY=false;
							}
							
							if(axis == AXIS_Y){
								int tidx=idx ;
								ADD_INCY(a_tbl,idx,line) ;
								if(tidx != idx){
									dt++ ;
								}
							}
							if(CHK_ROTATE_A(axis)){
								ADD_OFFSET_Y(a_tbl ,idx) ;
								dt++	;
							}
							idx++; EPT_IDX(idx, ActTbl);
							dt++;
						}
					}
					//t用來計算同動的命令個數(a_tbl[].next=1)
					//當dt=0---->什麼事都不作
					//  dt=1 --->將同動命令的.next欄位改為0
					//  dt>1---->補上NULL_ACT_CMD(.next欄位為0),以便和下面將產生的同動命令分隔
					if(	dt ){
						if(dt == 1){
							a_tbl[idx-1].next =	0;
						}
						WORD no_wait=0 ;
						bool wait_y=false;
						for( jseq=0; jseq < MachineStatus.axis_no; jseq++ ){
							uint8 axis;
							if(	(axis=seq[iseq][jseq]) !=	0xff ){
								if(Axis_ToPos && dw[axis]){
									no_wait++ ;
									ADD_WaitMotorNear(a_tbl,idx,axis,2) ;//G34
									if (axis==AXIS_Y)wait_y=true;
								}
							}
						}
      	    
						if (wait_y && UseRepairY(AXIS_Y)){
							flag_DISABLE_RPAIR_Y=true;//ADD_DisableRepairY(a_tbl , idx);
							has_WaitNearY = true;
						}
						if((dt != 1) && (no_wait ==0)){
							a_tbl[idx].cmd	= NULL_ACT_CMD;
							a_tbl[idx].sdchk_pos = 0;
							a_tbl[idx].next	= 0;
							idx++;		EPT_IDX(idx, ActTbl);
						}
	    	
						if(cond_y){          	
							if(has_a){
								ADD_MDY_GAPY(a_tbl,idx,has_a) ;
							}
							else{
								ADD_Modify_y(a_tbl,idx,has_a) ;//G3G4
							}
						}
					}
				}
				FILL_WAIT_MOTOR_NEAR(sde,a_tbl ,dw ,no ,idx) ;
				ADD_Delay(a_tbl,idx,seq[iseq],bDelay) ;
			}
			if((cidx == idx) && (p_buf->bygcode==4)	&& Has_spd(p_buf) ){
				//此行都沒有運動指令,純作delay
				ADD_Delay_ms(a_tbl,idx,bspd*100) ;
			}
			
			//Sprintf("%d",dw_loop[Z_AXIS]);
			//a_tbl[idx].loopmov=dw_loop[axis] ;
			
			
			CLR_TOUCH_proc(p_buf,a_tbl,idx) ;			
			a_tbl[idx].cmd = p_buf->byth==TH_ERR?MISS_UPDATE_LINE:UPDATE_LINE;
			a_tbl[idx].u.line	 = line+1;
			MDY_UPDATE_LINE ;
			a_tbl[idx].sdchk_pos	= 0;
			a_tbl[idx].next	 = 0;
			idx++;		EPT_IDX(idx, ActTbl);
			break;
    	}
   	case 7:
			if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
				}
			//加入延遲時間
			if(	p_buf->dval[AXIS_Y]!=PROG_VAL_NULL && p_buf->dval[AXIS_Y]!=0 ){
				ADD_Delay_ms(a_tbl,idx,(DWORD)BcdToBin(6, p_buf->dval[AXIS_Y])) ;
			}
			break;
		case 5:
    	{	
//		Chk_e_air(a_tbl,idx,e_air,0,0) ;
			ini_loopchk(false) ;
			a_tbl[idx].cmd	= LOOP_CHECK;
			a_tbl[idx].sdchk_pos = 0;
			a_tbl[idx].next	= 0;
			idx++;		EPT_IDX(idx, ActTbl);

			for( int i=0; i	< loop_no; i++ ){
				if(	loop_e[i] == line ){
					for(int8 axis=0; axis <	MachineStatus.axis_no; axis++ ){
						if(	axis==AXIS_Y ||	!MachineStatus.motor[axis] )  continue;
						
						EPT_IDX(axis, dw);
						if(	(((looppos[i][axis]-lpos[axis])) !=0) && (axis != AutoHook.byaxis) ){							
							dw[axis]= sdDifGrid(axis,looppos[i][axis],lpos[axis]) ;
							a_tbl[idx].cmd	  =	LOOP_X + axis;
							a_tbl[idx].ref	  =	((long long)ref[axis]*(dw[axis]<0?-dw[axis]:dw[axis]))/(RATIO);
							a_tbl[idx].mov	  =	dw[axis];
							a_tbl[idx].u.dst_pos = looppos[i][axis];
							a_tbl[idx].sdchk_pos	 = 0;
							a_tbl[idx].next	  =	0;
							if(CHK_ROTATE_A(axis)){
								a_tbl[idx].next=1 ;
								idx++ ;		EPT_IDX(idx, ActTbl);
								a_tbl[idx].cmd	  =	LOOP_Y;
								a_tbl[idx].ref	  =	a_tbl[idx-1].ref ;
								a_tbl[idx].mov= a_tbl[idx-1].mov ;
								BYTE dir= OFFSET_Y_dir(PLUS_SIGN) ;
								if(dir == MINUS_SIGN){
									a_tbl[idx].mov	= -a_tbl[idx].mov ;
								}
								a_tbl[idx].u.dst_pos=a_tbl[idx-1].u.dst_pos ;
								a_tbl[idx].sdchk_pos=a_tbl[idx-1].sdchk_pos ;
								a_tbl[idx].next=1 ;
							}
							idx++;			EPT_IDX(idx, ActTbl);
						}
					}
					FILL_WAIT_MOTOR_NEAR(looppos[i][AXIS_X],a_tbl ,dw ,no ,idx)	;
					a_tbl[idx].cmd	= LOOP_UPDATE_LINE;
					a_tbl[idx].u.line	= loop_s[i];		// loop	start line
					a_tbl[idx].mov	= line + 1;			// loop	end	  line
					a_tbl[idx].sdchk_pos = 0;
					a_tbl[idx].next	= 0;
					idx++;		EPT_IDX(idx, ActTbl);
					
					BYTE t_air =	e_air;
					Chk_Loop_e_air(a_tbl,idx,t_air,	looppos[i][AXIS_X],	loop_e_air[i]) ;
					
					a_tbl[idx].cmd	= LOOP_END;
					a_tbl[idx].sdchk_pos = 0;
					a_tbl[idx].next	= 0;
					idx++;		EPT_IDX(idx, ActTbl);
				}
			}
			break;
         }
		case 6:
			if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
			}
			MOVE2S(p_buf,a_tbl ,dw ,lpos , sds,	idx	,  ref_bspeed ,	 no  ,line) ;
			GET_RET_IDX();
			GET_LOOP_POS();

			Chk_e_air(a_tbl,idx,e_air,sds,p_buf->byair) ;
			if(!NEED_AIRTBL(p_buf)){
				a_tbl[idx].cmd	 = SET_AIR;
				a_tbl[idx].u.air	 = e_air = p_buf->byair;
				a_tbl[idx].sdchk_pos	= 0;
				a_tbl[idx].next	 = 0;
				idx++;		EPT_IDX(idx, ActTbl);
			}
			else{
				FILL_AIRTBL(p_buf,air_idx) ;
			}

			cal_dw_X(ept_dw,ept_lpos,sde , sds,line);

			cal_dw_Y(p_buf,dw[AXIS_Y],lpos)	;
			SDWORD tlpos[MAX_AXIS]; //紀錄回原點時各軸位置的正負號
			for(int8 axis=AXIS_Z; axis < MachineStatus.axis_no;	axis++ ){
				cal_dw_ZABC(p_buf,axis,dw[axis],ept_lpos,tlpos) ;
			}
			bool has_y = (dw[AXIS_Y]) ;
			bool has_a=  (dw[AXIS_A] ) ;
			bool cond_a = condx && (has_a)  ;
			bool cond_y= condx && (has_y)  ;
			modify_a=  cond_a  ;


			if(cond_y){
				ADD_SAVE_Y_MOV(a_tbl,idx,has_y? dw[AXIS_Y]: 0 ) ;
				if(!has_a && MachineStatus.Y_Encoder != 2){
					mdy_dw(dw[AXIS_Y]) ;
				}
			}

         int8 axis;
			for( cref=0, axis=0; axis <	MachineStatus.axis_no; axis++ ){
				dt = filltbldt(axis ,dw , ref,cref) ;
			}
			
			//探針停各軸，mode==2，A軸補走 cmd
			if(MachineStatus.Touch_Stop_Flag==2	&& T_Stop_idx && CHK_ROTW(AXIS_A)){
				a_tbl[idx].cmd = T_STOP_OFFSETA;
				a_tbl[idx].next	= 0;
				idx++;		EPT_IDX(idx, ActTbl);
			}		
						
			has_x =false ;
			for( axis=0; axis <	MachineStatus.axis_no; axis++ ){
				if(	dw[axis] ){
					MFill_BreakCnt
					if(	axis ==	AXIS_X ){
						a_tbl[idx].cmd = axis +	MOVE_X;
						has_x=true ;
                    }
					else
						a_tbl[idx].cmd = axis +	(p_buf->byth==TH_ERR?MISS_X:MOVE_X);
					if(axis == AXIS_Y){
						a_tbl[idx].StartWire= (BcdToBin(6, p_buf->dval[AXIS_Y]) >= 30000L)? true : false ;
					}
					a_tbl[idx].ref	  =	cref/(RATIO);
					a_tbl[idx].mov	  =	dw[axis];
					fill_acttbl_idms(axis,a_tbl,idx,dw) ;
					
					
					
					
					
#if 1
					a_tbl[idx].u.dst_pos = get_dst_pos(axis,dw[axis],lpos,tlpos);
#else
					a_tbl[idx].u.dst_pos = lpos[axis];
#endif
					a_tbl[idx].sdchk_pos	 = 0;
					a_tbl[idx].next	  =	1;
					if(	(has_x) && (axis==AXIS_Y)){
						//X軸命令和Y軸命令對調
						CHG_a_tbl_XY								
					}
					if(CHK_ROTATE_A(axis)){
						ADD_OFFSET_Y(a_tbl ,idx) ;
					}
					idx++;		EPT_IDX(idx, ActTbl);
				}
			}

			if(cond_y){
      	if(has_a){
					ADD_MDY_GAPY(a_tbl,idx,has_a) ;
        }
        else{
        	ADD_Modify_y(a_tbl,idx,has_a) ;//G6
        }
      }
			for( axis=0; axis <	MachineStatus.axis_no; axis++ ){
				if(	dw[axis] && Axis_ToPos){
					ADD_WaitMotorNear(a_tbl,idx,axis,2) ;//G6
				}
			}
			
			ADD_Delay(a_tbl,idx ,dw,bDelay) ;

			a_tbl[idx].cmd	= UPDATE_LINE;
			a_tbl[idx].u.line	= line+1;
			MDY_UPDATE_LINE ;
			a_tbl[idx].sdchk_pos = 0;
			a_tbl[idx].next	= 0;
			idx++;		EPT_IDX(idx, ActTbl);
			break;
		}
	}
#if 1
//	Chk_e_air(a_tbl,idx,e_air,0,0) ;
#else
	a_tbl[idx].cmd		= SET_AIR;
//	a_tbl[idx].u.air	= ProgBuf[0].air & e_air;
	a_tbl[idx].u.air	= 0	;
	a_tbl[idx].chk_pos	= 0;
	a_tbl[idx].next		= 0;
	idx++;
#endif

	dt =	BMOTORGRID_X;
	if(	ret_line !=	PROG_VAL_NULL ){
		if(	(lpos[AXIS_X]-ret_pos)!=0 ){
			pos = sdDifGrid(lpos[AXIS_X],ret_pos) ;
			if(	pos	> 0	){
				if(	(DWORD)pos > dt/2 )	pos	= dt	- pos;
				else			 pos = -pos;
			}
			else{
				pos	= -pos;
				if(	(DWORD)pos > dt/2 )	pos	= -((SDWORD)dt -	pos);
			}

			a_tbl[idx].cmd		 = MOVE_X;
			a_tbl[idx].ref		 = ((long long)ref_bspeed *(pos<0?-pos:pos))/(RATIO);
			if(NewH){
				dw[0]= pos ;
				fill_acttbl_idms(AXIS_X,a_tbl,idx,dw) ;
			}
			a_tbl[idx].mov		 = pos;
			a_tbl[idx].u.dst_pos = ret_pos;
			a_tbl[idx].sdchk_pos	 = 0;
			a_tbl[idx].next		 = 0;
			idx++;		EPT_IDX(idx, ActTbl);
		}
	}
	else{





#if 1
		if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
		}
		sds=dt ;
		Grid2Unit(AXIS_X,sds) ;
		if (lpos[AXIS_X]<0){ //當X軸單位為角度時，若最後位置在負方向直接回到0，不回到3600
			sds = 0;
		}
		MOVE2S(&ProgBuf[line],a_tbl ,dw ,lpos , sds,	idx	,  ref_bspeed ,	 no	, line) ;
#else
		TO_GRID_NOT_ROTATE(AXIS_X,lpos[AXIS_X]) ;
		if(	(pos=t-lpos[AXIS_X])!=0	){
			a_tbl[idx].cmd		 = MOVE_X;
			a_tbl[idx].ref		 = ((long long)ref_bspeed*(pos<0?-pos:pos))/(RATIO);
			a_tbl[idx].mov		 = pos;
			if(NewH){
				dw[0]= pos ;
				fill_acttbl_idms(AXIS_X,a_tbl,idx,dw) ;
			}
			SDWORD tpos= dt ;
			Grid2Unit(AXIS_X,tpos) ;
			a_tbl[idx].u.dst_pos = tpos;
			a_tbl[idx].chk_pos	 = 0;
			a_tbl[idx].next		 = 0;
			idx++;
		}
#endif




		RetTblIdx =	0;
	}

	
	
	a_tbl[idx].cmd		= UPDATE_LINE;
	a_tbl[idx].u.line	= ret_line==PROG_VAL_NULL?0:ret_line;
	a_tbl[idx].sdchk_pos	= 0;
	a_tbl[idx].next		= 0;
	idx++;		EPT_IDX(idx, ActTbl);
	
	a_tbl[idx].cmd = END_ACT ;  //
	
	static bool	first_time=true	;
   first_time;
	//修整捲取軸
	for(int	i=0	; i	< 4	; i++){
		if((flag_ZABC[i])){
			for(int	j=idx-1	; j	>=0	; j--){
				if(a_tbl[j].cmd	== MOVE_Z+i){
					BYTE axis= AXIS_Z+i;
					a_tbl[j].cmd= ZRT_Z+i ;
					//加入WAIT_ZRT_X
					a_tbl[idx].cmd		= WAIT_ZRT_X;
					a_tbl[idx].sdchk_pos	= axis;
					a_tbl[idx].next		= 0;
               		idx++ ;		EPT_IDX(idx, ActTbl);
					//  使得原點感測器熄滅
					bool spin_mdy=  (MachineStatus.SPIN_MDY&0xf) && (CHK_SPIN(axis));
					if(MachineStatus.motor[axis] &&(spin_mdy)){
						SDWORD mov=30 ;
						DWORD ref ;
						cal_zrtref(axis,ref) ;
						ref *=mov ;
						ref /= BcdToBin(MOTOR_GRADS_BCD,MachineStatus.motor_grads[axis]) ;
						a_tbl[idx].cmd= MOVE_X+axis ;
						a_tbl[idx].mov	  =	-mov ;
						a_tbl[idx].ref=ref ;
						a_tbl[idx].u.dst_pos = 0;
						a_tbl[idx].sdchk_pos	 = 0;
						a_tbl[idx].next	  =	0;
						idx++ ;		EPT_IDX(idx, ActTbl);
						ADD_WaitMotorNear(a_tbl , idx, axis,1) ;//修整捲取
					}
					break ;
				}
			}

		}
	}

#if 1
	//修整夾耳軸
	if((AutoHook.byaxis != 0xff)){
		//加入WAIT_ZRT_X
		a_tbl[idx].cmd		= WAIT_ZRT_X;
		a_tbl[idx].sdchk_pos	= AutoHook.byaxis;
		a_tbl[idx].next		= 0;
        idx++ ;			EPT_IDX(idx, ActTbl);
		for(int i=0 ; i < 5 ; i++){
			if((AutoHook.byaxis == MOVE_Z+i)){
				for(int	j=idx-1	; j	>=0	; j--){
					if((a_tbl[j].cmd	== MOVE_Z+i)){  //檢查格數少於130
						if((a_tbl[j].mov < 130) && (a_tbl[j].mov > 20)){
							a_tbl[j].cmd= ZRT_Z+i ;
							//降低回原點速度
							a_tbl[j].ref *=(BcdToBin(3,MachineStatus.Rate[AutoHook.byaxis])*10) ;
							a_tbl[j].ref /=(BcdToBin(4,MachineStatus.wZeroSpd[AutoHook.byaxis])) ;
                  		}	
						break ;
					}
				}
			}
		}
	}
#endif
	if(MachineStatus.SPIN_ZRT){
		a_tbl[idx].cmd		= CHK_SPIN_ZRT;
		a_tbl[idx].mov	= BcdToBin(4, MachineStatus.SPIN_ZRT);
		a_tbl[idx].next		= 0;
		idx++;		EPT_IDX(idx, ActTbl);
		a_tbl[idx].cmd		= WAIT_SPIN_ZRT;
		a_tbl[idx].sdchk_pos	= 0;
		a_tbl[idx].next		= 0;
		idx++;		EPT_IDX(idx, ActTbl);
	}
	
	a_tbl[idx].cmd		= END_ACT;
	a_tbl[idx].sdchk_pos	= 0;
	a_tbl[idx].next		= 0;
	idx++;		EPT_IDX(idx, ActTbl);
	
	
	sort_airtbl(air_idx) ;
	
	
	
	
#if 0	
//--各軸加減速--------------------------------------------------
	if (MachineStatus.UsePMfun == 0x1){
		if(ChkUsePMfun()){
			GenPMfun(a_tbl, idx);
			if (MachineStatus.SPDLinkMode==0x1)Mdy_PMfun(a_tbl,MOVE_Y);
		}
	}
//---------------------------------------------------------------	
#endif



	
	if((MachineStatus.TDecDisA[0] !=0)||(MachineStatus.TDecDisA[1] !=0)||(MachineStatus.TDecDisA[2] !=0)||(MachineStatus.TDecDisA[3] !=0)){
		for(int i=0 ; i < idx ; i++){
			int touchno=-1 ;
			if(a_tbl[i].cmd == SET_TOUCH){
				BYTE th = a_tbl[i].u.t.touch;
				if(	(th==TH1_STP	|| th==TH1_CHK)&& (MachineStatus.TDecDisA[0] !=0) ){
					touchno=0 ;
				}														
				else if( (th==TH2_STP ||	th==TH2_CHK)&& (MachineStatus.TDecDisA[1] !=0)	){													
					touchno=1 ;
				}																						
				else if( (th	== TH3_STP) && (MachineStatus.TDecDisA[2] !=0)){																
					touchno=2 ;
				}																						
				else if( (th	== TH4_STP)&& (MachineStatus.TDecDisA[3] !=0) ){																
					touchno=3 ;
				}
				//有探針設定
				if(touchno >=0){
					i++ ;
					if((a_tbl[i].cmd == SETSPEED_PMFUN)&& (a_tbl[i+1].cmd == MOVE_Y)){
						i+=1 ;
						SetTDec(i,touchno) ;
					}
					else if((a_tbl[i+1].cmd == SETSPEED_PMFUN)&&(a_tbl[i+2].cmd == MOVE_Y)){
						i+=2 ; 
						SetTDec(i,touchno) ;
					}
					else{
						continue ;
					}
				}
			}
		}
	}
	//找到第一個MOVE_Y
	for(int i=0;i < idx ; i++){
		if(a_tbl[i].break_cnt != 0 && a_tbl[i].cmd == MOVE_Y){
			first_move_y = i ;
			break ;
		}
	}

#if	 (SAVE_ACTTBL)
	if(first_time){

			DumpAirTbl(air_idx) ;
	}
	if(first_time){
		DumpActTbl(idx) ;
		first_time=false ;
	}
#endif




}

void MakeAutoActTbl_SOL	(short mode)
{
	mode = mode ;
	
	ActTbl_t HUGE  *a_tbl;
	ProgType_t HUGE	*p_buf ;

	bool 		flag_ZABC[4] = {false ,false ,false,false} ;
	bool 		flag_spd_th = false;
	BYTE  	loop_e_air[MAX_LOOP] ;
	BYTE  	e_air ;
	BYTE   	axis, seq[MAX_AXIS][MAX_AXIS] ;
	WORD   	idx, speed, line ;
	WORD   	air_idx ;
	WORD   	ret_line, loop_no ;
	WORD   	wi ;
	WORD 		bDelay[MAX_AXIS] ;
	WORD 		bspeed ;
	WORD 		bspd ;
	SWORD  	loop_s[MAX_LOOP],	loop_e[MAX_LOOP] ,	zabcend[MAX_AXIS] ;
	DWORD 	ref[MAX_AXIS] ,G1ref[MAX_AXIS] ;
	DWORD 	oref[MAX_AXIS],oG1ref[MAX_AXIS] ;
	DWORD 	spd_th_ref[MAX_AXIS] ;	
	DWORD 	ref_bspeed ;
	SDWORD 	pos, ret_pos, dw[MAX_AXIS], lpos[MAX_AXIS] ;
	SDWORD  sds, sde ;
	long long  	dt, cref ;
	long long  	spd_th_cref ;
	bool		has_WaitNearY=true; //false表示Y軸有移動,要加到定位
	bool		flag_DISABLE_RPAIR_Y=false;
	ept_DWORD ept_oref=
#ifdef Bound_Check
    {&oref[0], &oref[0] ,&oref[MAX_AXIS]}
#else
     oref
#endif
;
	ept_DWORD ept_oG1ref=
#ifdef Bound_Check
    {&oG1ref[0], &oG1ref[0] ,&oG1ref[MAX_AXIS]}
#else
     oG1ref
#endif
;		
	ept_SDWORD	ept_dw=
#ifdef Bound_Check
    {&dw[0],&dw[0],&dw[MAX_AXIS]}
#else
     dw
#endif
;
	ept_SDWORD ept_lpos=
#ifdef Bound_Check
      {&lpos[0],&lpos[0],&lpos[MAX_AXIS]}
#else
     lpos
#endif
;
	ept_bool	ept_flag_ZABC=
#ifdef Bound_Check
    {&flag_ZABC[0],&flag_ZABC[0],&flag_ZABC[4]};
#else
     flag_ZABC;
#endif








	
	PAUSE_Y = false;//初始化Gcode旗標
	
	bspeed = (WORD)BcdToBin(3, MachineStatus.speed[MachineStatus.speed_mode]) ;	// binary speed
		
	cal_ref(&ref_bspeed,bspeed);
	
	for(axis =0 ; axis < MAX_AXIS ; axis++){
		EPT_IDX(axis, bDelay);
		bDelay[axis] = (WORD)BcdToBin(3, MachineStatus.AxisDelay[axis]) ;//各軸參數:延遲
	}

	air_idx= idx   = 0;
	sds=sde=0 ;
	a_tbl =	ActTbl;
	p_buf =	ProgBuf;
	for( axis=0; axis <	MAX_AXIS; axis++ ){		
		EPT_IDX(axis, lpos);
		lpos[axis] = 0;
	}
	WORD no=find_changepoint() ;


	make_virtual_move(lpos)	;
	for(int axis =0 ; axis< MAX_AXIS ; axis++){
		zabcend[axis]=lpos[axis];
	}
	INIT_LOOP();
	//求出各軸的參考時間值(ms)
	cal_ref(ept_oref) ;
	cal_G1ref(ept_oG1ref) ;
	//紀錄所有的G9
	len_g9_struct =0 ;
	for(line = AutoHook.byline ;ProgBuf[line].bygcode; line++ ){
		p_buf= ProgBuf+line ;
		if(p_buf->bygcode == 9){
			SDWORD incy ;
			
			EPT_IDX(len_g9_struct, g9_struct);
			g9_struct[len_g9_struct].startl= (WORD)BcdToBin(3, ProgBuf[line].dval[START_X]);
			g9_struct[len_g9_struct].endl= (WORD)BcdToBin(3, ProgBuf[line].dval[END_X]);
			if(	p_buf->dval[AXIS_Y]!=PROG_VAL_NULL && p_buf->dval[AXIS_Y]!=0 ){
				incy	 = BcdToBin(6, p_buf->dval[AXIS_Y]);
				incy 	*= ((p_buf->bysign[AXIS_Y]&0x7f)==PLUS_SIGN?1:-1);
				TO_GRID_NOT_ROTATE(AXIS_Y,incy) ;
				g9_struct[len_g9_struct].incy= incy;
				len_g9_struct++ ;
			}
		}
		//找到最後一行的汽缸設定
		else if(((p_buf->bygcode >= 1) && (p_buf->bygcode <= 4))|| (p_buf->bygcode == 6)){
			e_air = p_buf->byair ;
		}
	}
	

	//2012_0903T_Stop計算各軸格數------------------------------------------------------------------------------------------------	
	//初始化
	T_Stop_idx=0;													//共?組探針
	T_Stop_idxLast=0;											//最後一組探針
	T_Stop_MdyVAL_idx=0;									//目前?組探針
	T_Stop_HaveTouch_Flag=false;					//是否有探到
	T_Stop_Axis=0;												//目前探針停軸狀態
	SDWORD T_Stop_DwG6Last[MAX_AXIS_8];		//各軸G6前最後格數
	int8   T_Stop_G6seq[MAX_AXIS_8];

	if(MachineStatus.Touch_Stop_Flag){
		for(int xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
			T_Stop_G6seq[xaxis]	=-1;	
			T_Stop_Dw[xaxis]		=	0;
			T_Stop_MdyVAL[axis]	= 0;			//補走格數
			T_Stop_Amov_flag		= false;	//Mode==2用
		}
		T_Stop_MdyVAL_Y=0;							//Y_補走格數
		int xT_idx=0;
    	
		for(line = AutoHook.byline ;ProgBuf[line].bygcode; line++ ){
			p_buf = ProgBuf+line ;
			int xaxis, xGcode=ProgBuf[line].bygcode;
			SDWORD xpos[MAX_AXIS_8]={0,0,0,0,0,0,0,0};	//目前位置
			
			//此行有探針，則紀錄上一行的格數---探針要到此格數後才可以Touch，避免馬達過快，停馬達時讀錯位置
			if(p_buf->byth > TH_NULL){
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
					T_Stop_DwTouch[xT_idx][xaxis] = T_Stop_Dw[xaxis];
				}
			}
    	
			if(xGcode==1 ||	xGcode==2||	xGcode==3||	xGcode==4||	xGcode==7){
				//開始計算各軸格數
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){					
					if( p_buf->dval[xaxis] != PROG_VAL_NULL ){
						xpos[xaxis] = BcdToBin(6, p_buf->dval[xaxis]);	
						TO_GRID(xaxis, xpos[xaxis]);					
						xpos[xaxis] *= ((p_buf->bysign[xaxis] & 0x7f)==PLUS_SIGN? 1:-1)	;		
						T_Stop_Dw[xaxis]	=	xpos[xaxis];
					}   	
				}
			} 
			else if(xGcode==6){
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
					T_Stop_G6seq[xaxis] = p_buf->byseq[xaxis];	//G6回原點方式
					if(p_buf->byseq[xaxis]!=NULL_ZRT){ //  != " 0->ZERO "
						T_Stop_DwG6Last[xaxis] = T_Stop_Dw[xaxis];	//紀錄G6前，最後未置
						T_Stop_Dw[xaxis] = 0;
					}
				}
			}
			//寫入探針位置
			if(p_buf->byth > TH_NULL){
				for(xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){	
					T_Stop_HaveVAL[xT_idx][xaxis] = xpos[xaxis];
				}
				xT_idx++;
			}
		}
		//修正_T_Stop，(捲取軸||轉芯)最後位置，並判斷正反轉
		for(int xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
			//修正_T_Stop，(捲取軸||轉芯)最後位置
			if(((CHK_SPIN(xaxis))||CHK_ROTQ(xaxis)) && (T_Stop_Dw[xaxis]==0) && (T_Stop_G6seq[xaxis]!=NULL_ZRT) && (virtual_zabc[xaxis].flag==false)){ //最後位置==0,且G6方式!="NULL_ZRT" 沒虛擬原點				
				SDWORD g6lpos=0, g6ldw=0;
				g6lpos = T_Stop_DwG6Last[xaxis];
				if(g6lpos<0){
					g6lpos = -g6lpos;	
				}
				g6ldw = g6lpos%BMOTORGRID(xaxis);
				
				if(((T_Stop_G6seq[xaxis]==SMART_ZRT) &&	(g6ldw>=(BMOTORGRID(xaxis)/2))) || T_Stop_G6seq[xaxis]==PLUS_ZRT){ //回原點方式== (S->ZERO && 大於(3200/2))	||	"+ ->ZERO"					
					if(g6lpos>BMOTORGRID(xaxis) && (!CHK_ROTATE_A(xaxis))){
						T_Stop_Dw[xaxis] = g6lpos+(BMOTORGRID(xaxis)-g6ldw);
					}
					else {
						T_Stop_Dw[xaxis] = BMOTORGRID(xaxis);
					}
				}
				else if(((T_Stop_G6seq[xaxis]==SMART_ZRT)	&& (g6ldw<(BMOTORGRID(xaxis)/2)))	|| T_Stop_G6seq[xaxis]==MINUS_ZRT){	//回原點方式== (S->ZERO && 小於(3200/2))	||	"- ->ZERO"					
					if(g6lpos>BMOTORGRID(xaxis)	&& (!CHK_ROTATE_A(xaxis))){
						T_Stop_Dw[xaxis] = g6lpos-g6ldw;
					}
					else {
						T_Stop_Dw[xaxis] = 0;
					}
				}
			}	
		}
	}
	//----------------------------------------------------------------------------------------------------------------------------------
	
	
	
	ProgCur_Gcode=ProgBuf[0].bygcode; 
	//開始處理所有的命令行
	for( line=AutoHook.byline; ProgBuf[line].bygcode; line++ ){
		p_buf =	ProgBuf+line;
		if(p_buf->bygcode	== ' '){
			if((idx	>= 1) && (a_tbl[idx-1].cmd == UPDATE_LINE)){
				EPT_IDX(idx, ActTbl);
				a_tbl[idx-1].u.line	+=1;
			}
			continue ;
		}
		sds =	BcdToBin_X(	p_buf->dval[START_X]);
		if(GetSign(p_buf,START_X) & 0x7f){
			sds=-sds ;
		}
		sde =	BcdToBin_X(	p_buf->dval[END_X]);
		if(GetSign(p_buf,END_X) & 0x7f){
			sde=-sde ;
		}
		

		if(Has_spd(p_buf)&& (p_buf->bygcode  !=7)){ //G7:SPD當延遲用
			speed=bspd=(WORD)BcdToBin(3, p_buf->wspd) ;
		}
		else{
			speed=bspd= bspeed ;
		}
		
		//決定此行命令的各軸G2速度
		cal_ref(ref,speed) ;
		
		spd_th_ref[AXIS_X] = 0;
		flag_spd_th = false; 
		
		if(MachineStatus.WorkMode == 1){ //生產速率(RATE)
			double tspd 	= (double)BcdToBin(3, p_buf->wspd)*((MachineStatus.SPDMode ==0)?1.0:0.1) ; //變速度
			double tRate 	= (double)BcdToBin(4, MachineStatus.Rate[AXIS_X]) ; //主軸(X)速度
			double  tspeed = (double)BcdToBin(3, MachineStatus.speed[MachineStatus.speed_mode]) ; //生產速率
						
			if(Has_spd(p_buf)){ //有變速度
				if (tspd > tRate)tspd = tRate;//變速度max即主軸速度100
				cal_ref(ref,tspd) ; 					//主軸速度=變速度
			}
			else{ 													//沒有變速度
				cal_ref(ref,tspeed) ; 				//主軸速度=生產速率
			}

#ifdef SPD_TOUCH
			if ((CHK_SPD_TOUCH(p_buf) && (!NEED_AIRTBL(p_buf))) || 
				  (line>0 && (Has_spd(p_buf)) && (p_buf->bygcode==2) && NEED_AIRTBL(p_buf-1))){ //自動生產時針對G2: 1.同時設SPD及探針(非汽缸畫面),2.設SPD且探針超前(汽缸畫面),要以全速執行,再由sc8254先降速,後全速
					flag_spd_th = true;
					spd_th_ref[AXIS_X] = ref[AXIS_X]; //測試要變速
					//cal_ref(ref,tspeed) ; 						//自動要全速
			}
#endif
			bool flag_spd_axis = false;
			for(uint8 axis = AXIS_Y ; axis < MachineStatus.axis_no ; axis++){
				ref[axis]   = oref[axis] ; 																			//G2-----其他各軸仍為馬達速度，(同動時若有主軸移動靠主軸限速(能達限速條件是主軸為同動中最慢的軸,不然仍是受同動中最慢軸配速)，若無則以原速度)			
				G1ref[axis] = ref[axis]*tRate/((Has_spd(p_buf))?tspd:tspeed) ; 	//G1-----其他各軸馬達速度依生產速度或變速度做比率配速
				if(MachineStatus.G2Mode == 1){
					ref[axis]= G1ref[axis] ;
				}
				if (axis == ServoCutter_axis){ //伺服切刀G1按照原G2速度，不降速(伺服切刀通常都單獨動且速度一致)
					G1ref[axis] = ref[axis];
				}				
			}
		}
		else { //生產速度(RPM)
			for(BYTE axis=AXIS_Y ; axis < MachineStatus.axis_no ; axis++){    	
				EPT_IDX(axis, ref);
				ref[axis]		= oref[axis]*bspeed/bspd ;
				G1ref[axis]	= oG1ref[axis]*bspeed/bspd ;
								
				//以馬達速度為上限,超過改成馬達上限
				if(ref[axis] < oref[axis]){
					ref[axis]=oref[axis] ;
				}
				if(G1ref[axis] < oref[axis]){
					G1ref[axis]=oref[axis] ;
				}
			}
		}

		//Gcod標記，紀錄送線暫停用
		if((p_buf->align_byte)&0x80){
			PAUSE_Y=(!PAUSE_Y);
		}

		//ini_var
		a_tbl[idx].spd_th.ref    = 0;
		a_tbl[idx].spd_th.sc8254 = 0;
		a_tbl[idx].loopref       = 0;
		a_tbl[idx].loopmov       = 0;
		a_tbl[idx].break_cnt     = 0;


		bool has_x ;
		bool condx = CHK_ROTW(AXIS_A) && EXT_ENCODER_MDY ;
		modify_a= false ;
		switch(	p_buf->bygcode )
		{
		case 1:	 sds = sde;
		case 2:
			{
				if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
				}
				MOVE2S(p_buf,a_tbl ,dw ,lpos , sds,	idx	,  ref_bspeed ,	 no	,line) ;
				GET_RET_IDX();
				GET_LOOP_POS();
				SET_TOUCH_AIR(p_buf,a_tbl,idx,air_idx,sds,ept_flag_ZABC,e_air) ;
				//計算各軸欲走的格數
				cal_dw_X(ept_dw,ept_lpos,sde,sds,line) ;
				cal_dw_Y(p_buf,dw[AXIS_Y],lpos)	;
				cal_dw_ZABC(p_buf,ept_dw,ept_lpos) ;
				
				//如果使用G2歸零，且有探針停各軸(Mode==2)，A軸在此時機補償
				if(MachineStatus.Touch_Stop_Flag==2	&& T_Stop_idx	){
					if(dw[AXIS_A]!=0 && lpos[AXIS_A]==0	&& CHK_ROTW(AXIS_A)){
						a_tbl[idx].cmd = T_STOP_OFFSETA;
						a_tbl[idx].next	= 0;
						idx++; EPT_IDX(idx, ActTbl);
					}						
				}
				if((ServoCutter_axis!=0)&& (dw[ServoCutter_axis] !=0)){
					EPT_IDX(ServoCutter_axis, lpos);
					EPT_IDX(ServoCutter_axis, dw);
					if(dw[ServoCutter_axis] >0){
						lpos[ServoCutter_axis]=dw[ServoCutter_axis]=BcdToBin(6,MachineStatus.CutDist) ;
					}
					else{
						dw[ServoCutter_axis]=-BcdToBin(6,MachineStatus.CutDist) ;
						lpos[ServoCutter_axis]=0 ;
					}
				}
				//檢查是否只有A軸動,Y軸不動且A為轉線
				bool has_y = (dw[AXIS_Y]) ;
				bool has_a = (dw[AXIS_A]) ;

				bool cond_g2 = condx && (p_buf->bygcode == 2) && (has_y) ;      	
				if(cond_g2){
					//產生 SAVE_Y_MOV
					ADD_SAVE_Y_MOV(a_tbl,idx,has_y? dw[AXIS_Y]: 0 ) ;
					if(has_y && !has_a && MachineStatus.Y_Encoder != 2){
						mdy_dw(dw[AXIS_Y]) ;
					}
				}
				modify_a = condx && (has_y)  ;      	
				//決定各軸中速度最慢的為同動的速度
				if((MachineStatus.speed_mode == FAST)){
					// 以x軸的速度為準
					cref = ref[AXIS_X]*dw[AXIS_X] ;
				}
				else{
					if(	p_buf->bygcode !=	1 ){
            uint8 taxis=0 ;
						for( cref=0; taxis <	MachineStatus.axis_no; taxis++ ){
							SDWORD tdw=dw[taxis] < 0 ? -dw[taxis]:dw[taxis] ;
							SDWORD tdw_loop=dw_loop[taxis] < 0 ? -dw_loop[taxis]:dw_loop[taxis] ;
							if((taxis >= AXIS_Z)&&(tdw != tdw_loop)){
							    if(tdw < tdw_loop){
							    	tdw=tdw_loop ;
							  	}
							}
							dt =	(long long)ref[taxis]*tdw;
							if(	cref < dt )	cref = dt;
						}
						if(MachineStatus.WorkMode == 1){ //生產速率(RATE)
							uint16 tspd 	= (uint16)BcdToBin(3, p_buf->wspd) ; //變速度
							uint16 tRate 	= (uint16)BcdToBin(4, MachineStatus.Rate[AXIS_X]) ; //主軸(X)速度
							uint16 tspeed = (uint16)BcdToBin(3, MachineStatus.speed[MachineStatus.speed_mode]) ; //生產速率
							if(tspd>tRate)tspd = tRate;
							if (Has_spd(p_buf)&& tspd<tspeed && flag_spd_th == false){
								cref = cref*tspeed/tspd ; //讓降速更明顯
							}
						}
#if 0
//#ifdef SPD_TOUCH
						if (flag_spd_th){
							spd_th_cref = (long long)spd_th_ref[AXIS_X]*dw[AXIS_X];
							if(	spd_th_cref < cref )	spd_th_cref = cref;
						}
#endif
					}
        }
				has_x =	false;
				DWORD xref =0 ;

				if ((p_buf->bygcode ==2)&&dw[AXIS_Y]&&!(PAUSE_Y)&&UseRepairY(AXIS_Y)&&(GetSign(p_buf,AXIS_Y) & 0x80 || MachineStatus.ToPos[AXIS_Y])){
					//同動、Y軸有移動、有壓紅字、有開整定=>整定前要先到定位
					if (has_WaitNearY==false){
						ADD_WaitMotorNear(a_tbl, idx, AXIS_Y,2) ;
						has_WaitNearY=true;
					}
				}
	
				for(int8  axis=0; axis <	MachineStatus.axis_no; axis++ ){
					if((axis==AXIS_Y)&&(PAUSE_Y)){continue;}
					if(	dw[axis] ||dw_loop[axis] ){
						bool cond23=  condx && (p_buf->bygcode == 1) ;
						bool cond_y= cond23  &&  ((axis == AXIS_Y)&& has_y) ;

						if(cond_y ){
							ADD_SAVE_Y_MOV(a_tbl,idx, (axis==AXIS_Y)? dw[AXIS_Y]:0) ;
							if((axis == AXIS_Y)&& (MachineStatus.Y_Encoder != 2)){
								mdy_dw(dw[AXIS_Y]) ;
							}
						}

						if ((p_buf->bygcode ==1)&&(axis==AXIS_Y)&&UseRepairY(axis)&&(GetSign(p_buf,axis) & 0x80 || MachineStatus.ToPos[axis])){
							//定點移動、Y軸有移動、有壓紅字、有開整定=>整定前要先有定位
							if (has_WaitNearY==false){
								ADD_WaitMotorNear(a_tbl, idx, axis,2) ;
								has_WaitNearY=true;
							}
						}

						MFill_BreakCnt
						
						if(	axis ==	AXIS_X ){
							has_x = true;
							a_tbl[idx].cmd = axis +	MOVE_X;
						}
						else{
							a_tbl[idx].cmd = axis +	(p_buf->byth==TH_ERR?MISS_X:MOVE_X);
						}

						a_tbl[idx].ref = (long long)(p_buf->bygcode!=1?cref:G1ref[axis]*(dw[axis]<0?-dw[axis]:dw[axis]))/(RATIO);
						a_tbl[idx].loopref = (long long)(p_buf->bygcode!=1?cref:G1ref[axis]*(dw_loop[axis]<0?-dw_loop[axis]:dw_loop[axis]))/(RATIO);
#ifdef SPD_TOUCH
						a_tbl[idx].spd_th.ref =0;
						if (flag_spd_th){
							//a_tbl[idx].spd_th.ref = (long long)spd_th_cref/(RATIO);
						}
#endif
						xref = a_tbl[idx].ref ;
            xref;
						if(axis == AXIS_Y){
							a_tbl[idx].StartWire= (BcdToBin(6, p_buf->dval[AXIS_Y]) >= 30000L)? true : false ;
						}
						a_tbl[idx].mov	  =	dw[axis];
						a_tbl[idx].loopmov=dw_loop[axis] ;
						a_tbl[idx].u.dst_pos = lpos[axis];
						a_tbl[idx].sdchk_pos	 = 0;
						a_tbl[idx].next	  =	p_buf->bygcode!=1?1:0;
						//當同動時,y軸先動
						if(	(has_x) && (axis==AXIS_Y) &&	(p_buf->bygcode!=1) ){
							//X軸命令和Y軸命令對調
							CHG_a_tbl_XY						
						}
						if(axis == AXIS_Y || CHK_ROTATE_A(axis)){
							has_WaitNearY=false;
						}
						if(axis == AXIS_Y){
							ADD_INCY(a_tbl,idx,line) ;
						}
						if(CHK_ROTATE_A(axis)){
            	has_a=true  ;
              bool tmodyfy_a=modify_a ;
              if(p_buf->bygcode == 1){
              	modify_a=false ;
              }
							ADD_OFFSET_Y(a_tbl ,idx) ;
							modify_a=tmodyfy_a ;
						}
						
						idx++;		EPT_IDX(idx, ActTbl);
						           	
						if((p_buf->bygcode ==1) && bDelay[axis]){
							ADD_Delay_ms(a_tbl,idx,(bDelay[axis]*10)) ;
						}
						if(p_buf->bygcode == 1){
							if (Axis_ToPos && dw[axis]){
								ADD_WaitMotorNear(a_tbl, idx, axis,2) ;//G1各軸CMD之後
								if (UseRepairY(axis)){
									flag_DISABLE_RPAIR_Y=true;//ADD_DisableRepairY(a_tbl, idx);
									
									has_WaitNearY = true;
								}
							}
						}
						
						//y軸修整
						if(cond_y){
							ADD_Modify_y(a_tbl , idx,((p_buf->bygcode ==1)&&axis == AXIS_Y)? 0: has_a) ;//G1G2
						}
					}
				}

				FILL_WAIT_MOTOR_NEAR(sde,a_tbl ,dw ,no ,idx) ;
				CLR_TOUCH_proc(p_buf,a_tbl,idx) ;
            	
				if(cond_g2){
					if(has_a){
						ADD_MDY_GAPY(a_tbl,idx,has_a) ;
					}
					else{
						ADD_Modify_y(a_tbl , idx,has_a) ;//G1G2
					}
				}
				if(p_buf->bygcode == 2){
					bool wait_y=false;
					for(BYTE axis =0 ; axis <MachineStatus.axis_no; axis++){
						if(Axis_ToPos && dw[axis]){
							ADD_WaitMotorNear(a_tbl,idx,axis,2) ;//G2:同動CMD之後
							if (axis==AXIS_Y)wait_y=true;
						}
					}
					if (wait_y&&UseRepairY(AXIS_Y)){
						flag_DISABLE_RPAIR_Y=true;//ADD_DisableRepairY(a_tbl, idx);
						has_WaitNearY = true;
					}
					ADD_Delay(a_tbl,idx ,dw,bDelay) ;
				}
				a_tbl[idx].cmd = p_buf->byth==TH_ERR?MISS_UPDATE_LINE:UPDATE_LINE;
				a_tbl[idx].u.line	 = line+1;
				MDY_UPDATE_LINE ;
				a_tbl[idx].sdchk_pos	= 0;
				a_tbl[idx].next	 = 0;
				idx++;		EPT_IDX(idx, ActTbl);
			}
			break;
		case 3:
		case 4:
      {
      if(flag_DISABLE_RPAIR_Y){
				flag_DISABLE_RPAIR_Y = false;
				ADD_DisableRepairY(a_tbl , idx);
			}		
			MOVE2S(p_buf, a_tbl, dw, lpos, sds,	idx, ref_bspeed, no, line) ;
			
			GET_RET_IDX();
			GET_LOOP_POS();
			SET_TOUCH_AIR(p_buf,a_tbl,idx,air_idx,sds,ept_flag_ZABC,e_air) ;
			
			cal_dw_X(ept_dw,ept_lpos,sde , sds,line);
			cal_dw_Y(p_buf,dw[AXIS_Y],lpos);
			cal_dw_ZABC(p_buf,ept_dw,ept_lpos);

			//設定好seq
			for(int iseq=0; iseq<MAX_AXIS; iseq++){
				int8 jseq ;
				for(jseq=AXIS_X; jseq<MAX_AXIS; jseq++){
					seq[iseq][jseq] =	0xff;
				}
				jseq = 0;
				//x軸一定是seq=0
				if(iseq == 0){seq[iseq][jseq++] = AXIS_X;}

				for(int8 axis=AXIS_Y; axis<MachineStatus.axis_no;	axis++){
					if((axis==AXIS_Y)&&(PAUSE_Y)){continue;}
					if(p_buf->byseq[axis]==iseq	&& MachineStatus.motor[axis] &&	dw[axis]) seq[iseq][jseq++] = axis;
				}
			}
			
			int cidx=idx ;
			//計算所有seq的運動命令
			if ((p_buf->byseq[AXIS_Y]==0)&&dw[AXIS_Y]&&!(PAUSE_Y)&&UseRepairY(AXIS_Y)&&(GetSign(p_buf,AXIS_Y) & 0x80 || MachineStatus.ToPos[AXIS_Y])){
				//同動、Y軸有移動、有壓紅字、有開整定=>整定前要先到定位
				if (has_WaitNearY==false){
					ADD_WaitMotorNear(a_tbl, idx, AXIS_Y,2) ;
					has_WaitNearY=true;
				}
			}
			
			
			for(int iseq=0; iseq<MAX_AXIS; iseq++){
				if(iseq==0){
					//檢查是否只有X軸移動,且X軸的移動值為0
					if(dw[AXIS_X]==0){
						seq[0][0]=0xff ;
					}
				}

				bool has_a=false,has_y=false ;
				int jseq ;
				for(cref=0, jseq=0; jseq<MachineStatus.axis_no; jseq++){
					uint8 axis ;
					if((axis=seq[iseq][jseq]) != 0xff){
						if(axis == AXIS_Y){has_y=true;}
						else if(axis == AXIS_A){has_a=true;}
						dt = ((axis==AXIS_X)?ref[axis]:G1ref[axis])*(dw[axis]<0?-dw[axis]:dw[axis]);
						if(	cref < dt )	cref = dt;
					}
				}

				bool cond_y= condx && has_y ;
				modify_a= cond_y ;
      	
				if(	cref ){
					has_x = false ;
	    	
					if(cond_y){
						ADD_SAVE_Y_MOV(a_tbl,idx,has_y? dw[AXIS_Y]: 0 ) ;
						if(!has_a&& (MachineStatus.Y_Encoder != 2)){
							mdy_dw(dw[AXIS_Y]) ;
						}
					}
					int jseq ;
					for( dt=0, jseq=0; jseq < MachineStatus.axis_no; jseq++ ){
						if(iseq==0){
							// G4時強迫以0.1秒速為準
							if(p_buf->bygcode==4	&& Has_spd(p_buf)){
								cref= (long long)bspd*100*RATIO ;
							}
						}
      	    
						uint8 axis;
						if((axis=seq[iseq][jseq]) != 0xff){
							
							if ((p_buf->byseq[AXIS_Y]!=0)&&(axis==AXIS_Y)&&(line!=0)&&UseRepairY(axis)&&(GetSign(p_buf,axis) & 0x80 || MachineStatus.ToPos[axis])){
								//定點移動、Y軸有移動、有壓紅字、有開整定=>整定前要先有定位
								if (has_WaitNearY==false){
									ADD_WaitMotorNear(a_tbl, idx, axis,2) ;
									has_WaitNearY=true;
								}
							}



							MFill_BreakCnt
							
							if(axis == AXIS_X){
								a_tbl[idx].cmd = axis +	MOVE_X;
								has_x = true ;
							}
							else{
								a_tbl[idx].cmd = axis +	(p_buf->byth==TH_ERR?MISS_X:MOVE_X);
							}
							if(axis == AXIS_Y){
								a_tbl[idx].StartWire= (BcdToBin(6, p_buf->dval[AXIS_Y]) >= 30000L)? true : false ;
							}
							a_tbl[idx].ref = cref/(RATIO);
							a_tbl[idx].mov = dw[axis];
							a_tbl[idx].u.dst_pos = lpos[axis];
							a_tbl[idx].sdchk_pos = 0;
							a_tbl[idx].next	=	1;
							
							
							//當同動時,y軸先動,將X軸命令和Y軸命令對調
							if((has_x) && (axis==AXIS_Y)){									
								CHG_a_tbl_XY
							}
							
							if(axis == AXIS_Y || CHK_ROTATE_A(axis)){
								has_WaitNearY=false;
							}
							
							if(axis == AXIS_Y){
								int tidx=idx ;
								ADD_INCY(a_tbl,idx,line) ;
								if(tidx != idx){
									dt++ ;
								}
							}
							if(CHK_ROTATE_A(axis)){
								ADD_OFFSET_Y(a_tbl ,idx) ;
								dt++	;
							}
							idx++; EPT_IDX(idx, ActTbl);
							dt++;
						}
					}
					//t用來計算同動的命令個數(a_tbl[].next=1)
					//當dt=0---->什麼事都不作
					//  dt=1 --->將同動命令的.next欄位改為0
					//  dt>1---->補上NULL_ACT_CMD(.next欄位為0),以便和下面將產生的同動命令分隔
					if(	dt ){
						if(dt == 1){
							a_tbl[idx-1].next =	0;
						}
						WORD no_wait=0 ;
						bool wait_y=false;
						for( jseq=0; jseq < MachineStatus.axis_no; jseq++ ){
							uint8 axis;
							if(	(axis=seq[iseq][jseq]) !=	0xff ){
								if(Axis_ToPos && dw[axis]){
									no_wait++ ;
									ADD_WaitMotorNear(a_tbl,idx,axis,2) ;//G34
									if (axis==AXIS_Y)wait_y=true;
								}
							}
						}
      	    
						if (wait_y && UseRepairY(AXIS_Y)){
							flag_DISABLE_RPAIR_Y=true;//ADD_DisableRepairY(a_tbl , idx);
							has_WaitNearY = true;
						}
						if((dt != 1) && (no_wait ==0)){
							a_tbl[idx].cmd	= NULL_ACT_CMD;
							a_tbl[idx].sdchk_pos = 0;
							a_tbl[idx].next	= 0;
							idx++;		EPT_IDX(idx, ActTbl);
						}
	    	
						if(cond_y){          	
							if(has_a){
								ADD_MDY_GAPY(a_tbl,idx,has_a) ;
							}
							else{
								ADD_Modify_y(a_tbl,idx,has_a) ;//G3G4
							}
						}
					}
				}
				FILL_WAIT_MOTOR_NEAR(sde,a_tbl ,dw ,no ,idx) ;
				ADD_Delay(a_tbl,idx,seq[iseq],bDelay) ;
			}
			if((cidx== idx) && (p_buf->bygcode==4)	&& Has_spd(p_buf) ){
				//此行都沒有運動指令,純作delay
				ADD_Delay_ms(a_tbl,idx,bspd*100) ;
			}
			
			
			
			
			CLR_TOUCH_proc(p_buf,a_tbl,idx) ;			
			a_tbl[idx].cmd = p_buf->byth==TH_ERR?MISS_UPDATE_LINE:UPDATE_LINE;
			a_tbl[idx].u.line	 = line+1;
			MDY_UPDATE_LINE ;
			a_tbl[idx].sdchk_pos	= 0;
			a_tbl[idx].next	 = 0;
			idx++;		EPT_IDX(idx, ActTbl);
			break;
    	}
   	case 7:
			if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
				}
			//加入延遲時間
			if(	p_buf->dval[AXIS_Y]!=PROG_VAL_NULL && p_buf->dval[AXIS_Y]!=0 ){
				ADD_Delay_ms(a_tbl,idx,(DWORD)BcdToBin(6, p_buf->dval[AXIS_Y])) ;
			}
			break;
		case 5:
    	{	
//		Chk_e_air(a_tbl,idx,e_air,0,0) ;
			ini_loopchk(false) ;
			a_tbl[idx].cmd	= LOOP_CHECK;
			a_tbl[idx].sdchk_pos = 0;
			a_tbl[idx].next	= 0;
			idx++;		EPT_IDX(idx, ActTbl);

			for( int i=0; i	< loop_no; i++ ){
				if(	loop_e[i] == line ){
					for(int8 axis=0; axis <	MachineStatus.axis_no; axis++ ){
						if(	axis==AXIS_Y ||	!MachineStatus.motor[axis] )  continue;
						
						EPT_IDX(axis, dw);
						if(	(((looppos[i][axis]-lpos[axis])) !=0) && (axis != AutoHook.byaxis) ){							
							dw[axis]= sdDifGrid(axis,looppos[i][axis],lpos[axis]) ;
							a_tbl[idx].cmd	  =	LOOP_X + axis;
							a_tbl[idx].ref	  =	((long long)ref[axis]*(dw[axis]<0?-dw[axis]:dw[axis]))/(RATIO);
							a_tbl[idx].mov	  =	dw[axis];
							a_tbl[idx].u.dst_pos = looppos[i][axis];
							a_tbl[idx].sdchk_pos	 = 0;
							a_tbl[idx].next	  =	0;
							if(CHK_ROTATE_A(axis)){
								a_tbl[idx].next=1 ;
								idx++ ;		EPT_IDX(idx, ActTbl);
								a_tbl[idx].cmd	  =	LOOP_Y;
								a_tbl[idx].ref	  =	a_tbl[idx-1].ref ;
								a_tbl[idx].mov= a_tbl[idx-1].mov ;
								BYTE dir= OFFSET_Y_dir(PLUS_SIGN) ;
								if(dir == MINUS_SIGN){
									a_tbl[idx].mov	= -a_tbl[idx].mov ;
								}
								a_tbl[idx].u.dst_pos=a_tbl[idx-1].u.dst_pos ;
								a_tbl[idx].sdchk_pos=a_tbl[idx-1].sdchk_pos ;
								a_tbl[idx].next=1 ;
							}
							idx++;			EPT_IDX(idx, ActTbl);
						}
					}
					FILL_WAIT_MOTOR_NEAR(looppos[i][AXIS_X],a_tbl ,dw ,no ,idx)	;
					a_tbl[idx].cmd	= LOOP_UPDATE_LINE;
					a_tbl[idx].u.line	= loop_s[i];		// loop	start line
					a_tbl[idx].mov	= line + 1;			// loop	end	  line
					a_tbl[idx].sdchk_pos = 0;
					a_tbl[idx].next	= 0;
					idx++;		EPT_IDX(idx, ActTbl);
					
					BYTE t_air =	e_air;
					Chk_Loop_e_air(a_tbl,idx,t_air,	looppos[i][AXIS_X],	loop_e_air[i]) ;
					
					a_tbl[idx].cmd	= LOOP_END;
					a_tbl[idx].sdchk_pos = 0;
					a_tbl[idx].next	= 0;
					idx++;		EPT_IDX(idx, ActTbl);
				}
			}
			break;
         }
		case 6:
			if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
			}
			MOVE2S(p_buf,a_tbl ,dw ,lpos , sds,	idx	,  ref_bspeed ,	 no  ,line) ;
			GET_RET_IDX();
			GET_LOOP_POS();

			Chk_e_air(a_tbl,idx,e_air,sds,p_buf->byair) ;
			if(!NEED_AIRTBL(p_buf)){
				a_tbl[idx].cmd	 = SET_AIR;
				a_tbl[idx].u.air	 = e_air = p_buf->byair;
				a_tbl[idx].sdchk_pos	= 0;
				a_tbl[idx].next	 = 0;
				idx++;		EPT_IDX(idx, ActTbl);
			}
			else{
				FILL_AIRTBL(p_buf,air_idx) ;
			}

			cal_dw_X(ept_dw,ept_lpos,sde , sds,line);

			cal_dw_Y(p_buf,dw[AXIS_Y],lpos)	;
			SDWORD tlpos[MAX_AXIS]; //紀錄回原點時各軸位置的正負號
			for(int8 axis=AXIS_Z; axis < MachineStatus.axis_no;	axis++ ){
				cal_dw_ZABC(p_buf,axis,dw[axis],ept_lpos,tlpos) ;
			}
			bool has_y = (dw[AXIS_Y]) ;
			bool has_a=  (dw[AXIS_A] ) ;
			bool cond_a = condx && (has_a)  ;
			bool cond_y= condx && (has_y)  ;
			modify_a=  cond_a  ;


			if(cond_y){
				ADD_SAVE_Y_MOV(a_tbl,idx,has_y? dw[AXIS_Y]: 0 ) ;
				if(!has_a && MachineStatus.Y_Encoder != 2){
					mdy_dw(dw[AXIS_Y]) ;
				}
			}

         int8 axis;
			for( cref=0, axis=0; axis <	MachineStatus.axis_no; axis++ ){
				dt =	(long long)ref[axis]*(dw[axis]<0?-dw[axis]:dw[axis]);
				if(	cref < dt )	cref = dt;
			}
			
			//探針停各軸，mode==2，A軸補走 cmd
			if(MachineStatus.Touch_Stop_Flag==2	&& T_Stop_idx && CHK_ROTW(AXIS_A)){
				a_tbl[idx].cmd = T_STOP_OFFSETA;
				a_tbl[idx].next	= 0;
				idx++;		EPT_IDX(idx, ActTbl);
			}		
						
			has_x =false ;
			for( axis=0; axis <	MachineStatus.axis_no; axis++ ){
				if(	dw[axis] ){
					MFill_BreakCnt
					if(	axis ==	AXIS_X ){
						a_tbl[idx].cmd = axis +	MOVE_X;
						has_x=true ;
                    }
					else
						a_tbl[idx].cmd = axis +	(p_buf->byth==TH_ERR?MISS_X:MOVE_X);
					if(axis == AXIS_Y){
						a_tbl[idx].StartWire= (BcdToBin(6, p_buf->dval[AXIS_Y]) >= 30000L)? true : false ;
					}
					a_tbl[idx].ref	  =	cref/(RATIO);
					a_tbl[idx].mov	  =	dw[axis];
					
					
					
					
					
#if 1
					a_tbl[idx].u.dst_pos = get_dst_pos(axis,dw[axis],lpos,tlpos);
#else
					a_tbl[idx].u.dst_pos = lpos[axis];
#endif
					a_tbl[idx].sdchk_pos	 = 0;
					a_tbl[idx].next	  =	1;
					if(	(has_x) && (axis==AXIS_Y)){
						//X軸命令和Y軸命令對調
						CHG_a_tbl_XY								
					}
					if(CHK_ROTATE_A(axis)){
						ADD_OFFSET_Y(a_tbl ,idx) ;
					}
					idx++;		EPT_IDX(idx, ActTbl);
				}
			}

			if(cond_y){
      	if(has_a){
					ADD_MDY_GAPY(a_tbl,idx,has_a) ;
        }
        else{
        	ADD_Modify_y(a_tbl,idx,has_a) ;//G6
        }
      }
			for( axis=0; axis <	MachineStatus.axis_no; axis++ ){
				if(	dw[axis] && Axis_ToPos){
					ADD_WaitMotorNear(a_tbl,idx,axis,2) ;//G6
				}
			}
			
			ADD_Delay(a_tbl,idx ,dw,bDelay) ;

			a_tbl[idx].cmd	= UPDATE_LINE;
			a_tbl[idx].u.line	= line+1;
			MDY_UPDATE_LINE ;
			a_tbl[idx].sdchk_pos = 0;
			a_tbl[idx].next	= 0;
			idx++;		EPT_IDX(idx, ActTbl);
			break;
		}
	}
#if 1
//	Chk_e_air(a_tbl,idx,e_air,0,0) ;
#else
	a_tbl[idx].cmd		= SET_AIR;
//	a_tbl[idx].u.air	= ProgBuf[0].air & e_air;
	a_tbl[idx].u.air	= 0	;
	a_tbl[idx].chk_pos	= 0;
	a_tbl[idx].next		= 0;
	idx++;
#endif

	dt =	BMOTORGRID_X;
	if(	ret_line !=	PROG_VAL_NULL ){
		if(	(lpos[AXIS_X]-ret_pos)!=0 ){
			pos = sdDifGrid(lpos[AXIS_X],ret_pos) ;
			if(	pos	> 0	){
				if(	(DWORD)pos > dt/2 )	pos	= dt	- pos;
				else			 pos = -pos;
			}
			else{
				pos	= -pos;
				if(	(DWORD)pos > dt/2 )	pos	= -((SDWORD)dt -	pos);
			}

			a_tbl[idx].cmd		 = MOVE_X;
			a_tbl[idx].ref		 = ((long long)ref_bspeed *(pos<0?-pos:pos))/(RATIO);
			a_tbl[idx].mov		 = pos;
			a_tbl[idx].u.dst_pos = ret_pos;
			a_tbl[idx].sdchk_pos	 = 0;
			a_tbl[idx].next		 = 0;
			idx++;		EPT_IDX(idx, ActTbl);
		}
	}
	else{





#if 1
		if(flag_DISABLE_RPAIR_Y){
					flag_DISABLE_RPAIR_Y = false;
					ADD_DisableRepairY(a_tbl , idx);
		}
		sds=dt ;
		Grid2Unit(AXIS_X,sds) ;
		if (lpos[AXIS_X]<0){ //當X軸單位為角度時，若最後位置在負方向直接回到0，不回到3600
			sds = 0;
		}
		MOVE2S(&ProgBuf[line],a_tbl ,dw ,lpos , sds,	idx	,  ref_bspeed ,	 no	, line) ;
#else
		TO_GRID_NOT_ROTATE(AXIS_X,lpos[AXIS_X]) ;
		if(	(pos=t-lpos[AXIS_X])!=0	){
			a_tbl[idx].cmd		 = MOVE_X;
			a_tbl[idx].ref		 = ((long long)ref_bspeed*(pos<0?-pos:pos))/(RATIO);
			a_tbl[idx].mov		 = pos;
			SDWORD tpos= dt ;
			Grid2Unit(AXIS_X,tpos) ;
			a_tbl[idx].u.dst_pos = tpos;
			a_tbl[idx].chk_pos	 = 0;
			a_tbl[idx].next		 = 0;
			idx++;
		}
#endif




		RetTblIdx =	0;
	}

	
	
	a_tbl[idx].cmd		= UPDATE_LINE;
	a_tbl[idx].u.line	= ret_line==PROG_VAL_NULL?0:ret_line;
	a_tbl[idx].sdchk_pos	= 0;
	a_tbl[idx].next		= 0;
	idx++;		EPT_IDX(idx, ActTbl);
	
	a_tbl[idx].cmd = END_ACT ;  //
	
	static bool	first_time=true	;
   first_time;
	//修整捲取軸
	for(int	i=0	; i	< 4	; i++){
		if((flag_ZABC[i])){
			for(int	j=idx-1	; j	>=0	; j--){
				if(a_tbl[j].cmd	== MOVE_Z+i){
					BYTE axis= AXIS_Z+i;
					a_tbl[j].cmd= ZRT_Z+i ;
					//加入WAIT_ZRT_X
					a_tbl[idx].cmd		= WAIT_ZRT_X;
					a_tbl[idx].sdchk_pos	= axis;
					a_tbl[idx].next		= 0;
               		idx++ ;		EPT_IDX(idx, ActTbl);
					//  使得原點感測器熄滅
					bool spin_mdy=  (MachineStatus.SPIN_MDY&0xf) && (CHK_SPIN(axis));
					if(MachineStatus.motor[axis] &&(spin_mdy)){
						SDWORD mov=30 ;
						DWORD ref ;
						cal_zrtref(axis,ref) ;
						ref *=mov ;
						ref /= BcdToBin(MOTOR_GRADS_BCD,MachineStatus.motor_grads[axis]) ;
						a_tbl[idx].cmd= MOVE_X+axis ;
						a_tbl[idx].mov	  =	-mov ;
						a_tbl[idx].ref=ref ;
						a_tbl[idx].u.dst_pos = 0;
						a_tbl[idx].sdchk_pos	 = 0;
						a_tbl[idx].next	  =	0;
						idx++ ;		EPT_IDX(idx, ActTbl);
						ADD_WaitMotorNear(a_tbl , idx, axis,1) ;//修整捲取
					}
					break ;
				}
			}

		}
	}

#if 1
	//修整夾耳軸
	if((AutoHook.byaxis != 0xff)){
		//加入WAIT_ZRT_X
		a_tbl[idx].cmd		= WAIT_ZRT_X;
		a_tbl[idx].sdchk_pos	= AutoHook.byaxis;
		a_tbl[idx].next		= 0;
        idx++ ;			EPT_IDX(idx, ActTbl);
		for(int i=0 ; i < 5 ; i++){
			if((AutoHook.byaxis == MOVE_Z+i)){
				for(int	j=idx-1	; j	>=0	; j--){
					if((a_tbl[j].cmd	== MOVE_Z+i)){  //檢查格數少於130
						if((a_tbl[j].mov < 130) && (a_tbl[j].mov > 20)){
							a_tbl[j].cmd= ZRT_Z+i ;
							//降低回原點速度
							a_tbl[j].ref *=(BcdToBin(3,MachineStatus.Rate[AutoHook.byaxis])*10) ;
							a_tbl[j].ref /=(BcdToBin(4,MachineStatus.wZeroSpd[AutoHook.byaxis])) ;
                  		}	
						break ;
					}
				}
			}
		}
	}
#endif
	if(MachineStatus.SPIN_ZRT){
		a_tbl[idx].cmd		= CHK_SPIN_ZRT;
		a_tbl[idx].mov	= BcdToBin(4, MachineStatus.SPIN_ZRT);
		a_tbl[idx].next		= 0;
		idx++;		EPT_IDX(idx, ActTbl);
		a_tbl[idx].cmd		= WAIT_SPIN_ZRT;
		a_tbl[idx].sdchk_pos	= 0;
		a_tbl[idx].next		= 0;
		idx++;		EPT_IDX(idx, ActTbl);
	}
	
	a_tbl[idx].cmd		= END_ACT;
	a_tbl[idx].sdchk_pos	= 0;
	a_tbl[idx].next		= 0;
	idx++;		EPT_IDX(idx, ActTbl);
	
	
	sort_airtbl(air_idx) ;
	
//--各軸加減速--------------------------------------------------
	if (MachineStatus.UsePMfun == 0x1){
		if(ChkUsePMfun()){
			GenPMfun(a_tbl, idx);
			if (MachineStatus.SPDLinkMode==0x1)Mdy_PMfun(a_tbl,MOVE_Y);
		}
	}
//---------------------------------------------------------------		
	if((MachineStatus.TDecDisA[0] !=0)||(MachineStatus.TDecDisA[1] !=0)||(MachineStatus.TDecDisA[2] !=0)||(MachineStatus.TDecDisA[3] !=0)){
		for(int i=0 ; i < idx ; i++){
			int touchno=-1 ;
			if(a_tbl[i].cmd == SET_TOUCH){
				BYTE th = a_tbl[i].u.t.touch;
				if(	(th==TH1_STP	|| th==TH1_CHK)&& (MachineStatus.TDecDisA[0] !=0) ){
					touchno=0 ;
				}														
				else if( (th==TH2_STP ||	th==TH2_CHK)&& (MachineStatus.TDecDisA[1] !=0)	){													
					touchno=1 ;
				}																						
				else if( (th	== TH3_STP) && (MachineStatus.TDecDisA[2] !=0)){																
					touchno=2 ;
				}																						
				else if( (th	== TH4_STP)&& (MachineStatus.TDecDisA[3] !=0) ){																
					touchno=3 ;
				}
				//有探針設定
				if(touchno >=0){
					i++ ;
					if((a_tbl[i].cmd == SETSPEED_PMFUN)&& (a_tbl[i+1].cmd == MOVE_Y)){
						i+=1 ;
						SetTDec(i,touchno) ;
					}
					else if((a_tbl[i+1].cmd == SETSPEED_PMFUN)&&(a_tbl[i+2].cmd == MOVE_Y)){
						i+=2 ; 
						SetTDec(i,touchno) ;
					}
					else{
						continue ;
					}
				}
			}
		}
	}
	//找到第一個MOVE_Y
	for(int i=0;i < idx ; i++){
		if(a_tbl[i].break_cnt != 0 && a_tbl[i].cmd == MOVE_Y){
			first_move_y = i ;
			break ;
		}
	}

#if	 (SAVE_ACTTBL)
	if(first_time){
			DumpAirTbl(air_idx) ;
	}
	if(first_time){
		DumpActTbl(idx) ;
		first_time=false ;
	}
#endif




}

void MakeAutoActTbl	(short mode)
{
	if(NewH){
		MakeAutoActTbl_NewH(mode) ;
	}
	else{
		MakeAutoActTbl_SOL(mode) ;
	}
}

#endif
