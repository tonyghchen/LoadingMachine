#include "nsdelay.h"

void InitializeTimer()
{
	asm mov  dx,43h    // �q�D0 ���W�����p�ɼҦ�2
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
	asm mov  dx,43h    // �q�D0 ���W�����p�ɼҦ�3
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
	asm cli 		   // �T��w�餤�_
		asm mov  dx,20h    // �w�}PIC ocw3
		asm mov  al,0Ah    // �n�DŪ��IRR
		asm out  dx,al
		asm in	 al,dx	  // Ū��IRR
		asm mov  cl,al	  //�s��bCL
		
		asm mov  al,00h    //����p�ɾ�0
		asm out  43h,al

		
		asm in	 al,40h   //Ū���p�ƭȪ��C�줸��
		asm mov  bl,al	  // ...�üȦs��BL
		asm in	 al,40h   //Ū���p�ƭȪ����줸��
		asm mov  bh,al	  // ...�üȦs��BH
		asm not  bx 	  //�p�ƭȥѻ����ର���W
		
		asm in	 al,21h    // Ū��PIC��IMR
		asm mov  ch,al	  // ...�üȦs��CH
		asm mov  al,0ffh  //�B�n�Ҧ��w�餤�_
		asm out  21h,al
		
		asm xor  ax,ax	  // Ū��BIOS�ɶ��Ȫ��C�줸��
		asm mov  es,ax
		asm mov  dx,es:[046ch]
		asm mov  al,ch	  //�٭�IMR
		asm out  21h,al
		asm sti 		  //�P��w�餤�_
		
		
		asm test cl,1	//�p�ƭȴ������0 (���_�o��INT 8) ?
		asm jz	loc_1	// �Y�S��,�h��loc_1
		asm or	bh,bh	 //�p�ƭ� >0xff ?
		asm jnz loc_1	 //�p�G�O����,����
		asm inc dx		 //�_�h���W�ɶ��Ȫ����줸��
loc_1:
	asm mov  ax,bx	 // �Ǧ^�`���(DX:AX)
}
// ���1��
unsigned long minTimerSet(unsigned int d){
	return (ReadTimer() + (unsigned long) (d) *NOCNT_1S*60) ;
}
// ���1��
unsigned long sTimerSet(unsigned int d){
	return (ReadTimer() + (unsigned long) (d) *NOCNT_1S) ;
}
// ���0.01��
unsigned long hTimerSet(unsigned int h){
	return (ReadTimer() +(unsigned long)(h)*NOCNT_1HS) ;
}
// ���0.1��
unsigned long dTimerSet(unsigned int d){
	return (ReadTimer() + (unsigned long) (d) *NOCNT_1DS) ;
}
// ���0.001��
unsigned long mTimerSet(unsigned int m){
	return (ReadTimer() +(unsigned long) (m) *NOCNT_1MS) ;
}
void sDelay(unsigned int sec){ //����sec ��
	unsigned long timeout= sTimerSet(sec) ;
	while(!IsTimeUp(timeout)) ;
}
void dDelay(unsigned int ds){ //����ds�ӤQ�����@ ��
	unsigned long timeout= dTimerSet(ds) ;
	while(!IsTimeUp(timeout)) ;
}
void hDelay(unsigned int hs){ //����hs�Ӧʤ����@ ��
	unsigned long timeout= hTimerSet(hs) ;
	while(!IsTimeUp(timeout)) ;
}
bool IsTimeUp(unsigned long h){
	return(((ReadTimer()-h)&0x80000000L)? false :true) ;
}
void mDelay(unsigned int ms){ //����ms�Ӥd�����@ ��
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
