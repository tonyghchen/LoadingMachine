#include "header.h"
#include <stdio.h>	// FILE 
#include <string.h>    // strlen()
#include <unistd.h>     //__file_exists()
#define LEN_Intbuf   1000000
char Intbuf[LEN_Intbuf] ;
int ridx_Intbuf=0 ;
int widx_Intbuf=0 ;
FILE *fp_Intbuf ;

void chk_endIntbuf()
{
	if(widx_Intbuf >= (LEN_Intbuf-200)){
		Intbuf[widx_Intbuf]='e' ;
		widx_Intbuf=0 ;    // ring buffer
	}
}
void strPrintf(char buf[]) 
{
	Intbuf[widx_Intbuf++]='s' ;
	for(int i=0 ;buf[i]!='\0' ;i++){
		Intbuf[widx_Intbuf++]=buf[i] ;
	}
	Intbuf[widx_Intbuf++]='\0' ;
	chk_endIntbuf() ;
}
void xdPrintf(char code ,  int num) 
{
	Intbuf[widx_Intbuf++]=code ;
	int *pp=(int *)&Intbuf[widx_Intbuf] ;
	*pp=num ;
	widx_Intbuf+=sizeof(int) ;
	chk_endIntbuf() ;
}
void dPrintf(int num) 
{
	xdPrintf('d' , num) ;
}
void dPrintf(char *buf , int num)
{
	strPrintf(buf) ;
	xdPrintf('d',num) ;
}
void xPrintf(int num) 
{
	xdPrintf('x' , num) ;
}
void xPrintf(char *buf , int num)
{
	strPrintf(buf) ;
	xdPrintf('x' , num) ;
}
void uPrintf(int num) 
{
	xdPrintf('u' , num) ;
}
void uPrintf(char *buf , int num)
{
	strPrintf(buf) ;
	xdPrintf('u' , num) ;
}
void fPrintf(float num) 
{
	Intbuf[widx_Intbuf++]='f' ;
	float  *pp=(float *)&Intbuf[widx_Intbuf] ;
	*pp=num ;
	widx_Intbuf+=sizeof(float) ;
	chk_endIntbuf() ;
}
void fPrintf(char *buf , float num) 
{
	strPrintf(buf) ;
	fPrintf(num) ;
}
void Open_IntPrintf()
{
	char buf[10] ;
	for(int i=0 ; i < 100 ; i++){
		sprintf(buf,"%02d.txt",i) ;
		if(!__file_exists(buf))break ;
	}
	fp_Intbuf=fopen(buf,"w") ;
}
void Close_IntPrintf()
{
	fclose(fp_Intbuf) ;
}
void BgPrintf()
{
	int *pp ;
	float *pf ;
	unsigned int *pu ;
	char buf[100] ;
	int loc_newline ;
	if(ridx_Intbuf !=widx_Intbuf){
		switch(Intbuf[ridx_Intbuf++]){
			case 'd' :
				pp= (int *)&Intbuf[ridx_Intbuf] ;
				sprintf(buf, "%d ,",*pp) ;
				Sprintf_next(buf) ;
				fprintf(fp_Intbuf,buf) ;
				ridx_Intbuf+=sizeof(int) ;
				break ;
			case 'x' :
				pp= (int *)&Intbuf[ridx_Intbuf] ;
				sprintf(buf,"%x ,",*pp) ;
				Sprintf_next(buf) ;
				fprintf(fp_Intbuf,buf) ;
				ridx_Intbuf+=sizeof(int) ;
				break ;
			case 'u' :
				pu= (unsigned int *)&Intbuf[ridx_Intbuf] ;
				sprintf(buf,"%u ,",*pu) ;
				Sprintf_next(buf) ;
				fprintf(fp_Intbuf,buf) ;
				ridx_Intbuf+=sizeof(unsigned int) ;
				break ;
			case 'f' :
				pf= (float *)&Intbuf[ridx_Intbuf] ;
				sprintf(buf,"%f ,",*pf) ;
				Sprintf_next(buf) ;
				fprintf(fp_Intbuf,buf) ;
				ridx_Intbuf+=sizeof(float) ;
				break ;
			case 's' :
				sprintf(buf,&Intbuf[ridx_Intbuf]) ;
				loc_newline= strlen(buf)-1 ;
				fprintf(fp_Intbuf,buf) ;
				if(buf[loc_newline]== '\n'){
					buf[loc_newline]='\0' ;
					Sprintf(buf) ;
				}
				else{
					Sprintf_next(buf) ;
				}
				ridx_Intbuf +=(strlen(&Intbuf[ridx_Intbuf])+1) ;
				break ;
			case 'e':
				ridx_Intbuf=0 ;
				break ;
		}
	}
}

