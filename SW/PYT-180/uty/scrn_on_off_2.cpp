void CRT_OFF()
{
	outportb(0x3c4,0x00);
	outportb(0x3c5,0x00);

	ScrnState=false ;
}
void CRT_ON()
{
	outportb(0x3c4,0x00);
	outportb(0x3c5,0x03);
	
	ScrnState= true ;
}
void SystemOff (void)
{
	CRT_OFF();
	int MaxX= GrMaxX() ;
	int MaxY= GrMaxY() ;
	if((scrn_buf=GrCreateContext(MaxX,MaxY,NULL,NULL))!=NULL){
   		GrBitBlt(scrn_buf,0,0,NULL,0,0,MaxX-1,MaxY-1,GrWRITE) ;
		bar256(0,0,MaxX-1,MaxY-1,BLACK_USR) ;
		GrSetContext(scrn_buf) ;
   	}
	//while(1){	//關機不正常
	//	DispMsgWin_q(-1, -1, MSG_WIN,Powernotoff[1],Powernotoff[0],Powernotoff[2]);
	//	FORCE_PROC_QUEUE ;
	//}
}
void SystemOn (void)
{
	CRT_ON();
	if(scrn_buf != NULL){
   		GrSetContext(NULL) ;
		GrContext *gc1= scrn_buf ;
   		GrBitBlt(NULL,0,0,gc1,0,0,gc1->gc_xmax,gc1->gc_ymax,GrWRITE) ;
   		GrDestroyContext(gc1) ;
   		scrn_buf=NULL ;
   	}
}
