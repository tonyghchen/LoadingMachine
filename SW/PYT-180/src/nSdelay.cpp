#include "nsdelay.h"

void InitializeTimer()
{
	asm mov  dx,43h    // 通道0 欲規劃為計時模式2
		asm mov  al,34h
		asm out  dx,al
		asm mov  dx,40h
		asm xor  al,al
		asm out  dx,al
		asm nop
		asm out  dx,al
}
void RestoreTimer()
{
	asm mov  dx,43h    // 通道0 欲規劃為計時模式3
		asm mov  al,36h
		asm out  dx,al
		asm mov  dx,40h
		asm xor  al,al
		asm out  dx,al
		asm nop
		asm out  dx,al
}
unsigned long ReadTimer()
{
	asm cli 		   // 禁止硬體中斷
		asm mov  dx,20h    // 定址PIC ocw3
		asm mov  al,0Ah    // 要求讀取IRR
		asm out  dx,al
		asm in	 al,dx	  // 讀取IRR
		asm mov  cl,al	  //存放在CL
		
		asm mov  al,00h    //閂住計時器0
		asm out  43h,al

		
		asm in	 al,40h   //讀取計數值的低位元組
		asm mov  bl,al	  // ...並暫存於BL
		asm in	 al,40h   //讀取計數值的高位元組
		asm mov  bh,al	  // ...並暫存於BH
		asm not  bx 	  //計數值由遞減轉為遞增
		
		asm in	 al,21h    // 讀取PIC的IMR
		asm mov  ch,al	  // ...並暫存於CH
		asm mov  al,0ffh  //遮罩所有硬體中斷
		asm out  21h,al
		
		asm xor  ax,ax	  // 讀取BIOS時間值的低位元組
		asm mov  es,ax
		asm mov  dx,es:[046ch]
		asm mov  al,ch	  //還原IMR
		asm out  21h,al
		asm sti 		  //致能硬體中斷
		
		
		asm test cl,1	//計數值曾遞減至0 (有否發生INT 8) ?
		asm jz	loc_1	// 若沒有,則至loc_1
		asm or	bh,bh	 //計數值 >0xff ?
		asm jnz loc_1	 //如果是的話,結束
		asm inc dx		 //否則遞增時間值的高位元組
loc_1:
	asm mov  ax,bx	 // 傳回常整數(DX:AX)
}
// 單位1分
unsigned long minTimerSet(unsigned int d){
	return (ReadTimer() + (unsigned long) (d) *NOCNT_1S*60) ;
}
// 單位1秒
unsigned long sTimerSet(unsigned int d){
	return (ReadTimer() + (unsigned long) (d) *NOCNT_1S) ;
}
// 單位0.01秒
unsigned long hTimerSet(unsigned int h){
	return (ReadTimer() +(unsigned long)(h)*NOCNT_1HS) ;
}
// 單位0.1秒
unsigned long dTimerSet(unsigned int d){
	return (ReadTimer() + (unsigned long) (d) *NOCNT_1DS) ;
}
// 單位0.001秒
unsigned long mTimerSet(unsigned int m){
	return (ReadTimer() +(unsigned long) (m) *NOCNT_1MS) ;
}
void sDelay(unsigned int sec){ //延遲sec 秒
	unsigned long timeout= sTimerSet(sec) ;
	while(!IsTimeUp(timeout)) ;
}
void dDelay(unsigned int ds){ //延遲ds個十分之一 秒
	unsigned long timeout= dTimerSet(ds) ;
	while(!IsTimeUp(timeout)) ;
}
void hDelay(unsigned int hs){ //延遲hs個百分之一 秒
	unsigned long timeout= hTimerSet(hs) ;
	while(!IsTimeUp(timeout)) ;
}
bool IsTimeUp(unsigned long h){
	return(((ReadTimer()-h)&0x80000000L)? false :true) ;
}
void mDelay(unsigned int ms){ //延遲ms個千分之一 秒
	unsigned long timeout= mTimerSet(ms) ;
	while(!IsTimeUp(timeout)) ;
}
float ELAAPSED_MS(long long t0,long long t1){
		return(ELAAPSED_CNT(t0,t1)/float(NOCNT_1MS)) ;
}
long long ELAAPSED_CNT(long long t0,long long t1){
	return(((t1)-(t0))) ;
}
long long tt ;
void init_interval_time()
{
	tt= ReadTimer() ;
}
float interval_time()
{
	return((ReadTimer()-tt)/float(NOCNT_1MS)) ;
}
