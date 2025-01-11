#include "pro\sdelay.h"
unsigned long tt ;


////////////////////////////////////////////////////////////////////////////////
//
//自動format 起始點
//

void InitializeTimer()
{
	asm mov  dx,43h ;			// 通道0 欲規劃為計時模式2
	asm mov  al,34h ;
	asm out  dx,al ;
	asm mov  dx,40h ;
	asm xor  al,al ;
	asm out  dx,al ;
	asm nop ;
	asm out  dx,al ;
}
void RestoreTimer()
{
	asm mov  dx,43h	;			// 通道0 欲規劃為計時模式3
	asm mov  al,36h ;
	asm out  dx,al ;
	asm mov  dx,40h ;
	asm xor  al,al ;
	asm out  dx,al ;
	asm nop ;
	asm out  dx,al ;
}
unsigned long ReadTimer()
{
	unsigned long l ;
	asm cli ;					// 禁止硬體中斷
	asm mov  dx,20h  ;			// 定址PIC ocw3
	asm mov  al,0Ah  ;			// 要求讀取IRR
	asm out  dx,al;
	asm in	 al,dx	;			// 讀取IRR
	asm mov  cl,al	;			//存放在CL

	asm mov  al,00h ;			//閂住計時器0
	asm out  43h,al;


	asm in	 al,40h	;			//讀取計數值的低位元組
	asm mov  bl,al	;			// ...並暫存於BL
	asm in	 al,40h	;			//讀取計數值的高位元組
	asm mov  bh,al	;			// ...並暫存於BH
	asm not  bx ;				//計數值由遞減轉為遞增

	asm in	 al,21h;			// 讀取PIC的IMR
	asm mov  ch,al	;			// ...並暫存於CH
	asm mov  al,0ffh;			//遮罩所有硬體中斷
	asm out  21h,al;

	asm xor  ax,ax	;			// 讀取BIOS時間值的低位元組
	asm mov  es,ax;
	asm mov  dx,es:[046ch];
	asm mov  al,ch	;			//還原IMR
	asm out  21h,al;
	asm sti ;					//致能硬體中斷


	asm test cl,1	;			//計數值曾遞減至0 (有否發生INT 8) ?
	asm jz	loc_1	;			// 若沒有,則至loc_1
	asm or	bh,bh	;			//計數值 >0xff ?
	asm jnz loc_1	;			//如果是的話,結束
	asm inc dx		;			//否則遞增時間值的高位元組
loc_1:
	asm mov  ax,bx	;			// 傳回常整數(DX:AX)
	asm mov word ptr l,ax ;		// low word of l
	asm mov  word ptr l+2,dx ;	// high word of l
	return(l) ;
}
// 單位1秒
struct SDELAY sTimerSet(unsigned int d){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts + (unsigned long) (d) *NOCNT_1S ;
	return (s) ;
}
// 單位0.01秒
struct SDELAY hTimerSet(unsigned int h){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts+(unsigned long)(h)*NOCNT_1HS ;
	return (s) ;
}
// 單位0.1秒
struct SDELAY dTimerSet(unsigned int d){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts + (unsigned long) (d) *NOCNT_1DS ;
	return (s) ;
}
// 單位0.001秒
struct SDELAY mTimerSet(unsigned int m){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts + (unsigned long) (m) *NOCNT_1MS ;
	return (s) ;
}
void sDelay(unsigned int sec){ //延遲sec 秒
	struct SDELAY timeout= sTimerSet(sec) ;
	while(!IsTimeUp(timeout)) ;
}
void dDelay(unsigned int ds){ //延遲ds個十分之一 秒
	struct SDELAY timeout= dTimerSet(ds) ;
	while(!IsTimeUp(timeout)) ;
}
void hDelay(unsigned int hs){ //延遲hs個百分之一 秒
	struct SDELAY timeout= hTimerSet(hs) ;
	while(!IsTimeUp(timeout)) ;
}
int IsTimeUp(struct SDELAY h){
	if(h.ts < h.te){
		return(ReadTimer() >= h.te) ;
	}
	else{
		unsigned long t= ReadTimer() ;
		if(t >= h.ts){
			return(0) ;
		}
		else{
			return(t >= h.te) ;
		}

	}
}
void mDelay(unsigned int ms){ //延遲ms個千分之一 秒
	struct SDELAY timeout= mTimerSet(ms) ;
	while(!IsTimeUp(timeout)) ;
}
float ELAAPSED_MS(unsigned long t0,unsigned long t1){
	return(ELAAPSED_CNT(t0,t1)/(float)(NOCNT_1MS)) ;
}
unsigned long ELAAPSED_CNT(unsigned long t0,unsigned long t1){
	if(t1 >= t0){
		return(((t1)-(t0))) ;
	}
	else{
		//當t1 < t0 ,代表counter已經發生overflow
		return(((0xffffffffUL-t0)+1+t1)) ;
	}
}
void init_interval_time()
{
	tt= ReadTimer() ;
}
float interval_time()
{
	return((ReadTimer()-tt)/(float)(NOCNT_1MS)) ;
}