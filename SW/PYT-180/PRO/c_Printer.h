#define LPT_NO			0

#define PRN_RESET		"\x1b\x40"			// 2
#define PRN_PAGE_LEN	"\x1b\x43\x7f"		// 3
#define PRN_SET_EMPH	"\x1b\x45"			// 2
#define PRN_CLR_EMPH	"\x1b\x46"			// 2
#define PRN_SET_ULINE	"\x1b\x2d\x1"		// 3
#define PRN_CLR_ULINE	"\x1b\x2d\x0"		// 3
#define PRN_SET_ITALIC	"\x1b\x34"			// 2
#define PRN_CLR_ITALIC	"\x1b\x35"			// 2
#define PRN_SET_DHLINE	"\x1b\x77\x1"		// 3
#define PRN_CLR_DHLINE	"\x1b\x77\x0"		// 3

#define PRN_LF_CR		"\x0a\x0d"			// 2
#define PRN_CR			"\x0d"				// 1
#define PRN_LF			"\x0a"				// 1
#define PRN_FF			"\x0c"				// 1
#define PRN_SP			"\x20"				// 1

#define PRN_CHAR_SET	"\x1b\x52\x0"		// 3

#define PRN_CHAR_NORMAL "\x1b\x71\x0"		// 3
#define PRN_CHAR_OUTLIN "\x1b\x71\x1"		// 3
#define PRN_CHAR_SHADOW "\x1b\x71\x2"		// 3
#define PRN_CHAR_OUTSHA "\x1b\x71\x3"		// 3

#define PRN_COLOR_BLACK "\x1b\x19\x0"		// 3
#define PRN_COLOR_MAGE	"\x1b\x19\x1"		// 3
#define PRN_COLOR_CYAN	"\x1b\x19\x2"		// 3
#define PRN_COLOR_BLUE	"\x1b\x19\x3"		// 3
#define PRN_COLOR_YELL	"\x1b\x19\x4"		// 3
#define PRN_COLOR_RED	"\x1b\x19\x5"		// 3
#define PRN_COLOR_GREEN "\x1b\x19\x6"		// 3

#define W_LT			0xc9
#define W_RT			0xbb
#define W_LB			0xc8
#define W_RB			0xbc
#define W_TM			0xcb
#define W_BM			0xca
#define W_LM			0xcc
#define W_RM			0xb9
#define W_H 			0xcd
#define W_V 			0xba
#define W_C 			0xce
