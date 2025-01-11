#if COMPILER == VC_COMPILER	//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV//X
                                                                //X
                                                                //X
//#include	<graph.h>                                           //X
#define putpixel(x,y,color) 				\
		_setcolor(color) ;					\
		_setpixel(x,y) ;
		                                                        //X
		                                                        //X
#elif COMPILER == BC_COMPILER	//******************************//X
//#include	<graphics.h>                                        //
#include	"c_bcgraph.h"                                    //
#endif	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//

////////////////////////////////////////////////////////////////////////////////

#define ICON_W						16
#define ICON_H						15

#define W_NORMAL					0x0000
#define W_TITLE 					0x0001
#define W_ICON						0x0002
#define W_MINIMUN					0x0004
#define W_CLOSE 					0x0008

/*
typedef struct
{
	short type;
	short main_col;
	short black_col, dark_col, middle_col, light_col;
}Frame_t;

typedef struct
{
	unsigned	style;
	short		lx, ly, rx, ry;
	short		title_fcol, title_bcol;
	char far	*title;
	short		icon;
	Frame_t 	frame;
}WinStyle_t;
*/


enum
{
	EDIT_ICON, WORK_ICON, TEST_ICON, STEP_ICON, MODY_ICON, PARA_ICON, HELP_ICON, W_MAX_ICON, W_MIN_ICON,
	W_CLOSE_ICON, W_STATUS_ICON, TOOL_ICON, POS_ICON, MAN_ICON, HAND_ICON, SCALE_ICON, LINK_ICON,
	ERROR_ICON, QUAN_ICON, TOUCH_ICON, CHOICE_ICON, UNCHOICE_ICON, SAFE_ICON, OK_ICON,
	MODE_ICON, FILE_ICON, FAST_ICON, AUTO_ICON, RPM_ICON, WARNING_ICON, W_UP_ICON, W_DOWN_ICON,
	W_LEFT_ICON, W_RIGHT_ICON, W_BAR_ICON,
};




