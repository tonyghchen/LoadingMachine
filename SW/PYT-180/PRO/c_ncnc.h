#if (DEBUG_RELEASE == DEBUG)
#define PATPATH		"pat\\"
#else
#define PATPATH		""
#endif

//#define DISABLE()						disable();
//#define ENABLE()						enable();

#define ARM_NUM_OF_AXIS			0xf1
#define ARM_DATE				0xf2
#define ARM_MONTH				0xf3
#define ARM_YEAR				0xf4
#define PC_CMD_RAM				0xd8
#define INV_PC_CMD				0x108
#define ARM_CMD_RAM				0xd9
#define INV_ARM_CMD				0x10c
#define ARM_SCL					0x100
#define ARM_SCH					0x104
#define ARM_HD_MOVE				0x20
#define ARM_NORMAL_MOVE			0x25
#define ARM_RESEND				0xa
#define RESET_ALL				0x21
#define ALL_STOP				0x19
#define NEAR_CTL				0x88
#define X_NEAR_CTL				0x88
#define Y_NEAR_CTL				0x89
#define Z_NEAR_CTL				0x8A
#define A_NEAR_CTL				0x8B
#define B_NEAR_CTL				0x8C
#define C_NEAR_CTL				0x8D
#define D_NEAR_CTL				0x8E
#define E_NEAR_CTL				0x8F
#define ALARM_CTL				0x90
#define X_ALARM_CTL				0x90
#define Y_ALARM_CTL				0x91
#define Z_ALARM_CTL				0x92
#define A_ALARM_CTL				0x93
#define B_ALARM_CTL				0x94
#define C_ALARM_CTL				0x95
#define D_ALARM_CTL				0x96
#define E_ALARM_CTL				0x97
#define ARM_STATUS2				0x80
#define ARM_X_STATUS2			0x80
#define ARM_Y_STATUS2			0x81
#define ARM_Z_STATUS2			0x82
#define ARM_A_STATUS2			0x83
#define ARM_B_STATUS2			0x84
#define ARM_C_STATUS2			0x85
#define ARM_D_STATUS2			0x86
#define ARM_E_STATUS2			0x87


////////////////////////////////////////////////////////////////////////////////


#define PAGE_CHARS						(SCRN_W/ASC_CHAR_W-3)
#define PAGE_LINES						((SCRN_H >480)? 21:14)
#define AIR_PAGE_CHARS					23

#define MARKERBOX_MAIN_FCOLOR      BLACK_USR
#define MARKERBOX_MAIN_BCOLOR      GRAY_14
//ASC_CHAR_W:8
//SCRN_W:640
//AIR_PAGE_CHARS:23
//PAGE_CHARS:SCRN_W/ASC_CHAR_W-3 = (640 / 8 )-3 = 77
//AIR_BOX_OFF				((PAGE_CHARS-AIR_PAGE_CHARS)*ASC_CHAR_W-4) = (77 - 23 )* 8 -4 = 428
#define MARKER_PAGE_CHARS 16
#define MARKER_BOX_OFF				((PAGE_CHARS-MARKER_PAGE_CHARS)*ASC_CHAR_W-4) 

#define MAX_FILE_NO 					100
#define PAGE_LINES_INDEX				20
#define MAX_PROG_LINE					100
#define MAX_AIR_LINE					100
#define MAX_LOOP						10
#define MAX_AUTO_SPEED					100
#define MAX_FAST_SPEED					100
#define AIR_LOC_POS 					(SCRN_W/ASC_CHAR_W-11) //640/8=80 , 80-11=69

#define MAX_REPAIR_SPD					20
#define MAX_REPAIR_DST					20
#define MAX_POSITION_ZONE				90
#define MAX_GAIN_VAL					90
#define MIN_GAIN_VAL					10
#define MAX_MAN_VAL 					100

#define PROG_VAL_MARK					0xffff
#define PROG_VAL_NULL					0xfffe

#define START_X 						MAX_PROG_AXIS
#define END_X							0
#define AIR_START_X 					(MAX_PROG_AXIS+1)
#define AIR_END_X 					  	(MAX_PROG_AXIS+2)

#define AXIS_X							0
#define AXIS_Y							1
#define AXIS_Z							2
#define AXIS_A							3
#define AXIS_B							4
#define AXIS_C							5
#define AXIS_D							6
#define AXIS_E							7

#define DISP_DELAY						(320)

#define MAX_ERP_BUF 					4000
#define MAX_KEY_BUF 					5
#define NORMAL_REPEAT					1000	// 2000
#define AXIS_X_REPEAT					600 	// 800
#define AXIS_Y_REPEAT					400
#define AXIS_Z_REPEAT					600 	// 800
#define AXIS_A_REPEAT					600 	// 800
#define AXIS_B_REPEAT					600 	// 800
#define AXIS_C_REPEAT					600 	// 800
#define AXIS_D_REPEAT					600 	// 800
#define AXIS_E_REPEAT					600 	// 800

enum{ MAX_SAFE_RANGE, MIN_SAFE_RANGE };
enum{ SAFE_OFF, SAFE_ON, SAFE_TEST };
enum{ OFF_CLOCK, RUN_CLOCK, TEST_CLOCK, STEP_CLOCK ,STEP_ON_CLOCK};
enum{ PRESS_KEY, RELEASE_KEY };
enum{ AUTO, FAST, SPEC };


#define MAN_MODE						0x0001u
#define RUN_MODE						0x0002u
#define TEST_MODE						0x0004u
#define STEP_MODE						0x0008u
#define TMODY_MODE						0x0010u
#define SMODY_MODE						0x0020u
#define PARA_MODE						0x0040u
#define HELP_MODE						0x0080u
#define DIALOG_MODE 					0x0100u
#define INDEX_MODE						0x0200u
#define USB_MODE						0x0400u
#define IDLE_MODE						0x0800u
enum{ CHK_FAST_POS, CHK_FAST_HOME, CHK_AUTO_RUN, CHK_AUTO_END, CHK_REMAKE_AUTO, CHK_REMAKE_FAST };
#define INI_DISP_BUF()	pDispBuf=ept_DispBuf;

EXTERN ept_char SetAirBuf;

#ifdef SetAirBuf_value      // TODO : 
#undef SetAirBuf_value
#endif 

#define SetAirBuf_value 		SetAirBuf.value
#define INI_SETAIR_BUF()	SetAirBuf=ept_DispBuf;
#define FILL_DISP_BUF(code)  EPT_BC(pDispBuf_value,pDispBuf); *pDispBuf_value++=code;
#define FILL_SETAIR_BUF(code)  EPT_BC(SetAirBuf_value,SetAirBuf); *SetAirBuf_value++=code;
#define FILL_DISP_BUF2(code1,code2)  FILL_DISP_BUF(code1);	FILL_DISP_BUF(code2);
#define FILL_DISP_BUF3(code1,code2,code3)  FILL_DISP_BUF2(code1,code2);  FILL_DISP_BUF(code3);
#define FILL_DISP_BUF4(code1,code2,code3,code4)  FILL_DISP_BUF3(code1,code2,code3);  FILL_DISP_BUF(code4);
#define FILL_DISP_BUF5(code1,code2,code3,code4,code5)  FILL_DISP_BUF3(code1,code2,code3);  FILL_DISP_BUF2(code4,code5);
#define FILL_DISP_BUF6(code1,code2,code3,code4,code5,code6)  FILL_DISP_BUF3(code1,code2,code3);  FILL_DISP_BUF3(code4,code5,code6);
#define FILL_DISP_BUF7(code1,code2,code3,code4,code5,code6,code7)  FILL_DISP_BUF3(code1,code2,code3);  FILL_DISP_BUF4(code4,code5,code6,code7);
#define FILL_DISP_BUF8(code1,code2,code3,code4,code5,code6,code7,code8)  FILL_DISP_BUF3(code1,code2,code3);  FILL_DISP_BUF5(code4,code5,code6,code7,code8);
#define LEN_DISP_BUF()  (pDispBuf_value-DispBuf) 
#define CHECK_QUAN_OK()   (MachineStatus.cur_quan>=MachineStatus.set_quan)
#define CHECK_MISS_OK()   (MachineStatus.set_miss!=0 && MachineStatus.cur_miss>=MachineStatus.set_miss)



#define LIGHT_ON()															\
	BOUTM |= MASK_BIT3;														\
	*(pc_base+OUTM)= BOUTM ;

#define LIGHT_OFF() 														\
	BOUTM |= MASK_BIT2;														\
	*(pc_base+OUTM)= BOUTM ;
//檢測M68K clock 16MHZ 或10 HZ
#define GET_CLOCK() 														\
	(((*(P8255_1+PORTB_8255))&0x80)?10:16)

#if 0
#define	KEY_CLR_QTY 					????
#endif




	#define  KEY_HAND_RESET 					0x8f
	#define  KEY_HAND_RIGHT 					0x99
	#define  KEY_HAND_LEFT						0x90
	#define  KEY_HAND_OFF						0xf0
	#define  KEY_HAND_X 						0xf1
	#define  KEY_HAND_Y 						0xf2
	#define  KEY_HAND_Z 						0xf3
	#define  KEY_HAND_A 						0xf4
	#define  KEY_HAND_B 						0xfa
	#define  KEY_HAND_C 						0xfb
	#define  KEY_HAND_D							0xfc
	#define  KEY_HAND_X1						0xf5
	#define  KEY_HAND_X10						0xf6
	#define  KEY_HAND_X100						0xf7

//小鍵盤
#define  KEY_HAND_RESET_S 				0x8f
#define  KEY_HAND_RIGHT_S 				0xff
#define  KEY_HAND_LEFT_S				0xff
#define  KEY_HAND_OFF_S					0xff
#define  KEY_HAND_X_S 					0xff
#define  KEY_HAND_Y_S 					0xff
#define  KEY_HAND_Z_S 					0xff
#define  KEY_HAND_A_S 					0xff
#define  KEY_HAND_B_S 					0xff
#define  KEY_HAND_C_S 					0xff
#define	 KEY_HAND_D_S					0xff

#if 1
#define	KEY_HAND_E						0xfd
#endif



//小鍵盤
#define  KEY_HAND_X1_S					0xff
#define  KEY_HAND_X10_S					0xff
#define  KEY_HAND_X100_S				0xff
//////////////////////////////////////////////////////////////////////////////

#define NO_OPERATION_3701				0x0
#define RD_XREG_3701					0x1
#define RD_YREG_3701					0x2
#define RD_UREG_3701					0x3
#define RD_VREG_3701					0x4
#define RD_CREG_3701					0x5
#define RD_DREG_3701					0x6
#define WR_XREG_3701					0x9
#define WR_YREG_3701					0xa
#define WR_UREG_3701					0xb
#define WR_VREG_3701					0xc
#define WR_CREG_3701					0xd
#define WR_DREG_3701					0xe
#define INTERPOLATION_INITIALIZE_3701	0xf

#define BUS_WIDTH				1
#define BASE_ADDR				0


#define CMD51_NONE						0x55
#define CMD51_EMSTOP					0x02
#define CMD51_RESTART					0x03
#define CMD51_RDYDATA1					0x04
#define CMD51_MOVE_CW					0x06
#define CMD51_MOVE_CCW					0x07
#define CMD51_MOVE_CW_MAN				0x26
#define CMD51_MOVE_CCW_MAN				0x27
#define CMD51_MOVE_CW_CHKSUM			0x36
#define CMD51_MOVE_CCW_CHKSUM			0x37
#define CMD51_MOVE_CW_MAN_CHKSUM		0x46
#define CMD51_MOVE_CCW_MAN_CHKSUM		0x47
#define CMD51_NEAR_GAIN 				0x08
#define CMD51_SERVO_ON                 	0x10
#define CMD51_SERVO_OFF					0x0f

#define ST51_NEAR						0x01
#define ST51_DIS_SPD					0x02
#define ST51_LINEOFF					0x03			//馬達線掉了
#define ST51_DATAOK1					0x04
#define ST51_OVERFLOW					0x06
#define ST51_NEAR_OK					0x07
#define ST51_RUNNING					0x08
#define ST51_OVERLAY					0x09
#define ST51_RE_SEND					0x0a	// checksum error
#define DATA51_L						(0x04*BUS_WIDTH)
#define DATA51_M						(0x08*BUS_WIDTH)
#define DATA51_H						(0x0c*BUS_WIDTH)
#define W_CMD_51						(0x14*BUS_WIDTH)
#define R_CMD_51						(0x24*BUS_WIDTH)
#define PARA_51 						(0x20*BUS_WIDTH)
#define STATUS_51						(0x28*BUS_WIDTH)
#define PORTA_8255						(0x0*BUS_WIDTH)
#define PORTB_8255						(0x4*BUS_WIDTH)
#define PORTC_8255						(0x8*BUS_WIDTH)
#define CTRL_8255						(0x3*BUS_WIDTH)



#if N620
#define P8255_1 						(BASE_ADDR+(0xc00+0x8)) 		//	INL(BASE_ADDR+(0xc08))
#define P8255_2 						(BASE_ADDR+(0xc00+0))			//	OUTL
#define P8255_3 						(BASE_ADDR+(0x28))
#define PINTS							(BASE_ADDR+(0xc00+0x10))		//中斷狀態
#define PINTC							(BASE_ADDR+(0xc00+0x12))		//中斷控制
#define INL_C 							(P8255_1+0) 					//	0xc800:0xc08
#define INM_C							(P8255_1+2) 					//	0xc800:0xc0a
#define INH_C 							(P8255_1+4) 					//	0xc800:0xc0c
#define OUTL_C							(P8255_2+0) 	//輸出埠(bit7..0)		0xc800:0xc00
#define OUTM_C							(P8255_2+2) 	//輸出埠(bit15..8)		0xc800:0xc02
#define OUTH_C							(P8255_2+4) 	//輸出埠(bit19..16) 	0xc800:0xc04
#define DriverClear						0xf2
#define DriverServoOn					0xf3   //0:servo on/1:servo off
#define DriverALM						0xf4
#define DriverNEAR						0xf5
#define HOMEStatus						0xf7
#define INL_C_NewH							0xc08
#define INM_C_NewH 							0xc0a
#define INH_C_NewH							0xc0c//6,7->IO2 IN[1,2]
#define INE_C_NewH							0xc0e
#define OUTL_C_NewH							0xc00
#define OUTM_C_NewH						0xc02	//6,7->IO2 OUT[17,18]

#define OUTH_C_NewH						0xc04 //IO2 OUT1~8
#define OUTE_C_NewH						0xc06 //IO2 OUT9~16
//#define OUTM_C_NewH						0xc02	//6,7->IO2 OUT[17,18]
//#define INH_C_NewH							0xc0c//6,7->IO2 IN[1,2]
#define IND_C_NewH							0xc20//IO2 IN3~10


#else
#define P8255_1 						(BASE_ADDR+(0xc00+0x10))	//  INL(BASE_ADDR+(0xc10))
#define P8255_2 						(BASE_ADDR+(0xc00+0))		//	OUTL	
#define P8255_3 						(BASE_ADDR+(0x28))
#define PINTS							(BASE_ADDR+(0xc00+0x20))	//中斷狀態
#define PINTC							(BASE_ADDR+(0xc00+0x24))	//中斷控制
#define OUTL_C							(P8255_2+PORTA_8255)		//輸出埠(bit7..0)
#define OUTM_C							(P8255_2+PORTB_8255)		//輸出埠(bit14..8)
#endif



#define MOTOR1_3701_1					(BASE_ADDR+(0x000000+0x00)*BUS_WIDTH)
#define MOTOR1_3701_2					(BASE_ADDR+(0x000000+0x40)*BUS_WIDTH)
#define MOTOR2_3701_1					(BASE_ADDR+(0x000000+0x80)*BUS_WIDTH)
#define MOTOR2_3701_2					(BASE_ADDR+(0x000200+0x00)*BUS_WIDTH)
#define MOTOR3_3701_1					(BASE_ADDR+(0x000200+0x40)*BUS_WIDTH)
#define MOTOR3_3701_2					(BASE_ADDR+(0x000200+0x80)*BUS_WIDTH)
#define MOTOR4_3701_1					(BASE_ADDR+(0x000400+0x00)*BUS_WIDTH)
#define MOTOR1_2016_1					(BASE_ADDR+(0x000000+0x00+0x30)*BUS_WIDTH)
#define MOTOR1_2016_2					(BASE_ADDR+(0x000000+0x40+0x30)*BUS_WIDTH)
#define MOTOR2_2016_1					(BASE_ADDR+(0x000000+0x80+0x30)*BUS_WIDTH)
#define MOTOR2_2016_2					(BASE_ADDR+(0x000200+0x00+0x30)*BUS_WIDTH)
#define MOTOR3_2016_1					(BASE_ADDR+(0x000200+0x40+0x30)*BUS_WIDTH)
#define MOTOR3_2016_2					(BASE_ADDR+(0x000200+0x80+0x30)*BUS_WIDTH)
#define MOTOR4_2016_1					(BASE_ADDR+(0x000400+0x00+0x30)*BUS_WIDTH)
#define MOTOR1_2016_1_CLR				(BASE_ADDR+(0x000000+0x00+0x34)*BUS_WIDTH)
#define MOTOR1_2016_2_CLR				(BASE_ADDR+(0x000000+0x40+0x34)*BUS_WIDTH)
#define MOTOR2_2016_1_CLR				(BASE_ADDR+(0x000000+0x80+0x34)*BUS_WIDTH)
#define MOTOR2_2016_2_CLR				(BASE_ADDR+(0x000200+0x00+0x34)*BUS_WIDTH)
#define MOTOR3_2016_1_CLR				(BASE_ADDR+(0x000200+0x40+0x34)*BUS_WIDTH)
#define MOTOR3_2016_2_CLR				(BASE_ADDR+(0x000200+0x80+0x34)*BUS_WIDTH)
#define MOTOR4_2016_1_CLR				(BASE_ADDR+(0x000400+0x00+0x34)*BUS_WIDTH)
//c8050-----pe<=1
//c80c0-----tsel <=1
#define MOTOR1_8254 					(BASE_ADDR+(0x000040+0x10)*BUS_WIDTH)
#define MOTOR4_8254 					(BASE_ADDR+(0x000000+0xc0)*BUS_WIDTH)
//Speed counter(low byte) SCL----address base+0x90----MOTOR2_8254
//Speed counter(high byte)SCH----address base+0x98----MOTOR3_8254
#define INTEL8051_SCL 					(BASE_ADDR+(0x000080+0x10)*BUS_WIDTH)
#define INTEL8051_SCH					(BASE_ADDR+(0x000080+0x18)*BUS_WIDTH)
#define MOTOR1_ADC						(BASE_ADDR+(0x000000+0x40+0x38)*BUS_WIDTH)
#define MOTOR2_ADC						(BASE_ADDR+(0x000200+0x40+0x38)*BUS_WIDTH)
#define MOTOR3_ADC						(BASE_ADDR+(0x000400+0x40+0x38)*BUS_WIDTH)
#define MOTOR1_P55_1					MOTOR1_3701_1
#define MOTOR1_P55_2					MOTOR1_3701_1
#define MOTOR2_P55_1					MOTOR1_3701_1
#define MOTOR2_P55_2					MOTOR2_3701_2
#define MOTOR3_P55_1					MOTOR2_3701_2
#define MOTOR3_P55_2					MOTOR2_3701_2
// Interrupt Enable Port (High(A,B,C)/Low byte(X,Y,Z))
#define IEPL							(pc_base+MOTOR1_3701_1+PARA_51)
#define R_IEPL							rDosMem(IEPL)
#define W_IEPL(data)					wDosMem(IEPL,(uint8)(data))
#define IEPH							(pc_base+MOTOR2_3701_2+PARA_51)
#define R_IEPH							rDosMem(IEPH)
#define W_IEPH(data)					wDosMem(IEPH,(uint8)(data))
#define IEPD							(pc_base+MOTOR4_3701_1+PARA_51)
#define R_IEPD							rDosMem(IEPD)
#define W_IEPD(data)					wDosMem(IEPD,(uint8)(data))
#define ARM_IEP							(pc_base+0x114)
#define R_ARM_IEP						rDosMem(ARM_IEP)
#define W_ARM_IEP(data)					wDosMem(ARM_IEP,(uint8)(data))
// Interrupt Check Port (High(A,B,C)/Low byte(X,Y,Z))
#define ICPL							(pc_base+MOTOR1_3701_1+STATUS_51)
#define R_ICPL							rDosMem(ICPL)
#define W_ICPL(data)					wDosMem(ICPL,(uint8)(data))
#define ICPH							(pc_base+MOTOR2_3701_2+STATUS_51)
#define R_ICPH							rDosMem(ICPH)
#define W_ICPH(data)					wDosMem(ICPH,(uint8)(data))
#define ICPD							(pc_base+MOTOR4_3701_1+STATUS_51)
#define R_ICPD							rDosMem(ICPD)
#define W_ICPD(data)					wDosMem(ICPD,(uint8)(data))
#define ARM_ICP							(pc_base+0x110)
#define R_ARM_ICP						rDosMem(ARM_ICP)
#define W_ARM_ICP(data)					wDosMem(ARM_ICP,(uint8)(data))



#define SAFE_CTRL						0xba4000l
#define SAFE_STATUS 					0xba8000l

#define OFF_PATTERN   187
#define	SAVE_PARAMETERS_int1(x0)								\
		iptr = (int *)farmalloc(sizeof(int)*1) ;				\
		iptr[0]= x0 ;

#define	GET_PARAMETERS_int1(x0) 								\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		farfree(iptr)

#define	SAVE_PARAMETERS_int2(x0,x1) 							\
		iptr = (int *)farmalloc(sizeof(int)*2) ;				\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;

#define	GET_PARAMETERS_int2(x0,x1)								\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		farfree(iptr)

#define	SAVE_PARAMETERS_int3(x0,x1,x2)							\
		iptr = (int *)farmalloc(sizeof(int)*3) ;				\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;

#define GET_PARAMETERS_int3(x0,x1,x2)							\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		farfree(iptr)

#define	SAVE_PARAMETERS_int4(x0,x1,x2,x3)						\
		iptr = (int *)farmalloc(sizeof(int)*4) ;				\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;

#define	GET_PARAMETERS_int4(x0,x1,x2,x3)						\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		farfree(iptr)

#define	SAVE_PARAMETERS_int5(x0,x1,x2,x3,x4)					\
		iptr = (int *)farmalloc(sizeof(int)*5) ;				\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;											\
		iptr[4]= x4 ;

#define	GET_PARAMETERS_int5(x0,x1,x2,x3,x4) 					\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		int x4 = iptr[4] ;										\
		farfree(iptr)

#define	SAVE_PARAMETERS_int6(x0,x1,x2,x3,x4,x5) 				\
		iptr = (int *)farmalloc(sizeof(int)*6) ;				\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;											\
		iptr[4]= x4 ;											\
		iptr[5]= x5 ;

#define	GET_PARAMETERS_int6(x0,x1,x2,x3,x4,x5)					\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		int x4 = iptr[4] ;										\
		int x5 = iptr[5] ;										\
		farfree(iptr)

#define	SAVE_PARAMETERS_int7(x0,x1,x2,x3,x4,x5,x6)				\
		iptr = (int *)farmalloc(sizeof(int)*7) ;				\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;											\
		iptr[4]= x4 ;											\
		iptr[5]= x5 ;											\
		iptr[6]= x6 ;

#define	GET_PARAMETERS_int7(x0,x1,x2,x3,x4,x5,x6)				\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		int x4 = iptr[4] ;										\
		int x5 = iptr[5] ;										\
		int x6 = iptr[6] ;										\
		farfree(iptr)

#define	SAVE_PARAMETERS_int8(x0,x1,x2,x3,x4,x5,x6,x7)			\
		iptr = (int *)farmalloc(sizeof(int)*8) ;				\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;											\
		iptr[4]= x4 ;											\
		iptr[5]= x5 ;											\
		iptr[6]= x6 ;											\
		iptr[7]= x7 ;

#define	GET_PARAMETERS_int8(x0,x1,x2,x3,x4,x5,x6,x7)			\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		int x4 = iptr[4] ;										\
		int x5 = iptr[5] ;										\
		int x6 = iptr[6] ;										\
		int x7 = iptr[7] ;										\
		farfree(iptr)

#define	STRN(stridx,n,len)										\
		char *cptr =(char *)(iptr+stridx) ; 					\
		char *arr_str[n] ;										\
		for(int i=0 ; i < n ; i++){ 							\
			arr_str[i]= cptr ;									\
			cptr +=len ;										\
		}


#define	SAVE_PARAMETERS_int1_strn(x0,n,len) 					\
		iptr = (int *)farmalloc(sizeof(int)*1+(len)*n) ;		\
		iptr[0]= x0 ;											\
		STRN(1,n,len)


#define	GET_PARAMETERS_int1_strn(x0,n,len)						\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		STRN(1,n,len)

#define	SAVE_PARAMETERS_int3_strn(x0,x1,x2,n,len)				\
		iptr = (int *)farmalloc(sizeof(int)*3+n*len) ;			\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		STRN(3,n,len)

#define	GET_PARAMETERS_int3_strn(x0,x1,x2,n,len)				\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		STRN(3,n,len)

#define	SAVE_PARAMETERS_int4_strn(x0,x1,x2,x3,n,len)			\
		iptr = (int *)farmalloc(sizeof(int)*4+n*len) ;			\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;											\
		STRN(4,n,len)

#define	GET_PARAMETERS_int4_strn(x0,x1,x2,x3,n,len) 			\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		STRN(4,n,len)

#define	SAVE_PARAMETERS_int6_strn(x0,x1,x2,x3,x4,x5,n,len)		\
		iptr = (int *)farmalloc(sizeof(int)*6+n*len) ;			\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;											\
		iptr[4]= x4 ;											\
		iptr[5]= x5 ;											\
		STRN(6,n,len)

#define	GET_PARAMETERS_int6_strn(x0,x1,x2,x3,x4,x5,n,len)		\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		int x4 = iptr[4] ;										\
		int x5 = iptr[5] ;										\
		STRN(6,n,len)


#define	SAVE_PARAMETERS_int7_strn(x0,x1,x2,x3,x4,x5,x6,n,len)	\
		iptr = (int *)farmalloc(sizeof(int)*7+len*n) ;			\
		iptr[0]= x0 ;											\
		iptr[1]= x1 ;											\
		iptr[2]= x2 ;											\
		iptr[3]= x3 ;											\
		iptr[4]= x4 ;											\
		iptr[5]= x5 ;											\
		iptr[6]= x6 ;											\
		STRN(7,n,len)

#define	GET_PARAMETERS_int7_strn(x0,x1,x2,x3,x4,x5,x6,n,len)	\
		int *iptr= (int *)dptr ;								\
		int x0 = iptr[0] ;										\
		int x1 = iptr[1] ;										\
		int x2 = iptr[2] ;										\
		int x3 = iptr[3] ;										\
		int x4 = iptr[4] ;										\
		int x5 = iptr[5] ;										\
		int x6 = iptr[6] ;										\
		STRN(7,n,len)

#define	FORCE_PROC_QUEUE			while(exe_proc_queue()) ;
#define	ENABLE_INPORT_INT(mask)		wDosMem(pc_base+PINTC,BPINTC |= mask); 
#define	DISABLE_INPORT_INT(mask)	wDosMem(pc_base+PINTC,BPINTC &= ~mask); 
#define	DEBOUNCE_TIME				0x10000L


 
#define	ADD_DOT_01(buf)							\
		Cptr s=buf-1 , t= buf ;					\
		*t--= *s-- ;							\
		*t--= '.' ; 							\
		buf++ ;
#define	ADD_MINUS_01(buf)						\
		Cptr s=buf-1 , t= buf ;					\
		*t--= *s-- ;							\
		*t--= '-' ; 							\
		buf++ ;
#define	ADD_DOT_02(buf)							\
		Cptr s=buf-1 , t= buf ;					\
		*t--= *s-- ;							\
		*t--= *s-- ;							\
		*t--= '.' ; 							\
		buf++ ;
		
#define ADD_DOT_UNIT(axis)									\
		switch(MachineStatus.Unit[axis]){					\
		case UNIT_DEG:										\
			{ADD_DOT_01(pDispBuf_value) ;}						\
			break ;											\
		case UNIT_MM:										\
		case UNIT_CIR:										\
			{ADD_DOT_02(pDispBuf_value) ;  }						\
			break ;											\
		default:											\
			break ;											\
		}
		
		
enum { UNIT_GRID , UNIT_DEG , UNIT_MM,UNIT_CIR} ;






#define MANMOV_AXIS(AXIS,DIR,key,rate,delay,MAN_HAND)\
if (NewH){												\
	SManMov.dir=DIR ;									 	\
	SManMov.axis=AXIS ;										\
	SManMov.man_hand=MAN_HAND ;								\
	RunManMov () ;											\
}														\


#define Has_spd(tt)		((tt->wspd&0xfff) && tt->wspd!=PROG_VAL_NULL)


		
//#define STATUS_ADDR(axis)  ((axis_type == INTEL8051_AXIS)? (pc_base+Base3701[axis]+R_CMD_51):(pc_base+0xd+(axis << 4)))
#define DISPCURPROGLIST														\
	buf_DispCurProgList[wr_DispCurProgList++]=MachineStatus.last_line ;		\
	if(wr_DispCurProgList >= NO_DispCurProgList){							\
		wr_DispCurProgList=0 ;												\
	}																		\
	no_DispCurProgList++ ;
#define BMOTORGRID_X		BMOTORGRID(AXIS_X)
#define CAL_XMAX																\
	SDWORD ttt = BMOTORGRID_X;                                                  \
	Grid2Unit(AXIS_X,ttt) ;                                                     \
	DWORD xmax= dBinToBcd(5,ttt) ;                                                  
	
#define VERIFY_XSTARTEND														\
	/*X軸起始格數設定值必須小於X軸最大格數*/   									\
	if(ProgBuf[line].dval[START_X]==PROG_VAL_NULL){								\
		ProgBuf[line].dval[START_X]=ProgBuf[line].dval[END_X];					\
	}																			\
	if(	(s=ProgBuf[line].dval[START_X]&0xffffL) >= xmax ){                       \
		*errline = line;	return(	PROG_SX_ERR	);                              \
	}                                                                           \
	/*X軸結束格數設定值必須小於X軸最大格數*/                                    \
	if(	(e=ProgBuf[line].dval[END_X]&0xffffL)   >=	xmax ){                     \
		*errline = line;	return(	PROG_EX_ERR	);                              \
	}
#define CHECK_Z																					\
	if(check_z){                                                                                \
		/*檢查Z軸以上有程式存在,但該軸被關閉*/												    \
		for(BYTE	axis=AXIS_Z ; axis <	Progaxis_no() ;	axis++){                      		\
			if((!MachineStatus.motor[axis])	&& (ProgBuf[line].dval[axis]!=PROG_VAL_NULL)){       \
				*errline = line;  return( PROG_ZOFF_ERR	);                                      \
			}                                                                                   \
		}                                                                                       \
	}
#define VERIFY_PROG_LINE_ERR																	\
	/*第一行gcode為0,代表沒有程式存在===>故為錯誤*/                                             \
	if(	line ==	0 )	{ *errline = line;	return(	PROG_LINE_ERR ); }                              \
	/*程式太長*/                                                                                \
	if(	line >=	MAX_PROG_LINE )	{ *errline = MAX_PROG_LINE-1;  return( PROG_LINE_ERR );	}
	
//亮綠燈	
#define WARN_LIGHT_ON_GREEN  	wDosMem(pc_base+OUTM,BOUTM |= MASK_BIT4) ;\
				if(MachineStatus.BUZZER){\
					RUN_MODE_LED_ON;\
					IDLE_MODE_LED_OFF;\
				}
//亮紅燈
#define WARN_LIGHT_OFF_RED 	wDosMem(pc_base+OUTM,BOUTM &= (~MASK_BIT4)) ;\
				if(MachineStatus.BUZZER){\
					RUN_MODE_LED_OFF;\
					IDLE_MODE_LED_ON;\
				}


#define RUN_MODE_LED_ON 	wDosMem(pc_base+OUTM,BOUTM |= MASK_BIT7) ;
#define RUN_MODE_LED_OFF 	wDosMem(pc_base+OUTM,BOUTM &= (~MASK_BIT7)) ;
#define IDLE_MODE_LED_ON 	wDosMem(pc_base+OUTH,BOUTH |= MASK_BIT0) ;
#define IDLE_MODE_LED_OFF wDosMem(pc_base+OUTH,BOUTH &= (~MASK_BIT0)) ;

#define MIN_AUTOHOOK 			10
#define MAX_AUTOHOOK            3950
								
#define MWAIT_MOTOR_NEAR(near,timeout_wait)																			\
			{																						\
				static WORD lcur_x ;																\
				WORD x= near;																		\
				WORD wcur_x = (WORD)(wRead2016(AXIS_X));											\
				WORD llimit;																		\
				llimit=(wait_motor->sdchk_pos >x)?wait_motor->sdchk_pos - x:0 ;								\
				if(!((llimit <= wcur_x) && (wcur_x	<= (wait_motor->sdchk_pos+x)))){						\
					if(flag_timeoutoff){															\
						ActTblIdx-- ;																\
					}																				\
					else{																				\
						/* check time out */														\
						if(x_cnt ==0){																\
							lcur_x = (WORD)(wRead2016(AXIS_X));										\
						}																			\
						x_cnt++ ;																	\
						if(x_cnt == 60){															\
							x_cnt=0 ;																\
							timeout_loopcnt++ ;														\
							WORD difx= (wcur_x >= lcur_x)?(wcur_x-lcur_x):(lcur_x-wcur_x) ;			\
							if(difx >= 2){															\
								ActTblIdx--	;														\
							}																		\
							else{																	\
								timeout_wait++ ;													\
								x_loop +=wcur_x ;													\
								x_loop_cur=wcur_x ;													\
							}																		\
						}																			\
						else{																		\
							ActTblIdx-- ;															\
						}                                                                           \
					}																				\
				}																					\
				else{																				\
					x_loop+=wcur_x ;																\
					x_cnt=0 ;																		\
				}																					\
			}
			
			
			
			
#define	LBYTE		0
#define	MBYTE		1
#define	HBYTE		2
