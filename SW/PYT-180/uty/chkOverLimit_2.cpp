void rd_AllStatus()
{
	for(int axis=0 ; axis < MachineStatus.axis_no ; axis++){
		pDispBuf += BcdToStrBuf(2, rDosMem(STATUS_ADDR(axis)) , pDispBuf);
		Fill_pDispBuf("  ");
	}
}
bool chkOverLimit(uint8 axis,uint8 dir,uint8 man_hand)
{
	uint32  dincval;

	if( MachineStatus.motor[axis] ){
		dincval = (man_hand==0)? BcdToBin(3, MachineStatus.manval[axis]):BcdToBin(3, MachineStatus.handval[axis]);
		if( axis==AXIS_Y && MachineStatus.y_scale )  dincval *= 10;
		int32 newval= BcdToBin(8,MachineStatus.axis_val[axis] ,MachineStatus.sign[axis]);
		int32 tt= (isPLUS_SIGN(dir)?dincval:-(int32)dincval) ; 
		newval += tt ;
		if(MachineStatus.Unit[axis]== 1){ //¨¤«×
			while(newval >=3600){
				newval-=3600 ; 
			}
			while(newval <=-3600){
				newval +=3600 ;
			}
		}
		int32 min= BcdToBin(8,MachineStatus.Min[axis] ,MachineStatus.Min_sign[axis]) ;
		int32 max= BcdToBin(8,MachineStatus.Max[axis] ,MachineStatus.Max_sign[axis]) ;
		if(((max != 99999)&&(newval > max)) || ((min != -99999)&&(newval < min))){ 
			DispMsgWin_q(-1, -1, WAR_WIN, 	"¶W ¹L ³n Åé ·¥ ­­!",
											" Over software Limit");
			WAIT_NEW_KEY();
			ClrMsgWin_q();								
			return(true) ;
		}
	 	else{
	 		return(false) ;
	 	}
	}
	return(true);
}
