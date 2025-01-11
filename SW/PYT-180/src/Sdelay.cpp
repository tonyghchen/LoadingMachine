#include "pro\sdelay.h"
unsigned long tt ;


////////////////////////////////////////////////////////////////////////////////
//
//�۰�format �_�l�I
//

void InitializeTimer()
{
	asm mov  dx,43h ;			// �q�D0 ���W�����p�ɼҦ�2
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
	asm mov  dx,43h	;			// �q�D0 ���W�����p�ɼҦ�3
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
	asm cli ;					// �T��w�餤�_
	asm mov  dx,20h  ;			// �w�}PIC ocw3
	asm mov  al,0Ah  ;			// �n�DŪ��IRR
	asm out  dx,al;
	asm in	 al,dx	;			// Ū��IRR
	asm mov  cl,al	;			//�s��bCL

	asm mov  al,00h ;			//����p�ɾ�0
	asm out  43h,al;


	asm in	 al,40h	;			//Ū���p�ƭȪ��C�줸��
	asm mov  bl,al	;			// ...�üȦs��BL
	asm in	 al,40h	;			//Ū���p�ƭȪ����줸��
	asm mov  bh,al	;			// ...�üȦs��BH
	asm not  bx ;				//�p�ƭȥѻ����ର���W

	asm in	 al,21h;			// Ū��PIC��IMR
	asm mov  ch,al	;			// ...�üȦs��CH
	asm mov  al,0ffh;			//�B�n�Ҧ��w�餤�_
	asm out  21h,al;

	asm xor  ax,ax	;			// Ū��BIOS�ɶ��Ȫ��C�줸��
	asm mov  es,ax;
	asm mov  dx,es:[046ch];
	asm mov  al,ch	;			//�٭�IMR
	asm out  21h,al;
	asm sti ;					//�P��w�餤�_


	asm test cl,1	;			//�p�ƭȴ������0 (���_�o��INT 8) ?
	asm jz	loc_1	;			// �Y�S��,�h��loc_1
	asm or	bh,bh	;			//�p�ƭ� >0xff ?
	asm jnz loc_1	;			//�p�G�O����,����
	asm inc dx		;			//�_�h���W�ɶ��Ȫ����줸��
loc_1:
	asm mov  ax,bx	;			// �Ǧ^�`���(DX:AX)
	asm mov word ptr l,ax ;		// low word of l
	asm mov  word ptr l+2,dx ;	// high word of l
	return(l) ;
}
// ���1��
struct SDELAY sTimerSet(unsigned int d){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts + (unsigned long) (d) *NOCNT_1S ;
	return (s) ;
}
// ���0.01��
struct SDELAY hTimerSet(unsigned int h){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts+(unsigned long)(h)*NOCNT_1HS ;
	return (s) ;
}
// ���0.1��
struct SDELAY dTimerSet(unsigned int d){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts + (unsigned long) (d) *NOCNT_1DS ;
	return (s) ;
}
// ���0.001��
struct SDELAY mTimerSet(unsigned int m){
	struct SDELAY s ;
	s.ts = ReadTimer();
	s.te =s.ts + (unsigned long) (m) *NOCNT_1MS ;
	return (s) ;
}
void sDelay(unsigned int sec){ //����sec ��
	struct SDELAY timeout= sTimerSet(sec) ;
	while(!IsTimeUp(timeout)) ;
}
void dDelay(unsigned int ds){ //����ds�ӤQ�����@ ��
	struct SDELAY timeout= dTimerSet(ds) ;
	while(!IsTimeUp(timeout)) ;
}
void hDelay(unsigned int hs){ //����hs�Ӧʤ����@ ��
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
void mDelay(unsigned int ms){ //����ms�Ӥd�����@ ��
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
		//��t1 < t0 ,�N��counter�w�g�o��overflow
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