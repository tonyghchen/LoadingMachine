#include "header.h"
#include "DosMem_p.cpp"
#include "DispInport_1.cpp"
#include "cvt_1.cpp"
#include "utyb_1.cpp"
#include "utyc_1.cpp"
#include "scrn_on_off_1.cpp"
#include "MAIN_ExeMode.cpp"

//#include "PMfun.cpp"
//#include "disp_para.cpp"
//#include "uty\T_Stop.cpp"
//#include "utya_1.cpp"
//#include "ya_abs.cpp"
//#include "abspos.cpp"
//#include "pass.cpp"

int32 sdmdy_2016(uint8 axis,int32 d1)
{
// 	if(MachineStatus.bENCR1[axis]==0){
// 		MachineStatus.bENCR1[axis]=1000 ;
// 	}
// 	return(d1*MachineStatus.bENCR0[axis]/MachineStatus.bENCR1[axis]);			
}
/*

void SendFlashColor_q(BYTE idx, COLOR_T	col1, COLOR_T col2)
{
#if REAL_COLOR
	flash_cursor.fcol= col1 ;
	flash_cursor.bcol= col2 ;
#else	
	BYTE *dptr=  (BYTE *)farmalloc(3*sizeof(BYTE)+LEN_CHKSUM)	;
	unsigned char *tptr= dptr ;
	SAVE_VAL(BYTE,idx) ;
	SAVE_VAL(BYTE,col1) ;
	SAVE_VAL(BYTE,col2) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(FLASH_COLOR_proc,tptr) ;
#endif
}
extern struct ROLLDATA *RollData;
extern unsigned int cur_step ;
void InitRollData (void)
{
	unsigned char *ptr = (unsigned char *)RollData->palette ;
	unsigned int i ;
	unsigned char pal[16*3] ;
	for(i=0 ; i < 16*3 ; i++){
		pal[i]=*ptr++ ;
	}
	//修整調色盤r,g,b為6bit
	for(i=0 ; i < 16*3 ; i++){
		pal[i] >>= 2 ;
	}
	//改變VGA卡調色盤
	SetPalette(0x60,0x10 ,(char *)pal) ;

	memcpy(&default_rgb[0x60*3],pal,0x30) ;
	cur_step = 0 ;
}
void pro_chg_logo(unsigned char *pal , unsigned char val , unsigned char &r ,unsigned char &g , unsigned char &b)
{
	r=pal[val*3] ;
	g=pal[val*3+1] ;
	b=pal[val*3+2] ;
	if((r!= 0xff) && (g!=0xff) && (b !=0xff)){
		switch(chg_logo){
			case 0:
				break ;
			case 1:
				g=b=0 ;
				break ;
			case 2:
				r=b=0 ;
				break ;
			case 3:
				r=g=0 ;
				break ;
			case 4:
				r=0 ;
				break ;
			case 5:
				g=0 ;
				break ;
			case 6:
				b=0 ;
				break ;
		}
	}
}
void DispRollData1_proc (void *ptr)
{
	unsigned int off_pal=0x60 ;	//調色盤的偏移植
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , x );
	GET_VAL(short , y) ;
	GET_VAL(short , w) ;
	GET_VAL(short , h) ;
	GET_VAL(short , dir) ;
	
	
	
	
	GET_VAL(BYTE *,tptr) ;



	CHK_CHKSUM
	unsigned char *pal = (unsigned char *)RollData->palette ;
	unsigned int tw,th;
	int count ;
	for(th =0 ; th < h ;th++){
		for(tw=0 ; tw < w ;  ){
			COLOR_T color  ;
			if(LOGOCompress){
				if((*tptr& 0xc0) == 0xc0){
					count = (*tptr & 0x3f) ;
					tptr++ ;
#if REAL_COLOR
					unsigned char r,g,b ;				
					pro_chg_logo(pal,*tptr,r,g,b) ;
					color=RGB8_16(r,g,b) ;
#else
					color = *tptr+off_pal ;
#endif
					for( ; (count!=0) && (tw <w) ; count--){
						if(dir == 0){
							putpixel(x+tw,y+th,color) ;
						}
						else{
							putpixel(x+w-1-tw,y+th,color) ;
						}
						tw++ ;
					}
				}
				else{
#if REAL_COLOR	
					unsigned char r,g,b ;
					pro_chg_logo(pal,*tptr,r,g,b) ;
					color=RGB8_16(r,g,b) ;
#else
					color = *tptr+off_pal ;
#endif
					if(dir == 0){
						putpixel(x+tw,y+th,color) ;
					}
					else{
						putpixel(x+w-1-tw,y+th,color) ;
					}
					tw++ ;
				}
				tptr++ ;
			}
			else{  // real color
				unsigned char r,g,b ;
				r=*tptr++ ;
				g=*tptr++ ;
				b=*tptr++ ;
				color=RGB8_16(r,g,b) ;
				if(dir == 0){
					putpixel(x+tw,y+th,color) ;
				}
				else{
					putpixel(x+w-1-tw,y+th,color) ;
				}
				tw++ ;
			}
		}
	}
	farfree(ptr) ;
}
short PrintString (short x, short y, COLOR_T fcol, COLOR_T bcol, char *fmt,...)
{
	char buf[120] ;
	char *fontptr ;
	uint16 *idxptr ;
	char *ptr ;
	short ty ,tx;
	unsigned char c ;
	unsigned int i ;
	short len =0 ;
	va_list marker;
	
	va_start( marker,fmt);
	
	ptr=buf ;
	vsprintf(buf,fmt,marker) ;
	while((c= *ptr) != 0){
		if(c == 0x7e){
			if(*++ptr != 0){
				fcol = *ptr ;
			}
			if(*++ptr != 0){
				bcol= *ptr ;
			}
			ptr++ ;
		}
		else if(c >= 0x80){
			idxptr= (uint16 *)ChIndex ;
			for(i=0 ; i < ChTotalNo ; i++){
				if(*idxptr++ == *(uint16 *)ptr){
					break ;
				}
			}
			if(i < ChTotalNo){
				fontptr = ChStart + i*30 ;
				ty= y ;
				while((y+15) > ty){
					c= *fontptr++ ;
					for(tx=0 ; tx < 16 ; tx++){
						if((c & 0x80) !=0){
							putpixel(x+tx,ty,fcol) ;
						}
						else{
							if(bcol != 0){
								putpixel(x+tx,ty,bcol) ;
							}
						}
						if(tx != 7){
							c <<= 1 ;
						}
						else{
							c= *fontptr++ ;
						}
					}
					ty++ ;
				}
				x += 16  ;
				len += 2 ;
			}
			ptr+=2 ;
		}
		else{
			//英文字
			fontptr = AscStart +(c*15) ;
			ty = y ;
			while((y+15) > ty){
				c= *fontptr++ ;
				for(tx=0 ; tx < 8 ; tx++){
					if((c & 0x80) !=0){
						putpixel(x+tx,ty,fcol) ;
					}
					else{
						if(bcol != 0){
							putpixel(x+tx,ty,bcol) ;
						}
					}
					c <<= 1 ;
				}
				ty++ ;
			}
			x += 8 ;
			len++ ;
			ptr++ ;
		}
	}
	return(len) ;
}

short PrintStringLine (SCRN_XY x, SCRN_XY y, COLOR_T fcol, COLOR_T bcol, char *string)
{
	WORD  len  ;	
	len = strlen(string) ;
	
	bar256(x,y,x+len*ASC_CHAR_W-1,y+ASC_CHAR_H-1,bcol) ;
	PrintStringLine (x, y, fcol, string) ;
	return(len) ;
}
short PrintStringLine (SCRN_XY x, SCRN_XY y, COLOR_T fcol, char *string)
{
	char *fontptr ;
	uint16 *idxptr ;
	char *ptr ;
	short ty ,tx;
	unsigned char c ;
	unsigned int i ;
	unsigned int  len=0  ;

	ptr=string ;


	for( ;(c= *ptr) != 0;){
		if(c >= 0x80){
			idxptr= (uint16 *)ChIndex ;
			for(i=0 ; i < ChTotalNo ; i++){
				if(*idxptr++ == *(uint16 *)ptr){
					break ;
				}
			}
			if(i < ChTotalNo){
				fontptr = ChStart + i*30 ;
				for(ty= 0 ; ty < 15 ; ty++){
					c= *fontptr++ ;
					for(tx=0 ; tx < 16 ; tx++){
						if((c & 0x80) !=0){
							putpixel(x+tx,y+ty, fcol) ;
						}
						if(tx != 7){
							c <<= 1 ;
						}
						else{
							c= *fontptr++ ;
						}
					}
				}
				x+=16 ;
			}
			ptr+=2 ;
		}
		else{
			if(c != ' '){
				fontptr = AscStart +(c*15) ;
				for(ty = 0 ; 15 > ty; ty++){
					if((c= *fontptr ++) != 0){
						for(tx=0 ; tx < 8 ; tx++){
							if((c & 0x80) !=0){
								putpixel(x+tx,y+ty,fcol) ;
							}
							c<<= 1 ;
						}
					}
				}
			}
			x+=8 ;
			ptr++ ;
		}
	}
	return(len) ;
}
void DrawWindow (WinStyle_t *style)
{
	Frame_t *frame= &(style->frame) ;
	DrawButton(style->lx,style->ly,style->rx,style->ry,frame) ;
	DrawWindowTitle(style) ;
}
void DrawWindowTitle_q (WinStyle_t *style)
{
	Frame_t *frame= &(style->frame) ;
	if(frame->type == 0){
		if((style->style & 0xf) !=0){
			rectangle_fill_q(style->title_bcol , style->lx+4 , style->ly+4 , style->rx-4 , style->ly+23) ;
			short t1=0 ;
			if((style->style & 0x2) !=0){
				PutIcon( style->lx+6 , style->ly+6 , style->icon , 3) ;
				t1=18 ;
			}
			if((style->style &0x1) != 0){
				PrintStringLine_q( style->lx+t1+6 ,style->ly+6 , style->title_fcol ,style->title_bcol ,style->title) ;
			}
			t1=0 ;
			if((style->style & 0x8) !=0){
				PutIcon_q( style->rx-22 , style->ly+6 , 9 , 3);
				t1=18 ;
			}
			if((style->style & 0x4) !=0){
				PutIcon_q( style->rx-22-t1 , style->ly+6 , 7 ,3) ;
				t1+=18 ;
				PutIcon_q( style->rx-22-t1 , style->ly+6 ,8,3) ;
			}
		}
	}
}
void DrawWindowTitle (WinStyle_t *style)
{
	Frame_t *frame= &(style->frame) ;
	if(frame->type == 0){
		if((style->style & 0xf) !=0){
			rectangle_fill( style->title_bcol , style->lx+4 , style->ly+4 , style->rx-4 , style->ly+23 );
			short t1=0 ;
			if((style->style & 0x2) !=0){
				PutIcon( style->lx+6 , style->ly+6 , style->icon , 3) ;
				t1=18 ;
			}
			if((style->style &0x1) != 0){
				PrintStringLine( style->lx+t1+6 ,style->ly+6 , style->title_fcol ,style->title_bcol ,style->title) ;
			}
			t1=0 ;
			if((style->style & 0x8) !=0){
				PutIcon( style->rx-22 , style->ly+6 , 9 , 3);
				t1=18 ;
			}
			if((style->style & 0x4) !=0){
				PutIcon( style->rx-22-t1 , style->ly+6 , 7 ,3) ;
				t1+=18 ;
				PutIcon( style->rx-22-t1 , style->ly+6 ,8,3) ;
			}
		}
	}
}
void DrawTextButton (WinStyle_t *style)
{
	Frame_t *frame= &(style->frame) ;
	DrawButton(style->lx,style->ly,style->rx,style->ry,frame) ;
	if(frame->type <= 0){
		GrLineOption lop ;
		lop.lno_color=style->title_bcol ;
		lop.lno_width=NORM_WIDTH ;
		lop.lno_pattlen=2 ;
		lop.lno_dashpat=(unsigned char *)"\1\1" ;
		GrCustomBox(style->lx+3,style->ly+3,style->rx-3,style->ry-3,&lop) ;
	}
	else{
		for(short j= style->ly+3 ; j < style->ry-3 ; j++){
			for(short i=style->lx+3+(j%2) ; i <= style->rx-3; i+=2){
				putpixel(i,j,style->title_bcol) ;
			}
		}

	}
	short len = strlen(style->title) ;
	BYTE *dptr= (BYTE *)farmalloc(6*sizeof(short)+len+1+LEN_CHKSUM) ;
	BYTE *tptr=dptr ;
	SAVE_VAL(short, style->title_fcol) ;
	SAVE_VAL(short, style->lx) ;
	SAVE_VAL(short, style->rx);
	SAVE_VAL(short, style->ly) ;
	SAVE_VAL(short, style->style) ;
	SAVE_VAL(short, style->icon) ;
	SAVE_STRING(style->title,len) ;
	SAVE_CHKSUM
	if(frame->type <= 0){
		DrawTextButton1_proc(tptr) ;
	}
	else{
		FILL_PROC_QUEUE(DrawTextButton1_proc,tptr) ;
	}
}
char *StrERROR[]={
	"ERROR",
	"錯誤" ,
	"ERRORE",
} ;
char *StrWARNING[]={
	"WARNING" ,
	"警告"  ,
	"AVVISI" ,
} ;
char *StrMESSAGE[]={
	"MESSAGE",
	"訊息" ,
	"MESSAGGIO",
} ;
char *StrOK[]={
	" OK " ,
	"確定" ,
	" OK " ,
} ;
char *StrRE[]={
	" OK " ,
	"請重新開機" ,
	" OK " ,
} ;
char *StrST[]={
	" Copying... " ,
	"複製中..." ,
	" Copying ... " ,
} ;
char *StrWRITE[]={
	" WR " ,
	"記憶" ,
	" WR " ,
} ;

void DispMsgWin (short lx, short ly, BYTE type, char *str)
{
	char	*msg[10], ch;
	short	no, len, i;
	short	rx, ry, w, h;
	WinStyle_t ws;

	msg[0] = str;
	len = 14;
	no = i = 0;
	while( 1 )
	{
		ch = *str;
		if( ch=='\n' || ch==0 )
		{
			*str++ = 0;
			msg[++no] = str;
			if( i+4 > len ) { len = i + 4; }
			i = 0;
			if( ch == 0 )  break;
		}
		else if( ch == '~' ) { str += 3; }
		else if(ch &0x80){
			//中文字
			str+=2 ; i+=2 ;
		}
		else{ str++;  i++; }
	}

	w = len*ASC_CHAR_W;
	h = (3+no+3)*ASC_CHAR_H;

	if( lx < 0 )  lx = (SCRN_W-w)/2;
	if( ly < 0 )  ly = (SCRN_H-h)/2;
	rx = lx+w-1;
	ry = ly+h-1;

	PushImage(lx, ly, rx, ry);

	DefaultButtonStyle(&(ws.frame));
	ws.style		= W_TITLE+W_ICON+W_CLOSE;
	ws.lx			= lx;
	ws.ly			= ly;
	ws.rx			= rx;
	ws.ry			= ry;
	ws.title_fcol	= BRIGHTWHITE_USR;
	ws.title_bcol	= RED_USR;
	switch( type )
	{
	case ERR_WIN:
		ws.title = StrERROR[idx_language];
		ws.icon  = ERROR_ICON;
		break;
	case WAR_WIN:
		ws.title = StrWARNING[idx_language];
		ws.icon  = WARNING_ICON;
		break;
	case MSG_WIN:
		ws.title = StrMESSAGE[idx_language];
		ws.icon  = HELP_ICON;
		break;
	case WR_WIN:
		ws.title = StrWRITE[idx_language];
		ws.icon  = HELP_ICON;
		break;
	case NO_WIN:
		ws.title = StrMESSAGE[idx_language];
		ws.icon  = HELP_ICON;
		break;
	case RE_WIN:
		ws.title = StrMESSAGE[idx_language];
		ws.icon  = HELP_ICON;
		break;
	case ST_WIN:
		ws.title = StrMESSAGE[idx_language];
		ws.icon  = HELP_ICON;
	}
	DrawWindow(&ws);

	for( i=0; i < no; i++ )
	{
		PrintStringLine((lx+rx-(ColorStringLen(msg[i])*ASC_CHAR_W))/2, ly+(i+3)*ASC_CHAR_H, WIN_TEXT_FCOLOR, ws.frame.main_col, msg[i]);
	}

	ws.style		= W_TITLE+W_ICON;
	ws.title_fcol	= WIN_TEXT_FCOLOR;
	ws.title_bcol	= ws.frame.main_col;
	if(type==WR_WIN)ws.title		= StrWRITE[idx_language]; //視窗顯示修改
	else if(type==NO_WIN)
		ws.title="";
	else if(type==RE_WIN)
		ws.title =StrRE[idx_language];
	else if(type==ST_WIN)
		ws.title =StrST[idx_language];
	else
		ws.title		= StrOK[idx_language];
	if(type!=NO_WIN){
		ws.icon			= OK_ICON;
		ws.lx			= (lx+rx-(strlen(ws.title)+6)*ASC_CHAR_W)/2;
		ws.ly			= ly+(i+3+1)*ASC_CHAR_H;
		ws.rx			= ws.lx+(strlen(ws.title)+6)*ASC_CHAR_W;
		ws.ry			= ws.ly+ASC_CHAR_H+8;
		DrawTextButton(&ws);
	}
}
void DrawHLightBar (short lx, short ly, short rx, short ry, short percent)
{
	short t1 , t2 ;
	percent = percent%101 ;
	t1= (rx-lx)*percent/100 ;
	rectangle_fill(LIGHTGREEN_USR,lx,ly,t2=lx+t1,ry) ;
	rectangle_fill(LIGHTRED_USR,t2,ly,rx,ry) ;
}
void DrawScrollVBar_q (short lx, short ly, short rx, short ry, short percent)
{
	short t1 , t2 ;
	//先繪製scroll bar中間部分
	rectangle_fill_q(LIGHTGRAY_USR,lx,ly+15,rx,ry-15) ;
	PutIcon_q(lx,ly,0x1e,3) ;
	PutIcon_q(lx,ry-14,0x1f,3) ;
	t1= ry-ly-44 ;
	if(t1 > 0){
		percent = percent %101 ;
		t2= percent*t1/100 ;
		PutIcon_q(lx,ly+15+t2,0x22,3) ;
	}
}
void DrawScrollVBar (short lx, short ly, short rx, short ry, short percent)
{
	short t1 , t2 ;
	//先繪製scroll bar中間部分
	rectangle_fill(LIGHTGRAY_USR,lx,ly+15,rx,ry-15) ;
	PutIcon(lx,ly,0x1e,3) ;
	PutIcon(lx,ry-14,0x1f,3) ;
	t1= ry-ly-44 ;
	if(t1 > 0){
		percent = percent %101 ;
		t2= percent*t1/100 ;
		PutIcon(lx,ly+15+t2,0x22,3) ;
	}
}
void DrawScrollHBar (short lx, short ly, short rx, short ry, short percent)
{
	short t1 , t2 ;
	//先繪製scroll bar中間部分
	rectangle_fill(LIGHTGRAY_USR,lx+16,ly,rx-16,ry) ;
	PutIcon(lx,ly,0x20,3) ;
	PutIcon(rx-15,ly,0x21,3) ;
	t1= rx-lx-47;
	if(t1 > 0){
		percent = percent %101 ;
		t2= percent*t1/100 ;
		PutIcon(lx+16+t2,ly,0x22,3) ;
	}
}
void DefaultButtonStyle (Frame_t *frame)
{
	frame->type =0 ;
	frame->main_col=LIGHTGRAY_USR;
	frame->black_col=BLACK_USR ;
	frame->dark_col=GRAY_USR ;
	frame->middle_col= LIGHTGRAY_USR ;
	frame->light_col=BRIGHTWHITE_USR;
}
void DISP_STR_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD,lx) ;
	GET_VAL(WORD,ly) ;
	GET_VAL(COLOR_T ,fcol) ;
	GET_VAL(COLOR_T ,bcol) ;
	BYTE *str=dptr ;
	GET_STRING
	CHK_CHKSUM
	PrintStringLine(lx,  ly, fcol, bcol, (char *)str);
	farfree(ptr) ;
}
void DispStrLine_q (SCRN_XY lx, SCRN_XY ly, COLOR_T fcol, COLOR_T bcol,	Cptr str)
{
	
	//改變顏色由0xf fcol bcol  string...   0xf
	COLOR_T nfcol , nbcol ;
	WORD len;
	WORD nof=0 ;
//	len	= StrLen(str);
	bool  reverse_flag ;
	int	clen ;
	Cptr sstr=	str	;
	for(clen=0;	*str !=0 ;){
		//切割字串時,不可將中文字切割成兩半
		if(*str != CHG_PAL){
			if(*str	!= ' ')	clen++ ;
			if((*str & 0x80)){ //chinese word
				str+=2 ;
			}
			else{//english word
				str++ ;
			}
		}
		len	= (int)(str-sstr) ;
		if((clen >=	20)	|| ((*str == 0)&& (len != 0))|| (*str ==CHG_PAL)){
			if(*str == CHG_PAL){
				str++ ;
				nof++ ;
				if(nof%2){
					//取得新顏色
#if REAL_COLOR
					nfcol=*(str+1) ;
					nfcol <<= 8 ;
					nfcol += *str ;
					str+=2 ;
					nbcol=*(str+1) ;
					nbcol <<= 8 ;
					nbcol += *str ;
					str+=2 ;
#else					
					nfcol= *str++ ;
					nbcol= *str++ ;
#endif					
				}
				reverse_flag = true ;
			}
			else{
				reverse_flag = false ;
			}
			if(len !=0){
				BYTE *dptr=  (BYTE *)farmalloc(2*sizeof(WORD)+2*sizeof(COLOR_T)+len+1+LEN_CHKSUM) ;
				BYTE *tptr= dptr ;
				SAVE_VAL(WORD,lx) ;
				SAVE_VAL(WORD,ly) ;
				SAVE_VAL(COLOR_T ,(reverse_flag)&&((nof%2)==0)? nfcol:fcol) ;
				SAVE_VAL(COLOR_T ,(reverse_flag)&&((nof%2)==0)? nbcol:bcol) ;
				SAVE_STRING(sstr,len) ;
				SAVE_CHKSUM
				FILL_PROC_QUEUE(DISP_STR_proc,tptr)	;
				lx += (len*ASC_CHAR_W) ;
				clen=0 ;
				sstr= str ;
			}
			else{
				clen=0 ;
				sstr= str ;
			}
		}
	}
}
void Clr_Set3701_ARM()
{
	for(uint8 axis=0 ; axis < MAX_AXIS ; axis++){
		Set3701_ARM.speed[axis]= 0 ;
		Set3701_ARM.dist[axis]= 0 ;
		Set3701_ARM.dir[axis]= 0 ;
	}
}
*/ 
