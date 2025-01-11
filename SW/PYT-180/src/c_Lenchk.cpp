#include "header.h"
#include <math.h>

char *lenchk_scale[]= { "+OVER","+0.35","+0.30","+0.25","+0.20","+0.15","+0.10","+0.05","0",
"-0.05","-0.10","-0.15","-0.20","-0.25","-0.30","-0.35" ,"-OVER"} ;
double tolerance[]={+0.20,-0.20} ;
char idx_lenchk_scale[]= { 4,12} ;
#define LENCHK_X1	70
#define LENCHK_Y1	77


void putdot_LENCHK(int x,int y)
{
	int x1= LENCHK_X1 ;
	int y1= LENCHK_Y1 ;
	putpixel(x1+x*3/2,y1+(127-(y*127/20)),BLACK_USR) ;
	putpixel(x1+x*3/2,y1+(127-(y*127/20))+1,BLACK_USR) ;
}
void d_curve_bg_lenchk_01(void *dptr)
{
	GET_PARAMETERS_int4(tx2,ty2,tx2w,y2) ;
#if COMPILER == DJ_COMPILER	
	GrLineOption lop ;
	lop.lno_color=BLACK_USR ;
	lop.lno_width=NORM_WIDTH ;
	lop.lno_pattlen=0 ;
	GrCustomLine(tx2,ty2,tx2+tx2w-1,ty2,&lop) ;
	lop.lno_color=LIGHTGRAY_USR ;
	ty2= y2+4*15+7 ;
	GrCustomLine(tx2,ty2,tx2+tx2w-1,ty2,&lop) ;
	ty2= y2+(8+4)*15+7 ;
	GrCustomLine(tx2,ty2,tx2+tx2w-1,ty2,&lop) ;
#endif	
#if COMPILER == BC_COMPILER	
	setcolor(BLACK_USR) ;
	setlinestyle(SOLID_LINE,0x0,NORM_WIDTH) ;
	line(tx2,ty2,tx2+tx2w-1,ty2) ;
	setcolor(LIGHTGRAY_USR) ;
	ty2= y2+4*15+7 ;
	line(tx2,ty2,tx2+tx2w-1,ty2) ;
	ty2= y2+(8+4)*15+7 ;
	line(tx2,ty2,tx2+tx2w-1,ty2) ;
#endif	
}
void d_curve_bg_lenchk(void *dptr)
{
	dptr=dptr ;
	int y2 = 80 ;
	int x3=60 ;
	int x3w= 10 ;
	int ty2= y2+8*15+7 ;
	int tx2= x3+x3w ;
	int tx2w=300 ;
	int y3 = y2+17*15-1 ;
	int tx3 = tx2+tx2w-1 ;
	bar256_q(tx2,y2,tx3,y3,LIGHTGREEN_USR) ;
	int *iptr ;
	SAVE_PARAMETERS_int4(tx2,ty2,tx2w,y2) ;
	FILL_PROC_QUEUE(d_curve_bg_lenchk_01,iptr) ;
}
void d_acc_no_curve_bg_00(void *dptr)
{
#if COMPILER == DJ_COMPILER
	GET_PARAMETERS_int4(vx1,vx1w,vy1,vy2) ;
	GrLineOption lop ;
	lop.lno_color=BLUE_USR ;
	lop.lno_width=NORM_WIDTH ;
	lop.lno_pattlen=2 ;
	lop.lno_dashpat=(unsigned char*)"\3\1" ;
	for(int i=0 ; i < 6 ; i++){
		int tx= vx1+i*vx1w ;
		if(i==5){
			lop.lno_pattlen=0 ;
		}
		GrCustomLine(tx,vy1,tx,vy2,&lop) ;
	}
#endif	
#if COMPILER == BC_COMPILER
	GET_PARAMETERS_int4(vx1,vx1w,vy1,vy2) ;
	setcolor(BLUE_USR) ;
	setlinestyle(DOTTED_LINE,0x0,NORM_WIDTH) ;
	for(int i=0 ; i < 6 ; i++){
		int tx= vx1+i*vx1w ;
		if(i==5){
			setlinestyle(SOLID_LINE,0x0,NORM_WIDTH) ;
		}
		line(tx,vy1,tx,vy2) ;
	}
#endif	
}
void d_acc_no_curve_bg(void *dptr)
{
	dptr=dptr ;
	//	int y2 = 80 ;
	int x3=60 ;
	int x3w= 10 ;
	int y3 = 70 ;
	int y4 = y3+265 ;
	int tx2= x3+x3w ;
	int tx2w=300 ;
	int vx1= tx2+tx2w+10 ;
	int vx1w = 36 ;
	int vy1= y3 ;
	int vy2= y4 ;
	int *iptr ;

	int vx2= vx1+5*vx1w-1 ;

	bar256_q(vx1,vy1,vx2,vy2,YELLOW_USR) ;


	SAVE_PARAMETERS_int4(vx1,vx1w,vy1,vy2) ;
	FILL_PROC_QUEUE(d_acc_no_curve_bg_00,iptr) ;
}
void d_lenchk_screen_01(void *dptr)
{
	GET_PARAMETERS_int2(x10,y10) ;
	//顯示公差
	for(int i=0 ; i < 2 ; i++){
		PUTCHIN(x10,y10+20*i,202+i-OFF_PATTERN,BLACK_USR) ;
	}

}
void d_lenchk_screen_01c(void *dptr)
{
	char buf[50] ;
	GET_PARAMETERS_int4(x10,y10,istart,iend) ;
	// 顯示測試值
	for(int i=istart ; i < iend ; i++){
		sprintf(buf,"%+4.2f",tolerance[i]) ;
		ascii_out(x10+60,y10+20*i+3,BLACK_USR,buf,true) ;
	}
}
void d_lenchk_screen_01a(void *dptr)
{
	GET_PARAMETERS_int4(x2,y2,istart,iend) ;
	//顯示刻度
	for(int i=istart ; i < iend; i++){
		int tx= (i== 8)?(x2+35) : x2 ;
		ascii_out( tx,y2+i*15,RED_USR,lenchk_scale[i],false) ;
	}
}
void d_lenchk_screen_01b(void *dptr)
{
	GET_PARAMETERS_int7(x3,y3,x3w,y4,x5,y5,y5h) ;
	//顯示垂直bar
	bar256(x3,y3,x3+x3w-1 ,y4 ,LIGHTBLUE_USR) ;




	//顯示下水平bar
	bar256(x5,y5,SCREEN_MAXX-1 , y5+y5h-1,LIGHTBLUE_USR) ;
}
void d_lenchk_screen_02a(void *dptr)
{
	GET_PARAMETERS_int5(y5,istart , c1,c2,c3) ;
	char buf[]= "1" ;
	buf[0]= c1 ;
	big30(0+(istart+0)*BIG30NWIDTH,y5+25,BLACK_USR,buf,true,-1) ;
	buf[0]= c2 ;
	big30(0+(istart+1)*BIG30NWIDTH,y5+25,BLACK_USR,buf,true,-1) ;
	buf[0]= c3 ;
	big30(0+(istart+2)*BIG30NWIDTH,y5+25,BLACK_USR,buf,true,-1) ;
}
void d_lenchk_screen_02(void *dptr)
{
	GET_PARAMETERS_int1(y5) ;
	// 自由長
	PUTCHIN(0,y5,190-OFF_PATTERN,BLACK_USR) ;
}
void d_lenchk_screen_03(void *dptr)
{
	GET_PARAMETERS_int4(x5,y6,istart,iend) ;
	//X平均值....
	for(int i=istart ; i < iend ; i++){
		PUTCHIN(x5,y6+i*20,191+i-OFF_PATTERN , BLACK_USR) ;
	}
}
void d_lenchk_screen_04(void *dptr)
{
	GET_PARAMETERS_int2(x7,y6) ;
	//良品數量
	PUTCHIN(x7,y6+15,196-OFF_PATTERN , BLACK_USR) ;


	lenchk_buf.max_acc_no= lenchk_buf.lmax_acc_no=0 ;
	//使得cur_idx和lcur_idx的各個數字不同
	char buf[10] ;
	sprintf(buf,"%07ld",lenchk_buf.cur_idx) ;
	for(int i=0 ; i < 7 ; i++){
		if(buf[i]== '0'){
			buf[i]= '9' ;
		}
		else{
			buf[i]-- ;
		}
	}
	sscanf(buf,"%ld",&lenchk_buf.lcur_idx) ;

}
void d_lenchk_screen_05(void *dptr)
{

	//總合....
	GET_PARAMETERS_int4(x8,y6,istart,iend) ;
	for(int i=istart ; i < iend ; i++){
		PUTCHIN(x8,y6+i*20,197+i-OFF_PATTERN , BLACK_USR) ;
	}
}
void d_lenchk_screen(void *dptr)
{
	dptr=dptr ;
	bar256_q(0,0,SCREEN_MAXX-1,SCREEN_MAXY-1,LIGHTGRAY_USR) ;  //清除螢幕為背景色


	//顯示公差
	int  x10=20 ;
	int  y10=5 ;
	// 顯示測試值
	//顯示上水平bar
	int y1=50 ;
	int y1h= 20 ;
	//顯示刻度
	int x2= 10 ;
	int y2= y1+y1h+10 ;
	//顯示垂直bar
	int y3 = y1+y1h ;
	int y4 = y3+265 ;
	int x3=60 ;
	int x3w= 10 ;
	//顯示下水平bar
	int x5= x3+x3w+50 ;
	int y5= y4 ;
	int y5h=20 ;
	int y6 = y5+y5h ;
	//良品數量
	int x7= x5+170 ;
	//總合....
	int x8= x7+170 ;

	int *iptr ;
	SAVE_PARAMETERS_int2(x10,y10) ;
	FILL_PROC_QUEUE(d_lenchk_screen_01,iptr) ;

	SAVE_PARAMETERS_int4(x10,y10,0,1) ;
	FILL_PROC_QUEUE(d_lenchk_screen_01c,iptr) ;
	SAVE_PARAMETERS_int4(x10,y10,1,2) ;
	FILL_PROC_QUEUE(d_lenchk_screen_01c,iptr) ;


	bar256_q(0,y1,SCREEN_MAXX-1,y1+y1h-1,LIGHTBLUE_USR) ;

	bool end_flag=false ;
	for(int i=0 ; !end_flag ; i++){
		int t= (i+1)*3 ;
		if(t >= 17){
			t=17 ;
			end_flag = true ;
		}
		SAVE_PARAMETERS_int4(x2,y2,i*3,t) ;
		FILL_PROC_QUEUE(d_lenchk_screen_01a,iptr) ;
	}
	SAVE_PARAMETERS_int7(x3,y3,x3w,y4,x5,y5,y5h) ;
	FILL_PROC_QUEUE(d_lenchk_screen_01b,iptr) ;

	//內部刻度線
	d_curve_bg_lenchk(NULL) ;
	FILL_PROC_QUEUE(d_acc_no_curve_bg,NULL) ;

	SAVE_PARAMETERS_int1(y5) ;
	FILL_PROC_QUEUE(d_lenchk_screen_02,iptr) ;

	char buf1[]= "+0.400" ;
	SAVE_PARAMETERS_int5(y5,0,buf1[0],buf1[1],buf1[2]) ;
	FILL_PROC_QUEUE(d_lenchk_screen_02a,iptr) ;
	SAVE_PARAMETERS_int5(y5,3,buf1[3],buf1[4],buf1[5]) ;
	FILL_PROC_QUEUE(d_lenchk_screen_02a,iptr) ;

	SAVE_PARAMETERS_int4(x5,y6,0,2) ;
	FILL_PROC_QUEUE(d_lenchk_screen_03,iptr) ;
	SAVE_PARAMETERS_int4(x5,y6,2,4) ;
	FILL_PROC_QUEUE(d_lenchk_screen_03,iptr) ;
	SAVE_PARAMETERS_int4(x5,y6,4,5) ;
	FILL_PROC_QUEUE(d_lenchk_screen_03,iptr) ;

	SAVE_PARAMETERS_int2(x7,y6) ;
	FILL_PROC_QUEUE(d_lenchk_screen_04,iptr) ;
	SAVE_PARAMETERS_int4(x8,y6,0,2) ;
	FILL_PROC_QUEUE(d_lenchk_screen_05,iptr) ;
	SAVE_PARAMETERS_int4(x8,y6,2,4) ;
	FILL_PROC_QUEUE(d_lenchk_screen_05,iptr) ;
	SAVE_PARAMETERS_int4(x8,y6,4,5) ;
	FILL_PROC_QUEUE(d_lenchk_screen_05,iptr) ;
}
void update_lenchk_screen_00(void *dptr)
{
	GET_PARAMETERS_int2(istart,iend) ;
	char buf[100] ;
	int y2= 80 ;
	for(int i=istart ; i < iend ; i++){
		sprintf(buf,"%ld",lenchk_buf.acc_no[16-i]) ;
		int t= (7-strlen(buf))*MEDNWIDTH ;
		bar256(570,y2+i*15,570+MEDNWIDTH*7-1,y2+(i+1)*15-1,LIGHTGRAY_USR) ;
		ascii_out(570+t,y2+i*15,BLACK_USR,buf,false) ;
		int tx1= (int)(560-((float)lenchk_buf.acc_no[16-i]/lenchk_buf.max_acc_no)*180) ;
		bar256(tx1,y2+i*15+7 , 560,y2+i*15+10 , GREEN_USR) ;
	}
}
void update_lenchk_screen_01a(void *dptr)
{
	char buf[100] ;
	GET_PARAMETERS_int2(x5,y6) ;
	lenchk_buf.std_dev= sqrt(lenchk_buf.std_dev-lenchk_buf.average*lenchk_buf.average)*3 ;
	sprintf(buf,"%6.3f",lenchk_buf.std_dev) ;
	bar256(x5+110,y6+1*20,x5+110+MEDNWIDTH*6-1,y6+2*20-1,LIGHTGRAY_USR) ;
	ascii_out(x5+110,y6+1*20,BLACK_USR,buf,true) ;
}
void update_lenchk_screen_01(void *dptr)
{
	dptr=dptr ;

	int *iptr ;
	char buf[100] ;
	int x5=120 ;
	int y6 = 355 ;
	//顯示更新數值
	if(lenchk_buf.cur_idx !=0){
		lenchk_buf.average= lenchk_buf.total/lenchk_buf.cur_idx ;
		lenchk_buf.std_dev = lenchk_buf.total2/lenchk_buf.cur_idx ;
	}
	else{
		lenchk_buf.average= 0 ;
		lenchk_buf.std_dev = 0 ;
	}
	lenchk_buf.stat_idx= lenchk_buf.cur_idx ;
	sprintf(buf,"%+6.3f",lenchk_buf.average) ;
	bar256(x5+110,y6+0*20,x5+110+MEDNWIDTH*6-1,y6+1*20-1,LIGHTGRAY_USR) ;
	ascii_out(x5+110,y6+0*20,BLACK_USR,buf,true) ;
	SAVE_PARAMETERS_int2(x5,y6) ;
	FILL_PROC_QUEUE(update_lenchk_screen_01a,iptr) ;
}
void update_lenchk_screen_02a(void *dptr)
{
	char buf[]= "1" ;
	GET_PARAMETERS_int4(digit,i,x7,y6) ;
	int x8 = x7+170 ;
	buf[0]= digit ;
	bar256(x7+i*BIG48NWIDTH,y6+50,x7+(i+1)*BIG48NWIDTH-1,y6+50+BIG48NHEIGHT,LIGHTGRAY_USR) ;
	big48(x7+i*BIG48NWIDTH,y6+50,BLACK_USR,buf,true,-1) ;


	bar256(x8+110+i*MEDNWIDTH,y6+3*20,x8+110+(i+1)*MEDNWIDTH-1,y6+4*20-1,LIGHTGRAY_USR) ;
	ascii_out(x8+110+i*MEDNWIDTH,y6+3*20,BLACK_USR,buf,true) ;
}
void update_lenchk_screen_02(void *dptr)
{
	dptr=dptr ;

	int *iptr ;
	char buf[100] ;
	int x5=120 ;
	int y6 = 355 ;
	int x7=x5+170 ;
	if(lenchk_buf.std_dev != 0){
		lenchk_buf.cap_idx= (tolerance[0]-tolerance[1])/(2*lenchk_buf.std_dev) ;
	}
	else{
		lenchk_buf.cap_idx= 0 ;
	}
	sprintf(buf,"%6.3f",lenchk_buf.cap_idx) ;
	bar256(x5+110,y6+2*20,x5+110+MEDNWIDTH*6-1,y6+3*20-1,LIGHTGRAY_USR) ;
	ascii_out(x5+110,y6+2*20,BLACK_USR,buf,true) ;

	char buf1[10] ;
	sprintf(buf,"%07ld",lenchk_buf.cur_idx) ;
	sprintf(buf1,"%07ld",lenchk_buf.lcur_idx) ;
	for(int i=0 ; i< 7 ; i++){
		if(buf[i] != buf1[i]){
			SAVE_PARAMETERS_int4(buf[i],i,x7,y6) ;
			FILL_PROC_QUEUE(update_lenchk_screen_02a,iptr ) ;
		}
	}
	lenchk_buf.lcur_idx= lenchk_buf.cur_idx ;
}
void update_lenchk_screen(void *dptr)
{
	dptr=dptr ;

	// 顯示acc_no bar
	long max_acc=0 ;
	for(int i=0 ; i < 17 ; i++){
		if(max_acc < lenchk_buf.acc_no[i]){
			max_acc= lenchk_buf.acc_no[i] ;
		}
	}
	if(max_acc > lenchk_buf.max_acc_no){
		//計算新的max_acc_no
		lenchk_buf.max_acc_no= (long)((max_acc / SCALE_ACC_NO)+1)*SCALE_ACC_NO ;
	}
	if(lenchk_buf.max_acc_no == 0){
		lenchk_buf.max_acc_no= SCALE_ACC_NO ;
	}
	if(lenchk_buf.max_acc_no != lenchk_buf.lmax_acc_no){
		lenchk_buf.lmax_acc_no= lenchk_buf.max_acc_no ;
		FILL_PROC_QUEUE(d_acc_no_curve_bg,NULL) ;
	}
	// 0~16 行
	int *iptr ;
	for(int i=0 ; i < 6 ; i++){
		int t= (i ==5) ? 17 : (i+1)*3 ;
		SAVE_PARAMETERS_int2((i*3),t) ;
		FILL_PROC_QUEUE(update_lenchk_screen_00,iptr) ;
	}
	FILL_PROC_QUEUE(update_lenchk_screen_01,NULL) ;

	FILL_PROC_QUEUE(update_lenchk_screen_02,NULL) ;

}



#include <math.h>
#include <mem.h>
#define LENCHK_BG1				LIGHTGREEN_USR
#define LENCHK_TEXT 			BLACK_USR
#define LENCHK_DOT				BLACK_USR
#define LENCHK_DASHED_LINE		LIGHTRED_USR
#define LENCHK_SOLID_LINE		BLUE_USR

#define SUSPEND_LENCHK			0x3
#define FREE_RUN_DIALOG_LENCX	(RUN_MSG_LX+26)
#define FREE_RUN_DIALOG_LENCY	(RUN_MSG_LY+RUN_MSG_H-10)
#define FREE_RUN_DIALOG_LENCW	(200)
#define FREE_RUN_DIALOG_LENCH	(40) 


void bar256_proc(void *dptr)
{
	GET_PARAMETERS_int5(x1,y1,x2,y2,c) ;
	bar256(x1,y1,x2,y2,c) ;
}
void bar256_q(SCRN_XY x1,SCRN_XY y1 , SCRN_XY x2,SCRN_XY y2 , COLOR_T c)
{
	//計算1ms的繪圖區
	int yinc = SCRN_W/(x2-x1)*45 ;
	int *iptr ;
	bool end_flag =false ;
	for(int i=0 ; !end_flag ; i++){
		int t = y1+(i+1)*yinc-1 ;
		if(t >= y2){
			t= y2 ;
			end_flag = true ;
		}
		SAVE_PARAMETERS_int5(x1,y1+i*yinc , x2 , t,c) ;
		FILL_PROC_QUEUE(bar256_proc,iptr) ;
	}
}
void line256(int x1,int y1,int x2,int y2 , int c)
{
	GrLine(x1,y1,x2,y2,c) ;
}
unsigned char status_lenchk()
{
	unsigned char far *base =BASE_ADDR	;
	return(*(base+0xca0)) ;
}
void putdot(int x,int y )
{
	int x1= FREE_RUN_DIALOG_LENCX ;
	int y1= FREE_RUN_DIALOG_LENCY ;
	putpixel(x1+x,y1+(20-y),LENCHK_DOT) ;
	putpixel(x1+x,y1+(20-y)+1,LENCHK_DOT) ;

	//putpixel(x+1,y,color) ;
	//putpixel(x+1,y+1,color) ;

}
void ini_lenchk_chart_00(void *dptr)
{
	dptr=dptr ;
	int x1 ,y1 ;
	int x2,y2 ;
	x1= FREE_RUN_DIALOG_LENCX ;
	x2= x1+FREE_RUN_DIALOG_LENCW ;
	y1= FREE_RUN_DIALOG_LENCY ;
	y2= y1+FREE_RUN_DIALOG_LENCH  ;
	bar256(x1,y1,x2,y2,LENCHK_BG1) ;
}
void ini_lenchk_chart_01(void *dptr)
{
#if COMPILER == DJ_COMPILER
	dptr=dptr ;
	int x1 ,y1 ;
	int x2,y2 ;
	x1= FREE_RUN_DIALOG_LENCX ;
	x2= x1+FREE_RUN_DIALOG_LENCW ;
	y1= FREE_RUN_DIALOG_LENCY ;
	y2= y1+FREE_RUN_DIALOG_LENCH  ;
	GrLineOption lop ;
	lop.lno_color=LENCHK_SOLID_LINE ;
	lop.lno_width=NORM_WIDTH ;
	lop.lno_pattlen=0 ;
	int midy= (y1+y2)/2 ;
	int off= (x2-x1)/4 ;
	GrCustomLine(x1,y1,x1,y2,&lop) ;
	GrCustomLine(x2,y1,x2,y2,&lop) ;
	GrCustomLine( x1,midy,x2,midy,&lop) ;
	GrCustomLine(x1,y1,x2,y1,&lop) ;
	GrCustomLine(x1,y2,x2,y2,&lop) ;
	lop.lno_pattlen=2 ;
	lop.lno_dashpat=(unsigned char *)"\1\1" ;
	for(int i=0 ; i < 3 ;i++){
		GrCustomLine(x1+(i+1)*off,y1,x1+(i+1)*off,y2,&lop) ;
	}
	lop.lno_color=LENCHK_DASHED_LINE ;
	lop.lno_pattlen=2 ;
	lop.lno_dashpat=(unsigned char *)"\5\2" ;
	GrCustomLine(x1,midy+12,x2,midy+12,&lop) ;
	GrCustomLine(x1,midy-12,x2,midy-12,&lop) ;

	//PrintColorStringLine(x1-24,midy-12-12,LENCHK_DASHED_LINE,"+OV") ;
	//PrintColorStringLine(x1-11,midy-6,LENCHK_SOLID_LINE,"0") ;
	//PrintColorStringLine(x1-24,midy+12-0,LENCHK_DASHED_LINE,"-OV") ;

	PUTCHIN(x1-23,midy-12-9,187-OFF_PATTERN,LENCHK_DASHED_LINE) ;
	PUTCHIN(x1-11,midy-8,188-OFF_PATTERN,LENCHK_SOLID_LINE) ;
	PUTCHIN(x1-23,midy+12-6,189-OFF_PATTERN,LENCHK_DASHED_LINE) ;
#endif
#if COMPILER == BC_COMPILER
	dptr=dptr ;
	int x1 ,y1 ;
	int x2,y2 ;
	x1= FREE_RUN_DIALOG_LENCX ;
	x2= x1+FREE_RUN_DIALOG_LENCW ;
	y1= FREE_RUN_DIALOG_LENCY ;
	y2= y1+FREE_RUN_DIALOG_LENCH  ;
	setcolor(LENCHK_SOLID_LINE) ;
	setlinestyle(SOLID_LINE,0x00,1) ;
	int midy= (y1+y2)/2 ;
	int off= (x2-x1)/4 ;
	line(x1,y1,x1,y2) ;
	line(x2,y1,x2,y2) ;
	line( x1,midy,x2,midy) ;
	line(x1,y1,x2,y1) ;
	line(x1,y2,x2,y2) ;
	setlinestyle(DOTTED_LINE,0x0,1) ;
	for(int i=0 ; i < 3 ;i++){
		line(x1+(i+1)*off,y1,x1+(i+1)*off,y2) ;
	}
	setcolor(LENCHK_DASHED_LINE) ;
	setlinestyle(DASHED_LINE,0x00,1) ;
	line(x1,midy+12,x2,midy+12) ;
	line(x1,midy-12,x2,midy-12) ;

	//PrintColorStringLine(x1-24,midy-12-12,LENCHK_DASHED_LINE,"+OV") ;
	//PrintColorStringLine(x1-11,midy-6,LENCHK_SOLID_LINE,"0") ;
	//PrintColorStringLine(x1-24,midy+12-0,LENCHK_DASHED_LINE,"-OV") ;

	PUTCHIN(x1-23,midy-12-9,187-OFF_PATTERN,LENCHK_DASHED_LINE) ;
	PUTCHIN(x1-11,midy-8,188-OFF_PATTERN,LENCHK_SOLID_LINE) ;
	PUTCHIN(x1-23,midy+12-6,189-OFF_PATTERN,LENCHK_DASHED_LINE) ;
#endif

}
void plot_lenchk(void *dptr)
{
	dptr=dptr ;
	int i=(int)(lenchk_buf.dialog_idx-lenchk_buf.base_idx) ;
	for(long ii=lenchk_buf.dialog_idx ; ii < lenchk_buf.cur_idx ; ii++,i++){
		switch(screen_state)
		{
		case MAIN_SCREEN :
			putdot(i ,(int)lenchk_buf.buf[i]) ;
			break ;
		case LENCHK_SCREEN:
			putdot_LENCHK(i ,(int)lenchk_buf.buf[i]) ;
			break ;
		}
	}
	lenchk_buf.dialog_idx = lenchk_buf.cur_idx-1 ;
}
void update_lenchk()
{
	unsigned char far *base =BASE_ADDR	;
	static int degree=0 ;
	unsigned char status ;
	float value ;
	if((status=status_lenchk()) == SUSPEND_LENCHK){
		lenchk_buf.base_idx = lenchk_buf.cur_idx = 0 ;
		for(int i=0 ; i < 17 ; i++){
			lenchk_buf.acc_no[i]= 0 ;
		}
		lenchk_buf.total=lenchk_buf.total2=0 ;
	}
	else{
		// 顯示檢長結果
		switch(status)
		{
		case 0x7:
			value = -18 ;
			break ;
		case 0x8:
		case 0x9:
			value = -(*(base+0xca8)/10) ;
			break ;
		case 0x10 :
			value =0 ;
			break ;
		case 0x11 :
		case 0x12 :
			value = (*(base+0xca8)/10) ;
			break ;
		case 0x13 :
			value = 18 ;
			break ;
		case 0xdf:
			value= 20.0*sin(degree/90.0) ;
			degree+=7 ;
			break ;
		default:
			value = 20 ;
			break ;
		}
		int off = (int)(lenchk_buf.cur_idx-lenchk_buf.base_idx) ;
		
		EPT_IDX(off, lenchk_buf.buf);
		EPT_IDX((int)((value+20)/(40.0/16)+0.5), lenchk_buf.acc_no);
		lenchk_buf.buf[off]= value ;
		lenchk_buf.cur_idx++ ;
		lenchk_buf.total = lenchk_buf.total+value ;
		lenchk_buf.total2= lenchk_buf.total2+ value*value ;
		lenchk_buf.acc_no[(int)((value+20)/(40.0/16)+0.5)]+=1 ;
		bool refresh = false ;
		if(off == (MAX_LENCHK_BUF-1)){
			// 儲存 lenchk_buf.buf[0..MAX_LENCHK_BUF/2-1]到XMS,
			// 且移動lenchk_buf.buf[MAX_LENCHK_BUF/2..MAX_LENCHK_BUF-1]到lenchk_buf.buf[0..MAX_LENCHK_BUF/2-1]
			refresh= true ;

#if (SAVE_LENCHK_XMS)
			XMSMoveblock((MAX_LENCHK_BUF/2)*sizeof(float),0x0,(char far *)lenchk_buf.buf,lenchk_buf.xmshandle,
			(char far *)(lenchk_buf.base_idx*sizeof(float))) ;
#endif

			memcpy(lenchk_buf.buf,lenchk_buf.buf+(MAX_LENCHK_BUF/2),(MAX_LENCHK_BUF/2)*sizeof(float)) ;
			lenchk_buf.base_idx+= (MAX_LENCHK_BUF/2);
			lenchk_buf.dialog_idx=lenchk_buf.base_idx ;
		}

		if(refresh){
			switch(screen_state)
			{
			case MAIN_SCREEN :
				FILL_PROC_QUEUE(ini_lenchk_chart_00,NULL) ;
				FILL_PROC_QUEUE(ini_lenchk_chart_01,NULL) ;
				break ;
			case LENCHK_SCREEN:
				FILL_PROC_QUEUE(d_curve_bg_lenchk,NULL) ;
				break ;
			}
		}
		FILL_PROC_QUEUE(plot_lenchk,NULL) ;
	}
	if(screen_state== LENCHK_SCREEN){
		FILL_PROC_QUEUE(update_lenchk_screen,NULL) ;
	}
}

