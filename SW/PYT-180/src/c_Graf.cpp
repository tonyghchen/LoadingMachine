#include "header.h"
#include "c_icons.h"
//#include <malloc.h> 	// _fmalloc,_ffree
#include "c_svga8.h"
void digitdot_proc(void *ptr);
#define IDX_FLASH_RGB		0x20


char RollData_img[4+80*80] ;
#define MAX_IMAGESTACK		10
/*
struct IMAGESTACK{
	short lx ;
	short ly ;
	short rx ;
	short ry ;
#if COMPILER == DJ_COMPILER	
	GrContext *buf ;
#else	
	char far *buf ;
#endif
} ;
*/
struct IMAGESTACK imagestack[MAX_IMAGESTACK] ;
int no_image ;
unsigned char fillmask[]={
	0x55,0xAA,0x55,0xAA,0x55,0xAA,0x55,0xAA,
	0xCC,0xCC,0x33,0x33,0xCC,0xCC,0x33,0x33,
} ;
//extern bool ScrnState;
void GetMsgWinXY(short &lx , short &ly ,short &rx , short &ry)
{
	if(no_image >0){
		lx=imagestack[no_image-1].lx ;
		ly=imagestack[no_image-1].ly ;
		rx=imagestack[no_image-1].rx ;
		ry=imagestack[no_image-1].ry ;
	}
	else{
		lx=ly=rx=ry=10 ;
	}
}


void GetPalette(char huge *PalBuf)
{
#if COMPILER == BC_COMPILER
	struct REGPACK reg;

	reg.r_ax = 0x1017;
	reg.r_bx = 0;
	reg.r_cx = 256;
	reg.r_es = FP_SEG(PalBuf);
	reg.r_dx = FP_OFF(PalBuf);
	intr(0x10,&reg);
#endif
}
void GetPalette(unsigned int start , unsigned int len , char huge *buf)
{
	unsigned int i ;
	for(i=0 ; i < len ; i++){
		while((inp(0x3da)&0x1)!=0) ;
		while((inp(0x3da)&0x1)==0) ;
		outp(0x3c6,0xff) ;
		outp(0x3c7,start+i) ;
		*buf++= inp(0x3c9) ;	//r
		*buf++= inp(0x3c9) ;	//g
		*buf++= inp(0x3c9) ;	//b
	}

}
void SetPalette( char huge *PalBuf)
{
#if COMPILER == BC_COMPILER	
	struct REGPACK reg;

	reg.r_ax = 0x1012;
	reg.r_bx = 0;
	reg.r_cx = 256;
	reg.r_es = FP_SEG(PalBuf);
	reg.r_dx = FP_OFF(PalBuf);
	intr(0x10,&reg);
#endif
}
void SetPalette(unsigned int start , unsigned int len , char *buf)
{




	unsigned int i ;
	for(i=0 ; i < len ; i++){
#if COMPILER != DJ_COMPILER		
		while((inp(0x3da)&0x1)!=0) ;
		while((inp(0x3da)&0x1)==0) ;
		outp(0x3c6,0xff) ;
		outp(0x3c8,start+i) ;
		outp(0x3c9,*buf++) ;  //r
		outp(0x3c9,*buf++) ;  //g
		outp(0x3c9,*buf++) ;  //b
#else
	#if REAL_COLOR
	#else
		GrSetColor(start+i,buf[i*3+0]<<2,buf[i*3+1]<<2,buf[i*3+2]<<2) ;
	#endif
#endif
	}






}
bool SetPalette(unsigned int start , unsigned int len , char huge *buf,unsigned long timeout)
{
	unsigned int i ;
	for(i=0 ; i < len ; i++){
		unsigned long t1 ;
		t1=0 ;
		while((inp(0x3da)&0x1)!=0){
			t1++ ;
			if(t1== timeout) return(0) ;
		}
		while((inp(0x3da)&0x1)==0){
			t1++ ;
			if(t1 == timeout)return(0) ;
		}
		outp(0x3c6,0xff) ;
		outp(0x3c8,start+i) ;
		outp(0x3c9,*buf++) ;  //r
		outp(0x3c9,*buf++) ;  //g
		outp(0x3c9,*buf++) ;  //b
	}
	return(1) ;

}

char far * MakeFarPointer (char far *p)
{
#if COMPILER == DJ_COMPILER
	return(p) ;
#else	
	//	 將far pointer的offset及segment修改成
	//
	//		new_segment = segment+(offset/16)
	//		new_offset = offset%16
	//
	unsigned short *ptr_p  , *ptr_newp;
	char far *newp ;
	ptr_p = (unsigned short *)&p ;
	ptr_newp=(unsigned short *)&newp ;
	*ptr_newp= *ptr_p%16 ;
	*(ptr_newp+1) = *(ptr_p+1)+(*ptr_p/16) ;
	return(newp) ;
#endif	
}
#define TIME_OUT_FLASH    1000

void Flash (short idx)
{
#if REAL_COLOR
	//	if(!(MachineStatus.op_mode &(TEST_MODE+HELP_MODE))&& ScrnState){
	if(!(MachineStatus.op_mode &(TEST_MODE+HELP_MODE))){
		if(flash_cursor.state){
			flash_cursor.state=false;
			PrintStringLine(flash_cursor.x,flash_cursor.y,flash_cursor.bcol,flash_cursor.fcol,(char *)flash_cursor.str) ;
		}
		else{
			flash_cursor.state=true;
			PrintStringLine(flash_cursor.x,flash_cursor.y,flash_cursor.fcol,flash_cursor.bcol,(char *)flash_cursor.str) ;
		}
	}	
#else	
	char rgb[9] ;
	int flash_start = IDX_FLASH_RGB+idx*2 ;
	GetPalette(flash_start,2,&rgb[3]) ;
	memcpy(&rgb[0],&rgb[6],3) ;
	SetPalette(flash_start,2,&rgb[0]) ;
#endif
}
void SetFlash (short idx, COLOR_T col1, COLOR_T col2)
{
	char rgb[3] ;
	int flash_start = IDX_FLASH_RGB+idx*2 ;




	memcpy(rgb,&default_rgb[col1*3],3) ;




	if(!SetPalette(flash_start,1,rgb,TIME_OUT_FLASH)){
		//重來1次
		BYTE *dptr= (BYTE *)farmalloc(1*sizeof(BYTE)+2*sizeof(COLOR_T)+LEN_CHKSUM) ;
		BYTE *tptr=dptr ;
		SAVE_VAL(BYTE , idx) ;
		SAVE_VAL(COLOR_T , col1) ;
		SAVE_VAL(COLOR_T , col2) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(FLASH_COLOR_proc,tptr) ;
		return ;
	}
	memcpy(&default_rgb[flash_start*3],rgb,3) ;




	memcpy(rgb,&default_rgb[col2*3],3) ;





	if(!SetPalette(flash_start+1,1,rgb,TIME_OUT_FLASH)){
		//重來1次
		BYTE *dptr= (BYTE *)farmalloc(1*sizeof(BYTE)+2*sizeof(COLOR_T)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(BYTE, idx) ;
		SAVE_VAL(COLOR_T, col1) ;
		SAVE_VAL(COLOR_T, col2) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(FLASH_COLOR_proc,tptr) ;
		return ;
	}
	memcpy(&default_rgb[(flash_start+1)*3],rgb,3) ;
}

short SetVideoMode (void)
{
	// return ==0: failure
	//		  !=0: ok
	short status ;
	Init_Graphic();
	status = 1 ;




	return(status) ;
}
void InitImageStack (void)
{
	no_image =0 ;
}
void RInitImage (void)
{
	while(no_image){
		no_image-- ;
		GrDestroyContext(imagestack[no_image].buf) ;
	}
}

short PopImage (short lx, short ly)
{
	if(no_image !=0){
		no_image-- ;
#if SAVEIMAGE		
	#if COMPILER==DJ_COMPILER
		if(lx <0){
			lx = imagestack[no_image].lx ;
		}
		if(ly < 0){
			ly = imagestack[no_image].ly ;
		}
		GrContext *gc1= imagestack[no_image].buf ;
   		GrBitBlt(NULL,lx,ly,gc1,0,0,gc1->gc_xmax,gc1->gc_ymax,GrWRITE) ;
   		GrDestroyContext(gc1) ;
	#else   			
		if(lx <0){
			lx = imagestack[no_image].lx ;
		}
		if(ly < 0){
			ly = imagestack[no_image].ly ;
		}
		_putimage(lx,ly,imagestack[no_image].buf,_GPSET) ;
		farfree(imagestack[no_image].buf) ;
	#endif
#else
		RedrawImage() ;
#endif
		return(0) ;
	}
	return(1) ;
}
void DrawCasingLine (short x1, short y1, short x2, short y2, Frame_t *frame)
{
	x1=x1 ;
	y1=y1 ;
	x2=x2 ;
	y2=y2 ;
	frame=frame ;
}
void DrawCasing_q (short x1, short y1, short x2, short y2, Frame_t *frame)
{
	short col1 , col2 ;
	if(frame->type <=0){
		col1 = frame->black_col ;
		col2 = frame->light_col ;
	}
	else{
		col2 = frame->black_col ;
		col1 = frame->light_col ;
	}
	rectangle_border_q(col1,x1,y1,x2-1,y2-1) ;

	rectangle_border_q(col2,x1+1,y1+1,x2,y2) ;
	if(frame->type <0){
		rectangle_fill_q(frame->main_col,x1+2,y1+2,x2-2,y2-2) ;
	}
}
void DrawCasing (short x1, short y1, short x2, short y2, Frame_t *frame)
{
	short col1 , col2 ;
	if(frame->type <=0){
		col1 = frame->black_col ;
		col2 = frame->light_col ;
	}
	else{
		col2 = frame->black_col ;
		col1 = frame->light_col ;
	}
	rectangle_border(col1,x1,y1,x2-1,y2-1) ;

	rectangle_border(col2,x1+1,y1+1,x2,y2) ;
	if(frame->type <0){
		rectangle_fill(frame->main_col,x1+2,y1+2,x2-2,y2-2) ;
	}
}


void DrawButton (short x1, short y1, short x2, short y2, Frame_t *frame)
{
	short col1 , col2 ,col3 , col4 ;
	col1 = col4= frame->dark_col ;
	if(frame->type <=0){
		col2 = frame->black_col ;
		col3 = frame->light_col ;
	}
	else{
		col2  = frame->light_col ;
		col3  = frame->black_col ;
	}
#if COMPILER == DJ_COMPILER
	rectangle_fill(frame->main_col ,x1,y1,x2,y2);

	GrLine(x1,y1 ,x2-1,y1,col1) ;
	GrLine(x1,y1+1,x1,y2-1,col1) ;
	
	GrLine(x2,y1,x2,y2,col2) ;
	GrLine(x1,y2,x2-1,y2,col2) ;
	
	GrLine(x1+1,y1+1,x2-2,y1+1,col3) ;
	GrLine(x1+1,y1+2,x1+1,y2-2,col3) ;

	GrLine(x2-1,y1+1,x2-1,y2-1,col4) ;
	GrLine(x1+1,y2-1,x2-2,y2-1,col4) ;
#endif


#if COMPILER == BC_COMPILER
	rectangle_fill(frame->main_col ,x1,y1,x2,y2);

	_setcolor(col1) ;
	_moveto(x1,y1) ;
	_lineto(x2-1,y1) ;
	_moveto(x1,y1+1) ;
	_lineto(x1,y2-1) ;
	
	_setcolor(col2) ;
	_moveto(x2,y1) ;
	_lineto(x2,y2) ;
	_moveto(x1,y2) ;
	_lineto(x2-1,y2) ;
	
	_setcolor(col3) ;
	_moveto(x1+1,y1+1) ;
	_lineto(x2-2,y1+1) ;
	_moveto(x1+1,y1+2) ;
	_lineto(x1+1,y2-2) ;

	_setcolor(col4) ;
	_moveto(x2-1,y1+1) ;
	_lineto(x2-1,y2-1) ;
	_moveto(x1+1,y2-1) ;
	_lineto(x2-2,y2-1) ;

#endif

}
void DrawButton_col1(short x1,short y1 , short x2,short y2,short col1)
{
#if COMPILER == DJ_COMPILER
	GrLine(x1,y1,x2-1,y1,col1) ;
	GrLine(x1,y1+1,x1,y2-1,col1) ;
#else
	_setcolor(col1) ;
	_moveto(x1,y1) ;
	_lineto(x2-1,y1) ;
	_moveto(x1,y1+1) ;
	_lineto(x1,y2-1) ;
#endif
}
void DrawButton_col2(short x1,short y1 , short x2,short y2,short col2)
{
#if COMPILER == DJ_COMPILER
	GrLine(x2,y1,x2,y2  ,col2) ;
	GrLine(x1,y2,x2-1,y2,col2) ;
#else
	_setcolor(col2) ;
	_moveto(x2,y1) ;
	_lineto(x2,y2) ;
	_moveto(x1,y2) ;
	_lineto(x2-1,y2) ;
#endif
}
void DrawButton_col3(short x1,short y1 , short x2,short y2,short col3)
{
#if COMPILER == DJ_COMPILER
	GrLine(x1+1,y1+1,x2-2,y1+1,col3) ;
	GrLine(x1+1,y1+2,x1+1,y2-2,col3) ;
#else
	_setcolor(col3) ;
	_moveto(x1+1,y1+1) ;
	_lineto(x2-2,y1+1) ;
	_moveto(x1+1,y1+2) ;
	_lineto(x1+1,y2-2) ;
#endif
}
void DrawButton_col4(short x1,short y1 , short x2,short y2,short col4)
{
#if COMPILER == DJ_COMPILER
	GrLine(x2-1,y1+1,x2-1,y2-1,col4) ;
	GrLine(x1+1,y2-1,x2-2,y2-1,col4) ;
#else
	_setcolor(col4) ;
	_moveto(x2-1,y1+1) ;
	_lineto(x2-1,y2-1) ;
	_moveto(x1+1,y2-1) ;
	_lineto(x2-2,y2-1) ;
#endif
}
DrawButtonx_proc_GET(DrawButton1_proc, x1, y1, x2, y2, col1, DrawButton_col1)
DrawButtonx_proc_GET(DrawButton2_proc, x1, y1, x2, y2, col2, DrawButton_col2)
DrawButtonx_proc_GET(DrawButton3_proc, x1, y1, x2, y2, col3, DrawButton_col3)
DrawButtonx_proc_GET(DrawButton4_proc, x1, y1, x2, y2, col4, DrawButton_col4)
DrawButtonxx_proc_GET(DrawButton12_proc, x1, y1, x2, y2, col1, col2, DrawButton_col1, DrawButton_col2)
DrawButtonxx_proc_GET(DrawButton34_proc, x1, y1, x2, y2, col3, col4, DrawButton_col3, DrawButton_col4)
DrawButton1234_proc_GET

void DrawButton_q (short x1, short y1, short x2, short y2, Frame_t *frame)
{
	short col1 , col2 ,col3 , col4 ;
	col1 = col4= frame->dark_col ;
	if(frame->type <=0){
		col2 = frame->black_col ;
		col3 = frame->light_col ;
	}
	else{
		col2  = frame->light_col ;
		col3  = frame->black_col ;
	}
	rectangle_fill_q(frame->main_col ,x1,y1,x2,y2);
	
	short len= (x2-x1+1)+(y2-y1+1) ;
	BYTE *dptr ;
	if(len < 300){
		DrawButton1234_proc_SAVE
	}
	else if(len < 600){
		DrawButtonxx_proc_SAVE( x1, y1, x2, y2, col1, col2, DrawButton12_proc)
		DrawButtonxx_proc_SAVE( x1, y1, x2, y2, col3, col4, DrawButton34_proc)
	}
	else{
		DrawButtonx_proc_SAVE( x1, y1, x2, y2, col1,DrawButton1_proc) 
		DrawButtonx_proc_SAVE( x1, y1, x2, y2, col2,DrawButton2_proc)
		DrawButtonx_proc_SAVE( x1, y1, x2, y2, col3,DrawButton3_proc)
		DrawButtonx_proc_SAVE( x1, y1, x2, y2, col4,DrawButton4_proc)
	}
}
void DrawTextButton1_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short ,title_fcol) ;
	GET_VAL(short ,lx) ;
	GET_VAL(short ,rx) ;
	GET_VAL(short ,ly) ;
	GET_VAL(short ,style) ;
	GET_VAL(short ,icon) ;
	BYTE *str= dptr ;
	GET_STRING
	CHK_CHKSUM
	char *title	= (char *) str ;
	short t1=0 ;
	if((style &0x2) != 0){
		PutIcon(lx+4,ly+4,icon,3) ;
		t1= 18 ;
	}

	if((style &0x1) != 0){
		short t2= GetStrLineWidth(title) ;
		PrintString((lx+rx-t2+t1+4)/2,ly+4,title_fcol,0,title) ;
	}
	farfree(ptr) ;
}
void DrawWindow_q (WinStyle_t *style)
{
	Frame_t *frame= &(style->frame) ;
	DrawButton_q(style->lx,style->ly,style->rx,style->ry,frame) ;
	DrawWindowTitle_q(style) ;
}
void PutIcon_q (short lx, short ly, short idx, short op)
{
	BYTE *dptr = (BYTE *)farmalloc(4*sizeof(short)+LEN_CHKSUM) ;
	BYTE *tptr= dptr ;
	SAVE_VAL(short , lx) ;
	SAVE_VAL(short , ly) ;
	SAVE_VAL(short , idx) ;
	SAVE_VAL(short , op) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(PutIcon_proc , tptr) ;
}
//不可以為static function,因為有其他地方會呼叫
void PutIcon (short lx, short ly, short idx, short op)
{
	// 總共有35個ICONs
	int start= idx*((16*15)+4)+4 ;
	for(int y=0 ; y < 15 ; y++){
		for(int x=0 ; x < 16 ; x++){
#if REAL_COLOR			
			int rgb_idx= icons[start++] ;
			GrPlot(lx+x,ly+y,RGB6_16(default_rgb[rgb_idx*3],default_rgb[rgb_idx*3+1],default_rgb[rgb_idx*3+2])) ;
#else
			GrPlot(lx+x,ly+y,icons[start++]) ;
#endif
		}
	}
}


void PutIcon_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short , lx) ;
	GET_VAL(short , ly) ;
	GET_VAL(short , idx) ;
	GET_VAL(short , op) ;
	CHK_CHKSUM
	PutIcon(lx,ly,idx,op) ;
	farfree(ptr) ;	
}


void rectangle_fill_q(COLOR_T color, short lx, short ly , short rx, short ry)
{
	short xlen= rx-lx+1 ;
	short ylen= ry-ly+1 ;
	short fill_dot=30000 ;
	short yinc = fill_dot/xlen ;
	short times= ylen/yinc ;
	short i ;
	for(i=0 ; i < times ; i++){
		BYTE *dptr = (BYTE *)farmalloc(5*sizeof(WORD)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(WORD, color) ;
		SAVE_VAL(WORD, lx) ;
		SAVE_VAL(WORD, ly + i*yinc) ;
		SAVE_VAL(WORD, rx) ;
		SAVE_VAL(WORD, ly + (i+1)*yinc -1) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(rectangle_fill_proc,tptr ) ;
	}
	if((ylen - times*yinc) !=0){
		BYTE *dptr = (BYTE *)farmalloc(5*sizeof(WORD)+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(WORD, color) ;
		SAVE_VAL(WORD, lx) ;
		SAVE_VAL(WORD, ly + i*yinc) ;
		SAVE_VAL(WORD, rx) ;
		SAVE_VAL(WORD, ry ) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(rectangle_fill_proc,tptr) ;
	}
}
void rectangle_fill_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD, color) ;
	GET_VAL(WORD, lx) ;
	GET_VAL(WORD, ly) ;
	GET_VAL(WORD, rx) ;
	GET_VAL(WORD, ry) ;
	CHK_CHKSUM
	bar256(lx,ly,rx,ry,color) ;
	farfree(ptr) ;
}
void digitdot_q(short lx , short ly ,COLOR_T color)
{
	BYTE *dptr= (BYTE *)farmalloc(2*sizeof(short)+1*sizeof(COLOR_T)+LEN_CHKSUM) ;
	BYTE *tptr = dptr ;
	SAVE_VAL(short,lx) ;
	SAVE_VAL(short,ly) ;
	SAVE_VAL(COLOR_T,color) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(digitdot_proc,tptr) ;
}
void rectangle_q(  short lx, short ly , short rx, short ry,COLOR_T color,short width)
{
	BYTE *dptr= (BYTE *)farmalloc(5*sizeof(short)+1*sizeof(COLOR_T)+LEN_CHKSUM) ;
	BYTE *tptr = dptr ;
	SAVE_VAL(short,lx) ;
	SAVE_VAL(short,ly) ;
	SAVE_VAL(short,rx) ;
	SAVE_VAL(short,ry) ;
	SAVE_VAL(COLOR_T,color) ;
	SAVE_VAL(short,width) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(rectangle_proc,tptr) ;
	
}
void rectangle(short lx, short ly , short rx, short ry,COLOR_T color,short width)
{
	GrLineOption lop ;
	lop.lno_color=color ;
	lop.lno_width=width ;
	lop.lno_pattlen=0 ;
	GrCustomBox(lx,ly,rx,ry,&lop) ;
}
void rectangle_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short,lx) ;
	GET_VAL(short,ly) ;
	GET_VAL(short,rx) ;
	GET_VAL(short,ry) ;
	GET_VAL(short,color) ;
	GET_VAL(short,width) ;
	CHK_CHKSUM
	rectangle(lx, ly, rx, ry, color, width) ;
	farfree(ptr) ;
}
void digitdot_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(short,lx) ;
	GET_VAL(short,ly) ;
	GET_VAL(short,color) ;
	CHK_CHKSUM
	putpixel(lx,ly,color) ;
	putpixel(lx+1,ly,color) ;
	putpixel(lx,ly+1,color) ;
	putpixel(lx+1,ly+1,color) ;
	farfree(ptr) ;
}
void rectangle_fill(COLOR_T color, short lx, short ly , short rx, short ry)
{
	bar256(lx,ly,rx,ry,color) ;
}
void rectangle_border_q(COLOR_T color, short lx, short ly , short rx, short ry)
{
	rectangle_q(lx,ly,rx,ry,color,NORM_WIDTH) ;
}

void rectangle_border(COLOR_T color, short lx, short ly , short rx, short ry)
{
	rectangle(lx,ly,rx,ry,color,NORM_WIDTH) ;
}
void closevideo(void )
{

#if COMPILER != DJ_COMPILER
	closegraph() ;
#else
	GrSetMode(GR_default_text) ;
#endif
}

int huge DetectVGA256(void){
	return(SVGA640x480x256) ;
}
void Init_Graphic(void)
{
	int bitno;
#if REAL_COLOR
	bitno=16 ;
#else
	bitno=8 ;
#endif
	GrSetMode(GR_width_height_bpp_graphics,SCRN_W,SCRN_H,bitno) ;
}
void bar256(SCRN_XY x1,SCRN_XY y1,SCRN_XY x2,SCRN_XY y2 , COLOR_T c)
{
	GrFilledBox(x1,y1,x2,y2,c) ;
}




void line256(int x1,int y1,int x2,int y2 ,  COLOR_T c)
{
	GrLineOption lop ;
	lop.lno_color=c ;
	lop.lno_width=NORM_WIDTH ;
	lop.lno_pattlen=0 ;
	GrCustomLine(x1,y1,x2,y2,&lop) ;
}





extern unsigned char huge ChFontData[] ;



extern unsigned char AscFontTbl[] ;


void  InitChFont (void)
{
	ChTotalNo= *((uint16 *)&ChFontData[2]) ;
	AscStart = MakeFarPointer((char *)&ChFontData[4]) ;
	ChIndex = MakeFarPointer((char *)&ChFontData[4+0x78*16]) ;
	ChStart = MakeFarPointer((char *)ChIndex+ChTotalNo*2) ;
}

void  ClearStringArea (short lx, short ly, short char_no, short color)
{
	rectangle_fill(color,lx,ly,lx+char_no*8-1, ly+15-1) ;
}
short SetStrColor (short fcol, short bcol, char *buf)
{
	*buf++ = 0x7e ;
	*buf++= (unsigned char) fcol ;
	*buf++= (unsigned char)bcol ;
	*buf++= 0 ;
	return(3) ;
}
short ColorStringLen (char *str)
{
	unsigned int len=0 ;
	unsigned char c ;
	while((c= *str++) !=0){
		if(c== 0x7e){
			str+=2 ;
		}
		else if(c >= 0x80){
			len += 2;
			str++ ;
		}
		else{
			len++ ;
		}
	}
	return(len) ;
	
}
short GetStrLineWidth (char *str)
{
	short width =0 ;
	unsigned char c ;
	while((c= *str++) != 0){
		if(c == 0x7e){
			str+= 2 ;
		}
		else if(c >= 0x80){
			str+=1 ;
			width +=16 ;
		}
		else{
			width+= 8 ;
		}
	}
	return(width) ;
}
short PrintStringLine_fmt_q (SCRN_XY x, SCRN_XY y, COLOR_T fcol, COLOR_T bcol, char *fmt, ...)
{
	char buf[120] ;
	va_list marker;
	
	
	va_start( marker,fmt);
	vsprintf(buf,fmt,marker) ;
	PrintStringLine_q (x,  y, fcol,  bcol, buf) ;
	return(1) ;
}
short PrintStringLine_fmt (SCRN_XY x, SCRN_XY y, COLOR_T fcol, COLOR_T bcol, char *fmt, ...)
{
	char buf[120] ;
	va_list marker; 
	
	
	va_start( marker,fmt);
	vsprintf(buf,fmt,marker) ;
	return(PrintStringLine (x,  y, fcol,  bcol, buf)) ;
}
void PrintStringLine_q(SCRN_XY x, SCRN_XY y, COLOR_T fcol, COLOR_T bcol, char *string)
{
	short len = ColorStringLen(string) ;
	short no_char=25 ;
	short times= len / no_char+1 ;
	short i ;
	char *str1= string ;
	short x1=x ;
	for(i=0 ; i < times ; i++){
		char *str2= str1 ;
		short j;
		for(j=0 ; j < no_char ; ){
			if(*str1 & 0x80){
				j+=2 ;str1+=2;
			}
			else if(*str1==0){
				break ;
			}
			else{
				j++;str1++ ;
			}
		}
		if(j== 0)break ;
		BYTE *dptr= (BYTE *)farmalloc(4*sizeof(WORD)+j+1+LEN_CHKSUM) ;
		BYTE *tptr = dptr ;
		SAVE_VAL(WORD , x1) ;
		SAVE_VAL(WORD , y) ;
		SAVE_VAL(WORD , fcol) ;
		SAVE_VAL(WORD , bcol) ;
		SAVE_STRING(str2,j) ;
		SAVE_CHKSUM
		FILL_PROC_QUEUE(PrintStringLine1_proc,tptr ) ;
		x1= x1+ASC_CHAR_W*j ;
	}
}
void PrintStringLine1_proc(void *ptr) 
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD , x1) ;
	GET_VAL(WORD , y) ;
	GET_VAL(WORD , fcol) ;
	GET_VAL(WORD , bcol) ;
    BYTE *str= dptr ;
    GET_STRING
	CHK_CHKSUM
	PrintStringLine(x1,y,fcol,bcol,(char *)str) ;
	farfree(ptr) ;
}
short PushImage (short lx, short ly, short rx, short ry)
{
	// 0:OK
	long size ;
	if((no_image+1) < MAX_IMAGESTACK){
#if SAVEIMAGE		
	#if COMPILER == DJ_COMPILER
		if((imagestack[no_image].buf=GrCreateContext(rx-lx+1,ry-ly+1,NULL,NULL))!=NULL){
   			GrBitBlt(imagestack[no_image].buf,0,0,NULL,lx,ly,rx,ry,GrWRITE) ;
			
			EPT_IDX(no_image, imagestack);
			imagestack[no_image].lx=lx ;
			imagestack[no_image].ly=ly ;
			imagestack[no_image].rx=rx ;
			imagestack[no_image].ry=ry ;
			no_image++ ;
			return(0) ;
		}
	#else
		size = _imagesize(lx,ly,rx,ry) ;
		if(size < 0x0000FF00L){
			if((imagestack[no_image].buf=(char *)farmalloc(size))!=NULL){ 
				
				EPT_IDX(no_image, imagestack);
				imagestack[no_image].lx=lx ;
				imagestack[no_image].ly=ly ;
				imagestack[no_image].rx=rx ;
				imagestack[no_image].ry=ry ;
				_getimage(lx,ly,rx,ry,imagestack[no_image].buf) ;
				no_image++ ;
				return(0) ;
			}
			return(1) ;
		}
	#endif
#else
		EPT_IDX(no_image, imagestack);
		imagestack[no_image].lx=lx ;
		imagestack[no_image].ly=ly ;
		imagestack[no_image].rx=rx ;
		imagestack[no_image].ry=ry ;
		no_image++ ;
		return(0) ;
#endif		
	}
	return(1) ;
}
void LoadFont(int no)
{
	FILE *fp ;
	char filename[]= PATPATH"0" ;
	
	EPT_IDX(sizeof(filename)-2, filename);
	filename[sizeof(filename)-2]= '0'+no ;
	fp = FOPEN(filename,"rb") ;
	char far *pp= ChStart ;
	for(int i=0 ; i < ChTotalNo*30 ; i++){
		*pp++= fgetc(fp) ;
	}
	FCLOSE(fp) ;
}

