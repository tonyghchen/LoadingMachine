/**************************************************************************//**
 * @file     main.cpp
 * @version  V1.00
 * @brief    PYT-180 Firmware
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#define GLOBAL
#include "header.h"
#include "NuMicro.h"
#include "pyt-180.h"
#include "app_config.h"
#include "ec.h"
#include "EtherCatInterface.h"

void fakepara();
void Test_input();
bool set_ScrnSav();
void RecevieParam();
void test_hardware();
void Test_IO(uint8 keycode);
void showEtherCatInfo();

//uint8 TxBuf[10];
//uint8 RxBuf[80];	
uint8 Rtemp[40];	
static int Cnt= 0;
bool StartRecActtbl;

int ActtblIdx;
int ReceiveIdx;
//BYTE Recacttbl[50];

//UC *pacttbl;
SerialCom Com2;
SerialCom Com1;



struct TEST {
		BYTE b ;
		unsigned short w ;
    int l ;
} ;
void test1_SRAM()
{
	
	uint32_t  tid=1 ;
	RTT("tid=%d 10000 SRAM_WRITE16(i+0x100, i+value1)",tid) 
	TRACE_TASK_START(tid);
	unsigned short 	value1 = 0x1234;
	for(int i=0; i <10000 ; i++){
		SRAM_WRITE16(i+0x100, i+value1);
	}
	TRACE_TASK_END(tid++) ;
	
	RTT("tid=%d 10000 SRAM_WRITE16(i+0x101, i+value1)",tid) 
	TRACE_TASK_START(tid);
	for(int i=0; i <10000 ; i++){
		SRAM_WRITE16(i+0x101, i+value1);
	}
	TRACE_TASK_END(tid++) ;
	
	RTT("tid=%d 10000 SRAM_WRITE8(i+0x101, i+value1)",tid) 
	TRACE_TASK_START(tid);
	for(int i=0; i <10000 ; i++){
		SRAM_WRITE8(i+0x101, i+value1);
	}
	TRACE_TASK_END(tid++) ;
	
	
	RTT("tid=%d 10000 value1+=SRAM_READ16(i+0x100)",tid) 	
	TRACE_TASK_START(tid);
	for(int i=0; i <10000 ; i++){
		value1+=SRAM_READ16(i+0x100);
	}
	TRACE_TASK_END(tid++) ;

	RTT("tid=%d 10000 FPGA_WRITE8(0XC00, i+value1)",tid) 	
	TRACE_TASK_START(tid);
	for(int i=0; i <10000 ; i++){
			FPGA_WRITE8(0XC00, i+value1) ;
	}
	TRACE_TASK_END(tid++) ;

	RTT("tid=%d 10000 tt[i]=i+value1",tid) 	
	TRACE_TASK_START(tid);
  unsigned short tt[1000] ;
  for(int i=0; i < 10000 ; i++){
		tt[i%1000]=i+value1 ;
	}
	TRACE_TASK_END(tid++) ;
	

	RTT("tid=%d 10000 value1+=tt[i%1000]",tid) 	
	TRACE_TASK_START(tid);
  for(int i=0; i < 10000 ; i++){
		value1+=tt[i%1000] ;
	}
	TRACE_TASK_END(tid++) ;
		
	
	unsigned short 	value = 0x1234;
	SRAM_WRITE16(0x100, value);
	RTT("\nWritten= %x, Read= %x %x\r\n", value, SRAM_READ16(0x100),*SRAM_PTR(unsigned short,0x100));
	value = 0x5678;
	SRAM_WRITE16(0x102, value);
	RTT("Written= %x, Read= %x\r\n", value, SRAM_READ16(0x102));
	value = 0x9ABC;
	SRAM_WRITE16(0x104, value);
	RTT("Written= %x, Read= %x\r\n", value, SRAM_READ16(0x104));
	value = 0xdef0;
	SRAM_WRITE16(0x106, value);
	RTT("Written= %x, Read= %x\r\n", value, SRAM_READ16(0x106));
	for(int i=0 ; i < 8 ;i++){
		RTT("addr=%x--->%x\n",0x100+i,SRAM_READ8(0x100+i)) ;
	}
	RTT("0x101w=%x 0x103w=%x 0x105w=%x , 0x101L=%x,0x103L=%x\n", SRAM_READ16(0x101),SRAM_READ16(0x103),SRAM_READ16(0x105),SRAM_READ32(0x101),SRAM_READ32(0x103)) ;
	SRAM_WRITE32(0x101,0x76543210) ;
	RTT("execute...SRAM_WRITE32(0x101,0x76543210) \n") ;
	for(int i=0 ; i < 8 ;i++){
		RTT("addr=%x--->%x\n",0x100+i,SRAM_READ8(0x100+i)) ;
	}
	RTT("0x101w=%x 0x103w=%x 0x105w=%x , 0x101L=%x,0x103L=%x\n", SRAM_READ16(0x101),SRAM_READ16(0x103),SRAM_READ16(0x105),SRAM_READ32(0x101),SRAM_READ32(0x103)) ;
	
	RTT("sizeof(struct TEST)=%d TEST.b=%x TEST.w=%x TEST.l =%x \n",sizeof(struct TEST) , SRAM_PTR(struct TEST ,0x101)->b,SRAM_PTR(struct TEST ,0x101)->w,SRAM_PTR(struct TEST ,0x101)->l) ;
	
	
	TRACE_MSG("Hit any key to continue\n 1Mbyte RAM TEST ...");
	int ch =WAIT_KEY() ;
	TRACE_MSG("code=%x\n",ch);
	
	//
	//先將1Mbytes內每個記憶體位置填入不一樣數值(將高16bits和低16bits做互斥或)後,再讀出一一比對
	//
	for (int i = 0; i < 0x100000 ; i+=2){
		int data=(i>>16)^(i&0xffff) ;  //每個記憶體位置填入不一樣數值=將高16bits和低16bits做互斥或
		  SRAM_WRITE16(i,0) ;
			SRAM_WRITE16(i, data);
	}
	bool ok=true ;
	for (int i = 0; i < 0x100000 ; i+=2){
		if((i%0x10000)==0){
			TRACE_MSG("test address=0x%x~0x%x\n",i,i+0xffff) ;
		}
		int data=(i>>16)^(i&0xffff) ;
		if(data != SRAM_READ16(i)){
			ok=false ;
			TRACE_MSG("error address=%x data=%x right data=%x\n",i,SRAM_READ16(i),data) ;
			break ;
		}
	}
	if(ok){
		 TRACE_MSG("test OK!\n") ;
	}
}
bool CHK_KEY()
{
	//FORCE_PROC_QUEUE
	//update_roll_q() ;
	if(NewH){
		update_run_DDA() ;
	}
	//if( (KeyBufRIdx == KeyBufWIdx) && (bioskey(1)==0) ){
	//	return(false) ;
	//}
	//else{
		if(set_ScrnSav()){
			return(false) ;
		}
		BYTE code = KeyBuf[KeyBufRIdx];
		if(	KeyBufRIdx+1 >=	MAX_KEY_BUF	)	KeyBufRIdx = 0;
		else								KeyBufRIdx++;
		if(code == KEY_DUMMY_RESET){
			return(true) ;
		}
		else{
			return(false) ;
		}
	//}
}

bool set_ScrnSav()
{/*
	if(KeyBufRIdx != KeyBufWIdx){
		if(KeyBuf[KeyBufRIdx]==0){ //執行中touch到會在rs232上產生0的碼
			ClrKeyBuf() ;
			return true ;
		}
	}
	bool flag = false ;
	if((MachineStatus.flg_ScrnSav) && (KeyBufRIdx != KeyBufWIdx)){
		MachineStatus.flg_ScrnSav= false ;
		//重繪螢幕畫面
		SystemOn_q() ;
		ClrKeyBuf();
		flag= true ;
	}
	if(MachineStatus.ScrnSav!=0){
		timeout_ScrnSav= minTimerSet(BcdToBin(2, MachineStatus.ScrnSav)) ;
	}*/
	bool flag = false ;
	if(Reset)
		SoftReset();
	return flag ;
}
void test_hardware()
{
	wr_rs232(4);wr_rs232(0) ; wr_rs232(2) ;
	d() ;
	//wr_rs232(4); wr_rs232(0xff) ; wr_rs232(0) ;	//Ū����L���A
	//d() ;


	for(int i=0; i < 400 ; i++){
		d() ;
	}
	//while(cnt <  0x500000){
	//	if(KeyLockCHG){
	//		break ;
	//	}
	//	cnt++ ;
	//}
	if(NewH){
		wr_rs232(4);wr_rs232(0) ; wr_rs232(0) ;
	}
	for(int i=0; i < 10 ; i++){
		d() ;
	}

}
int get_num_RTT()
{
	int num=0 ;
	while(1){
		int ch =WAIT_KEY() ;
		MSG_RTT("%c",ch) ;
		if((ch >='0')&& (ch <='9')){
			num*=10 ;
			num+=(ch-'0') ;
		}
		else{
			break;
		}
	}
	return(num) ;
}
int get_PPR(int axis)
{
	for(int i=0 ;i < no_stDriverTable ;i++){
		if(gstProcessState.u32Vid[axis]==stDriverTable[i].u32Vid){
			 return(stDriverTable[i].u32PPR) ;
		}
	}
}
void UART_Write_Buf(UART_T* uart,uint8_t txbuf[],uint32_t no)
{
	if(uart == UART1){
		for(int i=0 ; i <no ;  i++){
			SRAM_WRITE8(TxCmdBuf1+wTxCmdBuf1,txbuf[i] ) ; 
			INC_idxCmdBuf(wTxCmdBuf1);
		}
		//Trigger TXE interrupt
		if(!(uart->INTEN&UART_INTEN_THREIEN_Msk)){
			UART_EnableInt(uart,UART_INTEN_THREIEN_Msk) ;
		}
	}
}
struct UART_CMDTBL{
	uint8_t   cmd ;
	uint8_t   length ;
} ;
uint8_t UART_cmdbuf[40] ;
struct UART_CMDTBL UART_cmdtbl[]={
	{0xc0,10} ,
	{0xc3,1} ,
	{0xd0,19} ,
	{0x2a,1} ,
	{0x2b,1} ,
	{0,0}  //結束
}
int UART_Complete()
{
		if(rRxCmdBuf1!= wRxCmdBuf1){
			// rsapberry PI 有送資料來
			uint8_t  cmd=SRAM_READ8(RxCmdBuf1+rRxCmdBuf1) ;
			for(int i=0 ;UART_cmdtbl[i].cmd !=0 ; i++){
				if(cmd== UART_cmdtbl[i].cmd){
					  int len ;
						if(wRxCmdBuf < rRxCmdBuf){							
								len=wRxCmdBuf+MAX_CMD_BUF-rRxCmdBuf ;
						}																		
						else{																
								len=wRxCmdBuf-rRxCmdBuf ;						
						}
            if(len >= (UART_cmdtbl[i].length+1)){
							// 有一個完整的命令
							for(int i=0 ; i < len ; i++){
								rd1_1(UART_cmdbuf[i]) ;
							}
							return(UART_cmdbuf[0]) ;
						}
						else{
							return(0) ;
						}
				}
			}
			// error cmd 
			rd1_1(UART_cmdbuf[0]) ;
			return(UART_cmdbuf[0]) ;
		}
		rertun(0) ;
}
		
int main (void)
{
	//變數初始化
	wRxCmdBuf1=rRxCmdBuf1=wTxCmdBuf1=rTxCmdBuf1=0 ;
	
#ifdef TEST_SYNC
	Sync.run=false ;
#endif
	
	
#ifdef TEST_BREAK
	Break.flag=false ;
#endif	
#ifdef TEST_BREAK_PULSE
		Touch.flag=0;
		Touch.cnt=0;
	  Touch.idx_ddacnt=0 ;
#endif	
	Config_Hardware(APP_SPI_CLOCK);
	FPGA_WRITE8(0XC00, 0X0) ;
	
	
#if !(TEST_BREAK_PULSE)
	for(uint8_t i=0 ; i < MAX_DRIVER ;i++){
		gstProcessState.u32DisPos[i]=0 ;
	}
	EtherCatMasterInit(APP_SPI_CLOCK);
	RTT("gstProcessState.u8RunMode=%d\n",gstProcessState.u8RunMode) ;
	RTT("gstProcessState.u32RunCounter=%d\n",gstProcessState.u32RunCounter) ;
	RTT("gstProcessState.u32MatchCounter=%d\n",gstProcessState.u32MatchCounter) ;
	RTT("gstProcessState.u8DriverCnt=%d\n",gstProcessState.u8DriverCnt) ;
	uint32_t u32Vid, u32Pid , Pos;
  for (int nDriver=0; nDriver < gstProcessState.u8DriverCnt; nDriver++){        
      EtherCatGetVidPid(nDriver, &gstProcessState.u32Vid[nDriver], &gstProcessState.u32Pid[nDriver]);
		  RTT("Driver=%d,u32Vid=%x, u32Pid=%x\n",nDriver,gstProcessState.u32Vid[nDriver], gstProcessState.u32Pid[nDriver]) ;
//      EtherCatGetActualPos(nDriver+1, &Pos);
//		  printf("driver current pos=%x\n",Pos) ;
	}
	RTT("gstProcessState.u8DOutCnt=%d\n",gstProcessState.u8DOutCnt) ;
	RTT("gstProcessState.u8DInCnt=%d\n",gstProcessState.u8DInCnt) ;
#endif
#if (!TEST_BREAK_PULSE)&&(!TEST_SDO) 	
				EtherCatMasterRunning();
#endif
		
#ifdef TEST_TOUCH_PROBE		
	FPGA_WRITE8(0XC00, 0X0) ;
	RTT("Test Touch Probe\n") ;  
	while(1){
		int ch =WAIT_KEY() ;
		MSG_RTT("%c",ch) ;
		FPGA_WRITE8(0XC00, 0Xff) ;
		RTT("Trigger 1\n") ;
		ch =WAIT_KEY() ;
		MSG_RTT("%c",ch) ;
		FPGA_WRITE8(0XC00, 0X0) ;
		RTT("Trigger 0\n") ;
	}
	
#endif
#ifdef TEST_SDO
		MSG_RTT("Test SDO\n") ;
		uint32_t loc,t1=0x12345678;
		uint16_t tp=1;
		while(1){
				uint32_t u32,loc ;
				uint16_t  u16 ;
			  uint8_t   u8 ;
				EtherCatSlaveSdoRead(0,0x607a,0,4,(uint8_t *)&u32) ;
			  loc=u32 ;
			  MSG_RTT("Target Position 607a = %x\n",u32) ;
			  TRACE_MSG("Target Position 607a = %x\n",u32) ;
				EtherCatSlaveSdoRead(0,0x6040,0,2,(uint8_t *)&u16) ;
			  MSG_RTT("Controlword_6040 = %x\n",u16) ;
			  TRACE_MSG("Controlword_6040 = %x\n",u16) ;
				EtherCatSlaveSdoRead(0,0x6041,0,2,(uint8_t *)&u16) ;
			  MSG_RTT("Statusword_6041 = %x\n",u16) ;
			  TRACE_MSG("Statusword_6041 = %x\n",u16) ;
				EtherCatSlaveSdoRead(0,0x60b8,0,2,(uint8_t *)&u16) ;
			  MSG_RTT("Touch_Probe_function_60b8 = %x\n",u16) ;
			  TRACE_MSG("Touch_Probe_function_60b8 = %x\n",u16) ;
			
			
				EtherCatSlaveSdoRead(0,0x1c12,0,1,(uint8_t *)&u8) ;
			  MSG_RTT("0x1c12 0 b = %x\n",u8) ;
			  TRACE_MSG("0x1c12 0 b = %x\n",u8) ;
			
				EtherCatSlaveSdoRead(0,0x1c12,1,2,(uint8_t *)&u16) ;
			  MSG_RTT("0x1c12 1 w = %x\n",u16) ;
			  TRACE_MSG("0x1c12 1 w = %x\n",u16) ;
				uint16_t a1600=u16 ;
				EtherCatSlaveSdoRead(0,a1600,0,1,(uint8_t *)&u8) ;
			  MSG_RTT("0x%x 0 b = %x\n",a1600,u8) ;
			  TRACE_MSG("0x%x 0 b = %x\n",a1600,u8) ;
				for(int i=1 ; i < u8+1 ; i++){
					EtherCatSlaveSdoRead(0,a1600,i,4,(uint8_t *)&u32) ;
					MSG_RTT("0x%x %d l = %x\n",a1600,i,u32) ;
					TRACE_MSG("0x%x %d l = %x\n",a1600,i,u32) ;
					
				}
			
				EtherCatSlaveSdoRead(0,0x1c13,0,1,(uint8_t *)&u8) ;
			  MSG_RTT("0x1c13 0 b = %x\n",u8) ;
			  TRACE_MSG("0x1c13 0 b = %x\n",u8) ;
			
				EtherCatSlaveSdoRead(0,0x1c13,1,2,(uint8_t *)&u16) ;
			  MSG_RTT("0x1c13 1 w = %x\n",u16) ;
			  TRACE_MSG("0x1c13 1 w = %x\n",u16) ;
				uint16_t a1a00=u16 ;
				EtherCatSlaveSdoRead(0,a1a00,0,1,(uint8_t *)&u8) ;
			  MSG_RTT("0x%x 0 b = %x\n",a1a00,u8) ;
			  TRACE_MSG("0x%x 0 b = %x\n",a1a00,u8) ;
				for(int i=1 ; i < u8+1 ; i++){
					EtherCatSlaveSdoRead(0,a1a00,i,4,(uint8_t *)&u32) ;
					MSG_RTT("0x%x %d l = %x\n",a1a00,i,u32) ;
					TRACE_MSG("0x%x %d l = %x\n",a1a00,i,u32) ;
					
				}
			
			
/*
			  u8=0 ;
				for(int i=1;i < 6 ;i++){
					EtherCatSlaveSdoWrite(0,0x20f8,i,1,(uint8_t *)&u8) ;
				}
*/
				for(int i=0;i < 6 ;i++){
					EtherCatSlaveSdoRead(0,0x20f8,i,1,(uint8_t *)&u8) ;
					MSG_RTT("r0x20f8 sub-idx=%d = %x\n",i,u8) ;
					TRACE_MSG("r0x20f8 sub-idx=%d = %x\n",i,u8) ;
				}


 

/*
				EtherCatSlaveSdoRead(0,0x60c5,0,4,(uint8_t *)&u32) ;
			  MSG_RTT("Max_acceleration_60c5 = %x\n",u32) ;
			  TRACE_MSG("Max_acceleration_60c5  = %x\n",u32) ;
				

				u32=t1++;
				EtherCatSlaveSdoWrite (0,0x60c5,0,4,(uint8_t *)&u32) ; 			
				EtherCatSlaveSdoRead(0,0x60c5,0,4,(uint8_t *)&u32) ;
			  MSG_RTT("Max_acceleration_60c5 = %x\n",u32) ;
			  TRACE_MSG("Max_acceleration_60c5  = %x\n",u32) ;
*/			
				FPGA_WRITE8(0XC00, 0X00) ;
			
	      uint16_t tt[]={0,0x3333} ;		
				for(int j=0 ; j < 2 ; j++){
					u16=tt[j] ;
					EtherCatSlaveSdoWrite (0,0x60b8,0,2,(uint8_t *)&u16) ; 			
					MSG_RTT("wTouch_Probe_function_60b8 = %x\n",u16) ;
					TRACE_MSG("wTouch_Probe_function_60b8 = %x\n",u16) ;
					EtherCatSlaveSdoRead(0,0x60b8,0,2,(uint8_t *)&u16) ;
					MSG_RTT("rTouch_Probe_function_60b8 = %x\n",u16) ;
					TRACE_MSG("rTouch_Probe_function_60b8 = %x\n",u16) ;
					
					
					EtherCatSlaveSdoRead(0,0x60b9,0,2,(uint8_t *)&u16) ;
					MSG_RTT("rTouch_Probe_function_60b9 = %x\n",u16) ;
					TRACE_MSG("rTouch_Probe_function_60b9 = %x\n",u16) ;
				
					for(int i=0 ; i < 4 ; i++){
						EtherCatSlaveSdoRead(0,0x60bA+i,0,4,(uint8_t *)&u32) ;
						MSG_RTT("rTouch_Probe_function_%x = %x\n",0x60ba+i,u32) ;
						TRACE_MSG("rTouch_Probe_function_%x = %x\n",0x60ba+i,u32) ;
					}
				}
					
				for(;;){
						int ch =WAIT_KEY() ;
						MSG_RTT("%c",ch) ;
					  loc +=0x200 ;
						EtherCatSlaveSdoWrite(0,0x607a,0,4,(uint8_t *)&loc) ;
						MSG_RTT("Target Position 607a = %x\n",loc) ;
						TRACE_MSG("Target Position 607a = %x\n",loc) ;
					
						FPGA_WRITE8(0XC00, 0Xff) ;
						MSG_RTT("Trigger 1") ;
						TRACE_MSG("Trigger 1") ;
					
						EtherCatSlaveSdoRead(0,0x60b9,0,2,(uint8_t *)&u16) ;
						MSG_RTT("rTouch_Probe_function_60b9 = %x\n",u16) ;
						TRACE_MSG("rTouch_Probe_function_60b9 = %x\n",u16) ;
					
						for(int i=0 ; i < 4 ; i++){
							EtherCatSlaveSdoRead(0,0x60bA+i,0,4,(uint8_t *)&u32) ;
							MSG_RTT("rTouch_Probe_function_%x = %x\n",0x60ba+i,u32) ;
							TRACE_MSG("rTouch_Probe_function_%x = %x\n",0x60ba+i,u32) ;
						}
						EtherCatSlaveSdoRead(0,0x60fd,0,4,(uint8_t *)&u32) ;
						MSG_RTT("input_monoitor_60fd = %x\n",u32) ;
						TRACE_MSG("input_monoitor_60fd = %x\n",u32) ;
						ch =WAIT_KEY() ;
						MSG_RTT("%c",ch) ;
						FPGA_WRITE8(0XC00, 0X00) ;
						MSG_RTT("Trigger 0") ;
						TRACE_MSG("Trigger 0") ;
						EtherCatSlaveSdoRead(0,0x60b9,0,2,(uint8_t *)&u16) ;
						MSG_RTT("rTouch_Probe_function_60b9 = %x\n",u16) ;
						TRACE_MSG("rTouch_Probe_function_60b9 = %x\n",u16) ;
					
						for(int i=0 ; i < 4 ; i++){
							EtherCatSlaveSdoRead(0,0x60bA+i,0,4,(uint8_t *)&u32) ;
							MSG_RTT("rTouch_Probe_function_%x = %x\n",0x60ba+i,u32) ;
							TRACE_MSG("rTouch_Probe_function_%x = %x\n",0x60ba+i,u32) ;
						}
						EtherCatSlaveSdoRead(0,0x60fd,0,4,(uint8_t *)&u32) ;
						MSG_RTT("input_monoitor_60fd = %x\n",u32) ;
						TRACE_MSG("input_monoitor_60fd = %x\n",u32) ;
						
				}
			
		}
#endif
#ifdef TEST_BREAK_PULSE
		MSG_RTT("TEST_BREAK_PULSE\n") ;
		MSG_RTT("Input Y-axis STEP:") ;
		Touch.step=get_num_RTT() ;
		
		FPGA_WRITE8(0xf2,0) ;   //清除Driver Clear
    FPGA_WRITE8(0xf8,2) ;  //T1發生時停Y軸(2)
		FPGA_WRITE8(0xc12,0xff) ; //Touch enable
		uint8_t   one_clear=false ;
		while(1){
			uint8_t clear= FPGA_READ8(0xf2) ;
			if(!one_clear && clear !=0){
				Touch.flag=1 ;
				uint32_t DDA= FPGA_READ16(0x6) ;
				MSG_RTT("clear=%x DDA=%x\n",clear,DDA) ;
				one_clear=true ;
			}
			uint8_t flag=FPGA_READ8(0xc10) ;
			if(flag!=0){
				Touch.flag=flag ;
				MSG_RTT("touch int flag=%x\n",Touch.flag) ;
			}
		}
		
#endif		
#ifdef TEST_SYNC
	while(1){
		MSG_RTT("\nInput axis:") ;
		Sync.axis=get_num_RTT() ;
		
		MSG_RTT("\nInput Speed (RPM):") ;
		Sync.speed=get_num_RTT() ;
		MSG_RTT("\nInput Dir (0:forward/1:backward):") ;
		Sync.dir=get_num_RTT() ;
		MSG_RTT("\nInput Total ms :") ;
		Sync.totalms=get_num_RTT() ;
		MSG_RTT("Input inc_dec ms :") ;
		Sync.idms=get_num_RTT() ;
		int PPR = get_PPR(Sync.axis) ;
		Sync.step=Sync.speed*PPR/(60*1000) ;
		RTT("\naxis=%d Speed(RPM)=%d totalms=%d inc_dec ms=%d step=%d PPR=%d\n",Sync.axis,Sync.speed,Sync.totalms,Sync.idms,Sync.step,PPR) ;
		Sync.ms=0 ;
		Sync.run=true ;
	}
		
#endif		
#ifdef TEST_BREAK
	while(1){
		unsigned char ret ;
		while((ret=FPGA_READ8(KEY_STATUS)) ==0xff)
			;
		TRACE_MSG("code=%x\n",ret);
		if((ret ==0x1)||(ret==2)){
			Break.axis=ret-1 ;
			Break.idx=0 ;
			FPGA_WRITE8(0XC00, (Break.axis ==0)?0x20:0x80) ;
			Break.flag=true ;
		}
		else{
			FPGA_WRITE8(0XC00, 0X00) ;
		}
}
		
#endif
		
#ifdef TEST_MANMOV_KEY
	while(1){
		unsigned char ret ;
		while((ret=FPGA_READ8(KEY_STATUS)) ==0xff)
			;
		TRACE_MSG("code=%x\n",ret);
		uint8_t DrvIdx ;
		if((ret >=1) && (ret <=5)){
			MAN_MOV.dir=0;
			DrvIdx=ret-1 ;
		}
		else if((ret >=0x11) && (ret <=0x15)){
			MAN_MOV.dir=1;
			DrvIdx=ret-0x11 ;
		}
		else{
			MAN_MOV.dir=0;
			DrvIdx=0 ;
		}
		MAN_MOV.step=(gstProcessState.u32Vid[DrvIdx]==stDriverTable[0].u32Vid)? (stDriverTable[0].u32PPR/4):((gstProcessState.u32Vid[DrvIdx]==stDriverTable[1].u32Vid)?(stDriverTable[1].u32PPR/4):(stDriverTable[2].u32PPR/4)) ;
		TRACE_MSG("step=%d",MAN_MOV.step) ;
		MAN_MOV.DrvIdx=DrvIdx ;
	}
		
#endif

#ifdef TEST_RAM		
	while(1){	
		test1_SRAM() ;
		TRACE_MSG("%d\n",cnt_UserProcessPDO) ;
	}
#endif
													
													
													
#ifdef TEST_MANMOV_UART
	
	
	
	uint32_t len ;
 	uint8_t txbuf[20];
	while(1){
		if(UART_Complete() ){
			  // rsapberry PI 有送資料來
			uint8_t DrvIdx;
			uint8_t idx =1 ;
			switch(UART_cmdbuf[0]){
				case 0xc0:
					//手動加減鍵
					
					DrvIdx=UART_cmdbuf[idx++] ;

					MAN_MOV.dir=UART_cmdbuf[idx++] ;
				
				  MAN_MOV.step=UART_cmdbuf[idx++] ;
				  MAN_MOV.step+=(UART_cmdbuf[idx++] << 8) ;
				  MAN_MOV.step+=(UART_cmdbuf[idx++] << 16) ;
				
				
				  MAN_MOV.ldir=UART_cmdbuf[idx++] ;
				  MAN_MOV.lstep[0]=UART_cmdbuf[idx++] ;
				  MAN_MOV.lstep[1]=UART_cmdbuf[idx++] ;
				  MAN_MOV.lstep[2]=UART_cmdbuf[idx++] ;
				  MAN_MOV.lstep[3]=UART_cmdbuf[idx++] ;
				  
					RTT("Axis=%d,dir=%u,step=%d,ldir=%x,lstep=%02x%02x%02x%02x\n",DrvIdx,MAN_MOV.dir,MAN_MOV.step,MAN_MOV.ldir,MAN_MOV.lstep[0],MAN_MOV.lstep[1],MAN_MOV.lstep[2],MAN_MOV.lstep[3]) ;
					MAN_MOV.DrvIdx=DrvIdx-1 ;//開始動作
					TRACE_TASK_START(1);
					txbuf[0]=0x51 ;
					txbuf[1]=DrvIdx;
					txbuf[2]= MAN_MOV.ldir;
					txbuf[3]= MAN_MOV.lstep[0];
					txbuf[4]= MAN_MOV.lstep[1];
					txbuf[5]= MAN_MOV.lstep[2];
					txbuf[6]= MAN_MOV.lstep[3];
					UART_Write_Buf(UART1,txbuf,7) ;
					TRACE_TASK_END(1) ;	
					break ;
				case 0xc3:
					
					MAN_MOV.mode=UART_cmdbuf[idx++] ;
				
					if(MAN_MOV.mode==0){
						RTT("to LOGical MODE\n") ;
					}
					else if(MAN_MOV.mode ==1){
						RTT("to Physical MODE\n") ;
						//送出各軸的實際位置
						for(int i=0 ; i < gstProcessState.u8DriverCnt ; i++){
							TRACE_TASK_START(100+i);
							txbuf[0]=0x51 ;
							txbuf[1]=i+1;
							txbuf[2]= 0;
							txbuf[3]= gstProcessState.u32Pos[i];
							txbuf[4]= gstProcessState.u32Pos[i]>>8;
							txbuf[5]= gstProcessState.u32Pos[i]>>16;
							txbuf[6]= gstProcessState.u32Pos[i]>>24;
							UART_Write_Buf(UART1,txbuf,7) ;
							RTT("%d,%d",i+1,gstProcessState.u32Pos[i]);
							TRACE_TASK_END(100+i) ;	
						}
					}
				  RTT("end Mode....") ;
					break ;
				case 0xd0:
					DrvIdx=UART_cmdbuf[idx++] ;
				
				  int N =(uint16_t *)*(&UART_cmdbuf[idx]) ;
				  idx+=2 ;
				  int Start_ms=uint32_t *)*(&UART_cmdbuf[idx]) ;
					idx+=4 ;
				
				  int ms =uint16_t *)*(&UART_cmdbuf[idx]) ;
				  idx+=2 ;
				
				  int idms =uint16_t *)*(&UART_cmdbuf[idx]) ;
				  idx+=2 ;
				  
					int step=(uint32_t *)*(&UART_cmdbuf[idx]) ;
					idx+=4 ; 
					int dst_pos;
					Rd4_1(dst_pos)
					RTT("cmd=%x axis=%d N=%d start_ms=%d ms=%d idms=%d step=%d dst_pos=%d",0xd0,DrvIdx,N,Start_ms,ms,idms,step,dst_pos) ;
					break ;
				case 0x2a:
					INC_idxCmdBuf(rRxCmdBuf1) 
				  RTT("START_ACT")
				  break;
					
				case 0x2b:
					INC_idxCmdBuf(rRxCmdBuf1) 
				  RTT("END_ACT")
				  break;
				default:
				  RTT("ERROR CMD=%x",SRAM_READ8(RxCmdBuf1+rRxCmdBuf1)) ;
					INC_idxCmdBuf(rRxCmdBuf1) 
					
					break ;
			}	
		}		
	}
#endif
	
	
  int n, value, DDA_tmp1, DDA_tmp2,	DDA_tmp3, DDA_tmp4;
	Com2.uart = UART2;
	Com1.uart = UART1;
	NewH=1;
	Chkraspberry=FALSE;
	WriteId=0;
	//insercnt=0;
	uint32_t m;
	NVIC_EnableIRQ(UART2_IRQn);
	NVIC_EnableIRQ(UART1_IRQn);
	UART_EnableInt(UART2, (UART_INTEN_RDAIEN_Msk));// | UART_INTEN_THREIEN_Msk | UART_INTEN_RXTOIEN_Msk));
	UART_EnableInt(UART1, (UART_INTEN_RDAIEN_Msk));// | UART_INTEN_THREIEN_Msk | UART_INTEN_RXTOIEN_Msk));
	
	MachineStatus.ONE=0x1 ;
	
	GenKeyKind() ;
	INL = INL_C_NewH ;		
	INM = INM_C_NewH ;		
	INH = INH_C_NewH ;		
	INE	= INE_C_NewH ;		//6,7->IO2 IN[1,2]
	OUTL= OUTL_C_NewH ;		
	OUTM= OUTM_C_NewH ;			//6,7->IO2 OUT[17,18]
	
	OUTH= OUTH_C_NewH ;	 //IO2 OUT9~16~8
	OUTE= OUTE_C_NewH;			 //IO2 OUT9~16		
	IND=IND_C_NewH;//IO2 IN3~10
	
	
	ini_zrt_power_on() ;
	
	fakepara();
	
	is_first_a = true ;
	double_chk_is_first_a = true ;//關閉翻線手動
	
	//MachineStatus.y_suspend=1;
	//MachineStatus.y_scale=0;
		axis_type =	ARM_AXIS ;
		//設定鍵盤參數
		//wDosMem(0xd0c30,(uint16)178) ;//263ms進入重複狀態
		//wDosMem(0xd0c32,(uint16)11) ;//18ms重複一個鍵
	if(NewH){   //�s��LĲ�o����time
		//test_hardware() ;
		//int t1=260 , t2 =15 ;
		//wr_rs232(0) ; wr_rs232(t1) ; wr_rs232(t1>>8) ;
		//dDelay(5) ;
		//wr_rs232(1) ; wr_rs232(t2) ; wr_rs232(t2>>8) ;
		//dDelay(5) ;
		//int t3=260 , t4=15*3 ;
		//wr_rs232(2) ; wr_rs232(t3) ; wr_rs232(t3>>8) ;
		//dDelay(5) ;
		//wr_rs232(3) ; wr_rs232(t4) ; wr_rs232(t4>>8) ;
		//dDelay(5) ;
		//// led 
		//y_suspendLED() ;
		//d() ;
		//	MAN_AIR_CURSORLED()	;
					  		
		for(uint8 axis=0 ; axis < MAX_AXIS ; axis++){
			Ini_Feedback(axis) ;
		}
	}
	wDosMem(pc_base+0xc30,(uint16)178) ;//263ms進入重複狀態
	wDosMem(pc_base+0xc32,(uint16)11) ;//18ms重複一個鍵
	RetVal = setjmp(RetBuf) ;
	//
	//		按下reset鍵後,程式從此處開始執行
	//
	//
	//
	//
	
	DisableHomeInt();	
	Cvtmotor_grads();
	for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis++){
		if(NewH)DDATbl[axis].new_accval=0;
	}
	for(int i=0;i<4;i++)//initial硬體上探針flag
		DISABLE_TOUCH_STOP(i);
	ResetDriverClear();
	
	ReMake_flag=false;	
	MachineStatus.touch_before_err = false;
	StartRecActtbl=false;
	ChkSlide=false;
	safe_runtag=0;
	RetTblIdx=0;
	Air_idx=0;
	EnableTest=false ;
	HasHand=false ;
	MachineStatus.run_state=6;
	InitVar();	
	if(NewH){
		Ratio=100 ;
		tRatio=0;
		ltRatio=tGenRatio=0;
		Ratiochk=0;
		DISABLE_TOUCH_INT
		wDosMem(pc_base+0xc14,(uint8)0xff)  ; //設定探針邊緣偵測模式 			新硬體	0xff=1,信號1變0時觸發
		//wDosMem(pc_base+0x30,(uint8)0x30); //fpga馬達修改type
	}
	ChkPara=0;
	Reset = 0;
	
	InitIo();
	nInitMotorIo();	
	mTimerSet(10) ;//按reset鍵時,需延遲一段時間;否則檢查不到軸			
	printf("Start Run-------------\n");
	//sendError(VirtualHome,1,3);
	while (1)
	{ 			
		//if((TimerTicks.timer%3000)==0)
		//sendError(VirtualHome,1,3);
		//uint8 status= rDosMem(pc_base+INL);
		//		printf("%d\n",status);
		//}
		//			showEtherCatInfo();
		//Test_input();
		if(MachineStatus.op_mode!=RUN_MODE)
			RecevieParam();
		//TouchIsr();
		//KeyIsr() ;
		//HandIsr();
		always_run();		
		if( MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE) ){
			RUN_RUN() ;
			if( REAL_FAST ){
				;//FAST_RUN();
			}
			else{
				AUTO_RUN();
			}
		}
		IDLE_RUN();
	}
}

void RecevieParam(){
	static int AttblId=0;
	static int ReadId= 0;
	static int test=0;
	static int ucnt=0;
	if(ReadId!=WriteId){
		if(StartRecActtbl && (MachineStatus.op_mode==MAN_MODE || MachineStatus.op_mode==TMODY_MODE)){ //����acttbl
			switch(CmdBuf[ReadId]){
				case Airtbl_SET_AIR://AirTable
				case Airtbl_CLR_AIR:
				case Airtbl_SET_TOUCH:
							if(WriteId-ReadId>=8 || ReadId-WriteId>=8){
								virtualpp=(UC*) & RActtbl[RIdx];
								
							for(int i=0;i<8;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==7){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
									struct AgetsetAir *getsetAir=(struct AgetsetAir *)virtualpp;
									
									if(getsetAir->cmd==Airtbl_SET_AIR){
										AirTbl[Air_idx].cmd	 = SET_AIR;//p_buf->byth==TH_ERR?MISS_SET_AIR:SET_AIR;
										AirTbl[Air_idx].u.air	 = getsetAir->u.air;
										AirTbl[Air_idx].dir  =	getsetAir->dir;
										AirTbl[Air_idx].chk_pos  =	getsetAir->chk_pos;
										//AirTbl[Air_idx].line= now_line ;
										//chk_air_offset_line(now_line, s, xoffset_line);
										//AirTbl[Air_idx].offset_line=xoffset_line;
										printf("1_idx=%d cmd=%d air=%d chk_pos=%d dir=%d\n",Air_idx, AirTbl[Air_idx].cmd,
												AirTbl[Air_idx].u.air, AirTbl[Air_idx].chk_pos, AirTbl[Air_idx].dir) ;
										Air_idx++;
									}
									else if(getsetAir->cmd==Airtbl_CLR_AIR){
										struct AgetsetAir *clrAir=(struct AgetsetAir *)virtualpp;
										AirTbl[Air_idx].cmd		= CLR_AIR;
										AirTbl[Air_idx].u.air	= clrAir->u.air;//~e_air ;
										AirTbl[Air_idx].chk_pos	= clrAir->chk_pos;//e;
										AirTbl[Air_idx].dir	= clrAir->dir;
										//AirTbl[Air_idx].line= (WORD)(p_buf-ProgBuf) ;
										printf("2_idx=%d cmd=%d air=%d chk_pos=%d dir=%d\n",Air_idx, AirTbl[Air_idx].cmd,
												AirTbl[Air_idx].u.air, AirTbl[Air_idx].chk_pos, AirTbl[Air_idx].dir) ;
										Air_idx++;
										
									}
									else if(getsetAir->cmd==Airtbl_SET_TOUCH){
										struct AsetTouch *setTouch=(struct AsetTouch *)virtualpp;
										AirTbl[Air_idx].cmd	 = SET_TOUCH;
										//th = p_buf->byth ;
										AirTbl[Air_idx].u.t.touch = setTouch->t.touch;
										AirTbl[Air_idx].u.t.stop_axis = 1;//stop_axis;
										AirTbl[Air_idx].chk_pos  = setTouch->chk_pos;
										printf("3_idx=%d cmd=%d touch=%d stop_axis=%d chk_pos=%d\n",Air_idx, AirTbl[Air_idx].cmd,
												AirTbl[Air_idx].u.t.touch, AirTbl[Air_idx].u.t.stop_axis, AirTbl[Air_idx].chk_pos) ;
										Air_idx++;
									}
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",Air_idx);
						}
					break;
				case Airtbl_CLR_TOUCH:
				
							if(WriteId-ReadId>=12 || ReadId-WriteId>=12){
									virtualpp=(UC*) & RActtbl[RIdx];
								
							for(int i=0;i<12;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==11){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
									
									struct AclrTouch *clrTouch=(struct AclrTouch *)virtualpp;
									AirTbl[Air_idx].cmd	 = CLR_TOUCH;
									//th = p_buf->byth ;
									//touch2stop_axis(p_buf,th,stop_axis)	;
									AirTbl[Air_idx].u.t.touch	= clrTouch->t.touch;
									AirTbl[Air_idx].chk_pos  =	clrTouch->chk_pos;
									//s =	BcdToBin_X(p_buf->dval[AIR_START_X]);
									//TO_GRID_NOT_ROTATE(AXIS_X,s) ;
									//e =	BcdToBin_X(p_buf->dval[AIR_END_X]);
									//TO_GRID_NOT_ROTATE(AXIS_X,e) ;
									AirTbl[Air_idx].utouch.start=clrTouch-> utouch.start;
									AirTbl[Air_idx].utouch.end=clrTouch-> utouch.end;
									AirTbl[Air_idx].dir  =	clrTouch-> dir;
									//a_tbl[idx].line=(WORD) (p_buf-ProgBuf) ;
									printf("4_idx=%d cmd=%d touch=%d chk_pos=%d start=%d end=%d dir=%d\n",Air_idx, AirTbl[Air_idx].cmd,
											AirTbl[Air_idx].u.t.touch, AirTbl[Air_idx].chk_pos, AirTbl[Air_idx].utouch.start,
											AirTbl[Air_idx].utouch.end, AirTbl[Air_idx].dir) ;
									Air_idx++;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",Air_idx);
						}
					break;
				
				case 0xe0://Virtual
				case 0xe1:
				case 0xe2:
				case 0xe3:
				case 0xe4:
				case 0xe5:
				case 0xe6:
				case 0xe7:
							if(WriteId-ReadId>=12 || ReadId-WriteId>=12){
								virtualpp=(UC*) & RActtbl[RIdx];
								BYTE virtAxis=CmdBuf[ReadId]-0xe0;
							printf("Virtual_") ;
								
							for(int i=0;i<12;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==11){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
									struct Ploop_s *loop_start=(struct Ploop_s *)virtualpp;
									virtual_zabc[virtAxis].flag= loop_start->next ;
									virtual_zabc[virtAxis].initial_move= loop_start->u.line ;
									virtual_zabc[virtAxis].last_move= loop_start->mov	;
									//printf("%d\n",loop_start->cmd);
									printf("%d\n",virtual_zabc[virtAxis].flag);
									printf("%d\n",virtual_zabc[virtAxis].initial_move);
									printf("%d\n",virtual_zabc[virtAxis].last_move);
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case END_ACT://4byte (���2---align4)
				case NULL_ACT_CMD:
						if(CmdBuf[ReadId]==END_ACT)
							RetTblIdx=0;
						if(WriteId-ReadId>=4 || ReadId-WriteId>=4){
								pp[PIdx]=(UC*) & RActtbl[RIdx];
							
							if(CmdBuf[ReadId]==END_ACT){
								printf("END_ACT__") ;
								ChkRacttbl=true;
								//printf("%d\n",PIdx);
							}
							else
								printf("NULL_ACT_CMD__\n") ;
							
							for(int i=0;i<4;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								if(i==3){
									if(ChkRacttbl){
										RetTblIdx+=RActtbl[RIdx]*16;
										printf("%d__",RActtbl[RIdx]) ;
										printf("%d\n",RetTblIdx) ;
									}
									StartRecActtbl=false;
									
									if(ChkRacttbl){
										RIdx=0;
										if(ModeTmp==TEST_MODE)
											KeyTest();
										//else if(FlagRun1)
										//	;//KeyRun1();
										else if(ModeTmp==STEP_MODE)
											KeyStep();
										else
											KeyStartRun();
									}
								}
								else{
									if(ChkRacttbl)
										if (i==2)
											RetTblIdx+=RActtbl[RIdx];
										printf("%d_",RActtbl[RIdx]) ;
								}
								RIdx++;
								ReadId++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
						}
					break;
						
				case MOVE_X://20byte(18)
				case MOVE_Y://20byte(18)
				case MOVE_Z://20byte(18)
				case MOVE_A://20byte(18)
				case MOVE_B://20byte(18)
				case MOVE_C://20byte(18)
				case MOVE_D://20byte(18)
				case MOVE_E://20byte(18)
							if(WriteId-ReadId>=28 || ReadId-WriteId>=28){
								pp[PIdx]=(UC*) & RActtbl[RIdx];
								printf("MOVE_") ;
								
							for(int i=0;i<28;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==27){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				
				case UPDATE_LINE://4byte	
				case SET_AIR:
				case CLR_AIR:
				case SET_TOUCH:
				case CHK_TOUCH:
				
						if(WriteId-ReadId>=4 || ReadId-WriteId>=4){
							pp[PIdx]=(UC*) & RActtbl[RIdx];							
							if(CmdBuf[ReadId]==SET_AIR)
								printf("SET_AIR__") ;
							else if (CmdBuf[ReadId]==CLR_AIR)
								printf("CLR_AIR_") ;
							else if (CmdBuf[ReadId]==SET_TOUCH)
								printf("SET_TOUCH_") ;
							else if (CmdBuf[ReadId]==CHK_TOUCH)
								printf("CHK_TOUCH_") ;
							else
								printf("UPDATE_LINE_") ;
							for(int i=0;i<4;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==3){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case CLR_TOUCH:		
						if(WriteId-ReadId>=8 || ReadId-WriteId>=8){
							pp[PIdx]=(UC*) & RActtbl[RIdx];			
							printf("CLR_TOUCH__") ;
							for(int i=0;i<8;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==3){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;					
				case SET_DELAY:
						if(WriteId-ReadId>=4 || ReadId-WriteId>=4){
							pp[PIdx]=(UC*) & RActtbl[RIdx];						
							printf("SET_DELAY_") ;
							for(int i=0;i<4;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==3){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
										
				case WAIT_DELAY:
						if(WriteId-ReadId>=4 || ReadId-WriteId>=4){
							pp[PIdx]=(UC*) & RActtbl[RIdx];
							printf("WAIT_DELAY_") ;
							for(int i=0;i<4;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==3){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case WAIT_MOTOR_NEAR_IN_LOOP://4byte	
						if(WriteId-ReadId>=8 || ReadId-WriteId>=8){
							pp[PIdx]=(UC*) & RActtbl[RIdx];
							printf("WAIT_MOTOR_NEAR_IN_LOOP_") ;
							for(int i=0;i<8;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==7){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case LOOP_UPDATE_LINE://8byte (���2+4---align4)
						if(WriteId-ReadId>=8 || ReadId-WriteId>=8){
							pp[PIdx]=(UC*) & RActtbl[RIdx];
							printf("LOOP_UPDATE_LINE_") ;
							for(int i=0;i<8;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==7){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case LOOP_START://4byte	
						if(WriteId-ReadId>=12 || ReadId-WriteId>=12){
							pp[PIdx]=(UC*) & RActtbl[RIdx];
							printf("LOOP_START_") ;
							for(int i=0;i<12;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==11){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case LOOP_CHECK:
						if(WriteId-ReadId>=4 || ReadId-WriteId>=4){
							pp[PIdx]=(UC*) & RActtbl[RIdx];
							printf("LOOP_CHECK_") ;
							for(int i=0;i<4;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==3){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case LOOP_END:
						if(WriteId-ReadId>=4 || ReadId-WriteId>=4){
							pp[PIdx]=(UC*) & RActtbl[RIdx];
							printf("LOOP_END_") ;
							for(int i=0;i<4;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==3){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				case LOOP_X:
				case LOOP_Y:
				case LOOP_Z:
				case LOOP_A:
				case LOOP_B:
				case LOOP_C:
				case LOOP_D:
				case LOOP_E:
						if(WriteId-ReadId>=28 || ReadId-WriteId>=28){
							pp[PIdx]=(UC*) & RActtbl[RIdx];
							printf("LOOP_Axis_") ;
							for(int i=0;i<28;i++){
								RActtbl[RIdx]=CmdBuf[ReadId];
								
								if(i==27){
									printf("%d\n",RActtbl[RIdx]) ;
									StartRecActtbl=false;
								}
								else{
										printf("%d_",RActtbl[RIdx]) ;
								}
								ReadId++;
								RIdx++;
								if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
									ReadId=1;
							}
							PIdx++;
							printf("%d\n",ReadId);
						}
					break;
				default:
					ReadId++;
					break;
			}
		}
		else if(MachineStatus.op_mode==MAN_MODE|| MachineStatus.op_mode==PARA_MODE|| MachineStatus.op_mode==TMODY_MODE){
			switch(CmdBuf[ReadId]){//������
				case 0xCC:
					if(MachineStatus.op_mode==MAN_MODE|| MachineStatus.op_mode==TMODY_MODE){
						StartRecActtbl=true;
						printf("204__");
						ReadId++;
					}
					else
						ReadId++;
					
					if(ReadId>=MAX_CMD_BUF)//�Ѽ�BUG
						ReadId=1;
				break;
				case 0xB9://線架時間
				case 0xC5://Yscale	
				case 0xC6:
				case 0xC7://模式	
				case 0xA7://軸數
				case 0xA8://汽缸設定
				case 0xBB://滑座極限
				case 0xBC://汽缸解除
				case 0xBD://油檢解除
				case 0xBE://X軸反向
				case 0xBF://鍵盤鎖住
				case 0xD1://X-解碼器
				case 0xD2://Y-解碼器
				case 0xD3://安全門
				case 0xD4://安全裝置
				case 0xD5://警示燈
				case 0xD6://自動斷電
				case 0xff://check send OK
				case 0xfe://flag_RRealAxis
				case 0x55://keycode
					if(WriteId-ReadId>=2 || ReadId-WriteId>=2){
						Cnt++;
						for(int i=0;i<2;i++){
							Rtemp[i]=CmdBuf[ReadId];
							if(ReadId++>=MAX_CMD_BUF-1)
								ReadId=1;
						}
						switch (Rtemp[0]){
							case 0xBB://滑座極限
								MachineStatus.SlideLimit=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.SlideLimit) ;
								break;
							case 0xBC://汽缸解除
								MachineStatus.AirOff=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.AirOff) ;
								break;
							case 0xBD://油檢解除
								MachineStatus.OilChk=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.OilChk) ;
								break;
							case 0xBE://X軸反向
								MachineStatus.XMINUS=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.XMINUS) ;
								break;
							case 0xBF://鍵盤鎖住
								MachineStatus.KEYLOCK=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.KEYLOCK) ;
								break;
							case 0xD1://X-解碼器
								MachineStatus.X_Encoder=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.X_Encoder) ;
								break;
							case 0xD2://Y-解碼器
								MachineStatus.Y_Encoder=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.Y_Encoder) ;
								break;
							case 0xD3://安全門
								MachineStatus.safety_door=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.safety_door) ;
								break;
							case 0xD4://安全裝置
								MachineStatus.bysafe_plugin=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.bysafe_plugin) ;
								break;
							case 0xD5://警示燈
								MachineStatus.BUZZER=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.BUZZER) ;
								break;
							case 0xB9://WireTime
								MachineStatus.WireTime=Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.WireTime) ;
								break;
							case 0xA7://軸數
								MachineStatus.axis_no=Rtemp[1];
								for (int i=0;i<MachineStatus.axis_no;i++)
									MachineStatus.p3701[i]=1;
								break;						
							case 0xA8://汽缸設定
								wDosMem(pc_base+OUTL, Rtemp[1]) ;
								printf("%d %x %d \n",Cnt,Rtemp[0],Rtemp[1]) ;
								break;
							case 0xC5://Yscale	
								MachineStatus.y_scale = Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.y_scale) ;
								//AxisLED(AXIS_Y);
									wr_rs232(4) ; wr_rs232(7) ; wr_rs232(MachineStatus.y_scale?1:0) ;
									//d();
								break;
							case 0xC6://速率	
								MachineStatus.speed[MachineStatus.speed_mode] = Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.speed[MachineStatus.speed_mode]) ;
								break;
							case 0xC7://模式	
								MachineStatus.speed_mode = Rtemp[1];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.speed_mode) ;
								break;
							case 0xD6://自動斷電	
								if (Rtemp[1]==1 && (MachineStatus.Type==620 ||MachineStatus.Type==650 ||MachineStatus.Type==635 ||MachineStatus.Type==608
														||MachineStatus.Type==820 ||MachineStatus.Type==850 ||MachineStatus.Type==835)){
									printf("PowerOff\n") ;
									//if (Chkraspberry)ready_PowerOff(1);
								}
								break;	
							case 0xFE://flag_RRealAxis
								if (Rtemp[1]==0xf3){
									SendKey(KEY_DUMMY_RESET);
									for(uint8 axis=0 ;axis <MachineStatus.axis_no ; axis++){
										Clr2016s(axis) ;
									}
									flag_RRealAxis=!flag_RRealAxis;
									flag_timeoutoff=!flag_RRealAxis ;
									SoftReset() ;
								}
								break;	
							case 0xFF://check send OK
								if(Rtemp[1]==0xf4){
									Chkraspberry=true;
									is_first_a=true;
									{
										int t1=260 , t2 =15 ;
										wr_rs232(0) ; wr_rs232(t1) ; wr_rs232(t1>>8) ;
										dDelay(5) ;
										wr_rs232(1) ; wr_rs232(t2) ; wr_rs232(t2>>8) ;
										dDelay(5) ;
										int t3=260 , t4=15*3 ;
										wr_rs232(2) ; wr_rs232(t3) ; wr_rs232(t3>>8) ;
										dDelay(5) ;
										wr_rs232(3) ; wr_rs232(t4) ; wr_rs232(t4>>8) ;
										dDelay(5) ;
										// led 
										y_suspendLED() ;
										dDelay(3) ;
										if(NewH){
											AB_manual_to_zero_NewH(is_first_a) ; 	//����½�u����
										}
										if(is_first_z){
											//Z_manual_to_zero(is_first_z) ;
										}
										
										for(int axis=0; axis<MAX_AXIS_8; axis++){
											if(MachineStatus.bIDMS[axis] !=0){
												//計算加速表
												double tacc= (double)(BMOTORGRID(axis)*MachineStatus.Rate[axis])/MIN2MS/MachineStatus.bIDMS[axis];
												for(int t=0 ; t < MachineStatus.bIDMS[axis];t++){
													MachineStatus.Autoidms[axis][t]=0.5*tacc*(t+1)*(t+1)-0.5*tacc*t*t+0.5 ;//+0.5作四捨五入
												}
											}
										}
									}
									printf("%d %x %d \n",Cnt,Rtemp[0],Rtemp[1]) ;
								}
								break;
							case 0x55://keycode
								if(Rtemp[1]==0x07){
									SendKey(KEY_DUMMY_RESET);
									printf("Reset\n");
									SoftReset() ;
								}
								printf("%d %x %d\n",Cnt,Rtemp[0],Rtemp[1]) ;
							break;
						}
					}
					break;
					
				case 0xAA://手動
				case 0xB8://單位
				case 0xA5://開關軸(LED燈)
				case 0xC1://設定失誤量
				case 0xC2://設定生產量
				case 0xBA://翻線角度
				case 0xD0://機器型號
					if(WriteId-ReadId>=3 || ReadId-WriteId>=3){
						Cnt++;
						for(int i=0;i<3;i++){
							Rtemp[i]=CmdBuf[ReadId];
							if(ReadId++>=MAX_CMD_BUF-1)
								ReadId=1;
						}
						switch (Rtemp[0]){
							case 0xD0://機器型號
								MachineStatus.Type=Rtemp[1]*256+Rtemp[2];
								printf("%d %x %d %d %d \n",Cnt,Rtemp[0],Rtemp[1],Rtemp[2],MachineStatus.Type) ;
							break;
							case 0xBA://翻線角度
								MachineStatus.AHome=Rtemp[1]*256+Rtemp[2];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.AHome) ;
							break;
							case 0xAA://手動
								MachineStatus.manval[Rtemp[1]]=Rtemp[2];
								printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.manval[Rtemp[1]]) ;
							break;
							case 0xB8://單位
								MachineStatus.Unit[Rtemp[1]]=Rtemp[2];
								printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.Unit[Rtemp[1]]) ;
							break;
							case 0xA5://開關軸(LED燈)
								if(Rtemp[1]==1){
									MachineStatus.y_suspend = !Rtemp[2];
									y_suspendLED() ;
								}
								else{
									MachineStatus.motor[Rtemp[1]]=Rtemp[2];
									AxisLED(Rtemp[1]);
									if (Rtemp[1]==AXIS_A && Rtemp[2]==1 && Chkraspberry)
									{
										if(double_chk_is_first_a && CHK_ROTW(AXIS_A) && MachineStatus.motor[AXIS_A] && MachineStatus.ZrtMode[AXIS_A]!= MODE_ZRT_YA_ABS1){//嚙踝蕭嚙踝蕭翻嚙線嚙踝蕭嚙?
											is_first_a=true;
											AB_manual_to_zero_NewH(is_first_a) ; 	//����½�u����
										}
									}
										
									MOTOR_SW(Rtemp[1]);
								}

								printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.motor[Rtemp[1]]) ;
							break;
							case 0xC1://設定失誤量
								MachineStatus.cur_miss=Rtemp[1]*256+Rtemp[2];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.cur_miss) ;
							break;
							case 0xC2://設定生產量
								MachineStatus.set_miss=Rtemp[1]*256+Rtemp[2];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.set_miss) ;
							break;
						}
					}
					break;
				case 0xAC://wZeroSpd
				case 0xAD://ZRTPreM
				case 0xAE://MotFunc
				case 0xAF://���F���A
				case 0xB0://���I�H��
				case 0xB1://���I����
				case 0xB2://���I�Ҧ�
				case 0xB4://���I����
				case 0xB5://�^���H��
				case 0xC3://�ثe�Ͳ��q
				case 0xC4://�]�w�Ͳ��q
				case 0xC8://馬達速度
				case 0xC9://加減速
					if(WriteId-ReadId>=4 || ReadId-WriteId>=4){
						Cnt++;
						for(int i=0;i<4;i++){
							Rtemp[i]=CmdBuf[ReadId];
							if(ReadId++>=MAX_CMD_BUF-1)
								ReadId=1;
						}
						switch (Rtemp[0]){
							case 0xAC://wZeroSpd
									MachineStatus.wZeroSpd[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.wZeroSpd[Rtemp[1]]) ;
									break;
							case 0xAD://ZRTPreM
									MachineStatus.ZRTPreM[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.ZRTPreM[Rtemp[1]]) ;
									break;
							case 0xAE://MotFunc
									MachineStatus.MotFunc[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.MotFunc[Rtemp[1]]) ;
									break;
							case 0xAF://nMotorType
									MachineStatus.nMotorType[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									wDosMem(pc_base+ALARM_CTL+Rtemp[1] ,(uint8)((MachineStatus.nMotorType[Rtemp[1]]==0x0)? 0:1)) ;
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.nMotorType[Rtemp[1]]) ;
									break;
							case 0xB0://SensorHighLow
									MachineStatus.SensorHighLow[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.SensorHighLow[Rtemp[1]]) ;
									break;
							case 0xB1://home_seq
									MachineStatus.home_seq[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.home_seq[Rtemp[1]]) ;
									break;
							case 0xB2://ZrtMode
									MachineStatus.ZrtMode[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.ZrtMode[Rtemp[1]]) ;
									break;
							/*case 0xB3://ZRTSET
									MachineStatus.ZRTSET[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.ZRTSET[Rtemp[1]]) ;
									break;*/
							case 0xB4://ZrtCorr
									MachineStatus.ZrtCorr[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.ZrtCorr[Rtemp[1]]) ;
									break;
							case 0xB5://bMotorNEAR
									MachineStatus.bMotorNEAR[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.bMotorNEAR[Rtemp[1]]) ;
									break;
							case 0xB6://motor_grads
									MachineStatus.motor_grads[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
									printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.motor_grads[Rtemp[1]]) ;
									break;
							case 0xC3://cur_quan
									MachineStatus.cur_quan=(Rtemp[1]*65536+Rtemp[2]*256+Rtemp[3]);
									printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.cur_quan) ;
									break;
							case 0xC4://set_quan
									MachineStatus.set_quan=(Rtemp[1]*65536+Rtemp[2]*256+Rtemp[3]);
									printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.set_quan) ;
									break;
							case 0xC8://馬達速度
								MachineStatus.Rate[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.Rate[Rtemp[1]]) ;
							break;
							case 0xC9://加減速
								MachineStatus.bIDMS[Rtemp[1]]=Rtemp[2]*256+Rtemp[3];
								printf("%d %x %d \n",Cnt,Rtemp[0],MachineStatus.bIDMS[Rtemp[1]]) ;
							break;
						}
	
					}
					break;
					
				case 0xB3://�s�]���I
				case 0xB6://���F���
				case 0xB7://��촫��
					if(WriteId-ReadId>=5 || ReadId-WriteId>=5){
						Cnt++;
						for(int i=0;i<5;i++){
							Rtemp[i]=CmdBuf[ReadId];
							if(ReadId++>=MAX_CMD_BUF-1)
								ReadId=1;
						}
						
						switch (Rtemp[0]){
							case 0xB6://���F���
								MachineStatus.motor_grads[Rtemp[1]]=(Rtemp[2]*65536+Rtemp[3]*256+Rtemp[4]);
								printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.motor_grads[Rtemp[1]]) ;
							break;
							case 0xB7://��촫��
								MachineStatus.nY0[Rtemp[1]]=(Rtemp[2]*65536+Rtemp[3]*256+Rtemp[4]);
								printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.nY0[Rtemp[1]]) ;
							break;
							case 0xB3://�s�]���I
							//MachineStatus.ZRTSET_sign[Rtemp[1]]=PLUS_SIGN;
							if(Rtemp[2]==0xff ||Rtemp[2]==0xfe){
								Rtemp[2]=~(Rtemp[2]);
								Rtemp[3]=~Rtemp[3];
								Rtemp[4]=~Rtemp[4]+1;
								//MachineStatus.ZRTSET_sign[Rtemp[1]]=MINUS_SIGN;
								MachineStatus.ZRTSET[Rtemp[1]]=-(Rtemp[2]*65536+Rtemp[3]*256+Rtemp[4]);
							}
							else
								MachineStatus.ZRTSET[Rtemp[1]]=(Rtemp[2]*65536+Rtemp[3]*256+Rtemp[4]);
							printf("%d %x %x %d \n",Cnt,Rtemp[0],Rtemp[1],MachineStatus.ZRTSET[Rtemp[1]]) ;
							break;
						}
					}
					break;
				case 0x06://��m
					if(WriteId-ReadId>=2 || ReadId-WriteId>=2){
						Cnt++;
						for(int i=0;i<2;i++){
							Rtemp[i]=CmdBuf[ReadId];
							if(ReadId++>=MAX_CMD_BUF-1)
								ReadId=1;
						}
						printf("%d %x  %x\n",Cnt,Rtemp[0],Rtemp[1]) ;
						BYTE axis=Rtemp[1];
					
						TxBuf[0]=poscmd ;	
						TxBuf[1]=axis;	
						int tmp=MachineStatus.axis_val[axis];
						for(int i =0;i<3;i++){
							TxBuf[4-i]=tmp&0xff;
							tmp>>=8;
						}
						printf("axis=%d pos=%d \n",axis,MachineStatus.axis_val[axis]);
						
						Com2.Tx(TxBuf,5) ;
					}
					break;
				default:
					ReadId++;
					break;
			}
		}
		else
			ReadId=WriteId;
	}
}

void Rs232_KeyIsr()
{
	UART_T* uart2=UART2;//Com2 Keyboard
	
	static int no =0 ;
	static UC lch ;
	UC ch ;
	//inportb(rs232_base[0] + IIR_8250) ;
	if(!(uart2->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk))   // Check RX empty => failed 
	{	
	// have a byte in receiver buffer
	ch = (uint8_t)UART1->DAT;
	if(no == 0){
		lch=ch ;
		no++ ;
	}
	else{
		no=0 ;
		if((!keylock && !keyswap) || lch==2){
			//printf("%x\n",ch) ;
			switch(lch)
			{
				case 0:			
					if(ch ==KEY_DUMMY_RESET){  // reset	key
						SetDriverClear() ;
						Reset =	1;
						SendKey(ch);
						printf("%x  %x status=%d\n",TxBuf[0],TxBuf[1],MachineStatus.op_mode) ;
					}
					if(	((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx)){
						KeyBuf[KeyBufWIdx]= ch ;
						//Test_IO(KeyBuf[KeyBufRIdx]);
						if(KeyBufWIdx+1 >= MAX_KEY_BUF){
							KeyBufWIdx=0;
						}
						else{
							KeyBufWIdx++ ;
						}
					}
					break ;
				case 1:
					break ;
				case 2:
					KeyInput = ch ; 
					//printf("Keylock=%d\n",KeyInput);
					KeyLockCHG=true;
					break ;
				case 4://��L�|�ǫe�m�X��4,����
					break ;
				default:
					lch=ch ;
					no=1 ;
					break ;
			}
		}
		}
	}
}

//#define DTime_12(dif)  (dif < 2670 && dif > 2660) 
#define DTime_12(dif)  (dif < 380 && dif > 370) 
#define DTime_2x(dif)  (dif < 190)      

void KeyIsr()
{			
		uint16 qlen=rDosMem(pc_base+0x020) ; 
		static uint16 lqlen=rDosMem(pc_base+0x020);
		static uint8 lcode =0 ;
		static int no=0 ,hand_statue=0;
		static struct TIMER  lTimerTicks ;
		uint8 code=rDosMem(pc_base+KEY_STATUS);
		bool flag=true ;
		
		//uint8 KeySafe=rDosMem(pc_base+INE);
		//uint32 lx=dReadAbsPos(AXIS_X);

		int cnt=0;
    if(qlen!=lqlen){
			int16 lenth=lqlen-qlen;																//�s���,�p��cnt��,���buffer��
			if(lenth>0) {																	//�s���,�|���ϦV��code�ץ�(�̦h���⦸)
				if( hand_statue==3){lenth=1;code=KEY_HAND_RIGHT;hand_statue=1;}
				if((hand_statue==2 ) && TimerTicks.timer-lTimerTicks.timer<300 ){lenth=1;  code=KEY_HAND_LEFT;hand_statue=3;}
				else{
					hand_statue=1;
					code=KEY_HAND_RIGHT;
				}
			}
			else {
				if( hand_statue==4){lenth=1;code=KEY_HAND_LEFT;hand_statue=2;}
				if((hand_statue==1 )&& TimerTicks.timer-lTimerTicks.timer<300 ){lenth=1;code=KEY_HAND_RIGHT;hand_statue=4;}
				
				else{
					hand_statue=2;
					code=KEY_HAND_LEFT; 
					lenth=-lenth;
				}
			}
			for(int i=1;i<lenth;i++) {
				if((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx ){
					KeyBuf[KeyBufWIdx+1]=code ;
					KeyBufWIdx = KeyBufWIdx%MAX_KEY_BUF ;
				}
			}
			lTimerTicks.timer=TimerTicks.timer;
			lqlen=qlen;
		}
		if((code !=0xff)&& !keyswap && !keylock && code!=0xf0 && code!=0xf2 && code!=0xf3 && code!=0xf4 && code!=0xfa && code!= 0xfb && code!=0xfc && code!=0xf5 && code!=0xf6 && code!=0xf7){
			if(code == lcode){
			
				long long dif=TimerTicks.timer-lTimerTicks.timer ;	
				if(DTime_2x(dif) ||DTime_12(dif)){
				printf("dif=%lld\n",dif);
					//為repeat鍵
					if(KeyKind[code]== 1){
						if((no%repeatno)!=0){
							flag=false ;
						}
						no++ ;
					}
					else if(KeyKind[code]== 2){
						//單鍵
						flag=false ;
					}
				}
				else{
					no=0 ;
				}
			}
			else{
				no=0 ;
			}
			lcode=code ;
			lTimerTicks=TimerTicks ;
			if(flag){
				// has a code
				if(code ==KEY_DUMMY_RESET){  // reset	key
					//StopMotor();
						SendKey(code);
						printf("%x  %x\n",TxBuf[0],TxBuf[1]) ;
					SetDriverClear() ;
					Reset =	1;
				}
				if((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx ){
					KeyBuf[KeyBufWIdx++]=code ;
					KeyBufWIdx = KeyBufWIdx%MAX_KEY_BUF ;
				}
			}
		}
}


void enable_all_touch()
{
	ENABLE_INPORT_INT(MASK_BIT6) ; // touch 1
	ENABLE_INPORT_INT(MASK_BIT7) ; // touch 2
	ENABLE_INPORT_INT(MASK_BIT3) ; // touch 3
	ENABLE_INPORT_INT(MASK_BIT4) ; // touch 4
}
void disable_all_touch()
{
	DISABLE_INPORT_INT(MASK_BIT6) ; // touch 1
	DISABLE_INPORT_INT(MASK_BIT7) ; // touch 2
	DISABLE_INPORT_INT(MASK_BIT3) ; // touch 3
	DISABLE_INPORT_INT(MASK_BIT4) ; // touch 4
}
void update_sc(bool force)
{
	if(IsTimeUp(timeout_ADC) || force){
		timeout_ADC= mTimerSet(TIMER_ADC) ;
		update_sc_kernel() ;
	}
}

void sendhand(uint8 axis,uint8 meg){
		uint8 Txhand[3];
		Txhand[0]=0x0b ;	
		Txhand[1]=axis ;
		Txhand[2]=meg ;
	
		printf("%x %x %x\n",Txhand[0],Txhand[1],Txhand[2]) ;
		Com2.Tx(Txhand,3) ;
}

void fakepara()
{
	MachineStatus.axis_no=4;	
	for(BYTE axis=0 ; axis <MachineStatus.axis_no ; axis++){
			if (axis ==AXIS_X){	//凸輪
				MachineStatus.MotFunc[axis] = CAM_FUNC;
				MachineStatus.Unit[axis] = UNIT_GRID;
				MachineStatus.motor_grads[axis]=22320;
			}
			else if (axis ==AXIS_Y){ //送線
				MachineStatus.MotFunc[axis] = FEED_FUNC;
				MachineStatus.Unit[axis] = UNIT_MM;
			}
			else if (axis ==AXIS_Z){ //轉芯
				MachineStatus.MotFunc[axis] = ROTQ_FUNC;
				MachineStatus.Unit[axis] = UNIT_DEG;
				MachineStatus.motor_grads[axis]=20000;
			}		
			else if (axis ==AXIS_A){ //���
				MachineStatus.MotFunc[axis] = ROTQ_FUNC;
				MachineStatus.Unit[axis] = UNIT_DEG;
				MachineStatus.motor_grads[axis]=72000;
			}		
			else if (axis ==AXIS_B){ //���
				MachineStatus.MotFunc[axis] = ROTQ_FUNC;
				MachineStatus.Unit[axis] = UNIT_GRID;
				MachineStatus.motor_grads[axis]=40000;
			}		
			else if (axis ==AXIS_C){ //���
				MachineStatus.MotFunc[axis] = ROTQ_FUNC;
				MachineStatus.Unit[axis] = UNIT_DEG;
				MachineStatus.motor_grads[axis]=40000;
			}		
			else if (axis ==AXIS_D){ //���
				MachineStatus.MotFunc[axis] = ROTQ_FUNC;
				MachineStatus.Unit[axis] = UNIT_DEG;
				MachineStatus.motor_grads[axis]=40000;
			}		
			else if (axis ==AXIS_E){ //���
				MachineStatus.MotFunc[axis] = ROTQ_FUNC;
				MachineStatus.Unit[axis] = UNIT_DEG;
				MachineStatus.motor_grads[axis]=40000;
			}		
MachineStatus.bENCR0[axis]=MachineStatus.bENCR1[axis]=1000;	
		MachineStatus.nY0[axis]=1000;	
		MachineStatus.p3701[axis]=1;
		MachineStatus.manval[axis]=10;
		MachineStatus.ZrtMode[axis]=2 ; 
		MachineStatus.SensorHighLow[axis]=1;	
		MachineStatus.wZeroSpd[axis]=100;
		MachineStatus.ZRTPreM[axis]=30;
		MachineStatus.home_seq[axis]=axis;
		MachineStatus.home_seq_sign[axis]= PLUS_SIGN;
		MachineStatus.motor[axis]=1;
		MachineStatus.ZrtCorr[axis]=axis;
	}	
	MachineStatus.Y1=1000;
	MachineStatus.nY0[AXIS_Y]=4330;	
	MachineStatus.set_quan=999999;
	MachineStatus.cur_quan=0;
	MachineStatus.cur_miss = 0;
	MachineStatus.safety_door=1;
	MachineStatus.TIMER=0;
	flag_off_power=true;
	BOUTM &= BNY(0,0,0,1, 1,1,1,1);
	KeyLockCHG=1;
	MachineStatus.WireTime=20;
	MachineStatus.PayOff=30000;
	MachineStatus.speed_mode =AUTO;
	MachineStatus.speed[MachineStatus.speed_mode]=25;
	wDosMem(pc_base+OUTL, (uint8)0) ;
	wDosMem(pc_base+OUTM, (uint8)0) ;
	wDosMem(pc_base+OUTH, (uint8)0) ;
	wDosMem(pc_base+OUTE, (uint8)0) ;		
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


