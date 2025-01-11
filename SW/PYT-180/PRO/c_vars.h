#ifdef GLOBAL
#define EXTERN
#else
#define EXTERN	extern
#endif

#define	HUGE	huge                            //

EXTERN 	struct CP cp_glb[MAX_PROG_LINE] ;
//EXTERN unsigned char int_no ;
EXTERN  int safedumpchk,safe_cnt,safe_cnt_1,safe_cnt_2,safe_cnt_3,safe_cnt_4,safe_cnt_5,safe_cnt_6,safe_cnt_7,safe_cnt_8,safebuf,safeerrbuf,chk_dumpsafe,CHK_STEP,chk_runsafe,GenRatio_cnt;
EXTERN int safe_runtag;
EXTERN int chk_run_touch,chk_Y_idms,TouchWire;//chk_Y_idms �e�u�����w�ɪ��P�_,�����ܨϥΥ[��t //TouchWire���w�ɧ�e�u��k
EXTERN  float  totalY;
EXTERN  int safe_cntR,safe_cnt_1R,safe_cnt_2R,safe_cnt_3R,safe_cnt_4R,safe_cnt_5R,safe_cnt_6R,safe_cnt_7R,safe_cnt_8R;
EXTERN  int first_dda;
EXTERN  float first_speed;

EXTERN unsigned char BPINTC ;
EXTERN unsigned char BOUTM ;
EXTERN unsigned char BOUTH ;
EXTERN short CurProgLine;
EXTERN short YProgoff;
#if 0
EXTERN short CurAirLine;		//�ϥզ檺���
EXTERN short YAiroff;			//�Ĥ@���ϥժ��檺�Z��--->CurAirLine-YAirOff���Ĥ@�檺���
#endif


EXTERN short CurProgLine_test;
EXTERN short YProgoff_test;
EXTERN short LastLine_test;

#if TRACE_Y
#define MAX_TRACE_Y  20
struct BTRACE_Y{
	WORD sPos,ePos ;
	WORD mov ;
} ;
EXTERN  int cnt_trace_y ;
EXTERN  bool ov_trace_y ;
EXTERN struct BTRACE_Y buf_trace_y[MAX_TRACE_Y] ;
#endif

EXTERN ProgType_t huge ProgBuf[MAX_PROG_LINE] ;
EXTERN ProgType_t huge CurProgBuf;

EXTERN ProgType_t huge ModyBeBuf[10] ,ModyAfBuf[10];
EXTERN int ModyNum,ReturnNum,ModyBeNum,ModyAfNum;
EXTERN int ModyLine[10];
EXTERN int AXIS_AMody[10];
//MARKER CURSOR
EXTERN ProgTypeExlarge_t huge ProgBufExlarge[MAX_PROG_LINE] ;
EXTERN ProgTypeExlarge_t huge CurProgBufExlarge;

#if 0
EXTERN AirType_t huge AirBuf[MAX_AIR_LINE] ;
EXTERN AirType_t CurAirBuf;
#endif

EXTERN WORD CursorLoc;
EXTERN Cursor_t CurCursor;

// EXTERN MachineStatus_t MachineStatus;

typedef struct Pmove{
	BYTE cmd ;
	BYTE next ;
	DWORD ref ;
	DWORD idms ;
	DWORD mov ;
	DWORD dst_pos ;
	DWORD	loopref;
	SDWORD loopmov ;
} ST_PMOVE_T;
typedef struct Pset_delay{
	BYTE cmd ;
	BYTE next ;	
	union
	{
		WORD	Delay ;
	}u;
} ST_PSET_DELAY_T;
typedef struct Pwait_delay{
	BYTE cmd ;
	BYTE next ;
} ST_PWAIT_DELAY_T;
typedef struct Pwait_motor{
	BYTE cmd ;
	BYTE next ;
	SDWORD	sdchk_pos;
} ST_PWAIT_MOTOR_T;
typedef struct Ploop_update{
	BYTE cmd ;
	BYTE next ;
	union
	{
		WORD	line;
	}u;
	WORD mov ;
} ST_PLOOP_UPDATE_T;
typedef struct Ploop_s{
	BYTE cmd ;
	BYTE next ;	
	union
	{
		DWORD	line;
	}u;
	WORD mov ;
} ST_PLOOP_S_T;
typedef struct Ploop_ck{
	BYTE cmd ;
	BYTE next ;
} ST_PLOOP_CK_T;
typedef struct Ploop_e{
	BYTE cmd ;
	BYTE next ;
} ST_PLOOP_E_T;
typedef struct Ploop_mov{
	BYTE cmd ;
	BYTE next ;
	DWORD ref ;
	DWORD idms ;
	DWORD mov ;	union
	{
		SDWORD	dst_pos;
	}u;
	DWORD loopref ;
	DWORD loopmov ;
} ST_PLOOP_MOV_T ;
typedef struct Pupdate{
	BYTE cmd ;
	BYTE next ;
	WORD	line;
} ST_PUPDATE_T;
typedef struct Pend{
	BYTE cmd ;
	BYTE next ;
} ST_PEND_T;
typedef struct Pnull{
	BYTE cmd ;
	BYTE next ;
} ST_PNULL_T;
typedef struct PsetAir{
	BYTE cmd ;
	union
	{
		BYTE	air;
	}u;
} ST_PSETAIR_T;
typedef struct PsetTouch{
	BYTE cmd ;
	struct{
		BYTE	touch;
		BYTE	stop_axis ;
	}t ;
} ST_PSETTOUCH_T;
typedef struct PclrTouch{
	BYTE cmd ;
	struct{
		BYTE	touch;
		BYTE	stop_axis ;
	}t ;
	struct{
		WORD start ;
		WORD end ;
	}utouch ;
} ST_PCLRTOUCH_T;

typedef struct virtual_str{
	DWORD flag ;						//true :有虛擬Z,A,B,C軸
	DWORD initial_move ;
	DWORD last_move ;
} ST_VIRTUAL_STR_T ;


typedef struct AgetsetAir{
	BYTE cmd ;
	union
	{
		BYTE	air;
	}u;
	BYTE dir ;
	SDWORD	chk_pos;
} ST_AGETSETAIR_T;


typedef struct AsetTouch{
	BYTE cmd ;
	struct{
		BYTE	touch;
	}t ;
	BYTE dir ;
	SDWORD	chk_pos;
} ST_ASETOUCH_T;
typedef struct AclrTouch{
	BYTE cmd ;
	struct{
		BYTE	touch;
	}t ;
	SDWORD	chk_pos;
	struct{
		SDWORD start ;
		SDWORD end ;
	}utouch ;
	BYTE dir ;
} ST_ACLRTOUCH_T;

EXTERN WORD ActTblIdx;
EXTERN WORD RetTblIdx;
EXTERN ActTbl_t HUGE ActTbl[MAX_PROG_LINE*4];
//EXTERN ActTbl_t HUGE PM_tbl[MAX_PROG_LINE*7];
//EXTERN ActTbl_t HUGE rey_tbl[MAX_PROG_LINE*7];

// EXTERN int AirTblIdx;
// EXTERN AirTbl_t HUGE  AirTbl[MAX_AIR_LINE*3];

EXTERN DWORD PasswordBuf;
EXTERN BYTE  InitParameter, InitAllProg;
EXTERN int y_Sprintf;


EXTERN WORD Old54Val;

#if CCY_CHECK==1	//VVVVVVVVVVVVVVVVVVVVVVVVVV//
extern	  WORD Random;                          //
EXTERN	 DWORD Code1;                           //
#endif	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//
EXTERN BYTE KeyBufRIdx, KeyBufWIdx, KeyTmp, HandQlen,Step_Handisr;
EXTERN BYTE KeyBuf[MAX_KEY_BUF];
EXTERN int WriteId;
EXTERN bool flag_off_power;
//EXTERN int insercnt;
EXTERN BYTE CmdBuf[1];
EXTERN int volatile  wRxCmdBuf1 ;
EXTERN int volatile  rRxCmdBuf1 ;
EXTERN int volatile  wTxCmdBuf1 ;
EXTERN int volatile  rTxCmdBuf1 ;
EXTERN int volatile  wTxCmdBuf2 ;
EXTERN int volatile  rTxCmdBuf2 ;
#define INC_idxCmdBuf(idxCmdBuf)															\
													idxCmdBuf++ ;   										\
	                        if(idxCmdBuf >=MAX_CMD_BUF){  			\
														idxCmdBuf=0 ;											\
													}
#define WaitNo_inCmdBuf(rCmdBuf,wCmdBuf,waitno)																	\
													do{																		\
														if(wCmdBuf < rCmdBuf){							\
															len=wCmdBuf+MAX_CMD_BUF-rCmdBuf ;	\
														}																		\
														else{																\
																len=wCmdBuf-rCmdBuf ;						\
														}																		\
													}																			\
													while(len < waitno) ; 
EXTERN BYTE testbuf[6];
EXTERN BYTE SafeCtrl;

EXTERN char HUGE DP_BASE_BUF[1] ;                                       //
#define DP_BASE_ADDR		(DP_BASE_BUF)                               //
#define DP_TRANS_ADDR		(DP_BASE_ADDR+0x0000)                       //
#define DP_RECEIVE_ADDR 	(DP_BASE_ADDR+0x0000)                       //
#define DP_POWER_ON_ADDR	(DP_BASE_ADDR+0x1800)                       //
#define DP_GEN_INT_ADDR 	(DP_BASE_ADDR+0x1ffe)                       //
#define DP_CLR_INT_ADDR 	(DP_BASE_ADDR+0x1fff)                       //
#define DP_RW_RETRY 		20                                          //
#define DP_DELAY_COUNT		3000                                        //


EXTERN UC *pp[100];
EXTERN UC *Airpp[50];
EXTERN UC *virtualpp;
EXTERN UC *vir_cmd[100];
EXTERN int PIdx;
EXTERN int virtualPIdx;
EXTERN __align (4)char RActtbl[1];  //500 * 28 * 5  500行每個Action 佔28byte,假設一行有5個action
EXTERN __align (4)char VirtualActtbl[28 * 5];


EXTERN BYTE ResponseCmd, Reset;
EXTERN BYTE ChkPara;
EXTERN BYTE ChkRacttbl;//����ACTTBL
EXTERN uint16	ModeTmp;

EXTERN BYTE LastCmdID, SendCmdID;
EXTERN int RIdx;
EXTERN WORD Air_idx;
EXTERN BYTE HUGE Buffer[1][1] ;		//QUEUE_NO][QUEUE_SIZE];
EXTERN char ErrMsg[QUEUE_SIZE];
EXTERN bool ErrMsg_timeout_flg;
EXTERN struct TIMER timeout_ErrMsg;
EXTERN struct TIMER  timeout_BZ;
EXTERN bool status_BZ
#ifdef GLOBAL
=false 
#endif
;
EXTERN bool BZ_first
#ifdef GLOBAL
=true 
#endif
;
#define FILE_RW_DELAY	  60000u
//#define FILE_RW_MAX_NUM	((QUEUE_SIZE-1)/sizeof(ProgType_t)) Ū�g�ϺЪ�command��10byte
#if 1
#define FILE_RW_MAX_NUM   100
#else
#define FILE_RW_MAX_NUM   ((QUEUE_SIZE-10)/sizeof(ProgType_t))
#define FILE_RW_MAX_NUM_AIR   ((QUEUE_SIZE-10)/sizeof(AirType_t))
#endif
EXTERN BYTE  FileRWAck, FileRWErr;
EXTERN WORD  FileSizeAck;
EXTERN DWORD FileOffAck;
EXTERN ProgType_t FileRWBuf[FILE_RW_MAX_NUM];
EXTERN WORD RW3701Err;
EXTERN WORD RESEND3701Err;
EXTERN WORD DS3701Err;
	
#define DISP_CUR_AIRLINE(x, y, disp_line, mode)							\
	DispAirLine(x, y, disp_line, (AirType_t *)(AirBuf+disp_line), mode);

	
#define DISP_EDIT_AIRLINE(x, y, disp_line, mode)	\
	DispAirLine(x, y, disp_line, &CurAirBuf, mode);

                                                        //
                                                        //
                                                        //
#define READ_ADC(axis)							\
		(rDosMem(pc_base+BaseMotorADC[axis/6]))
#define CHK_NEARLY_ZERO(axis)			  		\
		(((axis_type == INTEL8051_AXIS)?rDosMem(pc_base+Base3701[axis]+R_CMD_51): rDosMem(pc_base+0xd+(axis<< 4))) == ST51_NEAR)
                                                        //
                                                        //
EXTERN WORD DispDelay, CurDispIdx;


EXTERN char* TouchTitle[][4]
#ifdef GLOBAL
={
	{" TH 1", " TH 2", " TH 3", " TH 4"},
	{"���w1", "���w2", "���w3", "���w4"},
	{" TH 1", " TH 2", " TH 3", " TH 4"},
}
#endif
;

struct PROC_QUEUE{
	void (*fnptr)(void *ptr) ;
	void *dptr ;
	char *fnname ;
//	bool used ;
	int next ;
} ;
#define MAX_PROC_QUEUE	 2000   //V2.39  ���400--->2000
EXTERN PROC_QUEUE huge proc_queue[MAX_PROC_QUEUE] ;
EXTERN int head_proc_queue ;
EXTERN int last_proc_queue ;
EXTERN int free_proc_queue ;
EXTERN int free_proc_queue_no ;

enum{  NORMAL_KEY_STATE ,WAIT_NEW_KEY_STATE } ;
EXTERN unsigned char KeyState ;
#if 0
EXTERN long  long timeout_motor_move ;
#endif
#define MAX_DispCurAxis      50 //V2.39 ���20--->50
EXTERN struct TIMER timeout_DispCurAxis ;
#define TIMER_ADC            3
EXTERN struct TIMER timeout_ADC ;
EXTERN  struct TIMER timeout_ScrnSav ;
#define TIMER_ROLL_DATA      4 
EXTERN struct TIMER timeout_roll_data ;
#define TIMER_FLASH	       3
EXTERN struct TIMER timeout_flash ;
#define SCALE_ACC_NO	 100
struct LENCHK_BUF{
	long stat_idx ;
	double total,total2 ;
	double average,std_dev,cap_idx ;
	long base_idx ;
	long cur_idx ;
	long lcur_idx ;
	long dialog_idx ;
	float buf[MAX_LENCHK_BUF] ;
	float *stat_buf ;
	long acc_no[17] ;
	long max_acc_no ;
	long lmax_acc_no ;
	unsigned xmshandle ; // xms handle

} ;
EXTERN struct LENCHK_BUF lenchk_buf ;
enum SCREEN_STATE{ MAIN_SCREEN , LENCHK_SCREEN} ;
EXTERN SCREEN_STATE screen_state ;
EXTERN unsigned char slide_axis ;
EXTERN unsigned char ServoCutter_axis ;
EXTERN bool flag_ZRT_ZABCD[5] ;
EXTERN DWORD ZABCD_2016[5] ;	
// Set3701Val-----�����U�b���������
// Mov3701Val-----�����U�b�w�������
// Abs3701Pos-----�����U�b�t�X��2016��

EXTERN SDWORD Set3701Val[MAX_AXIS];
EXTERN SDWORD Mov3701Val[MAX_AXIS];
EXTERN SDWORD  Abs3701Pos[MAX_AXIS]; 
EXTERN BYTE  Mov3701Sign[MAX_AXIS] ;


#define pc_base 0x60000000UL
EXTERN char VersionDate[30] ;
EXTERN BYTE VersionDate_buf_start ;
//����3/6���O����
//	0:�S��checksum���b���							,�N��N
// 	1:��checksum���b���(for Set3701)					,�N��C 
//	3:��checksum���b���(for Set3701&set3701ManMov)	,�N��D  
//  �̷ӫ��w��checksum�覡�U�R�O,�b�d�o�S���^��			,�N��E
//	0xff:�S���b���									,�N��- 
EXTERN BYTE AxisChkSum[MAX_AXIS] ;
enum{INTEL8051_AXIS,ARM_AXIS} ;
EXTERN unsigned char axis_type ;

EXTERN bool key_flg                                      //
#ifdef GLOBAL                                           //
=true                                                  //
#endif                                                  //
;                                                       //
EXTERN bool in_movToZeroAll ;                                      //
EXTERN bool Slide_first_zero ;//�Ʈy�^���I��}�l�ˬd��ʷ���
EXTERN char RW3701ErrStr[100] ;


EXTERN bool AirTblOn ;

EXTERN WORD lcur_x ;
EXTERN WORD ldir ;
EXTERN bool FlashOn ;
EXTERN bool in_Chk3701No ;
EXTERN bool AirScrn_ON;
EXTERN bool MarkerScrn_ON;
EXTERN struct TIMER TimerTicks ;
EXTERN struct TIMER TimerTicks2 ;
//EXTERN struct TIMER TimerTicks3 ;
EXTERN long long Timerchk[100] ;
EXTERN	DWORD volatile msTicks;                       // Counter for millisecond Interval
EXTERN	DWORD volatile lmsTicks;                       // Counter for millisecond Interval
EXTERN struct TIMER aaa ;
EXTERN int  chk_hand_cnt;
EXTERN bool flag_complete_spring_cmd ;
EXTERN bool flag_complete_spring ;
EXTERN bool flag_ReturnManMode ;
EXTERN bool flag_DispCurPosDelay ;
#define NO_DispCurProgList 10
EXTERN WORD no_DispCurProgList ;
EXTERN WORD rd_DispCurProgList ;
EXTERN WORD wr_DispCurProgList ;
EXTERN WORD buf_DispCurProgList[NO_DispCurProgList] ;

#if 0
#define NO_DispCurAirList 10
EXTERN WORD no_DispCurAirList ;
EXTERN WORD rd_DispCurAirList ;
EXTERN WORD wr_DispCurAirList ;
struct BUF_DISPCURAIRLIST{
	int line ;
	BYTE cmd ;
} ;
EXTERN struct BUF_DISPCURAIRLIST  buf_DispCurAirList[NO_DispCurProgList] ;
#endif

EXTERN bool flag_axis_cmd_SaveFile ;
EXTERN bool flag_run ;
EXTERN WORD plus_cnt,minus_cnt ;
EXTERN bool ExeMode ;

EXTERN bool has_SET_TOUCH ; 

EXTERN bool keyswap ; 
EXTERN bool keylock ; 
EXTERN BYTE keyscrn ; 

EXTERN BYTE off_power ; 


EXTERN bool flag_EnableHomeInt[MAX_AXIS] ; 
EXTERN bool flag_NearHome[MAX_AXIS] ; 
EXTERN bool flag_axis_val  
#ifdef GLOBAL
=false 
#endif
;
EXTERN SDWORD  Abs3701Pos_StartZrt[MAX_AXIS];   
EXTERN bool  DDisk ;   
EXTERN int len_g9_struct ;
EXTERN struct G9_STRUCT g9_struct[30] ;

EXTERN struct AUTO_HOOK  AutoHook ;
EXTERN bool  ScrnState ;
EXTERN bool  EnableHomeInt_ZrtMode[MAX_AXIS];   
EXTERN DWORD dsave_cur_th[4] ;
EXTERN WORD last_axis ;
EXTERN bool flag_ClrTouchPos[4] ;
EXTERN bool flag_DispMissNo ;
struct DISPSTATUSBAR{
		bool flag ;
		BYTE axis ;
		DWORD dst_pos ;
	} ;
EXTERN DISPSTATUSBAR st_DispStatusBar ;

#if (SAVE_AXIS_CMD==1)
EXTERN bool flag_SaveFile ;
#endif

#if ISR_FILL_PROC_QUEUE
EXTERN bool in_TouchIsr ;
EXTERN bool in_MotorIsr ;
EXTERN bool in_TimerIsr ;
#endif
EXTERN BYTE NEAR_b ;
EXTERN BYTE YLOC_dir,ALOC_dir ;
EXTERN SDWORD AmdyY  ;

EXTERN char VERSION[10] ;
EXTERN char VERSION_DATE[12] ;
EXTERN WORD x_cnt ,y_cnt ,zrt_cnt;
EXTERN uint32 WaitNearCnt[MAX_AXIS_8];

#if NEW_FILE
EXTERN char *FileTitle[][1]
#ifdef GLOBAL
={
	{"    FILE"},
	{"    �ɮ�"},
	{"    FILE"},
}
#endif
;

#else
EXTERN char *FileTitle[][1]
#ifdef GLOBAL
={
	{"     FILE NO  "},
	{"     �ɮ׽s�� "},
	{"     N\x6 FILE  "},
}
#endif
;
#endif

EXTERN char *FileCommentTitle[][1]
#ifdef GLOBAL
={
	{"    FILE Comment"},
	{"     �ɮ׵���   "},
	{"     N\x6 FILE  "},
}
#endif
;



#if NEW_INDEX
EXTERN struct INDEX_STRUCT  Index ;
#endif


EXTERN char *SetToZero[]
#ifdef GLOBAL
={
	" set to Zero",
	"�Q�]�w��0", 
	" set to Zero",
}
#endif
;


EXTERN BYTE th_stopy ;
EXTERN bool IndexScrn ;

#if NEWV_MDY

struct SStopMotor{
	bool flag ;
	unsigned	long time_out ;
} ;

EXTERN SStopMotor  sstopmotor[MAX_AXIS]	;

#endif
#if DEBUG_RESEND
EXTERN WORD aresend_cnt[MAX_AXIS][MAX_RESEND_CNT];
EXTERN bool err_mark ;
#endif



EXTERN struct SET3701CMD set3701cmd[NOSET3701CMD] ;
EXTERN int idx_set3701cmd ;
EXTERN  BYTE  SaveKeyBuf[NOSAVEKEYBUF] ;
EXTERN int idx_SaveKeyBuf ;
EXTERN struct ERR  Err;
EXTERN bool  FlagRun1 ;

#if SW_SIM_MOTOR
EXTERN struct SIM_MOTOR  sim_motor;
#endif


EXTERN struct STOP_SPIN stop_spin ;
EXTERN bool modify_a ;
EXTERN unsigned char USB ;
EXTERN bool USBOK ;
#if CHK_MAN_MOV
EXTERN struct ST_CHK_MAN_MOV  chk_man_mov;
#endif



EXTERN uint16 ERP_BufRIdx, ERP_BufWIdx;	//RS232�A�ثe"�g�J"	 ,	"Ū��"����
//TODO
//EXTERN BYTE ERPBuf[MAX_ERP_BUF];		//RS232�x�s�}�C
//EXTERN BYTE ERP_regist[MAX_ERP_BUF*7];	//�B�zERP�}�C
EXTERN uint32 aa_length;			    //��Ū������
EXTERN uint32 ERP_idx;			    //��Ū������
EXTERN bool VersionCheckFlag;			    //�O�@��

EXTERN char  c_version[5];


struct SMANMOV{
	BYTE axis ;
	int dir ;
	BYTE man_hand ;
} ;

EXTERN struct SMANMOV SManMov ;

EXTERN uint8 prokeycode;

EXTERN uint8 STEP_DDAState
#ifdef GLOBAL
=0 
#endif
;
EXTERN uint8 DDAState
#ifdef GLOBAL
=0 
#endif
;
struct DDATBL{
	int totalms ;  //
	int idms ;
	int avgms ;
	BYTE dir ;
	int movval ;
	int curms ;
	int lmovval ;
	int curval ;
	int accval ;
	int remainingval ;
	int16 dda ;
	//int16 decval[1000] ;
	int new_accval;	//�βֿndda��ܥثe��m
} ;
// EXTERN struct DDATBL DDATbl[MAX_AXIS] ;
EXTERN uint8 cnt_Set3701 ;	
EXTERN int ltRatio;
EXTERN int tGenRatio;
EXTERN int Ratiochk;
EXTERN int tRatio;
EXTERN int Ratio 
#ifdef GLOBAL
=100 
#endif
;
EXTERN int RUN_Ratio 
#ifdef GLOBAL
=100 
#endif
;

EXTERN int curRatio
#ifdef GLOBAL
=100 
#endif
;
EXTERN int FeedbackCnt[MAX_AXIS] ;	
EXTERN uint16 lFeedbackCnt16[MAX_AXIS] ;
	

enum{ ENABLE_INT,ENABLE_STOP,ENABLE_INT_STOP} ;






#define LEN_DDABUF   5000
EXTERN int idx_DDABUF
#ifdef GLOBAL
=0
#endif
;

struct DDABUF_st{
	int val ;
	int ms ;
	int curms ;
} ;

//todo
//EXTERN struct DDABUF_st DDABUF[LEN_DDABUF] ;
EXTERN int  scurRatio ;	

//todo
//EXTERN int buf3[5000] ;
EXTERN int off_buf3
#ifdef GLOBAL
=0
#endif
;


