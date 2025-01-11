#if COMPILER == DJ_COMPILER
#define huge 
#define far 
#define interrupt   
#define farfree    free
#define farmalloc  malloc
#define DOS_ADDR    unsigned
#define putpixel    GrPlot
#define getpixel    GrPixel
#else
#define DOS_ADDR    BYTE far *
#endif

#ifdef REAL_COLOR
#define COLOR_T     WORD
#else
#define COLOR_T     BYTE
#endif

#define RGB8_16(r,g,b)     (((r>> 3)<< 11)+((g>>2)<< 5)+(b>>3))
#define RGB6_16(r,g,b)     (((r>> 1)<< 11)+((g)<< 5)+(b>>1))
#define R16_8(color16)	   ((color16 >> 11)<< 3) 
#define G16_8(color16)     (((color16 >> 5)&0x3f)<< 2)
#define B16_8(color16)     (((color16 )&0x1f)<< 3)
#ifdef REAL_COLOR

#define ORANGE_USR			RGB8_16(0xff,0x35,0x2)
#define SKYBLUE_USR		    RGB8_16(0x77,0xc4,0xe7)

#define NULL_COLOR				RGB6_16(0x00,0x00,0x00) 
#define BLUE_USR				RGB6_16(0x00,0x00,0x2A)
#define GREEN_USR				RGB6_16(0x00,0x2A,0x00)
#define CYAN_USR				RGB6_16(0x00,0x2A,0x2A)
#define RED_USR 				RGB6_16(0x2A,0x00,0x00)
#define MAGENTA_USR 			RGB6_16(0x2A,0x00,0x2A)
#define BROWN_USR				RGB6_16(0x2A,0x15,0x00)
#define LIGHTGRAY_USR			RGB6_16(0x31,0x31,0x31)
#define GRAY_USR				RGB6_16(0x26,0x26,0x26)
#define LIGHTBLUE_USR			RGB6_16(0x15,0x15,0x3F)
#define LIGHTGREEN_USR			RGB6_16(0x15,0x3F,0x15)
#define LIGHTCYAN_USR			RGB6_16(0x15,0x3F,0x3F)
#define LIGHTRED_USR			RGB6_16(0x3F,0x15,0x15)
#define LIGHTMAGENTA_USR		RGB6_16(0x3F,0x15,0x3F)
#define YELLOW_USR				RGB6_16(0x3F,0x3F,0x15)
#define BRIGHTWHITE_USR 		RGB6_16(0x3F,0x3F,0x3F)

#define BLACK_USR				RGB6_16(0x02,0x01,0x02)
#define GRAY_1					RGB6_16(0x05,0x05,0x05)
#define GRAY_2					RGB6_16(0x08,0x08,0x08)
#define GRAY_3					RGB6_16(0x0B,0x0B,0x0B)
#define GRAY_4_USR				RGB6_16(0x0E,0x0E,0x0E)
#define GRAY_5					RGB6_16(0x11,0x11,0x11)
#define GRAY_6					RGB6_16(0x14,0x14,0x14)
#define GRAY_7_USR				RGB6_16(0x18,0x18,0x18)
#define GRAY_8					RGB6_16(0x1C,0x1C,0x1C)
#define GRAY_9					RGB6_16(0x20,0x20,0x20)
#define GRAY_10 				RGB6_16(0x24,0x24,0x24)
#define GRAY_11 				RGB6_16(0x28,0x28,0x28)
#define GRAY_12 				RGB6_16(0x2D,0x2D,0x2D)
#define GRAY_13 				RGB6_16(0x32,0x32,0x32)
#define GRAY_14 				RGB6_16(0x38,0x38,0x38)
#define GRAY_15 				RGB6_16(0x3F,0x3F,0x3F)

#define FLASH_COLOR1_1			RGB6_16(0x3F,0x3F,0x15)
#define FLASH_COLOR1_2			RGB6_16(0x00,0x2A,0x2A)
#define FLASH_COLOR2_1			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR2_2			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR3_1			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR3_2			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR4_1			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR4_2			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR5_1			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR5_2			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR6_1			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR6_2			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR7_1			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR7_2			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR8_1			RGB6_16(0x00,0x00,0x00)
#define FLASH_COLOR8_2			RGB6_16(0x00,0x00,0x00)
#define SEQ1_USR				GRAY_4_USR
#define SEQ2_USR				GRAY_7_USR
#define NULL_BCLR_USR			RGB6_16(0x3f,0x3f,0x30)
#else
#define NULL_COLOR				0 
#define BLUE_USR				1
#define GREEN_USR				2
#define CYAN_USR				3
#define RED_USR 				4
#define MAGENTA_USR 			5
#define BROWN_USR				6
#define LIGHTGRAY_USR			7
#define GRAY_USR				8
#define LIGHTBLUE_USR			9
#define LIGHTGREEN_USR			10
#define LIGHTCYAN_USR			11
#define LIGHTRED_USR			12
#define LIGHTMAGENTA_USR		13
#define YELLOW_USR				14
#define BRIGHTWHITE_USR 		15

#define BLACK_USR				16
#define GRAY_1					17
#define GRAY_2					18
#define GRAY_3					19
#define GRAY_4					20
#define GRAY_5					21
#define GRAY_6					22
#define GRAY_7					23
#define GRAY_8					24
#define GRAY_9					25
#define GRAY_10 				26
#define GRAY_11 				27
#define GRAY_12 				28
#define GRAY_13 				29
#define GRAY_14 				30
#define GRAY_15 				31

#define FLASH_COLOR1_1			32
#define FLASH_COLOR1_2			33
#define FLASH_COLOR2_1			34
#define FLASH_COLOR2_2			35
#define FLASH_COLOR3_1			36
#define FLASH_COLOR3_2			37
#define FLASH_COLOR4_1			38
#define FLASH_COLOR4_2			39
#define FLASH_COLOR5_1			40
#define FLASH_COLOR5_2			41
#define FLASH_COLOR6_1			42
#define FLASH_COLOR6_2			43
#define FLASH_COLOR7_1			44
#define FLASH_COLOR7_2			45
#define FLASH_COLOR8_1			46
#define FLASH_COLOR8_2			47
#endif
enum{ PLUS_SIGN, MINUS_SIGN };
#define isPLUS_SIGN(sign)   ((sign&0x7f)== PLUS_SIGN)
#define isMINUS_SIGN(sign)   (!isPLUS_SIGN(sign))
#define ChgSign(sign)       sign=(isPLUS_SIGN(sign)? ((sign&0xfe)|MINUS_SIGN):((sign&0xfe)|PLUS_SIGN))
