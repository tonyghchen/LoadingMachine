#include "c_vars.h"


EXTERN char *StrActTbl[]                                                //
#ifdef GLOBAL                                                           //
	={                                                                  //
	"MOVE_X", "MOVE_Y", "MOVE_Z", "MOVE_A", "MOVE_B", "MOVE_C","MOVE_D","MOVE_E",//				//0~6
	"UPDATE_LINE","SET_AIR", "CLR_AIR" ,"SET_TOUCH", "CLR_TOUCH", "CLR_LOOP_AIR", //	//7~12
	"ZRT_Z", "ZRT_A","ZRT_B" ,"ZRT_C","ZRT_D","ZRT_E",                          //				//13~17
                                                                        //
	"MISS_X", "MISS_Y", "MISS_Z", "MISS_A", "MISS_B", "MISS_C","MISS_D","MISS_E",//				//18~24
	"MISS_UPDATE_LINE", "MISS_SET_AIR",                                 //				//25~26
                                                                        //				
	"LOOP_X", "LOOP_Y", "LOOP_Z", "LOOP_A", "LOOP_B", "LOOP_C","LOOP_D","LOOP_E",//				//27~33
	"LOOP_UPDATE_LINE", "LOOP_START", "LOOP_CHECK", "LOOP_END",         //				//34~37
                                                                        //
	"MID_CHK", "END_ACT", "NULL_ACT_CMD", "CNT8254_CMD" ,"OFFSET_Y" ,"OFFSET_Y_M","INCY" ,   //		//38~44
	"SET_DELAY" ,"WAIT_DELAY","WAIT_MOTOR_NEAR_IN_LOOP" ,"WAIT_MOTOR_NEAR_X","WAIT_MOTOR_NEAR_Y","WAIT_MOTOR_NEAR","WAIT_MOTOR_HOOK" ,"WAIT_ZRT_X",//			//45~53
	"LOC_PLUS_MINUS","LOC_MINUS_PLUS" ,"MODIFY_Y","SAVE_Y" ,"SAVE_Y_MOV","WAIT_MOTOR_NEAR_SERVO","CHK_SPIN_ZRT","WAIT_SPIN_ZRT",                                 //			//54~61
	"SETSPEED_PMFUN",													//62
	"T_STOP_MDYVAL","T_STOP_OFFSET","T_STOP_OFFSETA",					//63~65
	"WAIT_EXTERNAL_ENCODER","WAIT_STOP_Y_MOTOR" ,	
	"CHK_TOUCH","DISABLE_REPAIR_Y",
	}
#endif
;






      
enum{
	PROG_OK, PROG_LINE_ERR, PROG_GCODE_ERR, PROG_RETURN_ERR, PROG_TH_ERR,
	PROG_LOOPS_ERR, PROG_LOOPE_ERR, PROG_LOOP_TIMES_ERR,
	PROG_SX_ERR, PROG_EX_ERR, PROG_Y_ERR, PROG_Z_ERR, PROG_A_ERR, PROG_B_ERR, PROG_C_ERR,PROG_Z_AXIS_ERR,PROG_ZOFF_ERR,PROG_SPD_ERR,
	PROG_STOP_SPIN_NO_MOVE, PROG_STOP_SPIN_NO_GOHOME ,LESS_MIN_AUTOHOOK ,GREATER_MAX_AUTOHOOK ,PROG_SX_ERR_SMALL,PROG_EX_ERR_SMALL,
	PROG_LOOP_G6_ERR,OVER_RPM_ERR,OVER_A_LIMIT,
};
EXTERN char *err_mes[]
#ifdef GLOBAL
		={
		"�{���s�g", 									// PROG_LINE_ERR			1
		"Program Line",									
		"G-CODE��", 									// PROG_GCODE_ERR			2
		"G-CODE value",
		"RETURN��" ,									// PROG_RETURN_ERR			3
		"RETURN value" ,
		"���w�MAIR�]�w���|" ,							// PROG_TH_ERR				4
		"Touch and AIR Overlay" ,
		"�j��_�l��Ƴ]�w��" ,							// PROG_LOOPS_ERR			5
		"LOOP Starting line" ,
		"�j�鵲����Ƴ]�w��" ,							// PROG_LOOPE_ERR			6
		"LOOP Ending line" ,
		"�j�馸�Ƴ]�w��" ,								// PROG_LOOP_TIMES_ERR		7
		"LOOP Times line" ,
		"X�b�_�l��Ƴ]�w�ȹL�j" ,						// PROG_SX_ERR				8
		"X-Axis Starting Degree Too Large" ,
		"X�b������Ƴ]�w�ȹL�j" ,						//	PROG_EX_ERR				9
		"X-Axis Ending Degree Too Large" ,
		"Y�b" , 										//	PROG_Y_ERR				10
		"Y-Axis" ,
		"Z �b �W �L �n �� �� ��" , 										//	PROG_Z_ERR				11
		"Z-Axis Over Limit" ,
		"A �b �W �L �n �� �� ��" , 										//	PROG_A_ERR				12
		"A-Axis Over Limit" ,
		"B �b �W �L �n �� �� ��" , 										//	PROG_B_ERR				13
		"B-Axis Over Limit" ,
		"C �b �W �L �n �� �� ��" , 										//	PROG_C_ERR				14
		"C-Axis Over Limit" ,
		"Z�b�]�w�Ȼݬ�0" ,								//	PROG_Z_AXIS_ERR			15
		"Z-Axis must be set 0" ,
		"Z�b�H�W����J�{��,�o�Q����" ,					//	PROG_ZOFF_ERR			16
		"Above Z-Axis have a program,but been off" ,
		"�bFAST�Ҧ��U,SPD���i�H��" ,					//	PROG_SPD_ERR			17
		"IN FAST mode,Can\'t use SPD" ,
		"�ϥα��w�����b,���S�����b���ʭ�" ,					//	PROG_STOP_SPIN_NO_MOV			18
		"Use Touch to Stop SPIN,but no SPIN setting value" ,
		"�ϥα��w�����b,�����b�̫�S���^���I" ,					//	PROG_STOP_SPIN_NO_GOHOME	19
		"Use Touch to Stop SPIN,but SPIN no Go Home" ,
		"***���դw���}***\nX�b���}�l��Ƥ���p��10" ,			//	LESS_MIN_AUTOHOOK			20
		"*** Hook-axis is ON ***\nX-Axis Starting Degree cannot less 10" ,
		"***���դw���}***\nX�b��������Ƥ���j��3900" ,			//	GREATER_MAX_AUTOHOOK		21
		"*** Hook-axis is ON ***\nX-Axis Ending Degree cannot greater 3900" ,
		"***���դw���}***\nX�b�_�l��Ƥ���p��e�@�檺X�b�������" ,	// PROG_SX_ERR_SMALL	22
		"*** Hook-axis is ON ***\nX-Axis Starting Degree cannot less X-Axis Ending Degree of last line" ,
		"***���դw���}***\nX�b�_�l��ƥ����j��X�b�������" ,			//	PROG_EX_ERR_SMALL	23
		"*** Hook-axis is ON ***\nX-Axis Starting Degree must be greater X-Axis Ending Degree" ,
		"G5�f�tG6��\n�ЦbG5�e�[�JG1\n�b�ֳt�^���I���b��J0\nEX:            \nS->ZERO\n000.00\n\n+->ZERO,-->ZERO�P�W" ,			//	24 PROG_LOOP_G6_ERR //G6�bG5���P�_���~
		"Last Line Can\'t use G6 In Loop" ,
		
		}
#endif
;
struct VIRTUAL_ZABC{
	bool flag ;						//true :������Z,A,B,C�b
	SDWORD initial_move ;
	SDWORD last_move ;
} ;
EXTERN struct VIRTUAL_ZABC virtual_zabc[MAX_AXIS] ;


EXTERN char *SpeedTitle[][1]
#ifdef GLOBAL
={
	{"        RPM   "},
	{"     �Ͳ��t�� "},
	{"     PZ MIN   "},
}
#endif
;
EXTERN char *SpeedTitle1[][1]
#ifdef GLOBAL
={
	{"        RATE  "},
	{"     �Ͳ��t�v "},
	{"     PZ MIN   "},
}
#endif
;


EXTERN char *ManTitle[][1]
#ifdef GLOBAL
={
	{"    MAN  "},
	{"    ��� "},
	{"    MANU "},
}
#endif
;


enum { MODE_ZRT_DIRECT , MODE_ZRT_INDIRECT, MODE_ZRT_IMM, MODE_ZRT_ROTATE,MODE_ZRT_YA_ABS1,MODE_ZRT_YA_ABS2,MODE_ZRT_SA_ABS1,MODE_ZRT_SA_ABS2 } ; 






EXTERN  struct ST_EXTENCODER st_extencoder ;

#if NEW_FUN1
#define MAX_MOVY		100
EXTERN unsigned	long movy[MAX_MOVY]	;
EXTERN unsigned	int idx_movy	;
EXTERN unsigned	long movy2[MAX_MOVY]	,movy3[MAX_MOVY];
EXTERN unsigned	int idx_movy2	;
#endif

EXTERN bool Err_ExtEncoder ;




EXTERN char *UpdateSystemDisk[]
#ifdef GLOBAL
={
	" Update System Disk...",
	" ��s�t�κϺ�...",
	" Update System Disk...",
}
#endif
;

EXTERN char *ReadyPoweroff[] 
#ifdef GLOBAL
={
	" Ready To Power Off...",
	" �� �� �� �� ��...",
	" PRONTO PER SPEGNERE...",
}
#endif
;
EXTERN char *Powernotoff[] 
#ifdef GLOBAL
={
	" If power not off,please press energy stop...",
	" �w����,�p�L�����Ы���氱��s...",
	" If power not off,please press energy stop...",
}
#endif
;
EXTERN  struct SET3701_ARM Set3701_ARM ;
EXTERN bool flagStopRun ;
EXTERN bool chk_unconnector ;
EXTERN bool ChkSlide ;//�Ʈy����
EXTERN int cnt3701 ;//�Ʈy����
EXTERN int to3701ms ;//�Ʈy����
//TODO
//EXTERN int cul[2000],ccc[100],toto[2000],ttt[2000],tdda[2000],ltotoms,testchk[2000],tcurtime,ttestkey[2000],testkey;//�Ʈy����
struct chkqlen{
	uint16 qLen;
	long long timer;
	int totolms;
	int curms;
	int dda;
	int curval;
};
//EXTERN chkqlen CHKqlen[500];  TODO
EXTERN int chk3701 ;//�Ʈy����
EXTERN int chkcnt ;//�Ʈy����
EXTERN uint16 LqLen ;//�Ʈy����
EXTERN bool enable_chk_unconnector[MAX_AXIS] ;
EXTERN bool keydump;
EXTERN struct OVER_RPM    OverRpm ;
EXTERN int  X_2016_Y0 ;
EXTERN int  X_2016_Y1 ;
EXTERN BYTE last_sign[MAX_AXIS] ;
//EXTERN FILE *fp_config_c;
//EXTERN FILE *fp_config_d ;
EXTERN bool is_first_a ;
EXTERN bool double_chk_is_first_a ;
EXTERN bool is_first_z ;
EXTERN WORD ManMovRef[]
#ifdef GLOBAL
={ 1, 1, 1, 1, 1, 1 ,1}
#endif
;

// EXTERN char *StrZrtMode[][8]
// #ifdef GLOBAL
// ={
// 	{ "DIRECT","INDIRT","IMMED ","ROTW  ","YAABS1" ,"YAABS2","SAABS1" ,"SAABS2"},
// 	{ "����  ","����  ","�ߧY  ","��u  ","�w�t1 " ,"�w�t2 ","�T�v1 " ,"�T�v2 "},
// 	{ "DIRETT","INDIRT","IMMEIA","ROTW  ","YAABS1" ,"YAABS2","SAABS1" ,"SAABS2"},
// }
// #endif
// ;

EXTERN char *StrG2Mode[][3]
#ifdef GLOBAL
={
	{ "OVER  ","Normal","Custom"},
	{ "�W�t�v","���t�v","�ۭq  "},
	{ "OVER  ","Normal","Costom"},
}
#endif
;
EXTERN char *StrnMotorType[][3]
#ifdef GLOBAL
={
	{ "SANYO ","YASKAW","DELTA "},
	{ "�T�v  ","�w�t  ","�x�F  "},
	{ "SANYO ","YASKAW","DELTA "},
}
#endif
;


EXTERN char *StrUnit[][4]
#ifdef GLOBAL
={
	{"GRID","DEG ","mm  ","Roll" },
	{"���","����","mm  ","���" },
	{"GRID","DEG ","MM. ","Roll" },
}
#endif
;
EXTERN char *StrUnit1[][1]
#ifdef GLOBAL
={
	{"sec "},
	{"��  "},
	{"sec "},
}
#endif
;
EXTERN char *StrWorkMode[][2]
#ifdef GLOBAL
={
	{"RPM ","RATE"},
	{"�t��","�t�v"},
	{"RPM ","RATE"},
}
#endif
;
EXTERN char *StrONOFF[][2]
#ifdef GLOBAL
={
	{"OFF ","ON  "},
	{"����","�}��"},
	{"OFF ","ON  "},
}
#endif
;
EXTERN char *StrHighLow[][3]
#ifdef GLOBAL
={
	{"Low   ","High  ","NULL  "},
	{"Low   ","High  ","���Ѧ�"},
	{"Low   ","High  ","NULL  "},
}
#endif
;
EXTERN char *StrONOFF_min[][2]
#ifdef GLOBAL
={
	{"OFF ","min  "},
	{"����","���� "},
	{"OFF ","min  "},
}
#endif
;
EXTERN char *StrX_Encoder[][2]
#ifdef GLOBAL
={
	{"Prset ","4000  "},
	{"�w�]  ","4000��"},
	{"Prset ","4000  "},
}
#endif
;
EXTERN char *StrTAIDAMotor[][2]
#ifdef GLOBAL
={
	{"Prset","TAIDA"},
	{"�w�] ","�x�F "},
	{"Prset","TAIDA"},
}
#endif
;
EXTERN char *StrUse[][2]
#ifdef GLOBAL
={
	{"NotUse" , "Use   "},
	{"���ϥ�",  "�ϥ�  "},
	{"NotUse" , "Use   "},
}
#endif
;
EXTERN char *StrDef_PMFn[][2]
#ifdef GLOBAL
={
	{"ALL Axis" ,"PMFun "  },
	{"�U�b�w�]" ,"�[��t"  },
	{"ALL Axis", "PMFun "  },
}
#endif
;
EXTERN bool boUpdate_AXIS_X ;
EXTERN unsigned char x_dir ;
EXTERN WORD lx_loc ;
EXTERN WORD disp_y
#ifdef GLOBAL
=0
#endif
;
EXTERN bool flagSPIN_ZRT ;
EXTERN bool flag_VerifyProg ;
EXTERN bool firstSPIN_ZRT ;
EXTERN WORD movSPIN_ZRT ;
#if REAL_COLOR
EXTERN struct FLASH_CURSOR  flash_cursor ;
#endif




EXTERN uint8 ARM_CARD_TYPE ;
EXTERN bool flag_DispEncoder
#ifdef GLOBAL
=false
#endif
 ;
EXTERN bool flag_RRealAxis
#ifdef GLOBAL
=false
#endif
 ;
EXTERN uint32 timeout_WAIT_MOTOR_NEAR_X ;
EXTERN uint32 timeout_WAIT_MOTOR_NEAR_IN_LOOP ;
EXTERN bool flag_timeoutoff
#ifdef GLOBAL
=false
#endif
 ;
EXTERN char	far * AscStart ;
EXTERN char	far *ChIndex ;
EXTERN char	far *ChStart ;
EXTERN uint8 TxBuf[10];
EXTERN unsigned int ChTotalNo ;
EXTERN BYTE Para51[3];
EXTERN struct STBATCHn stBATCHn ;
EXTERN unsigned char BITmask[]
#ifdef GLOBAL
= { 0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1}
#endif
 ;
EXTERN int32 PayOff_b ;

EXTERN bool flag_DispInport
#ifdef GLOBAL
=false
#endif
;

EXTERN bool flag_ServoCutter
#ifdef GLOBAL
=false
#endif
;

EXTERN uint16 CurGrSetMode ;

//2011_09------�s�F�s�W�\��A�{��Cursor���N����
EXTERN uint8 ProgCur_POS;    //�p��cursor���k���p
EXTERN uint8 ProgCur_PosOK;  //�{��cursor�]�w��m
EXTERN uint8 ProgCur_Gcode;  //�W�@��GCode
EXTERN uint8 ProgCur_Gbuf;   //�U�@��GCode

EXTERN uint8 IMMZrtTest_axis;
EXTERN bool flag_IMMZrtTest;
EXTERN bool flag_EnableHome;
EXTERN bool ret_bit4OPEN, ret_bit2OPEN,	ret_bit1OPEN,	ret_bit3OPEN;

EXTERN unsigned char status_xyzabcd_buf ;
EXTERN uint32 timeout_loopcnt
#ifdef GLOBAL
=0
#endif
;
EXTERN uint32 x_loop
#ifdef GLOBAL
=0
#endif
;
EXTERN uint32 x_loop_cur
#ifdef GLOBAL
=0
#endif
;

//�Ȱ��X��
EXTERN bool PauseClock_flg
#ifdef GLOBAL
=false
#endif
;

struct DISPSET3701_ARM{
	bool  flag ;
	uint32 speed[MAX_AXIS] ;
	uint32 dist[MAX_AXIS] ;
	uint8 bSpeed_PMfun[3] ;

} ;
EXTERN struct DISPSET3701_ARM DispSet3701_ARM ;

struct PM_6XXY{
	int rpm[6] ;
	uint8 bSPDFun[6] ;
	uint8 bSPDPlus[6] ;
	uint8 bSPDMinus[6] ;
};
EXTERN struct PM_6XXY oPM_6xxY[]
#ifdef GLOBAL
={
	//650
	{
		{2300	, 2000 	, 1700 	, 1400	, 1000	, 0		,} ,
		{50		, 40	, 30	, 20	, 0		, 0		,} ,
		{50		, 40	, 30	, 20	, 0		, 0		,} ,
		{50		, 50	, 50	, 50	, 0		, 0		,} ,
	} ,
	//635
	{
		{3000	, 2500 	, 2000 	, 1500	, 1000	, 500	,} ,
		{70		, 50	, 50	, 50	, 30	, 0		,} ,
		{90		, 80	, 60	, 50	, 30	, 0		,} ,
		{50		, 50	, 50	, 50	, 50	, 0		,} ,
	} ,	
	//620
	{
		{3200	, 2500 	, 2000 	, 1500	, 1000	, 0		,} ,
		{50		, 40	, 30	, 20	, 0		, 0		,} ,
		{60		, 40	, 30	, 20	, 0		, 0		,} ,
		{50		, 50	, 50	, 50	, 0		, 0		,} ,
	} 
}
#endif
;
EXTERN struct PM_6XXY PM_6xxY ;


#if 0
struct TT1{
	bool flag ;
	WORD no ;
	WORD start ;
	WORD end ;
} ;
EXTERN struct TT1 tt1 ;
#endif



EXTERN int cnt_T_STOP_MDYVAL ;


EXTERN SDWORD Y650_Encoder[10];
EXTERN bool Y650_Encoder_flg
#ifdef GLOBAL
=false
#endif
;
EXTERN bool Y650_Encoder_Xflg
#ifdef GLOBAL
=false
#endif
;
EXTERN SDWORD encoder;
EXTERN bool flag_encoder ;
EXTERN int idx_TDecDisA;

EXTERN UI rs232_base[]
#ifdef GLOBAL
 = { 0x3f8 , 0x2f8 , 0x3e8 } 
#endif
 ;

EXTERN uint8 Set3701_AXIS_Y_ldir
#ifdef GLOBAL
=PLUS_SIGN
#endif
;

EXTERN struct TIMER time_out_step	;
EXTERN int16 cnt_stepDispCurAxis
#ifdef GLOBAL
=0
#endif
 ;
EXTERN struct TIMER timeout_stepDispCurAxis ;

//debug_repair_y//////////////////
EXTERN int first_move_y;
struct REPAIRYBUF{
	SWORD target;
	SWORD exy;
	int   idx;
};

EXTERN REPAIRYBUF repairbuf[100];
EXTERN WORD rey_ridx 
#ifdef GLOBAL
= 0
#endif
; 
EXTERN WORD rey_widx 
#ifdef GLOBAL
= 0
#endif
; 
////////////////////
EXTERN union {
	BYTE 	bytes[4];
	WORD 	word[2];
	DWORD 	dword;
}cvtbuf;
EXTERN int32 Target_Break_cnt
#ifdef GLOBAL
= 0
#endif
;

EXTERN uint8 UseEX5000 
#ifdef GLOBAL
= 0
#endif
;

#if 0   // TODO
EXTERN uint32 Spd_Table_ACC_Time[3][512]
#ifdef GLOBAL
={
//21~40
{1,2,3,5,8,10,14,18,22,28,33,38,45,51,58,66,74,85,93,103,114,125,136,147,159,172,185,199,214,228,246,260,278,293,310,329,345,364,385,404,427,444,468,492,513,535,555,579,605,628,656,681,706,736,762,789,820,847,875,904,934,969,997,1030,1064,1097,1132,1163,1196,1235,1265,1303,1337,1373,1412,1450,1491,1529,1567,1606,1645,1687,1729,1769,1814,1857,1898,1947,1988,2035,2079,2122,2169,2215,2263,2314,2356,2409,2461,2507,2562,2607,2662,2711,2761,2817,2867,2924,2981,3032,3091,3144,3203,3258,3313,3373,3434,3485,3547,3606,3669,3734,3791,3857,3916,3976,4042,4104,4166,4234,4297,4370,4430,4500,4575,4634,4701,4771,4840,4915,4973,5051,5125,5195,5270,5340,5412,5488,5554,5632,5706,5784,5864,5939,6014,6096,6174,6257,6327,6406,6496,6570,6652,6735,6815,6901,6981,7068,7156,7234,7326,7405,7490,7579,7665,7757,7842,7932,8025,8116,8205,8291,8381,8476,8567,8661,8756,8847,8945,9037,9136,9230,9319,9418,9515,9610,9715,9815,9909,10015,10110,10222,10316,10413,10521,10618,10727,10827,10933,11042,11141,11249,11364,11460,11569,11677,11781,11894,11998,12109,12221,12332,12448,12558,12673,12785,12894,13008,13121,13235,13356,13469,13587,13708,13820,13939,14055,14176,14300,14405,14532,14650,14776,14900,15015,15145,15268,15395,15517,15639,15760,15891,16011,16141,16269,16401,16533,16653,16787,16915,17042,17174,17299,17438,17575,17697,17840,17973,18103,18251,18371,18510,18644,18779,18926,19056,19196,19340,19480,19623,19755,19896,20041,20174,20319,20463,20602,20754,20892,21041,21188,21334,21484,21626,21767,21924,22066,22211,22364,22510,22674,22815,22971,23126,23269,23425,23571,23729,23888,24036,24198,24350,24505,24668,24827,24986,25138,25292,25457,25613,25775,25941,26099,26263,26422,26590,26756,26911,27073,27240,27398,27572,27737,27904,28078,28239,28414,28584,28736,28917,29083,29262,29431,29594,29779,29942,30121,30299,30472,30648,30819,30990,31173,31340,31522,31702,31873,32056,32237,32422,32606,32775,32960,33139,33316,33508,33686,33868,34065,34243,34436,34618,34801,34993,35167,35356,35546,35738,35931,36113,36311,36506,36692,36883,37066,37265,37462,37652,37847,38040,38238,38440,38634,38831,39029,39228,39419,39612,39811,40025,40212,40417,40620,40827,41034,41227,41427,41633,41831,42044,42244,42453,42665,42869,43085,43282,43495,43711,43911,44122,44327,44536,44758,44956,45178,45399,45606,45818,46028,46238,46459,46674,46888,47106,47320,47549,47762,47978,48212,48418,48645,48855,49072,49306,49519,49748,49974,50195,50424,50645,50874,51101,51313,51551,51773,52000,52236,52463,52695,52923,53149,53389,53612,53845,54077,54310,54539,54780,55004,55249,55472,55716,55960,56191,56426,56662,56903,57144,57372,57618,57861,58103,58350,58584,58840,59070,59311,59564,59797,60046,60294,60535,60787,61031,61281,61536,61765,62021,62272,62519,62771,63015,63273,63533,63775,64033,64291,64535,64799,65042,65298},
//41~60
{1,2,3,5,7,9,11,15,18,23,26,31,36,42,48,55,61,68,77,84,95,100,110,120,129,139,150,159,173,184,197,209,222,235,250,266,279,295,308,329,342,362,376,394,413,431,449,468,486,506,527,547,569,588,611,634,659,681,703,725,755,776,804,828,852,880,908,933,962,988,1016,1047,1074,1104,1132,1165,1196,1226,1256,1292,1320,1356,1387,1422,1457,1490,1526,1563,1597,1632,1668,1702,1746,1776,1815,1853,1893,1930,1972,2009,2053,2088,2132,2176,2214,2258,2299,2342,2389,2437,2475,2525,2563,2614,2658,2704,2747,2794,2842,2894,2939,2989,3037,3086,3140,3189,3241,3289,3341,3395,3452,3498,3554,3605,3662,3716,3769,3822,3878,3934,3994,4047,4104,4162,4219,4281,4334,4394,4455,4516,4573,4642,4693,4760,4820,4882,4948,5009,5071,5137,5199,5266,5328,5392,5461,5522,5598,5662,5726,5795,5862,5931,6009,6072,6140,6212,6284,6361,6424,6498,6570,6643,6717,6794,6857,6940,7007,7089,7164,7235,7312,7393,7464,7548,7618,7699,7780,7860,7945,8017,8103,8181,8264,8344,8424,8499,8591,8673,8754,8836,8922,9006,9095,9176,9266,9348,9433,9530,9610,9708,9786,9877,9967,10064,10147,10238,10324,10417,10505,10600,10693,10786,10875,10970,11071,11161,11257,11346,11445,11541,11644,11733,11829,11926,12029,12126,12226,12321,12419,12522,12620,12723,12821,12922,13025,13134,13235,13334,13432,13545,13645,13754,13852,13964,14067,14176,14281,14388,14498,14602,14721,14823,14934,15036,15151,15258,15375,15481,15590,15699,15818,15927,16043,16153,16269,16383,16502,16616,16727,16847,16959,17083,17198,17316,17427,17549,17660,17785,17905,18024,18139,18263,18381,18512,18628,18747,18873,18995,19129,19247,19374,19494,19625,19746,19877,19997,20123,20248,20378,20510,20630,20759,20894,21017,21151,21281,21409,21547,21674,21812,21934,22072,22201,22343,22471,22614,22738,22876,23011,23145,23283,23415,23555,23693,23836,23970,24114,24246,24391,24527,24671,24809,24949,25090,25235,25378,25522,25660,25803,25953,26098,26247,26383,26527,26669,26823,26968,27118,27255,27402,27552,27713,27856,28000,28148,28307,28457,28609,28758,28907,29064,29215,29380,29524,29675,29822,29989,30135,30292,30440,30601,30763,30922,31072,31231,31391,31553,31715,31870,32035,32186,32360,32517,32680,32837,33002,33162,33334,33490,33648,33811,33980,34147,34310,34473,34644,34807,34975,35151,35310,35486,35644,35822,35994,36161,36325,36501,36664,36845,37016,37180,37356,37527,37701,37877,38055,38228,38401,38567,38759,38922,39107,39275,39459,39639,39820,39993,40179,40354,40539,40722,40892,41079,41251,41441,41622,41805,41979,42169,42350,42549,42719,42906,43093,43280,43465,43658,43834,44029,44220,44401,44603,44784,44976,45160,45355,45541,45729,45917,46121,46297,46506,46687,46885,47077,47270,47468,47672,47860,48053,48256,48448,48661,48841,49044,49242,49444,49639,49839,50031,50238,50428,50637,50842,51029,51241,51440,51648,51859,52059,52257},
//61~80
{1,2,3,5,7,9,12,15,18,22,26,30,35,40,45,51,57,63,70,77,84,92,100,108,117,126,135,145,155,165,176,187,198,210,222,234,247,260,273,287,301,315,330,345,360,376,392,408,425,442,459,477,495,513,532,551,570,590,610,630,651,672,693,715,737,759,782,805,828,852,876,900,925,950,975,1001,1027,1053,1080,1107,1134,1162,1190,1218,1247,1276,1305,1335,1365,1395,1426,1457,1488,1520,1552,1584,1617,1650,1683,1717,1751,1785,1820,1855,1890,1926,1962,1998,2035,2072,2109,2147,2185,2223,2262,2301,2340,2380,2420,2460,2501,2542,2583,2625,2667,2709,2752,2795,2838,2882,2926,2970,3015,3060,3105,3151,3197,3243,3290,3337,3384,3432,3480,3528,3577,3626,3675,3725,3775,3825,3876,3927,3978,4030,4082,4134,4187,4240,4293,4347,4401,4455,4510,4565,4620,4676,4732,4788,4845,4902,4959,5017,5075,5133,5192,5251,5310,5370,5430,5490,5551,5612,5673,5735,5797,5859,5922,5985,6048,6112,6176,6240,6305,6370,6435,6501,6567,6633,6700,6767,6834,6902,6970,7038,7107,7176,7245,7315,7385,7455,7526,7597,7668,7740,7812,7884,7957,8030,8103,8177,8251,8325,8400,8475,8550,8626,8702,8778,8855,8932,9009,9087,9165,9243,9322,9401,9480,9560,9640,9720,9801,9882,9963,10045,10127,10209,10292,10375,10458,10542,10626,10710,10795,10880,10965,11051,11137,11223,11310,11397,11484,11572,11660,11748,11837,11926,12015,12105,12195,12285,12376,12467,12558,12650,12742,12834,12927,13020,13113,13207,13301,13395,13490,13585,13680,13776,13872,13968,14065,14162,14259,14357,14455,14553,14652,14751,14850,14950,15050,15150,15251,15352,15453,15555,15657,15759,15862,15965,16068,16172,16276,16380,16485,16590,16695,16801,16907,17013,17120,17227,17334,17442,17550,17658,17767,17876,17985,18095,18205,18315,18426,18537,18648,18760,18872,18984,19097,19210,19323,19437,19551,19665,19780,19895,20010,20126,20242,20358,20475,20592,20709,20827,20945,21063,21182,21301,21420,21540,21660,21780,21901,22022,22143,22265,22387,22509,22632,22755,22878,23002,23126,23250,23375,23500,23625,23751,23877,24003,24130,24257,24384,24512,24640,24768,24897,25026,25155,25285,25415,25545,25676,25807,25938,26070,26202,26334,26467,26600,26733,26867,27001,27135,27270,27405,27540,27676,27812,27948,28085,28222,28359,28497,28635,28773,28912,29051,29190,29330,29470,29610,29751,29892,30033,30175,30317,30459,30602,30745,30888,31032,31176,31320,31465,31610,31755,31901,32047,32193,32340,32487,32634,32782,32930,33078,33227,33376,33525,33675,33825,33975,34126,34277,34428,34580,34732,34884,35037,35190,35343,35497,35651,35805,35960,36115,36270,36426,36582,36738,36895,37052,37209,37367,37525,37683,37842,38001,38160,38320,38480,38640,38801,38962,39123,39285,39447,39609,39772,39935,40098,40262,40426,40590,40755,40920,41085,41251,41417,41583,41750,41917,42084,42252,42420,42588,42757,42926,43095,43265,43435,43605,43776},
}
#endif
;
#endif

EXTERN uint8 running_cnt[MAX_AXIS];//ChkAllMotorFinish����tick�p��
struct ST_MANMOV{
	uint8 axis ;
	uint8 dir ;
	struct TIMER timeout ;
};
EXTERN ST_MANMOV  st_ManMov;
	
struct ZRT{
	WORD state ;
	BYTE mode ;
	bool first;	//�ΨӰϤ��⦸�^���I:�Ĥ@��first=true ;�ĤG��first=false
	bool power_on ; //�ΨӰϤ��}����O�_�^�L���I:���^�L���Ipower_on=true ;���^�L���Ipower_on=false
	struct TIMER timeout ;
	SDWORD org_loc ;
	DWORD axis_val ;
	BYTE  sign ;
	int NewVal ;
} ; 
// // EXTERN ZRT zrt[MAX_AXIS] ;	


EXTERN bool loopstart ;
EXTERN 	int loopstart_idx ;
EXTERN SDWORD dw_loop[MAX_AXIS] ;
EXTERN SDWORD looppos[MAX_LOOP][MAX_AXIS] ;
EXTERN bool loopchk[MAX_AXIS] ;

#define PARA_PAGE_INDEX_MAX 2
EXTERN uint8 PARA_PAGE_INDEX 
#ifdef GLOBAL
= 0
#endif
;

//test
struct TTBUG{
	SDWORD buf1[100];
	SDWORD buf2[100];
	SDWORD buf3[100];
	uint32 ridx;
	uint32 widx;
	SDWORD pos;
} ; 
EXTERN TTBUG ttbug ;
//

EXTERN uint32 PCB3_YEAR
#ifdef GLOBAL
= 0
#endif
;

#define CLR_X_ABSPOS
EXTERN uint32 X_ABSPOS
#ifdef GLOBAL
= 0
#endif
;
struct X_GRID_VAR{
	SDWORD g2;
	SDWORD g10;
	SDWORD g3950;
} ; 
EXTERN X_GRID_VAR XGRID ;
EXTERN uint32 zrtcnt
#ifdef GLOBAL
= 0
#endif
;

struct YA_ABSPOS{
	bool 		status[MAX_AXIS];			// ����Ȱ��FŪ�����G:1���\/0����
	bool  	trace[MAX_AXIS];
	DWORD 	gear[MAX_AXIS]; 			// ���F�@����=���F���/������
	long long max[MAX_AXIS] ; 		//*�̤j���=���F�@����*65536_NEW
	long long curpos[MAX_AXIS] ;	//*�ثe��m(+/-)_NEW
	DWORD  	curpos2016[MAX_AXIS] ;// �b�ثe��m�ɪ�2016��
	SDWORD 	zrtcye_val[MAX_AXIS];	//*���F�ثe���_NEW
	DWORD 	zrtpos_val[MAX_AXIS];	//*���F�ثe��m(�T�v�ݥ�)_NEW
	SDWORD 	ovzrtoff[MAX_AXIS];		//*������I����=�̤j���%���F���_NEW
	DWORD		ENCR[MAX_AXIS];				//*�^�¦�m�P���F��m���_NEW
};
EXTERN YA_ABSPOS ya_abspos;

EXTERN bool State5217;
EXTERN bool YAABS_MsgBar; 
EXTERN bool ReadAbs_Err
#ifdef GLOBAL
=false
#endif
;
EXTERN  bool in_ReadAbsMotor
#ifdef GLOBAL
=false
#endif
;

EXTERN  bool in_AB_manual
#ifdef GLOBAL
=false
#endif
;
EXTERN  bool in_Z_manual
#ifdef GLOBAL
=false
#endif
;

EXTERN uint32 SET_RUNDAYS ;
EXTERN uint32 CUR_RUNDAYS ;
EXTERN bool RUNDAYS_Over 
#ifdef GLOBAL
=false
#endif
;

EXTERN unsigned long help_pass 
#ifdef GLOBAL
=0
#endif
;

EXTERN bool ScrnSav_KeyWakeUp 
#ifdef GLOBAL
=false
#endif
;

EXTERN struct TIMER t0 ;

struct TOUCH_SPD{
	bool 	change;
	WORD 	spd;
	WORD	speed;
};
EXTERN bool chktouch;
EXTERN TOUCH_SPD TouchSPD;
EXTERN bool flag_TouchSPDChange 
#ifdef GLOBAL
=false
#endif
;



EXTERN bool x_home 
#ifdef GLOBAL
=true 
#endif
;


EXTERN bool TestMode 
#ifdef GLOBAL
=false
#endif
;



EXTERN  uint8 NewH;
EXTERN  bool Chkraspberry;


EXTERN uint8 KeyKind[256];

EXTERN int16  DDAMax[8] // 1ms�̤j��DDA�� 
#ifdef GLOBAL			//ddamax�����ק令�⭿
= {	80 ,  	//x 24000*100/60/1000=40
	1360 ,	//y 96000*420/60/1000=672
	400	,   //z  24000*250/60/1000=100 (�M�F���40000*250/60/1000=166)
	300 ,   //A-Axis 720000*120/60/1000=144
	600 ,   //B-    400000*450/60/1000=300
	600 ,
	600 ,
	20000	//�Ʈy�ק﷥���ƭ�
}
#endif
; 

EXTERN unsigned repeatno
#ifdef GLOBAL
=3
#endif
;


EXTERN unsigned CLOCKType
#ifdef GLOBAL
=RUN_CLOCK
#endif
;

#define COPY_SIZE  2000
EXTERN char CopyBuf[COPY_SIZE];
#define MAX_fNames     50
EXTERN char fNames[MAX_fNames][15];
EXTERN int len_fNames ;
EXTERN int idx_fNames ;


EXTERN UC KeyInput
#ifdef GLOBAL
=0
#endif
;
EXTERN bool KeyLockCHG
#ifdef GLOBAL
=false
#endif
;
EXTERN bool motor_CHG
#ifdef GLOBAL
=false
#endif
;

EXTERN unsigned char axis_char[] 
#ifdef GLOBAL
= { 'X','Y','Z','A','B','C','D','E'} 
#endif
;

EXTERN bool IsManMode
#ifdef GLOBAL
=false
#endif
;

EXTERN bool HasHand
#ifdef GLOBAL
=false
#endif
;


EXTERN bool EnableTest
#ifdef GLOBAL
=false
#endif
;

EXTERN WORD CurLine
#ifdef GLOBAL
=0
#endif
;

EXTERN uint8 nUsbDisk;

EXTERN 	uint16 INL;
EXTERN 	uint16 INM;
EXTERN 	uint16 INH;
EXTERN 	uint16 INE;
EXTERN 	uint16 OUTL;
EXTERN 	uint16 OUTM;
EXTERN 	uint16 OUTH;

EXTERN 	uint16 OUTE;
EXTERN 	uint16 IND;



