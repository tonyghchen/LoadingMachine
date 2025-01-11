#ifdef GLOBAL
#define EXTERN    
#else
#define EXTERN extern   
#endif




// #define TEST_HARDWARE
// #define TEST_BREAK_PULSE   //脈波形馬達探針測試
// #define TEST_SYNC
// #define TEST_RAM
// #define TEST_ORG   //邱展發的馬達測試程式
//#define TEST_BREAK
// #define TEST_MANMOV_KEY
#define TEST_MANMOV_UART 
// #define TEST_SDO
// #define TEST_TOUCH_PROBE
#define RTT_TRACE_LOC 


void SEGGER_SYSVIEW_Update_SampleData(uint32_t u32TargetPos, uint32_t u32ActualPos) ;

#ifdef RTT_TRACE_LOC 
typedef struct st_RTT_TRACE_LOC{
		uint8_t     axis;
		uint8_t     flg ;
	  uint32_t    lact ;
	  uint32_t    ltar ;
		int cnt ;
		int cnt1 ;
		int	lenBuf ; 
} ST_RTT_TRACE_LOC;
EXTERN	ST_RTT_TRACE_LOC	TraceLoc ;

#endif

//  定義目前狀態(current state)
#define NormalState   	 	0
#define HomeState      		1			//原點
#define TestState      		2			//測試
#define TestEditState  		3   	//測試修改-手輪可以+微調
#define ProductionState 	4   	//生產
#define CuttingState    	5			//執行快速切刀
#define AITestState				6   	//AI 區塊測試


EXTERN bool volatile touch_complete
#ifdef GLOBAL
=false
#endif
;
EXTERN int touch_no
#ifdef GLOBAL
=0
#endif
;


#ifdef TEST_BREAK
#define MAX_BREAK   500
typedef struct st_BREAK{
    uint8_t     flag;
		uint8_t     axis;
		uint32_t    idx ;
		uint32_t    Pos ;
} ST_BREAK;
EXTERN	ST_BREAK	Break ;

#endif

#ifdef TEST_SYNC
typedef struct st_SYNC{
		uint8_t     axis;
 		uint32_t    speed ;
		uint32_t  totalms ;
   uint32_t     idms;
	  uint32_t    step;
	uint8_t       dir ;
	uint32_t   Pos ;
	uint32_t    ms ;
		uint8_t     run ;
	
} ST_SYNC;
EXTERN	ST_SYNC	Sync ;

#endif

#ifdef TEST_BREAK_PULSE
#define MAX_DDACNT   50
typedef struct st_TOUCH{
		uint8_t     flag;
 		uint32_t    cnt ;	
	  uint32_t    step;
	  uint32_t    ddacnt[MAX_DDACNT] ;
	  uint32_t    idx_ddacnt;
} ST_TOUCH;
EXTERN	ST_TOUCH	Touch ;

#endif

#ifdef TEST_TOUCH_PROBE
EXTERN uint16_t ProbeState ;
EXTERN uint32_t Pos2 ;
#endif


#define S0_KEY     0   //檢查連續S0_TOUCH_KEY_CNT為1才跳態為S1KEY,同時輸出"探針測試正常"
#define S0_TOUCH_KEY_CNT    20
#define S1_KEY     1
#define S1_TOUCH_KEY_CNT    20
typedef struct st_TOUCH_KEY{
		uint8_t     state[5];
 		uint32_t    cnt[5] ;	
} ST_TOUCH_KEY;
EXTERN	ST_TOUCH_KEY	TouchKey ;
typedef struct st_RESET_KEY{
		uint8_t     state[7];
 		uint32_t    cnt[7] ;
		uint32_t  Limitcnt[7] ;	
} ST_RESET_KEY;
EXTERN	ST_RESET_KEY	ResetKey ;

typedef struct st_FUN_KEY{
		uint8_t     state[6];
 		uint32_t    cnt[6] ;
		uint32_t    Limitcnt[6] ;	
} ST_FUN_KEY;
EXTERN	ST_FUN_KEY	FunKey ;
#define S0_MPG     0
#define S0_MPG_CNT   20
#define S1_MPG     1
#define S1_MPG_CNT   50
typedef struct st_MPG{
		uint8_t     state;
 		uint32_t    cnt ;
		uint8_t    dir ;
		uint32_t   ON ;	
} ST_MPG;
EXTERN  ST_MPG  MPG ;
typedef struct st_REPEAT{
 		uint32_t    Start_ms ;
 		uint32_t    End_ms ;
		uint16_t    CNT ;
	  uint16_t    curCNT ;
	  uint16_t   StartActionTable ;
	  uint32_t   Len_ms ;
	  uint32_t   Last_ms ;
} ST_REPEAT;
EXTERN  ST_REPEAT  Repeat[10] ;
EXTERN  uint16_t   NoRepeat ;
EXTERN  uint16_t   idx_Repeat ;
EXTERN  bool   in_Repeat ;
EXTERN  uint32_t   RepeatmsMoveStep ;






//擴充記憶體的安排有1Mbytes
#define MAX_CMD_BUF 					800
#define MAX_IDMS_BUF     500			//最大500ms
#define RxCmdBuf1        0
#define TraceArraySize  (5000*4)
#define TxCmdBuf1        RxCmdBuf1+MAX_CMD_BUF
#define IdmsBuf         TxCmdBuf1+MAX_CMD_BUF
#define frwIdmsBuf      IdmsBuf+(MAX_IDMS_BUF*4*MAX_AXIS)
#define TraceLocActual     frwIdmsBuf+(MAX_IDMS_BUF*4*MAX_AXIS)
#define TraceLocTarget		TraceLocActual+TraceArraySize	
//IdmsBuf的長度,加減速最大500ms,每個佔4bytes,MAX_AXIS軸
//------------------------------------------------------------------------
//  FPGA Macros for Accessing
//------------------------------------------------------------------------
#define FPGA_READ8(u32Addr)            (*((volatile unsigned char *)(EBI_BANK0_BASE_ADDR+(u32Addr))))
#define FPGA_WRITE8(u32Addr, u32Data)  (*((volatile unsigned char *)(EBI_BANK0_BASE_ADDR+(u32Addr))) = (u32Data))


#define MANMS 50
#define FPGA_READ16(u32Addr)           (*((volatile unsigned short *)(EBI_BANK0_BASE_ADDR+(u32Addr))))
#define FPGA_WRITE16(u32Addr, u32Data) (*((volatile unsigned short *)(EBI_BANK0_BASE_ADDR+(u32Addr))) = (u32Data))
#define rDosMem(u32Addr)           (*((volatile unsigned short *)((u32Addr))))
#define FPGA_Readtest(u32Addr)           (*((volatile unsigned short *)((u32Addr))))
#define wDosMem(u32Addr, u32Data) (*((volatile unsigned short *)((u32Addr)))= (u32Data))


//------------------------------------------------------------------------
//  FPGA Macros for Accessing
//------------------------------------------------------------------------
#define FPGA_READ8(u32Addr)            (*((volatile unsigned char *)(EBI_BANK0_BASE_ADDR+(u32Addr))))
#define FPGA_WRITE8(u32Addr, u32Data)  (*((volatile unsigned char *)(EBI_BANK0_BASE_ADDR+(u32Addr))) = (u32Data))
#define FPGA_READ16(u32Addr)           (*((volatile unsigned short *)(EBI_BANK0_BASE_ADDR+(u32Addr))))
#define FPGA_WRITE16(u32Addr, u32Data) (*((volatile unsigned short *)(EBI_BANK0_BASE_ADDR+(u32Addr))) = (u32Data))	
	
//------------------------------------------------------------------------
//  SARM Macros for Accessing
//------------------------------------------------------------------------
#define SRAM_READ8(u32Addr)            (*((volatile unsigned char *)(EBI_BANK1_BASE_ADDR+(u32Addr))))
#define SRAM_WRITE8(u32Addr, u32Data)  (*((volatile unsigned char *)(EBI_BANK1_BASE_ADDR+(u32Addr))) = (u32Data))
#define SRAM_READ16(u32Addr)           (*((volatile unsigned short *)(EBI_BANK1_BASE_ADDR+(u32Addr))))
#define SRAM_WRITE16(u32Addr, u32Data) (*((volatile unsigned short *)(EBI_BANK1_BASE_ADDR+(u32Addr))) = (u32Data))	
#define SRAM_READ32(u32Addr)           (*((volatile unsigned int *)(EBI_BANK1_BASE_ADDR+(u32Addr))))
#define SRAM_WRITE32(u32Addr, u32Data) (*((volatile unsigned int  *)(EBI_BANK1_BASE_ADDR+(u32Addr))) = (u32Data))	
#define SRAM_PTR(data_type,u32Addr)               (((volatile data_type *)(EBI_BANK1_BASE_ADDR+(u32Addr))))

void fillActionTable(int idxMS,int idxAT) ;
void SetAir(int airno);
void ClrAir(int airno);
void SetTouchAir(int airno);
void ClrTouchAir(int airno);
void fillActionTable2TouchAir(int idxMS,int idxAT) ;
#define MAX_CMDBUFTBL    100
struct CMDBUFTBL{
	uint32_t  ms ;
	uint8_t  cmd ;
	uint8_t  buf[30] ;
} ;
EXTERN struct CMDBUFTBL CmdBufTbl[MAX_CMDBUFTBL] ;
EXTERN int ridx_CmdBufTbl  ;
EXTERN int widx_CmdBufTbl ;
EXTERN int CmdState ;
enum{CMD1,CMD2,ST_DATA} ;


#define SIO_RING_BUF_LEN   0x100

#define SO_BUF_LEN         (SIO_RING_BUF_LEN)
#define SI_BUF_LEN         (SIO_RING_BUF_LEN)

#define UART_RING_BUFSIZE               SO_BUF_LEN
#define __UART_BUF_MASK                 (UART_RING_BUFSIZE-1)
#define __UART_BUF_INCR(bufidx)          (bufidx=(bufidx+1)&__UART_BUF_MASK)

typedef struct uart_info_st
{
        uint16_t              so_buf_put_idx, so_buf_get_idx;
        uint16_t              si_buf_put_idx, si_buf_get_idx, si_buf_len;
        uint8_t               si_buf[SI_BUF_LEN];
        uint8_t               so_buf[SO_BUF_LEN];
	
				void send_bytes(char *data, int nDataSize) {
						for(int i =0; i < nDataSize; i++){
								so_buf[so_buf_put_idx] = data[i]; 
                __UART_BUF_INCR(so_buf_put_idx); 
						}
				}
				
				int read_bytes(char *data, int nDataSize)
				{
						int nReadBytes = 0;
					
						while(si_buf_len > 0){
								if (nReadBytes < nDataSize){
								    *data++ = (char)si_buf[si_buf_get_idx];
								    __UART_BUF_INCR(si_buf_get_idx);
									nReadBytes++;
                                    si_buf_len--;
								}
								else{
								    break;
								}
						}
						return (nReadBytes);
				}				
} MODULE_UART_INFO_Typedef;

EXTERN MODULE_UART_INFO_Typedef  gstUARTModbus;
#define defUART_rKeySpeed_0x56					0x56		//測試旋鈕速度值
#define defUART_rCurrProductQty_0x57		0x57		//目前生產量 - 表格
#define defUART_rCurrProductTime_0x58		0x58		//目前生產時間 (ms) - 時間軸
#define defUART_rOverUnderFlow_0x5a			0x5a
#define defUART_rN_0x5b									0x5b
#define defUART_rProduceStop_0x5d				0x5d
#define defUART_rTest2Product_0x5e			0x5e
#define defUART_rMOVE_STEP_OK_0x61			0x61
#define defUART_rMOVE_VR_STEP_OK_0x62		0x62
#define defUART_rTouchStatus_0x63				0x63
#define defUART_rTouchOK_0x64						0x64
#define defUART_rPowerDown_0x67					0x67
#define defUART_LoadCellData_0x70           0x70


#define defUART_wSTART_ACT_0x2a					0x2a
#define defUART_wEND_ACT_0x2b						0x2b
#define defUART_wSPD_0x2c            		0x2c
#define defUART_wSPD_CHANGE_0x2d     		0x2d


#define defUART_wStop_0xa0							0xa0		//停機 (做完目前彈簧停止)
#define defUART_wReset_0xa2							0xa2		//重置(立即停止)
#define defUART_wCurrProductQty_0xa4		0xa4		//目前生產量
#define defUART_wSetProductQty_0xa5			0xa5		//設定生產量
#define defUART_wCurrFailQty_0xa6				0xa6		//目前失誤量
#define defUART_wSetFailQty_0xa7				0xa7		//設定失誤量
#define defUART_wFullRun_0xa8						0xa8		//全速生產
#define defUART_wTestRun_0xa9						0xa9		//測試生產
#define defUART_wStepRun_0xaa						0xaa		//手輪生產
#define defUART_wVR_AUTO_0xab						0xab    //原點模式 
#define defUART_wManualUpDown_0xc0			0xc0		//手動加減
#define defUART_wPosition_0xc2					0xc2		//位置設定
#define defUART_wMode_0xc3							0xc3		//模式設定
#define defUART_wAIR_SET_0xc4						0xc4		//汽缸設定

#define defUART_wMOVE_0xd0							0xd0		//MOVE
#define defUART_wSTART_MOVE_STEP_0xd1 	0xd1  	//START_MOVE_STEP
#define defUART_wMOVE_STEP_0xd2					0xd2 		//MOVE STEP
#define defUART_wEND_MOVE_STEP_0xd3			0xd3    //END_MOVE_STEP
#define defUART_wSTART_VR_STEP_0xd4			0xd4		//START_VR_STEP
#define defUART_wMOVE_VR_STEP_0xd5			0xd5		//MOVE VR STEP
#define defUART_wEND_VR_STEP_0xd6				0xd6		//END_VR_STEP
#define defUART_wTOUCH_0xd7					    0xd7		//TOUCH
#define defUART_wMOVE_TOUCH_0xd8				0xd8    // MOVE_TOUCH
#define defUART_wMOVE_R_0xd9						0xd9		//MOVE_R (送線)
#define defUART_wProgramToolRun_0xda		0xda		//工具程式執行
#define defUART_AxisSwitch_0xdb         0xdb    //軸開關狀態
#define defUART_FAxisPosition_0xdc      0xdc    //送線軸資訊
#define defUART_wSlow_0xdd							0xdd		//降速
#define defUART_HandWheelPower_0xDE			0xDE    //手輪倍率
#define defUART_HandWheelAxis_0xDF			0xDF      //手輪選軸
#define defUART_wAIR_0xE0								0xe0		//AIR
#define defUART_wSetCurrLogiPos_0xE1		0xe1		//設定目前邏輯位置
#define defUART_wSetNearPosition_0xE2		0xe2		//設定接近位置
#define defUART_wREPEAT_0xE3						0xe3		//重複
#define defUART_wSmartBack_0xE6					0xe6		//智慧到位
#define defUART_CurrentState_0xF0				0xF0    //目前的狀態


struct UART_CMDTBL{
	uint8_t  cmd ;
	uint8_t   length ;
} ;
EXTERN struct UART_CMDTBL UART_cmdtbl[]
#ifdef GLOBAL
={
	{defUART_wSTART_ACT_0x2a				,2} , //ProgramNo(2), 0xFFFF:主程式, 其他:工具程式)
	{defUART_wEND_ACT_0x2b					,1} ,	//State(1), 0: End, 1: Continous
  {defUART_wSPD_0x2c              ,1} ,
	{defUART_wSPD_CHANGE_0x2d   		,1} ,
  {defUART_wStop_0xa0							,0} , //停機
  {defUART_wReset_0xa2						,0} , //重置
	{defUART_wCurrProductQty_0xa4		,4} ,	//目前生產量
	{defUART_wSetProductQty_0xa5		,4} ,	//設定生產量
	{defUART_wCurrFailQty_0xa6			,1} ,	//目前失誤量
 	{defUART_wSetFailQty_0xa7				,1} ,	//設定失誤量
	{defUART_wFullRun_0xa8					,0} , //全速生產
	{defUART_wTestRun_0xa9					,0} , //測試生產
  {defUART_wStepRun_0xaa					,0} ,	//手輪生產
  {defUART_wVR_AUTO_0xab					,1} , //原點模式
	{defUART_wManualUpDown_0xc0			,14} ,	//手動加減
	{defUART_wPosition_0xc2					,4} ,	//位置設定
	{defUART_wMode_0xc3							,2} ,	//模式設定
	{defUART_wAIR_SET_0xc4					,2} ,	//汽缸設定
	{defUART_wMOVE_0xd0							,23+2} ,	//MOVE fileno(2)
	{defUART_wSTART_MOVE_STEP_0xd1	,0} ,
	{defUART_wMOVE_STEP_0xd2				,19} ,
	{defUART_wEND_MOVE_STEP_0xd3		,0} ,
	{defUART_wSTART_VR_STEP_0xd4		,0} ,
	{defUART_wMOVE_VR_STEP_0xd5			,19} ,
  {defUART_wEND_VR_STEP_0xd6			,0} ,
	{defUART_wTOUCH_0xd7				    ,11} ,
	{defUART_wMOVE_TOUCH_0xd8				,23+2} , // move_TOUCH
 	{defUART_wMOVE_R_0xd9						,19+2} , // move_Feed
 	{defUART_wSlow_0xdd							,2} ,   //raspiberrey buffer size降速 
  {defUART_wProgramToolRun_0xda		,0} , // 工具程式執行
	
	{defUART_AxisSwitch_0xdb        ,4} ,
	{defUART_FAxisPosition_0xdc     ,1} ,
	{defUART_HandWheelPower_0xDE    ,1} ,
	{defUART_HandWheelAxis_0xDF     ,1} ,
	{defUART_wAIR_0xE0				      ,9} ,
	{defUART_wSetCurrLogiPos_0xE1	 	,5} ,
	{defUART_wSetNearPosition_0xE2	,3} ,
	{defUART_wREPEAT_0xE3						,10} ,
	{defUART_wSmartBack_0xE6				,1} ,
	{defUART_CurrentState_0xF0 			,1} ,
 	{0,0}  //結束
} 
#endif
;
EXTERN bool  flgEStop
#ifdef GLOBAL
=false
#endif
;
EXTERN bool volatile  flgRePower
#ifdef GLOBAL
=false
#endif
;
EXTERN bool volatile  flgSetTouchProbeMode
#ifdef GLOBAL
=false
#endif
;

EXTERN int FAxis
#ifdef GLOBAL
=1
#endif
;
EXTERN bool  flgDisplayErr
#ifdef GLOBAL
=false
#endif
;
EXTERN bool  flgResetCmd
#ifdef GLOBAL
=false
#endif
;
EXTERN bool   flgDisplayADC0
#ifdef GLOBAL
=false
#endif
;

#define NormalState      	0
#define HomeState    			1
#define TestState   			2
#define TestEditState     3
#define ProductionState   4
#define CuttingState      5
#define AITestState       6
#define AIStepTestState 	7
#define VRHOMEState 			8
#define SPHOMEState				9
void SetHandWheelPower(uint8_t t1) ;
void SetSPD(uint8_t) ;
void SetSPD_CHANGE(uint8_t) ;

EXTERN uint16_t noWaitMotor
#ifdef GLOBAL
=0
#endif
;







