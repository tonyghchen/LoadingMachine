
#include "int64.h"

INT64::INT64()
{
}
void Mul(unsigned long a,unsigned long b) 
{
	unsigned long ah,al,bh,bl ,albl,albh,ahbl,ahbh;
	
	al = a & 0xffff ;
	ah = a >> 16 ;
	bl = b & 0xffff ;
	bh = b >> 16 ;
	albl=al*bl ;
	albh= al*bh ;
	ahbl= ah*bl ;
	ahbh=ah*bh ;
	unsigned p1 = albl ;
	unsigned long t2 = albl >> 16 ;
	unsigned long carry=0 ;
	t2 += albh ;
	if(t2 < albh){
		carry+= 0x10000 ;
	}
	t2 += ahbl ;
	if(t2 < ahbl){
		carry+=0x10000 ;
	} 
	unsigned p2= t2 ;
	t2 >>= 16 ;
	t2 += (ahbh+carry) ;
	hi=t2 ;
	lo = p2 ;
	lo <<=16 ;
	lo+=p1 ;	
}
void Mul(unsigned long a,unsigned b) 
{
}
void Div(unsigned long a) 
{
}
void Div(unsigned a) 
{
}
unsigned long HiLong() 
{
}
unsigned long LoLong() 
{
}
