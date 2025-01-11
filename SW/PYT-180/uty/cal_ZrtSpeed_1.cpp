DWORD cal_ZrtSpeed(LOG_AXIS laxis , short speed_factor)
{
	uint32 basespd ;
	if(speed_factor == 8){
		basespd= BcdToBin(3,MachineStatus.wZeroSpd2[laxis.idx]) ;
		if(basespd == 0){
			basespd=1 ;
		}
	}
	else{
		basespd= BcdToBin(3,MachineStatus.wZeroSpd[laxis.idx]) ;
		if(basespd == 0){
			basespd=1 ;
		}
		basespd*=speed_factor ;
	}		
	//�H10�鬰���,�p���Ƥγt�� 1��= 60*1000ms
	return((1000L*60/basespd)*10)  ;	
}
