int	Chk3701No (void)
{
	static int	rno	;
	static bool once=false ;
	if(once)return rno ;
	once=true ;


	in_Chk3701No=true ;
	if(axis_type ==	INTEL8051_AXIS){
//紀錄3/6號板版本
//	0:沒有checksum的軸控制器							,代號N
// 	1:有checksum的軸控制器(for Set3701)					,代號C 
//	3:有checksum的軸控制器(for Set3701&set3701ManMov)	,代號D  
//  依照指定的checksum方式下命令,軸卡卻沒有回應			,代號E
//	0xff:沒有軸控制器									,代號- 
		for(uint8 axis=0; axis <	MAX_AXIS; axis++ ){
			if(AxisChkSum[axis]!=0xff){
				Set3701(axis,0,0,0,0,true,0) ;
				if((AxisChkSum[axis]&0x1) && RW3701Err){
					RW3701Err =0 ;
					AxisChkSum[axis]=0 ;
					Set3701(axis,0,0,0,0,true,0) ;
					VersionDate[VersionDate_buf_start+axis]='E'	;
				}
				MachineStatus.p3701[axis]=RW3701Err?0:1	;
				RW3701Err=0	;
			}
			else{
				MachineStatus.p3701[axis]=0	;
			}
		}
		MachineStatus.axis_no=0 ;
		for(uint8 axis=0; axis < MAX_AXIS; axis++ ){
			if(	MachineStatus.p3701[axis] == 1 ){ //以最後一軸為軸數
				  MachineStatus.axis_no=axis+1;
			}
		}
	}
	else{
		MachineStatus.axis_no= rDosMem(pc_base+ARM_NUM_OF_AXIS) ;
		for(uint8 axis =0 ; axis < MachineStatus.axis_no; axis++){
			MachineStatus.p3701[axis]=1	;
		}
		//檢查ARM的type----
		// ARM_CARD_TYPE =2 ----開創
		// ARM_CARD_TYPE =0 ----新達
		ARM_CARD_TYPE=0 ;
#if 1
		Set3701(AXIS_X,0,0,0,0,true,0) ;
		RW3701Err=0 ;
		Set3701(AXIS_X,0,0,0,0,true,0) ;
		if(RW3701Err){
			ARM_CARD_TYPE=2 ;
			RW3701Err=0 ;
		}
#endif
		ChkOverFlow[AXIS_X]=false ;
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
	if(axis_type ==	INTEL8051_AXIS){
//		StopMotor() ;//新620
	}
	else{
		SendToArmCmd(RESET_ALL)	; // reset all
		DelayCount(500);
	}
	in_Chk3701No=false ;
	return(rno)	;
}
