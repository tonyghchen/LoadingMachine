int	Chk3701No (void)
{
	static int	rno	;
	static bool once=false ;
	if(once)return rno ;
	once=true ;


	in_Chk3701No=true ;
	{
		MachineStatus.axis_nox[0]= rDosMem(pc_base+ARM_NUM_OF_AXIS) ;
		if(MachineStatus.axis_nox[0] > 8){														//NEW-16
			ARM_CARD_TYPE=1 ;																	//NEW-16
			CardNo=1 ;																			//NEW-16
			MachineStatus.axis_no= MachineStatus.axis_nox[0] ;									//NEW-16
		}
		else{
			ARM_CARD_TYPE=2 ;
			MachineStatus.axis_nox[1]= rDosMem(pc_base+0x400+ARM_NUM_OF_AXIS) ;
			if(MachineStatus.axis_nox[1] > 8){
				MachineStatus.axis_nox[1]=0 ;
				CardNo=1 ;
			}
			else{
				CardNo=2 ;
			}
			MachineStatus.axis_no= MachineStatus.axis_nox[0]+MachineStatus.axis_nox[1] ;
		}
 		for(uint8 laxis =0 ; laxis < MachineStatus.axis_no; laxis++){
			MachineStatus.p3701[laxis]=1	;
		}
		
	}
	rno=MachineStatus.axis_no ;
	if(	MachineStatus.axis_no >	MAX_AXIS ){
		MachineStatus.axis_no =	MAX_AXIS;
	}
	if(	MachineStatus.axis_no <	2 )	 MachineStatus.axis_no = 2;
	// 依據軸數將沒有馬達的旗標關閉
	for(uint8 axis=MachineStatus.axis_no	; axis	< MAX_AXIS ; axis++){
		MachineStatus.motor[axis]=	0 ;
	}
	{
		SendToArmCmd(RESET_ALL)	; // reset all
		DelayCount(500);
	}
	in_Chk3701No=false ;
	return(rno)	;
}
