void ini_Unit_Max_Min()
{
	uint8 axis;
	for(axis =0 ; axis < MAX_AXIS ; axis++){
		MachineStatus.Unit[axis]= UNIT_GRID ;
		MachineStatus.Max[axis]= 0x9999999 ;
		MachineStatus.Max_sign[axis]= PLUS_SIGN ;
		MachineStatus.Min[axis]= 0x9999999 ;
		MachineStatus.Min_sign[axis]= MINUS_SIGN ;
	}
}
void restore_Unit_Max_Min()
{
	uint8 axis;
	open_config("rb+") ;
	for(axis =0 ; axis < MAX_AXIS ; axis++){
		load_Unit(axis);
		load_Max(axis);
		load_Min(axis);
	}                            
	close_config() ;
}
void set5217()
{
	char code;
	if (State5217==false){
		DispMsgWin_q(-1, -1, MSG_WIN, "數字鍵1---進入絕對值原點設定\n其餘鍵 ---放棄              " ,"Key 1---Enter ABS Zrt Set\nOther Key---Ouit         ");
	}
	else {
		DispMsgWin_q(-1, -1, MSG_WIN, "數字鍵1---儲存絕對值原點\n其餘鍵 ---放棄          " ,"Key 1---Save ABS Zrt Set\nOther Key---Ouit       ");
	}
	FORCE_PROC_QUEUE ;
	WAIT_NEW_KEY(code);
	ClrMsgWin_q();
	
	if (code == KEY_1){
		State5217 = !State5217 ;
		if(!State5217){
			//原點設定
			uint8 axis;
			for(axis=0  ; axis < MAX_AXIS ; axis++){
				if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2)||
						(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)){
					SDWORD pos ;
					SDWORD cycle ;
					cal_ya_abspos(axis,cycle,pos,ya_abspos.curpos[axis]) ;
					save_ZrtCyePos(axis ,cycle ,pos);
				}
			}
			restore_Unit_Max_Min() ;
		}
		else{
			ini_Unit_Max_Min() ;
		}
		SoftReset() ;
	}
}
//馬達位置轉換   cycle&pos合成--->單一位置(返回值)
long long cal_ya_abspos(uint8 axis,SDWORD cycle,SDWORD pos)
{
	long long mov;
	if (cycle<0)cycle+=MAX_YA_CYCLE;
	
	mov = (long long)cycle*ya_abspos.gear[axis]+pos;

	if(mov < 0){
		mov +=ya_abspos.max[axis] ;
	}
	mov = mov%(ya_abspos.max[axis]);

	return (mov);
}
//馬達位置轉換  單一位置(inpos)分成--->cycle&pos
void cal_ya_abspos(uint8 axis,SDWORD &cycle,SDWORD &pos,long long inpos)
{
	if(inpos < 0){
		inpos +=ya_abspos.max[axis] ;
	}
  cycle=inpos / ya_abspos.gear[axis] ;
  pos= inpos % ya_abspos.gear[axis] ;
  
  if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2)){ //(安川格式)
  	if(cycle >= (MAX_YA_CYCLE/2)){
  			cycle -= MAX_YA_CYCLE ;
		}
	}
}
void save_ZrtCyePos(uint8 axis , SDWORD cycle ,SDWORD  pos)
{/*
	MachineStatus.ZrtCye_sign[axis] = (cycle>0)?PLUS_SIGN:MINUS_SIGN; 
	MachineStatus.ZrtCye[axis] = dBinToBcd(5,abs(cycle));//原點圈數
	MachineStatus.ZrtPos[axis] = dBinToBcd(8,pos); //原點位置
	
	open_config("rb+") ;
	save_ZrtCye(axis) ;
	save_ZrtPos(axis) ;
	close_config() ;*/
}
void zrt_inc(uint8 axis , SDWORD  val)
{
	SDWORD pos = BcdToBin(8,MachineStatus.ZrtPos[axis]);
	SDWORD cycle = BcdToBin(5,MachineStatus.ZrtCye[axis],MachineStatus.ZrtCye_sign[axis]);
  long long zero = cal_ya_abspos(axis,cycle,pos);
  cal_ya_abspos(axis,cycle,pos,zero+val) ;
  	
  save_ZrtCyePos(axis,cycle,pos) ;  	
}
bool chk_zrt_inc(uint8 axis , SDWORD  val)
{
	SDWORD  pos	= BcdToBin(8,MachineStatus.ZrtPos[axis]);
	SDWORD cycle = BcdToBin(5,MachineStatus.ZrtCye[axis],MachineStatus.ZrtCye_sign[axis]);
  long long zero = cal_ya_abspos(axis,cycle,pos);
  long long nzero=zero+val ;
  if((nzero >=ya_abspos.max[axis])|| (nzero < 0)){
  		return(false) ;
	}
	else{
		return(true) ;
	}
}
void PlusOv_zrtoff(uint8 axis)
{
	DWORD motor_pos = (BMOTORGRID(axis)*ya_abspos.ENCR[axis]);
	
	if(ya_abspos.ovzrtoff[axis]!=0){
		if(chk_zrt_inc(axis,motor_pos-ya_abspos.ovzrtoff[axis])){
			zrt_inc(axis,(motor_pos-ya_abspos.ovzrtoff[axis])) ;
		}
		else{
			zrt_inc(axis,-ya_abspos.ovzrtoff[axis]) ;
		}
	}
}
void MinusOv_zrtoff(uint8 axis)
{
	DWORD motor_pos = (BMOTORGRID(axis)*ya_abspos.ENCR[axis]);
	
	if(ya_abspos.ovzrtoff[axis]!=0){
		if(chk_zrt_inc(axis,ya_abspos.ovzrtoff[axis])){
			zrt_inc(axis,ya_abspos.ovzrtoff[axis]) ;
		}
		else{
			zrt_inc(axis,-(motor_pos-ya_abspos.ovzrtoff[axis])) ;
		}
	}
}
void reverse_mov_ZRT_YA_ABS(uint8 axis)
{
	DWORD  ref; 
	uint8  dir,dir_y,temp_about;
	SDWORD mov,inv_mov;
	
	Update_ya_abspos_curpos(axis) ;
  DWORD lpos = (DWORD) dReadAbsPos_com_Real (axis);
  	
	DWORD  pos	 =  BcdToBin(8,MachineStatus.ZrtPos[axis]);
	SDWORD cycle =  BcdToBin(5,MachineStatus.ZrtCye[axis],MachineStatus.ZrtCye_sign[axis]);
  long long zero = cal_ya_abspos(axis,cycle,pos);
	long long cur  = ya_abspos.curpos[axis];
	
	if(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1){
		if (cur>zero){
			mov = (SDWORD)(cur-zero);
			dir = MINUS_SIGN;
		}
		else {
 			mov = (SDWORD)(zero-cur);
    	dir = PLUS_SIGN;
 		}
 		if(mov >=ya_abspos.max[axis]){
 			mov -=ya_abspos.max[axis] ;
		}
 		inv_mov = ya_abspos.max[axis] - mov;
    	
 		if (inv_mov<mov){
 			mov = inv_mov;
 			dir = (dir == MINUS_SIGN)? PLUS_SIGN:MINUS_SIGN;
 		}  
 	}
 	else if (MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2){
 		long long tcur= ya_abspos.curpos[axis] ;
 		if(tcur < 0){
 			tcur +=ya_abspos.max[axis] ;  
 		}
 		if(tcur >= zero){
 			mov =(SDWORD)((tcur-zero)% BMOTORGRID(axis)) ;
 			dir=MINUS_SIGN ;
 		}
 		else{
 			mov = (SDWORD)((zero-tcur)%BMOTORGRID(axis)) ;
 			dir = PLUS_SIGN ;
 		}
 		inv_mov = BMOTORGRID(axis)-mov ;
 		uint8 inv_dir = (dir == PLUS_SIGN)? MINUS_SIGN : PLUS_SIGN ;
 		//5度內就近回原點
 		SDWORD mov5=BMOTORGRID(axis)*5/360 ;
 		if(mov <= mov5){
 		}
 		else if(inv_mov <=mov5){
 			mov = inv_mov ;
 			dir = inv_dir ;
 		}
 		else{
 			//依照原點順序的方向回原點
			uint8 tdir=isPLUS_SIGN(MachineStatus.home_seq_sign[axis])?PLUS_SIGN:MINUS_SIGN ;
#if USE_ABOUT			
			if(MachineStatus.ABOut[axis] !=0){
				tdir = (tdir == PLUS_SIGN)?MINUS_SIGN:PLUS_SIGN ;
			}
#endif
			if(tdir == dir){
			}
			else{
				mov =inv_mov ;
				dir = inv_dir ;
			} 		
 		}
	}
	else if(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1){
		long long sa_mov;
		long long sa_inv_mov;
		if (cur>zero){
			sa_mov = (cur-zero);
			dir = MINUS_SIGN;
		}
		else {
 			sa_mov = (zero-cur);
    	dir = PLUS_SIGN;
 		}
 		if(sa_mov >=ya_abspos.max[axis]){
 			sa_mov -=ya_abspos.max[axis] ;
		}
 		sa_inv_mov = ya_abspos.max[axis] - sa_mov;
    	
 		if (sa_inv_mov<sa_mov){
 			sa_mov = sa_inv_mov;
 			dir = (dir == MINUS_SIGN)? PLUS_SIGN:MINUS_SIGN;
 		}
 		mov = (SDWORD)(sa_mov/ya_abspos.ENCR[axis]);  
 	}
 	else if (MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2){
 		long long tcur= ya_abspos.curpos[axis] ;
 		long long sa_mov;
		long long sa_inv_mov;
 		if(tcur < 0){
 			tcur +=ya_abspos.max[axis] ;  
 		}
 		if(tcur >= zero){
 			sa_mov =((tcur-zero)%(BMOTORGRID(axis)*ya_abspos.ENCR[axis])) ;
 			dir=MINUS_SIGN ;
 		}
 		else{
 			sa_mov =((zero-tcur)%(BMOTORGRID(axis)*ya_abspos.ENCR[axis])) ;
 			dir = PLUS_SIGN ;
 		}
 		sa_inv_mov = (BMOTORGRID(axis)*ya_abspos.ENCR[axis])-sa_mov ;
 		uint8 sa_inv_dir = (dir == PLUS_SIGN)? MINUS_SIGN : PLUS_SIGN ;
 		//5度內就近回原點
 		long long sa_mov5=(BMOTORGRID(axis)*ya_abspos.ENCR[axis])*5/360 ;
 		if(sa_mov <= sa_mov5){
 		}
 		else if(sa_inv_mov <=sa_mov5){
 			sa_mov = sa_inv_mov ;
 			dir = sa_inv_dir ;
 		}
 		else{
 			//依照原點順序的方向回原點
			uint8 tdir=isPLUS_SIGN(MachineStatus.home_seq_sign[axis])?PLUS_SIGN:MINUS_SIGN ;
#if USE_ABOUT			
			if(MachineStatus.ABOut[axis] !=0){
				tdir = (tdir == PLUS_SIGN)?MINUS_SIGN:PLUS_SIGN ;
			}
#endif
			if(tdir == dir){
			}
			else{
				sa_mov =sa_inv_mov ;
				dir = sa_inv_dir ;
			} 		
 		}
 		
 		//Sprintf("axis=%d,cur=%lld,zero=%lld,sa_mov=%lld,dir=%d",axis,ya_abspos.curpos[axis],zero,sa_mov,dir);
 		
 		mov = (SDWORD)(sa_mov/ya_abspos.ENCR[axis]);
	}
	if (mov !=0){		
		MachineStatus.sign[axis]= zrt[axis].sign ;
		MachineStatus.axis_val[axis]= zrt[axis].axis_val ;
		
		cal_zrtref(axis,ref) ;
		ref *=mov ;
		ref /=BMOTORGRID(axis) ;
#if USE_ABOUT		
		temp_about = MachineStatus.ABOut[axis];
		MachineStatus.ABOut[axis] = 0; 
#endif
		Set3701(axis, dir, ref, mov, mov, true, 0,0);
#if USE_ABOUT
		MachineStatus.ABOut[axis] = temp_about;
#endif

		if(CHK_ROTW(axis)){//補線
			uint8 axis_a = AXIS_A ;
			uint8 axis_y = AXIS_Y ;
			dir_y = OFFSET_Y_dir(dir) ;
#if USE_ABOUT
			temp_about = MachineStatus.ABOut[axis_y];
			MachineStatus.ABOut[axis_y] = (MachineStatus.ABOut[axis_a] != MachineStatus.ABOut[axis_y])?1:0;
#endif
			Set3701(AXIS_Y,dir_y,ref, mov, mov, true, 0,0) ;
#if USE_ABOUT			
			MachineStatus.ABOut[axis_y] = temp_about;
#endif
		}
	}
}

void Update_ya_abspos_curpos()
{
	uint8 axis;
	for(axis=0  ; axis < MAX_AXIS ; axis++){
		Update_ya_abspos_curpos(axis) ;
	}
}
void Update_ya_abspos_curpos(uint8 axis)
{
	if(ya_abspos.trace[axis]){
		DWORD cur2016=dReadAbsPos_com_Real(axis)*ya_abspos.ENCR[axis] ;
		if(cur2016 != ya_abspos.curpos2016[axis]){
			SDWORD mov = cur2016-ya_abspos.curpos2016[axis] ;
			long long lcurpos= ya_abspos.curpos[axis] ;
			if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2)){
				ya_abspos.curpos[axis] += mov ;
				ya_abspos.curpos2016[axis]=cur2016 ;
				if(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2){
					if((lcurpos < 0)&& (ya_abspos.curpos[axis] >= 0)){  //正轉溢位
						PlusOv_zrtoff(axis) ;
					}
					else if(ya_abspos.curpos[axis] >=ya_abspos.max[axis]){ //正轉溢位
						ya_abspos.curpos[axis] -=ya_abspos.max[axis] ;
						PlusOv_zrtoff(axis) ;
					}
					else if((lcurpos >= 0)&& (ya_abspos.curpos[axis] < 0)){//反轉溢位
						MinusOv_zrtoff(axis) ;
					}
					else if(ya_abspos.curpos[axis] <= (-ya_abspos.max[axis])){
						ya_abspos.curpos[axis] +=ya_abspos.max[axis] ;
						MinusOv_zrtoff(axis) ;
					}
				}
				else{
					if(ya_abspos.curpos[axis] >= ya_abspos.max[axis]){
						ya_abspos.curpos[axis]-= ya_abspos.max[axis] ;
					}
					else if(ya_abspos.curpos[axis]<0){
						ya_abspos.curpos[axis]+= ya_abspos.max[axis] ;
					}
				}
			}
			else if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)){
				//ya_abspos.curpos[axis] = cal_ya_abspos(axis,ya_abspos.zrtcye_val[axis],(cur2016+ya_abspos.zrtpos_val[axis]));
				ya_abspos.curpos[axis] += mov ; 
				ya_abspos.curpos2016[axis]=cur2016 ;
				if(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2){
					if(ya_abspos.curpos[axis] >= ya_abspos.max[axis]){ //正轉溢位
						ya_abspos.curpos[axis] -=ya_abspos.max[axis] ;
						PlusOv_zrtoff(axis) ;
					}
					else if((lcurpos >= 0) && (ya_abspos.curpos[axis]<0)){//反轉溢位
						ya_abspos.curpos[axis] +=ya_abspos.max[axis] ;
						MinusOv_zrtoff(axis) ;
					}
				}
				else{
					if(ya_abspos.curpos[axis] >= ya_abspos.max[axis]){
						ya_abspos.curpos[axis]-= ya_abspos.max[axis] ;
					}
					else if(ya_abspos.curpos[axis]<0){
						ya_abspos.curpos[axis]+= ya_abspos.max[axis] ;
					}
				}
			}
#if 0
			if( MachineStatus.op_mode == MAN_MODE ){
				SDWORD cycle;
				SDWORD pos;
				cal_ya_abspos(axis,cycle,pos,ya_abspos.curpos[axis]) ;
				char Msgbuf[50];
				sprintf(Msgbuf,"axis_%1d cycle=%d, pos = %d absloc=%lld        ",axis,cycle,pos,ya_abspos.curpos[axis]) ;
				DispStrLine_q(5, STATUS_BAR_LY, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, Msgbuf);
			}
#endif
		}
	}	
}
void cal_gear()
{
	uint8 axis;
	for(axis=0; axis < MAX_AXIS; axis++){	
			DWORD bmotor_grades = BMOTORGRID(axis);
			DWORD bGEAR0 = BcdToBin(5,MachineStatus.GEAR0[axis]) ; //機構格數1圈
			DWORD bGEAR1 = BcdToBin(5,MachineStatus.GEAR1[axis]) ; //馬達格數1圈
			if (bGEAR0==0){
				bGEAR0 = 1;
			}
			DWORD gear = bmotor_grades*bGEAR1/bGEAR0;
			
			ya_abspos.ENCR[axis] = 1; //NEW:三洋回授需要再齒比轉換
			if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)){//NEW
				ya_abspos.ENCR[axis] = SA_ABS_ENCR;//16
			}
			
			if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2)){
				ya_abspos.gear[axis] = gear;
				ya_abspos.max[axis] = gear*MAX_YA_CYCLE ;
				ya_abspos.ovzrtoff[axis] = ya_abspos.max[axis]%bmotor_grades ;
			}
			else if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)){
				ya_abspos.gear[axis] = MAX_SA_CYCLE_POS;
								
				ya_abspos.max[axis] = (long long)ya_abspos.gear[axis]*MAX_YA_CYCLE ;
				ya_abspos.ovzrtoff[axis]= ya_abspos.max[axis]%(bmotor_grades*ya_abspos.ENCR[axis]) ;
			}
	}
}
void ReadAbsMotors()
{
	uint8 axis;
	for(axis=0  ; axis < MAX_AXIS ; axis++){
		ya_abspos.status[axis] = true;
		if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2) ||
			  (MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)){//NEW
			if (ReadKeyDate_flag){
				mDelay(300);
			}
			ya_abspos.zrtpos_val[axis] = 0;
			ya_abspos.zrtcye_val[axis] = ReadAbsMotor(axis);//安川:馬達目前圈數,三洋:馬達圈數及位置
			if (ya_abspos.status[axis]){
				ya_abspos.trace[axis]=true ;
				
				if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)){
					Clr2016s(axis) ; //三洋讀完絕對值馬達位置,已包含圈數和格數,回授一開機是0會對;但如果之後再重讀絕對值位置,目前的回授需清零
				}				
				ya_abspos.curpos2016[axis]=dReadAbsPos_com_Real(axis)*ya_abspos.ENCR[axis] ;//NEW
				ya_abspos.curpos[axis]=cal_ya_abspos(axis,ya_abspos.zrtcye_val[axis],(ya_abspos.curpos2016[axis]+ya_abspos.zrtpos_val[axis]));
			}
			else {
				ReadAbs_Err=true;
			}
		}
	}
}
SDWORD ReadAbsMotor(uint8 axis)
{
	SDWORD zrtbuf=0;
	/*
	in_ReadAbsMotor = true;	
		
	uint8 switchcode=1 ;
	int cnt=0;	
		
//三洋馬達
	if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)){
		uint16 COM2=0x2f8;	 //rs232_base[1]==0x2f8, COM2
		INI_Sprintf() ;
//	Sprintf("Read AXIS_%d Absolute Address......",axis) ;
		uint8 ch3=inportb(COM2+3) ;
		outportb(COM2+3,(ch3|0x18)&0xdf);//改成even parity bit5~3=011
														
		wDosMem(pc_base+0xc20, switchcode); //關鍵盤開軸訊號
		wDosMem(pc_base+0x400*(switchcode-1)+0x18c, (uint8)(0xC0+(axis%8))); 	

		
		int state =0 ;
		uint8 codebuf[8] ;
		struct TIMER timeout_Motor= sTimerSet(5) ;
		do{
			if( KeyBufRIdx != KeyBufWIdx ){
				int code=GetKey() ;
				int addr = code >> 5 ;
				if(addr == state){
//				Sprintf("state=%2d code = %2x",state,code) ;
					codebuf[addr]=code ;
					state++ ;
				}
				else{
					//重來
//				Sprintf("error----->state=%2d code = %2x",state,code) ;
					state=0 ;
				}
				FORCE_PROC_QUEUE ;
				if((state == 8) && (codebuf[7]!= 0xe0)){
					state=0 ;
				}
			}
			cnt++ ;
			if(cnt==0x12345678){
				ya_abspos.status[axis] = false; //time_out
				break ;
			}
		}while((state !=8)) ;

		unsigned long tt=0 ;
		for(int i=6 ;  i >=1 ; i--){
			tt <<=5 ;
			tt +=(codebuf[i]&0x1f) ;
		}
		int cycle= tt>> 12 ;
		int grid= ((tt<< 5)+(codebuf[0]&0x1f)) &0x1ffff ;		
		
		zrtbuf = cycle;
		//ya_abspos.zrtcye_val[axis] = cycle; //三洋絕對值馬達圈數
		ya_abspos.zrtpos_val[axis] = grid;  //三洋絕對值馬達位置


		
		wDosMem(pc_base+0xc20,(uint8) 0); //回復keyboard功能
		wDosMem(pc_base+0x400*(switchcode-1)+0x18c, (uint8)(0)); //關軸訊號
		outportb(COM2+3,ch3);//回復原來的baud設定
		while( KeyBufRIdx != KeyBufWIdx ){	
			GetKey() ;
		}				
	}
//安川馬達    						
	else if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1)||(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2)){
		wDosMem(pc_base+0xc20, switchcode);//關鍵盤 切換軸卡
		wDosMem(pc_base+0x400*(switchcode-1)+0x18c, (uint8)(0x80+(axis%8)));//開軸訊號  
		//讀絕對軸命令
		wDosMem(pc_base+0x400*(switchcode-1)+0x190, (uint8)~(1<<(axis%8))); 	//3N8 ABS_CTL address
		wDosMem(pc_base+0xe6, (uint8)((axis%8)+1));  //新8軸 ABS_CTL address
		cnt=0 ;
		int idx=0;
		uint8 codebuf[8] ;
		bool code_start_flag = false;
		Clr2016s(axis) ;
		WORD lpos=10 ;
		SWORD tpos;
		do{
			if( KeyBufRIdx != KeyBufWIdx ){					
				int code=GetKey() ;					
				if (code == 0x50)code_start_flag = true;
				if (code_start_flag)codebuf[idx++]=code&0x7f;
				if((code&0x7f)== 0x0d)break ;
		    cnt=0 ;      		        
			}
			else{
				cnt++ ;
				if(cnt==0x12345678){
					break ;
				}
			}
		}while(1) ;
		cnt=0 ;
#if 1
		do{
			cnt++ ;
			if(abs(lpos-(WORD)dReadAbsPos_com(axis))>=2){
				cnt=0 ;
				lpos=(WORD)dReadAbsPos_com(axis) ;
			}
			if(cnt == 0x10000)break ;
		}while(1) ;
#endif
		wDosMem(pc_base+0x190, (uint8)0xff); 	//3N8 ABS_CTL address
		wDosMem(pc_base+0xe6, (uint8)0); 		//新8軸 ABS_CTL address
		
		zrtbuf =(codebuf[2]-0x30)*10000+
						(codebuf[3]-0x30)*1000+
				 		(codebuf[4]-0x30)*100+
				 		(codebuf[5]-0x30)*10+
				 		(codebuf[6]-0x30);
		zrtbuf =(codebuf[1]==0x2b)?zrtbuf:-zrtbuf;
		
		if (!code_start_flag)ya_abspos.status[axis] = false;
		if (YAABS_MsgBar){
			char Msgbuf[30];
			sprintf(Msgbuf,"AXIS_%2d, code = %d",axis,zrtbuf) ;
			DispStrLine_q(5, STATUS_BAR_LY, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, Msgbuf);
		}            
		else {            
			lpos=(WORD)dReadAbsPos_com(axis) ; 
			Sprintf("AXIS_%2d, code = %d,lpos=%d,dir=%d",axis,zrtbuf,lpos,MachineStatus.ABDir[axis]) ;
		}             
		sDelay(3) ;						  
		wDosMem(pc_base+0xc20,(uint8) 0); //回復keyboard功能
		wDosMem(pc_base+0x400*(switchcode-1)+0x18c, (uint8)(0)); //關軸訊號
	}
						            
	in_ReadAbsMotor	= false;  
	*/
	return zrtbuf;            
}
void  DispReadAbsMotorFailure()
{
	uint8 axis ;
	INI_DISP_BUF();
	for(axis=0 ; axis < MAX_AXIS ; axis++){
		if (ya_abspos.status[axis] == false){
			Fill_pDispBuf(AxisName[idx_language][axis]);
			Fill_pDispBuf(" 絕 對 位 置 讀 取 失 敗 \n"," Load YA-ABS Motor Failure \n"," Load YA-ABS Motor Failure \n");
		}
	}
	FILL_DISP_BUF(0);
	DispMsgWin_q(-1, -1, ERR_WIN, DispBuf);	
	
	WAIT_NEW_KEY();
	ClrMsgWin_q();
}

bool ChkZrtPos()
{
	uint8 axis ;
	for(axis=0 ; axis < MAX_AXIS ; axis++){
		if ((MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS1) ||(MachineStatus.ZrtMode[axis]==MODE_ZRT_YA_ABS2)||
				(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS1) ||(MachineStatus.ZrtMode[axis]==MODE_ZRT_SA_ABS2)
			)return true;
	}	
	return false;
}
