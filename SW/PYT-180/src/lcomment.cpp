#include "header.h"


void FillToEnd (Cptr buf,int endlen)
{
	WORD i, len;
	len=StrLen_S(buf) ;
	if(endlen > len ){
		i = endlen-len ;
		for(  ; i; i-- ){
			*pDispBuf_value++ = ' ';
		}
	}
	*pDispBuf_value = 0;
}
void KeyAirScrn(void)
{
	if(!AirScrn_ON){
		ChgCursorLoc(AIR_CURSOR) ;
		AirScrn_ON =true ;
		DispAirWindow() ;
	}
	else{
		ChgCursorLoc(PROG_CURSOR);
		AirScrn_ON=false ;
		DispEditBox_q();
		DispEditTitle_q();
	}
	DispPageProg_q(CurProgLine);
	SetCursor(1);
}
void DispAirWindow(void)
{
	DispAirBox_q() ;
	DispAirTitle_q() ;
}

void DispAirBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= AIRBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= EDIT_BOX_LX+AIR_BOX_OFF;
	ws.ly				= EDIT_BOX_LY;
	ws.rx				= EDIT_BOX_RX;
	ws.ry				= EDIT_BOX_RY;

	DrawWindow_q(&ws);
	DrawScrollVBar_q(VSCROLL_LX, VSCROLL_LY, VSCROLL_RX, VSCROLL_RY, 0);
}
void DispAirTitle_q (void)
{
	MakeAirTitleStr(false);
	DispStrLine_q(EDIT_BOX_LX2+AIR_BOX_OFF, EDIT_BOX_LY+2, RED_USR, GRAY_12, DispBuf);

#if DDRAW
	while(exe_proc_queue()) ;
#endif
}
void MakeAirTitleStr (bool force_eng)
{
	INI_DISP_BUF();
	if(MachineStatus.xgrid_deg !=0){
		Fill_pDispBuf(force_eng ,	"   X(¨¤«×) " ,
									"   X(Deg)  ") ;
	}
	else{
		Fill_pDispBuf("  ");
		Fill_pDispBuf(AxisName[force_eng?0:idx_language][AXIS_X]);
		Fill_pDispBuf("  ");
	}

	
	FILL_DISP_BUF(' ');
	Fill_pDispBuf("T  ");
	Fill_pDispBuf("  AIR   ");
	*pDispBuf_value = 0;
	FillToEnd(DispBuf,AIR_PAGE_CHARS);
	
}







void KeyLineComment(void)
{
	if(!LineComment_ON){
		ChgCursorLoc(LineComment_CURSOR) ;
		LineComment_ON =true ;
		DispLineCommentWindow() ;
	}
	else{
		ChgCursorLoc(PROG_CURSOR);
		LineComment_ON=false ;
		DispEditBox_q();
		DispEditTitle_q();
	}
	DispPageProg_q(CurProgLine);
	SetCursor(1);
}



void DispLineCommentWindow(void)
{
	DispLineCommentBox_q() ;
	DispLineCommentTitle_q() ;
}
void DispLineCommentBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= AIRBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= EDIT_BOX_LX+LineComment_BOX_OFF;
	ws.ly				= EDIT_BOX_LY;
	ws.rx				= EDIT_BOX_RX;
	ws.ry				= EDIT_BOX_RY;

	DrawWindow_q(&ws);
	DrawScrollVBar_q(VSCROLL_LX, VSCROLL_LY, VSCROLL_RX, VSCROLL_RY, 0);
}
void DispLineCommentTitle_q (void)
{
	MakeLineCommentTitleStr(false);
	DispStrLine_q(EDIT_BOX_LX2+LineComment_BOX_OFF, EDIT_BOX_LY+2, RED_USR, GRAY_12, DispBuf);

#if DDRAW
	while(exe_proc_queue()) ;
#endif
}

COLOR_T LineCommentColors[]={
	RED_USR,
	ORANGE_USR,
	YELLOW_USR,
	GREEN_USR ,
	BLUE_USR ,
	MAGENTA_USR,
	BROWN_USR ,
} ;
char *LineCommentTitle[]={
			"Comment" ,
 			"µù ¸Ñ", 
            "Comment" 
} ;
char *LineCommentName[][7]
={
	{ "0   ","1   ","2   ","3   ","4   " ,"5   ","6   " },
	{ "Â®Åé","°eR ","§é¨¤","°e½u","ÁY½u" ,"±²¨ú","¤ÁÂ_" },
	{ "0   ","1   ","2   ","3   ","4   " ,"5   ","6   " },
};

COLOR_T getLineCommentColor(char code)
{
	return(LineCommentColors[code-'0'] );
}
void MakeLineCommentTitleStr (bool force_eng)
{
	INI_DISP_BUF();
	Fill_pDispBuf("  ");
	Fill_pDispBuf(LineCommentTitle[force_eng?0:idx_language]);
	Fill_pDispBuf("  ");

	*pDispBuf_value = 0;
	FillToEnd(DispBuf,LineComment_PAGE_CHARS);	
}
void LineCommentMody (void)
{
	BYTE *b;
	CursorData_t *ptr= *(CurCursor.ptr) ;

	b = (BYTE *)(ptr)->var;
	DISP_CUR_PROGLINE(0, YProgoff, CurProgLine, 1);
//	DispLineCommentLine(ptr->y , &CurProgBufex , 1) ;	
}
bool chkLineComment_TYPE(char data)
{
	if((data >='0') && (data <='6'))return true ;
	return false ;
}

void DispLineCommentLine ( WORD y, ProgTypeex_t huge *progex, WORD mode)
{
	
	char code=progex->LineComment;
	bool dispflag=chkLineComment_TYPE(code) ;
	
	INI_DISP_BUF();
	if(dispflag){
		Fill_pDispBuf(	"  -") ;
		FILL_DISP_BUF(code);
		Fill_pDispBuf(	"--[") ;
		Fill_pDispBuf(LineCommentName[idx_language][code-'0']) ;
		FILL_DISP_BUF(']') ;
	}
	*pDispBuf_value = 0;
	FillToEnd(DispBuf,LineComment_PAGE_CHARS);
	
	
	int loc_x = EDIT_BOX_LX2+LineComment_BOX_OFF+4;
	int loc_y= EDIT_BOX_LY+2+(ASC_CHAR_H+1)+y*(ASC_CHAR_H+1);
	if( mode ){
		DispStrLine_q(loc_x, loc_y, CUR_PROG_FCOLOR, CUR_PROG_BCOLOR, DispBuf);
	}
	else{
		DispStrLine_q(loc_x, loc_y, AIRBOX_MAIN_FCOLOR, AIRBOX_MAIN_BCOLOR, DispBuf);
	}
	if(dispflag){
		rectangle_fill_q(getLineCommentColor(code),loc_x,loc_y,loc_x+ASC_CHAR_W*2,loc_y+ASC_CHAR_H-1) ;
	}
}
bool chk_HUANGex()
{
	FILE *fp ;
	fp=FOPEN(HUANGex_C,"rb") ;
	if(fp != NULL){
		FCLOSE(fp) ;
		return(true) ;
	}
	return(false) ;
}
void GHUANGex()
{
	FILE *fp_c, *fp_d ;
	fp_c= FOPEN(HUANGex_C,"wb") ;
	if(DDisk){
		fp_d=FOPEN(HUANGex_D,"wb") ;
	}
	ini_proglineex() ;
	for(long l=0 ; l < (long)MAX_PROG_LINE*MAX_FILE_NO ; l++){
		fwrite(&CurProgBufex ,1,sizeof(ProgTypeex_t) ,fp_c) ;
		if(DDisk){
			fwrite(&CurProgBufex ,1,sizeof(ProgTypeex_t) ,fp_d) ;
		}
	}
	FCLOSE(fp_c) ;
	if(DDisk){
		FCLOSE(fp_d) ;
	}
}
void ini_proglineex()
{
	memset((void *)&CurProgBufex,0,sizeof(ProgTypeex_t)) ;
	CurProgBufex.LineComment=' ' ;
}
short WriteDPProgLineex (WORD	file_no, WORD line,	WORD num, ProgTypeex_t huge *data)
{
	WORD  size;
	long  off;
	size = num * sizeof(ProgTypeex_t);
	off	 = (((long)file_no)*MAX_PROG_LINE+line)	* (long)(sizeof(ProgTypeex_t));

	short tt= WriteFileBuf (HUANGex_C, off, size,	(char *)data) ;
	if(DDisk){
		WriteFileBuf (HUANGex_D, off, size,	(char *)data) ;
	}
	return(tt) ;
}


short ReadDPProgLineex (WORD file_no,	WORD line, WORD	num, ProgTypeex_t	*data)
{
	WORD size;
	long off;

	size = num * sizeof(ProgTypeex_t);
	off	 = (((long)file_no)*MAX_PROG_LINE+line)	* (long)(sizeof(ProgTypeex_t));





	short tt=  ReadFileBuf(HUANGex_C,off,size,(char *)data) ;
	return(tt) ;
}
short ReadDPProgLineex (FILE *fp , WORD	num, ProgTypeex_t	*data)
{

	WORD size;
	
	size = num * sizeof(ProgTypeex_t);

	short tt=  fread((char *)data,1,size,fp) ;
	return(tt) ;
}
short ReadFullFileex (short file_no)
{
	WORD i,	ret;
	FILE *fp ;
	long off= (((long)file_no)*MAX_PROG_LINE)	* (long)(sizeof(ProgTypeex_t));
	ret	= 1;
	
	if((fp=FOPEN(HUANGex_C,"rb")) != NULL ){
		if( fseek(fp,off,SEEK_SET) ==0){
			for( i=0; i	< MAX_PROG_LINE/FILE_RW_MAX_NUM; i++ ){
				if(	!ReadDPProgLineex(fp,	FILE_RW_MAX_NUM, (ProgTypeex_t *)(ProgBufex+i*FILE_RW_MAX_NUM))	){
					FileRWErr =	1;
					ret	= 0;
					break;
				}
			}
			if(	ret	){




#if	 ( (MAX_PROG_LINE%FILE_RW_MAX_NUM) != 0	)
				i *= FILE_RW_MAX_NUM;
				if(	!ReadDPProgLineex(fp,	MAX_PROG_LINE%FILE_RW_MAX_NUM, (ProgType_t *)(ProgBufex+i)) ){
					FileRWErr =	1;
					ret	= 0;
				}
#endif




			}
		}
		else{
		    ret=0 ;
		}
		FCLOSE(fp) ;
	}
	else{
		ret=0 ;
	}
}


