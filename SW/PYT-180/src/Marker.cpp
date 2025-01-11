#include "header.h"
#include  <process.h>
#include <ctype.h>
//require "Fill_pDispBuf()"
static char *MARKER_TITLE[]={
	"Comment" ,
 	"註 解", 
    "Comment" 
};
//require "PrintStringLine_fmt(lx+2,ly+2,para_title_fcolor,para_title_bcolor,STRING_NAME[idx_language][i])"
static char *MARKER_TITLE_TEST[][1]={
	{"COMMENT "},
	{"  註解  "},
	{"COMMENTO"},
};
	
//keymarker-test
void Key_Marker(void){
	if(!MarkerScrn_ON){
		ChgCursorLoc(MARKER_CURSOR) ;
		MarkerScrn_ON =true ;
		DispMarkerWindow() ;
	}
	else{
		ChgCursorLoc(PROG_CURSOR);
		MarkerScrn_ON=false ;
		DispEditBox_q();
		DispEditTitle_q();
	}
	DispPageProg_q(CurProgLine);
	SetCursor(1);
}

void DispMarkerBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= MARKERBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= EDIT_BOX_LX+MARKER_BOX_OFF;
	ws.ly				= EDIT_BOX_LY;
	ws.rx				= EDIT_BOX_RX;
	ws.ry				= EDIT_BOX_RY;

	DrawWindow_q(&ws);
	DrawScrollVBar_q(VSCROLL_LX, VSCROLL_LY, VSCROLL_RX, VSCROLL_RY, 0);
}



void MakeMarkerTitleStr(bool force_eng){
	INI_DISP_BUF();	
	Fill_pDispBuf("  ");
	Fill_pDispBuf(MARKER_TITLE[force_eng?0:idx_language]);
	Fill_pDispBuf("  ");
	//PrintStringLine_fmt(20+2, 20+2, PARA_TITLE_FCOLOR, PARA_TITLE_BCOLOR, MARKER_TITLE_TEST[idx_language][1]);
	*pDispBuf_value = 0;
	FillToEndLen (DispBuf,MARKER_PAGE_CHARS);
}

void DispMarkerTitle_q(void){
	MakeMarkerTitleStr(false);
	DispStrLine_q(EDIT_BOX_LX2+MARKER_BOX_OFF, EDIT_BOX_LY+2, RED_USR, GRAY_12, DispBuf);
}


void DispMarkerWindow(void){
	DispMarkerBox_q() ;
	DispMarkerTitle_q() ;
}

/*
typedef struct
{
	BYTE MarkerColor;
	BYTE Sparement[19];
}ProgTypeExlarge_t;

*/

static char *MARKER_COMMENT[][7]={
	{ "0   ","1   ","2   ","3   ","4   " ,"5   ","6   " },
	{ "簧體","送R ","折角","送線","縮線" ,"捲取","切斷" },
	{ "0   ","1   ","2   ","3   ","4   " ,"5   ","6   " },
};

COLOR_T Marker_CommentColors[]={
	RED_USR,
	ORANGE_USR,
	YELLOW_USR,
	GREEN_USR ,
	BLUE_USR ,
	MAGENTA_USR,
	BROWN_USR ,
} ;

COLOR_T MarkerCursorLineColor(char code){
	return Marker_CommentColors[code-'0'];
}

bool ChkMarkerNum(char data)
{
	if((data >='0') && (data <='6'))return true ;
	return false ;
};

void DispMarkerLine (WORD y, ProgTypeExlarge_t huge* progex, WORD mode)
{
	char code=progex->MarkerColor;
	bool ShowColorImmediately=ChkMarkerNum(code);
	INI_DISP_BUF();	
	
	if(ShowColorImmediately){
	pDispBuf=SetColorS(BLACK_USR,MarkerCursorLineColor(code),pDispBuf) ;
	Fill_pDispBuf("  ");
	pDispBuf=SetColorE(pDispBuf) ;
	Fill_pDispBuf("-");
	FILL_DISP_BUF(code);
	Fill_pDispBuf("--");
	Fill_pDispBuf("[");
	Fill_pDispBuf(MARKER_COMMENT[idx_language][code-'0']) ;
	Fill_pDispBuf("]");
	//pDispBuf=SetColorE(pDispBuf) ;
	}
	
	*pDispBuf_value = 0;
	FillToEndLen (DispBuf,MARKER_PAGE_CHARS);
	int loc_x = EDIT_BOX_LX2+MARKER_BOX_OFF+4;
	int loc_y= EDIT_BOX_LY+2+(ASC_CHAR_H+1)+y*(ASC_CHAR_H+1);
	if( mode ){
		DispStrLine_q(loc_x, loc_y, CUR_PROG_FCOLOR, CUR_PROG_BCOLOR, DispBuf);
	} 
	else{			
		DispStrLine_q(loc_x, loc_y, MARKERBOX_MAIN_FCOLOR, MARKERBOX_MAIN_BCOLOR, DispBuf);
	}
}

void MakeMarkerLine (ProgTypeExlarge_t huge* progex)
{
	INI_DISP_BUF();	
	*pDispBuf_value = 0;
	FillToEnd(DispBuf);
}

void MarkerMody(void){

	DISP_CUR_PROGLINE(0, YProgoff, CurProgLine, 1);
}

void IfAxis5Colored(int endlen)
{
	uint16 len;
	uint16 nof =0 ;
	Cptr  str=DispBuf ;
	for( len=0; len!=endlen;  ){
		if(*str == CHG_PAL){
			nof++ ;
			if(nof%2){
#ifdef REAL_COLOR
				str+=5 ;
#else				
				str+=3 ;
#endif				
			}
			else{
				str++ ;
			}
		}
		else{
			str++ ;
			len++ ;
		}
	}
	if((nof%2) ==1){
		*str++=CHG_PAL ;
	}
	*str=0 ;
}

//filewrite_Exlarge
short WriteDPProgLineEx (WORD	file_no, WORD line,	WORD num, ProgTypeExlarge_t huge *data)
{
	//WORD	ret;
	//WORD	i, size;


	WORD  size;
	long  off;
	size = num * sizeof(ProgTypeExlarge_t);
	off	 = (((long)file_no)*MAX_PROG_LINE+line)	* (long)(sizeof(ProgTypeExlarge_t));
	//Adjust_ProgBuf(data,num) ;

	short tt= WriteFileBuf (HUANG01EX_C, off, size,	(char *)data) ;
		if(DDisk){
			WriteFileBuf (HUANG01EX_D, off, size,	(char *)data) ;
		}
	//Adjust_ProgBuf(data,num) ;
	return(tt) ;
}


short ReadDPProgLineEx (FILE *fp , WORD	num, ProgTypeExlarge_t	*data){
	//num ==100
	WORD size;
	
	size = num * sizeof(ProgTypeExlarge_t);
	short tt=  fread((char *)data,1,size,fp) ;
	return(tt) ;
}

bool chk_HUANGex()
{
	FILE *fp ;
	fp=FOPEN(HUANG01EX_C,"rb") ;
	if(fp != NULL){
		FCLOSE(fp) ;
		return(true) ;
	}
	return(false) ;
}

void GHUANGex()
{
	//first create file
	FILE *fp_c, *fp_d ;
	fp_c= FOPEN(HUANG01EX_C,"wb") ;
	if(DDisk){
		fp_d=FOPEN(HUANG01EX_D,"wb") ;
	}
	ini_proglineex() ;
	for(long l=0 ; l < (long)MAX_PROG_LINE*MAX_FILE_NO ; l++){
		fwrite(&CurProgBufExlarge ,1,sizeof(ProgTypeExlarge_t) ,fp_c) ;
		if(DDisk){
			fwrite(&CurProgBufExlarge ,1,sizeof(ProgTypeExlarge_t) ,fp_d) ;
		}
	}
	FCLOSE(fp_c) ;
	if(DDisk){
		FCLOSE(fp_d) ;
	}
}

void ini_proglineex()
{
	//把零放進位址&CurProgBufExlarge裡面,長度是sizeof(ProgTypeExlarge_t)
	memset((void *)&CurProgBufExlarge,0,sizeof(ProgTypeExlarge_t)) ;
	CurProgBufExlarge.MarkerColor=' ' ;
}



