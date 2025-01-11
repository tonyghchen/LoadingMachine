//#include <stdarg.h>
#include "c:\ncnc\uty\utyc_2.cpp"

uint32 x_Sprintf ;

void Sprintf(char *fmt,...)
{
	char buf[120] ;
	va_list marker;

   int x=5 ;
	va_start( marker,fmt);
	vsprintf(buf,fmt,marker) ;
	DispStrLine_q(x,y_Sprintf,AIRBOX_MAIN_FCOLOR, AIRBOX_MAIN_BCOLOR,buf) ;
	x_Sprintf=x+strlen(buf)*ASC_CHAR_W[idxFout] ;
    while(exe_proc_queue()) ;
    if((y_Sprintf+ASC_CHAR_H[idxFout]) > (SCREEN_MAXY-40)){
    		y_Sprintf=25 ;
    }
    else{
		y_Sprintf+= ASC_CHAR_H[idxFout] ;
	}
}

void Sprintf_next(char *fmt,...)
{
	char buf[120] ;
	va_list marker;

   int x=x_Sprintf ;
	va_start( marker,fmt);
	vsprintf(buf,fmt,marker) ;
	DispStrLine_q(x,y_Sprintf-ASC_CHAR_H[idxFout],AIRBOX_MAIN_FCOLOR, AIRBOX_MAIN_BCOLOR,buf) ;
	x_Sprintf=x+strlen(buf)*ASC_CHAR_W[idxFout] ;
    while(exe_proc_queue()) ;
}

