#include "header.h"

void StopMotor (uint8 axis)
{
// 	if(MachineStatus.motor[axis]){
// 			wDosMem(pc_base+DriverClear,BITmask[7-axis]) ;
// 			StopDDA(axis) ;
// 			wDosMem(pc_base+DriverClear,(uint8)0) ;
// 	}
}

bool Chk3701 (uint8	axis)
{
// 		update_run_DDA() ;
// 		return(DDATbl[axis].totalms ==0) ;
    return (false);
}
void Clr2016s(short axis)
{
		//DISABLE() ;
		ReadAxes(axis) ;
		FeedbackCnt[axis]=0 ;
		//ENABLE() ;
}

void Wait3701 (uint8	axis)
{
	while( 1 ){
		if(	Chk3701(axis))
			break;
		CHECK_RESET_update(true);
		//�ˬd�~�����O�_������
		//ProcessKeyswap() ;//�s620
	}
}
uint32 dReadAbsPos (uint8 axis)
{
// 	uint8 bl, bh;
// 	uint16 w,w2;
// 	uint32 d1,d2;
// 	if(NewH){
// 		d1=FeedbackCnt[axis] ;
// 	}
// 	
// 	if(	axis ==	AXIS_X ){
// 		if(BMOTORGRID(AXIS_X)==4000 && !MachineStatus.X_Encoder){ //620 Xencorder(�ѽX��)�[�J�P�_�O�_��4000��(�ª�)
// 			d1=(SDWORD)d1*X_2016_Y0/X_2016_Y1 ;

// 		}
// 		w=d1 ;
// 		if((w >= (lx_loc +XGRID.g2))|| ((w < XGRID.g10)&& (lx_loc > XGRID.g3950))){
// 			x_dir = 0 ; // ����
// 			lx_loc= w ;
// 		}
// 		else if((lx_loc >= XGRID.g2) && (w <= (lx_loc-XGRID.g2))){
// 			x_dir=1 ; //����
// 			lx_loc= w ;
// 		}
// 	}
// 	if(MachineStatus.ABDir[axis]){ //���F��AB�^�«H���n�Ϭ�
// 		d1=(~d1)+1; //�ϦV	
// 	}
// 	return(	d1 );
}
// int Stopaddr[]={0x100,0,0x101,0x102,0x103,0x104,0x105} ;
void EnableHomeInt (uint8 axis,uint8 mask , uint8 type )
{
// 	if(MachineStatus.motor[axis] ){
// 		if((type == ENABLE_INT) || (type == ENABLE_INT_STOP)){
// 			//wDosMem(pc_base+Stopaddr[axis],(uint8)axis);
// 		}
// 		if((type == ENABLE_INT_STOP) || (type == ENABLE_STOP)){
// 			wDosMem(pc_base+Stopaddr[axis],(uint8)mask) ;
// 		}
// 	}
}
void EnableHomeInt (uint8 axis,uint8 type )	//NEWH
{
// 	if(	MachineStatus.motor[axis] ){
// 		if((type == ENABLE_INT) || (type == ENABLE_INT_STOP)){
// 			wDosMem(pc_base+0x114, (uint8)(Para51[0] &= ~(BITmask[7-axis]))) ;
// 		}
// 		if((type == ENABLE_INT_STOP)|| (type == ENABLE_STOP)){
// 			wDosMem(pc_base+0xfd, (uint8)(Para51[1] |= BITmask[7-axis])) ;
// 		}
// 	}
}
void DisableHomeInt ()
{
	wDosMem(pc_base+0xfd,  Para51[1] = 0) ;
	wDosMem(pc_base+0x114, Para51[0] = 0xff) ;
}
void DisableHomeInt (uint8 axis,uint8 mask)
{
// 	wDosMem(pc_base+Stopaddr[axis],(uint8)0) ;
}
void DisableHomeInt	(uint8 axis)
{
// 	if(	MachineStatus.motor[axis] ){
// 		if(NewH){
// 			wDosMem(pc_base+0xfd, (uint8)(Para51[1] &= ~(BITmask[7-axis]))) ;
// 			wDosMem(pc_base+0x114, Para51[0] |= BITmask[7-axis]) ;
// 		}
// 	}	
}

void update_sc_kernel()
{	
	uint8 new_adc ;
	if(axis_type == INTEL8051_AXIS){
		new_adc = READ_ADC(AXIS_X);
		wDosMem(pc_base+BaseMotorADC[0] , (uint8)0xff);
	}
	else{
		new_adc= rDosMem(pc_base+0xe0) ;
	}

	
	//static bool lflag_ServoCutter=false ;
	//if( MachineStatus.set8254 || (abs(MachineStatus.adc_level-new_adc)>=2)||(flag_ServoCutter!=lflag_ServoCutter) ){
	//	if(flag_ServoCutter){
	//		new_adc = 255 ;
	//	}
	//	lflag_ServoCutter=flag_ServoCutter ;
	//	MachineStatus.adc_level = new_adc;
//
	//	uint16 sc = adc2sc(new_adc);
	//	printf_adc(new_adc,sc) ; //5216�Ҧ��|�L�X��
	//					
	//	nSet8254(sc);
	//	MachineStatus.set8254 = 0;
	//}
	//else{
	//	static int cnt =0 ;
	//	cnt++ ;
	//	if(cnt >1000){
	//		cnt=0 ;
	//	}
	//}
}

