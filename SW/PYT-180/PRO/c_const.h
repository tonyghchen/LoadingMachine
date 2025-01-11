#define CHG_PAL		0xf
enum{ TH_NULL, TH1_STP,	TH2_STP, TH1_CHK, TH2_CHK, TH3_STP,	TH4_STP,TH3_SPIN,TH4_SPIN, TH_ERR	};
enum{ TD_NULL, TD_1, TD_2, TD_3, TD_4, TD_5	};
enum{ SMART_ZRT, PLUS_ZRT, MINUS_ZRT, NULL_ZRT };


EXTERN	   char	THMark[22]
#ifdef GLOBAL
={ ' ',	0x01, 0x02,	0x03, 0x04,	0x0b, 0x0c,0x0d,0x0e,0x05	,
 0x01,0x02,0x0b,0x0c,0x01,0x02,0x0b,0x0c,0x01,0x02,0x0b,0x0c}
#endif
;


EXTERN	COLOR_T THMark_clr[22]
#ifdef GLOBAL
={
	NULL_COLOR, NULL_COLOR, NULL_COLOR,NULL_COLOR, NULL_COLOR,
	NULL_COLOR, NULL_COLOR,NULL_COLOR,NULL_COLOR,NULL_COLOR,
	BLUE_USR,BLUE_USR,BLUE_USR,BLUE_USR,RED_USR,
	RED_USR,RED_USR,RED_USR, LIGHTMAGENTA_USR,LIGHTMAGENTA_USR,
	LIGHTMAGENTA_USR,LIGHTMAGENTA_USR 
}		//1:BLUE 4:RED 13:LIGHTMAGENTA
#endif
;

EXTERN	char TDMark[6]
#ifdef GLOBAL
	={ ' ',	0x31, 0x32,	0x33, 0x34,	0x35 }
#endif
;

EXTERN	char HMark[4]
#ifdef GLOBAL
	={ 'S',	'+', '-', 'O' }
#endif
;

#if	0
EXTERN char*  AirScrn[]
#ifdef GLOBAL
={
	"-AIR SCRN-",
	"-¨T¬ûµe­±-"
}
#endif
;

#endif

//(sizeof(ModeName)/sizeof(ModeName[0]))
#define	sizeof_ModeName	   3
EXTERN char*  ModeName[]
#ifdef GLOBAL
={
	"  AUTO ",
	"  FAST ", 
	"SPECIAL"
}
#endif
;


EXTERN unsigned	int	 Base3701[]
#ifdef GLOBAL
	={
		MOTOR1_3701_1, MOTOR1_3701_2,
		MOTOR2_3701_1, MOTOR2_3701_2,
		MOTOR3_3701_1, MOTOR3_3701_2,
		MOTOR4_3701_1 ,
	}
#endif
;

EXTERN unsigned	int	 Base2016[]
#ifdef GLOBAL
	={
		MOTOR1_2016_1, MOTOR1_2016_2,
		MOTOR2_2016_1, MOTOR2_2016_2,
		MOTOR3_2016_1, MOTOR3_2016_2,
		MOTOR4_2016_1
	}
#endif
;
EXTERN unsigned	int	 Clr2016[]
#ifdef GLOBAL
	={
		MOTOR1_2016_1_CLR, MOTOR1_2016_2_CLR,
		MOTOR2_2016_1_CLR, MOTOR2_2016_2_CLR,
		MOTOR3_2016_1_CLR, MOTOR3_2016_2_CLR,
		MOTOR4_2016_1_CLR,
	}
#endif
;

EXTERN unsigned	int	 BaseMotorADC[]
#ifdef GLOBAL
	={
		MOTOR1_ADC,	MOTOR2_ADC ,MOTOR3_ADC
	}
#endif
;



#define PORT_CN1			(rDosMem(pc_base+P8255_1+PORTA_8255)) 
#define PORT_EX0			(!(PORT_CN1 & (MASK_BIT5)))
#define PORT_OIL0			(!(PORT_CN1 & (MASK_BIT0)))
#define PORT_SAFETY_DOOR0	(!(PORT_CN1 & (MASK_BIT2)))
#define PORT_EXTRST0		(!(PORT_CN1 & (MASK_BIT1)))
#define PORT_T1				(!(PORT_CN1 & (MASK_BIT6)))
#define PORT_T2				(!(PORT_CN1 & (MASK_BIT7)))
#define PORT_T3				(!(PORT_CN1 & (MASK_BIT3)))
#define PORT_T4				(!(PORT_CN1 & (MASK_BIT4)))


