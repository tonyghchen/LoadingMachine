#include "header.h"
uint8 lDDAState=0;
// short TManMov[2][MANMS] ;
int idx_TManMov ;
int idx_Table ;
int count=0;
int cntdda=0;
int Manidms=0 ;           			//手動加減速時間 
uint16 DDA_idx_Table ;
//void ReciveDDA(int axis,uint32_t dda);
uint32_t Tx(unsigned char TxBuf[], uint32_t u32WriteBytes)
{
		return UART_Write(UART2, TxBuf, u32WriteBytes);
}
void Ini_Feedback(uint8 axis)
{
	lFeedbackCnt16[axis]=rDosMemw(pc_base+2+4*axis) ;  //硬體16bit 回授
	FeedbackCnt[axis]=0 ;
}	
int MReadAdc100()		//value 0~100
{
	int cnt=0 ;
	int adc ;
	do{
		adc=rDosMemw(pc_base+0xe0) ;
		adc=adc/260 ;
		cnt++ ;
	}
	while(((adc >100) || (adc < 0)) && (cnt < 10)) ;
	if(adc > 100)adc=100 ;
	if(adc < 0)adc=0 ;
	return(adc) ;
}
	uint16 GenRatio()
{
	switch(CLOCKType){
		case RUN_CLOCK:
			return(RUN_Ratio) ;
		case STEP_CLOCK:
			if(STEP_DDAState)return(ReadAdc100()*RUN_Ratio/100) ;
			else	return(0) ;
		case TEST_CLOCK:
			return(ReadAdc100()*RUN_Ratio/100) ;
		case OFF_CLOCK:
			return(0) ;
	}
}	
void run_DDA()
{	
// 	Ratio=GenRatio() ;
// 	
// 	if(first_dda && first_speed <100){		//第一條速度遞增(生產延遲) 
// 		//Sprintf("%d",first_speed);																		//生產延遲修改,修改為回原點後firsrdda=1,且測試鈕為零時不動作
// 		if(((MachineStatus.op_mode &&( MachineStatus.op_mode==TEST_MODE))&&(ReadAdc100()*RUN_Ratio/100)) ||MachineStatus.op_mode==RUN_MODE){
// 			first_speed+=0.1;
// 			Ratio=first_speed;
// 			if(MachineStatus.op_mode==RUN_MODE && first_speed>100){
// 				Ratio=GenRatio() ;
// 				first_dda=0;
// 			}
// 			else if(((MachineStatus.op_mode==TEST_MODE)||MachineStatus.op_mode==STEP_MODE) && first_speed>(ReadAdc100()*RUN_Ratio/100)){//測試用生產延遲不到100%會跑到100才降速
// 				Ratio=(ReadAdc100()*RUN_Ratio/100) ;
// 				first_dda=0;
// 			}
// 		}
// 	}
// 	
// 	bool chk_dda=false;
// 	bool static chk_af=false;
// 	static struct TIMER  lTimerTicks;
// 	uint16 qLen;
// 	 static int cnt=0;
// 	 int ddd=0;
// 	if(cnt_Set3701 && (!PORT_STOPRUN || (PORT_STOPRUN && !MachineStatus.SlideLimit) || (PORT_STOPRUN && slide_axis && !MachineStatus.motor[slide_axis]))){
// 		qLen =rDosMemw(pc_base+0xf00) ;
// 		//if(DDATbl[AXIS_X].totalms!=0 && qLen<2)
// 		//	printf("toalms=%d \n",qLen);
// 		for(int i=0 ; (i < 5-qLen) && (cnt_Set3701) ;i++){	//timer會被搶掉4~5ms,從2改5 //test-->run dda會掉11左右 //改回5
// 		int static RatioCnt=0;
// 		if(tRatio!=GenRatio()){//補VR 有跳動?!
// 			if(!RatioCnt){
// 				tGenRatio=GenRatio();
// 				Ratiochk=0;
// 			}
// 			else{
// 				if(!Ratiochk && GenRatio() != tGenRatio)
// 					RatioCnt=22;
// 			}
// 			RatioCnt+=1;
// 			if(RatioCnt>=23)RatioCnt=23;
// 			double tmp;
// 			tmp=(GenRatio()-ltRatio)*(RatioCnt/23.0)+ltRatio;
// 			tRatio=(int)tmp;
// 			if(!Ratiochk && GenRatio() != tGenRatio)
// 				RatioCnt=0;
// 		}
// 		else{
// 			
// 			Ratiochk=1;
// 			RatioCnt=0;
// 			ltRatio=tRatio=GenRatio();
// 		}
// 		//cnt+=1;
// 		//if(!qLen)Sprintf("%d cnt=%d",qLen,cnt);
// 			if((curRatio+tRatio) > 100){ //超出邊界,需要讀出下一筆
// 			    // Get next ms val 
// 				for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis++){
// 					if(curRatio !=100){
// 						DDATbl[axis].remainingval = DDATbl[axis].curval-DDATbl[axis].accval;
// 					}
// 					else{
// 						DDATbl[axis].remainingval  = 0 ;
// 					}
// 					if(DDATbl[axis].totalms > DDATbl[axis].curms){
// 						DDATbl[axis].curms++ ;
// 						int tt ;
// 						if(DDATbl[axis].curms <=DDATbl[axis].avgms){
// 							tt= DDATbl[axis].lmovval ;
// 							DDATbl[axis].lmovval=(long long)DDATbl[axis].movval*DDATbl[axis].curms/DDATbl[axis].avgms ;
// 							tt= DDATbl[axis].lmovval-tt ;
// 						}
// 						if(DDATbl[axis].idms !=0){ //有加減速
// 							if(DDATbl[axis].curms <= DDATbl[axis].idms){
// 								//加速部分
// 								int off=(DDATbl[axis].curms-1) ;
// 								tt=tt-MachineStatus.Autoidms[axis][DDATbl[axis].idms-1-off] ;
// 							}
// 							else if(DDATbl[axis].curms <=DDATbl[axis].avgms){
// 								//等速部分
// 							}
// 							else{
// 								//減速部分
// 								int off = DDATbl[axis].curms-DDATbl[axis].avgms-1 ;
// 								tt=MachineStatus.Autoidms[axis][DDATbl[axis].idms-1-off] ;
// 							}
// 						}
// 						if(isMINUS_SIGN(DDATbl[axis].dir)){
// 							tt=-tt ;
// 						}

// 						DDATbl[axis].curval=tt ;
// 						DDATbl[axis].accval=0 ;
// 					}
// 					else{
// 						DDATbl[axis].curval=0 ;
// 						DDATbl[axis].accval=0 ;
// 					}
// 				}
// 			}
// 			//計算目前的dda值
// 			if(((curRatio== 100) && (tRatio== 100)) || ((curRatio ==0) && (tRatio == 100))){
// 				for(uint8 axis =0 ; axis < MachineStatus.axis_no ; axis++){
// 					DDATbl[axis].dda = (uint16)DDATbl[axis].curval; 
// 				}
// 				curRatio=100 ;
// 			}
// 			else{
// 				int cur =tRatio+curRatio ;
// 				int last ;
// 				if(cur > 100){
// 					last=100 ;
// 					cur=curRatio=cur-100 ;
// 				}
// 				else{
// 					last=0 ;
// 					curRatio=cur ;
// 				}
// 				if(tRatio==0 && curRatio==100)//切測試時,ratio為零但curRatio=100
// 					cur=0;
// 				for(uint8 axis=0 ; axis < MachineStatus.axis_no ; axis++){
// 					int tacc = cur*DDATbl[axis].curval/100 ;
// 					int dda = tacc- DDATbl[axis].accval;
// 					DDATbl[axis].accval=tacc ;
// 					if(last == 100){
// 						dda= dda+DDATbl[axis].remainingval ; 
// 						DDATbl[axis].remainingval=0 ;
// 					}
// 					DDATbl[axis].dda = (uint16)dda ;
// 				}
// 			}
// 			//檢查翻線是否須補線
// 			if (MachineStatus.MotFunc[AXIS_A]	==	ROTW_FUNC){
// 				if(DDATbl[AXIS_A].dda){
// 					int dda=DDATbl[AXIS_A].dda ;
// 					BYTE tdir=OFFSET_Y_dir(PLUS_SIGN) ;
// 					if(isMINUS_SIGN(tdir)){
// 						dda=-dda ;
// 					}
// 					DDATbl[AXIS_Y].dda +=dda ;
// 				}
// 			}
// 			chk3701=0;
// 			//cnt++;
// 			for(uint8 axis=0 ; axis < MachineStatus.axis_no ; axis++){
// 				//修正馬達名稱修改後比對的dda極限
// 				if((DDATbl[MachineStatus.MotFunc[axis]].dda <= DDAMax[MachineStatus.MotFunc[axis]]) && (DDATbl[MachineStatus.MotFunc[axis]].dda >= -DDAMax[MachineStatus.MotFunc[axis]])){
// 					//DDATbl[axis].new_accval+=DDATbl[axis].dda;
// 					if(axis==AXIS_Y && DDATbl[AXIS_A].dda && MachineStatus.MotFunc[AXIS_A]	==	ROTW_FUNC){//new_accval在A軸補線時要扣掉 //沒有參考到A軸是翻線時(沒寫MachineStatus.MotFunc[AXIS_A]	==	ROTW_FUNC)
// 					
// 						if(MachineStatus.Type == TYPE_650_850)
// 								DDATbl[AXIS_Y].new_accval=DDATbl[AXIS_Y].new_accval+DDATbl[AXIS_A].dda;//650補線相反
// 							else 
// 								DDATbl[AXIS_Y].new_accval=DDATbl[AXIS_Y].new_accval-DDATbl[AXIS_A].dda;
// 					}
// 					
// 					//qLen =rDosMemw(pc_base+0xf00) ;
// 					//if(axis==AXIS_X && qLen<2)
// 					//		printf("qLen=%d \n",qLen);
// 					
// 					wDosMem(pc_base+4*axis , (uint16)DDATbl[axis].dda);
// 					//ReciveDDA((int)axis,(uint32_t)DDATbl[axis].dda);
// 					
// 					if(DDATbl[axis].totalms==DDATbl[axis].curms)
// 						DDATbl[axis].curval= 0;
// 					DDATbl[axis].new_accval+=DDATbl[axis].dda;
// 					//MachineStatus.NewVal[axis]+=DDATbl[axis].dda;
// 				}
// 				else{
// 					printf("Axis=%d dda=%d ddamax=%d",axis,DDATbl[MachineStatus.MotFunc[axis]].dda,DDAMax[MachineStatus.MotFunc[axis]]);
// 					//
// 					////超過極限
// 					//Sprintf("	Over Limit.......") ;
// 					//Sprintf("axis =%d dda=%d   max=%d MotFunc=%d",axis,DDATbl[MachineStatus.MotFunc[axis]].dda,DDAMax[MachineStatus.MotFunc[axis]],MachineStatus.MotFunc[axis]) ;
// 					//Sprintf("DDATbl[axis].totalms=%d DDATbl[axis].curms=%d DDATbl[axis].movval=%d",DDATbl[axis].totalms,DDATbl[axis].curms,DDATbl[axis].movval) ;
// 					//Sprintf("DDATbl[axis].idms=%d DDATbl[axis].lmovval=%d DDATbl[axis].accval=%d",DDATbl[axis].idms,DDATbl[axis].lmovval,DDATbl[axis].accval) ;
//           //          double a=1.0;
// 					//for(int i=0 ; i < 0x12345678; i++){ 
// 					//	a=a*1.2 ;
// 					//}
// 					SoftReset();
// 				}
// 			}
// 			//檢查命令是否已經執行完
// 			for(uint8 axis=0 ; axis < MachineStatus.axis_no ; axis++){
// 				if((DDATbl[axis].totalms !=0) && (DDATbl[axis].totalms == DDATbl[axis].curms) && (DDATbl[axis].curval== 0)){
// 					
// 					//cnt=0;
// 					//DISABLE() ;
// 					DDATbl[axis].totalms=0 ;
// 					cnt_Set3701-- ;
// 					//ENABLE() ;
// 				}
// 			}
// 		}
// 	}
// 	//else if(PORT_STOPRUN && cnt_Set3701 && slide_axis && MachineStatus.SlideLimit && MachineStatus.motor[slide_axis]){
// 	//	ChkSlide=false;
// 	//	DispSlideError();
// 	//	ResetDriverClear();
// 	//}
}	
void StopDDA (BYTE axis)
{
	//DISABLE() ;
// 	if(DDATbl[axis].totalms !=0){
// 		if(cnt_Set3701 !=0){
// 			cnt_Set3701-- ;
// 		}
// 		DDATbl[axis].totalms=0 ;
// 	}
// 	//ENABLE()
// 	while(rDosMemw(pc_base+0xf00+2*axis) !=0) ;
// 	mDelay(2) ;
}
void SetDriverClear()
{
	wDosMem(pc_base+DriverClear,(uint8)0xff) ;
}
//使馬達不再接收脈波,即進入停止狀況
void SetDriverClear(uint8 axis) 
{
	uint8 org= rDosMem(pc_base+DriverClear) ;
	wDosMem(pc_base+DriverClear,(uint8)(org | BITmask[7-axis])) ;
}
//終止所有在停止狀況的馬達
void ResetDriverClear()
{
	wDosMem(pc_base+DriverClear,(uint8)0x00) ;
}
void ResetDriverClear(uint8 axis)
{
	uint8 org= rDosMem(pc_base+DriverClear) ;
	wDosMem(pc_base+DriverClear,(uint8)(org & (~BITmask[7-axis]))) ;
}
void StopMotor_NewH(void)
{
// 	SetDriverClear() ;	
// 	for(int axis =0 ; axis < MachineStatus.axis_no ; axis++){
// 		StopDDA(axis) ;
// 	}
}
	void StopMotor(void)
{
		StopMotor_NewH() ;

}
bool chkOverLimit (uint8 axis,uint8 dir,uint8 man_hand,int &newval ,int &incmov, int &mov)
{
// 	int tnewval = newval ;
// 	
// 	if( MachineStatus.motor[axis] ){
// 		/*
// 		int dincval = (man_hand==0)? BcdToBin(3, MachineStatus.manval[axis]):BcdToBin(3, MachineStatus.handval[axis]);
// 		if( axis==AXIS_Y && MachineStatus.y_scale )  dincval *= 10;
// 		incmov= (isPLUS_SIGN(dir)?dincval:-(int32)dincval) ; 
// 		
// 		newval += incmov ;
// 		*/
// 		//int dincval = (man_hand==0)? MachineStatus.manval[axis]: MachineStatus.handval[axis];
// 		int dincval = (man_hand==0)? MachineStatus.manval[axis]: MachineStatus.handval[axis];
// 		if( axis==AXIS_Y && MachineStatus.y_scale )  dincval *= 10;
// 		incmov= (isPLUS_SIGN(dir)?dincval:-(int32)dincval) ;
// 		newval += incmov ;
// 		/*int32 min= BcdToBin(8,MachineStatus.Min[axis] ,MachineStatus.Min_sign[axis]) ;
// 		int32 max= BcdToBin(8,MachineStatus.Max[axis] ,MachineStatus.Max_sign[axis]) ;
// 		if((((max != 999999)&&(newval > max)) || ((min != -999999)&&(newval < min)))  && ((MachineStatus.SlideLimit && axis==slide_axis)|| axis!=slide_axis )){
// #if 0			
// 			DispMsgWin_q(-1, -1, WAR_WIN, 	"超 過 軟 體 極 限!",
// 											" Over software Limit");
// 			WAIT_NEW_KEY();
// 			ClrMsgWin_q();								
// #endif			
// 			return(true) ;
// 		}
// 	 	else{
// 		*/
// 			mov=sdDifGrid(axis,newval,tnewval) ;
// 			//mov=newval-tnewval ;
// 			//mov=incmov;
// 	
// 	//if(SManMov.dir==MINUS_SIGN)
// 	//	mov=-mov;
// 	 		return(false) ;
// 	 	//}
// 	}
// 	return(true);
}
int absMov (int &mov)
{
	if(mov >=0){
		return(0) ;
	}
	else{
		mov = -mov ;
		return(1) ;
	}
}
void RunManMov ()
{	
// 		BYTE axis = SManMov.axis ;
// 	// 產生目前手動量及下一次手動量	
// 	
// 	//int tcurloc= (isPLUS_SIGN(SManMov.dir)?MachineStatus.axis_val[axis]:-MachineStatus.axis_val[axis]) ; 
// 	int tcurloc= MachineStatus.axis_val[axis] ; 
// 	//int tcurloc = BcdToBin(8,MachineStatus.axis_val[axis] ,MachineStatus.sign[axis]);
// 	//printf("%d %d %d\n",SManMov.dir,MachineStatus.axis_val[axis],tcurloc);
// 	int CurMov ;
// 	int NextMov ;
// 	int incmov ;
// 	bool ChkManMovSlide=true;
// 	chk_unconnector= true ;
// 	enable_chk_unconnector[axis]= true ;
// 	for(int axis=0 ; axis <MachineStatus.axis_no ; axis++){
// 			ChkOverFlow[axis]=true;
// 	}
// 	if(PORT_STOPRUN && slide_axis && MachineStatus.SlideLimit && MachineStatus.motor[slide_axis]){
// 		ChkManMovSlide=false;
// 	}
// 	if(!chkOverLimit(axis ,SManMov.dir,SManMov.man_hand,tcurloc , incmov , CurMov) && ChkManMovSlide){
// 		MachineStatus.is_home[axis]=0 ;
// 		uint16 sign =absMov(CurMov);
// 		if(Manidms !=0){
// 			int cidms = find_idms(axis,CurMov,MANMS) ;
// 			for(int i=0 ; i < (Manidms-cidms) ; i++){
// 				TManMov[0][i]=0 ;
// 				TManMov[0][MANMS-1-i]=0 ;
// 			}
// 			GenTmov(axis, &TManMov[0][Manidms-cidms],sign,CurMov,MANMS-2*(Manidms-cidms),cidms) ;
// 		}
// 		else{
// 			GenTmov(axis, &TManMov[0][0],sign,CurMov,MANMS,0) ;			//產生均速表
// 		}
// 		//計算下一次手動量
// 		if(!chkOverLimit(axis ,SManMov.dir,SManMov.man_hand,tcurloc ,incmov , NextMov)){
// 			uint16 sign=absMov(NextMov) ;
// 			if(Manidms !=0){
// 				int cidms = find_idms(axis,NextMov,MANMS) ;
// 				GenTmov(axis,TManMov[1],sign,NextMov,MANMS-Manidms,0) ;// 產生均速表
// 			}
// 			else{
// 				GenTmov(axis,TManMov[1],sign,NextMov,MANMS/2,0) ;// 產生均速表
// 				
// 			}
// 			idx_Table=1 ;
// 		}
// 		else{
// 			idx_Table=2 ; //代表沒有下一手動量
// 		}
// 		idx_TManMov=0 ;
// 		DDAState=1 ;
// 	}
}
void DispCurLine(){					
	WORD Line_tmp=CurLine;
	static WORD lLine;
	if(lLine!=CurLine){
		TxBuf[0]=Cmd_Line ;
		for(int i =0;i<2;i++){
			TxBuf[2-i]=Line_tmp&0xff;
			Line_tmp>>=8;
		}
		sendCmd(Cmd_Line,TxBuf,3);
		
		lLine=CurLine;
	}
}
void DispCurAxis_q(short force){
	
// 	DWORD  tmp;
// 	uint8 textBuf[5];
// 	textBuf[0]=poscmd ;	
// 	//textBuf[1]=axis;	
// 	
// 	for(WORD i=0; i < MachineStatus.axis_no; i++ ){
// 		if( MachineStatus.motor[i] ){
// 			BYTE axis=i;
// 			textBuf[1]=axis	;	
// 			if(MachineStatus.p3701[i]){
// 				if( force || ((MachineStatus.axis_val[i]!=MachineStatus.laxis_val[i]) || (MachineStatus.sign[i]!=MachineStatus.lsign[i])) ){
// 					
// 						//if(axis==AXIS_X && MachineStatus.axis_val[axis]>=4000 && MachineStatus.Unit[axis] == UNIT_GRID)
// 						// MachineStatus.axis_val[axis]-=4000;
// 					//MachineStatus.NewVal[axis]+= MachineStatus.axis_val[axis] ;
// 					
// 					//if(MachineStatus.NewVal[axis]>MachineStatus.motor_grads[axis])//�W�L�|�d����
// 					//	MachineStatus.NewVal[axis]-=MachineStatus.motor_grads[axis];
// 					MachineStatus.lsign[i] = MachineStatus.sign[i];
// 					if(axis==AXIS_X && MachineStatus.axis_val[i]>=4000 && !flag_RRealAxis)
// 						MachineStatus.axis_val[i]%=dBMOTORUNIT_X();
// 					
// 					MachineStatus.laxis_val[i] = MachineStatus.axis_val[i];
// 					
// 					SDWORD tt= MachineStatus.laxis_val[axis]=MachineStatus.axis_val[axis] ;
// 					//DWORD sign = MachineStatus.sign[AXIS_X]  ;

// 					//Grid2Unit(axis,tt) ;
// 						
// 					//MachineStatus.NewValtmp[axis]=tt;
// 						int tmp=tt;
// 							if(MachineStatus.sign[i] && tmp>0)
// 								tmp=-tmp;
// 							else if(!MachineStatus.sign[i]&& tmp<0)
// 								tmp=-tmp;
// 						
// 						for(int i =0;i<3;i++){
// 							textBuf[4-i]=tmp&0xff;
// 							tmp>>=8;
// 						}
// 						//if(axis==AXIS_Y||(axis==AXIS_X &&(MachineStatus.axis_val[axis]>4000||MachineStatus.axis_val[axis]<0)))
// 						//	printf("%x %x %x %x %x %x__\n",MachineStatus.axis_val[axis],textBuf[0],textBuf[1],textBuf[2],textBuf[3],textBuf[4]) ;
// 						Tx(textBuf,5) ;
// 					//}
// 				}
// 			}
// 		}
// 	}
}	
void DispRPM(int rpm){	
	TxBuf[0]=Cmd_RPM ;	
	for(int i =0;i<3;i++){
		TxBuf[3-i]=rpm&0xff;
		rpm>>=8;
	}
	//printf("RPM=%x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
	Tx(TxBuf,4) ;
}
void CloseRPM(){	
	TxBuf[0]=Cmd_Close_RPM ;	
	TxBuf[1]=0xf4 ;	
	//printf("RPM=%x %x\n",TxBuf[0],TxBuf[1]);
	Tx(TxBuf,2) ;
}
void ClrTouchPos (short	mode, WORD flag)
{

// 	if(	flag&0x01 ){
// 		//if(	flag&0x01 )
// 		//	DispStrLine_q(tx+2,	ly+2, TOUCH_TITLE_FCOLOR, TOUCH_TITLE_BCOLOR, TouchTitle[idx_language][0]);
// 		//else
// 		//	DispStrLine_q(tx+2,	ly+2, TOUCH_TITLE_FCOLOR, TOUCH_TITLE_BCOLOR, TouchTitle[idx_language][2]);

// 		INI_DISP_BUF();
// 		if (MachineStatus.touch_before_err){
// 			SendTouch(Cmd_Touch1,2,MachineStatus.axis_val[AXIS_Y]);
// 		//		MachineStatus.touch_before_err = false;
// 		//			Fill_pDispBuf(	"送線前",
// 		//		  					"Before" ,
// 		//							"Before");
// 		}
// 		else{
// 			SendTouch(Cmd_Touch1,3,MachineStatus.axis_val[AXIS_Y]);
// 			//Fill_pDispBuf("       ");
// 		}
// 		//FILL_DISP_BUF(0);
// 		//if(	!mode )	 DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR,	WIN_TEXT_BCOLOR, DispBuf);
// 		//else		 DispStrLine_q(lx+2, ly+2, WIN_TEXT_FCOLOR,	RED_USR, DispBuf);
// 	}

// 	//if(	flag&0x0a ){
// 	else{
// 		//if(	flag&0x02 )
// 		//	DispStrLine_q(tx+2,	ly+2, TOUCH_TITLE_FCOLOR, TOUCH_TITLE_BCOLOR, TouchTitle[idx_language][1]);
// 		//else
// 		//	DispStrLine_q(tx+2,	ly+2, TOUCH_TITLE_FCOLOR, TOUCH_TITLE_BCOLOR, TouchTitle[idx_language][3]);

// 		//INI_DISP_BUF();
// 		if (MachineStatus.touch_before_err){
// 			SendTouch(Cmd_Touch2,2,MachineStatus.axis_val[AXIS_Y]);
// 		//	MachineStatus.touch_before_err = false;
// 		//		Fill_pDispBuf(	"送線前",
// 		//	  					    "Before" ,
// 		//						    "Before");
// 		}
// 		else{
// 			SendTouch(Cmd_Touch2,3,MachineStatus.axis_val[AXIS_Y]);
// 			//Fill_pDispBuf("       ");
// 		}
// 		//FILL_DISP_BUF(0);
// 		//if(	!mode )	DispStrLine_q(lx+2,	ly+2, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR,	DispBuf);
// 		//else		DispStrLine_q(lx+2,	ly+2, WIN_TEXT_FCOLOR, RED_USR,	DispBuf);
// 	}
}
void DispTouchPos()
{
// 	SDWORD tt ;
// 		if( MachineStatus.dcur_th[0] ){
// 			/*
// 			tt= MachineStatus.axis_val[AXIS_Y] ;
// 			//tt= MachineStatus.dcur_th[0] ;
// 			TxBuf[0]=Cmd_Touch1 ;	
// 			for(int i =0;i<3;i++){
// 				TxBuf[3-i]=tt&0xff;
// 				tt>>=8;
// 			}
// 			printf("%x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
// 			Tx(TxBuf,4) ;
// 			//printf("0__%d\n",MachineStatus.dcur_th[0]);
// 			printf("0__%d\n",MachineStatus.axis_val[AXIS_Y]);
// 			*/
// 			SendTouch(Cmd_Touch1,1,MachineStatus.axis_val[AXIS_Y]);
// 			MachineStatus.dcur_th[0] = 0;
// 		}
// 		else if( MachineStatus.dcur_th[2] ){
// 			/*
// 			tt= MachineStatus.axis_val[AXIS_Y] ;
// 			
// 			TxBuf[0]=Cmd_Touch1 ;	
// 			for(int i =0;i<3;i++){
// 				TxBuf[3-i]=tt&0xff;
// 				tt>>=8;
// 			}
// 			printf("%x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
// 			Tx(TxBuf,4) ;
// 			printf("2__%d\n",MachineStatus.axis_val[AXIS_Y]);
// 			*/
// 			SendTouch(Cmd_Touch1,1,MachineStatus.axis_val[AXIS_Y]);
// 			MachineStatus.dcur_th[2] = 0;
// 		}
// 		
// 		
// 		if( MachineStatus.dcur_th[1] ){
// 			/*
// 			tt= MachineStatus.axis_val[AXIS_Y] ;
// 			
// 			TxBuf[0]=Cmd_Touch2 ;	
// 			for(int i =0;i<3;i++){
// 				TxBuf[3-i]=tt&0xff;
// 				tt>>=8;
// 			}
// 			printf("%x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
// 			Tx(TxBuf,4) ;
// 			printf("1__%d\n",MachineStatus.axis_val[AXIS_Y]);
// 			*/
// 			SendTouch(Cmd_Touch2,1,MachineStatus.axis_val[AXIS_Y]);
// 			
// 			MachineStatus.dcur_th[1] = 0;
// 		}
// 		else if( MachineStatus.dcur_th[3] ){
// 			/*
// 			tt= MachineStatus.axis_val[AXIS_Y] ;
// 			
// 			TxBuf[0]=Cmd_Touch2 ;	
// 			for(int i =0;i<3;i++){
// 				TxBuf[3-i]=tt&0xff;
// 				tt>>=8;
// 			}
// 			printf("%x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
// 			Tx(TxBuf,4) ;
// 			printf("3__%d\n",MachineStatus.axis_val[AXIS_Y]);
// 			*/
// 			
// 			SendTouch(Cmd_Touch2,1,MachineStatus.axis_val[AXIS_Y]);
// 			
// 			MachineStatus.dcur_th[3] = 0;
// 		}
}
// void ClrTouch()
// {
// 	int  tt= 1336 ;
// 	TxBuf[0]=Cmd_Touch1 ;	
// 	for(int i =0;i<3;i++){
// 		TxBuf[3-i]=tt&0xff;
// 		tt>>=8;
// 	}
// 	printf("%x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
// 	Tx(TxBuf,4) ;
// }
void SendTouch(uint8 Cmd,int mode,int pos)
{
	TxBuf[0]=Cmd ;	
	TxBuf[1]=mode;
	for(int i =0;i<3;i++){
		TxBuf[4-i]=pos&0xff;
		pos>>=8;
	}
	printf("cmd=%x mode=%x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3],TxBuf[4]);
	Tx(TxBuf,5) ;
}
void addcurmiss_cmd()
{
// 	MachineStatus.cur_miss++;
// 	int tmp=MachineStatus.cur_miss;
// 	
// 	TxBuf[0]=curmiss ;	
// 	//TxBuf[1]=Cmd_Curmiss ;	
// 	for(int i =0;i<2;i++){
// 		TxBuf[2-i]=tmp&0xff;
// 		tmp>>=8;
// 	}
// 	printf("%d %x %x %x\n",MachineStatus.cur_miss,TxBuf[0],TxBuf[1],TxBuf[2]);
// 	Tx(TxBuf,3) ;
// 	printf("%d %d\n",MachineStatus.cur_miss);
}

void complete_spring_cmd()
{
// 	MachineStatus.cur_quan++;
// 	int tmp=MachineStatus.cur_quan;
// 	
// 	TxBuf[0]=curquan ;	
// 	//TxBuf2[1]=Cmd_Curquan ;	
// 	for(int i =0;i<3;i++){
// 		TxBuf[3-i]=tmp&0xff;
// 		tmp>>=8;
// 	}
// 	//printf("%d %x %x %x %x\n",MachineStatus.cur_quan,TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
// 	Tx(TxBuf,4) ;
// 	if(MachineStatus.cur_quan>=MachineStatus.set_quan)MachineStatus.stop_machine = 1;
// 	//printf("%d %d\n",MachineStatus.cur_quan,MachineStatus.set_quan);//顯示產量
// 	if( CHECK_QUAN_OK() || CHECK_MISS_OK() || rdflagStopRun())  MachineStatus.stop_machine = 1;
// 	/*
// 	uint8 sign=PLUS_SIGN ;
// 	DWBcdAddBin(&sign, &MachineStatus.cur_quan, 1);
// 	svprodnoCMOS(&MachineStatus.cur_quan) ;
// 	if( CHECK_QUAN_OK() || CHECK_MISS_OK() || rdflagStopRun())  MachineStatus.stop_machine = 1;
// 	DispQuanNo_q(0);
// 	if(stBATCHn.flag){
// 		stBATCHn.Cno++ ;
// 		if(stBATCHn.Cno >= stBATCHn.no){
// 			stBATCHn.Cno=0 ;
// 			stBATCHn.airON =1 ;
// 			SetAir(stBATCHn.airno,1) ;
// 			stBATCHn.timeout= sTimerSet(1) ;
// 		}
// 	}
// 	*/
// 	DispTestMsg_q();
}
void CalNextManMov ()
{
// 	BYTE axis=SManMov.axis ;
// 	int CurMov ,incmov,NextMov ;
// 	//int tcurloc = BcdToBin(8,MachineStatus.axis_val[axis] ,MachineStatus.sign[axis]);
// 	int tcurloc= MachineStatus.axis_val[axis] ; 
// 	chkOverLimit(axis ,SManMov.dir,SManMov.man_hand,tcurloc ,incmov , CurMov) ;
// 	//SDWORD tt=CurMov;
// 	//if(axis==AXIS_Y)tt=incmov;
// 	//if(tt<0)
// 	//	tt=-tt;
// 	//if(SManMov.dir==0)
// 	//	MachineStatus.axis_grid[axis]+=tt;
// 	//else
// 	//	MachineStatus.axis_grid[axis]-=tt;
// 	//if(MachineStatus.axis_grid[axis]>=MachineStatus.motor_grads[axis] && axis==AXIS_X)
// 	//	MachineStatus.axis_grid[axis]-=MachineStatus.motor_grads[axis];
// 	//int32 tmp=MachineStatus.axis_grid[axis];
// 	//
// 	//if(axis!=AXIS_Y)Grid2Unit(axis,tmp) ;
// 	
// 	MachineStatus.axis_val[axis]=tcurloc;
// 	if(axis==AXIS_X && MachineStatus.axis_val[axis]>=4000)
// 		MachineStatus.axis_val[axis]-=4000;
// 	
// 	if(MachineStatus.axis_val[axis]>=0)
// 		MachineStatus.sign[axis]=PLUS_SIGN;
// 	else
// 		MachineStatus.sign[axis]=MINUS_SIGN;
// 	//印出目前的值
// 	ChkAxisVal(axis, &(MachineStatus.sign[axis]), &(MachineStatus.axis_val[axis]));
// 	
// 	if(!flag_RRealAxis)
// 		DispCurAxis_q(0);
// 	
// 	//計算下一次手動量
// 	chkOverLimit(axis ,SManMov.dir,SManMov.man_hand,tcurloc ,incmov , CurMov) ;
// 	//計算下下一次手動量
// 	if(	!chkOverLimit(axis ,SManMov.dir,SManMov.man_hand,tcurloc ,incmov , NextMov)){
// 		int sign=absMov(NextMov) ;
// 		idx_Table++ ;
// 		if(idx_Table ==2){
// 			idx_Table=0 ;
// 		}
// 		if(Manidms !=0){
// 			int cidms = find_idms(axis,NextMov,MANMS) ;
// 			GenTmov(axis, TManMov[idx_Table],sign,NextMov,MANMS-Manidms,0) ;   //產生均速表
// 		}
// 		else{
// 			GenTmov(axis, TManMov[idx_Table],sign,NextMov,MANMS/2,0) ;   //產生均速表
// 		}
// 	}
// 	else{
// 		idx_Table=2 ; //代表沒有下一手動量
// 	}	
}
// sign=0===>plus_sign    =1 minus_sign 
void GenTmov (BYTE axis , short Tmov[] , uint8 sign , int mov , int ms , int cidms )
{
	
// 	int lloc=0 ;
// 	int tms = ms -cidms ;
// 	//產生加減速部分
// 	for(int i=0 ; i < cidms ; i++){
// 		int  cloc= mov*(i+1)/tms;
// 		Tmov[i]=(sign == 0)?MachineStatus.Tidms[axis][i]: -MachineStatus.Tidms[axis][i];
// 		int t= cloc-lloc ;
// 		Tmov[tms+i]=(sign ==0)?(t-MachineStatus.Tidms[axis][i]) : -(t-MachineStatus.Tidms[axis][i]);
// 		lloc=cloc ;			
// 	}
// 	//產生等速部分
// 	for(int i=cidms ; i < tms ; i++){
// 		int  cloc= mov*(i+1)/tms;
// 		Tmov[i]=(sign ==0)?(cloc-lloc):-(cloc-lloc);
// 		lloc=cloc ;			
// 	}
}
void wr_dda(uint8 axis,int16 dda)
{
	wDosMem(pc_base+4*axis,(uint16)dda) ;
	//ReciveDDA((int)axis,(uint32_t)dda);
	/*if(CHK_ROTW(axis)){
		BYTE tdir=OFFSET_Y_dir(PLUS_SIGN) ;
		if(isMINUS_SIGN(tdir)){
			dda=-dda ;
		}
		wDosMem(pc_base+4*AXIS_Y,(uint16)dda) ;
	}
	*/
}	

void ManMov_DDA()
{	
//   int qLen ;
// 	BYTE axis = SManMov.axis ;
// 	switch(DDAState){
// 		
// 		case 1:    
// 			//檢查Queue的長度
// 			qLen =rDosMemw(pc_base+0xf00+2*axis) ;
// 			for(int i=0 ; i < 2-qLen ;i++){
// 				int dda=TManMov[0][idx_TManMov++] ;
// 				wr_dda(axis,dda) ;
// 				if(idx_TManMov== (MANMS-Manidms)){
// 					//檢查是否連動
// 					printf("%d %d\n",KeyBufWIdx ,KeyBufRIdx);
// 					if(KeyBufWIdx !=KeyBufRIdx){
// 						//檢查最後一個按鍵是否和目前手動按鍵一樣
// 						uint16 tKeyBufWIdx ;
// 						if(KeyBufWIdx !=0){
// 							tKeyBufWIdx=KeyBufWIdx-1 ;
// 						}
// 						else{
// 							tKeyBufWIdx=MAX_KEY_BUF-1 ;
// 						}
// 						if((KeyBuf[tKeyBufWIdx] == prokeycode) && (idx_Table !=2)){ //最後一個按鍵是否和目前手動按鍵一樣且idx_Table不為2
// 							KeyBufRIdx=KeyBufWIdx ; //清除keybuf
// 							idx_TManMov=0 ;
// 							DDA_idx_Table=idx_Table ;						
// 							DDAState=2 ;
// 						}
// 						else{
// 							DDAState=3 ;
// 							idx_TManMov=MANMS-Manidms ;
// 						}
// 					}
// 					else{
// 						DDAState=3 ;
// 						idx_TManMov=MANMS-Manidms ;
// 					}
// 					if((Manidms==0)&& (DDAState==3)){
// 						DDAState=0 ;

// 					}
// 					CalNextManMov() ;
// 					break ;
// 				}			
// 			}
// 			break ;
// 		case 2: //連動
// 			//printf("%d\n",DDAState);
// 			//檢查Queue的長度
// 			qLen =rDosMemw(pc_base+0xf00+2*axis) ;
// 			for(int i=0 ; i < 2-qLen ;i++){
// 				int dda= TManMov[DDA_idx_Table][idx_TManMov++] ;
// 				wr_dda(axis,dda) ;
// 				int len =(Manidms !=0)?	(MANMS-Manidms):(MANMS/2) ;	
// 				
// 				if(idx_TManMov== len){
// 					//檢查是否連動

// 					printf("%d %d\n",KeyBufWIdx ,KeyBufRIdx);
// 					if(KeyBufWIdx !=KeyBufRIdx){
// 						
// 						//檢查最後一個按鍵是否和目前手動按鍵一樣
// 						uint16 tKeyBufWIdx ;
// 						if(KeyBufWIdx !=0){
// 							tKeyBufWIdx=KeyBufWIdx-1 ;
// 						}
// 						else{
// 							tKeyBufWIdx=MAX_KEY_BUF-1 ;
// 						}
// 						if((KeyBuf[tKeyBufWIdx] == prokeycode) && (idx_Table !=2)){ //最後一個按鍵是否和目前手動按鍵一樣且idx_Table不為2

// 							KeyBufRIdx=KeyBufWIdx ; //清除keybuf
// 							idx_TManMov=0 ;
// 							DDA_idx_Table=idx_Table ;						
// 							DDAState=2 ;

// 						}
// 						else{
// 							DDAState=3 ;
// 							idx_TManMov=MANMS-Manidms ;
// 						}
// 					}
// 					else{
// 						DDAState=3 ;
// 						idx_TManMov=MANMS-Manidms ;
// 					}
// 					if((Manidms==0)&& (DDAState==3)){
// 						DDAState=0 ;

// 					}
// 					CalNextManMov() ;
// 				}
// 			}
// 			break ;
// 		case 3 :  //執行減速,結束目前手動
// 		    //檢查Queue的長度
// 			qLen =rDosMemw(pc_base+0xf00+2*axis) ;
// 			for(int i=0 ; i < 2-qLen ;i++){
// 				wr_dda(axis,TManMov[0][idx_TManMov++]) ;
// 				if(idx_TManMov== (MANMS)){
// 					DDAState=0 ;
// 					break ;
// 				}
// 			}
// 			break;
// 		default:
// 			break ;
// 	}
}
void update_run_DDA()
{
// // 	static struct TIMER lTimerTicks ={0} ;
// // 	if(lTimerTicks.timer != TimerTicks.timer){
// // 		lTimerTicks= TimerTicks ;
// // 		run_DDA() ;
// // 		ReadAxes() ;
// // 		ManMov_DDA() ;
// // 		Step_operation();
// // 		//KeyIsr() ;
// // 	}
}
//找到加減速時間
int find_idms (BYTE axis, int mov , int ms )
{
// 	double V= mov *1.0/ms ;
// 	int cidms=0 ;
// 	for(int i=0 ; i < Manidms ; i++){
// 		if(V < MachineStatus.Tidms[axis][i]){
// 			cidms= i ;
// 			break ;
// 		}
// 	}
// 	if(cidms != 0){
// 		for(;;){
// 			V=mov *1.0/(ms-cidms) ;
// 			if(V > MachineStatus.Tidms[axis][cidms]){
// 				cidms ++ ;
// 			}
// 			else{
// 				break ;
// 			}
// 		}
// 	}
// 	return(cidms) ;
}

bool ChkDriverClear(uint8 axis)
{
	uint8 tt= rDosMem(pc_base+DriverClear) ;
	return(tt & BITmask[7-axis]) ;
}
// static unsigned int cntDDA=0 ;
void ReadAxes()
{
// 	static int cnt=0 ;
// 	for(uint8 axis=0 ; axis < MachineStatus.axis_no ; axis++){
// 		uint16 tt= rDosMemw(pc_base+2+axis*4) ;
// 		if(lFeedbackCnt16[axis] != tt){
// 			int dif= (int16)(tt-lFeedbackCnt16[axis]) ;
// 			lFeedbackCnt16[axis]=tt ;
// 			FeedbackCnt[axis] +=dif ;
// 			if(axis == AXIS_X){
// 				if(FeedbackCnt[AXIS_X] >= ((int32) MachineStatus.bmotor_grads[AXIS_X])){
// 					FeedbackCnt[AXIS_X]-=MachineStatus.bmotor_grads[AXIS_X] ;
// 				}
// 				else if(FeedbackCnt[AXIS_X] <0){
// 					FeedbackCnt[AXIS_X]+=MachineStatus.bmotor_grads[AXIS_X];
// 				}
// 			}
// 		}
// 	}
}
void ReadAxes(uint8 axis)
{
	uint16 tt= rDosMemw(pc_base+2+axis*4) ;
	if(lFeedbackCnt16[axis] != tt){
		int dif= (int16)(tt-lFeedbackCnt16[axis]) ;
		/*if((axis == AXIS_A) && (abs(dif) > 160)){
			Sprintf("AAA  tt =%x lFeedbackCnt16=%x  dif=%d",tt ,lFeedbackCnt16[axis],dif) ;
		}
		else if((axis == AXIS_X)&& (abs(dif) > 200)){
			Sprintf("XXX  tt =%x lFeedbackCnt16=%x  dif=%d",tt ,lFeedbackCnt16[axis],dif) ;
		}
		*/
		lFeedbackCnt16[axis]=tt ;
		FeedbackCnt[axis] +=dif ;
	}
}
