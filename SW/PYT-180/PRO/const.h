
#include "c_const.h"
#define PORT_INM			(rDosMem(pc_base+INM))
#define PORT_INH			(rDosMem(pc_base+INH))
//噴漆功能
#define PORT_STOPRUN		(!(PORT_INM & (MASK_BIT7)))    

#define EXT_ENCODER_MDY  	((!(p_buf->byth >TH_NULL)) && CHK_ROTW1(AXIS_A))
#define EXT_ENCODER_MDY_VAL	((MachineStatus.Type == TYPE_635_835||MachineStatus.Type == TYPE_650_850||MachineStatus.Type == TYPE_1635_1835)?50 :13) 
#define MDY_GAPY    ((MachineStatus.Type == TYPE_635_835||MachineStatus.Type == TYPE_650_850||MachineStatus.Type == TYPE_1635_1835)?128 :79) 
#define MDY_GAPY1     ((MachineStatus.Type == TYPE_635_835||MachineStatus.Type == TYPE_650_850||MachineStatus.Type == TYPE_1635_1835)?98 :49)
#define MDY_GAPY2     (MDY_GAPY-MDY_GAPY1) 
#define SERVO_Y_NEAR         3
#define SERVO_A_NEAR         3


EXTERN char  AxisName[3][MAX_AXIS_8][8];


#define	MODE(man,run,test,step,tmody,smody,para,help,dialog,index,USB_S)				\
	(man?MAN_MODE:0)	+ (run?RUN_MODE:0)	 +(test?TEST_MODE:0)+(step?STEP_MODE:0)+	\
	(tmody?TMODY_MODE:0)+(smody?SMODY_MODE:0)+(para?PARA_MODE:0)+(help?HELP_MODE:0)+	\
	(dialog?DIALOG_MODE:0)+(index?INDEX_MODE:0)+(USB_S?USB_MODE:0)





// EXTERN	KeyMap_t KeyMapTbl[]
// #ifdef GLOBAL
// 	={
// //																							 M R	T S	T S	P H D I U
// //																							 A U	E T	M M	A E I N S
// //																							 N N	S E	O O	R L A D B
// //																							 	  	T P	D D	A P L E
// //																							 		   	  Y Y	    O X
// //																							 				        	G

// 		{KEY_HELP					, KeyHelp					, MODE(1,0,0,0,0,0,0,1,0,0,1)},//MODE(1,1,1,0,0,0,0,1,0,0,1)},
// 		{KEY_PG_UP				, KeyPgUp			 			, MODE(1,0,0,0,1,1,0,1,0,1,1)},
// 		{KEY_PG_DOWN			, KeyPgDown			 			, MODE(1,0,0,0,1,1,0,1,0,1,1)},
//  		{KEY_CHG_CURSOR		, KeyChgCursor		 				, MODE(1,0,0,0,0,0,0,0,0,1,1)},
// 		{KEY_UP						, KeyUp				 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_DOWN					, KeyDown			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
//  		{KEY_LEFT					, KeyLeft			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_RIGHT				, KeyRight						, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_7						, KeyNum7			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_4						, KeyNum4			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_1						, KeyNum1			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_8						, KeyNum8			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_5						, KeyNum5			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_2						, KeyNum2			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
//  		{KEY_0						, KeyNum0			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_9						, KeyNum9			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_6						, KeyNum6			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_3						, KeyNum3			 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
// 		{KEY_SIGN					, KeySign			 		, MODE(1,0,0,0,1,1,1,0,1,1,1)},
// 		{KEY_SPACE_BAR		, KeySpaceBar		 				, MODE(1,0,0,0,1,1,1,0,0,1,1)},
// 		{KEY_SPECIAL			, KeySpecial		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},

// 		{KEY_PLUS_X				, KeyPLUSX			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_X			, KeyMinusX			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_Y_SCALE			, KeyManYScale				, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_Y_SW					, KeyMotorYSW		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},//按修改程式不可使用y軸送線
// 		{KEY_SUSPEND			, KeySuspend		 			, MODE(0,0,1,1,1,1,0,0,0,0,0)},
// 		{KEY_PLUS_Y				, KeyPLUSY			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_Y			, KeyMinusY			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_Z_SW					, KeyMotorZSW		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_PLUS_Z				, KeyPLUSZ			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_Z			, KeyMinusZ			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_A_SW					, KeyMotorASW		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_PLUS_A				, KeyPLUSA			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_A			, KeyMinusA			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_B_SW					, KeyMotorBSW		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_PLUS_B				, KeyPLUSB			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_B			, KeyMinusB			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_C_SW					, KeyMotorCSW		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_PLUS_C				, KeyPLUSC			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_C			, KeyMinusC			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_D_SW					, KeyMotorDSW		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_PLUS_D				, KeyPLUSD			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_D			, KeyMinusD			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_E_SW					, KeyMotorESW		 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_PLUS_E				, KeyPLUSE				 		, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_MINUS_E			, KeyMinusE			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		
// 		{KEY_ZRT					, KeyZrt			 		, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_SPEED_MODE		, KeySetSpeedMode	 				, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_STEP					, KeyStep			 		, MODE(1,1,0,0,0,0,0,0,0,0,0)},
// 		{KEY_TEST					, KeyTest			 		, MODE(1,1,0,0,0,0,0,0,0,0,0)},
// 		{KEY_STOP					, KeyStop			 		, MODE(0,1,1,1,0,0,0,0,0,0,0)},
// 		{KEY_RUN1					, KeyRun1			 		, MODE(1,0,1,1,0,0,0,0,0,0,0)},
// 		{KEY_G0						, KeyG0				 		, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_SPD 					, KeySPD	 		 		, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_CLR_Y				, KeyClrY			 			, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_Y_SW					, KeyMotorYSW		 		, MODE(1,0,0,0,0,0,0,0,0,0,0)},//按修改程式不可使用y軸送線
// 		{KEY_SUSPEND			, KeySuspend		 			, MODE(0,0,1,1,1,1,0,0,0,0,0)},
// 		{KEY_SAFE					, KeySafe			 		, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_COPY_FILE		, KeyCopyFile						, MODE(1,0,0,0,0,0,0,0,1,0,1)},
// 		{KEY_LOAD_FILE		, KeyLoadFile						, MODE(1,0,0,0,0,0,0,0,1,0,1)},
// 		{KEY_T						, KeySetT			 		, MODE(1,0,0,0,1,1,0,0,0,0,0)},
// 		{KEY_SAVE_FILE		, KeySaveFile		 				, MODE(1,0,0,0,0,0,0,0,1,0,1)},
// 		{KEY_INS					, KeyIns			 		, MODE(1,0,0,0,1,1,0,0,0,0,1)},
// 		{KEY_WR						, KeyWr				 		, MODE(1,0,0,0,1,1,1,1,1,1,1)},
//  		{KEY_JMPNN				, KeyJmpnn			 			, MODE(1,0,0,0,0,0,0,0,1,0,1)},
// 		{KEY_T_DELAY			, KeyTDelay			 			, MODE(1,0,0,0,1,1,0,0,0,0,1)},
// 		{KEY_AIR					, KeySetAir			 		, MODE(1,0,0,0,1,1,0,0,0,0,1)},
// 		{KEY_CAN					, KeyCan			 		, MODE(1,0,0,0,1,1,0,0,0,0,1)},
// 		{KEY_SETPRODNO		, KeySetProdno		 				, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_PRODNO0			, KeyProdno0		 			, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_AIRSCRN			, KeyAirScrn		 			, MODE(1,0,0,0,1,1,0,0,0,0,1)},
// 		{KEY_MARKER				,Key_Marker						, MODE(1,0,0,0,1,1,0,0,0,0,1)},
// 		{KEY_PARA					, KeySetPara		 		, MODE(1,0,0,0,0,0,1,0,0,0,1)},
// 		{KEY_CUTTER				, KeyCutter			 			, MODE(1,0,0,0,0,0,0,0,0,0,0)},
// 		{KEY_START_DEGREE	, KeyStartDegree	 				, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_PARA_NOPASS	, KeySetPara_nopass					, MODE(1,0,0,0,0,0,1,0,0,0,1)},
// 		{KEY_END_DEGREE		, KeyEndDegree		 				, MODE(1,0,0,0,0,0,0,0,0,0,1)},
// 		{KEY_START				, KeyStart			 			, MODE(1,0,1,1,0,0,0,0,0,0,0)},
// 		//{KEY_RESET_LOCK_ON, KeyResetLock   						, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_RETURN			, KeyReturn			 , MODE(1,0,0,1,1,0,0,0,0,0,0)},		//按修改可以使用返回功能
// 		{KEY_NEXT			, KeyNext			 , MODE(1,0,0,1,1,0,0,0,0,0,0)},
// 		{KEY_mytest			, KeyMytest			 , MODE(1,0,0,1,1,0,0,0,0,0,0)},
// 		
// 		
// 		{KEY_PARA					, KeySetPara		 			, MODE(1,0,0,0,0,0,1,0,0,0,1)},
// 		{KEY_PARA_NOPASS	, KeySetPara_nopass		, MODE(1,0,0,0,0,0,1,0,0,0,1)},
// 		
// 		
// 		{KEY_HAND_OFF			, KeyHandOff		 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_X1			, KeyHandX1			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_X10			, KeyHandX10		 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_X100		, KeyHandX100		 				, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_X				, KeyHandX			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_Y				, KeyHandY			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_Z				, KeyHandZ			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_A				, KeyHandA			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_B				, KeyHandB			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_C				, KeyHandC			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_D				, KeyHandD			 			, MODE(1,1,1,1,1,1,1,1,0,0,0)},
// 		{KEY_HAND_RIGHT		, KeyHandRight	 					, MODE(1,0,0,1,0,0,0,0,0,0,0)},
// 		{KEY_HAND_LEFT		, KeyHandLeft		 				, MODE(1,0,0,1,0,0,0,0,0,0,0)},

// 	}
// #endif
// ;



#define	WR_RS232(data)									\
	comm_port=0	;										\
	wr_rs232(data) ;									\
	comm_port=1	;										\
	wr_rs232(data) ;
	





#define _GPSET						0



