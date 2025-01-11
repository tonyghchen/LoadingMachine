#include "header.h"

void timer_phase(int hz) ;

FILE *fp_array[]= {
	 NULL,NULL,NULL,NULL,NULL, 
	 NULL,NULL,NULL,NULL,NULL, 
	 NULL,NULL,NULL,NULL,NULL, 
	 NULL,NULL,NULL,NULL,NULL, 
};

#define LEN_fp_array    (sizeof(fp_array)/sizeof(FILE *))
//timer中斷+圖形顯示(測試圖形顯示時,仍可以接受中斷,同時可以測試繪圖速度)
// 0x100--->24970
// 0x200--->49924
#if 1
void test_timer0()
{
	TimerTicks.timer =0 ;
	struct TIMER lTimerTicks ;
    timer_phase(TIMER0_HZ) ;
	lTimerTicks=TimerTicks ;
	for(unsigned long i=0;i < 0x400 ;i++){
		bar256(0,0,(SCRN_W-1),(SCRN_H-1),(int)(i%16)) ;
	}
	Sprintf("TimerTick %ll %ll",TimerTicks.timer,lTimerTicks.timer) ;
}
#endif



#if FILE_ACCESS
FILE *Fopen(char *filename , char *md)
{
	FILE *fp ;
	fp= fopen(filename,md) ;
	// save fp to fp_array 
	for(int i=0 ; i < LEN_fp_array ; i++){
		if(fp_array[i] == NULL){
			
			EPT_BC(i, fp_array) ;
			fp_array[i]= fp ;
			break ;
		}
	} 
	
	return(fp) ;
}
void Fclose(FILE *fp)
{
	bool flag = true ;
	// delete fp from fp_array
	for(int i=0 ; i < LEN_fp_array ; i++){
		if(fp_array[i] == fp){
			
			EPT_BC(i, fp_array) ;
			fp_array[i]= NULL ;
			flag= false ;
			break ;
		}
	}
	if(flag){
		//發生錯誤
		save_record("delete unopen fp!!") ;
	}
	fclose(fp) ;
}
bool check_file_access(void)
{
	for(int i=0 ; i < sizeof(fp_array)/sizeof(FILE *) ; i++){
		if(fp_array[i] != NULL)return(false) ;
	}
	return(true) ;
}
#endif





#if (DEBUG_RELEASE == DEBUG)
int test_endian()
{
	// pc --->little -endian
	// 68000 --->big -endian
	unsigned short i= 0x1234 ;
	unsigned char *b =(unsigned char *) & i ;
	unsigned short j= ((*b) << 8) +(*(b+1)) ;
	if( j == i){
		return(1) ;// big-endian
	}
	else{
		return(0) ; //little-endian
	}
}
void unit_test(void )
{
	SDWORD A[100],B[100] ;
	SDWORD unit ;
	for(int i=0 ; i < 100 ; i++){
		unit= i*10 ;
		TO_GRID(AXIS_X,unit) ;
		Grid2Unit(AXIS_X,unit) ;
		
		EPT_BC(i, A) ;
		A[i]= unit ;
	}
	for(int i=0 ; i < 100 ; i++){
		unit= i*10 ;
		TO_GRID(AXIS_X,unit) ;
		Grid2Unit_exact(AXIS_X,unit) ;
		
		EPT_BC(i, B) ;
		B[i]= unit ;
	}
}
void Probe(int i)
{
	int x= i%10 ;
	int y = i /10 ;
	bar256(x*40, y*40 , (x+1)*40-3 , (y+1)*40-3,RED_USR) ;
}
void test_ascii1_19(void)
{
	char buf[50] ;
	char *ptr=buf ;
	for(int i=1 ; i < 20 ; i++){
		*ptr++=i ;
		*ptr++=' ' ;
	}
	*ptr='\0' ;
	Sprintf(buf) ;
}

void test_trace_y()
{
	RollOn=0 ;
	FORCE_PROC_QUEUE ;
	int start,len ;
	if(cnt_trace_y !=0){
		buf_trace_y[cnt_trace_y-1].ePos= ReadAbsPos(AXIS_Y) ;
	}
	else{
		buf_trace_y[MAX_TRACE_Y-1].ePos= ReadAbsPos(AXIS_Y) ;
	}
	if(ov_trace_y){
		start= cnt_trace_y ;
		len =MAX_TRACE_Y  ;
	}
	else{
	    start=0 ;
		len= cnt_trace_y ;
	}
	for(int i=0 ; i < len ; i++){ //尾
		Sprintf("設定值 = %+05d  差距_2016 = %+05d ,起始_2016=%05u , 結束_2016= %05u",buf_trace_y[start].mov ,buf_trace_y[start].ePos -buf_trace_y[start].sPos ,buf_trace_y[start].sPos,buf_trace_y[start].ePos) ;
		start++ ;
		if(start ==MAX_TRACE_Y){
			start=0 ;
		}
	}
}
void  test_x()
{
#if 0
	Sprintf("org_loc=%d",(WORD)Read2016(AXIS_X)) ;
	Set3701(AXIS_X,0,30,100,100,true) ;
	mDelay(1000) ;
	Set3701(AXIS_X,0,420,1400,1400,true) ;
	mDelay(1000) ;
	Set3701(AXIS_X,0,30,100,100,true) ;
	mDelay(1000) ;
	Set3701(AXIS_X,0,200,400,400,true) ;
	mDelay(1000) ;
	Set3701(AXIS_X,0,30,100,100,true) ;
	mDelay(1000) ;
	Set3701(AXIS_X,0,270,900,900,true) ;
	mDelay(1000) ;
	Set3701(AXIS_X,1,420,1400,1400,true) ;
	mDelay(1000) ;
	Sprintf("last_loc=%d",(WORD)Read2016(AXIS_X)) ;
#endif
}
void test_axis(BYTE axis)
{

//測試
	char tbuf[10000] ;
#if 0
	Set3701(axis, PLUS_SIGN, 0x10000L, 9000L,40000L,true);
#endif
	int i;
	for(i=0 ; i < 10000 ; i++){
		tbuf[i]= *STATUS_ADDR(axis);
		if(tbuf[i] == ST51_OVERFLOW)break ;
		mDelay(1) ;
	}
}
FILE * test_fopen()
{
	FILE* fp= FOPEN("D:\\config.dat","rb") ;
	return(fp) ;
}
void test_const()
{
	int a[100];
	int i=0 ;
	a[i++]= INL ;
	a[i++]= INM ;
	a[i++]= INH ;
	a[i++]= OUTL ;
	a[i++]= OUTM ;
	a[i++]= OUTH ;
	a[i++]= PINTS ;
	a[i++]= PINTC ;
}
void DumpFloppy(int name)
{
#if 0	
	char CopyBuf[25] ;
	FILE *fp1 ;
	sprintf(CopyBuf, "A:\\CNC_%02d.DAT", name%100);
	fp1= FOPEN(CopyBuf,"rb") ;
	fread(&ProgBuf[0],MAX_PROG_LINE * sizeof(ProgType_t),1,fp1);
	Adjust_ProgBuf(&ProgBuf[0],MAX_PROG_LINE) ;
	FCLOSE(fp1) ;
	sprintf(CopyBuf,"A:\\CNC_%02d.TXT", name%100);
	fp1= FOPEN(CopyBuf,"wb") ;
	DumpFile(fp1) ;
	FCLOSE(fp1) ;
#endif
}








void DispAbsPos()
{
	BYTE sign[MAX_AXIS] ;
	DWORD axis_val[MAX_AXIS] ;
	for(int axis=0 ; axis < MachineStatus.axis_no; axis++ ){
		
		
		EPT_BC(axis,	sign) ;
		EPT_BC(axis, axis_val) ;
		EPT_BC(axis, MachineStatus.sign) ;
		EPT_BC(axis, MachineStatus.axis_val) ;
		
		sign[axis]= MachineStatus.sign[axis] ;
		axis_val[axis]=MachineStatus.axis_val[axis] ;
		MachineStatus.sign[axis]= PLUS_SIGN ;
		MachineStatus.axis_val[axis]= BinToBcd(6,ReadAbsPos(axis)) ;
	}
	DispCurAxis(1) ;
	while(exe_proc_queue()) ;
	for(int axis=0 ; axis < MachineStatus.axis_no; axis++ ){
		
		EPT_BC(axis, MachineStatus.sign) ;
		EPT_BC(axis, MachineStatus.axis_val) ;
		MachineStatus.sign[axis]= sign[axis] ;
		MachineStatus.axis_val[axis]= axis_val[axis] ;
	}
	sDelay(2) ;
}

void test_stopmotor()
{
}
#endif
