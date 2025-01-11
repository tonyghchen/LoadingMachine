#include "pro\header.h"
#include <string.h>
struct CHPAT huge *chpat ;
unsigned char huge *ppat ;
unsigned char huge *pbignum ;
unsigned char huge *pbig30 ;
unsigned char huge *pbig48 ;
unsigned char huge *psmallnum ;
unsigned char huge *pmednum ;
unsigned char huge *pascii ;

unsigned char num_par[6][6]= {
	{ SMALLNBYTES ,SMALLNHEIGHT , SMALLNWIDTH, SMALLNWIDTHB,SMALLNSPACE,SMALLNHEIGHT-5} ,
	{ BIGNBYTES ,BIGNHEIGHT , BIGNWIDTH, BIGNWIDTHB ,BIGNSPACE,BIGNHEIGHT-4} ,
	{ MEDNBYTES ,MEDNHEIGHT , MEDNWIDTH, MEDNWIDTHB ,MEDNSPACE,MEDNHEIGHT-5} ,
	{ MEDNBYTES ,MEDNHEIGHT , MEDNWIDTH, MEDNWIDTHB ,MEDNSPACE,MEDNHEIGHT-5} ,
	{ BIG30NBYTES ,BIG30NHEIGHT , BIG30NWIDTH, BIG30NWIDTHB ,BIG30NSPACE,BIG30NHEIGHT-4} ,
	{ BIG48NBYTES ,BIG48NHEIGHT , BIG48NWIDTH, BIG48NWIDTHB ,BIG48NSPACE,BIG48NHEIGHT-4} ,
} ;
#define UPDATE_MEDNUM							 		\
	int x2= x1+MEDNWIDTH-1 ;							\
	int y2= y1+MEDNHEIGHT-3 ;							\
	char s[]= " " ; 									\
	for(int i=0 ; i < len ; i++){						\
		if(new_s[i] != old_s[i]){						\
			bar256(x1,y1,x2,y2,clr_bg) ;				\
			s[0]= new_s[i] ;							\
			mednum(x1,y1,clr_text,s,false,0) ;			\
		}												\
		x1+= MEDNWIDTH ;								\
		x2+= MEDNWIDTH ;								\
		if((pointpos !=0) &&(i == (len - pointpos-1))){	\
			x1+=POINTWIDTH ;							\
			x2+=POINTWIDTH ;					  		\
		}												\
	}													\
	strcpy(old_s,new_s) ;



////////////////////////////////////////////////////////////////////////////////
//
//自動format 起始點
//

unsigned char huge *filetobuf(char *filename)
{

	FILE *fp = FOPEN(filename,"rb") ;
	if(fp ==NULL)return(NULL) ;
	long llen = filesize(fp) +10;
	unsigned char huge *pp =(unsigned char *) farmalloc((long)llen) ;
	char buf[251] ;
	int len ;
	for(unsigned char huge *tptr = pp ; (len = fread(buf , 1 , 250 , fp)) > 0 ; ){
		for(int i = 0 ; i < len ; i++){
			*tptr++ = buf[i] ;
		}
	}
	FCLOSE(fp) ;
	return(pp) ;
}
void free_pat(void)
{ 
	farfree(chpat) ;
	farfree(ppat) ;
	farfree(pbignum) ;
	farfree(pbig30) ;
	farfree(pbig48) ;
	farfree(psmallnum) ;
	farfree(pmednum) ;
	farfree(pascii) ;
}
void ini_pat(void)
{
	chpat =(struct CHPAT *)filetobuf(PATPATH"springp.idx") ;
	ppat= filetobuf(PATPATH"springp.dat") ;
	pbignum=filetobuf(PATPATH"bignum.dat") ;
	pbig30= filetobuf(PATPATH"big30.dat") ;
	pbig48= filetobuf(PATPATH"big48.dat") ;
	psmallnum=filetobuf(PATPATH"smallnum.dat") ;
	pmednum=filetobuf(PATPATH"mednum.dat") ;
	pascii=filetobuf(PATPATH"ascii.dat") ;
}
void tputchin_00(void *dptr)
{
	int *iptr= (int *)dptr ;
	int istart= iptr[0] ;
	int iend = iptr[1] ;
	int x= iptr[2] ;
	int y1= iptr[3] ;
	int w= iptr[4] ;
	int color= iptr[5] ;
	unsigned char huge **pbuf = (unsigned char huge **)(iptr+6) ;
	unsigned char huge * buf= pbuf[0] ;
	farfree(dptr) ;

	unsigned char  t1 ;
	int x1 ;
	for(int i = istart ; i < iend ; i++){
		x1=x ;
		for(int j = 0 ; j < w ; j++){
			t1 = *buf++ ;
			for(int k=0 ; k < 8 ; k++){
				if(t1 & BITmask[k]){
					putpixel(x1,y1,color) ;
				}
				x1++ ;
			}
		}
		y1++ ;
	}
}
void tputchin(int x , int y , int color , int w , int h , unsigned char huge *buf )
{
	int th = 550/w ;
	int times= h/th+(((h%th)== 0) ? 0: 1) ;
	for(int i = 0 ; i < times ; i++){
		BYTE *dptr= (BYTE *) farmalloc(sizeof(short)*6+sizeof(unsigned char huge *)*1+LEN_CHKSUM) ;
        BYTE *tptr = dptr ;
		short ith ;
		SAVE_VAL(short , ith=i*th) ;
		int iend = (i+1)*th ;
		SAVE_VAL(short , (iend > h)? h:iend) ;
		SAVE_VAL(short , x) ;
		SAVE_VAL(short , y+ith) ;
		SAVE_VAL(short , w) ;
		SAVE_VAL(short , color) ;
		SAVE_VAL(unsigned char huge *, buf+w*ith) ;
		SAVE_CHKSUM
		if(i==0){
			//直接輸出
			tputchin_00((void *)tptr) ;
		}
		else{
			FILL_PROC_QUEUE(tputchin_00,tptr) ;
		}
	}
}
bool chk_valid_num(char *buf)
{
	// 檢查顯示的字串是否為有效的數值
	for(char c= *buf ; c != '\0' ; ){
		if((c == '-') || (c == '+') ||(c == ' ')||(c== '.')||((c >= '0') && (c <= '9'))){
			c=*++buf;
		}
		else{
			return(false) ;
		}
	}
	return(true) ;
}
int  big_smallnumc(SCRN_XY x , SCRN_XY y , COLOR_T color , unsigned char t ,bool reverse, int size )
{
	// reverse:false代表以color色顯示文字/true代表以color色顯示文字以外的部分

	int i , j , k ,w ;
	unsigned char	t1 ;
	unsigned int off ;
	unsigned char huge *pp1 ;
	int x1=x,y1=y ;
	if(t =='+'){
		off= 10*num_par[size][NBYTES] ;
	}
	else if(t== '-'){
		off=11*num_par[size][NBYTES] ;
	}
	else if(t == '/'){
		off=12*num_par[size][NBYTES] ;
	}
	else if(t == '?'){
		off=13*num_par[size][NBYTES] ;
	}
	else if(t == '.'){
		off=14*num_par[size][NBYTES] ;
	}
	else if(t == ' '){
		return(num_par[size][NSPACE]) ;
	}
	else{
		off= (t-'0')*num_par[size][NBYTES] ;
	}
	switch(size){
case 0:
	pp1= psmallnum ;
	break ;
case 1:
	pp1 = pbignum ;
	break ;
case 2:
	pp1= pmednum ;
	break ;
case 3:
	pp1= pascii ;
	off = (t-0x20)*num_par[size][NBYTES] ;
	break ;
case 4:
	pp1= pbig30 ;
	break ;
case 5:
	pp1= pbig48 ;
	break ;
	}
	pp1 += off ;
	for(i = 0 ; i < num_par[size][NHEIGHT] ; i++){
		x1=x ;
		for(j = 0,w=0 ; j < num_par[size][NWIDTHB] ; j++){
			t1 = *pp1++ ;
			for(k=0 ; (k < 8) &&(w < num_par[size][NWIDTH]) ; k++,w++){
				if(reverse){
					if(!(t1 & BITmask[k])){
						putpixel(x1,y1,color) ;
					}
				}
				else{
					if(t1 & BITmask[k]){
						putpixel(x1,y1,color) ;
					}
				}
				x1++ ;
			}
		}
		y1++ ;
	}
	return(num_par[size][NWIDTH]) ;
}
void ascii_out(SCRN_XY x , SCRN_XY y , COLOR_T color , Cptr buf ,bool reverse )
{
	int size=3 ;
	unsigned char t ;
	while((t=*buf++)!=0){
		x+=big_smallnumc(x,y,color ,t,reverse,size) ;
	}
}
void big_smallnum(SCRN_XY x , SCRN_XY y , COLOR_T color , Cptr buf ,bool reverse, int size,int8 pointpos )
{
	unsigned char t ;
	if(chk_valid_num(buf)){
		if(pointpos <= 0){
			while((t=*buf++)!=0){
				x+=big_smallnumc(x,y,color ,t,reverse,size) ;
			}
		}
		else{
			//顯示有小數點的數
			int intlen = (strlen(buf) -pointpos) ;
			for(int i=0 ; i < intlen ;i++){
				x+= big_smallnumc(x,y,color,*buf++,reverse,size) ;
			}
			// 繪製小數點
			int y1 = y+num_par[size][POINTYOFF];
			putpixel(x,y1-1,color) ;
			putpixel(x+1,y1-1,color) ;
			putpixel(x,y1,color) ;
			putpixel(x+1,y1,color) ;
			x += POINTWIDTH ;
			for(int i=0 ; i < (pointpos) ;i++){
				x+= big_smallnumc(x,y,color,*buf++,reverse,size) ;
			}
		}
	}
	else{
		invalid_num(x,y,color , strlen(buf) , 1) ;
	}
}
void big48(SCRN_XY x , SCRN_XY y , COLOR_T color , Cptr buf ,bool reverse,int8 pointpos)
{
	big_smallnum(x ,y , color ,buf , reverse, 5,pointpos) ;
}
void big30(SCRN_XY x , SCRN_XY y , COLOR_T color , Cptr buf ,bool reverse,int8 pointpos)
{
	big_smallnum(x ,y , color ,buf , reverse, 4,pointpos) ;
}
void bignum(SCRN_XY x , SCRN_XY y , COLOR_T color , Cptr buf ,bool reverse,int8 pointpos )
{
	big_smallnum(x ,y , color ,buf , reverse, 1,pointpos) ;
}
void smallnum(SCRN_XY x , SCRN_XY y , COLOR_T color , Cptr buf ,bool reverse , int8 pointpos )
{
	big_smallnum(x ,y , color ,buf , reverse, 0 ,pointpos) ;
}
void mednum(SCRN_XY x , SCRN_XY y , COLOR_T color , Cptr buf ,bool reverse,int8 pointpos )
{
	big_smallnum(x ,y , color ,buf , reverse, 2 ,pointpos) ;
}
void invalid_num(SCRN_XY x , SCRN_XY y , COLOR_T color , int nochar , int size)
{
	int width = num_par[size][NWIDTH] ;
	int height = num_par[size][NHEIGHT] ;
	bar256(x , y+height-2 , x+width*nochar , y+height-1 , color) ;
	big_smallnumc(x+width*nochar/2-width/2,y,color ,'?',false,size) ;

}
void update_mednum(int new_val , char *old_s ,int len,	int x1 , int y1 , int clr_text , int clr_bg,int pointpos)
{
	char new_s[10] ;
	char fmt[]= "%03d" ;
	fmt[2]= '0'+len ;
	sprintf(new_s,fmt,new_val) ;
	UPDATE_MEDNUM
}
void update_mednum(char *new_s , char *old_s ,int len,	int x1 , int y1 , int clr_text , int clr_bg,int pointpos)
{
	UPDATE_MEDNUM
}


void PUTCHIN(SCRN_XY X,SCRN_XY  Y, int IDX,COLOR_T COLOR)
{
	tputchin(X,Y,COLOR,chpat[IDX].width,chpat[IDX].height,ppat+chpat[IDX].idx) ;
}

