#define KEY_STATUS			0xc1c
#define KEY_COMMAND 		0xc0c
#define KEY_ACK 			0x1
#define KEY_NORMAL			0xff
#define KEY_FREE_RUN		0x1006
#define KEY_TEST_RUN		0x1077
//#define KEY_SUSPEND 		0x1071
#define KEY_CHANGE_RPM		0x1058
#define KEY_SUSPEND_Y		0x1078

#define KEY_STEP_RUN		0x1069


// initialization Command Word
#define PICmasterICW1		0x20
#define PICmasterICW2		0x21
#define PICmasterICW3		0x21
#define PICmasterICW4		0x21
// operation command word
#define PICmasterOCW1		0x21	// mask register
#define PICmasterOCW2		0x20	// send EOI command
#define PICmasterOCW3		0x20	// miscellaneous

// slave 8259
// initialization Command Word
#define PICslaveICW1		0xa0
#define PICslaveICW2		0xa1
#define PICslaveICW3		0xa1
#define PICslaveICW4		0xa1
// operation command word
#define PICslaveOCW1		0xa1	// mask register
#define PICslaveOCW2		0xa0	// send EOI command
#define PICslaveOCW3		0xa0	// miscellaneous
#define LEVEL_INT			0x19
#define EDGE_INT			0x11

EXTERN  jmp_buf  RetBuf
#ifdef GLOBAL
={
	1
}
#endif
;
EXTERN short RetVal ;
#define INT5				0xd
#define INT7 				0xf
#define INT9 				0x71
#define INT10  				0x72
#define INT11				0x73
#define INT12				0x74	//¤£¯à¥Î
#define INT15				0x77



