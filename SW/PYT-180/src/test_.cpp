#ifdef GLOBAL
#define EXTERN    
#else
#define EXTERN extern   
#endif


// #define TEST_BREAK_PULSE   //脈波形馬達探針測試
// #define TEST_SYNC
// #define TEST_RAM
// #define TEST_ORG   //邱展發的馬達測試程式
//#define TEST_BREAK
// #define TEST_MANMOV_KEY
// #define TEST_MANMOV_UART 
// #define TEST_SDO
#define TEST_TOUCH_PROBE



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


