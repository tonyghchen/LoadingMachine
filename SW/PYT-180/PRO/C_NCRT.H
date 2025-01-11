#if DP_PART_PC != 1
#define ASC_CHAR_W				8
#define ASC_CHAR_H				15
#define CH_CHAR_W				16
#define CH_CHAR_H				15
#define BIG_DIGIT_W 			16
#define BIG_DIGIT_H 			20
#define ICON_W					16
#define ICON_H					15
#define ICON_OP_OR				-1


/*
enum
{
	EDIT_ICON, WORK_ICON, TEST_ICON, STEP_ICON, MODY_ICON, PARA_ICON, HELP_ICON, W_MAX_ICON, W_MIN_ICON,
	W_CLOSE_ICON, W_STATUS_ICON, TOOL_ICON, POS_ICON, MAN_ICON, HAND_ICON, SCALE_ICON, LINK_ICON,
	ERROR_ICON, QUAN_ICON, TOUCH_ICON, CHOICE_ICON, UNCHOICE_ICON, SAFE_ICON, OK_ICON,
	MODE_ICON, FILE_ICON, FAST_ICON, AUTO_ICON, RPM_ICON, WARNING_ICON, W_UP_ICON, W_DOWN_ICON,
	W_LEFT_ICON, W_RIGHT_ICON, W_BAR_ICON,
};
*/
#define PRN_RESET				"\x1b\x40"			// 2
#define PRN_SET_EMPH			"\x1b\x45"			// 2
#define PRN_CLR_EMPH			"\x1b\x46"			// 2
#define PRN_SET_ULINE			"\x1b\x2d\x1"		// 3
#define PRN_CLR_ULINE			"\x1b\x2d\x0"		// 3
#define PRN_SET_ITALIC			"\x1b\x34"			// 2
#define PRN_CLR_ITALIC			"\x1b\x35"			// 2
#define PRN_SET_DHLINE			"\x1b\x77\x1"		// 3
#define PRN_CLR_DHLINE			"\x1b\x77\x0"		// 3

#define PRN_LF_CR				"\x0a\x0d"			// 2
#define PRN_CR					"\x0d"				// 1
#define PRN_LF					"\x0a"				// 1
#define PRN_FF					"\x0c"				// 1
#define PRN_SP					"\x20"				// 1

#define PRN_CHAR_NORMAL 		"\x1b\x71\x0"		// 3
#define PRN_CHAR_OUTLIN 		"\x1b\x71\x1"		// 3
#define PRN_CHAR_SHADOW 		"\x1b\x71\x2"		// 3
#define PRN_CHAR_OUTSHA 		"\x1b\x71\x3"		// 3

#define W_LT					0xc9
#define W_RT					0xbb
#define W_LB					0xc8
#define W_RB					0xbc
#define W_TM					0xcb
#define W_BM					0xca
#define W_LM					0xcc
#define W_RM					0xb9
#define W_H 					0xcd
#define W_V 					0xba
#define W_C 					0xce
#endif

////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

#define DP_ACK_MARK 			0x80
			


enum{ ERR_WIN, WAR_WIN, MSG_WIN ,WR_WIN,NO_WIN,RE_WIN,ST_WIN};

enum
{
	NULL_CMD, BUSY, RESET, SYS_INFO, DISP_LED,
	SCRN_OFF, SCRN_ON, FLASH_COLOR,
	DISP_EDIT_WINDOW, DISP_WORK_WINDOW, DISP_TEST_WINDOW, DISP_STEP_WINDOW,
	DISP_MODY_WINDOW, DISP_PARA_WINDOW, DISP_HELP_WINDOW,
	DISP_STR, DISP_BIG_DIGIT, DISP_ICON, DISP_SAFE, DISP_MSG_WIN, CLR_MSG_WIN,
	SEND_PROG, DISP_PROG, HELP_UP, HELP_DOWN, UPDATE_SCROLL_BAR,
	ROLL_ON, ROLL_OFF, DISP_RUN_WIN, DISP_RUN_MSG, CLR_RUN_WIN,
	READ_FILE, WRITE_FILE, PRN_BUF, PRN_CHAR, PRN_STR,
	READ_ACK, WRITE_ACK, PRN_ACK,
	LOAD_DISK_FILE, SAVE_DISK_FILE
};
typedef struct
{
	short AxisNo;
	short Language;
	short GrayColor;
}SysInfo_t;


EXTERN SysInfo_t SysInfo
#ifdef GLOBAL
={2, 0, 0}
#endif
;
#define CURSOR_TIMER	0
#define LOGO_TIMER		1
#define RPM_TIMER		2




EXTERN short HelpCurLine
#ifdef GLOBAL
=0
#endif
;
EXTERN short HelpTotalLine
#ifdef GLOBAL
=0
#endif
;


EXTERN short RollOn
#ifdef GLOBAL
 = 0
#endif
;
