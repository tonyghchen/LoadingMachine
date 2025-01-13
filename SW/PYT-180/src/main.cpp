/**************************************************************************//**
 * @file     main.cpp
 * @version  V1.00
 * @brief    PYT-180 Firmware
 *
 *
 * @copyright (C) 
 *****************************************************************************/
#define GLOBAL
#include "header.h"
#include "NuMicro.h"
#include "pyt-180.h"
#include "app_config.h"
#include "ec.h"
#include "EtherCatInterface.h"
#include <ctype.h>
#include <math.h>
#include "trace_config.h"
#include "xinda_version.h"
#include "modbus_bsq_dg.h"

void fakepara();
void Test_input();
bool set_ScrnSav();
void RecevieParam();
void test_hardware();
void Test_IO(uint8 keycode);
void showEtherCatInfo();
void SendLoadCellToRas(uint16_t *pu16Value);

const unsigned int AppVersion __attribute__((at(0x00000400))) = (VER_MAJOR<<24)|(VER_MINOR<<16)|(VER_BUILD);

char gUARTCmdTxBuf[MAX_CMD_BUF];

uint8 Rtemp[40];	
static int Cnt= 0;
bool StartRecActtbl;

int ActtblIdx;
int ReceiveIdx;


SerialCom Com2;
SerialCom Com1;

struct TEST {
		BYTE b ;
		unsigned short w ;
    int l ;
} ;

void SEGGER_SYSVIEW_Update_SampleData(uint32_t u16Value);
uint32_t    gErrorCount;


#pragma optimize("", off)
class LoadCell
{
    
private:
#define MAX_DEVICE_ADDRESS  4
#define REPORT_CYCLE        50      // 50 ms
#define RESPONSE_TIMEOUT    4       // 2ms
#define MAX_RECEIVER_SIZE   64

    enum STATE { IDLE= -1, QUERY = 0, WAIT_RESPONSE=1, WAIT_NEXTCMD=2, WAIT_NEXTREPORT=3 } ;

    
    UART_T *      uart;
    uint8_t       CmdBuffer[32];
	uint8_t       ResponseBuffer[MAX_RECEIVER_SIZE];
    uint16_t      u16Value[MAX_DEVICE_ADDRESS], u16MeasureValue;
	uint8_t       u8DeviceAddr;
    STATE         State;
	uint8_t	  	  u8NextCmdDelayTick, u8NexCmdDelay;
    uint8_t       u8ResponseTimeoutCnt, u8MaxResponseTimeoutCnt;
    
    uint8_t       u8ReportTickCnt, u8MaxReportTickCnt;

    DWORD         u32CurrentMsTick ;
    
    uint32_t      u32ErrorCnt;
    uint32_t      u32TimeoutCnt;
    char            szDebugMsg[128];
public:
    LoadCell(){
        uart = UART3;//  LoadCell

        State = QUERY;
        reset();
        u32CurrentMsTick = 0;
        u8ResponseTimeoutCnt = 0;
        
        u8NexCmdDelay = 1;
        
        u32ErrorCnt = 0;
        u32TimeoutCnt = 0;
	}
    
    void debug(char *title, char *buffer, uint8_t size)
    {
        //if (gErrorCount <= 3)
            return ;
        
        uint8_t byIndex , i, byNibbleByte;
        char    *pDest = szDebugMsg; 
        byIndex = sprintf(szDebugMsg, "%s: ", title);
        pDest += byIndex;
        
        for(i=0; i < size; i++){
            byNibbleByte = (buffer[i] >> 4);
            *pDest++ = (byNibbleByte >= 10) ? ('A' + (byNibbleByte-10)) : ('0' + byNibbleByte);
            byNibbleByte = (buffer[i] & 0x0F);            
            *pDest++ = (byNibbleByte >= 10) ? ('A' + (byNibbleByte-10)) : ('0' + byNibbleByte); 
            *pDest++ = ' ';
        }
        *pDest = 0;
        RTT(szDebugMsg);
    }
    void reset()
    {
        u8DeviceAddr = 1;
        u8ReportTickCnt = 0;
        for(int i=0; i < MAX_DEVICE_ADDRESS; i++){
            u16Value[i] = 0;
        }
    }
   
    void ReportMeasureValue()
    {
        if (u16Value[0] == 0){
            gErrorCount++; 
        }
        SendLoadCellToRas(u16Value);
    }
    
	void QueryMeasureValue()
	{
        int CmdLen = modbus_bsq_dg_ReadMeasureValue(CmdBuffer, u8DeviceAddr);
        
        u8ResponseTimeoutCnt = 0;        
		gstUARTModbus.send_bytes((char*)CmdBuffer, CmdLen);
        //debug("LC Tx", (char*)CmdBuffer, CmdLen);
        //Trigger TXE interrupt
        if (!(uart->INTEN&UART_INTEN_THREIEN_Msk)){
            UART_EnableInt(uart, UART_INTEN_THREIEN_Msk) ;
        }
	}
   
    bool WaitResponse()
    {
        if ( gstUARTModbus.si_buf_len >= 7){
            
			uint16_t  u16RecCRC, u16CRC;
			uint8_t   u8Addr, u8FunCode, u8DataLength, byHighByte, byLowByte;
            uint8_t   u8DataSize = gstUARTModbus.si_buf_len;
			            
			gstUARTModbus.read_bytes((char*)ResponseBuffer, u8DataSize);
            //debug("LC Rx", (char*)ResponseBuffer, u8DataSize);
			u8Addr = ResponseBuffer[0];
			u8FunCode = ResponseBuffer[1];
			u8DataLength = ResponseBuffer[2];
			u16MeasureValue   = (ResponseBuffer[3] <<8)| ResponseBuffer[4];		
			u16RecCRC = (ResponseBuffer[5] <<8)| ResponseBuffer[6];		
			
			u16CRC = modbus_getCRC16(ResponseBuffer, 5);
			if (u8Addr == u8DeviceAddr && u8FunCode == 3 &&  u16CRC == u16RecCRC){
                u16Value[u8DeviceAddr-1] = u16MeasureValue;
				// Data Plot
                if (u8Addr == 1){
                    SEGGER_SYSVIEW_Update_SampleData(u16MeasureValue);
                }
				return (true);
			}
            else{
                gErrorCount++; 
                return (true);
            }
		}
        
		return (false);
    }
    
    void process (DWORD currentTick){
        u32CurrentMsTick = currentTick;
        switch(State){
            case IDLE :
                break;
            
            case QUERY:    // Query
                State = WAIT_RESPONSE;
                QueryMeasureValue();
                break;
            
            case WAIT_RESPONSE :    // Wait Response or Timeout
                if (WaitResponse() == true || 
                    ++u8ResponseTimeoutCnt >= RESPONSE_TIMEOUT){
                    
                    if (u8ResponseTimeoutCnt >= RESPONSE_TIMEOUT )
                        u32TimeoutCnt++;
                    
                    // 蒐集完所有裝置上的資料
                    if (++u8DeviceAddr > MAX_DEVICE_ADDRESS){	
                        // 回報裝置的重量
                        ReportMeasureValue();
                        State = WAIT_NEXTREPORT;
                        reset();
                    }
                    else{
                        // 進入等待時間後, 繼續蒐集下一個裝置上的資料
                        State = WAIT_NEXTCMD;
                        u8NextCmdDelayTick = 0;                        
                    }
				}
                break;
                
			case WAIT_NEXTCMD :    // silent interval
				if (++u8NextCmdDelayTick >= u8NexCmdDelay){
					State = QUERY;
                }
                break;
                
            case WAIT_NEXTREPORT :
                if (++u8ReportTickCnt >= REPORT_CYCLE){
                    u8ReportTickCnt = 0;
					State = QUERY;
                }
                break;
                
            default :
                break;
        }
    }
};
#pragma optimize("", on)

LoadCell gLoadCellInfo;


void _delay()
{
	float a=1.0,b=2.0,c=3.0; 
	for(int i=0 ; i < 0x10000 ;i++){
		a=b+c ;
	}
}


void test1_SRAM()
{
	
	uint32_t  tid=1 ;
	RTT("tid=%d 10000 SRAM_WRITE16(i*2+0x100, i+value1)",tid) 
	TRACE_TASK_START(tid);
	unsigned short 	value1 = 0x1234;
	for(int i=0; i <10000 ; i++){
		SRAM_WRITE16(i*2+0x100, i+value1);
	}
	TRACE_TASK_END(tid++) ;
	
	RTT("tid=%d 10000 SRAM_WRITE16(i*2+0x101, i+value1)",tid) 
	TRACE_TASK_START(tid);
	for(int i=0; i <10000 ; i++){
		SRAM_WRITE16(i*2+0x101, i+value1);
	}
	TRACE_TASK_END(tid++) ;
	
	RTT("tid=%d 10000 SRAM_WRITE8(i+0x101, i+value1)",tid) 
	TRACE_TASK_START(tid);
	for(int i=0; i <10000 ; i++){
		SRAM_WRITE8(i+0x101, i+value1);
	}
	TRACE_TASK_END(tid++) ;
	
	
	RTT("tid=%d 10000 value1+=SRAM_READ16(i*2+0x100)",tid) 	
	TRACE_TASK_START(tid);
	for(int i=0; i <10000 ; i++){
		value1+=SRAM_READ16(i*2+0x100);
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


void AlLlightOn()
{

}


void LightGreenON()
{
}


void LightRedON()
{
}


void LightYellowON()
{
}


bool CHK_KEY()
{
	return(false) ;

}

bool set_ScrnSav()
{
	bool flag = false ;
	return flag ;
}


void test_hardware()
{
}



int ReadAdc100()		//value 0~100
{
	int cnt=0 ;
	int adc ;
#if 1
    adc = 0;
#else    
	do{
		adc=FPGA_READ16(0xe0) ;
//		RTT("real ADC=%d",adc) ;
		adc=adc/260 ;
    		cnt++ ;
	}
	while(((adc >100) || (adc < 0)) && (cnt < 10)) ;
	if(adc > 100)adc=100 ;
	if(adc < 0)adc=0 ;
//	RTT("ADC(0~100)=%d",adc);
#endif    
	return(adc) ;
}


void UART_Write_Buf(UART_T* uart,uint8_t txbuf[],uint32_t no)
{
	if(uart == UART1){
		for(int i=0 ; i <no ;  i++){
			gUARTCmdTxBuf[wTxCmdBuf1] = txbuf[i]; 
			INC_idxCmdBuf(wTxCmdBuf1);
		}
		//Trigger TXE interrupt
		if(!(uart->INTEN&UART_INTEN_THREIEN_Msk)){
			UART_EnableInt(uart,UART_INTEN_THREIEN_Msk) ;
		}
	}
}


uint8_t txbuf[20];

void SendLoadCellToRas(uint16_t *pu16Value)
{
		txbuf[0]=defUART_LoadCellData_0x70 ;	//LoadCell 資料
		txbuf[1]=~txbuf[0] ;
		*(uint16*)(&txbuf[2]) = pu16Value[0] ;
      	*(uint16*)(&txbuf[4]) = pu16Value[1] ;
        *(uint16*)(&txbuf[6]) = pu16Value[2] ;
        *(uint16*)(&txbuf[8]) = pu16Value[3] ;
		UART_Write_Buf(UART1,txbuf, 10) ;    
}


void SendADCToRas(uint8_t ADC)
{
		int idx ;
		txbuf[idx=0]=defUART_rKeySpeed_0x56 ;	//測試旋鈕速度值
		txbuf[++idx]=~txbuf[0] ;
		txbuf[++idx]=ADC ;
		UART_Write_Buf(UART1,txbuf,++idx) ;
}


void SendVersionToRas()
{
		int idx =0 ;
		txbuf[idx]=0x66 ;
		txbuf[++idx]=~txbuf[0] ;
		txbuf[++idx]=VER_MAJOR ;
		txbuf[++idx]=VER_MINOR ;
		txbuf[++idx]=VER_BUILD ;
		txbuf[++idx]=(VER_BUILD>>8) ;
		UART_Write_Buf(UART1,txbuf,++idx) ;	 
}


void SendKeyToRas(uint8_t keycode)
{
		int idx ;
		txbuf[idx=0]=0x55 ;
		txbuf[++idx]=~txbuf[0] ;
		txbuf[++idx]=keycode ;
		UART_Write_Buf(UART1,txbuf,++idx) ;
}


void SendMPGToRas(uint8_t dir)
{
		int idx ;
		txbuf[idx=0]=0x65 ;
		txbuf[++idx]=~txbuf[0] ;
		txbuf[++idx]=dir ;
		UART_Write_Buf(UART1,txbuf,++idx) ;
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


int get_hexnum_RTT()
{
	int num=0 ;
	while(1){
		int ch =WAIT_KEY() ;
		MSG_RTT("%c",ch) ;
		if(isxdigit(ch)){
			ch=toupper(ch) ;
			ch=(ch <='9')? (ch-'0'): (ch-'A'+10) ;
			num*=16 ;
			num+=(ch) ;
			RTT("num=%d",num) ;
		}
		else{
			break;
		}
	}
	RTT("num=%d...................",num);
	return(num) ;
}


int get_PPR(int axis)
{
	for(int i=0 ;i < no_stDriverTable ;i++){
		if(gstProcessState.u32Vid[axis]==stDriverTable[i].u32Vid){
			 return(stDriverTable[i].u32PPR) ;
		}
	}
  return (0);
}


void run_ini()
{
	TouchAir_air_buf=0 ;
	FPGA_WRITE8(FPGA_GPIO_OUTL,TouchAir_air_buf) ;
	gstProcessState.TouchAir_touch_idx=8 ;
	for(int i=0 ;i < 8 ; i++){
		TouchAir[i].used=0;
	}
	FPGA_WRITE8(0x114,0) ;   //diable Home interrupt
	FPGA_WRITE8(0x10a,0) ;   //diable extHome interrupt
  
	FPGA_WRITE8(0xf2,0) ;   //清除Driver Clear
	FPGA_WRITE8(0xc12,0x00) ; //'0'disable & clear interrupt
	
	
	//清除目前失誤量
	gstProcessState.CurrFailQty=0 ;
	int idx ;
	txbuf[idx=0]=0x59 ;
	txbuf[++idx]=~txbuf[0] ;
	txbuf[++idx]=gstProcessState.CurrFailQty ;
	UART_Write_Buf(UART1,txbuf,++idx) ;
	//清除探針狀態
	txbuf[idx=0]=0x63 ;
	txbuf[++idx]=~txbuf[0] ;
	txbuf[++idx]=0 ;
	txbuf[++idx]=0 ;
	txbuf[++idx]=0 ;
	txbuf[++idx]=0 ;
	txbuf[++idx]=0 ;
	UART_Write_Buf(UART1,txbuf,++idx) ;	
	if(gstProcessState.VRAUTOHOME==EC_VRHOME_MODE){
		gstProcessState.RUNTEST=EC_TEST_MODE ;
	}
	else{
		gstProcessState.RUNTEST=EC_RUN_MODE ;
	}
	gstProcessState.flgStopMachine=false ;
	if(gstProcessState.flgProgramToolRun){
		gstProcessState.flgProgramToolRun=false ;
		gstProcessState.flgStopMachine=true ;	
	}
}


int UART_Complete()
{
	if(ridx_CmdBufTbl != widx_CmdBufTbl){
		// rsapberry PI 有送一完整命令來
		return(1) ;
	}
	return(0) ;
}


void UART_Update_ridx_CmdBufTbl()
{
	ridx_CmdBufTbl++;		
	if(ridx_CmdBufTbl>=MAX_CMDBUFTBL){
		ridx_CmdBufTbl=0 ;
	}
//			RTT("ridx_CmdBufTbl=%d",ridx_CmdBufTbl) ;
}


void stop_motor()
{	
	flgMoveStep=false ;
	flgActionTable=false ;

}


void ResetMachine()
{
	stop_motor() ;
	
	
	uint8_t aa[]={0x00,0x00,0x01,0x02,0x00,0x20,0x00,0x00,0x08,0x10} ;
	uint8_t ab[]={0x00,0x00,0x01,0x02,0x01,0x20,0x00,0x00,0x02,0x00} ;	
	uint8_t ac[]={0x00,0x00,0x01,0x02,0x01,0x20,0x00,0x00,0x01,0x00} ;	
  uint8_t  status ,tt;
	//清除錯誤的驅動器
  for (int nDriver=0; nDriver < gstProcessState.u8DriverCnt; nDriver++){   
		if(gstProcessState.errcode[nDriver]!=0){			
			if(gstProcessState.u32Vid[nDriver]==0x539){
				if(gstProcessState.errcode[nDriver]==0x810){
					  RTT("Encode clear...........") ;
						//安川編碼器備份警報
						EtherCatMasterStop();
						
						EtherCatSlaveSdoRead(nDriver,0x2710,0,1,&tt );
						EtherCatSlaveSdoRead(nDriver,0x2710,2,1,&status );
					
					  RTT("number of entries=%d   status=%d",tt,status) ;
					
						RTT("WRITE aa...........") ;
						EtherCatSlaveSdoWrite(nDriver,0x2710,1,10,aa) ;
					  for(int i=0 ; i < 100 ;i++){
							EtherCatSlaveSdoRead(nDriver,0x2710,2,1,&status );
							RTT("status =%d") ;
						}
						RTT("WRITE ab...........") ;
						EtherCatSlaveSdoWrite(nDriver,0x2710,1,10,ab) ;
					  for(int i=0 ; i < 100 ;i++){
							EtherCatSlaveSdoRead(nDriver,0x2710,2,1,&status );
							RTT("status =%d") ;
						}
						RTT("WRITE ac...........") ;
						EtherCatSlaveSdoWrite(nDriver,0x2710,1,10,ac) ;
					  for(int i=0 ; i < 100 ;i++){
							EtherCatSlaveSdoRead(nDriver,0x2710,2,1,&status );
							RTT("status =%d") ;
						}
						
						
						EtherCatMasterRunning();
						RTT("reset encoder  --- delay 5 sec") ;						
						//延遲5秒
						uint32_t tt =cnt_UserProcessPDO+5000 ;						
						while(cnt_UserProcessPDO < tt) ;
						RTT("reset encoder") ;
// 						flgReset=1 ;
				}	
		  }
      else{
				AxisResetEncoderClr=nDriver ;
				if(gstProcessState.errcode[nDriver]== 0xa1){
					flgEncoderClr=1 ;
				}
				else{
					flgReset=1 ;
				}
			}
		}
		while(flgReset){
		}	
		gstProcessState.errcode[nDriver]=0 ;
		LightYellowON() ;
	}
//	flgReset=1 ;
	//清除所有的RS232資料
//	rRxCmdBuf1= wRxCmdBuf1=0 ;
}


void fillActionTable(int idxMS,int idxAT)
{
		MoveStep[idxMS].axis= ActionTable[idxAT].axis ;
#ifdef RTT_TRACE_LOC
	  if(ActionTable[idxAT].axis == TraceLoc.axis){
			TraceLoc.flg=true ;
			TraceLoc.lenBuf=0 ;
		}
#endif
		MoveStep[idxMS].acc=0 ;
		MoveStep[idxMS].curstepAcc=0 ;
		MoveStep[idxMS].frwacc=0 ;
		MoveStep[idxMS].ms =ActionTable[idxAT].ms;
		MoveStep[idxMS].Start_ms =ActionTable[idxAT].Start_ms;
		MoveStep[idxMS].idms =ActionTable[idxAT].idms;
		MoveStep[idxMS].dir =ActionTable[idxAT].dir;
		MoveStep[idxMS].step =ActionTable[idxAT].step;
		MoveStep[idxMS].frwdir =ActionTable[idxAT].frwdir;
		MoveStep[idxMS].frwstep =ActionTable[idxAT].frwstep;
		MoveStep[idxMS].src_pos=(ActionTable[idxAT].Feed)? 0:gstProcessState.dst_pos[ActionTable[idxAT].axis-1] ;
		MoveStep[idxMS].dst_pos=ActionTable[idxAT].dst_pos;
	  if(ActionTable[idxAT].N!= gstProcessState.N){
			gstProcessState.flgN=true ;
			gstProcessState.N=ActionTable[idxAT].N ;
		}
}


void SetAir(int airno)
{
}

void ClrAir(int airno)
{
}


void SetTouchAir(int touchairno)
{

}


void ClrTouchAir(int touchairno)
{

}


void fillActionTable2TouchAir(int idxMS,int idxAT)
{
}


void SetHandWheelPower(uint8_t t1)
{
	gstProcessState.HandWheelPower=t1 ;
}


void SetSPD(uint8_t t1)
{
	gstProcessState.SPD=t1 ;
}


void ini_CmdBufTbl()
{
	CmdState=CMD1 ;
	ridx_CmdBufTbl =	widx_CmdBufTbl=0 ;
 	wRxCmdBuf1=rRxCmdBuf1=wTxCmdBuf1=rTxCmdBuf1=0 ;
}


bool Sync_MAN_MOV()
{
	if(CmdBufTbl[ridx_CmdBufTbl].cmd==defUART_wManualUpDown_0xc0){
		 int off=(msTicks-CmdBufTbl[ridx_CmdBufTbl].ms)%MS_MANMOV;
		 if(off == 2|| (off == 3)){
			 RTT("ridx_CmdBufTbl=%d ms=%d msTicks=%d  off=%d",ridx_CmdBufTbl,CmdBufTbl[ridx_CmdBufTbl].ms,msTicks,off);
			 return(true) ;
		 }
		 else{
			 return(false) ;
		 }
	 }
	 return(true) ;
}


#define DELAYMS  (200+(100*(gstProcessState.buffersize/100)*(gstProcessState.buffersize/100)*2))
static int zero_1=0 ;
int main (void)
{
	//變數初始化
	ini_CmdBufTbl() ;
	flgReset=0 ;
	flgEncoderClr=0 ;
  gstProcessState.flgcontMAN=gstProcessState.flgDisplay_touch=false ;
	gstProcessState.flgStopMachine=gstProcessState.flgreadyStopMachine=gstProcessState.flgProgramToolRun=false ;
	TouchKey.state[0]=TouchKey.state[1]=TouchKey.state[2]=TouchKey.state[3]=TouchKey.state[4]=S0_KEY ;
	TouchKey.cnt[0]  =TouchKey.cnt[1]  =TouchKey.cnt[2]  =TouchKey.cnt[3]  =TouchKey.cnt[4]  =0 ;
	
	
  ResetKey.state[0]   =ResetKey.state[1]   =ResetKey.state[2]   =ResetKey.state[3]=ResetKey.state[4]=ResetKey.state[5]=ResetKey.state[6]=S1_KEY ;
	ResetKey.cnt[0]     =ResetKey.cnt[1]     =ResetKey.cnt[2]     =ResetKey.cnt[3]  =ResetKey.cnt[4]  =ResetKey.cnt[5]  =ResetKey.cnt[6]  =0;
	ResetKey.Limitcnt[0]=ResetKey.Limitcnt[1]=ResetKey.Limitcnt[2]=S1_TOUCH_KEY_CNT ;
	ResetKey.Limitcnt[3]=ResetKey.Limitcnt[4]=ResetKey.Limitcnt[5]=ResetKey.Limitcnt[6]=50-1 ;

	FunKey.state[0]   =FunKey.state[1]   =FunKey.state[2]   =FunKey.state[3]   =FunKey.state[4]   =FunKey.state[5]=S1_KEY ;
	FunKey.cnt[0]     =FunKey.cnt[1]     =FunKey.cnt[2]     =FunKey.cnt[3]     =FunKey.cnt[4]     =FunKey.cnt[5]  =0 ;
	FunKey.Limitcnt[0]=S0_TOUCH_KEY_CNT*30 ;
	FunKey.Limitcnt[1]=FunKey.Limitcnt[2]=FunKey.Limitcnt[3]=FunKey.Limitcnt[4]=FunKey.Limitcnt[5]=S0_TOUCH_KEY_CNT ;
	bool flgPowerOff = false ;
	int  cntPowerOff=0 ;
	

	
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

#if 1
    Config_Hardware(APP_SPI_CLOCK);
#else
  uint8_t tt1,stl, stm,tl,tm ; ;
	do{
		do{
			//延遲
			float a=1.234,b=23.456;
			for(int i=0 ; i <10000000 ;i++){
				a=a*b ;
			}
			Config_Hardware(APP_SPI_CLOCK);
		
			tt1=FPGA_READ8(0xF1) ;
		}
		while(tt1 != 0x82) ;
		TRACE_INIT();
		RTT("hello!\n") ;
		
		FPGA_WRITE8(FPGA_GPIO_OUTL, stl=0X0) ;   // OUTL=0xc00
		FPGA_WRITE8(FPGA_GPIO_OUTM, stm=0x4+0x10+0x20+0x40) ;   // OUTM=0xc02,紅燈:0x4 斷電輸出:0x8 黃燈:0x10 綠燈:0x20 ,開大電:0x40
		tl=FPGA_READ8(FPGA_GPIO_OUTL) ;
		tm = FPGA_READ8(FPGA_GPIO_OUTM) ;
	}
	while((tl !=stl) || (tm != stm)) ;
#endif    
	
#ifdef TEST_HARDWARE
  RTT("TEST HARDWARE");
  int ret ;
	while(1){
		if((ret=FPGA_READ8(KEY_STATUS))!=0xff){
		   //RTT("keycode =%x\n",ret) ;
		}
		RTT("input OUTM 0xC02 setting val:") ;
		int val=get_hexnum_RTT() ;
		FPGA_WRITE8(0xC02,val) ;
		RTT("\n") ;
		
	}
#endif
	
	
#if !(TEST_BREAK_PULSE)
	for(uint8_t i=0 ; i < MAX_DRIVER ;i++){
		gstProcessState.u32DisPos[i]=0 ;
		gstProcessState.flgOverUnder[i]=0 ;
	}
	uint8_t t1=EtherCatMasterInit(APP_SPI_CLOCK);
	RTT("t1=%d",t1) ;
	RTT("gstProcessState.u8RunMode=%d\n",gstProcessState.u8RunMode) ;
	RTT("gstProcessState.u32RunCounter=%d\n",gstProcessState.u32RunCounter) ;
	RTT("gstProcessState.u32MatchCounter=%d\n",gstProcessState.u32MatchCounter) ;
	RTT("gstProcessState.u8DriverCnt=%d\n",gstProcessState.u8DriverCnt) ;
	uint32_t u32Vid, u32Pid , Pos;
  for (int nDriver=0; nDriver < gstProcessState.u8DriverCnt; nDriver++){        
      EtherCatGetVidPid(nDriver, &gstProcessState.u32Vid[nDriver], &gstProcessState.u32Pid[nDriver]);
			gstProcessState.errcode[nDriver]=0 ;
		  RTT("Driver=%d,u32Vid=%x, u32Pid=%x\n",nDriver,gstProcessState.u32Vid[nDriver], gstProcessState.u32Pid[nDriver]) ;
//      EtherCatGetActualPos(nDriver+1, &Pos);
//		  printf("driver current pos=%x\n",Pos) ;
	}
	RTT("gstProcessState.u8DOutCnt=%d\n",gstProcessState.u8DOutCnt) ;
	RTT("gstProcessState.u8DInCnt=%d\n",gstProcessState.u8DInCnt) ;
	
	
// 								for(int i=0 ; i < gstProcessState.u8DriverCnt ; i++){
// // 									TRACE_TASK_START(100+i);
// 									int idx;
// 									txbuf[idx=0]=0x51 ;
// 									txbuf[++idx]=~txbuf[0] ;
// 									txbuf[++idx]=i+1;
// 									txbuf[++idx]= gstProcessState.u32Pos[i];
// 									txbuf[++idx]= gstProcessState.u32Pos[i]>>8;
// 									txbuf[++idx]= gstProcessState.u32Pos[i]>>16;
// 									txbuf[++idx]= gstProcessState.u32Pos[i]>>24;
// 									UART_Write_Buf(UART1,txbuf,++idx) ;
// 									RTT("%d,%d",i+1,gstProcessState.u32Pos[i]);
// // 							    TRACE_TASK_END(100+i) ;	
// 						    }
// 								//送出結束軸(0)
// 								int idx;
// 								txbuf[idx=0]=0x51 ;
// 								txbuf[++idx]=~txbuf[0] ;
// 								txbuf[++idx]=0;
// 								txbuf[++idx]= 0;
// 								txbuf[++idx]= 0;
// 								txbuf[++idx]= 0;
// 								txbuf[++idx]= 0;
// 								UART_Write_Buf(UART1,txbuf,++idx) ;
// 								RTT("%d,%d",0,0);				

#endif
#if (!TEST_BREAK_PULSE)&&(!TEST_SDO)
#if 0
		// 讀取0x1600~0x1603
	  uint16_t    u16 ;
	  uint32_t    u32 ;
	  uint16_t    addr[]={0x1600,0x1A00} ;
		for(int k=0 ; k  < 2 ; k++){
			for(int j=0 ; j < 3 ; j++){
				EtherCatSlaveSdoRead(0,addr[k]+j,0,2,(uint8_t *)&u16) ;
				RTT("addr=%x  sub=0 value=%x",addr[k]+j,u16) ;
				for(int i=0 ; i < u16 ; i++){
					EtherCatSlaveSdoRead(0,addr[k]+j,i+1,4,(uint8_t *)&u32) ;
					RTT("addr=%x  sub%=d value=%x",addr[k]+j,i+1,u32) ;
				}
			}
		}
#endif 	
				EtherCatMasterRunning();
#endif
#ifdef TEST_MANMOV_UART
	
//計算 S型曲線家減速
  float x ;
	int N=8*2+1 ;
	for(int i=-N/2 ; i < N/2 ;i++){
		   x=i ;
		   float y= 1/(1+exp(-x)) ;
		  RTT("i=%d x=%f Sigmoid=%f",i,x,y) ;
	}	
	
	
	
	
	uint32_t len ;
	unsigned char ret ;
	gstProcessState.adc=ReadAdc100() ;
	SendADCToRas(gstProcessState.adc) ;
	
	
	msTicks=lmsTicks=0;	
	uint32_t data=0;
	int cnt =0 ;
	uint8_t touch_mask[]={0x40,0x80,0x8,0x10,0x2} ;
	uint8_t Reset_mask[]={0x80,0x8,0x40,0x2,0x4,0x10,0x20} ;
	uint8_t Fun_mask[]={0x1,0x2,0x4,0x8,0x10,0x20} ;  // power off(INH0),停機(INH1),啟動生產(INH2),測試(INH3),原點(INH4),吋動盒原點(INH5)
	uint8_t lINL=0,lINM=0,lINH=0 ;
	int16_t lCntHandWheel=FPGA_READ16(0x20) ;
	
	LightYellowON() ;
	
	FPGA_WRITE8(FPGA_GPIO_OUTH,0x00) ;
	FPGA_WRITE8(FPGA_GPIO_OUTE,0x00) ;
	
/********************/
	FAxis=1 ;
	flgSetTouchProbeMode=true ;
	
	
	
	while(1){
		int ret ;
		//if((ret=FPGA_READ8(KEY_STATUS))!=0xff){
		//   //RTT("keycode =%x\n",ret) ;
		//}
		if(flgResetCmd){
			  flgResetCmd=false ;
				ini_CmdBufTbl() ;
				ResetMachine() ;
		}
		static int delay=1000*5 ;
 	  if(lmsTicks  != msTicks){ //經過 1ms
			lmsTicks=msTicks ;
			
            gLoadCellInfo.process(lmsTicks);
            
			if(flgDisplayADC0){
				flgDisplayADC0=false ;
				SendADCToRas(0) ;
				RTT("send ADC00000----------------------------------------------------") ;
			}
			if(flgPowerOff){
				cntPowerOff++ ;
				FPGA_WRITE8(FPGA_GPIO_OUTM, 0X0) ;   // 關掉所有電源
				if(cntPowerOff >= (1000*6)){
						FPGA_WRITE8(FPGA_GPIO_OUTM, 0X8) ;   // 斷電輸出:0x8
						for(int j=0 ; j <100000 ;j++) ;
						FPGA_WRITE8(FPGA_GPIO_OUTM, 0X0) ;   // 
				}
			}

			
			//檢測"重置","按鍵鎖住""Switch"鍵,"A+","A-","Y+","Y-"
				
			//檢查"POWER off IN","停機" ,"啟動生產","測試","原點","翻線原點"
#if 0            
			for(int i=0;i < 6 ;i++){
				switch(FunKey.state[i]){
					case S0_KEY:
							if((INH&Fun_mask[i]) !=0){
								FunKey.cnt[i]++ ;
								if(FunKey.cnt[i] >S0_TOUCH_KEY_CNT){
									FunKey.state[i]=S1_KEY ;
									FunKey.cnt[i]=0 ;
								}
							}
							else{
								FunKey.cnt[i]=0 ;
							}
							break ;
					case S1_KEY:
							if((INH&Fun_mask[i]) ==0){
								FunKey.cnt[i]++ ;
								if(FunKey.cnt[i] >FunKey.Limitcnt[i]){
									FunKey.state[i]=S0_KEY ;
									FunKey.cnt[i]=0 ;
									//have a vaild key
									RTT("have a vaild key %d",i) ;
									if(i==0){
										//送出"關機準備中"命令給樹梅派
										int idx;
										txbuf[idx=0]=defUART_rPowerDown_0x67 ;
										txbuf[++idx]=~txbuf[0] ;
										UART_Write_Buf(UART1,txbuf,++idx) ;										
										flgPowerOff=true ;
									}
									else if(i==1){
										//停機
										gstProcessState.flgStopMachine=true ;
									}
									else if(i==2){
										//啟動生產
										if(gstProcessState.RUNTEST== EC_TEST_MODE){
											//測試轉生產
											gstProcessState.RUNTEST=EC_RUN_MODE ;
											int idx;
											txbuf[idx=0]=defUART_rTest2Product_0x5e ;
											txbuf[++idx]=~txbuf[0] ;
											UART_Write_Buf(UART1,txbuf,++idx) ;
										}
										else{
												SendKeyToRas(0x4) ;
										}
									}
									else if(i==3){
										//測試
										SendKeyToRas(0x5) ;
									}
									else if(i==4){
										//原點
										SendKeyToRas(0x3) ;
									}									
									else if((i==5)&& flgKeySwitch){
										//翻線原點
										RTT("RW HOME") ;
										SendKeyToRas(0xf) ;
									}									
								}
							}
							else{
								FunKey.cnt[i]=0 ;
							}
							break ;
				}
			}
#endif
			
			


		}
		

		//檢測驅動器是否有錯誤
		if((flgEncoderClr==0) && (flgReset ==0)){
			for (int nDriver=0; nDriver < gstProcessState.u8DriverCnt; nDriver++){        
				if((gstProcessState.StatusWord[nDriver]&0x8)&& !gstProcessState.errcode[nDriver]){
					uint16_t errcode ;
					EtherCatGetErrorCode(nDriver,&errcode) ;
					//有驅動器發生錯誤,必須停機
					stop_motor() ;
					EtherCatMasterStop();
					uint32_t u2101_1=0,u2101_2=0,u2102_1=0,u2102_2=0,u6060 ;
					if(gstProcessState.u32Vid[nDriver]== 0x539){
						//安川馬達
						gstProcessState.errcode[nDriver]=errcode ;
					}
					else{
						EtherCatSlaveSdoRead(nDriver,0x2101,1,1,(uint8_t *)&u2101_1) ;
						EtherCatSlaveSdoRead(nDriver,0x2101,2,1,(uint8_t *)&u2101_2) ;			 
						EtherCatSlaveSdoRead(nDriver,0x2102,1,4,(uint8_t *)&u2102_1) ;
						EtherCatSlaveSdoRead(nDriver,0x2102,2,4,(uint8_t *)&u2102_2) ;
						gstProcessState.errcode[nDriver]=u2101_1 ;
						if(gstProcessState.errcode[nDriver]==0){
							gstProcessState.errcode[nDriver]=u2102_1&0xff ;
						}
					}
					stop_motor();
					LightRedON() ;
					flgDisplayErr=true ;
// 					int idx ;
// 					txbuf[idx=0]=0x40 ;
// 					txbuf[++idx]=~txbuf[0] ;
// 					txbuf[++idx]=nDriver+1 ;
// 					int err=u2101_1 ;
// 					if(err ==0){
// 						err=u2102_1&0xff ;
// 					}
// 					txbuf[++idx]=err ;
// 					UART_Write_Buf(UART1,txbuf,++idx) ;	
// 					txbuf[idx=0]=0x40 ;
// 					txbuf[++idx]=~txbuf[0] ;
// 					txbuf[++idx]=nDriver+1-1 ;
// 					txbuf[++idx]=err-1 ;
// 					UART_Write_Buf(UART1,txbuf,++idx) ;	
// 					
// 					if((u2101_1 == 0xa1)){
// 						// encoder clear
// 						RTT("Encoder Clear.....axis=%d",nDriver);
// 						flgEncoderClr=1 ;
// 						AxisResetEncoderClr=nDriver ;
// 					}
					EtherCatMasterRunning();
					RTT("axis =%d %x errcode=%x %d  0x2101 %x %x 0x2102  %x  %x u6060=%x",nDriver,gstProcessState.StatusWord[nDriver],errcode,errcode,u2101_1,u2101_2,u2102_1,u2102_2,u6060)
				}
			} 			
		}
		
		//顯示錯誤的驅動器
		if(flgDisplayErr){
			flgDisplayErr=false ;
			for (int nDriver=0; nDriver < gstProcessState.u8DriverCnt; nDriver++){        
				if(gstProcessState.errcode[nDriver] !=0){
						int idx ;
						txbuf[idx=0]=0x40 ;
						txbuf[++idx]=~txbuf[0] ;
						txbuf[++idx]=nDriver+1 ;
						txbuf[++idx]=gstProcessState.errcode[nDriver] ;
						UART_Write_Buf(UART1,txbuf,++idx) ;	
				}
			}
		}
		if(gstProcessState.flgcontMAN){
			gstProcessState.flgcontMAN=false ;
			static uint32_t llstep=0 ;
			int idx ;
			txbuf[idx=0]=0x51 ;
			txbuf[++idx]=~txbuf[0] ;
			txbuf[++idx]=gstProcessState.contMAN_DrvIdx;
			uint8_t *pt=(uint8_t*)&gstProcessState.contMAN_lstep ;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;;
			UART_Write_Buf(UART1,txbuf,++idx) ;
			RTT("display axis=%d lstep=%d",gstProcessState.contMAN_DrvIdx,gstProcessState.contMAN_lstep) ;
			if(gstProcessState.contMAN_lstep== llstep){
				RTT("DDDDDDDDDDDDDDD-----------------------------------llstep =%d lstep=%d",llstep ,gstProcessState.contMAN_lstep);
			}
			llstep=gstProcessState.contMAN_lstep ;
		}
		if(gstProcessState.flgDisplay_touch){
			gstProcessState.flgDisplay_touch=false  ;
			int idx, touchIdx ;
			txbuf[idx=0]=0x63 ;
			txbuf[++idx]=~txbuf[0] ;
			touchIdx = gstProcessState.touch;
			if (touchIdx > 4){
					touchIdx -=4;
			}
			txbuf[++idx]= touchIdx ;
			uint8_t *pt=(uint8_t *)&gstProcessState.touch_yvalue ;
			txbuf[++idx]=*pt++ ;
			txbuf[++idx]=*pt++ ;
			txbuf[++idx]=*pt++ ;
			txbuf[++idx]=*pt++ ;
			UART_Write_Buf(UART1,txbuf,++idx) ;	
			if(gstProcessState.touch_yvalue ==0){
				//探針失敗
				txbuf[idx=0]=0x59 ;
				txbuf[++idx]=~txbuf[0] ;
				txbuf[++idx]=gstProcessState.CurrFailQty ;
				UART_Write_Buf(UART1,txbuf,++idx) ;	
			}
		}
		//測試模式下
		if(gstProcessState.flgCurrProductTime&& (gstProcessState.RUNTEST == EC_TEST_MODE)&&(cnt_UserProcessPDO%DELAYMS)== 0){
			gstProcessState.flgCurrProductTime=false ;
			int idx ;
			txbuf[idx=0]=defUART_rCurrProductTime_0x58 ;
			txbuf[++idx]=~txbuf[0] ;
			uint8_t *pt=(uint8_t *)&msMoveStep ;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			UART_Write_Buf(UART1,txbuf,++idx) ;	
//			RTT("msMoveStep=%d.............................................",msMoveStep);
			 ;
		}
		if(gstProcessState.flgN&& (gstProcessState.RUNTEST == EC_TEST_MODE)&& ((cnt_UserProcessPDO%DELAYMS)== 0)){
			gstProcessState.flgN=false ;
			int idx ;
			txbuf[idx=0]=defUART_rN_0x5b ;
			txbuf[++idx]=~txbuf[0] ;
			uint8_t *pt=(uint8_t *)&gstProcessState.N ;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			UART_Write_Buf(UART1,txbuf,++idx) ;	
//			RTT("N=%d.............................................",gstProcessState.N);
			gstProcessState.flgAccF=true;
		}
// 		if(gstProcessState.flgAccF&&((cnt_UserProcessPDO%DELAYMS)== 0)){
// 			gstProcessState.flgAccF=false ;
// 			gstProcessState.AccF+=10 ; 
// 			int idx ;
// 			txbuf[idx=0]=0x5c ;
// 			txbuf[++idx]=~txbuf[0] ;
// 			uint8_t *pt=(uint8_t *)&gstProcessState.AccF ;
// 			txbuf[++idx]= *pt++;
// 			txbuf[++idx]= *pt++;
// 			txbuf[++idx]= *pt++;
// 			txbuf[++idx]= *pt++;
// 			UART_Write_Buf(UART1,txbuf,++idx) ;	
// 			RTT("AccF=%d.............................................",gstProcessState.AccF);
// 		}
		if(gstProcessState.flgCurrProductQty){
			gstProcessState.flgCurrProductQty=false ;
			int idx ;
			txbuf[idx=0]=defUART_rCurrProductQty_0x57 ;
			txbuf[++idx]=~txbuf[0] ;
			uint8_t *pt=(uint8_t *)&gstProcessState.CurrProductQty ;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			txbuf[++idx]= *pt++;
			UART_Write_Buf(UART1,txbuf,++idx) ;	
//			RTT("CurrProductQty=%d.............................................",gstProcessState.CurrProductQty);
		}
		if(gstProcessState.flgCompleteActionTable){
			gstProcessState.flgCompleteActionTable=false ;
			int idx ;
			txbuf[idx=0]=defUART_rProduceStop_0x5d ;
			txbuf[++idx]=~txbuf[0] ;
			txbuf[++idx]=0 ;  //結束原因
		
			UART_Write_Buf(UART1,txbuf,++idx) ;	
			RTT("Stop Running.......................................................................................................");
			LightYellowON() ;
		}
		if(gstProcessState.flgOverUnders){
			int idx ;
			for(int i=0;i<gstProcessState.u8DriverCnt;i++){
				if(gstProcessState.flgOverUnder[i]==1){
					// overflow
					txbuf[idx=0]=defUART_rOverUnderFlow_0x5a ;
					txbuf[++idx]=~txbuf[0] ;
					txbuf[++idx]=i+1 ;
					txbuf[++idx]=1 ;
					UART_Write_Buf(UART1,txbuf,++idx) ;
					RTT("axis=%d overflow.................................................................",i+1) ;
				}
				else if(gstProcessState.flgOverUnder[i]==2){
					// underflow
					txbuf[idx=0]=defUART_rOverUnderFlow_0x5a ;
					txbuf[++idx]=~txbuf[0] ;
					txbuf[++idx]=i+1 ;
					txbuf[++idx]=0 ;
					UART_Write_Buf(UART1,txbuf,++idx) ;
					RTT("axis=%d underflow.....................................................................",i+1) ;
				}
			}
			gstProcessState.flgOverUnders=false ;
		}
		uint8_t adc = ReadAdc100() ;
		uint8_t tadc =(adc+gstProcessState.adc)/2;
		if(gstProcessState.adc != tadc){
			gstProcessState.adc=tadc ;
			SendADCToRas(gstProcessState.adc) ;
			RTT("adc = %d",adc) ;
		}
		
		if(gstProcessState.flgDisplays&& ((cnt_UserProcessPDO%DELAYMS)== 0)){
			for(int i=0 ; i < gstProcessState.u8DriverCnt;i++){
				if(gstProcessState.flgDisplay[i]){
					  gstProcessState.flgDisplay[i]=false ;
						int idx ;
						txbuf[idx=0]=0x51 ;
						txbuf[++idx]=~txbuf[0] ;
						txbuf[++idx]=i+1;
						 __disable_irq() ;
                    #if 0
					  long a,b,c,d ;
					  a=gstProcessState.src_pos[i] ;
					  b=gstProcessState.dst_pos[i] ;
						c=gstProcessState.curstep[i] ;
					  d=gstProcessState.step[i] ;
                    #endif
					  long tt= gstProcessState.src_pos[i]+(int64_t)(gstProcessState.dst_pos[i] -gstProcessState.src_pos[i])*gstProcessState.curstep[i]/gstProcessState.step[i] ;
						__enable_irq() ;
//      				RTT("0x51----------axis=%d value=%d %d  %d  %d   %d",i+1,tt,a,b,c,d) ;
					  uint8_t *pt=(uint8_t *)&tt ;
						txbuf[++idx]= *pt++;
						txbuf[++idx]= *pt++;
						txbuf[++idx]= *pt++;
						txbuf[++idx]= *pt++;
						UART_Write_Buf(UART1,txbuf,++idx) ;					
				}
			}
			gstProcessState.flgDisplays=false ;
		}
		if(!flgMoveStep){
			if(flgDispZero){
				  RTT("DispZero = %d",NoMoveStep) ;
				  for(int i=0 ; i < NoMoveStep;i++){
						RTT("axis=%d to zero",MoveStep[i].axis) ;
					}
					if(gstProcessState.stateMoveStep == STATE_MOVE_STEP){
						for(int i=0 ; i < NoMoveStep;i++){
							int idx ;
							txbuf[idx=0]=0x51 ;
							txbuf[++idx]=~txbuf[0] ;
							txbuf[++idx]=MoveStep[i].axis;
							txbuf[++idx]= 0;
							txbuf[++idx]= 0;
							txbuf[++idx]= 0;
							txbuf[++idx]= 0;
							UART_Write_Buf(UART1,txbuf,++idx) ;
						}
					}
				  for(int i=0 ; i < NoMoveStep;i++){
						int idx ;
						txbuf[idx=0]=(gstProcessState.stateMoveStep== STATE_MOVE_STEP)?defUART_rMOVE_STEP_OK_0x61:defUART_rMOVE_VR_STEP_OK_0x62 ;  // MOVE_STEP_OK/MOVE_VR_STEP_OK
						RTT("MOVE_OK=%d",txbuf[0]) ;
						txbuf[++idx]=~txbuf[0] ;
						txbuf[++idx]=MoveStep[i].axis;
						UART_Write_Buf(UART1,txbuf,++idx) ;
					}
					flgDispZero=false ;
			}
		}
	  if((MAN_MOV.DrvIdx== 0xff)&&!flgMoveStep && UART_Complete()&&Sync_MAN_MOV()){
			  // rsapberry PI 有送資料來
			uint8_t DrvIdx;
			uint8_t idx =0 ;
			uint8_t data ;
			uint8_t *pt ;
			long  dst_pos ;
			int axis ;
 			RTT("cmd=%x ,ridx_CmdBufTbl=%d ,widx_CmdBufTbl=%d",CmdBufTbl[ridx_CmdBufTbl].cmd,ridx_CmdBufTbl,widx_CmdBufTbl) ;
			switch(CmdBufTbl[ridx_CmdBufTbl].cmd){
				case  defUART_wSlow_0xdd :
					gstProcessState.buffersize =*((uint16_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx])) ;
				  RTT("-----------------------------------buffer size =%d  %d",gstProcessState.buffersize,DELAYMS)
				  break ;
				case defUART_wSetNearPosition_0xE2:
					DrvIdx=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
				  if(DrvIdx !=0){
						NearMotor[DrvIdx-1]=*((uint16_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx])) ;
						RTT("SetNearPosition :axis=%d near=%d",DrvIdx,NearMotor[DrvIdx-1]) ;
					}
					break ;
				case defUART_wCurrProductQty_0xa4:
					gstProcessState.CurrProductQty=*((uint32_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx])) ;
					RTT("CurrProductQty=%d........................................",gstProcessState.CurrProductQty) ;
					gstProcessState.flgCurrProductQty=false ;
				  break ;
				case defUART_wSetProductQty_0xa5:
					gstProcessState.SetProductQty=*((uint32_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx])) ;
					RTT("setProductQty=%d........................................",gstProcessState.SetProductQty) ;
				  break ;
				case defUART_wFullRun_0xa8:
// 					gstProcessState.RUNTEST=EC_RUN_MODE ;
					RTT("XXXXXXXXXXXXXXXXXXXXXXXXXX_________________EC_RUN_MODE") ;
				  break ;
				case defUART_wTestRun_0xa9:
// 					gstProcessState.RUNTEST=EC_TEST_MODE ;
					RTT("XXXXXXXXXXXXXXXXXXXXXXXX___________________EC_TEST_MODE") ;
				  break ;
				case defUART_wVR_AUTO_0xab: //原點模式 
					data=CmdBufTbl[ridx_CmdBufTbl].buf[idx] ; 
				  gstProcessState.VRAUTOHOME=(data==0)?EC_VRHOME_MODE:EC_AUTOHOME_MODE ;
				  if(data==0){
						RTT("EC_VRHOME_MODE......................................................") ;
					}
					else{
						RTT("EC_AUTOHOME_MODE....................................................");
					}
					break ;
				case defUART_wAIR_SET_0xc4:
					data=CmdBufTbl[ridx_CmdBufTbl].buf[idx] ;
				  uint8_t tair=CmdBufTbl[ridx_CmdBufTbl].buf[++idx] ;
					FPGA_WRITE8(0xC00,data) ;
				  RTT("SET    AIR %x TAIR %x\n",data,tair) ;
				
				  for(int i=0 ; i< 4; i++){
						if(tair &0x1){
							SetTouchAir(i+1) ;
						}
						else{
							ClrTouchAir(i+1) ;
						}
						tair >>=1 ;
					}
				
					break ;
				case defUART_wManualUpDown_0xc0:				//手動加減鍵					
					DrvIdx=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;

					MAN_MOV.dir=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
					MAN_MOV.frwstep=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				
					MAN_MOV.frwdir= MAN_MOV.dir ;
					if(MAN_MOV.frwstep& BIT31){
						MAN_MOV.frwstep = -(int)MAN_MOV.frwstep ;
						MAN_MOV.frwdir=(MAN_MOV.frwdir==0)?1:0 ;
					}
					idx+=4 ;
				  
					MAN_MOV.step=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					idx+=4 ;
				
				
				  MAN_MOV.lstep=*((uint32_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx]) );
				  
					RTT("Axis=%d,dir=%u,frwstep=%d step=%d,ldir=%x,lstep=%08d\n",DrvIdx,MAN_MOV.dir,MAN_MOV.frwstep,MAN_MOV.step,MAN_MOV.ldir,MAN_MOV.lstep) ;
					
					
				  MAN_MOV.state=STATE_INC_MANMOV ;
					RTT("START MANUAL MOV ............................................") ;
				  MAN_MOV.ms=0 ;
				  MAN_MOV.acc=0 ;
					MAN_MOV.frwacc=0;
					MAN_MOV.DrvIdx=DrvIdx-1 ;//開始動作
// 					TRACE_TASK_START(1);
					txbuf[idx=0]=0x51 ;
					txbuf[++idx]=~txbuf[0] ;
					txbuf[++idx]=DrvIdx;
				  pt=(uint8_t*)&MAN_MOV.lstep ;
					txbuf[++idx]= *pt++;
					txbuf[++idx]= *pt++;
					txbuf[++idx]= *pt++;
					txbuf[++idx]= *pt++;;
					UART_Write_Buf(UART1,txbuf,++idx) ;
// 					TRACE_TASK_END(1) ;	
					break ;
				case defUART_wMode_0xc3:
					
					MAN_MOV.mode=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
				  uint8_t Axis=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
					if(MAN_MOV.mode==0){
						RTT("to LOGical MODE\n") ;
					}
					else if(MAN_MOV.mode ==1){
							RTT("to Physical MODE  Axis=%d\n",Axis) ;
							if(Axis ==0xff){
								//送出各軸的實際位置
								for(int i=0 ; i < gstProcessState.u8DriverCnt ; i++){
// 									TRACE_TASK_START(100+i);
									int idx;
									txbuf[idx=0]=0x51 ;
									txbuf[++idx]=~txbuf[0] ;
									txbuf[++idx]=i+1;
									txbuf[++idx]= gstProcessState.u32Pos[i];
									txbuf[++idx]= gstProcessState.u32Pos[i]>>8;
									txbuf[++idx]= gstProcessState.u32Pos[i]>>16;
									txbuf[++idx]= gstProcessState.u32Pos[i]>>24;
									UART_Write_Buf(UART1,txbuf,++idx) ;
									RTT("%d,%u %08x",i+1,gstProcessState.u32Pos[i],gstProcessState.u32Pos[i]);
// 							    TRACE_TASK_END(100+i) ;	
                                }
								//送出結束軸(0)
								int idx;
								txbuf[idx=0]=0x51 ;
								txbuf[++idx]=~txbuf[0] ;
								txbuf[++idx]=0;
								txbuf[++idx]= 0;
								txbuf[++idx]= 0;
								txbuf[++idx]= 0;
								txbuf[++idx]= 0;
								UART_Write_Buf(UART1,txbuf,++idx) ;
								RTT("%d,%d",0,0);				
							}
							else{
								Axis-- ;
								int idx;
								txbuf[idx=0]=0x51 ;
								txbuf[++idx]=~txbuf[0] ;
								txbuf[++idx]=Axis+1;
								txbuf[++idx]= gstProcessState.u32Pos[Axis];
								txbuf[++idx]= gstProcessState.u32Pos[Axis]>>8;
								txbuf[++idx]= gstProcessState.u32Pos[Axis]>>16;
								txbuf[++idx]= gstProcessState.u32Pos[Axis]>>24;
								UART_Write_Buf(UART1,txbuf,++idx) ;
								RTT("%d,%u  %08x",Axis+1,gstProcessState.u32Pos[Axis],gstProcessState.u32Pos[Axis]);
							}
					 
					}
				  RTT("end Mode....") ;
					break ;
				case defUART_wSmartBack_0xE6 :
						gstProcessState.SmartBack=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
				    break ;				  
				case  defUART_wSPD_CHANGE_0x2d:
						ActionTable[NoActionTable].actcmd=2 ;
						ActionTable[NoActionTable].axis=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
						NoActionTable++  ;
						break ;
					
				case defUART_wMOVE_0xd0:
				case defUART_wMOVE_R_0xd9:
					ActionTable[NoActionTable].actcmd=0 ;
					ActionTable[NoActionTable].axis=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
				
				  ActionTable[NoActionTable].FileNo =*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
				
				  ActionTable[NoActionTable].N =*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
				  ActionTable[NoActionTable].Start_ms=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					idx+=4 ;
// 				  RTT("------%d   %d %d",ActionTable[NoActionTable].Start_ms,NoActionTable,ridx_CmdBufTbl) ;
				
				  ActionTable[NoActionTable].ms =*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
				
				  ActionTable[NoActionTable].idms =*(unsigned short*)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
				  
				  if(CmdBufTbl[ridx_CmdBufTbl].cmd==defUART_wMOVE_0xd0){
						ActionTable[NoActionTable].frwstep=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
						ActionTable[NoActionTable].frwdir=0 ;
						if(ActionTable[NoActionTable].frwstep & BIT31){
								ActionTable[NoActionTable].frwstep=-(int)ActionTable[NoActionTable].frwstep;
								ActionTable[NoActionTable].frwdir=1 ;
						}
						idx+=4 ;
					}
					else{
						ActionTable[NoActionTable].frwstep=0 ;
						ActionTable[NoActionTable].frwdir=0 ;
					}
					ActionTable[NoActionTable].step=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  ActionTable[NoActionTable].dir=0 ;
				  if(ActionTable[NoActionTable].step & BIT31){
							ActionTable[NoActionTable].step=-(int)ActionTable[NoActionTable].step;
						  ActionTable[NoActionTable].dir=1 ;
					}
					idx+=4 ; 
					
					ActionTable[NoActionTable].dst_pos=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					idx+=4 ;
					uint32_t tms=ActionTable[NoActionTable].Start_ms+ActionTable[NoActionTable].ms;
					if(tms > End_msActionTable){
						End_msActionTable=tms ;
					}
					ActionTable[NoActionTable].Feed=(CmdBufTbl[ridx_CmdBufTbl].cmd == 0xd9)? true : false ;
					 _delay() ; RTT("no=%d cmd=%x axis=%d FileN=%d N=%d start_ms=%d ms=%d idms=%d frwstep=%d dir=%d step=%d  dst_pos=%d",NoActionTable,CmdBufTbl[ridx_CmdBufTbl].cmd,ActionTable[NoActionTable].axis,ActionTable[NoActionTable].FileNo,ActionTable[NoActionTable].N,ActionTable[NoActionTable].Start_ms,ActionTable[NoActionTable].ms,ActionTable[NoActionTable].idms,ActionTable[NoActionTable].frwstep,ActionTable[NoActionTable].dir,ActionTable[NoActionTable].step,ActionTable[NoActionTable].dst_pos) ; _delay() ;
// 				  TouchFail_Pair_ActionTable(ActionTable[NoActionTable].FileNo,
//                                              ActionTable[NoActionTable].Start_ms,
//                                              NoActionTable
//                                              );
                  NoActionTable++  ;
// 					RTT("End_msActionTable=%d NoActionTable=%d ",End_msActionTable,NoActionTable);
					break ;
				case defUART_wAIR_0xE0:
					ActionTable[NoActionTable].actcmd=1 ;
				  ActionTable[NoActionTable].N =*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
				  ActionTable[NoActionTable].air 	=CmdBufTbl[ridx_CmdBufTbl].buf[idx++];
				  ActionTable[NoActionTable].Start_ms=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					idx+=4 ;
				
				  ActionTable[NoActionTable].ms =*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				
				
					if(ActionTable[NoActionTable].ms!=0){		
						tms=ActionTable[NoActionTable].Start_ms+ActionTable[NoActionTable].ms;
						if(tms > End_msActionTable){
							End_msActionTable=tms ;
						}
						RTT("cmd=%x FileNo=%d N=%d start_ms=%d ms=%d",CmdBufTbl[ridx_CmdBufTbl].cmd,ActionTable[NoActionTable].FileNo,ActionTable[NoActionTable].N,ActionTable[NoActionTable].Start_ms) ;
						NoActionTable++  ;
					}
					else{
						RTT("skip_cmd(ms=0)=%x FileNo=%d N=%d start_ms=%d ms=%d",CmdBufTbl[ridx_CmdBufTbl].cmd,ActionTable[NoActionTable].FileNo,ActionTable[NoActionTable].N,ActionTable[NoActionTable].Start_ms) ;						
					}
					break ;
				case defUART_wTOUCH_0xd7:
					ActionTable[NoActionTable].actcmd=1 ;
				  ActionTable[NoActionTable].N =*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
				  ActionTable[NoActionTable].touch 	=CmdBufTbl[ridx_CmdBufTbl].buf[idx++];
				  ActionTable[NoActionTable].FileNo 		=*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx +=2 ;
				  ActionTable[NoActionTable].Start_ms=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					idx+=4 ;
				
				  ActionTable[NoActionTable].ms =*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				
				
					if(ActionTable[NoActionTable].ms!=0){		
						tms=ActionTable[NoActionTable].Start_ms+ActionTable[NoActionTable].ms;
						if(tms > End_msActionTable){
							End_msActionTable=tms ;
						}
						RTT("cmd=%x FileNo=%d N=%d touch =%d start_ms=%d ms=%d",CmdBufTbl[ridx_CmdBufTbl].cmd,ActionTable[NoActionTable].FileNo,ActionTable[NoActionTable].N,ActionTable[NoActionTable].touch,ActionTable[NoActionTable].Start_ms) ;
						// todo
                        //檢查探針失敗後是否執行工具程式
                        if (ActionTable[NoActionTable].FileNo != 0xFFFF){
                            //TouchFail_AddJumpTable(tms, ActionTable[NoActionTable].FileNo);
                        }
                        NoActionTable++  ;
					}
					else{
						RTT("skip_cmd(ms=0)=%x FileNo=%d N=%d start_ms=%d ms=%d",CmdBufTbl[ridx_CmdBufTbl].cmd,ActionTable[NoActionTable].FileNo,ActionTable[NoActionTable].N,ActionTable[NoActionTable].Start_ms) ;						
					}
					break ;
				case defUART_wREPEAT_0xE3:
					{
						Repeat[NoRepeat].Start_ms=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx] );
						idx+=4 ;
						Repeat[NoRepeat].End_ms=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx] );
						idx+=4 ;
						Repeat[NoRepeat].CNT=*(uint16_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx] );
						idx+=2 ;
						//找到REPEAT StartActionTable
						uint16_t idx= NoActionTable-1 ;
						for(;;){
							if(ActionTable[idx].Start_ms == Repeat[NoRepeat].Start_ms) break ;
							idx-- ;
						}
						for(;;){
							if(ActionTable[idx].Start_ms != Repeat[NoRepeat].Start_ms) break ;
							idx-- ;
						}
						Repeat[NoRepeat].StartActionTable=idx+1 ;
						Repeat[NoRepeat].Len_ms=Repeat[NoRepeat].End_ms-Repeat[NoRepeat].Start_ms ;
						Repeat[NoRepeat].Last_ms=Repeat[NoRepeat].Start_ms+Repeat[NoRepeat].Len_ms*Repeat[NoRepeat].CNT;
						RTT("Repeat---noRepeat=%d  Start_ms=%d End_ms=%d CNT=%d StartActionTable=%d ,Len_ms+%d Last_ms=%d ",NoRepeat,Repeat[NoRepeat].Start_ms,Repeat[NoRepeat].End_ms,Repeat[NoRepeat].CNT,Repeat[NoRepeat].StartActionTable,Repeat[NoRepeat].Len_ms,Repeat[NoRepeat].Last_ms) ;
						NoRepeat++ ;
					}
					break ;
				case defUART_wSTART_ACT_0x2a:
					{	
					  uint16_t PN=*(unsigned short *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
						RTT("START_ACT No=%d",PN)
						if(PN== 0xffff){
							//主程式
							gstProcessState.NoProgramNo=0 ;
						  NoRepeat=0 ;
							gstProcessState.ProgramNo[gstProcessState.NoProgramNo]=PN ;
							gstProcessState.StartActionTable[gstProcessState.NoProgramNo]=NoActionTable=0 ;
							End_msActionTable=0 ;
              //TouchFail_InitJumpTable();
						}
						else{
							gstProcessState.NoProgramNo++ ;
							gstProcessState.ProgramNo[gstProcessState.NoProgramNo]=PN ;
							gstProcessState.StartActionTable[gstProcessState.NoProgramNo]=NoActionTable ;
							End_msActionTable=0 ;
              //TouchFail_StartConfigActionTable(true, NoActionTable+1);
						}
						break;
					}
					
				case defUART_wEND_ACT_0x2b:
					{
					  uint8_t continues=CmdBufTbl[ridx_CmdBufTbl].buf[idx] ;
						RTT("END_ACT  continues=%d",continues)
						ActionTable[NoActionTable].Start_ms=End_msActionTable ;
						ActionTable[NoActionTable].ms=0 ;
						NoActionTable++ ;
            //TouchFail_StartConfigActionTable(false, 0xFFFF);
						if(continues){
						}
						else{
							//更新actcmd==2的Start_ms
							for(uint16_t i=0; i <NoActionTable;i++){
								if(ActionTable[i].actcmd == 2){
									ActionTable[i].Start_ms=ActionTable[i+1].Start_ms ;
									ActionTable[i].ms=1 ;									
								}
							}
							gstProcessState.flgStopMachine=gstProcessState.flgreadyStopMachine=false ;
							idxActionTable=0 ;
							idx_Repeat=0 ;
							in_Repeat=false ;
							msMoveStep=0 ;
							for(int i=0;i < MAX_AXIS ; i++){
									MoveStep[i].axis=0 ;
							}
							NoMoveStep=0 ;
							run_ini() ;
							while((idxActionTable < NoActionTable) &&(msMoveStep == ActionTable[idxActionTable].Start_ms)){
								if(ActionTable[idxActionTable].actcmd ==0){
									for(int i=0 ; i<MAX_AXIS ; i++){
										if(MoveStep[i].axis ==0){
											fillActionTable(i,idxActionTable);
											if(i >= NoMoveStep){
												NoMoveStep=i+1 ;
											}
											break ;
										}
									}
								}
								else if(ActionTable[idxActionTable].actcmd ==1){
										for(int i=0 ; i< 8 ;i++){
											if(TouchAir[i].used==0){
												fillActionTable2TouchAir(i,idxActionTable);
												break ;
											}
										}
								}
								else if(ActionTable[idxActionTable].actcmd ==2){  // change spd
										gstProcessState.SPD_CHANGE=ActionTable[idxActionTable].axis*100 ;
									  gstProcessState.flagSPD_CHANGE=true ;
								}

								idxActionTable++ ;
							}
							gstProcessState.remind =0 ;
							flgActionTable=true ;
							LightGreenON() ;
						}
						break;
					}
			  case defUART_wSTART_MOVE_STEP_0xd1: //回原點
				  RTT("START_STEP")
				  NoMoveStep=0 ;
					break;
			  case defUART_wEND_MOVE_STEP_0xd3:
				  RTT("END_STEP")
				  msMoveStep=0 ;
					gstProcessState.remind =0 ;
				  bool allzero=true ;
				  for(int i=0  ; i < NoMoveStep ;i++){
						int axis= MoveStep[i].axis-1;
						gstProcessState.step[axis]=MoveStep[i].step ;
						if(gstProcessState.step[axis] !=0){
							allzero=false ;
						}
						gstProcessState.src_pos[axis]=MoveStep[i].src_pos ;
						gstProcessState.dst_pos[axis]=0 ;
						gstProcessState.OrgPos[axis]=0 ;
						gstProcessState.curstep[axis]=0 ;
					}
					gstProcessState.stateMoveStep=STATE_MOVE_STEP  ;
					if(!allzero){
						gstProcessState.flgreadyStopMachine=false ;
						flgMoveStep=true ;
					}
					else{
						flgDispZero = true ;
					}
					break;
			  case defUART_wMOVE_STEP_0xd2 : //回原點及虛擬原點的MOVE_STEP
					MoveStep[NoMoveStep].axis=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
				  MoveStep[NoMoveStep].ms =*(uint32_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=4 ;				
					MoveStep[NoMoveStep].idms =*(uint16_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
			
					MoveStep[NoMoveStep].frwstep=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					idx+=4 ;
					MoveStep[NoMoveStep].step=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					idx+=4 ;
				
					MoveStep[NoMoveStep].src_pos=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
			 

  				MoveStep[NoMoveStep].acc=0 ;
				  MoveStep[NoMoveStep].dir=0 ;
				  MoveStep[NoMoveStep].curstepAcc=0 ;
				  
				  if(MoveStep[NoMoveStep].step & BIT31){
							MoveStep[NoMoveStep].step=-(int)MoveStep[NoMoveStep].step;
						  MoveStep[NoMoveStep].dir=1 ;
					}
  				MoveStep[NoMoveStep].frwacc=0 ;
				  MoveStep[NoMoveStep].frwdir=0 ;
				  if(MoveStep[NoMoveStep].frwstep & BIT31){
							MoveStep[NoMoveStep].frwstep=-(int)MoveStep[NoMoveStep].frwstep;
						  MoveStep[NoMoveStep].frwdir=1 ;
					}
					
					RTT("cmd=%x axis=%d ms=%d idms=%d  dir=%d frwstep=%d step=%d src_pos=%d ",CmdBufTbl[ridx_CmdBufTbl].cmd,MoveStep[NoMoveStep].axis,MoveStep[NoMoveStep].ms,MoveStep[NoMoveStep].idms,MoveStep[NoMoveStep].dir,MoveStep[NoMoveStep].frwstep,MoveStep[NoMoveStep].step,MoveStep[NoMoveStep].src_pos) ;	
          NoMoveStep++ ;			  
					break;
				case defUART_wSTART_VR_STEP_0xd4:
					RTT("START_VR_STEP");
				  NoMoveStep=0 ;
					break ;
				case defUART_wMOVE_VR_STEP_0xd5:
					MoveStep[NoMoveStep].axis = CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ; 
					MoveStep[NoMoveStep].ms=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=4 ;
					MoveStep[NoMoveStep].idms=*(uint16_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=2 ;
					MoveStep[NoMoveStep].frwstep=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=4 ;
					MoveStep[NoMoveStep].step=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
				  idx+=4 ;
  				MoveStep[NoMoveStep].acc=0 ;
				  MoveStep[NoMoveStep].dir=0 ;
				  if(MoveStep[NoMoveStep].step & BIT31){
							MoveStep[NoMoveStep].step=-(int)MoveStep[NoMoveStep].step;
						  MoveStep[NoMoveStep].dir=1 ;
					}
					MoveStep[NoMoveStep].frwacc=0 ;
				  MoveStep[NoMoveStep].frwdir=0 ;
				  if(MoveStep[NoMoveStep].frwstep & BIT31){
							MoveStep[NoMoveStep].frwstep=-(int)MoveStep[NoMoveStep].frwstep;
						  MoveStep[NoMoveStep].frwdir=1 ;
					}
					
					
					
					MoveStep[NoMoveStep].dst_pos=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
					RTT("cmd=%x axis=%d ms=%d idms=%d dir=%d frwstep=%d step=%d  dst_pos=%d ",CmdBufTbl[ridx_CmdBufTbl].cmd,MoveStep[NoMoveStep].axis,MoveStep[NoMoveStep].ms,MoveStep[NoMoveStep].idms,MoveStep[NoMoveStep].dir,MoveStep[NoMoveStep].frwstep,MoveStep[NoMoveStep].step,MoveStep[NoMoveStep].dst_pos) ;	
				  NoMoveStep++ ;
					break ;
				case defUART_wEND_VR_STEP_0xd6:
					RTT("END_VR_STEP");
				  msMoveStep=0 ;
					gstProcessState.remind =0 ;
				  for(int i=0  ; i < NoMoveStep ;i++){
						int axis= MoveStep[i].axis-1;
						gstProcessState.step[axis]=MoveStep[i].step ;
						gstProcessState.src_pos[axis]=gstProcessState.dst_pos[axis] ;
						gstProcessState.dst_pos[axis]=MoveStep[i].dst_pos ;
						gstProcessState.curstep[axis]=0 ;
						gstProcessState.OrgPos[axis]=MoveStep[i].dst_pos ;
					}
					gstProcessState.flgreadyStopMachine=false ;
					gstProcessState.stateMoveStep=STATE_MOVE_VR_STEP  ;
				  flgMoveStep=true ;
				  break ;
				case 	defUART_wSetCurrLogiPos_0xE1:
					{
						int axis = CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ; 
						long dst_pos=*(uint32_t *)(&CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
						idx+=4 ;
						gstProcessState.dst_pos[axis]=dst_pos ;
				    RTT("setlogicPos axis=%d dst_pos=%d",axis,dst_pos) ;
				
				
						txbuf[idx=0]=0x51 ;
						txbuf[++idx]=~txbuf[0] ;
						txbuf[++idx]=axis;
						uint8_t *pt=(uint8_t *)&dst_pos ;
	
						txbuf[++idx]= *pt++;
						txbuf[++idx]= *pt++;
						txbuf[++idx]= *pt++;
						txbuf[++idx]= *pt++ ;
						UART_Write_Buf(UART1,txbuf,++idx) ;
					}
					break ;
				case defUART_wProgramToolRun_0xda:
					RTT("ProgramToolRun") ;
				  gstProcessState.flgProgramToolRun=true ;
				  break ;
				case defUART_wCurrFailQty_0xa6:
					RTT("cur Touch fail") ;
					gstProcessState.CurrFailQty=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
					break ;
				case defUART_wSetFailQty_0xa7:
					RTT("set Touch Error") ;
					gstProcessState.SetFailQty=CmdBufTbl[ridx_CmdBufTbl].buf[idx++] ;
					break ;
				case defUART_wStop_0xa0:
					//停機
					RTT("STOP") ;
					gstProcessState.flgStopMachine=true ;
					break ;
				case defUART_wReset_0xa2:
					//RESET
					RTT("RESET") ;
					ResetMachine() ;
					break ;
			 case defUART_AxisSwitch_0xdb:
				 //AxisSwitch
				 long AixsSwitch =*(uint32_t *)&(CmdBufTbl[ridx_CmdBufTbl].buf[idx]) ;
			   
			   RTT("AxisSwitch=%x", AixsSwitch);
			   break ;
			 case defUART_FAxisPosition_0xdc:
				FAxis=CmdBufTbl[ridx_CmdBufTbl].buf[idx];
				RTT("FAxisPosition=%d",FAxis) ;
			  FAxis-- ;
			  flgSetTouchProbeMode=true ;
 				SendADCToRas(gstProcessState.adc) ;
				SendVersionToRas() ;
				RTT("flgKeyLock=%d  flgKeySwitch=%d",flgKeyLock,flgKeySwitch) ;
			  if(flgKeyLock){
					SendKeyToRas(0x1) ;					
				}
				if(flgKeySwitch){
					SendKeyToRas(0x9) ;
				}
			  break ;
			case defUART_CurrentState_0xF0:
				gstProcessState.CurrentState=CmdBufTbl[ridx_CmdBufTbl].buf[idx];
				RTT("current state=%d",gstProcessState.CurrentState);
			  break ;
			default:
				  RTT("ERROR CMD=%x",CmdBufTbl[ridx_CmdBufTbl].cmd) ;
					
					break ;
			}
			UART_Update_ridx_CmdBufTbl() ;		
		}
		else if(0){
			//有一個按鍵存在ret
			RTT("key code=%x",ret) ;
			int idx ;
			switch(ret){
				case 0x30:
					//reset ON
					SendKeyToRas(0x7) ;
					ResetMachine()	;
				  RTT("%d",flgActionTable) ;
					break ;			
				case 0x31:
					//reset OFF
					SendKeyToRas(0x8) ;
					break ;
				case 0x32:
					//鍵盤鎖住---ON
				  flgKeyLock=true ;
					SendKeyToRas(0x1) ;
					break ;
				case 0x33:
					//鍵盤鎖住---OFF
				  flgKeyLock=false ;
					SendKeyToRas(0x2) ;
					break ;
				case 0x34:
					//鍵盤切換---ON
					SendKeyToRas(0x9) ;
				  flgKeySwitch=true ;
				  break ;
				case 0x35:
					//鍵盤切換---OFF
					SendKeyToRas(0xA) ;
				  flgKeySwitch=false ;
				  break ;
				case 0x11:
					//啟動生產
					if(gstProcessState.RUNTEST== EC_TEST_MODE){
						//測試轉生產
						gstProcessState.RUNTEST=EC_RUN_MODE ;
						int idx;
						txbuf[idx=0]=defUART_rTest2Product_0x5e ;
						txbuf[++idx]=~txbuf[0] ;
						UART_Write_Buf(UART1,txbuf,++idx) ;
					}
					else{
						SendKeyToRas(0x4) ;
					}
				  break ;
				case 0x21:
					//測試
					SendKeyToRas(0x5) ;
				  break ;
				case 0x1:
					//停機
				  gstProcessState.flgStopMachine=true ;
  				break ;
// 				case 0x11:
// 					//A HOME
// 				  if(!flgKeySwitch)break ;
// 					SendKeyToRas(0xF) ;
// 				  break ;
				case 0x22:
					//+Y
				  if(!flgKeySwitch)break ;
					SendKeyToRas(0xB) ;
				  break ;
				case 0x12:
					//-Y
				  if(!flgKeySwitch)break ;
					SendKeyToRas(0xC) ;
				  break ;
				case 0x23:
					//+A
				  if(!flgKeySwitch)break ;
					SendKeyToRas(0xD) ;
				  break ;
				case 0x13:
					//-A
				  if(!flgKeySwitch)break ;
					SendKeyToRas(0xE) ;
				  break ;
			}	
		}
	}
#endif
		
#ifdef TEST_TOUCH_PROBE		
// 	FPGA_WRITE8(0XC00, 0X0) ;   // OUTL=0xc00
	RTT("Test Touch Probe\n") ;  
// 	while(1){
// 		int ch =WAIT_KEY() ;
// 		MSG_RTT("%c",ch) ;
// 		FPGA_WRITE8(0XC00, 0Xff) ;
// 		RTT("Trigger 1\n") ;
// 		ch =WAIT_KEY() ;
// 		MSG_RTT("%c",ch) ;
// 		FPGA_WRITE8(0XC00, 0X0) ;
// 		RTT("Trigger 0\n") ;
// 	}
// 		uint8_t u8 ;
// 		EtherCatMasterStop();
// 		EtherCatSlaveSdoRead(0,0x20f8,0,1,(uint8_t *)&u8) ;
// 	  RTT("0x20f8_0=%x",u8) ;
// 		EtherCatSlaveSdoRead(0,0x20f8,1,1,(uint8_t *)&u8) ;
// 	  RTT("0x20f8_1=%x",u8) ;
// 	
// 				 
// 	  EtherCatMasterRunning();
	FPGA_WRITE8(0x114,0) ;   //diable Home interrupt
	FPGA_WRITE8(0x10a,0) ;   //diable extHome interrupt
  
	FPGA_WRITE8(0xf2,0) ;   //清除Driver Clear
//   FPGA_WRITE8(0xf9,2) ;  //T2發生時停Y軸(2)
	FPGA_WRITE8(0xc12,0x00) ; //'0'disable & clear interrupt
		while(1){
			bool ok ;
			do{
				RTT("Select Touch no") ;
				int ch =WAIT_KEY() ;
				MSG_RTT("%c",ch) ;
				ok=true ;
				if(ch =='1'){
					touch_no=ch-'1' ;
					RTT("\nwait Touch 1.....\n") ;
					FPGA_WRITE8(0xc12,0x1) ; //Touch1 enable
					FPGA_WRITE8(0xf8,2) ;  //T1發生時停Y軸(2)
				}
				else if(ch =='2'){
					RTT("\nwait Touch 2.....\n") ;
					touch_no=ch-'1' ;
					FPGA_WRITE8(0xc12,0x2) ; //Touch2 enable
					FPGA_WRITE8(0xf9,2) ;  //T2發生時停Y軸(2)
				}
				else{
					ok=false ;
					RTT("\n valid input 1/2 only\n") ;
				}
			}
			while(!ok);
			
			while(!touch_complete);
			touch_complete=false ;
			RTT("Complete current touch interrupt\n");
			
// 			uint16_t cnt=0;
// 			uint8_t clear= FPGA_READ8(0xf2) ;
// 			uint8_t flag=FPGA_READ8(0xc10) ;
// 			if(clear !=0){
// 				RTT("clear=%x \n",clear) ;
// 				FPGA_WRITE8(0xc12,0x00) ; //'0'disable & clear interrupt				
// 				FPGA_WRITE8(0xf8,0) ;  //T1發生時不停軸
// 				FPGA_WRITE8(0xf2,0) ;   //清除Driver Clear
// 			}
// 			if(flag!=0){
// 				RTT("touch int flag=%x\n",flag) ;
// 			}
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
													

  //int n, value, DDA_tmp1, DDA_tmp2,	DDA_tmp3, DDA_tmp4;
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
	
// 	MachineStatus.ONE=0x1 ;
	
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
		for(uint8 axis=0 ; axis < MAX_AXIS ; axis++){
			Ini_Feedback(axis) ;
		}
	}
	wDosMem(pc_base+0xc30,(uint16)178) ;//263ms進入重複狀態
	wDosMem(pc_base+0xc32,(uint16)11) ;//18ms重複一個鍵
// 	RetVal = setjmp(RetBuf) ;
	//
	//		按下reset鍵後,程式從此處開始執行
	//
	//
	//
	//
	
	DisableHomeInt();	
	Cvtmotor_grads();
// 	for(BYTE axis =0 ; axis < MachineStatus.axis_no ; axis++){
// 		if(NewH)DDATbl[axis].new_accval=0;
// 	}
	for(int i=0;i<4;i++)//initial硬體上探針flag
		DISABLE_TOUCH_STOP(i);
	ResetDriverClear();
	
	ReMake_flag=false;	
// 	MachineStatus.touch_before_err = false;
	StartRecActtbl=false;
	ChkSlide=false;
	safe_runtag=0;
	RetTblIdx=0;
	Air_idx=0;
	EnableTest=false ;
	HasHand=false ;
// 	MachineStatus.run_state=6;
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
	RTT("Start Run-------------\n");
	//sendError(VirtualHome,1,3);
}



void RecevieParam()
{
}

void Rs232_KeyIsr()
{
}



void KeyIsr()
{			
}


void enable_all_touch()
{
}


void disable_all_touch()
{
}



void update_sc(bool force)
{
		if(IsTimeUp(timeout_ADC) || force){
			timeout_ADC= mTimerSet(TIMER_ADC) ;
			update_sc_kernel() ;
		}
}


void sendhand(uint8 axis,uint8 meg)
{
}

void fakepara()
{

}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


