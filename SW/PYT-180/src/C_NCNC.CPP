#include "header.h"
//#include  <process.h>
//#include <ctype.h>
bool in_proc_queue = false ;
bool ftime_in_proc_queue  ;
FILE *fp_dump_proc_queue ;

#define PRN_RETRY  1000
#define INL 							0xc08
#define INE							0xc0e
#define INM 							0xc0a


#define	PRN_WR_DELAY			3000
   

bool prodno_enable=false;
long long lprodnoTimer;
BYTE GetKey	(void)
{
	BYTE code;
	static struct TIMER lTimerTicks;
	while( KeyBufRIdx == KeyBufWIdx	){CHECK_RESET(false); 
		}
	code = KeyBuf[KeyBufRIdx];
	if(	KeyBufRIdx+1 >=	MAX_KEY_BUF	)	KeyBufRIdx = 0;
	else								KeyBufRIdx++;


	
	return(	code );
}
void TouchActive (short	no)
{	
// 	if(	MachineStatus.chk_th[no] ){
// 		//�T�{�����_��SET_TOUCH�Ҳ���
// 		if(	!MachineStatus.pass_th[no] ){
// 			//SET_TOUCH�Ĥ@���o��
// 			MachineStatus.pass_th[no] =	1; // �ϱo�H�U�{���u����@��
// #ifdef SPD_TOUCH			
// 			if (MachineStatus.op_mode == RUN_MODE){
// 				nSet8254(MachineStatus.cnt8254);
// 			}
// 			else if (MachineStatus.op_mode == TEST_MODE){
// 				TouchSPD.change = false;
// 				TouchSPD.spd    = 0;
// 				TouchSPD.speed  = 0;
// 				MachineStatus.set8254 = 1;
// 				flag_TouchSPDChange = true;
// 			}
// #endif			
// 			if(	no < 2 ){
// 				// touch1��touch2----TH1_STP/TH1_CHK ,TH2_STP/TH2_CHK
// 				// TH1_CHK,TH2_CHK������e�u,�u�Nair���^
// 				if(	MachineStatus.chk_th[no]==TH1_STP || MachineStatus.chk_th[no]==TH2_STP ){
// 					if(MachineStatus.chk_th_stop_axis[no]==	AXIS_Y){
// 						uint8 PMfun_000[3]={0,0,0};

// 						//(���w���U�b)-------------------
// 						//if(T_Stop_idx){
// 						//	T_Stop_HaveTouch_Flag=true;
// 						//	T_Stop_Axis=0;
// 						//	for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
// 						//		if(T_Stop_Flag[T_Stop_MdyVAL_idx][axis]){
// 						//			StopMotor(axis);				//���P�b�R�O
// 						//			
// 						//			//�g�i�����b									
// 						//			T_Stop_Axis ^= 0x01<<(axis);
// 						//		}								
// 						//	}
// 						//}						
// 						if(	MachineStatus.wire_on )	WireOnOff(0);
// 					}
// 				}
// 				else{
// 				}
// 				MachineStatus.air_buf &= (no==0?((~MASK_BIT6)):((~MASK_BIT7)));
// 				wDosMem(pc_base+OUTL, MachineStatus.air_buf);
// 			}
// 			else{
// 				if(MachineStatus.chk_th_stop_axis[no]==	AXIS_Y){	
// 					
// 					//(���w���U�b)-------------------
// 					//if(T_Stop_idx){
// 					//	T_Stop_HaveTouch_Flag=true;
// 					//	T_Stop_Axis=0;
// 					//	for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
// 					//		if(T_Stop_Flag[T_Stop_MdyVAL_idx][axis]){					
// 					//			StopMotor(axis);						//���P�b�R�O
// 					//				//�g�i�����b									
// 					//				T_Stop_Axis ^= 0x01<<(axis);
// 					//		}
// 					//	}
// 					//}
// 					
// 				if(	MachineStatus.wire_on )	WireOnOff(0);
// 				}
// 				else if(CHK_SPIN(AXIS_Z) && MachineStatus.chk_th_stop_axis[no] == AXIS_Z){
// 					StopMotor(AXIS_Z) ;
// 					flag_ZRT_ZABCD[0]=true	;
// 				}
// 				else if(CHK_SPIN(AXIS_A) && MachineStatus.chk_th_stop_axis[no] == AXIS_A){
// 					StopMotor(AXIS_A) ;					
// 					flag_ZRT_ZABCD[1]=true	;
// 				}
// 				else if(CHK_SPIN(AXIS_B) && MachineStatus.chk_th_stop_axis[no]== AXIS_B){
// 					StopMotor(AXIS_B) ;
// 					flag_ZRT_ZABCD[2]=true	;
// 				}
// 				else if(CHK_SPIN(AXIS_C) && MachineStatus.chk_th_stop_axis[no]== AXIS_C){
// 					StopMotor(AXIS_C) ;				
// 					flag_ZRT_ZABCD[3]=true	;
// 				}
// 				MachineStatus.air_buf &= (no==2?((~MASK_BIT4)):((~MASK_BIT5)));
// 				wDosMem(pc_base+OUTL , MachineStatus.air_buf);
// 			}
// 			
// 			if(NewH){
// 				//���ܳt��(�p�G��X�b��Y�b)�ΰ���Y�bDDA(�u��Y�b)
// 				if((cnt_Set3701 ==1) && (DDATbl[AXIS_Y].totalms !=0)){
// 					//����Y�bDDA(�u��Y�b)
// 					cnt_Set3701=0 ;
// 					DDATbl[AXIS_Y].totalms =0 ;
// 				}		
// 			}
// 			
// #if SHOW_TOUCH_Y 			
// 			//MachineStatus.dcur_th[no] = BcdToBin(8,MachineStatus.axis_val[AXIS_Y]) ;    

// 			dsave_cur_th[no] = wRead2016(AXIS_X);
// 			
// 			if (MachineStatus.dcur_th[no]==0){
// 				if(!MachineStatus.dst_pos[AXIS_Y])MachineStatus.axis_lval[AXIS_Y]=0;
// 				MachineStatus.dcur_th[no] = ((SDWORD)MachineStatus.dst_pos[AXIS_Y])-MachineStatus.axis_lval[AXIS_Y] ;//���w��ܭץ�
// 				DispTouchPos();
// 				//printf("no=%d__%lld\n",no,MachineStatus.axis_val[AXIS_Y]);
// 			}
// #else	
// 			dsave_cur_th[no] = MachineStatus.dcur_th[no] = wRead2016(AXIS_X);		
// #endif			
// 			MachineStatus.cur_thy[no] = MachineStatus.axis_val[AXIS_Y] ;
// 		}
// 	}
// 	MachineStatus.th_test =	no+1;
}
void TouchIsr (void)
{
	
	
#if ISR_FILL_PROC_QUEUE
	in_TouchIsr=true ;
#endif
	uint8 status= rDosMem(pc_base+0xc00+0x10);
	if((status &	MASK_BIT0) != 0	){
		DISABLE_INPORT_INT(MASK_BIT0) ;
		TouchActive(0);
	}
	else if((status & MASK_BIT1) !=	0 ){
		DISABLE_INPORT_INT(MASK_BIT1) ;
		TouchActive(1);
	}
	else if((status & MASK_BIT2) !=	0 ){
		DISABLE_INPORT_INT(MASK_BIT2) ;
		TouchActive(2);
	}
	else if((status & MASK_BIT3) !=	0 ){
		DISABLE_INPORT_INT(MASK_BIT3) ;
		TouchActive(3);
	}

#if ISR_FILL_PROC_QUEUE
	in_TouchIsr=false ;
#endif
}
void HandIsr(void)
{
// 	uint8 mag,haxis,qlen;
// 	mag=rDosMem(pc_base+0xc24) ; 
// 	haxis=rDosMem(pc_base+0xc22) ; 
// 	qlen=rDosMemw(pc_base+0x020) ;  
// 	static uint8 sel_axis,sel_meg	;
// 	static uint8 lmag,lhaxis,lhaxis_chk,lqlen;
// 	static struct TIMER  lTimerTicks;
// 	static uint8 state=0;			
// 	static uint8 flag_mag=0,flag_haxis=0;
// 	int cnt=0 ;
// 		if(state==0){	
// 			if((lmag!=mag)){
// 				MachineStatus.hand_plugin=1;
// 				lmag=mag;
// 				state=1;
// 				flag_mag=1;
// 			}
// 			else {
// 				flag_mag=0;
// 			}
// 			if(lhaxis!=haxis){
// 				lhaxis=haxis;
// 				state=1;
// 				flag_haxis=1;
// 			}
// 			else {
// 				flag_haxis=0;
// 			}
// 		}
// 	switch(state){
// 	case 1:
// 			if(flag_mag){
// 				switch(mag){
// 					case 6:
// 						KeyHandX1();
// 						sel_meg=0;
// 						break;
// 					case 5:
// 						KeyHandX10();
// 						sel_meg=1;
// 						break;
// 					case 3:
// 						KeyHandX100();
// 						sel_meg=2;
// 						break;	
// 					default:
// 						break;
// 				}
// 			}
// 			if(flag_haxis){
// 				switch(lhaxis){
// 					case 255:
// 						KeyHandOff();
// 						sel_axis=0;
// 						break;
// 					case 253:
// 						KeyHandX();
// 						sel_axis=1;
// 						break;
// 					case 251:
// 						KeyHandY();
// 						sel_axis=2;
// 						break;	
// 					case 247:
// 						KeyHandZ();
// 						sel_axis=3;
// 						break;	
// 					case 239:
// 						KeyHandA();
// 						sel_axis=4;
// 						break;	
// 					case 223:
// 						KeyHandB();
// 						sel_axis=5;
// 						break;	
// 					case 191:
// 						KeyHandC();
// 						sel_axis=6;
// 						break;
// 					case 127:
// 						KeyHandD();
// 						sel_axis=7;
// 						break;	
//             
// 					default:
// 						break;
// 				}
// 			}
// 			if( MachineStatus.hand_plugin &&  !(MachineStatus.op_mode&(PARA_MODE+HELP_MODE)) )
// 				sendhand(sel_axis,sel_meg);
// 			state=0;
// 					
// 		break;
// 		}
// 	
}
SDWORD ReadMov(BYTE	axis)
{
	SDWORD u1,u2 ;
	SDWORD *base= (SDWORD *)(pc_base+0x8+(axis << 4)) ;
	u1=	*base ;
	while(1){
		u2 = *base ;
		if(u1==	u2){
			return(u1) ;
		}
		else{
			u1=	u2 ;
		}
	}
}
int dMOTORUNIT_X()
{
// 	int  max_x ;
// 	max_x = (MachineStatus.Unit[AXIS_X] == UNIT_GRID)?4000: 3600 ;
// 	//max_x = (MachineStatus.Unit[AXIS_X] == UNIT_GRID)?BMOTORGRID(AXIS_X): 3600 ;
// 	if(max_x==0)max_x=4000 ;
// 	return(max_x) ;
}
int dBMOTORUNIT_X()
{
	DWORD  tmp;
	int  max_x ;
	max_x = dMOTORUNIT_X() ;
	//tmp = BcdToBin(8,max_x );
	return(max_x) ;
}


WORD wRead2016 (BYTE	axis)
{
// 	WORD w,	t;

// 	w  = (WORD)dReadAbsPos(axis) ;
//   if(axis == AXIS_X){
// 		WORD t1=(WORD) BMOTORGRID_X ;
// 		t =	t1;
// 		if(	MachineStatus.home_err ){
// 			w =	t1 ;
// 		}
// 		else{
// 			if(	w >	t )	 {
// 				w = 0;
// 			}
// 		}
// 	}
// 	return(	w );
}
void GRID_TO_CIR(BYTE axis,SDWORD &tt)
{
// 	tt= int32(tt *100.0/ BMOTORGRID(axis)+0.5) ;
}
void CIR_TO_GRID(BYTE axis,SDWORD &tt)
{
// 	tt= int32(tt *float(BMOTORGRID(axis)) /100.0+0.5) ;
}
void  GRID_TO_DEG(BYTE axis,SDWORD &tt)
{
// 	tt= int32(tt *3600.0/ BMOTORGRID(axis)+0.5) ;
}
void DEG_TO_GRID(BYTE axis, SDWORD &tt)
{
// 	tt= int32(tt *float(BMOTORGRID(axis)) /3600.0+0.5) ;
}
void  GRID_TO_XGRID(BYTE axis,SDWORD &tt)
{
// 	tt= int32(tt *4000.0/ BMOTORGRID(axis)+0.5) ;
}
void XGRID_TO_GRID(BYTE axis, SDWORD &tt)
{
// 	tt= int32(tt *float(BMOTORGRID(axis)) /4000.0+0.5) ;
}
void  MM_TO_GRID(BYTE axis,SDWORD &mm)
{
// 	long long y1=BcdToBin(4,MachineStatus.Y1);//�ƭȬۭ��L�j,��long long
// 	long long y0=BcdToBin(5,MachineStatus.nY0[axis]);
// 	
// 	mm = (mm*y0/y1) ;
}
void GRID_TO_MM(BYTE axis,SDWORD &grid)
{
// 	long long y1=MachineStatus.Y1;//�ƭȬۭ��L�j,��long long
// 	long long y0=MachineStatus.nY0[axis];
// 	grid = (grid*y1/y0) ;
}
void TO_GRID_NOT_ROTATE(  BYTE axis,SDWORD &dw)
{
// 	switch(MachineStatus.Unit[axis]){
// 	case UNIT_GRID:
// 		if (axis == AXIS_X){
// 			XGRID_TO_GRID(axis,dw);
// 		}	
// 		break;
// 	case UNIT_DEG:
// 		DEG_TO_GRID(axis,dw) ;
// 		break ;
// 	case UNIT_MM:
// 		MM_TO_GRID(axis,dw);
// 		break ;
// 	case UNIT_CIR:
// 		CIR_TO_GRID(axis,dw) ;
// 		break ;
// 	}
}
void TO_GRID( BYTE axis, SDWORD &dw)
{
// 	if(CHK_ROTATE_A(axis)){
// 		DEG_TO_GRID(axis,dw) ;
// 	}
// #if 0
// 	else if((slide_axis) && (slide_axis == axis)){
// 		dw = dw *5000/6400 ;
// 	}
// #endif
// 	else{
// 		TO_GRID_NOT_ROTATE(axis,dw) ;
// 	}
}
SDWORD BcdToBin (short nibble, DWORD w,BYTE s)
{
	SDWORD tt ;
	tt= (SDWORD) BcdToBin(nibble,w) ;
	if((s&0x7f) == MINUS_SIGN){
		tt=-tt ;
	}
	return(tt) ;

}
//�p��AXIS_X�b,��Ӧ�m(���N�����)����Ʈt�Z
SDWORD sdDifGrid(SDWORD s, SDWORD t)
{	
	TO_GRID_NOT_ROTATE(AXIS_X,s) ;
	TO_GRID_NOT_ROTATE(AXIS_X,t) ;
	return(s-t) ;

}
//�p����N�b,��Ӧ�m(���N�����)����Ʈt�Z
SDWORD sdDifGrid(BYTE axis , SDWORD s, SDWORD t)
{
	TO_GRID(axis,s) ;
	TO_GRID(axis,t) ;
	return(s-t) ;
}


void ReMakeActTable (void)
{
// 	SetClock(OFF_CLOCK);
// 	if( VerifyProg(MachineStatus.speed_mode,0,1) ){
// //		DispCurProgList_q(MachineStatus.last_line);中斷服務程式不可以呼叫fill_proc_queue
// 		
// 		SDWORD tval[MAX_AXIS] ;
// 		for(BYTE axis=AXIS_Z ; axis < MAX_AXIS ; axis++){
// 			tval[axis]= virtual_zabc[axis].initial_move ;
// 		}
// 		//if( (MachineStatus.speed_mode == AUTO) || (MachineStatus.SimFast) ){
// 		//	MakeAutoActTbl(1);
// 		//}
// 		//else{
// 		//	MakeFastActTbl(1);
// 		//}
// 		SetClock(RUN_CLOCK) ;
// 		sort_airtbl();
// 		virtual_move(true) ;
// 		if( REAL_FAST ){
// 			//RunFastStart();
// 		}
// 		else{
// 			RunAutoStart();
// 		}

// 		MachineStatus.prog_mody = 0;
// 		SetClock(MachineStatus.op_mode==TEST_MODE?TEST_CLOCK:STEP_CLOCK);
// 	}
// 	else{
// 		ChgToModyMode(MachineStatus.op_mode==TEST_MODE?TMODY_MODE:SMODY_MODE);
// 	}
}
void ToManProc (void)
{
// 	CurLine=0;
// 	DispCurLine();
// 	BYTE axis;
// 	flag_run= false ;
// 	
// 	DisableHomeInt(AXIS_X);
// 	WireOnOff(0);
// 	//SetSafeSwMode(SAFE_OFF);
// 	DispCurAxis_q(1);
// 	SetClock(RUN_CLOCK);
// 	SetAllGain(MachineStatus.man_gain, 1);
// 	BOUTM &= BNY(0,0,0,1, 1,1,1,1);
// 	wDosMem(pc_base+OUTM , BOUTM) ;
// //	chg_newspeed(0) ;
// 	wDosMem(pc_base+OUTL , (uint8)0);
// 	wDosMem(pc_base+OUTH, (uint8)0) ;
// 	wDosMem(pc_base+OUTE, (uint8)0) ;	
// 	MachineStatus.stop_machine = 0;
// 	MachineStatus.th_test = 0;
// 	enable_all_touch() ; 
// /*
// 	if( MachineStatus.op_mode&RUN_MODE )  ClrRunWin_q();
// 	MachineStatus.op_mode = MAN_MODE;

// 	DispEditWin_q(0);
// 	ClrStatusBar_q();
// 	ClrTouchPos(0, 0x0f);
// 	DispSafeSw_q(MachineStatus.safe_sw);
// 	DispCurAxis_q(1);
// 	CurProgLine = YProgoff = 0;
// 	DispPageProg_q(CurProgLine);
// 	CurProgBuf = ProgBuf[CurProgLine];
// 	CurProgBufExlarge=ProgBufExlarge[CurProgLine];
// 	CursorLoc = PROG_CURSOR;
// 	SetCursor(1);

// 	MachineStatus.scrn_off = 0;
// 	ScreenOnOff(1);

// 	for( axis=0; axis < MachineStatus.axis_no; axis++ ){
// 		MachineStatus.is_home[axis] = 0;
// 	}
// 	nSet8254(MachineStatus.cnt8254);
// 	
// 	

// 	enable_all_touch() ; 
// 	*/
// 	for( axis=0; axis < MachineStatus.axis_no; axis++ ){
// 		MachineStatus.is_home[axis] = 0;
// 	}
// 	MachineStatus.op_mode = MAN_MODE;
// 	SendStatus();
}

void ReturnManMode (void)
{
// 	WORD ret_line, loop_no ;
// 	WORD   	idx, speed, line ;
// 	SDWORD t;
// 	SWORD  	loop_s[MAX_LOOP],	loop_e[MAX_LOOP] ,	zabcend[MAX_AXIS] ;
// 	//�����ɱj����̫᪺ܳ��m
// 	/*
// 	if( MachineStatus.speed_mode != FAST ){
// 		t= BMOTORGRID_X ;
// 		Grid2Unit(AXIS_X,t) ;
// 		t = (SDWORD)MachineStatus.dst_pos[AXIS_X] % t;

// 		
// 		INIT_LOOP();
// 		if(ret_line==PROG_VAL_NULL)MachineStatus.axis_val[AXIS_X] = dBinToBcd(5, t);	//�ϦVN000��ܲ��`
// 	}
// 	else{
// 		MachineStatus.axis_val[AXIS_X] = 0;
// 	}
// 	for(BYTE axis =AXIS_Z ; axis < MachineStatus.axis_no ; axis++){
// 		if( MachineStatus.motor[axis] ){
// 			t= (SDWORD)MachineStatus.dst_pos[axis] ;
// 			if( t<0){
// 				t = -t ;
// 			}
// 			MachineStatus.axis_val[axis] = dBinToBcd(6, t);
// 		}
// 	}
// */
// 	ToManProc();
// 	if( CHECK_MISS_OK() ){
// 		sendError(OverMiss,0,2);							
// 		printf("Reach Miss No !\n");
// 	}
// 	if( CHECK_QUAN_OK() ){
// 		sendError(OverQuan,0,2);	
// 		printf("Reach QTY No !\n"); 
// 	}
// /*
// 	if( CHECK_MISS_OK() ){
// 		FORCE_PROC_QUEUE												
// 		DispMsgWin_q(-1, -1, WAR_WIN|0x80, 	" �W �L �� �~ �q !",
// 									  		" Reach Miss No !" ,
//                              				" Reach Miss No !");
// 		WAIT_NEW_KEY();
// 		ClrMsgWin_q();
// 	}

// 	if( CHECK_QUAN_OK() ){
// 		FORCE_PROC_QUEUE												
// 		DispMsgWin_q(-1, -1, WAR_WIN| 0x80, " �W �L �� �� �q !", 
// 									  		" Reach QTY No !" ,
//                              				" Reach QTY No !");
// 		WAIT_NEW_KEY();
// 		ClrMsgWin_q();
// 	}
// 	
// 	ClrStatusBar_q();	
// 	//if(NewH&&MachineStatus.ScrnSav==0x88){	//��^�\��,��������ܦ��Ƶ���
// 	if(NewH){	//��^�\��,��������ܦ��Ƶ���
// 		DispReutrn_q();	
// 	}

// 	TotalY();
// 	DispTotalY_q();	
// 	*/
}
void PauseClock	(WORD op_mode)
{
// 	//�Ȱ��X��
// 	PauseClock_flg=true;
// 	
// 	SetClock(OFF_CLOCK);
// 	switch(op_mode)
// 	{
// 	case RUN_MODE:
// 		//WireOnOff(0);
// 		//ClrRunWin_q();
// 		//SetSafeSwMode(SAFE_OFF);
// 		//DispSafeSw_q(SAFE_OFF);
// 		break;
// 	case TEST_MODE:
// 		break;
// 	case STEP_MODE:
// 		break;
// 	}
}void RestoreClock (BYTE key)
{
	//2012_1123_�Ȱ��X��---------
// 	PauseClock_flg=false;
// 	switch(MachineStatus.op_mode)
// 	{
// 	case RUN_MODE:
// 		switch( key )
// 		{
// 		case KEY_START:
// 			MachineStatus.op_mode = RUN_MODE;
// 			//DispWorkWin_q(0);
// 			//DispRunWin_q();
// 			SetClock(RUN_CLOCK);
// 			break;
// 		case KEY_TEST:
// 			MachineStatus.op_mode = TEST_MODE;
// 			//DispTestWin_q(0);
// 			SetClock(TEST_CLOCK);
// 			break;
// 		case KEY_STEP:
// 			MachineStatus.op_mode = STEP_MODE;
// 			//DispStepWin_q(0);
// 			SetClock(STEP_CLOCK);
// 			break;
// 		}
// 		break;
// 	case TEST_MODE:
// 		SetClock(TEST_CLOCK);
// 		break;
// 	case STEP_MODE:
// 		SetClock(STEP_CLOCK);
// 		break;
// 	}
}

void ShowToVirtualHome ()
{
	printf("showVirtual\n");
	sendError(VirtualHome,1,3);
	//DispMsgWin_q(-1, -1, MSG_WIN, 	" 移 到 虛 擬 原 點 中 ... ", 
	//							  	" Go Virtual Home ... "  ,
  //                        			" TORNA Virtual HOME ... ");
	//FORCE_PROC_QUEUE ;
}

#define CHK_TIMES				20
void ShowSafeTest (BYTE b)
{
// 	printf("ShowSafeTest\n");
// 	WORD i;

// 	sendError(SlideTest,b,3);
// 	//INI_DISP_BUF();
// 	//Fill_pDispBuf(	" 滑 座 檢 測 ", 
// 	//			  	" Slide Sensor ",
//   //            		" Slide Sensor ");
// 	//pDispBuf_value += BinToStrBuf(2, b, pDispBuf);
// 	//Fill_pDispBuf(	" 測 試 正 常 !", 
// 	//			  	" Test OK !"  ,
//   //            		" Test OK !");
// 	//FILL_DISP_BUF(0);
// //
// 	//DispMsgWin_q(-1, -1, WAR_WIN, DispBuf);
// 	//FORCE_PROC_QUEUE ;
// 	MachineStatus.safe_err = 0;
// 	//SetSafeSwMode(SAFE_TEST);
// 	for( i=0; i<CHK_TIMES && !MachineStatus.safe_err && (KeyBufRIdx == KeyBufWIdx); i++ ){
// 		dDelay(1);
// 	}
// 	sendError(SlideTest,10,3);
}

void WAIT_RUN_TEST_KEY(BYTE type, BYTE ErrorCode)
{ 		
// 	printf("WAIT_RUN_TEST_KEY\n");
// 	//if(type== MSG_WIN){
// 	//	ClrMsgWin_q();
// 	//	INI_DISP_BUF() ;
// 	//	Fill_pDispBuf(	err_str[1],
// 	//					err_str[0],
// 	//					err_str[0]) ;
// 	//	
// 	//	Fill_pDispBuf(" �w �� ��",
// 	//				  " is OK ",
// 	//				  " is OK ");
// 	//}
// 	//Fill_pDispBuf(	"\n �Ұ�/����/��B��----�~��Ͳ�\n���m��---------�^��s��e��" ,
// 	//			  	"\n START/TEST/STEP----Continue produce\nRESET------Return To Edit Screen" ,
//   //            		"\n START/TEST/STEP----Continue produce\nRESET------Return To Edit Screen") ;
// 	//FILL_DISP_BUF(0);
// 	//DispMsgWin_q(-1, -1, type, DispBuf);
// 	//FORCE_PROC_QUEUE
// 	if(ErrorCode==TouchError)
// 			sendError(ErrorCode,MachineStatus.th_stop,3);//探針
// 	else
// 			sendError(ErrorCode,0,2);//線架,Oil,door
// 	ClrKeyBuf();
// 	WARN_LIGHT_OFF_RED 
// 	while( 1 ){
// 		if( KeyBufRIdx != KeyBufWIdx ){
// 			MachineStatus.th_stop = 0;
// 			if(set_ScrnSav()){
// 				continue ;
// 			}
// 			KeyTmp = GetKey();
// 			if( KeyTmp == KEY_START ){
// 				if(MachineStatus.op_mode == RUN_MODE){
// 					WARN_LIGHT_ON_GREEN
// 				}
// 				if( MachineStatus.op_mode&(TEST_MODE+STEP_MODE) )
// 					ResetKeyBuf(KEY_START);
// 				break;
// 			}
// 			else if( KeyTmp == KEY_TEST ){
// 				if( MachineStatus.op_mode != STEP_MODE ){
// 					SendKey(KEY_TEST);
// 					break;
// 				}
// 			}
// 			else if( KeyTmp == KEY_STEP ){
// 				if( MachineStatus.op_mode != TEST_MODE )
// 					break;
// 			}else if(Reset){
// 				SoftReset() ;
// 			}
// 		}
// 		else{
// 			always_update() ;
// 		}
// 	}
}
void DispTestMsg_q()
{
	struct TIMER Ticks;
	int rpm , rpmd ;
	struct TIMER t1 = ReadTimer() ;
	cal_rrpm(t1,Ticks,rpm,rpmd) ;
	//printf("rpm=%03d.%01d\n", rpm,rpmd);//���RPM
	int RPM=rpm*10+rpmd;
	DispRPM(RPM);
}
void complete_spring()
{
	DispTestMsg_q() ;
}
void RUN_RUN(void)
{
	/*
	if(flag_complete_spring_cmd){
		flag_complete_spring_cmd=false ;
		complete_spring_cmd() ;
		
			if( MachineStatus.stop_machine){
				//�����u®���Ͳ�
				flag_run=false ;
				flag_ReturnManMode=true ;
			}
		if(REAL_FAST){
			//ClrStatusBar_q();
		}
	}
	if(flag_complete_spring){
		flag_complete_spring=false ;
		complete_spring() ;
		//DispTestMsg_q();
	}
	if(flag_ReturnManMode){
		flag_ReturnManMode=false ;
		ReturnManMode();
	}
*/
	if(flag_complete_spring_cmd){
		flag_complete_spring_cmd=false ;
		complete_spring_cmd();
	}
	if(flag_complete_spring){
		flag_complete_spring=false ;
		//complete_spring() ;
	}
	if(flag_ReturnManMode){
		flag_ReturnManMode=false ;
		ReturnManMode();
		CloseRPM();
	}
	
	
	
/*
#if 1
	if(no_DispCurProgList){//���դϥզ��
		DispCurProgList_q(buf_DispCurProgList[rd_DispCurProgList++]);
		if(rd_DispCurProgList >= NO_DispCurProgList){
			 rd_DispCurProgList=0 ;
		}
		DISABLE() ;
		no_DispCurProgList--;
		ENABLE() ;
	}
#endif
	*/
}
void AUTO_RUN()
{
// 	int tval, set_val;
// 	static int ltval=0;
// 	static int ltt=0;
// 	if(NewH){
// 		chk_unconnector= true ;
// 		for(int axis=0 ; axis <MachineStatus.axis_no ; axis++){
// 				ChkOverFlow[axis]=true;
// 		}
// 	}
// 	if( MachineStatus.op_mode != RUN_MODE ){			//"�ק�{��"�ݱNADC��0�~�i�H�ϥ�
// 		if(ReadAdc100() < 3){
// 			if(!EnableTest){
// 				//�I�Gtest LED
// 				EnableTest=true ;
// 				if(KeyLockCHG){comm_port=0;wr_rs232(4);wr_rs232(6);wr_rs232(1) ;}
// 			}
// 		}
// 		else{
// 			if(EnableTest){
// 				EnableTest=false ;
// 				if(KeyLockCHG){comm_port=0;wr_rs232(4);wr_rs232(6);wr_rs232(0) ;}
// 			}
// 		}
// 	}
// 		//if(MachineStatus.op_mode!=STEP_MODE && NewH  && MachineStatus.bysafe_plugin && MachineStatus.safe_sw == SAFE_ON&&safe_runtag) {	
// 		//	SAFE_ON_new(MachineStatus.bysafe_plugin);
// 		//}
// 		
// 		for(BYTE axis=0; axis < MachineStatus.axis_no; axis++ ){
// 			if( MachineStatus.motor[axis] && MachineStatus.running[axis] ){
// 				if( CHK_CACL_DELAY() ){
// 					SDWORD tval = ReadReg3701(axis, RD_YREG_3701);
// 					//if(axis==AXIS_X &&MachineStatus.dst_pos[axis]-tval!=0 && ltt!=MachineStatus.dst_pos[axis]-tval){
// 					//	ltt=MachineStatus.dst_pos[axis]-tval;
// 					//	//printf("%d=%d-%d\n",MachineStatus.dst_pos[axis]-tval,MachineStatus.dst_pos[axis],tval);
// 					//}
// 					//printf("%d=%d-%d\n",MachineStatus.dst_pos[axis]-tval,MachineStatus.dst_pos[axis],tval);
// 					if(axis==AXIS_X && ((SDWORD)MachineStatus.dst_pos[axis]) - tval< 0 && !MachineStatus.XMINUS){//N000�����V�|��ܭt�� //�u��X�b�~�|
// 						tval = ((SDWORD)MachineStatus.dst_pos[axis]) - tval;//�ت��a�����-�����������
// 						tval+=4000;
// 					}
// 					else{
// 					//if(axis==AXIS_Y)printf("%d %d\n",MachineStatus.dst_pos[axis],tval);
// 						tval = ((SDWORD)MachineStatus.dst_pos[axis]) - tval;//�ت��a�����-�����������
// 						if(axis==AXIS_X && tval>=4000)
// 							tval-=4000;
// 					}
// 					/*
// 					if(axis==AXIS_X && tval>=4000){
// 						tval-=4000;
// 					}
// 					*/
// 					BYTE sign = tval<0?MINUS_SIGN:PLUS_SIGN;
// 					MachineStatus.sign[axis]	  = sign;
// 					//MachineStatus.axis_val[axis]  = dBinToBcd(6, tval*(sign==PLUS_SIGN?1:-1));
// 										MachineStatus.axis_val[axis]  = tval;//*(sign==PLUS_SIGN?1:-1);
// 										
// 					//if(axis==AXIS_X &&MachineStatus.axis_val[axis]!=0){
// 					//	printf("%d=%d-%d\n",MachineStatus.axis_val[axis],MachineStatus.dst_pos[axis],tval);
// 					//}
// 				}
// 			}
// 		}
// 		DispDelay++ ;
// 		if(IsTimeUp(timeout_DispCurAxis) ){
// 			if (MachineStatus.op_mode&(TEST_MODE+STEP_MODE))
// 				DispCurLine();
// 			DispCurAxis_q(0);
// 			timeout_DispCurAxis= mTimerSet(MAX_DispCurAxis);
// 		}
}

void Unit2Grid(BYTE axis , SDWORD &d)
{
// 	if(CHK_ROTATE_A(axis)){
// 		DEG_TO_GRID(axis,d)	;
// 	}
// 	else if (axis == AXIS_X && MachineStatus.Unit[axis] == UNIT_GRID){
// 		XGRID_TO_GRID(axis,d);
// 	}
// 	else{
// 		switch(MachineStatus.Unit[axis]){
// 		case UNIT_DEG :  
// 			DEG_TO_GRID(axis,d)	;
// 			break ;
// 		case UNIT_MM : 
// 		    if(axis == AXIS_Y){
// 				MM_TO_GRID(axis,d) ;
// 			}
// 			break ;
// 		case UNIT_CIR :  
// 			CIR_TO_GRID(axis,d)	;
// 			break ;		
// 		}
// 	}
}
int TimerIsr()
{
// 	TimerTicks.timer++ ;
// 	//if(TimerTicks.timer%60000==0)
// 	//	printf("%lld\n",TimerTicks.timer);
// 	if(NewH){
// 		KeyIsr() ;
// 		HandIsr();
// 	}
// 	if((flag_run) &&  (MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE)) ){
// 		if( REAL_FAST ){
// 			ISR_FAST_RUN();
// 		}
// 		else{
// 			ISR_AUTO_RUN();
// 		}
// 	}
	
}
SDWORD Off3701Pos(SDWORD Start , SDWORD cur)
{
	SDWORD t= (SWORD)((WORD)cur - (WORD)Start) ;
	return(t) ;
}
void CHECK_RESET(bool stopmotor)
{
	ngetkey();
	if( Reset ){
		if(stopmotor){
			StopMotor() ;
		}
		SoftReset();
	}
	if( KeyBufRIdx != KeyBufWIdx ){
		set_ScrnSav() ; //�s620
	}
}
void CHECK_RESET_update(bool stopmotor)
{
	CHECK_RESET(stopmotor) ;
	always_update() ;	
}
void always_update()
{
		update_run_DDA() ;
}
struct TIMER  ReadTimer()
{
//#ifdef  DEBUG_CLOCKISR
//	TimerTicks2.timer++ ;
//#endif 
	return(TimerTicks2) ;
}
// 單位1分
struct TIMER  minTimerSet(unsigned int d){
	struct TIMER tt= ReadTimer() ;
	tt.timer +=((d) *NOCNT_1S*60) ;
	return (tt ) ;
}
// 單位1秒
struct TIMER sTimerSet(unsigned int d){
	struct TIMER tt= ReadTimer() ;
	tt.timer +=((d) *NOCNT_1S) ;
	return (tt ) ;
}
// 單位0.1秒
struct TIMER dTimerSet(unsigned int d){
	struct TIMER tt= ReadTimer() ;
	tt.timer +=((d) *NOCNT_1DS) ;
	return (tt ) ;
} 
// 單位0.01秒
struct TIMER hTimerSet(unsigned int h){
	struct TIMER tt= ReadTimer() ;
	tt.timer +=((h)*NOCNT_1HS) ;
	return (tt ) ;
}
// 單位0.001秒
struct TIMER  mTimerSet(unsigned long m){
	struct TIMER tt= ReadTimer() ;
	tt.timer +=((m) *NOCNT_1MS) ;
	return (tt ) ;
} 
struct TIMER  tickTimerSet(unsigned int tick){
	struct TIMER tt= ReadTimer() ;
	tt.timer +=((tick)) ;
	return (tt ) ;
}
void sDelay(unsigned int sec){ //延遲sec 秒
	struct TIMER timeout= sTimerSet(sec) ;
	while(!IsTimeUp(timeout)) ;
}
void dDelay(unsigned int ds){ //延遲ds個十分之一 秒
	struct TIMER timeout= dTimerSet(ds) ;
	while(!IsTimeUp(timeout)) ;
}
void hDelay(unsigned int hs){ //延遲hs個百分之一 秒
	struct TIMER timeout= hTimerSet(hs) ;
	while(!IsTimeUp(timeout)) ;
}
bool IsTimeUp(struct TIMER h){
	struct TIMER tt=ReadTimer() ;
	return(((tt.timer-h.timer) < 0 )? false :true) ;
}
void mDelay(unsigned int ms){ //延遲ms個千分之一 秒
	struct TIMER timeout= mTimerSet(ms) ;
	while(!IsTimeUp(timeout)) ;
}
void tickDelay(unsigned int tick){ //延遲ms個千分之一 秒
	struct TIMER timeout= tickTimerSet(tick) ;
	while(!IsTimeUp(timeout)) ;
}
float ELAAPSED_MS(struct TIMER t0,struct TIMER  t1){
		return(ELAAPSED_CNT(t0,t1)/float(NOCNT_1MS)) ;
}
long long ELAAPSED_CNT(struct TIMER  t0,struct TIMER  t1){
	return(((t1.timer)-(t0.timer))) ;
}struct TIMER tt ;
void init_interval_time()
{
	tt= ReadTimer() ;
}
float interval_time()
{
	struct TIMER t1=ReadTimer() ;
	return((t1.timer-tt.timer)/float(NOCNT_1MS)) ;
}
void mDelay_s(int ms)
{
	for(int i=0 ; i < ms ; i++){
		for(long l=0 ; l < 0x2334L ; l++){
		}
	}
}
void DelayCount (DWORD cnt)
{
	while( cnt-- );
}

void InitAirTbl()
{
// 	AirTblIdx= 0;
	lcur_x=0;
	ldir=PLUS_MOVE ;
	has_SET_TOUCH=false ;
}
void InitIo (void)
{
	wDosMem(pc_base+OUTL, (uint8)0);
	wDosMem(pc_base+OUTM, BOUTM = 0);
	wDosMem(pc_base+OUTH, (uint8)0);;//IO2
	wDosMem(pc_base+OUTE, (uint8)0);//IO2

	wDosMem(pc_base+0x160, (uint8)0xfd);  //�]�wemstop_reg bit0�]0,�b���wtouch���,�|�M���ѤU��pluse
	ini_th_stopy() ;
	OFF_StopMotorLine
}
void ini_th_stopy()
{
	if(!NewH){
		// touch����Y�b���B�n 
		th_stopy=0x00 ;
		wDosMem(pc_base+TOUCH_ADDR, th_stopy) ;
		if(axis_type == INTEL8051_AXIS){
			wDosMem(pc_base+0x200+TOUCH_ADDR, (BYTE)0xf) ;  //B�b�ﱴ�w0:�۰ʰ����F,1:����
		}
	}
}

void DispMovAxis_q (BYTE axis)
{
// 	int tval, set_val;
// 	static int ltval=0;
// 	if( MachineStatus.motor[axis] ){
// 			set_val = ReadReg3701(axis, RD_VREG_3701); //�`�@�n���ʪ����
// 			tval	= ReadReg3701(axis, RD_YREG_3701); //�ѤU�S�����ʪ����
// 			tval = set_val - tval;//�ثe�w���ʪ����
// 		
// 			MachineStatus.sign[axis]	 = MachineStatus.dst_pos_sign[axis];
// 		//if(axis==AXIS_Y &&MachineStatus.axis_val[axis]!=0){
// 		//	printf("%d %d\n",MachineStatus.axis_val[axis] , MachineStatus.dst_pos[axis]);
// 		//	MachineStatus.axis_val[axis] = MachineStatus.dst_pos[axis];
// 		////MachineStatus.sign[axis]	 = MachineStatus.dst_pos_sign[axis];
// 		////int dif=tval-ltval;
// 		//}
// 		//else
// 			MachineStatus.axis_val[axis] = MachineStatus.dst_pos[axis];
// 		
// 		 MachineStatus.axis_val[axis]+=tval;
// 		
// 		
// 		
// 		
// 		if(MachineStatus.axis_val[axis]>=0)
// 			MachineStatus.sign[axis]= MachineStatus.dst_pos_sign[axis]=PLUS_SIGN;
// 		else
// 			MachineStatus.sign[axis]= MachineStatus.dst_pos_sign[axis]=MINUS_SIGN;
// 			//DWBcdAddBin(&(MachineStatus.sign[axis]), &(MachineStatus.axis_val[axis]), tval);
// 			ChkAxisVal(axis, &(MachineStatus.sign[axis]), &(MachineStatus.axis_val[axis]));
// 	}
// 	DispCurAxis_q(0);
}
#define HAND_SEL(axis)									 \
	MachineStatus.hand_plugin = 1;						 \
	MachineStatus.hand_sel = axis;						 \
	if( !(MachineStatus.op_mode&(PARA_MODE+HELP_MODE)) ){\
		DispHandVal_q();								 \
	}
void DispHandVal_q (void)
{
// 	if( MachineStatus.hand_plugin &&  !(MachineStatus.op_mode&(PARA_MODE+HELP_MODE)) ){
// 		
// 		//MachineStatus.hand_sel__(OFF_255_X_0_Y_1_Z_2_A_3_B_4_C_5_D_6_E_7)
// 		//MachineStatus.handval[i](X1_0x1_X10_0x10_X100_0x100)
// 	}
}
void CHG_HAND_SCALE(WORD scale)
{
// 	MachineStatus.hand_plugin = 1;
// 	MachineStatus.hand_scale = scale;
// 	for(BYTE axis=0; axis < MachineStatus.axis_no; axis++ ){
// 		MachineStatus.handval[axis] = scale;
// 	}
// 	if(MachineStatus.handval[AXIS_X] ==0x100){
// 		 MachineStatus.handval[AXIS_X]=10 ;
// 		 //MachineStatus.handval[AXIS_X]=MachineStatus.MPG_X100 ;
// 	}
// 	if((MachineStatus.handval[AXIS_A] ==0x100)&& CHK_ROTW(AXIS_A)){
// 		 MachineStatus.handval[AXIS_A]=10 ;
// 	}
// 	if( MachineStatus.hand_plugin &&  !(MachineStatus.op_mode&(PARA_MODE+HELP_MODE)) ){
// 		
// 					
// 		//printf("scale=%d x_%d y_%d z_%d a_%d b_%d c_%d d_%d e_%d\n",scale,MachineStatus.handval[0],MachineStatus.handval[1],MachineStatus.handval[2],MachineStatus.handval[3]
// 		//																			 ,MachineStatus.handval[4],MachineStatus.handval[5],MachineStatus.handval[6],MachineStatus.handval[7]);
// 	}
// 	//if( !(MachineStatus.op_mode&(PARA_MODE+HELP_MODE)) ){
// 	//	DispHandVal_q();
// 	//}
}
	void KeyHandX1 (void)
{
	CHG_HAND_SCALE(1);
}

void KeyHandX10 (void)
{
	CHG_HAND_SCALE(10);
}

void KeyHandX100 (void)
{
	CHG_HAND_SCALE(100);
}


void KeyHandOff (void)
{
// 	HAND_SEL(0xff);
}

void KeyHandX (void)
{
// 	HAND_SEL(AXIS_X);
}

void KeyHandY (void)
{
// // 	HAND_SEL(AXIS_Y);
}

void KeyHandZ (void)
{
// 	HAND_SEL(AXIS_Z);
}

void KeyHandA (void)
{
// 	HAND_SEL(AXIS_A);
}

void KeyHandB (void)
{
// 	HAND_SEL(AXIS_B);
}

void KeyHandC (void)
{
// 	HAND_SEL(AXIS_C);
}
void KeyHandD (void)
{
// 	HAND_SEL(AXIS_D);
}

void KeyHandE (void)
{
// // 	HAND_SEL(AXIS_E);
}
void Test_IO(uint8 keycode){
	unsigned char OT[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00};
	switch (keycode){
		case 0x20:
			wDosMem(pc_base+OUTH, OT[0]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("AIR1--output1\n");
			break;
		case 0x10:
			wDosMem(pc_base+OUTH, OT[1]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("AIR2--output2\n");
			break;
		case 0xa0:
			wDosMem(pc_base+OUTL, OT[2]) ;
			wDosMem(pc_base+OUTM, OT[8]) ;
			printf("AIR3--output3\n");
			break;
		case 0x21:
			wDosMem(pc_base+OUTL, OT[3]) ;
			wDosMem(pc_base+OUTM, OT[8]) ;
			printf("AIR4--output4\n");
			break;
		case 0x11:
			wDosMem(pc_base+OUTL, OT[4]) ;
			wDosMem(pc_base+OUTM, OT[8]) ;
			printf("AIR5--output5\n");
			break;
		case 0x1:
			wDosMem(pc_base+OUTL, OT[5]) ;
			wDosMem(pc_base+OUTM, OT[8]) ;
			printf("AIR6--output6\n");
			break;
		case 0x22:
			wDosMem(pc_base+OUTL, OT[6]) ;
			wDosMem(pc_base+OUTM, OT[8]) ;
			printf("AIR7--output7\n");
			break;
		case 0x12:
			wDosMem(pc_base+OUTL, OT[7]) ;
			wDosMem(pc_base+OUTM, OT[8]) ;
			printf("AIR8--output8\n");
			break;
		case 0x2:
			wDosMem(pc_base+OUTL, OT[8]) ;
			wDosMem(pc_base+OUTM, OT[0]) ;
			printf("WIRE SPEED UP--output9\n");
			break;
		case 0x23:
			wDosMem(pc_base+OUTL, OT[8]) ;
			wDosMem(pc_base+OUTM, OT[1]) ;
			printf("BUZZER--output10\n");
			break;
		case 0x13:
			wDosMem(pc_base+OUTL, OT[8]) ;
			wDosMem(pc_base+OUTM, OT[2]) ;
			printf("2nd SPEED--output11\n");
			break;
		case 0x3:
			wDosMem(pc_base+OUTL, OT[8]) ;
			wDosMem(pc_base+OUTM, OT[3]) ;
			printf("POWER OFF OUT--output12\n");
			break;
		case 0x24:
			wDosMem(pc_base+OUTL, OT[8]) ;
			wDosMem(pc_base+OUTM, OT[4]) ;
			printf("ALARM LIGHT--output13\n");
			break;
		case 0x14:
			wDosMem(pc_base+OUTL, OT[8]) ;
			wDosMem(pc_base+OUTM, OT[5]) ;
			printf("3rd SPEED--output14\n");
			break;			
		
		


		case 0x4:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[6]) ;
			printf("EX_OUT17\n");
			break;	
		case 0x25:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[7]) ;
			printf("EX_OUT18\n");
			break;	
			
		case 0x15:
			wDosMem(pc_base+OUTH, OT[0]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT1\n");
			break;	
		case 0x5:
			wDosMem(pc_base+OUTH, OT[1]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT2\n");
			break;	
			
		case 0x27:
			wDosMem(pc_base+OUTH, OT[2]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT3\n");
			break;	
		case 0x17:
			wDosMem(pc_base+OUTH, OT[3]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT4\n");
			break;	
		case 0x76:
			wDosMem(pc_base+OUTH, OT[4]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT5\n");
			break;	

		case 0x28:
			wDosMem(pc_base+OUTH, OT[5]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT6\n");
			break;	
		case 0x18:
			wDosMem(pc_base+OUTH, OT[6]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT7\n");
			break;	
		case 0x8:
			wDosMem(pc_base+OUTH, OT[7]) ;
			wDosMem(pc_base+OUTE, OT[8]) ;
			printf("EX_OUT8\n");
			break;	
			
			
		case 0x43:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[0]) ;
			printf("EX_OUT9\n");
			break;	
			
			
		case 0x44:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[1]) ;
			printf("EX_OUT10\n");
			break;	
			
		case 0x45:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[2]) ;
			printf("EX_OUT11\n");
			break;	
			
		case 0x53:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[3]) ;
			printf("EX_OUT12\n");
			break;	
			
		case 0x54:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[4]) ;
			printf("EX_OUT13\n");
			break;	
			
		case 0x55:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[5]) ;
			printf("EX_OUT14\n");
			break;	
			
		case 0x63:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[6]) ;
			printf("EX_OUT15\n");
			break;	
			
		case 0x64:
			wDosMem(pc_base+OUTH, OT[8]) ;
			wDosMem(pc_base+OUTE, OT[7]) ;
			printf("EX_OUT16\n");
			break;	
	}
}
void Test_input(){
	bool loopend=false ;
	printf("Test input\n");
		do{	
			if((TimerTicks.timer%3000)==0){
				if((rDosMem(pc_base+INL) &0x01)==0){
					printf("OIL ERROR--input1");
				}
				if((rDosMem(pc_base+INL) &0x02)==0){
					printf("SYSTEM LOCK--input2");
				}
				if((rDosMem(pc_base+INL) &0x04)==0){
					printf("SAFE DOOR--input3");
				}
				if((rDosMem(pc_base+INL) &0x08)){
					printf("T3--input4");
				}
				if((rDosMem(pc_base+INL) &0x10)){
					printf("T4--input5");
				}
				if((rDosMem(pc_base+INL) &0x20)==0){
					printf("WIRE ERROR--input6");
				}
				if((rDosMem(pc_base+INL) &0x40)){
					printf("T1--input7");
				}
				if((rDosMem(pc_base+INL) &0x80)){
					printf("T2--input8");
				}
				
				
				
				if((rDosMem(pc_base+INM) &0x01)==0){
					printf("X--input9");
				}
				if((rDosMem(pc_base+INM) &0x02)==0){
					printf("A+--input10");
				}
				if((rDosMem(pc_base+INM) &0x04)==0){
					printf("A---input11");
				}
				if((rDosMem(pc_base+INM) &0x08)==0){
					printf("KEY LOCK--input12");
				}
				if((rDosMem(pc_base+INM) &0x10)==0){
					printf("Y+--input13");
				}
				if((rDosMem(pc_base+INM) &0x20)==0){
					printf("Y---input14");
				}
				if((rDosMem(pc_base+INM) &0x40)==0){
					printf("KEY SWITCH--input15");
				}
				if((rDosMem(pc_base+INM) &0x80)==0){
					printf("UV1--input16");
				}
				
				
			
				if((rDosMem(pc_base+INH) &0x01)==0){
					printf("POWER OFF IN--input17\n");
				}			
				if((rDosMem(pc_base+INH) &0x02)==0){
					printf("B--input20\n");
				}			
				if((rDosMem(pc_base+INH) &0x04)==0){
					printf("A--input19\n");
				}			
				if((rDosMem(pc_base+INH) &0x08)==0){
					printf("C--input21\n");
				}			
				if((rDosMem(pc_base+INH) &0x10)==0){
					printf("Z--input18\n");
				}
				if((rDosMem(pc_base+INH) &0x20)==0){
					printf("D--input22,Exit\n");
					loopend=true;
				}


				if((rDosMem(pc_base+INH) &0x40)==0){
					printf("Ext--input1\n");
				}
				if((rDosMem(pc_base+INH) &0x80)==0){
					printf("Ext--input2\n");
				}				
				
				if((rDosMem(pc_base+IND) &0x01)==0){
					printf("Ext--input3\n");
				}			
				if((rDosMem(pc_base+IND) &0x02)==0){
					printf("Ext--input4\n");
				}			
				if((rDosMem(pc_base+IND) &0x04)==0){
					printf("Ext--input5\n");
				}			
				if((rDosMem(pc_base+IND) &0x08)==0){
					printf("Ext--input6\n");
				}			
				if((rDosMem(pc_base+IND) &0x10)==0){
					printf("Ext--input7\n");
				}
				if((rDosMem(pc_base+IND) &0x20)==0){
					printf("Ext--input8\n");
				}
				if((rDosMem(pc_base+IND) &0x40)==0){
					printf("Ext--input9\n");
				}
				if((rDosMem(pc_base+IND) &0x80)==0){
					printf("Ext--input10\n");
				}
			}
		}
		while(!loopend) ;	
	
	
}

void SetClock (short type)
{
	if(NewH){
		CLOCKType=type ;
	}
}

bool chk_utouch(WORD no,WORD start , WORD end)
{
// 	if(!MachineStatus.pass_th[no]){
// 		return(true) ;
// 	}
// 	else{
// 		//�D�T���e���]�w�����w��start=end=0,
// 		//�T���e���]�w�����w���ˬd���쪺��m,�O�_�bstart(�Ӧ�x�_�l��m)�Mend(�Ӧ�x������m)����
// 		// start�i��j��end;start�i��p��end
// 		if(start== end)return(false) ; 
// 		if(((dsave_cur_th[no] >= start) && (dsave_cur_th[no] <= end))||
// 		   ((dsave_cur_th[no] >= end) && (dsave_cur_th[no] <= start))
// 		){
// 			return(false) ;
// 		}
// 		else{
// 			return(true) ;
// 		}
// 	}
}

void chg_newspeed(bool speedup)
{							  
	if(speedup){
		BOUTM |= MASK_BIT2 ;
	}
	else{
		BOUTM &= (~MASK_BIT2) ;
	}
	wDosMem(pc_base+OUTM, BOUTM) ;
}

void Grid2Unit(BYTE axis , SDWORD &d)
{
// 	if(CHK_ROTATE_A(axis)){
// 		GRID_TO_DEG(axis,d)	;
// 	}
// 	else if (axis == AXIS_X && MachineStatus.Unit[axis] == UNIT_GRID){
// 		GRID_TO_XGRID(axis,d);
// 	}
// #if 0
// 	else if(slide_axis && (slide_axis == axis)){
// 		d= d*6400/5000 ;
// 	}
// #endif
// 	else{
// 		switch(MachineStatus.Unit[axis]){
// 		case UNIT_DEG :  
// 			GRID_TO_DEG(axis,d)	;
// 			break ;
// 		case UNIT_MM : 
// 		    if(axis == AXIS_Y){
// 				GRID_TO_MM(axis,d) ;
// 			}
// 			break ;
// 		case UNIT_CIR :  
// 			GRID_TO_CIR(axis,d)	;
// 			break ;		
// 		}
// 	}
}
void sort_airtbl()
{
	//AirTbl_t  HUGE	*a_tbl=AirTbl;
	//AirTbl_t   t_tbl;
	if(Air_idx ==0){
		AirTblOn = false ;
		return ;
	}
	else{
		AirTblOn= true ;
// 		AirTbl[Air_idx].cmd		  =	END_ACT;
		Air_idx++;
	}
	/*
	Airpp[0]=(UC*) & RActtbl[0];
	int Curidx=0;
	do{
		struct AgetsetAir *getsetAir=(struct AgetsetAir *)Airpp[Curidx];
		struct AsetTouch *setTouch=(struct AsetTouch *)Airpp[Curidx];
		struct AclrTouch *clrTouch=(struct AclrTouch *)Airpp[Curidx++];
			
				printf("Cmd=%d\n",getsetAir->cmd);
		switch (getsetAir->cmd){
			case Airtbl_SET_AIR:	
			case Airtbl_CLR_AIR:	
				AirTbl[Curidx].cmd=getsetAir->cmd;
				AirTbl[Curidx].chk_pos=getsetAir->chk_pos;
				AirTbl[Curidx].u.air=getsetAir->u.air;
				AirTbl[Curidx].dir=getsetAir->dir;
				printf("curidx=%d\n",Curidx);
			break;
			
			//case Airtbl_CLR_AIR:	
			//	AirTbl[Curidx].chk_pos=getsetAir->chk_pos;
			//	AirTbl[Curidx].u.air=getsetAir->u.air;
			//	AirTbl[Curidx].dir=getsetAir->dir;
			//break;
			
			case Airtbl_SET_TOUCH://4byte	
				AirTbl[Curidx].cmd=setTouch->cmd;
				AirTbl[Curidx].u.air=setTouch->t.touch;	
				AirTbl[Curidx].chk_pos=setTouch->chk_pos;
				AirTbl[Curidx].dir=setTouch->dir;
				printf("curidx=%d\n",Curidx);
			break;
			
			case Airtbl_CLR_TOUCH://4byte	
				AirTbl[Curidx].cmd=clrTouch->cmd;
				AirTbl[Curidx].u.air=clrTouch->t.touch;
				AirTbl[Curidx].chk_pos=clrTouch->chk_pos;
				AirTbl[Curidx].utouch.start=clrTouch->utouch.start;
				AirTbl[Curidx].utouch.end=clrTouch->utouch.end;
				AirTbl[Curidx].dir=clrTouch->dir;
				printf("curidx=%d\n",Curidx);
			break;		
			
		}
	}while(Curidx+1<Air_idx);
	*/
}

void RunAirTbl (DWORD cur_x,BYTE mov_dir)
{	
// 	AirTbl_t HUGE *a_tbl;
// 	BYTE   th, miss;
// 	int sAirTblIdx= AirTblIdx ;
// 	miss  = 0;
// 	WORD off_move=0 ;

// 	//找出off_move
// 	int tAirTblIdx= AirTblIdx ;
// 	if((mov_dir == PLUS_MINUS) || (mov_dir == MINUS_PLUS)){						
// 		while(1){
// 			if((mov_dir== PLUS_MINUS)&&(AirTbl[tAirTblIdx].cmd != END_ACT)){
// 				if((AirTbl[tAirTblIdx].cmd != LOC_PLUS_MINUS)){
// 					tAirTblIdx++ ;
// 				}
// 				else{
// 					off_move = (WORD)(AirTbl[tAirTblIdx].chk_pos-cur_x) ;
// 					break ;
// 				}
// 			}
// 			else if((mov_dir== MINUS_PLUS)&&(tAirTblIdx > 0)){
// 				if((AirTbl[--tAirTblIdx].cmd != LOC_MINUS_PLUS)){}
// 				else{
// 					off_move = (WORD)(cur_x-AirTbl[tAirTblIdx].chk_pos);
// 					break ;
// 				}
// 			}
// 			else{
// 				return ;
// 			}
// 		}
// 		

// 		if(off_move > OFF_MOVE){			
// 			return ;
// 		}
// 	}
// 	while(1){
// 		if((mov_dir== PLUS_MOVE)&&(AirTbl[AirTblIdx].cmd != END_ACT) && ((SDWORD)cur_x >= AirTbl[AirTblIdx].chk_pos)){
// 			if(AirTbl[AirTblIdx].dir != mov_dir){
// 				printf("1_idx=%d_%d__%d\n",AirTblIdx,AirTbl[AirTblIdx].dir,mov_dir);
// 				AirTblIdx++ ;
// 				continue ;
// 			}
// 		}
// 		else if((mov_dir== PLUS_MINUS)&&(AirTbl[AirTblIdx].cmd != END_ACT) && (((SDWORD)cur_x+off_move) >= AirTbl[AirTblIdx].chk_pos)){


// 		}
// 		else if((mov_dir== MINUS_MOVE)&&(AirTblIdx > 0) && ((SDWORD)cur_x <= AirTbl[AirTblIdx-1].chk_pos)){
// 			AirTblIdx-- ;
// 			if(AirTbl[AirTblIdx].dir != mov_dir) continue ;
// 		}
// 		else if((mov_dir== MINUS_PLUS)&&(AirTblIdx > 0) && (((SDWORD)cur_x-off_move) <= AirTbl[AirTblIdx-1].chk_pos)){
// 			AirTblIdx-- ;
// 		}
// 		else{
// 			break ;
// 		}
// 		a_tbl = &(AirTbl[AirTblIdx]);
// 		printf("cmd=%d\n",a_tbl->cmd);
// 		switch( a_tbl->cmd ){
// 		RUN_MISS_SET_AIR

// 		case SET_AIR://4byte	
// 				MachineStatus.air_buf |= a_tbl->u.air ;
// 				wDosMem(pc_base+OUTL , MachineStatus.air_buf);
// 		break;
// 		case CLR_AIR://4byte	
// 			MachineStatus.air_buf &= a_tbl->u.air ;
// 			wDosMem(pc_base+OUTL , MachineStatus.air_buf);
// 		break;
// 		case CLR_LOOP_AIR:
// 			if(	MachineStatus.in_loop ){
// 				//MachineStatus.air_buf &= a_tbl->u.air ;
// 				//wDosMem(pc_base+OUTL , MachineStatus.air_buf);
// 				//break;				
// 			}	
// 		case SET_TOUCH:  			
// 			//if(CHK_MATCH_LINE(a_tbl)){	
// 				has_SET_TOUCH=true ;									
// 				th = a_tbl->u.t.touch ;													
// 				ini_th_stopy() ;													
// 				if(	th==TH1_STP	|| th==TH1_CHK ){										
// 					MachineStatus.rec_th[0]	 = 	PROG_VAL_NULL;							
// 					MachineStatus.pass_th[0] = 0;										
// 					MachineStatus.chk_th[0]	 = th;										
// 					MachineStatus.chk_th_stop_axis[0]  = 1;//setTouch->t.stop_axis;			
// 					if(th== TH1_CHK){													
// 						DISABLE_TOUCH_STOP(1) ;											
// 					}																	
// 					else{																
// 						TOUCH_STOP(1,	STOPY) ;										
// 					}																	
// 					ENABLE_TOUCH_INT(1) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT6 ;								
// 					wDosMem(pc_base+OUTL ,MachineStatus.air_buf) ;						
// 				}																		
// 				else if( th==TH2_STP ||	th==TH2_CHK	){									
// 					MachineStatus.rec_th[1]	 =  PROG_VAL_NULL ;							
// 					MachineStatus.pass_th[1] = 0 ;										
// 					MachineStatus.chk_th[1]	 = th ;										
// 					MachineStatus.chk_th_stop_axis[1]  = 1;//setTouch->t.stop_axis;	
// 					if(th== TH2_CHK){													
// 						DISABLE_TOUCH_STOP(2) ;											
// 					}																	
// 					else{																
// 						TOUCH_STOP(2,	STOPY) ;										
// 					}																	
// 					ENABLE_TOUCH_INT(2) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT7 ;								
// 					wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						
// 				}																		
// 				else if( th	== TH3_STP ){												
// 					MachineStatus.rec_th[2]	 =PROG_VAL_NULL ;							
// 					MachineStatus.pass_th[2] = 0 ;										
// 					MachineStatus.chk_th[2]	 = th ;										
// 					MachineStatus.chk_th_stop_axis[2]  = 1;//setTouch->t.stop_axis;		
// 					TOUCH_STOP(3,	STOPY) ;											
// 					ENABLE_TOUCH_INT(3) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT4 ;								
// 					wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						
// 				}																		
// 				else if( th	== TH4_STP ){												
// 					MachineStatus.rec_th[3]	 = PROG_VAL_NULL ;							
// 					MachineStatus.pass_th[3] = 0 ;										
// 					MachineStatus.chk_th[3]	 = th ;										
// 					MachineStatus.chk_th_stop_axis[3]  = 1;//setTouch->t.stop_axis;		
// 					TOUCH_STOP(4,	STOPY) ;											
// 					ENABLE_TOUCH_INT(4) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT5 ;								
// 					wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						
// 				}
// 			break;
// 		case CLR_TOUCH:				
// 			if(has_SET_TOUCH){	
// 				
// 				DispCurAxis_q(0);
// 				has_SET_TOUCH=false ;
// 				
// 					ini_th_stopy() ;																		
// 					th = a_tbl->u.t.touch ;																	
// 					if(	th==TH1_STP	|| th==TH1_CHK ){														
// 						DISABLE_TOUCH_STOP(1)																
// 						ResetDriverClear() ;																
// 						if(chk_utouch(0,a_tbl->utouch.start,a_tbl->utouch.end) ){							
// 							if(	th==TH1_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	1 ;	
// 							DISABLE_INPORT_INT(MASK_BIT6) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT6) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[0]){													
// 								flag_ClrTouchPos[0]=true ;												
// 							}																				
// 							miss = 1 ;																		
// 						}																					
// 						MachineStatus.pass_th[0] = 0 ;														
// 						MachineStatus.chk_th[0]	 = 0 ;														
// 					}																						
// 					else if( th==TH2_STP ||	th==TH2_CHK	){													
// 						DISABLE_TOUCH_STOP(2)																
// 						ResetDriverClear() ;																
// 						if(	chk_utouch(1,a_tbl->utouch.start,a_tbl->utouch.end) ){							
// 							if(	th==TH2_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	2 ;	
// 							DISABLE_INPORT_INT(MASK_BIT7) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT7) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[1]){													
// 								flag_ClrTouchPos[1]=true ;													
// 							}																			
// 							miss = 1 ;																		
// 						}																					
// 						MachineStatus.pass_th[1] = 0 ;														
// 						MachineStatus.chk_th[1]	 = 0 ;														
// 					}																						
// 					else if( th	== TH3_STP ){																
// 						DISABLE_TOUCH_STOP(3)																
// 						ResetDriverClear() ;																
// 						if(chk_utouch(2,a_tbl->utouch.start,a_tbl->utouch.end) ){							
// 							if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 3 ;				
// 							DISABLE_INPORT_INT(MASK_BIT3) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT4) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[2]){													
// 								flag_ClrTouchPos[2]=true ;													
// 							}																				
// 							miss = 1 ;																		
// 						}																					
// 						MachineStatus.pass_th[2] = 0 ;														
// 						MachineStatus.chk_th[2]	 = 0 ;														
// 					}																						
// 					else if( th	== TH4_STP ){																
// 						DISABLE_TOUCH_STOP(4)																
// 						ResetDriverClear() ;																
// 						if(	chk_utouch(3,a_tbl->utouch.start,a_tbl->utouch.end) ){							
// 							if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 4 ;				
// 							DISABLE_INPORT_INT(MASK_BIT4) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT5) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[3]){													
// 								flag_ClrTouchPos[3]=true ;													
// 							}																				
// 							miss = 1 ;																		
// 						}																					
// 						MachineStatus.pass_th[3] = 0 ;														
// 						MachineStatus.chk_th[3]	 = 0 ;														
// 					}																						
// 					if(	!MachineStatus.miss_flag &&	miss ){													
// 						MachineStatus.miss_flag	= 1 ;														
// 						if(	MachineStatus.set_miss ){														
// 								uint8 sign=PLUS_SIGN ;													
// 							MachineStatus.cur_miss++;
// 							SendCur_miss();
// 							printf("cur_miss%d\n",MachineStatus.cur_miss);
// 							flag_DispMissNo=true ;															
// 						}																					
// 					}
// 			}		
// 			break;
// 		case LOC_PLUS_MINUS:
// 		case LOC_MINUS_PLUS :
// 		default:
// 			break ;
// 		}

// 		if((mov_dir ==PLUS_MOVE) || (mov_dir == PLUS_MINUS) ){
// 			AirTblIdx++ ;
// 		}
// 	}
// 	if((mov_dir == PLUS_MINUS) || (mov_dir == MINUS_PLUS)){
// 		AirTblIdx= sAirTblIdx ;
// 	}
}

void fill_AutoHook_axis()
{
// 	//是否有夾耳存在
// 	if(MachineStatus.motor[AXIS_Z] && CHK_HOOK(AXIS_Z)){
// 		AutoHook.byaxis= AXIS_Z ;
// 	}
// 	else if(MachineStatus.motor[AXIS_A] && CHK_HOOK(AXIS_A)){
// 		AutoHook.byaxis= AXIS_A ;
// 	}
// 	else if(MachineStatus.motor[AXIS_B] && CHK_HOOK(AXIS_B)){
// 		AutoHook.byaxis= AXIS_B ;
// 	}
// 	else if(MachineStatus.motor[AXIS_C] && CHK_HOOK(AXIS_C)){
// 		AutoHook.byaxis=AXIS_C ;
// 	}
// 	else if(MachineStatus.motor[AXIS_D] && CHK_HOOK(AXIS_D)){
// 		AutoHook.byaxis=AXIS_D ;
// 	}
// 	else if(MachineStatus.motor[AXIS_E] && CHK_HOOK(AXIS_E)){
// 		AutoHook.byaxis=AXIS_E ;
// 	}
// 	else{
// 		AutoHook.byaxis=0xff ;
// 		AutoHook.byline = 0 ;
// 	}
// 	if(AutoHook.byaxis !=0xff){
// 		AutoHook.boauto_mode=true ;
// 	}
// 	else{
// 		AutoHook.boauto_mode=false ;
// 	}
// 	printf("AutoHook=%d\n",AutoHook.byaxis);
}
