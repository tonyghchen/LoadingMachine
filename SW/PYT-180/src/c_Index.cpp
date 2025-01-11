#include "header.h"






#if NEW_INDEX
	#define INDEX_LX1			10
	#define INDEX_RX1			310
	#define INDEX_LX2			380
	#define INDEX_RX2			610
	#define INDEX_LY			MAIN_WIN_LY+40
	#define INDEX_RY			MAIN_WIN_LY+380
	#define INDEX_XLEN1			300
	#define INDEX_YLEN			180
	#define INDEX_XGAP			10
	#define INDEX_YGAP			10
	
	#define INDEX_FILE_LY       105




void KeyPgDown_INDEX_FILE_CURSOR()
{
		if(Index.loc_x+Index.start_x+PAGE_LINES_INDEX >= (MAX_FILE_NO-1)){  	
			Index.loc_x= PAGE_LINES_INDEX-1 ;                                 	
			Index.start_x = MAX_FILE_NO-1-Index.loc_x ;                       	
		}                                                                    	
		else{                                                                	
			Index.start_x+=PAGE_LINES_INDEX ;                                 	
			if(Index.start_x+(PAGE_LINES_INDEX-1) > (MAX_FILE_NO-1)){         	
				Index.loc_x= 0 ;                                               	
				Index.start_x = MAX_FILE_NO-1-(PAGE_LINES_INDEX-1) ;           	
			}                                                                 	
		}                                                                    	
		DispIndex_q() ;                                                      	
		DispIndex_q(Index.loc_x,true) ;                                      	
		DispIndexContent_q() ; 
}                                              	
void KeyPgUp_INDEX_FILE_CURSOR()
{
		if(Index.start_x+Index.loc_x >= PAGE_LINES_INDEX){                	
			Index.start_x=Index.start_x+Index.loc_x - PAGE_LINES_INDEX ;   	
			Index.loc_x =0 ;                                               	
		}                                                                 	
		else{                                                            	
			Index.start_x=Index.loc_x=0 ;                                  	
		}                                                                 	
		DispIndex_q() ;                                                   	
		DispIndex_q(Index.loc_x , true) ;                                 	
		DispIndexContent_q() ; 
}                                           	
bool KeyInNum_INDEX(BYTE num)
{          											
	if(CursorLoc == INDEX_CONTENT_CURSOR){
		BYTE *b ;                        		
		b = &Index.Content[Index.y][Index.x];                       	
		switch(num){                                                	
			case 0:                                                  	
				*b='0' ;                                              	
				KeyRight() ;											
				break ;                                               	
			case 1:                                                  	
				switch_next("1AaBbCc",b) ;                            	
				break ;                                               	
			case 2:                                                  	
				switch_next("2DdEeFf",b) ;                            	
				break ;                                               	
			case 3:                                                  	
				switch_next("3GgHhIi",b) ;                            	
				break ;                                               	
			case 4:                                                  	
				switch_next("4JjKkLl",b) ;                            	
				break ;                                               	
			case 5:                                                  	
				switch_next("5MmNnOo",b) ;                            	
				break ;                                               	
			case 6:                                                  	
				switch_next("6PpQqRr",b) ;                            	
				break ;                                               	
			case 7:                                                  	
				switch_next("7SsTtUu",b) ;                            	
				break ;                                               	
			case 8:                                                  	
				switch_next("8VvWv",b) ;                              	
				break ;                                               	
			case 9:                                                  	
				switch_next("9XxYyZz",b) ;                            	
				break ;                                               	
		}                                                           	
		DispIndexContent_q(true) ; 
		return true ;                                 	
	}                                                              		
	else if(CursorLoc == INDEX_FILE_CURSOR){                       		
		Index.fileno <<=4 ;                                         	
		Index.fileno+= num ;                                        	
		Index.loc_x= 0;                                             	
		Index.start_x= (WORD)BcdToBin(2,Index.fileno) ;             	
		DispIndex_q() ;                                             	
		DispIndex_q(0,true) ;                                       	
		DispIndexContent_q() ;
		return(true) ;                                      	
	}                 
	else{
		return(false) ;
	}                                             		
}



void IndexFileMody (void)
{
}
char *Index_title[]=
{ 
	  "MESSAGE",
	  "檔案說明",
	  "MESSAGE",
} ;  
void DispIndexBox_q (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.style		= W_TITLE+W_ICON+W_CLOSE;
	ws.frame.main_col	= AIRBOX_MAIN_BCOLOR;
	ws.lx				= 300;
	ws.ly				= INDEX_FILE_LY;
	ws.rx				= 520;
	ws.ry				= INDEX_FILE_LY+290;
	ws.title_fcol	= BRIGHTWHITE_USR;
	ws.title_bcol	= RED_USR;
	ws.title = Index_title[idx_language];
	ws.icon  = HELP_ICON;

	DrawWindow_q(&ws);
}
bool IsEmptyIndexContent()
{
		for(WORD line =0 ; line < 16 ; line++){
			for(WORD idx =0 ; idx< 25 ; idx++){
				if(Index.Content[line][idx] != ' ') return (false) ;
			}
		}
		return(true) ;
}
void ClrIndexWindow_q(void)
{
		IndexScrn=false ;                                           
		ini_axis_str() ;                                            
		ReDrawEditWin_q() ;                                         
		ShowCursor() ;                                              
}
void iniComment()
{
	for(int y=0 ; y< 16 ; y++){
		for(int x=0 ; x < 25 ; x++){
			Index.Content[y][x]=' ' ;
		}
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
	char cfile[20],efile[20],Ifile[20] ;
	char *file[]= {efile,cfile,Ifile} ;
	sprintf(cfile,"檔案編號:%03d之說明",fileno) ;
	sprintf(efile,"PROG NO:%03d",fileno) ;
	sprintf(Ifile,"PROG NO:%03d",fileno) ;
	PrintStringLine_fmt(lx+2+5, ly+2,FILE_TITLE_FCOLOR, FILE_TITLE_BCOLOR, file[idx_language]);
	
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
void DispIndexWindow_q()
{
	WORD fileno = (short)BcdToBin(3,MachineStatus.file) ;
	ReadIndexContent(fileno) ;
	if(!IsEmptyIndexContent()){
		DispIndexBox_q () ;
		for(WORD line =0 ; line < 16 ; line++){
			
			EPT_IDX(line, Index.Content);
			EPT_IDX(25, Index.Content[0]);
			Index.Content[line][25]= '\0' ;
			PrintStringLine_q(305, INDEX_FILE_LY+30+(line)*ASC_CHAR_H, WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, (char*)(&Index.Content[line]) );
			Index.Content[line][25]= '\n' ;
		}
		IndexScrn=true ;
	}
	else if(IndexScrn){
		 ClrIndexWindow_q() ;
	}
}
#endif
