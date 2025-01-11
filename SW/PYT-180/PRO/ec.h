

#ifdef GLOBAL
#define EXTERN    
#else
#define EXTERN extern   
#endif




#define MAX_DRIVER		30
typedef struct st_driver_para{
    uint32_t    u32PPR;
	  uint32_t    u32InitPos;
    uint32_t    u32Pos;
    uint32_t    u32SumVel;  
} ST_DRIVER_PARA_T;
#define EC_RUN_MODE  0
#define EC_TEST_MODE 1
#define EC_VRHOME_MODE     0
#define EC_AUTOHOME_MODE   1

#define STATE_MOVE_STEP    0
#define STATE_MOVE_VR_STEP   1
typedef struct st_process_state{
    uint8_t     u8RunMode;
    uint8_t     u8ReserveRotation;  
    
    uint32_t    u32RunCounter;
    uint32_t    u32MatchCounter;    
		bool flgOverUnders ;
    
    // for Driver
		uint8_t     u8DriverCnt;    
    ST_DRIVER_PARA_T *pDriverInfo;
		uint32_t u32Vid[MAX_DRIVER] ;
		uint32_t u32Pid[MAX_DRIVER] ;
	  uint32_t u32Pos[MAX_DRIVER] ;
	  uint8_t flgOverUnder[MAX_DRIVER] ;
	  uint16_t  StatusWord[MAX_DRIVER] ;
		uint32_t u32DisPos[MAX_DRIVER] ;   //顯示位置
		uint32_t u32IncPos[MAX_DRIVER] ;	 //增加位置
	
	  bool flgDisplays;
		bool flgDisplay[MAX_DRIVER] ;
	  long src_pos[MAX_DRIVER] ;
		long curstep[MAX_DRIVER] ;
		long step[MAX_DRIVER] ;
		long dst_pos[MAX_DRIVER] ;
		uint32_t OrgPos[MAX_DRIVER] ;   //生產時的位置
	  
		int32_t src_u32Pos[MAX_DRIVER] ;//配合探針
		uint16_t  errcode[MAX_DRIVER] ;
		int speed ;
		int remind ;
		int RUNTEST ;    //EC_TEST_MODE/EC_RUN_MODE
		int VRAUTOHOME ;    //EC_VRHOME_MODE/EC_AUTOHOME_MODE
		int stateMoveStep ;
		bool flgN ;
		uint16_t N ;
		uint16_t buffersize ;
		bool  flgAccF;
		uint32_t AccF ;
		
		uint8_t NoProgramNo ;
		uint16_t ProgramNo[10] ;
		uint16_t StartActionTable[10] ;
		uint32_t End_msActionTable[10] ;
		
		
		bool flgCurrProductQty ;
		bool flgStopMachine ;
		bool flgreadyStopMachine ;
		bool flgCompleteActionTable ;
		bool flgCurrProductTime;
		int CurrProductQty;
		int SetProductQty ;
		uint8_t adc ;
		
		bool  flgProgramToolRun ;
		bool     flgDisplay_touch ;
		uint8_t  touch ;
	  uint8_t TouchAir_touch_idx;
		uint32_t touch_y_dst_pos ;
    uint32_t touch_y_step ;
		uint32_t touch_y_u32Pos ;
		uint32_t touch_yvalue ;
		uint32_t ProbePos ;
		uint8_t touch_state ; // 0 :fail   1:ok
		uint8_t CurrFailQty;
		uint8_t SetFailQty ;
		
		uint8_t CurrentState ;
		uint8_t lCurrentState ;
		uint8_t HandWheelPower ;
		uint8_t SPD ;
		uint16_t SPD_CHANGE ;
		bool flagSPD_CHANGE ;
		bool SmartBack ;
		
		
		
		
		bool flgcontMAN ;
		uint8_t contMAN_DrvIdx ;
		uint32_t contMAN_lstep ;
		
    // for DataOut
    uint32_t    *pu32DOUTData;
    uint8_t     u8DOutCnt;
    
    uint32_t    u32DCounter;    
    uint8_t     u8DOutFlag;
    
    // for DataIn
    uint32_t    *pu32DInData;
    uint8_t     u8DInCnt;
    
    // for AnalogIn
    uint32_t    *pu32AInData;
    uint8_t     u8AInCnt;   

} ST_PROCESS_STATE_T;

struct WAIT_MOTOR{
	uint8_t  axis ;
	uint32_t near;
} ;
EXTERN struct WAIT_MOTOR WaitMotor[MAX_DRIVER] ;
EXTERN uint32_t NearMotor[MAX_DRIVER]
#ifdef GLOBAL
={
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
	0,0,0,0,0,
} 
#endif
;


EXTERN int volatile  cnt_UserProcessPDO
#ifdef GLOBAL
=0
#endif
;


EXTERN ST_PROCESS_STATE_T gstProcessState ;

typedef struct st_driver_table
{
    uint32_t    u32Vid;
    uint32_t    u32Pid;
    uint32_t    u32PPR;
} ST_DRIVER_TABLE_T;

EXTERN  ST_DRIVER_TABLE_T stDriverTable[]
#ifdef GLOBAL
= {
        // Delta,ASDA-A2-E CoE Drive
    {   0x01dd,     0x10305070,    1280000   },  

        // SanyoDenki RS2 EtherCAT                                
    {   0x01b9,     0x00000002,    131072    },
    
        // panasonic minas-a6be EtherCAT                                
    {   0x066f,     0x60380008,    8388608   }    
}
#endif
;
EXTERN int no_stDriverTable
#ifdef GLOBAL
=sizeof(stDriverTable)/sizeof(ST_DRIVER_TABLE_T)
#endif
;


#define MS_MANMOV		50
#define INCMS_MANMOV (MS_MANMOV+MS_MANMOV/2)
#define STATE_INC_MANMOV      0
#define STATE_SAME_MANMOV    	1
#define STATE_DEC_MANMOV      2

typedef struct st_man_mov{
    uint8_t     DrvIdx;
		uint8_t    dir ; // 0:正轉  1:反轉
	  uint32_t    step;
	  uint8_t     frwdir ;
	  uint32_t    frwstep;
		uint32_t    acc ;
	  uint32_t    frwacc ;
	  uint8_t     ms ;
		uint8_t      ldir ;
		uint32_t      lstep ;
	uint8_t        mode ;
	uint8_t        state ;
	uint32_t       buf[INCMS_MANMOV] ;
	uint32_t       frwbuf[INCMS_MANMOV] ;
} ST_MAN_MOV;
EXTERN	ST_MAN_MOV	MAN_MOV
#ifdef GLOBAL
={0xff ,0,0,0}
#endif
;

EXTERN bool  volatile flgKeyLock
#ifdef GLOBAL
=false 
#endif
;
EXTERN bool  volatile flgKeySwitch
#ifdef GLOBAL
=false 
#endif
;




EXTERN uint16_t NoActionTable ;
EXTERN uint16_t idxActionTable ;
EXTERN uint32_t End_msActionTable ;
EXTERN bool  volatile flgActionTable ;
struct ACTION_TABLE{ //32 byetes
	bool  Feed ;
	uint8_t  actcmd ;  // 0: move axis 1:touch air 
	uint8_t  touch ;
	uint8_t  air ;
	uint8_t  axis ;
	uint8_t  dir;
	uint8_t  frwdir;
	uint16_t FileNo ;
	uint16_t N ;
	uint32_t Start_ms ;
	uint16_t ms ;
	uint16_t idms ;
	uint32_t step ;
	uint32_t frwstep ;
	uint32_t dst_pos ;
} ;
EXTERN struct ACTION_TABLE ActionTable[2000] ; //3000*32

EXTERN uint8_t TouchAir_air_buf;
struct TOUCH_AIR{
	uint8_t used; //0: empty 1:used
	uint8_t touch ;
	uint8_t air ;
	uint32_t Start_ms ;
	uint16_t ms ;
} ;
EXTERN struct TOUCH_AIR TouchAir[8] ;

EXTERN uint16_t NoMoveStep ;
EXTERN bool  volatile flgMoveStep ;
EXTERN bool  volatile flgDispZero ;
EXTERN uint32_t msMoveStep ;
struct MOVE_STEP{
	uint8_t  axis ;
	uint32_t ms ;
	uint8_t  dir;
	uint32_t step ;
	uint8_t  frwdir ;
	uint32_t frwstep ;
	bool   lastms ;
	uint32_t src_pos;
	uint32_t dst_pos ;
	uint32_t curstep ;
	uint32_t curstepAcc;
	uint32_t frwcurstep ;
	uint32_t mov ;
	uint32_t frwmov ;
	uint32_t acc;
	uint32_t  frwacc ;
	uint32_t Start_ms ;
	uint16_t idms ;
} ;
#define MAX_AXIS   2
EXTERN struct MOVE_STEP MoveStep[MAX_AXIS] ;

EXTERN volatile int flgReset;
EXTERN int flgEncoderClr;
EXTERN int AxisResetEncoderClr;



int EtherCatMasterInit(uint32_t spi_clock);
int EtherCatGetVidPid(uint8_t u8DeviceIdx, uint32_t *pu32Vid, uint32_t *pu32Pid) ;
int EtherCatGetActualPos(uint8_t u8ServerIdx, uint32_t *pu32Data) ;
int UART_Complete() ;
void UART_Update_ridx_CmdBufTbl();

