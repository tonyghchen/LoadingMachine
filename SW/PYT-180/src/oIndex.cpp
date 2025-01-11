#include "header.h"

#if NEW_INDEX
#define INDEX_LX1			10
#define INDEX_RX1			310
#define INDEX_LX2			380
#define INDEX_RX2			610
#define INDEX_LY			40
#define INDEX_RY			380
#define INDEX_XLEN1			300
#define INDEX_YLEN			180
#define INDEX_XGAP			10
#define INDEX_YGAP			10
void iniComment()
{
	for(int y=0 ; y< 16 ; y++){
		EPT_BC(y,Index.Content) ;
		for(int x=0 ; x < 25 ; x++){
			
			EPT_BC(x,Index.Content[0]) ;
			Index.Content[y][x]=' ' ;
		}
		
		EPT_BC(25,Index.Content[0]) ;
		Index.Content[y][25]='\n' ;
	}
}
void GComment()
{
	FILE *fp_c, *fp_d ;
	fp_c= FOPEN(COMMENT_C,"wb") ;
	if(DDisk){
		fp_d=FOPEN(COMMENT_D,"wb") ;
	}
	iniComment() ;
	for(long l=0 ; l < (long)MAX_FILE_NO ; l++){
		fwrite(Index.Content ,1,sizeof(Index.Content) ,fp_c) ;
		if(DDisk){
			fwrite(Index.Content ,1,sizeof(Index.Content) ,fp_d) ;
		}
	}
	FCLOSE(fp_c) ;
	if(DDisk){
		FCLOSE(fp_d) ;
	}
}
void DispIndex_window_q()
{
	WinStyle_t ws;


	DispMainWindow_q(EDIT_ICON,0) ;
	DispIndex_q() ;


	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= EDITBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= INDEX_LX2;
	ws.ly				= INDEX_LY;
	ws.rx				= INDEX_RX2;
	ws.ry				= INDEX_RY;


	DrawWindow_q(&ws);

	DispIndexContent_q() ;
}
void DispIndex_q()
{
	FILL_PROC_QUEUE(DispFileFrameIndex1_proc,NULL) ;
}
void DispIndex_q(WORD idx,bool flash_mode)
{
	short lx= INDEX_LX1 ;
	short ly= INDEX_LY ;

	WORD fileno= idx+Index.start_x ;
	if( fileno< MAX_FILE_NO){
		char file[100] ;
		sprintf(file,"%03d-",fileno) ;
		FILE *fp_c;
		fp_c= FOPEN(COMMENT_C,"rb") ;
		fseek(fp_c , fileno*sizeof(Index.Content),SEEK_SET) ;
		fread(&file[4],1,25,fp_c) ;
		file[4+25]= 0 ;
		FCLOSE(fp_c) ;
		short bcol,fcol ;
		if(flash_mode){
			fcol= FLASH_COLOR1_1;
			bcol= FLASH_COLOR1_2;
		}
		else{
			if(Index.loc_x == idx){
				fcol = CUR_PROG_FCOLOR ;
				bcol = CUR_PROG_BCOLOR ;
			}
			else{
				fcol=EDITBOX_MAIN_FCOLOR;
				bcol=EDITBOX_MAIN_BCOLOR;
			}
		}
		PrintStringLine_q(lx+2, ly+2+idx*18, fcol, bcol, file);
	}
}
void DispFileFrameIndex1_proc (void *ptr)
{
	Frame_t frame;
	char file[40] ;
	for(BYTE line =0 ; line < PAGE_LINES_INDEX ; line++){
		DispIndex_q(line,false) ;
	}
}
void ReadIndexContent(WORD fileno)
{
	FILE *fp_c;
	fp_c= FOPEN(COMMENT_C,"rb") ;
	fseek(fp_c , fileno*sizeof(Index.Content),SEEK_SET) ;
	fread(Index.Content,1,sizeof(Index.Content),fp_c) ;
	FCLOSE(fp_c) ;
}
void DispFileFrameIndex2_proc (void *ptr)
{

	BYTE *dptr=(BYTE *)ptr ;
	GET_VAL(short,fileno) ;
	CHK_CHKSUM

	short lx= INDEX_LX2;
	short ly=INDEX_LY ;
	short rx= INDEX_RX2 ;
	Frame_t frame;


	DefaultButtonStyle(&frame);
	frame.type = 0;
	DrawCasing(lx+2, ly+2, rx, ly+18, &frame);
	char file[20] ;
	sprintf(file,"檔案編號:%03d之說明",fileno) ;
	PrintStringLine_fmt(lx+2+5, ly+2,FILE_TITLE_FCOLOR, FILE_TITLE_BCOLOR, file);
	
	ReadIndexContent(fileno) ;
	
	for(int line=0 ; line < 16 ; line++){
		PrintStringLine_fmt(lx+2, ly+2+(line+1)*19, FILE_TITLE_FCOLOR, FILE_TITLE_BCOLOR,"%2d.",line+1);
		char text[]= "1234567890123456789012345" ;
		Index.Content[line][25] = '\0' ;
		PrintStringLine(lx+2+3*8, ly+2+(line+1)*19, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, (char*)(&Index.Content[line]) );
		Index.Content[line][25] = '\n' ;
	}
	farfree(ptr) ;
}
void DispIndexContent_q()
{
	BYTE *dptr= (BYTE *) farmalloc(1*sizeof(short)+LEN_CHKSUM) ;
	BYTE *tptr=dptr ;
	SAVE_VAL(short, Index.start_x+Index.loc_x) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(DispFileFrameIndex2_proc,tptr) ;
}
void DispIndexContent_q(bool flash)
{
	BYTE *dptr= (BYTE *) farmalloc(5*sizeof(short)+LEN_CHKSUM) ;
	BYTE *tptr=dptr ;
	SAVE_VAL(short, Index.x) ;
	SAVE_VAL(short, Index.y) ;
	SAVE_VAL(short, Index.Content[Index.y][Index.x]) ;
	short bcol,fcol ;
	if(flash){
		fcol = FLASH_COLOR1_1 ;
		bcol = FLASH_COLOR1_2 ;
	}
	else{
		fcol = WIN_TEXT_FCOLOR ;
		bcol = WIN_TEXT_BCOLOR ;
	}
	SAVE_VAL(short, fcol) ;
	SAVE_VAL(short, bcol) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(DispIndexContent_proc,tptr) ;

}
void DispIndexContent_proc(void *ptr)
{
	BYTE *dptr=(BYTE *)ptr ;
	GET_VAL(short,x) ;
	GET_VAL(short,y) ;
	GET_VAL(short,nchar) ;
	GET_VAL(short,fcol) ;
	GET_VAL(short,bcol) ;
	CHK_CHKSUM

	short lx= INDEX_LX2;
	short ly=INDEX_LY ;
	short rx= INDEX_RX2 ;
	char text[]= " " ;
	text[0]= nchar ;
	PrintStringLine_fmt(lx+2+3*8+x*ASC_CHAR_W, ly+2+(y+1)*19,fcol ,bcol , text);
	farfree(ptr) ;
}
#endif
