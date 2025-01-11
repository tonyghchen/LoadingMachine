
/*void OnScrn(void)
{
	if(!ScrnState){
		union REGS r;
		if(MachineStatus.BIOSVendor== 'A'){ //American Megatrend Inc.   ¤jPC
			r.x.ax=0x120d ;
			r.x.bx=0x114 ;
			r.h.cl=2 ;    //Bit 1 set to 1
			int86(0x10,&r,&r) ;
		}
		else if(MachineStatus.BIOSVendor== 'P'){ //Phoenix Technologies, LTD  ¤pPC
    	    r.x.ax=0x4F10 ;
    	    r.x.bx=0x0001 ;   //  Video On
			int86(0x10,&r,&r) ;
		}
	}
	
	ScrnState= true ;

}
void OffScrn(void)
{
	union REGS r;
	if(MachineStatus.BIOSVendor== 'A'){
		r.x.ax=0x120d ;
		r.x.bx=0x114 ;
		r.h.cl=0 ;    //Bit 1 set to 0
		int86(0x10,&r,&r) ;
	}
	else if(MachineStatus.BIOSVendor== 'P'){
	 	r.x.ax=0x4F10 ;
        r.x.bx=0x0401 ;   //  Video Off
		int86(0x10,&r,&r) ;
	}
	
	ScrnState=false ;
}
void SystemOff (void)
{
	OffScrn() ;
}
void SystemOn (void)
{
	OnScrn() ;
}
*/

