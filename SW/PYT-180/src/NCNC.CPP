#include "header.h"
//#include "chfont.h"
void GetPosition(void);
//�e�X10�骺�^���I�R�O
#define MAX_ZRT_CIR       15L
#define SPEED_FACTOR     1
#define REVERSE_GRID     (30*SPEED_FACTOR)
#define REVERSE_REF 	 (0x50*SPEED_FACTOR)

typedef struct{     
     uint32 safeabs;
	 uint32 safelkey;
	 uint32 safekey;	 
}safechk;

uint32_t Tx(UART_T* uart,unsigned char TxBuf[], uint32_t u32WriteBytes)
{
	return UART_Write(uart, TxBuf, u32WriteBytes);
}

void sendError(uint8 Cmd,int no,int len)//Cmd,�ĴX�b,�X��BYTE
{
// 	printf("Cmd=%d %d %d\n",Cmd,no,len);
// 	printf("Cur_quan=%d %x %x %x %x\n",MachineStatus.cur_quan,TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3]);
// 	uint8 TxBuf2[3];
// 	
// 	TxBuf2[0]=0x11 ;	
// 	TxBuf2[1]=Cmd ;
// 	
// 	if (len>=3)
// 		TxBuf2[2]=no ;
// 	Tx(UART2,TxBuf2,len) ;
// 	
}

void sendCmd(uint8 Cmd,uint8 buf[],int len)//Cmd,�ĴX�b,�X��BYTE
{
	uint8 TxBuf2[4];
	
	TxBuf2[0]=Cmd ;	
	
	for (int i=0;i<len;i++)
		TxBuf2[i]=buf[i] ;
	
	Tx(UART2,TxBuf2,len) ;
	
}

void HomeActive	(BYTE axis){
	
// 	EPT_IDX(axis, MachineStatus.go_home);
// 	if(	axis ==	AXIS_X ){
// 		if(	MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE) ){
// 			if(	MachineStatus.speed_mode !=	FAST )	return;
// 			else{
// 			}
// 		}
// 	}
// 	if(	MachineStatus.go_home[axis]	|| (axis==AXIS_X &&	MachineStatus.stop_machine)	){
// 		StopMotor(axis);
// 		if(CHK_ROTATE_A(axis)){
// 			StopMotor(AXIS_Y);
// 		}
// 		
// 		MachineStatus.go_home[axis]	= 0;
// 	}
// 	if((axis !=	AXIS_X)){
// 		Clr2016s(axis) ;
// 	}
}
BYTE MaskZrtMode[]= { 0x10,0x04,0x02,0x8,0x20 } ;
	void SendCmdZrt (BYTE axis, BYTE dir ,short speed_factor)
{
// 	Abs3701Pos_StartZrt[axis] = dReadAbsPos(axis);

// 	//�H10�鬰���,�p���Ƥγt�� 1��= 60*1000ms
// 	DWORD basespd= BcdToBin(4,MachineStatus.wZeroSpd[axis]) ;
// 	if(basespd == 0){
// 		basespd=1 ;
// 	}
// 	uint16 zrt_cycle = MAX_ZRT_CIR;
// 	if (MachineStatus.motor_grads[axis]<=0x1000){
// 		zrt_cycle = zrt_cycle*2;//�Y���F��Ƥ���p��,�Y�����I�����,���i�ਫMAX_ZRT_CIR(15)���٦^���F���I
// 	}
// 	DWORD MovZeroRef =(1000L*60*zrt_cycle/basespd*speed_factor)*10  ;
// 	SDWORD Mov = MachineStatus.motor_grads[axis]*zrt_cycle ;
// 	MachineStatus.dst_pos_sign[axis]	= MachineStatus.sign[axis];
// 	//MachineStatus.axis_val[axis]=0;
// 	MachineStatus.dst_pos[axis] 		= MachineStatus.axis_val[axis];
// 	if((dir&0x7f) == MINUS_SIGN){
// 		Mov = -Mov ;
// 		dir= PLUS_SIGN ;
// 	}
// 	Set3701(axis, PLUS_SIGN , MovZeroRef, Mov,Mov,true,(axis==AXIS_Y)?Mov:0,0);
// 	MachineStatus.go_home[axis] = 1;
}

bool chk_over_home(BYTE axis)
{
	SDWORD n= Off3701Pos(Abs3701Pos_StartZrt[axis],dReadAbsPos(axis)) ;
	if(n < 0){
		n=-n ;
	}
	return( n > 60 );
}
bool CHK_OVERFLOW1(uint8 phy_axis)//���A����
{	
// 	if(ChkOverFlow[phy_axis]){
// 		ChkOverFlow[phy_axis]=false;
// 		BYTE b=rDosMem(pc_base+0xf4) ;
// 		if(MachineStatus.nMotorType[phy_axis]==0){ //�s�v
// 			return(!(b & BITmask[7-phy_axis])) ;
// 		}
// 		else{
// 			return((b & BITmask[7-phy_axis])) ;
// 		}	
// 	}
// 	else{
// 		return(false) ;
// 	}
}
void AxisMDY(char axis)
{
// 	SDWORD mov=BMOTORGRID(axis)*30/3200 ;
// 	DWORD ref ;
// 	cal_zrtref(axis,ref) ;
// 	ref *=mov ;
// 	ref /= BcdToBin(MOTOR_GRADS_BCD,MachineStatus.motor_grads[axis]) ;
// 	Set3701(axis,MINUS_SIGN, ref , mov,mov,true,0,0);
// 	Wait3701(axis) ;
}
enum { 
	   ZRT_WAIT3701 , ZRT_DELAY1 , ZRT_COMPLETE,ZRT_GOAWAY_SENSOR,ZRT_WAIT_GOAWAY,
	   ZRT_DIRECT_WAIT_HOME_INT ,
	   ZRT_INDIRECT_WAIT_HOME_INT , ZRT_INDIRECT_WAIT_HOME_INT1 ,ZRT_INDIRECT_WAIT1 
	   	, ZRT_INDIRECT_WAIT0 , ZRT_INDIRECT_DELAY3 ,
	   ZRT_IMM_WAIT0,ZRT_IMM_WAIT1,ZRT_IMM_DELAY2,
	   ZRT_ROTATE_WAIT3701_1,ZRT_ROTATE_WAIT_HOME_INT_LEFT,ZRT_ROTATE_WAIT_HOME_INT_RIGHT
	   	,ZRT_ROTATE_DELAY4,ZRT_ROTATE_WAIT_RIGHT,ZRT_ROTATE_DELAY5,
	  } ;
void KeyPLUSX (void)
{	
	SendKey(otherkey);
	/*
	if(!check_setting()){
		return ;
	}
	//���b�w���}�����ռҦ��U,�ݼȮɱN�w���}�����\������
	if( MachineStatus.safe_sw == SAFE_TEST ) SetSafeSwMode(SAFE_OFF) ;
	MANMOV_AXIS(AXIS_X, PLUS_SIGN, KEY_PLUS_X, AXIS_X_REPEAT,0,0);
	if( MachineStatus.safe_sw == SAFE_TEST ) SetSafeSwMode(SAFE_TEST) ;
	*/
	MANMOV_AXIS(AXIS_X, PLUS_SIGN, KEY_PLUS_X, AXIS_X_REPEAT,0,0);
}
void KeyPLUSY (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_Y, PLUS_SIGN, KEY_PLUS_Y, AXIS_Y_REPEAT,0,0);

}
void KeyPLUSZ (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_Z, PLUS_SIGN, KEY_PLUS_Z, AXIS_Z_REPEAT,0,0);
}
void KeyPLUSA (void)
{	
// 	SendKey(otherkey);
// 	if(double_chk_is_first_a && CHK_ROTW(AXIS_A) && MachineStatus.motor[AXIS_A] && MachineStatus.ZrtMode[AXIS_A]!= MODE_ZRT_YA_ABS1){//����½�u���
// 		is_first_a=true;
// 		//SoftReset();
// 		
// 		if(NewH){
// 			AB_manual_to_zero_NewH(is_first_a) ; 	//??????u????
// 		}
// 		if(is_first_z){
// 			//Z_manual_to_zero(is_first_z) ;
// 		}
// 	}
// 	else{
// 		MANMOV_AXIS(AXIS_A, PLUS_SIGN, KEY_PLUS_A, AXIS_A_REPEAT,1,0);
// 	}
// 		MANMOV_AXIS(AXIS_A, PLUS_SIGN, KEY_PLUS_A, AXIS_A_REPEAT,1,0);
}

//-------keyPlus-------------------------------------------------------------------------
void KeyPLUSB (void)
{	
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_B, PLUS_SIGN, KEY_PLUS_B, AXIS_B_REPEAT,0,0);
}
void KeyPLUSC (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_C, PLUS_SIGN, KEY_PLUS_C, AXIS_C_REPEAT,0,0);
}
void KeyPLUSD (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_D, PLUS_SIGN, KEY_PLUS_D, AXIS_D_REPEAT,0,0);
}
void KeyPLUSE (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_E, PLUS_SIGN, KEY_PLUS_E, AXIS_E_REPEAT,0,0);
}
//-------keyPlus-------------------------------------------------------------------------


//-------keyminus-------------------------------------------------------------------------
void KeyMinusX (void)
{	
	SendKey(otherkey);
	/*
	if( MachineStatus.safe_sw == SAFE_TEST ) SetSafeSwMode(SAFE_OFF) ;
	MANMOV_AXIS(AXIS_X, MINUS_SIGN, KEY_MINUS_X, AXIS_X_REPEAT,0,0);
	if( MachineStatus.safe_sw == SAFE_TEST ) SetSafeSwMode(SAFE_TEST) ;*/
	MANMOV_AXIS(AXIS_X, MINUS_SIGN, KEY_MINUS_X, AXIS_X_REPEAT,0,0);
}

void KeyMinusY (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_Y, MINUS_SIGN, KEY_MINUS_Y, AXIS_Y_REPEAT,0,0);
}

void KeyMinusZ (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_Z, MINUS_SIGN, KEY_MINUS_Z, AXIS_Z_REPEAT,0,0);
}

void KeyMinusA (void)
{	
// 	SendKey(otherkey);
// 	if(double_chk_is_first_a && CHK_ROTW(AXIS_A) && MachineStatus.motor[AXIS_A] && MachineStatus.ZrtMode[AXIS_A]!= MODE_ZRT_YA_ABS1){//����½�u���
// 		is_first_a=true;
// 		SoftReset();
// 	}
// 	else{
// 		MANMOV_AXIS(AXIS_A, MINUS_SIGN, KEY_MINUS_A, AXIS_A_REPEAT,1,0);
// 	}
// 		MANMOV_AXIS(AXIS_A, MINUS_SIGN, KEY_MINUS_A, AXIS_A_REPEAT,1,0);
}
void KeyMinusB (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_B, MINUS_SIGN,KEY_MINUS_B,AXIS_B_REPEAT,0,0);
}

void KeyMinusC (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_C, MINUS_SIGN,KEY_MINUS_C,AXIS_C_REPEAT,0,0);
}
void KeyMinusD (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_D, MINUS_SIGN,KEY_MINUS_D,AXIS_D_REPEAT,0,0);
}
void KeyMinusE (void)
{
	SendKey(otherkey);
	MANMOV_AXIS(AXIS_E, MINUS_SIGN,KEY_MINUS_E,AXIS_E_REPEAT,0,0);
}

//-------keyminus------------------------------------------------------------------------


//-------NOSEND--------------------------------------------------------------------------
void MOTOR_SW(BYTE axis)
{	
// 		//MachineStatus.motor[axis] = (!MachineStatus.motor[axis]);
// 		//AxisLED(axis) ;
// 	
// 		if( axis < MachineStatus.axis_no ){
// 		
// 			//MachineStatus.motor[axis] = (!MachineStatus.motor[axis]);
// 			//AxisLED(axis) ;
// 				
// 			if( MachineStatus.motor[axis] ){
// 				MachineStatus.is_home[axis] = 0;
// 			}
// 			bool show = false ;
// 			if(
// 				(
// 					((axis== AXIS_Z)&& MachineStatus.motor[axis] && CHK_HOOK(AXIS_Z)) ||
// 					((axis== AXIS_A)&& MachineStatus.motor[axis] && CHK_HOOK(AXIS_A)) ||
// 					((axis== AXIS_B)&& MachineStatus.motor[axis] && CHK_HOOK(AXIS_B)) ||
// 					((axis== AXIS_C)&& MachineStatus.motor[axis] && CHK_HOOK(AXIS_C)) ||
// 					((axis== AXIS_D)&& MachineStatus.motor[axis] && CHK_HOOK(AXIS_D)) ||
// 					((axis== AXIS_E)&& MachineStatus.motor[axis] && CHK_HOOK(AXIS_E)) 
// 				) 
// 			   ){
// 				show=true ;
// 			}
// 			if(show){
// 				sendError(DispHook,0,2);	
// 			//		DispMsgWin_q(-1, -1, MSG_WIN, 	"�s\xa5\x5c��\n***���դw���}***\n�㦳�۰ʰ���\xa5\x5c��", //�\���X0xa5,0x5c(\)
// 			//						  				"New Function\n*** Hook-axis is ON ***\n can auto execution" ,
// 			//                      						"New Function\n*** Hook-axis is ON ***\n can auto execution");
// 			//		WAIT_NEW_KEY();
// 			//		ClrMsgWin_q();
// 	//
// 			}
// 	}
}

void KeyZrt (void)
{	
// 	SendKey(otherkey);
// 	for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis++){
// 		if(NewH)DDATbl[axis].new_accval=0;
// 	}
// 	/*
// 	ChkSlide=true;
// 	if( CursorLoc != PROG_CURSOR ) ChgCursorLoc(PROG_CURSOR); //�^���I�����T���]�w
// 	if(!check_setting()){
// 		return ;
// 	}
// 	SetSafeSwMode(SAFE_OFF);
// 	*/
// 	if(double_chk_is_first_a && CHK_ROTW(AXIS_A) && MachineStatus.motor[AXIS_A] && MachineStatus.ZrtMode[AXIS_A]!= MODE_ZRT_YA_ABS1){//����½�u���
// 		is_first_a=true;
// 		SoftReset();
// 	}
// 	else{
// 		MovToZeroAll(0);
// 	}
// 	//if( MachineStatus.safe_sw == SAFE_TEST )  SetSafeSwMode(SAFE_TEST);
// 		MovToZeroAll(0);
}

//-------NOSEND--------------------------------------------------------------------------------------


//-------NeedSend------------------------------------------------------------------------------------
void KeyManYScale (void)
{
	SendKey(KEY_Y_SCALE);
	
	//AxisLED(AXIS_Y) ;
	//MachineStatus.y_scale = !MachineStatus.y_scale;
	//if(MachineStatus.y_scale ){
	//		wr_rs232(4) ; wr_rs232(7) ; wr_rs232(1) ;
	//		d();
	//}
	//else if(!MachineStatus.y_scale){
	//	wr_rs232(4) ; wr_rs232(7) ; wr_rs232(0) ;
	//		d();
	//}
	
	//DispManVal_q();
	//ShowCursor();
}

void KeyMotorYSW (void)
{
	SendKey(KEY_Y_SW);
	printf("%x  %x\n",TxBuf[0],TxBuf[1]) ;
	
	//MachineStatus.y_suspend = !MachineStatus.y_suspend;
	//y_suspendLED() ;
	
	//open_config("rb+") ;
	//save_y_suspend() ;
	//close_config() ;
	//DispEditTitle_q();
	//DispActAir(0);
}
void ChgToModyMode (WORD op_mode)
{	
// 	ChkRacttbl=false;
// 	SetClock(OFF_CLOCK);
// 	
// 	MachineStatus.op_mode = op_mode;
// 	//DispModyWin_q(0);
// 	//CurProgLine = MachineStatus.last_line;
// 	//if( CurProgLine < PAGE_LINES )	YProgoff = CurProgLine;
// 	//else						YProgoff = PAGE_LINES-1;
// 	//DispPageProg_q(CurProgLine);
// 	//CurProgBuf = ProgBuf[CurProgLine];
// 	//CurProgBufExlarge=ProgBufExlarge[CurProgLine];
// 	//CursorLoc = PROG_CURSOR;
// 	//SetCursor(1);
// 	MachineStatus.prog_mody = 1;
}

void ChgToMovMode (WORD op_mode)
{	
// 	if( VerifyProg(MachineStatus.speed_mode,op_mode == RUN_MODE,0) ){
// 		MachineStatus.op_mode = op_mode;
// 		//if( op_mode == TEST_MODE )	DispTestWin_q(0);
// 		//else{	
// 		//	DispStepWin_q(0);
// 		//}

// 		//DispCurProgList_q(MachineStatus.last_line);
// 		
// 		SetClock(op_mode==TEST_MODE?TEST_CLOCK:STEP_CLOCK);
// 	}
}
void KeySuspend (void)
{
// 	SendKey(KEY_SUSPEND);
// 	Tx(UART2,TxBuf,2) ;
// 	printf("%x  %x\n",TxBuf[0],TxBuf[1]) ;
// 	
// 	if( MachineStatus.op_mode != RUN_MODE && MachineStatus.op_mode != MAN_MODE){	
// 		if(ReadAdc100() < 3){				//"�ק�{��"�ݱNADC��0�~�i�H�ϥ�
// 				if(KeyLockCHG){
// 					wr_rs232(4);wr_rs232(6);wr_rs232(1) ;
// 					d();
// 				}
// 		}
// 		else{
// 				if(KeyLockCHG){
// 					wr_rs232(4);wr_rs232(6);wr_rs232(0) ;
// 					d();
// 				}
// 		}
// 	}
// 	if(!EnableTest ){			//"�ק�{��"�ݱNADC��0�~�i�H�ϥ�
// 	//	INI_DISP_BUF();
// 	//	Fill_pDispBuf(	" ���ձ۶s�S�������s!!! ", 
// 	//					" Test Knob not at Zero ",
// 	//					" Test Knob not at Zero ");
// 	//	FILL_DISP_BUF(0);
//     //    
// 	//	DispMsgWin_q(-1, -1, WAR_WIN, DispBuf);
// 	//	FORCE_PROC_QUEUE ;
// 	//	dDelay(10);
// 	//	ClrMsgWin_q();
// 	}
// 	else {
// 			for(BYTE axis= AXIS_Z;axis < MAX_PROG_AXIS ;	axis++){
// 				virtual_zabc[axis].initial_move=0 ;
// 				virtual_zabc[axis].last_move=0 ;
// 				virtual_zabc[axis].flag= false ;
// 			}
// 		switch( MachineStatus.op_mode )
// 		{
// 		case TEST_MODE:
// 			ChgToModyMode(TMODY_MODE);
// 			break;
// 		case STEP_MODE:
// 			ChgToModyMode(SMODY_MODE);
// 			break;
// 		case TMODY_MODE:
// 			ChgToMovMode(TEST_MODE);
// 			break;
// 		case SMODY_MODE:
// 			ChgToMovMode(STEP_MODE);
// 			break;
// 		}
// 		SendStatus();
// 	}

}
void KeyMotorZSW (void)
{
	SendKey(KEY_Z_SW);
	
	//MOTOR_SW(AXIS_Z);
}
void KeyMotorASW (void)
{
	SendKey(KEY_A_SW);
	
	//MOTOR_SW(AXIS_A);
}

void KeyMotorBSW (void)
{
	SendKey(KEY_B_SW);
	
	//MOTOR_SW(AXIS_B);
}

void KeyMotorCSW (void)
{
	SendKey(KEY_C_SW);
	
	//MOTOR_SW(AXIS_C);
}

void KeyMotorDSW (void)
{
	SendKey(KEY_D_SW);
	
	//MOTOR_SW(AXIS_D);
}

void KeyMotorESW (void)
{
	SendKey(KEY_E_SW);
	
	//MOTOR_SW(AXIS_E);
}

void KeyClrY (void)//�|���g
{
// 	SendKey(otherkey);
// 	uint8 TxBuf[10];
// 	
// 	MachineStatus.sign[AXIS_Y]	   = PLUS_SIGN;
// 	MachineStatus.axis_val[AXIS_Y] = 0;
// 	MachineStatus.axis_grid[AXIS_Y] = 0;					
// 	TxBuf[0]=poscmd ;	
// 	TxBuf[1]=AXIS_Y;			
// 	//int tmp=MachineStatus.NewVal[AXIS_Y];
// 	for(int i =0;i<3;i++){
// 		//TxBuf[4-i]=tmp&0xff;
// 		//tmp>>=8;
// 		TxBuf[4-i]=0;
// 	}
// 	//printf("%x  %x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3],TxBuf[4]) ;
// 	Tx(UART2,TxBuf,5) ;
}

void KeyStep (void)
{
// 			ModeTmp=STEP_MODE;
// 	uint8 mag;
// 	mag=rDosMem(pc_base+0xc24) ; 
// 	if(mag!=0x7){
// 		if(NewH && KeyLockCHG){
// 			comm_port=0 ;	
// 			wr_rs232(4);wr_rs232(4);wr_rs232(0) ;	
// 		}
// 	
// 		if(!ChkRacttbl){
// 			for(BYTE axis= AXIS_Z;axis < MAX_PROG_AXIS ;	axis++){
// 				virtual_zabc[axis].initial_move=0 ;
// 				virtual_zabc[axis].last_move=0 ;
// 				virtual_zabc[axis].flag= false ;
// 			}
// 			FlagRun1=true ;
// 			PIdx=RIdx=0;
// 			SendKey(KEY_STEP);
// 		}
// 		else{
// 			if( MachineStatus.op_mode == RUN_MODE ){
// 				SetClock(OFF_CLOCK);
// 				WireOnOff(0);
// 				//ClrRunWin_q();
// 				//SetSafeSwMode(SAFE_OFF);
// 				//DispSafeSw_q(SAFE_OFF);
// 				MachineStatus.op_mode = STEP_MODE;
// 				//DispStepWin_q(0);
// 				SetClock(STEP_CLOCK);
// 			}
// 			else{
// 				StartRun(STEP_MODE);
// 			}
// 		}
// 	}
// 	else{
// 		//INI_DISP_BUF();	//���w�ˤ���L�k�ϥΤ���B��ܴ��ܵ���
// 		//Fill_pDispBuf(	" ����������!!! ", 
// 		//				" MPG Is Not Detected!!! ",
// 		//				" MPG Is Not Detected!!! ");
// 		//FILL_DISP_BUF(0);
//     //    
// 		//DispMsgWin_q(-1, -1, WAR_WIN, DispBuf);
// 		//FORCE_PROC_QUEUE ;
// 		
// 		sendError(NoMPG,0,2);
// 		dDelay(10);
// 		//ClrMsgWin_q();		
// 	}
}
void KeyStartRun ()
{	
// 	if(PORT_OIL0){//�Ѫo�t�ο��~run�ɷ|����O�~���O,�令���P�_�O�_�Ѫo�t�ο��~
// 		// debounce
// 		for(long l=0 ; l< DEBOUNCE_TIME; l++) ;
//     
// 		if( PORT_EX0){
// 			ChkExStop();
// 		}
// 		else if( PORT_OIL0 && !MachineStatus.OilChk){//�Ѫo�˴��Ѱ�
// 			ChkOilStop();
// 		}
// 		else if(PORT_STOPRUN&& (slide_axis==0) &&(MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE))){
// 			flagStopRun=true ;
// 		}
// 	}
// 	else{
// 		ChkSlide=true;
// 		if(NewH && KeyLockCHG){
// 			//comm_port=0;
// 			wr_rs232(4) ; wr_rs232(4) ; wr_rs232(0) ;
// 		}	
// 		for(int axis=0 ; axis <MachineStatus.axis_no ; axis++){
// 		ChkOverFlow[axis]=true;
// 		}
// 		if( MachineStatus.op_mode&(TEST_MODE+STEP_MODE) ){
// 			if( !MachineStatus.prog_mody ){
// 				SetClock(OFF_CLOCK);
// 				MachineStatus.op_mode = RUN_MODE;
// 				SendStatus();
// 				//SetSafeSwMode(MachineStatus.safe_sw);
// 				//DispSafeSw_q(MachineStatus.safe_sw);
// 				//DispWorkWin_q(0);
// 				//DispRunWin_q();
// 				if(FlagRun1){
// 					KeyStop() ;
// 				}
// 				SetClock(RUN_CLOCK);
// 			}
// 		}
// 		else{
// 			if( MachineStatus.safety_door && (PORT_SAFETY_DOOR0) ){
// 				sendError(SafeError,0,2);
// 				//DispDoorError() ;
// 				WAIT_NEW_KEY();
// 				//ClrMsgWin_q();
// 			}
// 			else{
// 					StartRun(RUN_MODE);
// 			}
// 		}
// 	}
}

void KeyStart (void)
{
		ModeTmp=RUN_MODE;
	if(!ChkRacttbl){
		for(BYTE axis= AXIS_Z;axis < MAX_PROG_AXIS ;	axis++){
			virtual_zabc[axis].initial_move=0 ;
			virtual_zabc[axis].last_move=0 ;
			virtual_zabc[axis].flag= false ;
		}
		PIdx=RIdx=0;
		SendKey(KEY_START);
	}
	else{
		if(NewH){
		//comm_port=0;
			wr_rs232(4);wr_rs232(6);wr_rs232(0) ;
		}//�ק�{���O�ץ�
		FlagRun1=false ;
		KeyStartRun() ;
	}
}
void KeyRun1 (void)
{
// 	ModeTmp=RUN_MODE;
// 	if(!ChkRacttbl){
// 		for(BYTE axis= AXIS_Z;axis < MAX_PROG_AXIS ;	axis++){
// 			virtual_zabc[axis].initial_move=0 ;
// 			virtual_zabc[axis].last_move=0 ;
// 			virtual_zabc[axis].flag= false ;
// 		}
// 		FlagRun1=true ;
// 		PIdx=RIdx=0;
// 		SendKey(KEY_RUN1);
// 	}
// 	else{
// 		//if((MachineStatus.ONE) && GetLastKey() == (KEY_RUN1)){
// 		if((MachineStatus.ONE) && FlagRun1){
// 			//FlagRun1=true ;
// 			KeyStartRun() ;
// 			FlagRun1=false ;//add
// 		}
// 	}
}
void KeyStop (void)
{
// 	SendKey(otherkey);
// 	//SendKey(KEY_STOP);
// 	
// 	safe_runtag=0;
// 	MachineStatus.stop_machine = 1;
// 	ChkRacttbl=false;
}
void KeyTest (void)
{	
// 			ModeTmp=TEST_MODE;
// 	if((MachineStatus.op_mode == MAN_MODE)&& !EnableTest&& NewH){
// 			
// 			//INI_DISP_BUF();
// 			//Fill_pDispBuf(	" ���ձ۶s�S�������s!!! ", 
// 			//				" Test Knob not at Zero ",
// 			//				" Test Knob not at Zero ");
// 			//FILL_DISP_BUF(0);
// 			//
// 			//DispMsgWin_q(-1, -1, WAR_WIN, DispBuf);
// 			//FORCE_PROC_QUEUE ;
// 			//dDelay(10);
// 			//ClrMsgWin_q();
// 			printf("ADC not Zero!!!\n");
// 			sendError(AdcNotZero,0,2);
// 		}
// 	else{
// 		if(!ChkRacttbl){
// 			for(int axis=0 ; axis <MachineStatus.axis_no ; axis++){
// 				ChkOverFlow[axis]=true;
// 			}
// 			for(BYTE axis= AXIS_Z;axis < MAX_PROG_AXIS ;	axis++){
// 				virtual_zabc[axis].initial_move=0 ;
// 				virtual_zabc[axis].last_move=0 ;
// 				virtual_zabc[axis].flag= false ;
// 			}
// 			PIdx=RIdx=0;
// 			SendKey(KEY_TEST);
// 		}
// 		else{
// 			if ( MachineStatus.op_mode == TMODY_MODE){
// 					ReMake_flag=true;
// 					MachineStatus.op_mode=ModeTmp;
// 			}
// 			else{
// 				if(NewH){
// 					//testkey=1;
// 					chk_unconnector= true ;
// 					ChkSlide=true;
// 					for(int axis=0 ; axis <MachineStatus.axis_no ; axis++){
// 							ChkOverFlow[axis]=true;
// 					}
// 				}

// 				if(NewH&&KeyLockCHG){
// 					//comm_port=0;
// 					wr_rs232(4);wr_rs232(6);wr_rs232(1) ;
// 				}
// 				if( MachineStatus.op_mode == RUN_MODE ){
// 					SetClock(OFF_CLOCK);
// 					WireOnOff(0);
// 					//ClrRunWin_q();
// 					//SetSafeSwMode(SAFE_OFF);
// 					//DispSafeSw_q(SAFE_OFF);
// 					MachineStatus.op_mode = TEST_MODE;
// 					SendStatus();
// 					//DispTestWin_q(0);
// 					SetClock(TEST_CLOCK);
// 					//FORCE_PROC_QUEUE
// 				}
// 				/*
// 				else if((MachineStatus.op_mode == MAN_MODE)&& !EnableTest&& NewH){
// 					
// 					//INI_DISP_BUF();
// 					//Fill_pDispBuf(	" ���ձ۶s�S�������s!!! ", 
// 					//				" Test Knob not at Zero ",
// 					//				" Test Knob not at Zero ");
// 					//FILL_DISP_BUF(0);
// 					//
// 					//DispMsgWin_q(-1, -1, WAR_WIN, DispBuf);
// 					//FORCE_PROC_QUEUE ;
// 					//dDelay(10);
// 					//ClrMsgWin_q();
// 					printf("ADC not Zero!!!\n");
// 				}
// 				*/
// 				else{
// 					StartRun(TEST_MODE);
// 				}
// 			}
// 		}
// 	}
}
void KeySetPara (void)
{
// 	SendKey(KEY_PARA);
// 	
// 	if( MachineStatus.op_mode == MAN_MODE ){
// 			ChkPara=1;
// 			MachineStatus.op_mode = PARA_MODE;
// 	}
// 	else{
// 		if(ChkPara==2){
// 			MachineStatus.op_mode = PARA_MODE;
// 			ChkPara=1;
// 		}
// 		else{
// 			SoftReset();
// 		}
// 	}
}
void KeySetPara_nopass (void)
{
// 	SendKey(KEY_PARA_NOPASS);
// 	
// 	if( MachineStatus.op_mode == MAN_MODE ){
// 			ChkPara=2;
// 			MachineStatus.op_mode = PARA_MODE;
// 	}
// 	else{
// 		if(ChkPara==1){
// 			MachineStatus.op_mode = PARA_MODE;
// 			ChkPara=2;
// 		}
// 		else
// 			SoftReset();
// 	}
}

void KeyHelp (void)
{
		int t1=260 , t2 =15 ;
		wr_rs232(0) ; wr_rs232(t1) ; wr_rs232(t1>>8) ;
		dDelay(3) ;
		wr_rs232(1) ; wr_rs232(t2) ; wr_rs232(t2>>8) ;
		dDelay(3) ;
		int t3=260 , t4=15*3 ;
		wr_rs232(2) ; wr_rs232(t3) ; wr_rs232(t3>>8) ;
		dDelay(3) ;
		wr_rs232(3) ; wr_rs232(t4) ; wr_rs232(t4>>8) ;
		dDelay(3) ;
	SendKey(KEY_HELP);
	//GetPosition();
}
void KeyPgUp (void)
{
	SendKey(KEY_PG_UP);
}
void KeyPgDown (void)
{
	SendKey(KEY_PG_DOWN);
}
void KeyChgCursor (void)
{
	SendKey(KEY_CHG_CURSOR);
}
void KeyUp (void)
{
	SendKey(KEY_UP);
}
void KeyDown (void)
{
	SendKey(KEY_DOWN);
}
void KeyLeft (void)
{
	SendKey(KEY_LEFT);
}

void KeyRight (void)
{
	SendKey(KEY_RIGHT);
}
void KeyNum0 (void)
{
	SendKey(KEY_0);
}
void KeyNum1 (void)
{
	SendKey(KEY_1);
}
void KeyNum2 (void)
{
	SendKey(KEY_2);
}
void KeyNum3 (void)
{
	SendKey(KEY_3);
}
void KeyNum4 (void)
{
	SendKey(KEY_4);
}
void KeyNum5 (void)
{
	SendKey(KEY_5);
}
void KeyNum6 (void)
{
	SendKey(KEY_6);
}
void KeyNum7 (void)
{
	SendKey(KEY_7);
}
void KeyNum8 (void)
{
	SendKey(KEY_8);
}
void KeyNum9 (void)
{
	SendKey(KEY_9);
}
void KeySign (void)
{
	SendKey(KEY_SIGN);
}
void KeySpaceBar (void)
{
	SendKey(KEY_SPACE_BAR);
}
void KeySpecial (void)
{
	//SendKey(KEY_SPECIAL);
}
void KeyG0 (void)
{
	SendKey(KEY_G0);
}
void KeySPD (void)
{
	SendKey(KEY_SPD);
}
void KeySetT (void)
{
	SendKey(KEY_T);
}
void KeyIns (void)
{
	SendKey(KEY_INS);
}
void KeyWr (void)
{
	SendKey(KEY_WR);
}
void KeyJmpnn (void)
{
	SendKey(KEY_JMPNN);
}
void KeyTDelay (void)
{
	SendKey(KEY_T_DELAY);
}
void KeySetAir (void)
{
	SendKey(KEY_AIR);
}
void KeyCan (void)
{
	SendKey(KEY_CAN);
}
void Key_Marker (void)
{
	SendKey(KEY_MARKER);
}
void KeyAirScrn (void)
{
	SendKey(KEY_AIRSCRN);
}
void KeyCutter (void)
{
	SendKey(KEY_CUTTER);
}
void KeyStartDegree (void)
{
	SendKey(KEY_START_DEGREE);
}
void KeyEndDegree (void)
{
	SendKey(KEY_END_DEGREE);
}
void KeySafe (void)
{
	SendKey(KEY_SAFE);
}
void KeyCopyFile (void)
{
	SendKey(KEY_COPY_FILE);
}
void KeyLoadFile (void)
{
	SendKey(KEY_LOAD_FILE);
}
void KeySaveFile (void)
{
	SendKey(KEY_SAVE_FILE);
}
void KeySetProdno (void)
{
	SendKey(KEY_SETPRODNO);
}
void KeyProdno0 (void)
{
	SendKey(KEY_PRODNO0);
}
void KeySetSpeedMode (void)
{
	SendKey(KEY_SPEED_MODE);
}
void KeyReturn (void)
{
	SendKey(KEY_RETURN);
}
void KeyNext (void)
{
	SendKey(KEY_NEXT);
}
void KeyMytest (void)
{
	//printf("MyTestKey");
	////MachineStatus.TIMER=1;
	//uint8 TxBuf[3];
//
	//MachineStatus.cur_miss++;
	//int tmp=MachineStatus.cur_miss;
	//
	//TxBuf[0]=curmiss ;	
	////TxBuf[1]=Cmd_Curmiss ;	
	//for(int i =0;i<2;i++){
	//	TxBuf[2-i]=tmp&0xff;
	//	tmp>>=8;
	//}
	//printf("%d %x %x %x\n",MachineStatus.cur_quan,TxBuf[0],TxBuf[1],TxBuf[2]);
	//Tx(UART2,TxBuf,3) ;
	////printf("cur_miss=%d\n",MachineStatus.cur_miss);
	//
	//
	//uint8 TxBuf2[4];
	//
	//MachineStatus.cur_quan+=2;
	//tmp=MachineStatus.cur_quan;
	//
	//TxBuf2[0]=Cmd_Touch1 ;	
	////TxBuf2[1]=Cmd_Curquan ;	
	//for(int i =0;i<3;i++){
	//	TxBuf2[3-i]=tmp&0xff;
	//	tmp>>=8;
	//}
	//printf("%x %x %x %x\n",TxBuf2[0],TxBuf2[1],TxBuf2[2],TxBuf2[3]);
	//Tx(UART2,TxBuf2,4) ;
	////printf("cur_quan=%d\n",MachineStatus.cur_quan);
	
	
}
void SendKey (BYTE keycode)
{
	uint8 TxBuf[2];
	TxBuf[0]=0x55 ;
	TxBuf[1]=keycode;
	Tx(UART2,TxBuf,2) ;
}
void SendStatus ()
{
// 	uint8 TxBuf[3];
// 	TxBuf[0]=Cmd_Status ;	
// 	uint16 tmp=MachineStatus.op_mode ;	
// 	//TxBuf[1]=MachineStatus.op_mode ;	
// 	for(int i =0;i<2;i++){
// 		TxBuf[2-i]=tmp&0xff;
// 		tmp>>=8;
// 	}
// 	printf("status=%d %x %x %x\n",MachineStatus.op_mode,TxBuf[0],TxBuf[1],TxBuf[2]);
// 	Tx(UART2,TxBuf,3) ;
}
void SendCur_miss (void)
{
// 	printf("Cur_miss=");
// 	uint8 TxBuf[3];

// 	int tmp=MachineStatus.cur_miss;
// 	
// 	TxBuf[0]=curmiss ;	
// 	for(int i =0;i<2;i++){
// 		TxBuf[2-i]=tmp&0xff;
// 		tmp>>=8;
// 	}
// 	printf("%d %x %x %x\n",MachineStatus.cur_miss,TxBuf[0],TxBuf[1],TxBuf[2]);
// 	Tx(UART2,TxBuf,3) ;
}
void SendErrorCode ()
{
// 	printf("Cur_miss=");
// 	uint8 TxBuf[3];

// 	int tmp=MachineStatus.cur_miss;
// 	
// 	TxBuf[0]=curmiss ;	
// 	for(int i =0;i<2;i++){
// 		TxBuf[2-i]=tmp&0xff;
// 		tmp>>=8;
// 	}
// 	printf("%d %x %x %x\n",MachineStatus.cur_miss,TxBuf[0],TxBuf[1],TxBuf[2]);
// 	Tx(UART2,TxBuf,3) ;
}
//-------NeedSend------------------------------------------------------------------------------------

uint8 GetLastKey	(void)
{
	uint16 i,	tidx;

	//tidx = KeyBufRIdx;
	tidx = WriteId;
	for( i=0; i	< 2; i++ ){
		if(	tidx ==	0 )	 tidx =	MAX_KEY_BUF-1;
		else			 tidx--;
	}
	//return(	KeyBuf[tidx] );
	return(CmdBuf[tidx]);
}
uint8 GetNextKey	(void)
{
	if(	KeyBufRIdx != KeyBufWIdx ){
		return(	KeyBuf[KeyBufRIdx] );
	}
	else{
		return(	0 );
	}
}

uint8 ClrKeyBuf (void)
{
	uint16 i;
	uint8  code ;

//	if(bioskey(1)) code=bioskey(0) ;
		
	for( i=0; (i<MAX_KEY_BUF) && (KeyBufRIdx!=KeyBufWIdx)&&(KeyBuf[KeyBufRIdx]!=0xfe); i++ )  code=GetKey();


	return(code) ;
}
void ResetKeyBuf (uint8 key)
{
	//DISABLE();
	KeyBufRIdx = 0;
	KeyBufWIdx = 1;
	KeyBuf[0]  = key;
	//ENABLE();
}
	static struct TIMER  lTimerTicks;
	#define Step_timer 200
void Step_operation(void){
	
	switch(STEP_DDAState){
		
		case 1:
			//if(TimerTicks.timer-lTimerTicks.timer>=(Step_timer * NOCNT_1MS)){
			if(TimerTicks.timer-lTimerTicks.timer>=(Step_timer)){
				if(KeyBufWIdx !=KeyBufRIdx){
						//�ˬd�̫�@�ӫ���O�_�M�ثe��ʫ���@��
						uint16 tKeyBufWIdx ;
						if(KeyBufWIdx !=0){
							tKeyBufWIdx=KeyBufWIdx-1 ;
						}
						else{
							tKeyBufWIdx=MAX_KEY_BUF-1 ;
						}
						if((KeyBuf[tKeyBufWIdx] == prokeycode)){ //�̫�@�ӫ���O�_�M�ثe��ʫ���@�˥Bidx_Table����2
							KeyBufRIdx=KeyBufWIdx ; //�M��keybuf
							lTimerTicks.timer=TimerTicks.timer;		
						}

				}
				else {
					STEP_DDAState=0;
				}
			}
			break;
	}
}
void KeyHandRight (void)
{	
// 	HandQlen=rDosMemw(pc_base+0x020) ; 

// 	if(GetLastKey() == KEY_HAND_LEFT)return ; //�L�o��,�����}�ɪ��ϼu(�k���ܥ���)

// 	WORD  j;
// 	DWORD i;
// 	BYTE man_gain=BcdToBin(5,MachineStatus.man_gain) ;
// 	if(MachineStatus.op_mode&STEP_MODE ){
// 		if(NewH){
// 			lTimerTicks.timer=TimerTicks.timer;
// 			STEP_DDAState=1;
// 		}
// 	}
// 	else{
// 		if( MachineStatus.hand_sel != 0xff ){
// 			uint8 laxis	= MachineStatus.hand_sel ;
// 			uint8 dir		= PLUS_SIGN ;
// 			MANMOV_AXIS(MachineStatus.hand_sel, PLUS_SIGN, 0, 0,0,1);
// 		}
// 		else{
// 			ClrKeyBuf();
// 		}
// 	}
}
void KeyHandLeft (void)
{	

// 	if(GetLastKey() == KEY_HAND_RIGHT)return ; //�L�o��,�����}�ɪ��ϼu(�k���ܥ���)
// 	if( MachineStatus.op_mode&STEP_MODE ){
// 	}
// 	else{
// 		if( MachineStatus.hand_sel != 0xff ){
// 			uint8 laxis	= MachineStatus.hand_sel ;
// 			uint8 dir 	= MINUS_SIGN ;
// 			MANMOV_AXIS(MachineStatus.hand_sel, MINUS_SIGN, 0, 0,0,1);
// 		}
// 		ClrKeyBuf();
// 	}
}
void KeyProcMap (void)
{
	BYTE key;
	WORD i;
	uint8 TxBuf[2];
//	SerialCom Com2;
	//printf("1_%d %d\n",KeyBufRIdx , KeyBufWIdx);
	prokeycode = key = GetKey();
	//printf("2_%d %d\n",KeyBufRIdx , KeyBufWIdx);


// 	for( i=0; ; i++ ){
// 		if( (key==KeyMapTbl[i].key) || (KeyMapTbl[i].key==0) ){
// 			if( KeyMapTbl[i].avail_mode&MachineStatus.op_mode ){
// 				if(((USB != ' ') &&(KeyMapTbl[i].avail_mode&USB_MODE)) || USB == ' ' || ((MachineStatus.UsbDisk !=1)&& (MachineStatus.UsbDisk !=9))){
// 					KeyMapTbl[i].proc();
// 					if(!key_flg){
// 						mDelay(300) ;
// 						key_flg=true ;
// 					}
// 				}
// 				//else{
// 				//	Disp_USB_WARN() ;
// 				//}
// 			}
// 			break;
// 		}
// 	}
		
//}
}

void chk_off_power(BYTE loc)
{
// 	//static bool flag_off_power=false ;
// 	static struct TIMER timeout_off_power ;
// 	if(flag_off_power){	
// 		if(IsTimeUp(timeout_off_power)){
// 			timeout_off_power= mTimerSet(500);
// 			if( ((rDosMem(pc_base+INH) & 0x01) != off_power)){
// 				dDelay(1) ;
// 				if(((rDosMem(pc_base+INH) & 0x01) != off_power)){
// 					// ready to  off power 
// 					flag_run=flag_off_power=false ;
// 					ready_PowerOff(loc) ;
// 				}
// 			}
// 		}
// 	}
// 	else if(MachineStatus.TIMER!=0)
// 		ready_PowerOff(loc) ;
// 	/*
// 	else{
// 		//setting sample interval
// 		timeout_off_power= mTimerSet(500);
// 		flag_off_power=true ;
// 	} 
// 	*/
	
}
void ready_PowerOff(BYTE loc)
{
	//ClrMsgWin_q();
	//DispMsgWin_q(-1, -1, MSG_WIN, ReadyPoweroff[1], ReadyPoweroff[0], ReadyPoweroff[2]);
	//FORCE_PROC_QUEUE ;
	//SaveBackupFile((WORD)BcdToBin(3,MachineStatus.file)) ;
	//save_config_backup() ;
	for(unsigned long l=0 ; l < 0x1234567L ; l++) ;
	StopMotor();
	//close_record() ; // v1.30�ק�	
	//svprodnoDisk() ;// �x�s�ثe���Ͳ��q
	//if( CHK_ROTATE_A(AXIS_A) && (MachineStatus.Type== TYPE_650_850)&& (loc !=0) && MachineStatus.AHome && MachineStatus.motor[AXIS_A]){ //��������
	//	AXISA_to_home() ;
	//}
	PowerOff() ;
	
}
void PowerOff()
{
	//if(!NewH){
	//	Server_onoff(0) ; 				  //NewH servo off
	//}
	//else{
		wDosMem(pc_base+0x0F3,(uint8)0xff);//SOL servo off
	//}
	for(unsigned long l=0 ; l < 0x4234567L ; l++) ;
	BOUTM |= MASK_BIT3;
	wDosMem(pc_base+OUTM , BOUTM) ;
	BOUTM &= BNY(0,0,0,1, 1,1,1,1);
	//ClrMsgWin_q();
	//SystemOff();
}

void WAIT_NEW_KEY_SAME(void)
{
	//FORCE_PROC_QUEUE
	//ClrKeyBuf();
	//while( (KeyBufRIdx == KeyBufWIdx) && (bioskey(1)==0) && (ERP_BufRIdx==ERP_BufWIdx)){
	while( (KeyBufRIdx == KeyBufWIdx) && (ERP_BufRIdx==ERP_BufWIdx)){
		always_update() ;
	}
	//set_ScrnSav() ;
	timeout_flash= dTimerSet(TIMER_FLASH) ;
}
void WAIT_NEW_KEY(void)
{
	WAIT_NEW_KEY_SAME() ;
	ClrKeyBuf();
}

void WAIT_NEW_KEY(char &code)
{
	WAIT_NEW_KEY_SAME()	;
	code= ClrKeyBuf();
}
void ChkCN1Stop(BYTE mask , BYTE errorCode , bool chk_normal)
{
// 	if((!((PORT_CN1) & mask)) ){
// 		if(MachineStatus.AirOff)//�T���Ѱ�
// 			wDosMem(pc_base+OUTL, (uint8)0) ;
// 		if( MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE) ){
// 			PauseClock(MachineStatus.op_mode);
// 			//FORCE_PROC_QUEUE ;

// 			sendError(errorCode,0,2);
// 			//DispMsgWin_q(-1, -1, ERR_WIN, Err_str[1],
// 			// 							  Err_str[0],
//       //                                    Err_str[0]);
// 			//FORCE_PROC_QUEUE
// 			if(MachineStatus.op_mode == RUN_MODE){
// 				WARN_LIGHT_OFF_RED
// 			}
// 			do{				//�u�[���`��debounce�ư�
// 				while(!(PORT_CN1 & mask)){CHECK_RESET_update(false);}
// 				for(int i=0;i<=10;i++)	for(long l=0 ; l< DEBOUNCE_TIME; l++) ;
// 			}while(!(PORT_CN1 & mask));
// 			
// 			WAIT_RUN_TEST_KEY(MSG_WIN,errorCode);
// 			//ClrMsgWin_q();

// 			RestoreClock(KeyTmp);
// 		}
// 		else{
// 			if(!chk_normal)return ;
// 			
// 			StopMotor();
// 			sendError(errorCode,0,2);
// 			//DispErrWin_q(Err_str) ;
// 			while( !(PORT_CN1 & mask)){CHECK_RESET_update(false);}
// 			ClrKeyBuf();
// 			//ClrMsgWin_q();
// 			if(NewH)ResetDriverClear();
// 		}
// 	}
}
void DispSlideError ()
{
// 	printf("SlideError\n");
// 	PauseClock(MachineStatus.op_mode);//���~���R�����������ܽ
// 	sendError(OverLimite,0,2);
// 	//FILL_DISP_BUF(0);
// 	//DispMsgWin_q(-1, -1, ERR_WIN, 	" �W �L ���A�Ʈy �� �� �� �� !\n\n ���m��---------�^��s��e��",
// 	//							  	" Over SLide Limit Failure !\n\n RESET------Return To Edit Screen" ,
//   //                        			" Over SLide Limit Failure !\n\n RESET------Return To Edit Screen"
//   //                        );
// 	//FORCE_PROC_QUEUE
// 	//ClrKeyBuf();
// 	WARN_LIGHT_OFF_RED 
// 	while( 1 ){
// 		if( KeyBufRIdx != KeyBufWIdx ){
// 			if(set_ScrnSav()){
// 				continue ;
// 			}
// 			KeyTmp = GetKey();
// 			if(Reset){
// 				SoftReset() ;
// 			}
// 		}
// 		else{
// 			always_update() ;
// 		}
// 	}
}

void DispServoCutterError ()
{	
// 	printf("ServoCutterError\n");
// 	PauseClock(MachineStatus.op_mode);//���~���R������������
// 	sendError(CutError,0,2);
// 			
// 	//FILL_DISP_BUF(0);
// 	//DispMsgWin_q(-1, -1, ERR_WIN, 	"   ��  �A  ��  �M   ��  ��  !\n\n ���m��---------�^��s��e��",
// 	//							  	" Servo Cutter Axis Failure !\n\n RESET------Return To Edit Screen" ,
//   //                        			" Servo Cutter Axis Failure !\n\n RESET------Return To Edit Screen"
//   //                        );
// 	//FORCE_PROC_QUEUE
// 	//ClrKeyBuf();
// 	WARN_LIGHT_OFF_RED 
// 	while( 1 ){
// 		if( KeyBufRIdx != KeyBufWIdx ){
// 			if(set_ScrnSav()){
// 				continue ;
// 			}
// 			KeyTmp = GetKey();
// 			if(Reset){
// 				SoftReset() ;
// 			}
// 		}
// 		else{
// 			always_update() ;
// 		}
// 	}
}
void DispExtEncoderError()
{
	printf("ExtEncoderError\n");
	StopMotor() ;
	ToManProc() ;
	//DispMsgWin_q(-1, -1, ERR_WIN, 	" �~ �� �� �X �� �� �~ ...",
	//							  	" External Encoder Error ..."  ,
  //                        			" External Encoder Error ..."
  //                        );
	sendError(EncoderError,0,2);
	WAIT_NEW_KEY();
	//ClrMsgWin_q();
}
void DispMotorUnconnectError (short axis)
{
// 	printf("MotorUnconnectError axis=%d\n",axis);
// 	sendError(Unconnect,axis,3);
// 	//INI_DISP_BUF();	//���w�ˤ���L�k�ϥΤ���B��ܴ��ܵ���
// 	PauseClock(MachineStatus.op_mode);
// 	//Fill_pDispBuf(AxisName[idx_language][axis]);		
// 	//Fill_pDispBuf(MotorLineError[idx_language]);		
// 	//Fill_pDispBuf(ErrorReset[idx_language]);	
// 	//FILL_DISP_BUF(0);
// 	//DispMsgWin_q(-1, -1, ERR_WIN, DispBuf);
// 	//FORCE_PROC_QUEUE
// 	ClrKeyBuf();
// 	WARN_LIGHT_OFF_RED 
// 	while( 1 ){
// 		if( KeyBufRIdx != KeyBufWIdx ){
// 			if(set_ScrnSav()){
// 				continue ;
// 			}
// 			KeyTmp = GetKey();
// 			if(Reset){
// 				SoftReset() ;
// 			}
// 		}
// 		else{
// 			always_update() ;
// 		}
// 	}
// 	StopMotor() ;
// 	ToManProc() ;
// 	//INI_DISP_BUF();
// 	//Fill_pDispBuf(AxisName[idx_language][axis]);
// 	//Fill_pDispBuf(MotorLineError[idx_language]);
// 	//FILL_DISP_BUF(0);
// 	//DispMsgWin_q(-1, -1, ERR_WIN, DispBuf);
// 	//WAIT_NEW_KEY();
// 	//ClrMsgWin_q();
// 	//FileRWErr = 0;
}


void DispServoFailure(int8 axis)
{
// 	printf("ServoFailure\n");
// 	//INI_DISP_BUF();	
// 	PauseClock(MachineStatus.op_mode);//���~���R������������
// 	sendError(ServoError,axis,3);
// 	//Fill_pDispBuf(AxisName[idx_language][axis]);		
// 	//Fill_pDispBuf(" �� �A �� �� !", 
// 	//			  " Servo Failure !",
// 	//			  " Servo Failure !");		
// 	//Fill_pDispBuf(ErrorReset[idx_language]);	
// 	//FILL_DISP_BUF(0);
// 	//DispMsgWin_q(-1, -1, ERR_WIN, DispBuf);
// 	//FORCE_PROC_QUEUE
// 	ClrKeyBuf();
// 	WARN_LIGHT_OFF_RED 
// 	while( 1 ){
// 		if( KeyBufRIdx != KeyBufWIdx ){
// 			//if(set_ScrnSav()){
// 			//	continue ;
// 			//}
// 			KeyTmp = GetKey();
// 			if(Reset){
// 				SoftReset() ;
// 			}
// 		}
// 		else{
// 			always_update() ;
// 		}
// 	}
}
void ChkOverFlowStop (void)
{
// 	BYTE axis,  t;
// 	
// 	for( axis=0; axis < MachineStatus.axis_no; axis++ ){

// #if 1
// 		t=0 ;
// #else
// 		if( axis == AXIS_Y )
// 		  	t = !((*(pc_base+P8255_1+PORTB_8255))&(MASK_BIT0));
// 		else if( axis == AXIS_Z )
// 			t = !((*(pc_base+P8255_1+PORTB_8255))&(MASK_BIT1));
// 		else
// 			t = 0;
// #endif
// 		if(MachineStatus.motor[axis] &&( CHK_OVERFLOW1(axis) || t ) ){
// 			StopMotor();
// 			ToManProc();
// 			
// 			DispServoFailure(axis) ;
// 			
// 			for(long l=0 ; l < DEBOUNCE_TIME ; l++) ;
// 			while( !((rDosMem(pc_base+P8255_1+PORTB_8255))&(MASK_BIT0)) ){CHECK_RESET_update(false);}
// 			while( !((rDosMem(pc_base+P8255_1+PORTB_8255))&(MASK_BIT1)) ){CHECK_RESET_update(false);}
// 			WAIT_NEW_KEY();
// 			//ClrMsgWin_q();
// 			return;
// 		}
// 	}
}

char *OilErr_str[]= {" Oil System Failure "," �� �o �t �� �� �~ " ," PROBLEMA SISTEMA OLIO "} ;                     
char *ExErr_str[]={" Ext. Device Failure ",  " �u �[ �] �� �� �~ " ," PROBLEMA SISTEMA ESTERNO "} ;
char *DoorErr_str[]={" Door Error ", " �w �� �� �� �~ " ," Door Error "};

void ChkExStop (void)
{ 
	printf("ChkExStop\n");
	ChkCN1Stop(MASK_BIT5,ExtError,true) ;
}

void ChkOilStop (void)
{
	printf("ChkExStop\n");
	ChkCN1Stop(MASK_BIT0,OilError,true) ;
}

void ChkDoorStop (void)
{
	printf("ChkDoorStop\n");
	ChkCN1Stop(MASK_BIT2,SafeError,false) ;
}
static safechk safe_buf[50],safe_errorbuf[50];
static safechk safe_chk[50],safe_chk_1[50],safe_chk_2[50],safe_chk_3[50],safe_chk_4[50],safe_chk_5[50],safe_chk_6[50],safe_chk_7[50],safe_chk_8[50];
static int Safe_dumpKey=0,Safe_onKey=0;
static SDWORD chk_move;
static DWORD chk_MovZeroRef;
static uint32 lpos=0;
static	uint8	lKeySafe=0,chk_safe=0;
void SAFE_TEST_new(){
	uint8 KeySafe=rDosMem(pc_base+INE);
	if(KeySafe!=lKeySafe){//�w���˸m���խק�
		switch(KeySafe^lKeySafe){
			case 0x1:
			ShowSafeTest(1);
			break;
			case 0x2:
			ShowSafeTest(2);
			break;
			case 0x4:
			ShowSafeTest(3);
			break;
			case 0x8:
			ShowSafeTest(4);
			break;
			case 0x10:
			ShowSafeTest(5);
			break;
			case 0x20:
			ShowSafeTest(6);
			break;
			case 0x40:
			ShowSafeTest(7);
			break;
			case 0x80:
			ShowSafeTest(8);
			break;
			default:
			break;
		}
		lKeySafe=KeySafe;
	}
}

SDWORD ReadReg3701 (BYTE axis, BYTE	reg)
{
// 	SDWORD t, n	;
// 	SDWORD d;
// 	static int lfeedY=0;
// 	static int a=1;
// 	switch(	reg	)
// 	{
// 	case RD_VREG_3701:    //�`�@�n���ʪ����
// 		d =	Set3701Val[axis];
// 		break;
// 	case RD_YREG_3701:    //�ѤU�S�����ʪ����
// 		if((axis <=	AXIS_E)){
// 			t=Off3701Pos(Abs3701Pos[axis],n=dReadAbsPos(axis)) ;
// 			
// 			if((axis== AXIS_Y) && (MachineStatus.Type == TYPE_650_850)){
// 				t=-t ;
// 			}
// 			Abs3701Pos[axis] = n; //�O���ثe2016��m
// 			//�ˬdX�b�O�_���g�L���I(3996,3997,3998,3999,4000-->0,1,2)�N�Ϯt�Ȥ���,�ݭ׾�
// 			
// 			//if((axis == AXIS_X) && (t < -1000))Sprintf("%d",t);
// 			//if((axis == AXIS_X) && (t < -1000)&&Set3701Val[axis]>0){
// 			if((axis == AXIS_X) && (t < -1000)){
// 				t += BMOTORGRID_X ;
// 			}
// 			Mov3701Val[axis] +=	t;
// 			if((axis == AXIS_X)&&Mov3701Val[axis]>500&&Set3701Val[axis]<0 && t<0){	//�ϦV�L���I�ഫ
// 				Mov3701Val[axis]-=BMOTORGRID_X;
// 			}			

// 			SDWORD nMov3701Val=sdmdy_2016(axis,Mov3701Val[axis]);			
// 			//if(axis==AXIS_X)printf("1___%d--%d--%d\n",Set3701Val[axis],nMov3701Val,Mov3701Val[axis]);


// 			if(CHK_ROTW(AXIS_A) && (axis == AXIS_Y)){
// 				nMov3701Val= ExtGrid2_Grid(nMov3701Val) ;
// 				if(MachineStatus.Type == TYPE_650_850)nMov3701Val=-nMov3701Val;//650���w�ɰe�u���t(�A����)
// 			}
// 			else if((axis == AXIS_Y) && CHK_ROTW(AXIS_A) && MachineStatus.motor[AXIS_A]&& MachineStatus.running[AXIS_A]){
// 				//������u�ʧ@��,Y�b�����ʪ���m����u�ӱ���
// 				Mov3701Val[axis]= (Set3701Val[axis]*sdmdy_2016(AXIS_A,Mov3701Val[AXIS_A]))/Set3701Val[AXIS_A] ;
// 				nMov3701Val=sdmdy_2016(axis,Mov3701Val[axis]);
// 			}
// 			if(NewH && (axis!=AXIS_Y ||(axis==AXIS_Y && !chk_run_touch))){
// 				nMov3701Val=DDATbl[axis].new_accval; //���w�e�u�ȧ�^��
// 			}
// 			if(NewH && (axis==AXIS_Y && chk_run_touch)){//635�|���T�{	//TouchWire���w�ɧ�e�u��k	 //���w��s��k�B�ץ�
// 				int dif=dReadAbsPos (axis)-lfeedY;
// 				if(CHK_ROTW(AXIS_A)){
// 					if(MachineStatus.Type == TYPE_635_835 ||MachineStatus.Type == TYPE_1635_1835)
// 						nMov3701Val=(dif*0.9434425);	//635�e�u�ȭק�(�ϥ�)
// 					else if(MachineStatus.Type == TYPE_650_850)
// 						nMov3701Val=(dif*5.47);
// 					else if(MachineStatus.Type == TYPE_620_820){
// 						nMov3701Val=dif*9.6;
// 					}
// 				}
// 				else
// 					nMov3701Val=dif;
// 			}
// 			else if(NewH &&!chk_run_touch)
// 				lfeedY=dReadAbsPos (AXIS_Y);
// 			
// 			d =	Set3701Val[axis] - nMov3701Val;
// 			if(Set3701Val[axis]	>= 0){
// 				if((nMov3701Val < -2)){
// 					d=Set3701Val[axis] ; 
// 				}
// 				else if(nMov3701Val > Set3701Val[axis]){
// 					d=0	;
// 				}
// 			}
// 			else{
// 				if((nMov3701Val > 2)){
// 					d= Set3701Val[axis] ;
// 				}
// 				else if(Set3701Val[axis] >	nMov3701Val){
// 					d=0	;
// 				}
// 			}
// 		}
// 		break;
// 	default:
// 		d =	0;
// 		break;
// 	}
// 	if((axis == AXIS_Y)&& CHK_ROTW1(AXIS_A) &&(Set3701Val[axis] > EXT_ENCODER_MDY_VAL)){
// 		d += EXT_ENCODER_MDY_VAL ;
// 	}
// 	Grid2Unit(axis,d) ;
// 	return(	d );
}
void reverse_mov_ZRT(BYTE axis,uint32 mov)
{
// 	uint32 grid= mov;
// 	uint32 ref=grid ;
// 	//if(MachineStatus.home_seq_sign[axis]== PLUS_SIGN)
// 	//	MachineStatus.NewVal[axis]-=grid;
// 	//else
// 	//	MachineStatus.NewVal[axis]+=mov;
// 	//	printf("%d\n",MachineStatus.NewVal[axis]);
// 	Set3701(axis,(MachineStatus.home_seq_sign[axis]== PLUS_SIGN)? MINUS_SIGN : PLUS_SIGN ,ref , grid,grid,true,0,0);
}

void RRealAxis(void)
{
// 	SDWORD	tval;
// 	for(uint8 axis=0 ; axis < MachineStatus.axis_no ; axis++){
// 		tval=sdmdy_2016(axis,dReadAbsPos (axis)) ;
// 		MachineStatus.axis_val[axis]= tval ;
// 	//DispCurAxis_q(1) ;
// 		//machinestatus.sign[axis]=plus_sign ;
// 	}	
// 	if(flag_RRealAxis&&(MachineStatus.op_mode&(MAN_MODE))){
// 		if(IsTimeUp(timeout_DispCurAxis) ){
// 			DispCurAxis_q(0);
// 			timeout_DispCurAxis= mTimerSet(MAX_DispCurAxis);
// 		}
// 	}
// 	//DispCurAxis_q(0) ;
}

void  DispGoHomeFailure(int8 axis)
{
	printf("GoHomeFailure\n");
	sendError(HomeError,axis+1,3);
	/*
	INI_DISP_BUF();
	Fill_pDispBuf( AxisName[idx_language][axis]);
	Fill_pDispBuf(	" �^ �� �I �� �� !",
				  	" Go Home Failure !",
				  	" Go Home Failure !");
	FILL_DISP_BUF(0);
	DispMsgWin_q(-1, -1, ERR_WIN, DispBuf);
	*/
}
short MovToZeroAll (short force)
{				
// 	flag_RRealAxis=false;
// 	uint8 TxBuf[10];
// 	//�騤���Y���b���I,�ݤ�ʦ^���I
// 	//if(Chk_Angle() && !MachineStatus.is_home[AXIS_Z]){
// 	//	Z_manual_to_zero(is_first_z) ;
// 	//}	
// 	
// 	
// 	if(flag_IMMZrtTest==true){ //5218
// 		flag_IMMZrtTest=false;
// 		for(int i=0; i<7; i++){
// 			DisableHomeInt(i);
// 		}
// 	}
// 	
// 	
// 	BYTE is_home[MAX_AXIS] ;
// 	if(!flagSPIN_ZRT){	
// 		sendError(GoHome,1,3);
// 		dDelay(3) ;
// 	//	ShowToHome() ;
// 	}
// 	in_movToZeroAll=true ;
// 	
// 		//��gseq�}�C
// 	//��home_seq�]�w�@�ˮ�,���\�h�b�P�ɦ^���I
// 	BYTE  axis, i, j, seq[MAX_AXIS][MAX_AXIS];
// 	// 	seq[0][0],seq[0][1],seq[0][2]....�Y�D�ƭ�0xff,�N���Ĥ@���^���I���b
// 	// 	seq[1][0],seq[1][1],seq[1][2]....�Y�D�ƭ�0xff,�N���ĤG���^���I���b
// 	// 	seq[2][0],seq[2][1],seq[2][2]....�Y�D�ƭ�0xff,�N���ĤT���^���I���b
// 	//	...	
// 	bool flag =false ;
// 	for( i=0; i < MAX_AXIS; i++ ){
// 		for( axis=0; axis < MAX_AXIS; axis++ ) seq[i][axis] = 0xff;
// 		j = 0;
// 		for( axis=0; axis < MachineStatus.axis_no; axis++ ){
// 			if( axis != AXIS_Y ){
// 				if( MachineStatus.home_seq[axis] == i ){
// 					if( force ){
// 						if(flagSPIN_ZRT){
// 							if((MachineStatus.is_home[axis]=(CHK_SPIN(axis))?0:1) ==1){
// 								flag=true ;
// 							}
// 						}
// 					 	else{
// 							MachineStatus.is_home[axis] = 0;	// is_home[axis]=1�N��axis�b�ثe�w�g�b���I
// 						}
// 					}
// 					if( MachineStatus.motor[axis] ){						
// 						is_home[axis]= MachineStatus.is_home[axis] ;
// 						if( !MachineStatus.is_home[axis] ){		
// 							 seq[i][j++] = axis;
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// 	
// 	if(flagSPIN_ZRT && !flag){
// 		in_movToZeroAll=false ;
// 		return(1) ;
// 	}
// 		
// 		
// 	//�e�u�����]���s
// 	MachineStatus.sign[AXIS_Y]	   = PLUS_SIGN;
// 	MachineStatus.axis_val[AXIS_Y] = 0;
// 	MachineStatus.axis_grid[AXIS_Y] = 0;	
// 	//MachineStatus.NewVal[AXIS_Y] = 0;	
// 	TxBuf[0]=poscmd ;	
// 	TxBuf[1]=AXIS_Y;			
// 	int tmp=MachineStatus.axis_val[AXIS_Y];
// 	for(int i =0;i<3;i++){
// 		TxBuf[4-i]=tmp&0xff;
// 		tmp>>=8;
// 	}
// 	//printf("%x  %x %x %x %x\n",TxBuf[0],TxBuf[1],TxBuf[2],TxBuf[3],TxBuf[4]) ;
// 	Tx(UART2,TxBuf,5) ;
// 	
// 	Clr2016s(AXIS_Y) ;
// 	
// 	for(axis=0 ; axis <MachineStatus.axis_no ; axis++){	
// 		zrt[axis].mode=MachineStatus.ZrtMode[axis] ; 
// 		//zrt[axis].axis_val= MachineStatus.axis_val[axis] ;
// 		zrt[axis].axis_val= MachineStatus.axis_val[axis] ;
// 		zrt[axis].sign = MachineStatus.sign[axis] ;
// 		//zrt[axis].org_loc= BcdToBin(8,MachineStatus.axis_val[axis] ,MachineStatus.sign[axis]) ;
// 		zrt[axis].org_loc= (long)MachineStatus.axis_val[axis];
// 		TO_GRID(axis,zrt[axis].org_loc) ;
// 	} 
// 	if((MachineStatus.axis_no > AXIS_A) && CHK_ROTW(AXIS_A)){
// 		zrt[AXIS_A].mode= MODE_ZRT_ROTATE ;
// 	}
// 	
// 	
// 	
// 	
// 	for( i=0; i < MAX_AXIS; i++ ){
// 		//�����k�s�w��
// 		for( j=0; j <MachineStatus.axis_no; j++ ){
// 			zrt[j].state= ZRT_COMPLETE ; //�w�]
// 		}
// 		for( j=0; j < MachineStatus.axis_no; j++ ){
// 			
// 			if( (axis=seq[i][j]) != 0xff ){						
// 				MachineStatus.dst_pos_sign[axis] = zrt[axis].sign ;
// 				MachineStatus.dst_pos[axis] = zrt[axis].axis_val ;
// 				if(zrt[axis].mode == MODE_ZRT_ROTATE){
// 					reverse_mov_ZRT_rotate(axis) ; //½�u�G���^���I�~����,�a�^��
// 				}
// 				//else if ((zrt[axis].mode == MODE_ZRT_YA_ABS1)||(zrt[axis].mode == MODE_ZRT_YA_ABS2)||
// 				//	       (zrt[axis].mode == MODE_ZRT_SA_ABS1)||(zrt[axis].mode == MODE_ZRT_SA_ABS2)){
// 				//	reverse_mov_ZRT_YA_ABS(axis) ;
// 				//}
// 				else{
// 					reverse_mov_ZRT(axis,(uint32)BcdToBin(4,MachineStatus.ZRTPreM[axis])) ; //�k�s�w��
// 					
// 				}
// 				zrt[axis].state = ZRT_WAIT3701 ;
// 			}
// 			zrt[axis].first = true ;
// 		}
// 		
// 		
// 		//�����k���I
// 		bool complete ;
// 		do{
// 			complete =true ;
// 			for(axis=0 ; axis < MachineStatus.axis_no; axis++ ){
// 				switch(zrt[axis].state){
// 				case  ZRT_WAIT3701:
// 					if(Chk3701(axis)){
// 						bool continue_reverse = false;
// 						switch(zrt[axis].mode){
// 							case MODE_ZRT_DIRECT:
// 								if ((MachineStatus.SensorHighLow[axis]==0x2) || ((axis == AXIS_X)&&BMOTORGRID(AXIS_X)==4000)){
// 									//�u���@���k�s�w��
// 								}
// 								else if (NewH && GetMotorZrt(axis)==0){
// 									continue_reverse = true; //GetMotorZrt,1-sensor�O�G,0-sensor�O��
// 								}
// 								break ;
// 							case MODE_ZRT_INDIRECT:
// 							case MODE_ZRT_IMM:
// 								if (Get_Zrt_io(axis)==0 && MachineStatus.ZRTPreM[axis])
// 									continue_reverse = true;
// 								break ;
// 							case MODE_ZRT_YA_ABS1:
// 							case MODE_ZRT_YA_ABS2:
// 							case MODE_ZRT_SA_ABS1:
// 							case MODE_ZRT_SA_ABS2:
// 								AtHome(axis);
// 								break ;
// 							default:;
// 						}

// 						if (zrt[axis].state != ZRT_COMPLETE){
// 							if (!continue_reverse|| REVERSE_ONCE){ //REVERSE_ONCE : PCB3���O2014�~�e���u�ਫ�@���k�s�w��(�LGetMotorZrt�\��)
// 								zrt[axis].state=ZRT_DELAY1 ;
// 								zrt[axis].timeout= mTimerSet(30) ;
// 							}
// 							else {
// 								MachineStatus.dst_pos_sign[axis] = MachineStatus.sign[axis]; //���
// 								MachineStatus.dst_pos[axis]	= MachineStatus.axis_val[axis];
// 								if ((zrt[axis].mode == MODE_ZRT_DIRECT) && (MachineStatus.ZRTPreM[axis] == 0)){
// 									leave_snesor(axis) ; //���V(�^���I��V)���}sensor
// 								}	
// 								else {
// 									reverse_mov_ZRT(axis,10) ; //�k�s�w��=�ϦV(�^���I�ϦV)���}sensor
// 								}

// 							}
// 						}
// 					}
// 					break ;
// 					case  ZRT_DELAY1:
// 						if(IsTimeUp(zrt[axis].timeout)){
// 							//if(axis==AXIS_X)printf("---%d\---n",zrt[axis].timeout);
// 							if(zrt[axis].mode == MODE_ZRT_ROTATE){
// 								if(zrt[axis].power_on){
// 									MachineStatus.sign[axis]= zrt[axis].sign ;
// 									MachineStatus.axis_val[axis]= zrt[axis].axis_val ;
// 									if((!zrt[axis].power_on) && (zrt[axis].org_loc <= 50) && (zrt[axis].org_loc >= -100)){
// 										int total=200 ;
// 										Set3701(axis, PLUS_SIGN, total , total ,total ,true,0,0);
// 										zrt[axis].state= ZRT_ROTATE_WAIT3701_1 ;
// 									}
// 									else if(zrt[axis].org_loc >=0 ){
// 										SendCmdZrt(axis, MINUS_SIGN,1);
// 										zrt[axis].state= ZRT_ROTATE_WAIT_HOME_INT_RIGHT ;
// 									}
// 									else{
// 										SendCmdZrt(axis, PLUS_SIGN,1);
// 										zrt[axis].state=ZRT_ROTATE_WAIT_HOME_INT_LEFT ;
// 									}
// 									if(NewH){
// 										EnableHomeInt(axis,ENABLE_INT_STOP) ;
// 									}
// 								}
// 								else{
// 									set_zrt_power_on(axis) ;
// 									MachineStatus.dst_pos_sign[axis]	  = MachineStatus.sign[axis]	 = PLUS_SIGN;
// 									MachineStatus.dst_pos[axis] = MachineStatus.axis_val[axis] = 0;
// 									DispCurAxis_q(1);
// 									zrt[axis].state= ZRT_COMPLETE ; //½�u
// 								}
// 							}
// 							else{
// 								if(IsTimeUp(timeout_DispCurAxis) ){
// 									DispMovAxis_q(axis);
// 									timeout_DispCurAxis= mTimerSet(MAX_DispCurAxis);
// 								}
// 								SendCmdZrt(axis,MachineStatus.home_seq_sign[axis],zrt[axis].first?1:8) ;
// 								
// 								switch(zrt[axis].mode){
// 								case MODE_ZRT_DIRECT:
// 									if(NewH){
// 										EnableHomeInt(axis,ENABLE_INT_STOP) ;
// 									}
// 									zrt[axis].state= ZRT_DIRECT_WAIT_HOME_INT ;
// 									break ;
// 								case MODE_ZRT_INDIRECT:
// 									{
// 										if((!zrt[axis].power_on)&&(zrt[axis].first && (zrt[axis].org_loc <=20) && (zrt[axis].org_loc >=-20)) || (!zrt[axis].first)){//�ĤG����,�^���I
// 											if(NewH){
// 												EnableHomeInt(axis,ENABLE_INT_STOP) ;
// 											}
// 											zrt[axis].state= ZRT_INDIRECT_WAIT_HOME_INT ;
// 										}
// 										else{
// 											zrt[axis].state= Get_Zrt_io(axis)?ZRT_INDIRECT_WAIT0:ZRT_INDIRECT_WAIT1 ;
// 										}
// 									}
// 									break ;
// 								case MODE_ZRT_IMM:
// 									zrt[axis].state=Get_Zrt_io(axis)? ZRT_IMM_WAIT0 : ZRT_IMM_WAIT1 ; //�ثe�b���I�ݭn�����ܬ�1
// 									break ;
// 								}
// 							}
// 						}
// 					break ;
// 				case  ZRT_ROTATE_WAIT3701_1:
// 					if(Chk3701(axis)){
// 						zrt[axis].state=ZRT_ROTATE_DELAY4 ;
// 						zrt[axis].timeout= mTimerSet(30) ;
// 					}
// 					break ;
// 				case  ZRT_ROTATE_DELAY4:
// 					if(IsTimeUp(zrt[axis].timeout)){
// 						SendCmdZrt(axis, MINUS_SIGN,1);
// 						EnableHomeInt(axis,ENABLE_INT_STOP) ;
// 						zrt[axis].state=ZRT_ROTATE_WAIT_HOME_INT_RIGHT ;
// 					}
// 					break ;
// 				case ZRT_INDIRECT_WAIT_HOME_INT:
// 					if(!MachineStatus.go_home[axis]){
// 						DisableHomeInt(axis) ;
// 						AtHome(axis) ;
// 					}
// 					else{
// 						if(chk_over_home(axis)){
// 							DisableHomeInt(axis) ;
// 							zrt[axis].state= Get_Zrt_io(axis)?ZRT_INDIRECT_WAIT0 : ZRT_INDIRECT_WAIT1 ;
// 						}
// 					}
// 					break ;
// 				case  ZRT_INDIRECT_WAIT1 :
// 					if(Get_Zrt_io(axis)){
// 						zrt[axis].state=ZRT_INDIRECT_DELAY3 ;
// 						zrt[axis].timeout= mTimerSet(100) ;
// 					}
// 					break ;
// 				case ZRT_INDIRECT_DELAY3:
// 					if(IsTimeUp(zrt[axis].timeout)){
// 						zrt[axis].state= ZRT_INDIRECT_WAIT0 ;
// 					}
// 					break ;
// 				case  ZRT_INDIRECT_WAIT0 :
// 					if(Get_Zrt_io(axis)==0){
// 						if(NewH){
// 							EnableHomeInt(axis,ENABLE_INT_STOP) ;
// 						}
// 						zrt[axis].state=ZRT_INDIRECT_WAIT_HOME_INT1;
// 					}
// 					break ;
// 				case  ZRT_INDIRECT_WAIT_HOME_INT1 :
// 				case  ZRT_DIRECT_WAIT_HOME_INT :
// 						if(ChkDriverClear(axis)){
// 							DisableHomeInt(axis) ;
// 							StopMotor(axis) ;
// 							AtHome(axis) ;
// 						}
// 					break ;
// 				case  ZRT_ROTATE_WAIT_HOME_INT_RIGHT :
// 					if(!MachineStatus.go_home[axis]){
// 						DisableHomeInt(axis) ;
// 						zrt[axis].first= false ;
// 						AtHome(axis) ;
// 					}
// 					break ;
// 				case  ZRT_ROTATE_WAIT_HOME_INT_LEFT :
// 					if(!MachineStatus.go_home[axis]){
// 						DisableHomeInt(axis) ;
// 						MachineStatus.dst_pos_sign[axis]= PLUS_SIGN ;
// 						MachineStatus.dst_pos[axis]= 0 ;
// 						if(NewH){
// 							move_rotate_left_right(ROTATE_ZRT_GRID) ;
// 						}
// 						zrt[axis].state= ZRT_ROTATE_WAIT_RIGHT ;
// 					}
// 					break ;
// 				case  ZRT_ROTATE_WAIT_RIGHT :
// 					if(Chk3701(axis)){
// 						zrt[axis].state=ZRT_ROTATE_DELAY5 ;
// 						zrt[axis].timeout= mTimerSet(300) ;
// 					}
// 					break ;
// 				case  ZRT_ROTATE_DELAY5 :
// 					if(IsTimeUp(zrt[axis].timeout)){
// 						MachineStatus.dst_pos_sign[axis]= MachineStatus.sign[axis] ;
// 						MachineStatus.dst_pos[axis]= MachineStatus.axis_val[axis] ;
// 						if(NewH){
// 							move_rotate_right_left(ROTATE_ZRT_GRID+300) ;
// 							MachineStatus.go_home[axis]=1 ;
// 							EnableHomeInt(axis,ENABLE_INT_STOP) ;
// 						}
// 						zrt[axis].state=ZRT_ROTATE_WAIT_HOME_INT_RIGHT ;
// 					}
// 					break ;
// 						
// 				case  ZRT_IMM_WAIT1 :
// 					if(Get_Zrt_io(axis)){
// 						zrt[axis].state=ZRT_IMM_DELAY2 ;
// 						zrt[axis].timeout= mTimerSet(100) ;
// 					}
// 					break ;
// 				case ZRT_IMM_DELAY2:
// 					if(IsTimeUp(zrt[axis].timeout)){
// 						zrt[axis].state= ZRT_IMM_WAIT0 ;
// 					}
// 					break ;
// 				case  ZRT_IMM_WAIT0 :
// 					if(Get_Zrt_io(axis)==0){
// 						StopMotor(axis) ;
// 						AtHome(axis) ;
// 					}
// 					break ;
// 				}
// 				if(zrt[axis].state != ZRT_COMPLETE){
// 					complete= false ;
// 					
// 					if (zrt[axis].state == ZRT_GOAWAY_SENSOR || zrt[axis].state == ZRT_WAIT_GOAWAY){
// 					}
// 					else{
// 						if(IsTimeUp(timeout_DispCurAxis) ){
// 							DispMovAxis_q(axis);
// 							timeout_DispCurAxis= mTimerSet(MAX_DispCurAxis);
// 						}

// 						if( MachineStatus.safe_err )  return( -1 );

// 						if( MachineStatus.motor[axis] && CHK_OVERFLOW1(axis) ){
// 							StopMotor(axis);
// 							DispGoHomeFailure(axis);
// 							WAIT_NEW_KEY();
// 							//ClrMsgWin_q();
// 							SoftReset() ;
// 						}
// 					}
// 				}
// 			}
// 			//DelayCount(DISP_DELAY);
// 			CHECK_RESET(true); //�s620
// 			//update_roll_q() ; //�s620
// 			if(NewH){
// 				update_run_DDA() ;
// 			}
// 			//while(exe_proc_queue()) ;
// 		}
// 		while(!complete) ;
// 	}
// 	
// 	
// 	if(!flagSPIN_ZRT){
// 		dDelay(3) ;
// 		sendError(GoHome,0,3);
// 		//ClrMsgWin_q();
// 	}
// //�ϱo���I�P��������
// 	for(BYTE axis=AXIS_Z ; axis < MachineStatus.axis_no ; axis++){
// 		bool rotq_mdy = (MachineStatus.ROTQ_MDY&0xf) && (CHK_ROTQ(axis))&& !is_home[axis] ; //���
// 		bool spin_mdy=  (MachineStatus.SPIN_MDY&0xf) && (CHK_SPIN(axis))&& !is_home[axis] ;	//����
// 		if(MachineStatus.motor[axis] &&(rotq_mdy||spin_mdy)){
// 			AxisMDY(axis);
// 		}
// 	}

// #if 1
// 	//����s�]���I
// 	bool flag_zrt=false ;
// 	for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis++){
// 		if(MachineStatus.motor[axis] && MachineStatus.ZRTSET[axis] !=0&& !is_home[axis]){
// 			if(!flag_zrt){
// 				flag_zrt = true ;
// 				/*
// 				if(!flagSPIN_ZRT){
// 					DispMsgWin_q(-1, -1, MSG_WIN, 	"����s�]���I...." ,
// 									  				" Move To NEW Setting ZRT...");
// 					FORCE_PROC_QUEUE ;
// 				}
// 				*/
// 			}
// 			printf("zrtset=%d\n",MachineStatus.ZRTSET[axis]);
// 			//SDWORD mov=BcdToBin(5,MachineStatus.ZRTSET[axis],MachineStatus.ZRTSET_sign[axis]) ;
// 			//Unit2Grid(axis,mov) ;
// 			SDWORD tmp=MachineStatus.ZRTSET[axis];
// 			printf("1_grid=%d \n",tmp);
// 			Unit2Grid(axis,tmp) ;
// 			printf("grid=%d \n",tmp);
// 			DWORD ref ;
// 			cal_zrtref(axis,ref) ;
// 			//ref*=(mov >= 0) ? mov : -mov ;
// 			ref*=MachineStatus.ZRTSET[axis] ;
// 			ref /= BcdToBin(MOTOR_GRADS_BCD,MachineStatus.motor_grads[axis]) ;
// 			Set3701(axis,PLUS_SIGN, ref , tmp,tmp,true,0,0);
// 			Wait3701(axis) ;
// 		}
// 	}
// 	if(!flagSPIN_ZRT){
// 		if(flag_zrt){
// 			ClrMsgWin_q();
// 		}
// 	}
// #endif
// /*
// #if SW_SIM_MOTOR
// 	#ifndef DEBUG_NCNC
// 		dDelay(10) ;
// 	#endif
// 		
// 	for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis++){
// 		sim_motor.dabsloc[axis]=0 ;
// 		sim_motor.totalmov[axis]=0 ;
// 		sim_motor.wlval2016[axis]=(WORD)dReadAbsPos(axis) ;
// 	}
// #endif
// */


// 	in_movToZeroAll=false ;
// 	//T_STOP�sZrt��2016�ƭ�
// 	for(int xaxis=AXIS_Z; xaxis<MAX_AXIS_8; xaxis++){	
// 		Axis_Zrt2016VAL[xaxis]=(SDWORD)dReadAbsPos(xaxis);
// 		//��l��_�U�b_�ثe�ֿn_�����u®���`���
// 		T_Stop_DwAll_32[xaxis]=0;
// 		T_Stop_DwAll_16[xaxis]=0;
// 	}
// 	if(NewH){
// 		for(int xaxis=AXIS_X ; xaxis < MachineStatus.axis_no ; xaxis++){
// 			if(xaxis !=AXIS_Y){
// 				Clr2016s(xaxis) ;
// 			}
// 		}
// 	}
// 	//first_dda=1;
// 	Slide_first_zero=true;
// 	return(1) ;
// 	
	
}	

void InitRunVar (void)
{
// 	WORD i;
// 	MachineStatus.pass_x_home	= 0;
// 	MachineStatus.home_err		= 0;
// 	MachineStatus.stop_machine	= 0;
// 	MachineStatus.th_stop		= 0;
// 	MachineStatus.miss_flag		= 0;
// 	MachineStatus.man_air		= 0;
// 	MachineStatus.air_buf		= 0;
// 	MachineStatus.loop_ptr		= 0;
// 	MachineStatus.in_loop		= 0;
// 	MachineStatus.last_line		= 0;
// 	MachineStatus.prog_mody		= 0;
// 	MachineStatus.wire_on		= 0;
// 	
// 	MachineStatus.adc_level		=(uint8) -1;
// 	MachineStatus.cur8254		= MachineStatus.cnt8254;
// 	timeout_WAIT_MOTOR_NEAR_X=
// 	timeout_WAIT_MOTOR_NEAR_IN_LOOP=0 ;
// 	for( i=0; i < 4; i++ ){
// 		//chk_th ---���ɬ�0;������SET_TOUCH��,��ȱN�]��touchno(����0);
// 		//			�D�n��TouchIsr�ΨӰϤ�,�����_�O���w����;��SET_TOUCH����
// 		//pass_th---SET_TOUCH��,��ȳ]��0;��TouchIsr���_�o�ͮ�,��ȳ]��1
// 		//rec_th----SET_TOUCH��,��JPROG_VAL_NULL��touch�Ҧb�檺X�b�ҩl��
// 		//cur_th----TouchIsr���_�o�ͮ�,�Yrec_th�Ȭ�PROG_VAL_NULL�h�s�J�ثe2016��;�_�h�s�Jrec_th��
// 		
// 		MachineStatus.chk_th[i]		= 0;
// 		MachineStatus.pass_th[i]	= 0;
// 		MachineStatus.rec_th[i]		= 0;
// 		MachineStatus. dcur_th[i]	= 0;
// 	}

// 	for( i=0; i < MAX_AXIS; i++ ){
// 		
// 		EPT_IDX(i, MachineStatus.running);
// 		EPT_IDX(i, EnableHomeInt_ZrtMode);		
// 		MachineStatus.running[i] = 0;
// 		EnableHomeInt_ZrtMode[i]= false ;
// 	}
// 	ActTblIdx = 0;
// 	flag_complete_spring_cmd =
// 	flag_complete_spring= 
// 	flag_ReturnManMode =
// 	flag_axis_cmd_SaveFile=
// 	flag_DispCurPosDelay=false ;
// 	no_DispCurProgList =0 ;
// 	rd_DispCurProgList =wr_DispCurProgList =0 ;
// 	plus_cnt=minus_cnt=0 ;
// 	for(int i=0 ; i <4 ; i++){
// 		flag_ClrTouchPos[i]= false ;
// 	}
// 	flag_DispMissNo=false ;
// 	st_DispStatusBar.flag =false ;
// 	NEAR_b =  (BYTE)BcdToBin(2, MachineStatus.NEAR);
// 	PayOff_b=MachineStatus.PayOff;
// 	if(MachineStatus.Unit[AXIS_Y]==UNIT_MM){
// 		MM_TO_GRID(AXIS_Y,PayOff_b) ;
// 	}

// 	
// 	
// #if (SAVE_AXIS_CMD)
// 	flag_SaveFile = false ;
// #endif	



// 	InitAirTbl() ;
// 	MachineStatus.TargetY=0 ;
// 		
// 	st_extencoder.first= true ;
// 	st_extencoder.nogap=0 ;
// 	st_extencoder.meangap=0 ;
// 	st_extencoder.plus_maxgap=0 ;
// 	st_extencoder.minus_maxgap=0 ;
// 	flagStopRun = false ;
// 	chk_unconnector=false ;
// 	ChkSlide=false;
// 	Slide_first_zero=false;
// 	for(int axis=0 ; axis < MAX_AXIS ; axis++){
// 		enable_chk_unconnector[axis]= false ;
// 	}
// 		for(int axis=0 ; axis <MachineStatus.axis_no ; axis++){
// 				ChkOverFlow[axis]=false;
// 		}
// 	firstSPIN_ZRT=true ;
// 	movSPIN_ZRT=0 ;
// 	
// 	ReMake_flag=false;
// 	
// 	//2012_0807_�ץ�_�U�b�[��t�A�Ͳ��ɱN"�[��t�Ȧs��"�M���s---
// 	uint8 reg[3]={0,0,0};
// //	SetSpeed_PMfun(reg);
// 	cnt_T_STOP_MDYVAL=0 ;
// 	ini_loopchk(false) ;
// 	MachineStatus.touch_before_err =false;	
}



void ini_zrt_power_on()
{
// 	for(BYTE axis=0 ; axis < MAX_AXIS ; axis++){
// 		zrt[axis].power_on=true ;
// 	}
}
void set_zrt_power_on(BYTE axis)
{
// 	zrt[axis].power_on= false ;
}	
void ChkAxisVal (BYTE axis, BYTE *sign, int *val)
{
// 	int  tmp;
// 	int dw=*val;

// 	static int i=0;
// 	i+=1;


// 	//dw = BcdToBin(8, *val);
// 	
// 	if(MachineStatus.Unit[AXIS_X] == UNIT_GRID){
// 		//if( (*sign & 0x7f) != PLUS_SIGN )  dw = -dw;
// 	}
// 	switch( axis )
// 	{
// 	case AXIS_X:
// 		tmp = dBMOTORUNIT_X() ;
// 		if(MachineStatus.Unit[AXIS_X] == UNIT_GRID){
// 			if( dw < 0 )  
// 				dw += tmp;
// 			else
// 				dw %= tmp;
// 			//printf("%d %d\n",dw,tmp);
// 			*val = dw;
// 			//*val = dBinToBcd(8, dw);
// 			*sign = PLUS_SIGN;
// 		}
// 		else{
// 			dw %= tmp;
// 			*val = dw;
// 			//*val = dBinToBcd(8, dw);
// 		}
// 		break;
// 	default:
// 		break;
// 	}




}
BYTE OFFSET_Y_dir(BYTE dir)
{
// BYTE tdir=dir ;
// if((MachineStatus.Type != TYPE_1635_1835)&&(MachineStatus.Type != TYPE_620_820)&&(MachineStatus.Type != 0x630)&&(MachineStatus.Type != 0x20) ){ //TYPE_1635_1835���s��635_835(�ɽu�M620�@��)
// 	BYTE b8_dir = tdir & 0x80 ; 
// 	tdir= (((dir& 0x7f) == PLUS_SIGN)? MINUS_SIGN:PLUS_SIGN) | b8_dir ;
// }
// return(tdir) ;
}

void cal_zrtref(BYTE axis,DWORD &ref)
{
// 	//DWORD basespd= BcdToBin(4,MachineStatus.wZeroSpd[axis]) ;
// 	DWORD basespd= MachineStatus.wZeroSpd[axis] ;
// 	if(basespd == 0){
// 		basespd=1 ;
// 	}
// 	ref =(1000L*60*10/basespd) ;
}
BYTE Get_Zrt_io(BYTE axis)
{
// 	if(MachineStatus.ZrtCorr[axis] == 0){  //0-->W��J�I
// 		return(rDosMem(pc_base+INM)& 0x1) ;
// 	}
// 	else{
// 		return(rDosMem(pc_base+INH)& MaskZrtMode[MachineStatus.ZrtCorr[axis]-AXIS_Z]) ;
// 	}
}

void leave_snesor(BYTE axis)
{ 
// 	//�����^���I�S�]�k�s�w����,�Y���bsensor�G�O�B,�Φ^���I��V�����}sensor
// 	//�קKsensor�O�G�B�����T,�~�{���O���I���_
// 	uint32 grid=10 ;
// 	uint32 ref=grid ;
// 	Set3701(axis,(MachineStatus.home_seq_sign[axis]== PLUS_SIGN)? PLUS_SIGN : MINUS_SIGN  ,ref , grid,grid,true,0,0);
}

void AtHome(BYTE axis)
{
// 	MachineStatus.is_home[axis] = 1;
// 	Set3701(axis, 0, 0, 0,0,true,0,0);
//     
// 	MachineStatus.dst_pos_sign[axis]	  = MachineStatus.sign[axis]	 = PLUS_SIGN;
// 	MachineStatus.dst_pos[axis] = MachineStatus.axis_val[axis] = 0;//MachineStatus.NewVal[axis] = 0;
// 	MachineStatus.axis_val[axis]=0;
// 	//MachineStatus.NewVal[axis]=0;
// 	MachineStatus.axis_grid[axis]=0;
// 	
// 	DispCurAxis_q(1);

// 	if (((slide_axis)&& (axis == slide_axis)) || ((ServoCutter_axis) && (axis == ServoCutter_axis))){ //�Ʈy�Τ��M
// 		zrt[axis].state= ZRT_GOAWAY_SENSOR ;
// 	}
// 	else {
// 		set_zrt_power_on(axis) ;
// 		zrt[axis].state= ZRT_COMPLETE ;
// 		MachineStatus.axis_grid[axis]=0;
// 	}
// 	cnt_Set3701=0 ;
// 	if(cnt_Set3701==0)
// 			wDosMem(pc_base+DriverClear,(uint8)0) ;

}

void reverse_mov_ZRT_rotate(BYTE axis)
{
// 	if(!zrt[axis].power_on){
// 		BYTE dir= MINUS_SIGN ,dir_y;
// 		DWORD mov ;
// 		//��Ū��2016����,�M�w���ʮ��
// 		if(axis_type ==	INTEL8051_AXIS){
// 			WORD cur_a ;
// 			cur_a =(WORD) dReadAbsPos(axis) ;
// 			if(cur_a & 0x8000){
// 				// �t��
// 				cur_a= (cur_a ^ 0xffff)+1 ;
// 				dir= PLUS_SIGN ;
// 			}
// 			mov=cur_a ;
// 		}
// 		else{
// 			DWORD cur_a ;
// 			cur_a = dReadAbsPos(axis) ;
// 			if(cur_a & BIT31){
// 				// �t��
// 				cur_a= (cur_a ^ 0xffffffff)+1 ;
// 				dir= PLUS_SIGN ;
// 			}
// 			mov = cur_a ;
// 		}
// //		mov %= (WORD)BcdToBin(MOTOR_GRADS_BCD,MachineStatus.motor_grads[axis]) ;
// 		if(mov != 0){
// 			//�p��ɶ�
// 			DWORD ref ;
// 			cal_zrtref(AXIS_A,ref) ;
// 			ref *=mov ;
// 			ref /=BcdToBin(MOTOR_GRADS_BCD,MachineStatus.motor_grads[axis]) ;
// 			MachineStatus.sign[axis]= zrt[axis].sign ;
// 			MachineStatus.axis_val[axis]= zrt[axis].axis_val ;
// 			Set3701(axis, dir, ref , mov,mov,true,0,0);
// 		}
// 	}
}
void ngetkey()
{
// 	char buf[3] ;
// 	int key ;
// 	static int keycode_mode=0 ;
// 	static char first_code= 0 ;
// 	static bool flag_keylock=false ;
// 	static struct TIMER timeout_keylock ;
// 	int has_key ;
// 		//ProcessKeyswap() ;//�s620
// 	// ��L���
// 	if(NewH && KeyLockCHG){				//�s�D���f�t����L
// 		if(KeyInput&0x1&&MachineStatus.KEYLOCK==1) keylock=true;	//��L����Ѽ�
// 		else keylock=false;
// 	}
// 	// keyscrn =0 -----clear keyscrn
// 	//          1 -----keyswap
// 	//          2 -----keylock
// 	
// 	//if(keylock){
// 	//	if(keyscrn != 2){
// 	//		// disp keylock
// 	//		//DispKeyscrn_q(keyscrn=2) ;
// 	//		printf("keylock\n");
// 	//	}
// 	//}
// 	//else if(keyswap){
// 	//	if(keyscrn != 1){
// 	//		//DispKeyscrn_q(keyscrn =1) ;
// 	//		// disp keyswap
// 	//		printf("keyswap\n");
// 	//	}
// 	//}
// 	//else{
// 	//	if(keyscrn !=0){
// 	//		// clear keyscrn
// 	//		//DispKeyscrn_q(keyscrn =0) ;
// 	//		printf("clear keyscrn\n");
// 	//	}
// 	//}
// 	has_key=0 ;

// 	if(has_key){
// 		//�ˬd�O�_�����Ureset ��
// 		if(key == KEY_DUMMY_RESET){
// 			StopMotor() ;
// 			Reset=1 ;
// 		}
// 		else if(KeyState == WAIT_NEW_KEY_STATE){
// 			// wait for key state
// 			KeyState= NORMAL_KEY_STATE ;
// 			//ClrMsgWin_q();
// 			ClrKeyBuf();
// 		}	
// 		// else{					
// 		// 	fill_key_buf(key) ;
// 		// }		   
// 	}
}
void InitVar (void)
{
// 	BYTE i;
// // ���m��Ҧ��ܼƪ���ȳ]�w
// 	
// 	MachineStatus.WorkMode = MachineStatus.lWorkMode;
// 	//MachineStatus.BiosRst =	MachineStatus.lBiosRst = 0;

// 	PAUSE_Y=false;	//Gcod�аO�A�����e�u�Ȱ���
// 	x_dir=0 ;
// 	lx_loc=0 ;
// 	FlashOn=true ;
// 	timeout_flash= dTimerSet(TIMER_FLASH) ;
// 	timeout_roll_data= dTimerSet(TIMER_ROLL_DATA);
// 	screen_state = MAIN_SCREEN ;
// 	KeyState=NORMAL_KEY_STATE ;
// 	Reset = 1 ;
// 	ModeTmp=MAN_MODE;
// 	ChkActtblEnd=true;
// 	ChkRacttbl=false;
// 	
// 	KeyBufRIdx = KeyBufWIdx = 0;
// 	RIdx = PIdx = 0;
// 	SendCmdID = LastCmdID = 0;
// 	ResponseCmd = 0;
// 	
// 	RW3701Err = 0;
// 	RESEND3701Err=0 ;
// 	DS3701Err =0 ;
// 	FileRWErr = 0;
// 	if( MachineStatus.file >= dBinToBcd(3, MAX_FILE_NO) )  MachineStatus.file = 0;
// 	MachineStatus.flg_ScrnSav=false ;

// 	CurProgLine = 0;
// 	YProgoff = 0;
// 	CursorLoc = PROG_CURSOR;
// 	Old54Val = 0xffff;


// 	MachineStatus.op_mode		= MAN_MODE;
// 	MachineStatus.speed_mode	= MachineStatus.speed_mode!=AUTO?FAST:AUTO;
// 	MachineStatus.stop_machine	= 0;
// 	MachineStatus.man_air		= 0;
// 	MachineStatus.air_buf		= 0;
// 	MachineStatus.safe_sw		= (MachineStatus.safe_sw!=SAFE_ON?SAFE_OFF:SAFE_ON);
// 	MachineStatus.safe_err		= 0;
// 	MachineStatus.scrn_off		= 0;
// 	//MachineStatus.y_scale		= 0;//reset���N�b���v����

// 	if(MachineStatus.language >3){
// 		MachineStatus.language	= 0;
// 	}
// 	MachineStatus.wire_on		= 0;
// 	MachineStatus.gray_color	= 0;
// 	MachineStatus.th_test		= 0;

// 	if( MachineStatus.repair_spd > dBinToBcd(2, MAX_REPAIR_SPD) )	MachineStatus.repair_spd = 0;
// 	if( MachineStatus.repair_dst > dBinToBcd(2, MAX_REPAIR_DST) )	MachineStatus.repair_dst = 0;


// 	for( i=0; i < MAX_AXIS; i++ ){
// 		MachineStatus.is_home[i] = 0;
// 		MachineStatus.go_home[i] = 0;
// 	}
// 	//ini_axis_str() ;
// 	// X,Y�b�T�w���}(ON)
// 	MachineStatus.motor[0] = 1;
// 	MachineStatus.motor[1] = 1;

// 	AirScrn_ON=false ;
// 	MarkerScrn_ON=false;
// 	flag_run=false ;
// 	y_Sprintf=25 ;
// 	keyswap=keylock=false ;
// 	keyscrn=0 ;
// 	off_power = 0x1 ;
// 	
// 	ErrMsg[0]= '\0' ;
// 	ErrMsg_timeout_flg=false ;
// 	


// 	YLOC_dir=ALOC_dir= PLUS_SIGN ;
// 	AmdyY=0 ; 
// 	IndexScrn=false ;
// 	
// 	




// #if  NEWV_MDY
// 	for(BYTE axis =0 ; axis < MAX_AXIS ; axis++){
// 		sstopmotor[axis].flag= false ;
// 	}
// #endif
// 	Err_ExtEncoder= false ;
// 	//Clr_Set3701_ARM() ;

// 	in_movToZeroAll=false ;
// 	flagSPIN_ZRT=false ;
// 	flag_VerifyProg=false ;
// 	for(uint8 axis=0 ; axis < MAX_AXIS ;axis++){
// 		ChkOverFlow[axis]=false ;
// 	}
// 	//SetCutterMaxLimit(); 	//�]�w���M�b�̤j����=���M�Z��
// 	//cal_gear();						//�����m�����F����

}


#define  MUL48(a)					\
		tl = tmov & 0xffff ;		\
		th = tmov >> 16 ;			\
		tl = tl * a ;				\
		tm = th = th * a ;			\
		tm= tm << 16 ;				\
		th = th >> 16 ;				\
		tl = tl+tm ;				\
		if(tl < tm){				\
			th++ ;					\
		}

#define DIV48(a)								\
		th = (th << 16)+ (tl >> 16) ;			\
		rem = th % a ;							\
		reh= th /a ;							\
		tl = (tl&0xffff) + (rem << 16) ;		\
		rel= tl / a ;							\
		res = rel + (reh << 16) ;				\
		mov = res ;

SDWORD ExtGrid2_Grid(SDWORD mov)
{
// 	//for 620 return(mov*38400*2/23463)
// 	//for 635 return(mov*283/50)
// 	bool sign = true ;
// 	DWORD tl,th ,tm, tmov,rem,res,reh,rel;
// 	if(mov < 0){
// 		sign = false ;
// 		tmov= -mov ;
// 	}
// 	else{
// 		tmov= mov ;
// 	}
// 	if (MachineStatus.gear_y[0]!=0x0 && MachineStatus.gear_y[1]!=0x0){
// 		uint32 gear0 = (uint32)BcdToBin(6,MachineStatus.gear_y[0]) ; 
// 		uint32 gear1 = (uint32)BcdToBin(6,MachineStatus.gear_y[1]) ;
// 		mov = (long long)tmov*gear0/gear1;
// 	}
// 	else if(MachineStatus.Type == TYPE_635_835 ||MachineStatus.Type == TYPE_1635_1835){
// //		mov = mov *283/50 ;
// 		MUL48(283)
// 		DIV48(50) 
// 	}
// 	else if(MachineStatus.Type == TYPE_650_850){
// 		mov = (long long)tmov*547/100;
// 	}
// 	else{
// 		if (CHK_ROTW(AXIS_A)){
// 			mov = (long long)tmov*38400*2/23463;
// 	 	}
// 	 	else {
// 			mov = (long long)tmov*12/5;
// 		}
// 	}
// 	if(!sign){
// 		mov = -mov ;
// 	}
// #if 0	//5000��encoder
// 	mov /=2 ;
// #endif
// 	return (mov) ;	
// 	
}
SDWORD Grid2_ExtGrid(SDWORD mov)
{
// 	//for 620 return(mov*38400*2/23463)
// 	//for 635 return(mov*283/50)
// 	bool sign = true ;
// 	DWORD tl,th ,tm, tmov,rem,res,reh,rel;
// 	if(mov < 0){
// 		sign = false ;
// 		tmov= -mov ;
// 	}
// 	else{
// 		tmov= mov ;
// 	}
// 	if (MachineStatus.gear_y[0]!=0x0 && MachineStatus.gear_y[1]!=0x0){
// 		uint32 gear0 = (uint32)BcdToBin(6,MachineStatus.gear_y[0]) ; 
// 		uint32 gear1 = (uint32)BcdToBin(6,MachineStatus.gear_y[1]) ;
// 		mov = (long long)tmov*gear1/gear0;
// 	}
// 	else if(MachineStatus.Type == TYPE_635_835||MachineStatus.Type == TYPE_1635_1835){
// //		mov = mov *283/50 ;
// 		MUL48(283)
// 		DIV48(50) 
// 	}
// 	else if(MachineStatus.Type == TYPE_650_850){
// 		mov = (long long)tmov*100/547;
// 	}
// 	else{
// 		if (CHK_ROTW(AXIS_A)){
// 			mov = (long long)tmov*23463/(38400*2);	
// 		}
// 		else {
// 			mov = (long long)tmov*5/12;
// 		}
// 	}
// 	if(!sign){
// 		mov = -mov ;
// 	}
// 	return (mov*(1+UseEX5000)) ;		
}
#define MAX_DELAY 5 
short ChkAllMotorFinish (void)
{
// 	// return	1:-----all motor is stop
// 	//			  0:-----at least a motor running

// 	BYTE	axis, sign, ret;
// 	
// 	ret = 1;
// 	for( axis=0; axis < MachineStatus.axis_no; axis++ ){
// 		if(running_cnt[axis] < MAX_DELAY){
// 			running_cnt[axis] = running_cnt[axis]+1;
// 		}
// 		if( MachineStatus.motor[axis] && MachineStatus.running[axis]){
// 			unsigned char status = rDosMem(STATUS_ADDR(axis)) ;
// 			if (running_cnt[axis] < MAX_DELAY){
// 				ret=0 ;
// 				continue ;
// 			}
// 			else if(DDATbl[axis].totalms!=0 ){
// 			//if(DDATbl[axis].totalms!=0 ){
// 				ret=0 ;
// 				continue ;
// 			}
// 			MachineStatus.running[axis] = 0;
// 			if(axis == AXIS_Y){
// 				if((MachineStatus.wire_on) && (MachineStatus.PayOff != 1)){
// 			 		WireOnOff(0);
// 				}

// 				MachineStatus.axis_lval[axis] = MachineStatus.axis_val[axis];
// 				MachineStatus.sign[axis]	  = PLUS_SIGN;
// 				MachineStatus.axis_val[axis]  = 0;
// 			}
// 			else{
// 				//MachineStatus.dst_pos[axis]=MachineStatus.axis_val[axis] ;
// 				sign = (((SDWORD)MachineStatus.dst_pos[axis])<0)?MINUS_SIGN:PLUS_SIGN;
// 				MachineStatus.sign[axis] = sign;
// 				//MachineStatus.axis_val[axis] = dBinToBcd(6, ((SDWORD)MachineStatus.dst_pos[axis])*((sign&0x7f)==PLUS_SIGN?1:-1));
// 				MachineStatus.axis_val[axis] = MachineStatus.dst_pos[axis];
// 				//printf("%d__%d\n",axis,MachineStatus.axis_val[axis]);
// 			}
// 		}
// 	}
// 	
// 	//�ˬd�O�_�w�g�Ұʦ^���I(���ӬO���w���b...)
// 	/*
// 	for(BYTE axis = AXIS_Z ; axis < MachineStatus.axis_no ; axis++){
// 		if(EnableHomeInt_ZrtMode[axis] && (Get_Zrt_io(axis)==0)){	
// 			EnableHomeInt_ZrtMode[axis]= false ;
// 			HomeActive(axis) ;
// 		}
// 	}
// 	*/
// 	return( ret );
}
void Read_ZABCD_2016()
{
			for(int i=0 ; i < 5 ; i++){
				flag_ZRT_ZABCD[i]=false ;
				ZABCD_2016[i]=dReadAbsPos(AXIS_Z+i) ;
			}
}
			


bool check_setting()
{
// 	if(BcdToBin(3,MachineStatus.speed[MachineStatus.speed_mode]) ==0){
// //		ShowRPM_0() ;
// 		printf("speed_mode=0\n");
// 		return false;
// 	}
// 	for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis ++){
// 		if(MachineStatus.motor_grads[axis] == 0x0){
// //			ShowMotorGrads_0(axis) ;
// 		printf("motor_grads=0\n");
// 			return false;
// 		}
// 		if( (MachineStatus.Rate[axis] == 0x0)){
// //			ShowRate_0(axis) ;
// 		printf("Rate=0\n");
// 			return false ;
// 		}
// 		if( (MachineStatus.wZeroSpd[axis] == 0x0)){
// //			ShowZeroSpd_0(axis) ;
// 		printf("wZeroSpd=0\n");
// 			return false ;
// 		}
// 	}
// 	return true ;
}

short VerifyProg (short speed_mode, bool check_z,bool inReMakeActTable)
{
	short ret;
	WORD  errline;
	
//	Prog2Air(false) ;
	//�P�_���լO�_�s�b
//	fill_AutoHook_axis() ;
	//if( speed_mode == AUTO )  ret = VerifyAutoProg(&errline,check_z);
  //else					  ret = VerifyFastProg(&errline,check_z);

	if( ret != PROG_OK ){
		if(inReMakeActTable){
			flag_VerifyProg=true ;
			return(0) ;
		}
		INI_DISP_BUF();
		//Fill_pDispBuf(ProgLine[idx_language]);
		//pDispBuf_value += BinToStrBuf(3, errline, pDispBuf);
		//Fill_pDispBuf("\n");
		//if(ret == OVER_RPM_ERR){
		//	char buf[20];
		//	Fill_pDispBuf(AxisName[idx_language][OverRpm.axis]);
		//	Fill_pDispBuf(AxisSetTooLarge[idx_language]);
		//	sprintf(buf,"%ld",OverRpm.val) ;
		//	Fill_pDispBuf(buf);
		//	ADD_DOT_UNIT(OverRpm.axis) ;
		//	Fill_pDispBuf(")");
		//}
		//else{
		//	Fill_pDispBuf(err_mes[(ret-PROG_OK-1)*2+((idx_language==1)? 0:1)]);
		//}
		//if(ret !=PROG_LOOP_G6_ERR){
		//	Fill_pDispBuf(Error[idx_language]);
		//	Fill_pDispBuf("\n");
		//	Fill_pDispBuf("   ");
		//}
		//FILL_DISP_BUF(0);
		//DispMsgWin_q(-1, -1, ERR_WIN, DispBuf);
		if(ret == PROG_ZOFF_ERR){
			printf("�Шϥδ��ռҦ�");
		//	INI_DISP_BUF();
		//	Fill_pDispBuf("�Шϥδ��ռҦ�", 
		//				  " Please using test mode",
		//				  " Please using test mode");
		//	FILL_DISP_BUF(0);
		//	DispStrLine_q(250,255,RED_USR, LIGHTGRAY_USR,DispBuf) ;
		}
		WAIT_NEW_KEY();
		ClrMsgWin_q();
		ret = 0;
	}
	else{
		ret = 1;
	}

	return( ret );
}
void RunFastStart (void)
{
// // 	MachineStatus.run_state = CHK_FAST_POS;
}

void RunAutoStart (void)
{
// 	MachineStatus.run_state = CHK_AUTO_RUN;	
}

//�]�w�u�[�}��
void WireOnOff (BYTE on)
{
// 	MachineStatus.wire_on = on;
// 	if( on ){ 
// 		BOUTM |= MASK_BIT0;
// 	}
// 	else{ 
// 		BOUTM &= (~MASK_BIT0);
// 	}
// 	wDosMem(pc_base+OUTM , BOUTM) ;
}

void ChkStartWire (int32 mov)
{
	//if((MachineStatus.PayOff !=0)&& (MachineStatus.PayOff !=1)){
	//	WireOnOff((mov>=MachineStatus.PayOff ));
	//}
	//else if(MachineStatus.PayOff ==0) WireOnOff(1);//�s�u�[�[�t
	WireOnOff(1);
}

void ChkStopWire (void)
{
// 	SDWORD tval, set_val;
// 	//if((MachineStatus.PayOff !=0)&&(MachineStatus.PayOff !=1)){
// 	//if((MachineStatus.PayOff !=1)){//�s�u�[�[�t
// 		if( MachineStatus.wire_on ){
// 			set_val	= ReadReg3701(AXIS_Y, RD_VREG_3701);
// 			tval	= ReadReg3701(AXIS_Y, RD_YREG_3701);	//�u�[�[�t��new_accval�����D,���ª��覡
// 			//if(MachineStatus.WileMode==0){
// 				if( tval <= (set_val*(100-MachineStatus.WireTime)/100) ) 
// 					WireOnOff(0);
// 			//}
// 		}
// 	//}
}
#define	BASE_TIME	15							//
#define	RATIO			(int)(10000*16)			//
#define	FACTOR		1								//
#define	SPD(RPM)			 (DWORD)(BASE_TIME*RATIO*FACTOR/RPM)
// EXTERN	DWORD ZSpdTbl[]
// 		={
// 			SPD(10)	,																																												/* 000		  	*/
// 			SPD(10)	,SPD(15) ,SPD(20) ,SPD(25) ,SPD(30)	,SPD(35) ,SPD(40) ,SPD(45) ,SPD(50)	,SPD(55) ,			/* 001----010 */
// 			SPD(60)	,SPD(65) ,SPD(70) ,SPD(75) ,SPD(80)	,SPD(85) ,SPD(90) ,SPD(95) ,SPD(100),SPD(105),			/* 011----020 */
// 			SPD(110),SPD(115),SPD(120),SPD(125),SPD(130),SPD(135),SPD(140),SPD(145),SPD(150),SPD(155),			/* 021----030 */
// 			SPD(160),SPD(165),SPD(170),SPD(175),SPD(180),SPD(185),SPD(190),SPD(195),SPD(200),SPD(205),			/* 031----040 */
// 			SPD(210),SPD(215),SPD(220),SPD(225),SPD(230),SPD(235),SPD(240),SPD(245),SPD(250),SPD(255),			/* 041----050 */
// 			SPD(260),SPD(265),SPD(270),SPD(275),SPD(280),SPD(285),SPD(290),SPD(295),SPD(300),SPD(305),			/* 051----060 */
// 			SPD(310),SPD(320),SPD(330),SPD(340),SPD(350),SPD(360),SPD(370),SPD(380),SPD(390),SPD(400),			/* 061----070 */
// 			SPD(410),SPD(420),SPD(430),SPD(440),SPD(450),SPD(460),SPD(470),SPD(480),SPD(490),SPD(500),			/* 071----080 */
// 			SPD(510),SPD(520),SPD(530),SPD(540),SPD(550),SPD(560),SPD(570),SPD(580),SPD(590),SPD(600),			/* 081----090 */
// 			SPD(610),SPD(620),SPD(630),SPD(640),SPD(650),SPD(660),SPD(670),SPD(680),SPD(690),SPD(700),			/* 091----100 */
// 			SPD(702),SPD(704),SPD(706),SPD(708),SPD(710),SPD(712),SPD(714),SPD(716),SPD(718),SPD(720),			/* 101----110 */
// 			SPD(722),SPD(724),SPD(726),SPD(728),SPD(730),SPD(732),SPD(734),SPD(736),SPD(738),SPD(740),			/* 111----120 */
// 			SPD(742),SPD(744),SPD(746),SPD(748),SPD(750),SPD(752),SPD(754),SPD(756),SPD(758),SPD(760),			/* 121----130 */
// 			SPD(762),SPD(764),SPD(766),SPD(768),SPD(770),SPD(772),SPD(774),SPD(776),SPD(778),SPD(780),			/* 131----140 */
// 			SPD(782),SPD(784),SPD(786),SPD(788),SPD(790),SPD(792),SPD(794),SPD(796),SPD(798),SPD(800),			/* 141----150 */
// 	}
// ;
void virtual_move(bool in_isr )
{
// 	bool need_virtual_move = false ;
// 	for(BYTE axis= AXIS_Z ; axis < MAX_AXIS ; axis ++){
// 		if((virtual_zabc[axis].initial_move !=0) || (virtual_zabc[axis].last_move !=0)){
// 			if(flagSPIN_ZRT){
// 				if((need_virtual_move=(CHK_SPIN(axis))?true:false) ==true){
// 					break ;
// 				}
// 			}
// 			else{
// 				need_virtual_move= true ;
// 				break ;
// 			}
// 		}
// 	} 
// 	if(!need_virtual_move){
// 		return ;
// 	}
// 	dDelay(2) ;
// 	if(need_virtual_move&& !in_isr && !flagSPIN_ZRT){
// 		ShowToVirtualHome() ;
// 	}
// 	for(long l=0 ; l < LOOP_TIMES ; l++);
// 	for(long l=0 ; l < LOOP_TIMES ; l++);
// 	for(long l=0 ; l < LOOP_TIMES ; l++);
// 	//Z,A,B,C�b�O�_���������I
// 	for(BYTE axis= AXIS_Z ; axis < MAX_AXIS ; axis++){
// 		SDWORD move =virtual_zabc[axis].initial_move - virtual_zabc[axis].last_move ; 
// 		if((virtual_zabc[axis].flag)&& (move !=0)){
// 			SDWORD omove=move ;
// 			TO_GRID(axis,move) ;
// 			DWORD absmov=(move >0)? move : -move ;
// 			DWORD ref ;
// 			if(axis == slide_axis){			
// 				cal_zrtref(axis,ref) ;
// 				ref *=absmov ;
// 				ref /= MachineStatus.motor_grads[axis] ;
// 			}
// 			else{
// // 				ref=((long long)ZSpdTbl[MachineStatus.speed[MachineStatus.speed_mode]]*absmov)/(RATIO);
// 			}
// 			int sign =  (move >0 )? PLUS_SIGN:MINUS_SIGN ;
// 			Set3701(axis, sign, ref, absmov,absmov,true,0,0);

// 			uint8 ret ;
// 			while( 1 ){
// 				if(Chk3701(axis)) break;

// 				CHECK_RESET(true);
// 				// ���Z,A,B,C�b��
// 				if(IsTimeUp(timeout_DispCurAxis) ){
// 					DispMovAxis_q(axis);
// 					timeout_DispCurAxis= mTimerSet(MAX_DispCurAxis);
// 				}
// 				//while(exe_proc_queue()) ;
// 			}
// 			MachineStatus.sign[axis] = sign;
// 			if(omove < 0){
// 				omove = -omove ;
// 			}
// 			MachineStatus.axis_val[axis] = omove;//dBinToBcd(5,omove);
// 			DispCurAxis_q(1) ;
// 			//while(exe_proc_queue()) ;
// 		}
// 	} 
// 	if(need_virtual_move&& !in_isr && !flagSPIN_ZRT){
// 		dDelay(2) ;
// 		sendError(VirtualHome,0,3);
// 	}
}

void StartRun (WORD op_mode)
{	
// 	if(double_chk_is_first_a && CHK_ROTW(AXIS_A) && MachineStatus.motor[AXIS_A] && MachineStatus.ZrtMode[AXIS_A]!= MODE_ZRT_YA_ABS1){//����½�u���
// 		is_first_a=true;
// 		SoftReset();
// 	}
// 	else{
// 	first_dda=0;
// 	//if(!MachineStatus.XMINUS){			//X�b�ϦV
// 	//	for(int i=0;i<=MAX_PROG_LINE;i++){
// 	//		if(ProgBuf[i].bygcode==0)break ;
// 	//		if((ProgBuf[i].dval[START_X]&0x1000000)||(ProgBuf[i].dval[END_X]&0x1000000)){
// 	//			DispXMINUSError(); 
// 	//			return ;
// 	//		}
// 	//	}
// 	//}
// 	//if(op_mode!=STEP_MODE && NewH  && MachineStatus.bysafe_plugin && MachineStatus.safe_sw == SAFE_ON ){//���եi�Φw���˸m�\��
// 	//	if(safe_runtag==0){
// 	//		for(int i=0;i<49;i++){		//�w���˸m���M��
// 	//			safe_chk_1[i].safekey=safe_chk_2[i].safekey=safe_chk_3[i].safekey=safe_chk_4[i].safekey=safe_chk_5[i].safekey=safe_chk_6[i].safekey=safe_chk_7[i].safekey=safe_chk_8[i].safekey=0;
// 	//		}
// 	//		GenRatio_cnt=lKeySafe=chk_dumpsafe=lpos=safe_cnt=safe_cnt_1=safe_cnt_2=safe_cnt_3=safe_cnt_4=safe_cnt_5=safe_cnt_6=safe_cnt_7=safe_cnt_8=safedumpchk=Safe_dumpKey=Safe_onKey=chk_safe=chk_runsafe=0;	
// 	//		safe_runtag=1;
// 	//	}
// 	//	//else {SAFE_ON_new(MachineStatus.bysafe_plugin);
// 	//	//Sprintf("StartCollect__%d",safe_runtag);}
// 	//}

// 	//if(NewH &&MachineStatus.PRODDELAY){	//�Ĥ@���t�׻��W(�Ͳ�����)
// 		//Sprintf("start");
// 		first_dda=0;
// 		first_speed=0;	
// 	//}	
// #if NEW_FUN1
// 	idx_movy=0 ;
// 	idx_movy2=0 ;
// #endif
// 	//�ˬd�bFAST�Ҧ��U,����u�s�b
// 	//if(( MachineStatus.speed_mode == FAST ) && CHK_ROTW(AXIS_A) && MachineStatus.motor[AXIS_A]){
// 	//	//ShowNoFASTMode () ;
// 	//	return ;
// 	//}
// 	////�ˬd�����`���]�w -----���F���
// 	//if(!check_setting()){
// 	//	return ;
// 	//}
// 	
// 	//chkRUNDAYS_Over() ;
// //	ChgCursorLoc(PROG_CURSOR);
// 	//SetCursor(1);
// 	if( VerifyProg(MachineStatus.speed_mode,op_mode== RUN_MODE,0) ){
// //		SetSafeSwMode(SAFE_OFF);


// 		disable_all_touch() ; //****M*****
// 		


// 		struct TIMER time_out1=	mTimerSet(500);
// 		//if(AirScrn_ON){
// 		//	AirScrn_OFF();
// 		//	DispPageProg_q(CurProgLine);
// 		//	SetCursor(1);
// 		//}

// 		if(MovToZeroAll(1) ){
// 			//���^���I�ɶ��ܵu��,�G�[�J����,�H�O�Ҧw���}����8051�i�H����R�O
// 			while(!IsTimeUp(time_out1)) ;
// // 			for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis++){
// // 				if(NewH)DDATbl[axis].new_accval=0;
// // 			}
// 				to3701ms=0;chkcnt=ltotoms=0;
// 				cnt3701=0;keydump=1;
// 				tcurtime=0;tRatio=0;
// 				tRatio=0;
// 				tGenRatio=0;
// 				Ratiochk=0;

// 			//if( op_mode==STEP_MODE || MachineStatus.safe_sw==SAFE_OFF){	//���եi�Φw���˸m�\��
// 			//	SetSafeSwMode(SAFE_OFF);
// 			//	DispSafeSw_q(SAFE_OFF);
// 			//}
// 			//else{
// 			//	SetSafeSwMode(SAFE_ON);
// 			//	DispSafeSw_q(SAFE_ON);
// 			//}
// 			Read_ZABCD_2016() ;
// 			//switch( op_mode )
// 			switch( ModeTmp )
// 			{
// 			case RUN_MODE:
// //				ini_SaveRBuf() ;
// 				MachineStatus.op_mode = RUN_MODE;
// 				chg_newspeed((CHK_ROTW(AXIS_A))? 0:1) ;
// 				SetClock(RUN_CLOCK);
// //				DispWorkWin_q(0);
// //				DispRunWin_q();			
// 				break;
// 			case TEST_MODE:
// 				MachineStatus.op_mode = TEST_MODE;
// 				chg_newspeed((CHK_ROTW(AXIS_A))? 0:1) ;
// 				SetClock(TEST_CLOCK);
// //				DispTestWin_q(0);
// 				break;
// 			case STEP_MODE:
// 				MachineStatus.op_mode = STEP_MODE;
// 				SetClock(STEP_CLOCK);
// //				DispStepWin_q(0);
// 				MachineStatus.safe_sw = SAFE_OFF;
// 				break;
// 			}
// 			SendStatus();
// 			//set_FEEDER() ;
// 			// dDelay(3);

// 			SetAllGain(MachineStatus.gain_val, 0);
// 			
// 			//DispMissNo_q();

// 			InitRunVar();
// 			if(MachineStatus.op_mode==STEP_MODE){
// 				SetClock(RUN_CLOCK) ;
// 			}
// 			if( REAL_FAST ){
// //				MakeFastActTbl(!(MachineStatus.op_mode&RUN_MODE));
// //				virtual_move(false) ;
// 				RunFastStart();
// 			}
// 			else{
// //				MakeAutoActTbl(!(MachineStatus.op_mode&RUN_MODE));
// 				sort_airtbl();
// 				virtual_move(false) ;
// 				RunAutoStart();
// 			}
// 			if(MachineStatus.op_mode==STEP_MODE){
// 				SetClock(STEP_CLOCK) ;
// 			}
// 			else if(MachineStatus.op_mode== TEST_MODE){
// 				//MakeAutoActTbl(1);  //���մ��ըS�ʧ@
// 				timeout_ADC= mTimerSet(TIMER_ADC) ;
// 				MachineStatus.set8254=1 ;
// 				update_sc(1) ;
// 			}
// 			//EnableHomeInt(AXIS_X);
// 			if(MachineStatus.op_mode == RUN_MODE){
// 				if(FlagRun1){
// 					KeyStop() ;
// 				}
// 			}

// 		SendStatus();
// 		MachineStatus.cur_miss = 0;
// 		//TxBuf[0]=curmiss ;	
// 		//for(int i =0;i<2;i++){
// 		//	TxBuf[2-i]=0;
// 		//}
// 		//	Tx(UART2,TxBuf,3) ;
// 		}
// 		else{
// 			//if( MachineStatus.safe_sw == SAFE_TEST )  SetSafeSwMode(SAFE_TEST);
// 		}
// 		flag_run=true ;
// 		//timeout_DispCurAxis= mTimerSet(MAX_DispCurAxis);
// 	}
// 	}
}

#define CHK_TIMES				20
void ShowTouchTest (BYTE b)
{
// 	WORD i;
// 	sendError(TouchTest,b,3);//���w����
// 	printf("touch%d_",b);
// 	
// 	MachineStatus.th_test = 0;
// 	for( i=0; i<CHK_TIMES && !MachineStatus.th_test && (KeyBufRIdx == KeyBufWIdx); i++ ){
// 		dDelay(1);
// 	}
// 	sendError(TouchTest,b+4,3);//���w���ջ��M��
// 	//ClrMsgWin_q();
// 	enable_all_touch() ;
}
void TouchErrStop (void)
{
// 	//char *touch_err[]={ " Touch Miss !" ,
// 	//										" �� �w �� �~ !" } ;
// 	PauseClock(MachineStatus.op_mode);

// 	//INI_DISP_BUF();
// 	//Fill_pDispBuf(	" �� �w ", 
// 	//								" Touch " ,
// 	//								" SCHIACCIARE ");
// 	//pDispBuf_value += BinToStrBuf(1, MachineStatus.th_stop, pDispBuf);
// 	//Fill_pDispBuf(	" �� �~", 
// 	//			  				" Miss" ,
//   //            		" Miss");
//   if (MachineStatus.touch_before_err){
//   	MachineStatus.touch_before_err = false;
// 		if( MachineStatus.dcur_th[0] ||MachineStatus.dcur_th[2] )
// 			SendTouch(Cmd_Touch1,1,MachineStatus.axis_val[AXIS_Y]);
// 		else if( MachineStatus.dcur_th[0] ||MachineStatus.dcur_th[2] )
// 			SendTouch(Cmd_Touch1,2,MachineStatus.axis_val[AXIS_Y]);
// 		
// 	//	Fill_pDispBuf(	"(�e)",
// 	//			  					"(Before Touch)" ,
//   //            			"(Before Touch)");
// 	}
// 					  
// 	WAIT_RUN_TEST_KEY(ERR_WIN,TouchError);
// 	MachineStatus.th_stop = 0;
// 	//ClrMsgWin_q();

// 	RestoreClock(KeyTmp);
}
/*
void DumpActTbl(int e)
{
	FILE *fp ;
	int i ;

	fp = FOPEN("Acttbl.txt","w") ;
	//DumpFile(fp) ;
	fprintf(fp," Length = %d\n",e) ;
	for(i=0 ; i < e ; i++){
		if (ActTbl[i].cmd == UPDATE_LINE){
			fprintf(fp,"\n") ;
			fprintf(fp,"\n") ;
			fprintf(fp,"\n") ;
		}
		fprintf(fp,"%04d %s(0x%x)",i,StrActTbl[ActTbl[i].cmd],ActTbl[i].cmd) ;
		switch(ActTbl[i].cmd)
		{
		case MOVE_X :
		case MOVE_Y :
		case MOVE_Z :
		case MOVE_A :
		case MOVE_B :
		case MOVE_C :
		case MOVE_D :
		case MOVE_E :
		case MISS_X :
		case MISS_Y :
		case MISS_Z :
		case MISS_A :
		case MISS_B :
		case MISS_C :
		case MISS_D :
		case MISS_E :
		case LOOP_X :
		case LOOP_Y :
		case LOOP_Z :
		case LOOP_A :
		case LOOP_B :
		case LOOP_C :
		case LOOP_D :
		case LOOP_E :
		case INCY :
		case ZRT_Z :
		case ZRT_A :
		case ZRT_B :
		case ZRT_C :
		case ZRT_D :
		case ZRT_E :
			fprintf(fp,"    ms = %l5d  idms=%l3d step = %l8d loop_ms = %l5d loop_step=%l8d dst_pos=%l8d chk_pos=%ld brk=%l6d test_ms=%l5d",
			ActTbl[i].ref,ActTbl[i].idms, ActTbl[i].mov, ActTbl[i].loopref, ActTbl[i].loopmov, ActTbl[i].u.dst_pos, ActTbl[i].sdchk_pos, ActTbl[i].break_cnt, ActTbl[i].spd_th.ref) ;
			break ;

		case LOOP_CHECK :
		case LOOP_END :
		case MID_CHK :
		case END_ACT :
		case NULL_ACT_CMD :
			break ;
		
		}
		fprintf(fp," next=%d\n",ActTbl[i].next) ;
	}
	FCLOSE(fp) ;
}
*/
/*
void DumpFile(FILE *fp)
{
	int line;

	MakeEditTitleStr(false) ;
	fprintf(fp,(char *)DispBuf) ;
	fprintf(fp,"\n") ;
	for(line=0 ;  ; line++){
		MakeProgLine(line,(ProgType_t *)&ProgBuf[line],(ProgTypeExlarge_t *)&ProgBufExlarge[line]) ;
		Filter_CHG_PAL() ;
		fprintf(fp,(char *)DispBuf) ;
		fprintf(fp,"\n") ;
		if(ProgBuf[line].bygcode==0)break ;
	}
}
*/
