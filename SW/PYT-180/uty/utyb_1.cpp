void SystemOn_q()
{
}
void SystemOn_proc(void *dptr)
{
	dptr=dptr ;
//	SystemOn() ;
}
void SystemOff_q()
{
}
void SystemOff_proc(void *dptr)
{
	dptr=dptr ;
//	SystemOff() ;
}
uint16 StrLen_S (Cptr str)
{
	uint16 len;
	uint16 nof =0 ;

	for( len=0; *str;  ){
		if(*str == CHG_PAL){
			nof++ ;
			if(nof%2){
#ifdef REAL_COLOR
				str+=5 ;
#else				
				str+=3 ;
#endif				
			}
			else{
				str++ ;
			}
		}
		else{
			str++ ;
			len++ ;
		}
	}

	return( len );
}
void Filter_CHG_PAL()
{

}
