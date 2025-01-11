int	Chk3701No (void)
{
	static int	rno	;
	static bool once=false ;
	if(once)return rno ;
	once=true ;


	in_Chk3701No=true ;
	if(axis_type ==	INTEL8051_AXIS){
//����3/6���O����
//	0:�S��checksum���b���							,�N��N
// 	1:��checksum���b���(for Set3701)					,�N��C 
//	3:��checksum���b���(for Set3701&set3701ManMov)	,�N��D  
//  �̷ӫ��w��checksum�覡�U�R�O,�b�d�o�S���^��			,�N��E
//	0xff:�S���b���									,�N��- 
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
			if(	MachineStatus.p3701[axis] == 1 ){ //�H�̫�@�b���b��
				  MachineStatus.axis_no=axis+1;
			}
		}
	}
	else{
		MachineStatus.axis_no= rDosMem(pc_base+ARM_NUM_OF_AXIS) ;
		for(uint8 axis =0 ; axis < MachineStatus.axis_no; axis++){
			MachineStatus.p3701[axis]=1	;
		}
		//�ˬdARM��type----
		// ARM_CARD_TYPE =2 ----�}��
		// ARM_CARD_TYPE =0 ----�s�F
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
	// �̾ڶb�ƱN�S�����F���X������
	for(uint8 axis=MachineStatus.axis_no	; axis	< MAX_AXIS ; axis++){
		MachineStatus.motor[axis]=	0 ;
	}
	if(axis_type ==	INTEL8051_AXIS){
//		StopMotor() ;//�s620
	}
	else{
		SendToArmCmd(RESET_ALL)	; // reset all
		DelayCount(500);
	}
	in_Chk3701No=false ;
	return(rno)	;
}
