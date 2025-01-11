#include "header.h"
#define COMNO		2
#define ON			1
#define OFF			0
#define RS_BUF_MAX			0x500
#define TR_BUF_MAX			0x50
#define RBR_8250			0
#define THR_8250			0
#define IER_8250			1
#define IIR_8250			2
#define LCR_8250			3
#define MCR_8250			4
#define LSR_8250			5
#define MSR_8250			6
#define DLL_8250			0
#define DLM_8250			1
#define BASED_8259A 		0x20
#define EOI 				0x20
#define comm_port 0
//#define DI		 asm		cli ;
//#define EI		 asm		sti ;

static UC mask_8259a[]= { 0xef , 0xf7 , 0xdf } ;/* irq4  , irq3 , irq5 */
static UI rs_buf_ridx[COMNO] , rs_buf_widx[COMNO] , rs_buf_len[COMNO] ;// rs: receiver tr:transmitter
UI tr_buf_ridx[COMNO] , tr_buf_widx[COMNO] , tr_buf_len[COMNO] ;
static UC huge rs_buf[COMNO][RS_BUF_MAX] ;
UC huge tr_buf[COMNO][TR_BUF_MAX] ;
static UC tr_flg[COMNO] , rs_flg[COMNO] ;
static UC cts_flg[COMNO] , rts_flg[COMNO] ;

void New_Tx(unsigned char TxBuf[])
{
	UART_Write(UART1, TxBuf, 1);
}
uint32 TxTest(unsigned char TxBuf[])
{
	return UART_Write(UART1, TxBuf, 3);
}

void wr_rs232(UC ch)
{	
	TxBuf[0]=ch;
	New_Tx(TxBuf);
	//d();
	/*
	while(tr_buf_len[comm_port] == TR_BUF_MAX){
	}
	tr_buf[comm_port][tr_buf_widx[comm_port]++] = ch ;
	if(tr_buf_widx[comm_port] == TR_BUF_MAX){
		tr_buf_widx[comm_port] = 0 ;
	}
	
	tr_buf_len[comm_port]++ ;
	if((cts_flg[comm_port] == ON) && (tr_flg[comm_port] == OFF)){
		
		tr_flg[comm_port] = ON ;
		outportb(rs232_base[comm_port] + IER_8250 , 0x0b) ;
	}
	*/
}
// keyKind---按鍵種類
// 0---------手動按鍵+x,-x,+y,-Y...
// 1-----較慢的重複時間間隔往左,往右....
// 2-----單鍵(沒有重複功能)
void GenKeyKind()
{
	for(int i=0 ; i < 256 ; i++){
		KeyKind[i]=2 ;
	}
	KeyKind[KEY_UP]=1 ;
	KeyKind[KEY_DOWN]=1 ;
	KeyKind[KEY_LEFT]=1 ;
	KeyKind[KEY_RIGHT]=1 ;
	KeyKind[KEY_PG_UP]=1 ;
	KeyKind[KEY_PG_DOWN]=1 ;
	
	KeyKind[KEY_HAND_LEFT]=0 ;
	KeyKind[KEY_HAND_RIGHT]=0 ;
	KeyKind[KEY_PLUS_X]=0 ;
	KeyKind[KEY_PLUS_Y]=0 ;
	KeyKind[KEY_PLUS_Z]=0 ;
	KeyKind[KEY_PLUS_A]=0 ;
	KeyKind[KEY_PLUS_B]=0 ;
	KeyKind[KEY_PLUS_C]=0 ;
	KeyKind[KEY_PLUS_D]=0 ;
	KeyKind[KEY_PLUS_E]=0 ;
	
	KeyKind[(unsigned char )KEY_MINUS_X]=0 ;
	KeyKind[KEY_MINUS_Y]=0 ;
	KeyKind[KEY_MINUS_Z]=0 ;
	KeyKind[KEY_MINUS_A]=0 ;
	KeyKind[KEY_MINUS_B]=0 ;
	KeyKind[KEY_MINUS_C]=0 ;
	KeyKind[KEY_MINUS_D]=0 ;
	KeyKind[KEY_MINUS_E]=0 ;
}	
void y_suspendLED()
{
	//if(NewH &&KeyLockCHG)
// 		wr_rs232(4) ; wr_rs232(5) ; wr_rs232(MachineStatus.y_suspend?1:0) ;
		
}
void AxisLED(uint8 axis)
{
// 	if(axis >= AXIS_Y){
// 		uint8 ledno= axis-AXIS_Z+8 ;
// 		/*
// 		TxBuf[0]=4;
// 		TxBuf[1]=ledno;
// 		TxBuf[2]=MachineStatus.motor[axis]?1:0;
// 		New_Tx(TxBuf);
// 		*/
// 		wr_rs232(4) ; wr_rs232(ledno) ; wr_rs232(MachineStatus.motor[axis]?1:0) ;
// 		//d();
// 	}
}

void Adjust_AZero_NewH(void)
{
// 	move_rotate_left_right(ROTATE_ZRT_GRID) ;
// 	
// 	
// 	
// 	
// 	MachineStatus.dst_pos_sign[AXIS_A]= PLUS_SIGN ;
// 	MachineStatus.dst_pos[AXIS_A]= 0 ;
// 	while(!Chk3701(AXIS_A)){
// 		DispMovAxis_q(AXIS_A);
// 		//while(exe_proc_queue()) ;
// 	}
// 	//等待走到定點
// 	WORD dif_a;
// 	do{
// 		WORD lcur_a = (WORD)wRead2016(AXIS_A) ;
// 		tickDelay(50) ;
// 		WORD cur_a=(WORD)wRead2016(AXIS_A) ;
// 		dif_a= (cur_a > lcur_a)? cur_a-lcur_a : lcur_a-cur_a ;
// 	}
// 	while(dif_a >= 1) ;


// 	MachineStatus.dst_pos_sign[AXIS_A]= MachineStatus.sign[AXIS_A] ;
// 	MachineStatus.dst_pos[AXIS_A]= MachineStatus.axis_val[AXIS_A] ;
// 	move_rotate_right_left( ROTATE_ZRT_GRID+600) ;
// 	EnableHomeInt(AXIS_A,BITmask[7-AXIS_A],ENABLE_STOP) ;
// 	ClrKeyBuf();
// 	while(!ChkDriverClear((uint8)AXIS_A) ){
// 		DispMovAxis_q(AXIS_A);
// 		//while(exe_proc_queue()) ;
// 		if(CHK_KEY())SoftReset() ;
// 	}
// 	DisableHomeInt(AXIS_A,0) ;
// 	DDATbl[AXIS_A].totalms=0 ;
// 	cnt_Set3701=0 ;
// 	ResetDriverClear() ;
}
void DispManualSet_q(void)
{
	sendError(ManualSet,1,3);
		//DispMsgWin_q(-1, -1, MSG_WIN, "按-A或+A導引翻線回原點!" ,
		//							  "Press -A or +A Make ROTW-Axis Go Home !",
		//							  "Press -A or +A Make ROTW-Axis Go Home !");
}
void AB_manual_to_zero_NewH(bool &is_first_a)
{
// 	if(CHK_ROTW(AXIS_A) && is_first_a && MachineStatus.motor[AXIS_A] && MachineStatus.ZrtMode[AXIS_A]!= MODE_ZRT_YA_ABS1){
// 											printf("AB_manual_to_zero\n");
// 		//is_first_a=false ;
// 		DispManualSet_q() ;
// 		
// 		
// 		EnableHomeInt(AXIS_A,BITmask[7-AXIS_A],ENABLE_STOP)  ; // 設定外接原點A亮燈時,使得A軸煞車
// 		char last_key ;
// 		if(!ChkDriverClear((uint8)AXIS_A)){
// 			do{
// 				while( (KeyBufRIdx == KeyBufWIdx)){
// 					static uint8 vdriverCLear=0 ;
// 					static int cnt =0 ;
// 					uint8 tt=rDosMem(pc_base+DriverClear) ;
// 					ngetkey() ;
// 					chk_off_power(0) ;
// 					update_run_DDA() ;
// 					//update_roll_q() ;
// 					//FORCE_PROC_QUEUE
// 				}

// 				update_run_DDA() ;
// 				//FORCE_PROC_QUEUE
// 				if(set_ScrnSav()){
// 					continue ;
// 				}
// //				CalNextManMov() ;
// 				if(DDAState ==0 && STEP_DDAState==0){
// 					char code ;
// 					//if(bioskey(1)){
// 					//	prokeycode=code= bioskey(0) ;
// 					//}
// 					//else{
// 						prokeycode=code=GetKey();
// 					//}
// 					if(code==KEY_HELP)is_first_a=false ;//按help解除翻線手動回原點
// 					if( Reset )SoftReset();
// 					if((code == (KEY_PLUS_A)) || (code == (KEY_MINUS_A))){
// //						DISABLE() ;
// 						in_AB_manual = true;
// 						last_key= code ;
// 						last_key;
// 						if(code == (KEY_PLUS_A)){
// 							
// 							MANMOV_AXIS((AXIS_A), PLUS_SIGN, (KEY_PLUS_A),AXIS_A_REPEAT,0,0);
// 							
// 						}
// 						else{
// 							
// 							MANMOV_AXIS((AXIS_A), MINUS_SIGN,(KEY_MINUS_A),AXIS_A_REPEAT,0,0);
// 							
// 						}
// 						in_AB_manual = false;
// //						ENABLE() ;
// 					}
// 				}
// 			}
// 			while(!ChkDriverClear((uint8)AXIS_A));
// 		}
// 		DDAState=0 ;
// 		DisableHomeInt(AXIS_A,0)  ; // 關掉外接原點A亮燈時,使得A軸煞車
// 		ResetDriverClear() ;


// 		{
// //			DisableHomeInt(AXIS_A) ;
// 			//ClrMsgWin_q();
// 			
// 				dDelay(2) ;
// 			sendError(ManualSet,0,3);
// 			//尋找右邊的原點
// 			
// 				dDelay(2) ;
// 			sendError(AutoHome,1,3);
// 			//DispMsgWin_q(-1, -1, MSG_WIN, "自動回原點中....." ,
// 			// 							  " Automatic Go Home .... ",
// 			// 							  " Automatic Go Home .... ");
// 										  
// 			//FORCE_PROC_QUEUE
// 			
// 			
// 			Adjust_AZero_NewH() ;
// 			set_zrt_power_on(AXIS_A) ;
// 		}
// 		sTimerSet(10) ;
// 		ClrKeyBuf() ;
// 		
// 		//ClrMsgWin_q();
// 		
// 		MachineStatus.sign[AXIS_A]	   = PLUS_SIGN;
// 		MachineStatus.axis_val[AXIS_A] = 0;
// 		DispCurAxis_q(1);
// 		//FORCE_PROC_QUEUE
// 		Clr2016s(AXIS_A) ;
// 		//is_first_a=false ;	//翻線未回原點按Reset會重複手動導引回原點
// 			double_chk_is_first_a=false;//關閉翻線手動
// 			is_first_a=false;
// 		dDelay(2) ;
// 		sendError(AutoHome,0,3);
// 	}
}

void move_rotate(int total , BYTE rotate_dir) 
{
	long ref = total *2 ;
	Set3701(AXIS_A, rotate_dir, ref , total,total,true,0,0);
}
void move_rotate_left_right( int total)
{
	move_rotate(total,PLUS_SIGN) ;
}
void move_rotate_right_left(int total)
{
	move_rotate(total,MINUS_SIGN) ;
}
