uint8 RD_PC_CMD(BYTE card)
{
	if(ARM_CARD_TYPE==1){												//NEW-16
		card=0 ; //只有一組命令											//NEW-16
	}																	//NEW-16
	uint8 cmd= rDosMem(pc_base+card*0x400+PC_CMD_RAM) ;	
	uint8 inv= rDosMem(pc_base+card*0x400+INV_PC_CMD) ;
	if((cmd+inv)== 0xff){
		return(cmd) ;
	}
	else{
		return(0x55) ;
	}
}
uint8 WR_PC_CMD(BYTE cmd , BYTE card)
{
	if(ARM_CARD_TYPE==1){												//NEW-16
		card=0 ;														//NEW-16
	}                                                             		//NEW-16
	wDosMem(pc_base+card*0x400+PC_CMD_RAM,cmd) ;          
   BYTE inv = 0xff-cmd;
	wDosMem(pc_base+card*0x400+INV_PC_CMD,inv) ;          
}
bool FILL_PC_CMD_Cards(BYTE cmd)
{	
	bool ok[2]={false,false} ;
	bool allok ;
	long i=0 ;
	do{
		for(uint8 card=0 ; (card <CardNo); card++){
			if(!ok[card]){
				WR_PC_CMD(cmd,card) ;
			}
		}
		allok=true ;
		for(uint8 card=0 ; (card <CardNo) ; card++){
			if(!ok[card]){
				ok[card]=(RD_PC_CMD(card)==cmd) ;
				allok = allok&&ok[card] ;
			}
		}
		i++ ;
	}
	while(!allok&& (i < TIMEOUT_FILL_PC_CMD)) ;
	return(allok) ;
}
bool FILL_PC_CMD(BYTE cmd,bool *CardStatus)
{	
	bool ok[2]={false,false} ;
	bool allok ;
	long i=0 ;
	do{
		for(uint8 card=0 ; (card <CardNo); card++){
			if(!ok[card]&&CardStatus[card]){
				WR_PC_CMD(cmd,card) ;
			}
		}
		allok=true ;
		for(uint8 card=0 ; (card <CardNo) ; card++){
			if(!ok[card]&&CardStatus[card]){
				ok[card]=(RD_PC_CMD(card)==cmd) ;
				allok = allok&&ok[card] ;
			}
		}
		i++ ;
	}
	while(!allok&& (i < TIMEOUT_FILL_PC_CMD)) ;
	return(allok) ;
}
bool FILL_PC_CMD(BYTE cmd,uint8 card)
{	
	bool ok[2]={false,false} ;
	bool allok ;
	long i=0 ;
	do{
		if(!ok[card]){
			WR_PC_CMD(cmd,card) ;
		}
		allok=true ;
		if(!ok[card]){
			ok[card]=(RD_PC_CMD(card)==cmd) ;
			allok = allok&&ok[card] ;
		}
		i++ ;
	}
	while(!allok&& (i < TIMEOUT_FILL_PC_CMD)) ;
	return(allok) ;
}
bool FILL_PC_CMD_CHK_ARM_CMD(uint8 cmd,BYTE card)
{
 uint32 j ;
	for( j = 0 ; (j < LOOP_TIMES/RESEND_CNT_ARM) ; j++){
		FILL_PC_CMD(cmd,card) ;
		if(CHK_ARM_CMD(cmd,card))break ;
	}
   PHY_AXIS phy_axis={0} ;
	CHK_RW3701Err((j==(LOOP_TIMES/RESEND_CNT_ARM)),phy_axis,"set3701-3",pc_base+ARM_CMD_RAM,rDosMem(pc_base+ARM_CMD_RAM),0)	;
	return(!(j==(LOOP_TIMES/RESEND_CNT_ARM))) ;
}
bool FILL_PC_CMD_CHK_ARM_CMD(uint8 cmd,bool *CardStatus)
{
 uint32 j ;
	for( j = 0 ; (j < LOOP_TIMES/RESEND_CNT_ARM) ; j++){
		FILL_PC_CMD(cmd,CardStatus) ;
      if(CHK_ARM_CMD(cmd,CardStatus))break ;
	}
   PHY_AXIS phy_axis={0} ;
	CHK_RW3701Err((j==(LOOP_TIMES/RESEND_CNT_ARM)),phy_axis,"set3701-3",pc_base+ARM_CMD_RAM,rDosMem(pc_base+ARM_CMD_RAM),0)	;
	return(!(j==(LOOP_TIMES/RESEND_CNT_ARM))) ;
}
bool FILL_PC_CMD_CHK_ARM_CMD(uint8 cmd)
{
 uint32 j ;
	for( j = 0 ; (j < LOOP_TIMES/RESEND_CNT_ARM) ; j++){
		FILL_PC_CMD_Cards(cmd) ;
		if(CHK_ARM_CMD(cmd))break ;
	}
   PHY_AXIS phy_axis={0} ;
	CHK_RW3701Err((j==(LOOP_TIMES/RESEND_CNT_ARM)),phy_axis,"set3701-3",pc_base+ARM_CMD_RAM,rDosMem(pc_base+ARM_CMD_RAM),0)	;
	return(!(j==(LOOP_TIMES/RESEND_CNT_ARM))) ;
}
uint8 RD_ARM_CMD(BYTE card)
{
	if(ARM_CARD_TYPE==1){												//NEW-16 
		card=0 ;                                                        //NEW-16
	}																	//NEW-16
	uint8 cmd= rDosMem(pc_base+card*0x400+ARM_CMD_RAM) ;  
	uint8 inv= rDosMem(pc_base+card*0x400+INV_ARM_CMD) ;	
	if((cmd+inv)== 0xff){
		return(cmd) ;
	}
	else{
		return(0x55) ;
	}
}
bool CHK_ARM_CMD(uint8 cmd,BYTE card)
{								
	bool ok[]={false,false} ;
	bool allok ;
	uint32 i=0;
	do{
		allok=true ;
		if( !ok[card]){
			uint8 rcmd=RD_ARM_CMD(card) ;
			if((rcmd == cmd)||(rcmd == ARM_RESEND) ){
				ok[card]=true ;
			}
			else{
				ok[card]=false ;
			}
			allok = allok && ok[card] ;
		}
		i++ ;
	}
	while((i< RESEND_CNT_ARM)&&(!allok)) ;
	return(allok) ;
}
bool CHK_ARM_CMD(uint8 cmd)
{		
	bool ok[]={false,false} ;
	bool allok ;
	uint32 i=0;
	do{
		allok=true ;
		for(uint8 card =0 ; card < CardNo ; card++){
			if( !ok[card]){
				uint8 rcmd=RD_ARM_CMD(card) ;
				if((rcmd == cmd)||(rcmd == ARM_RESEND) ){
					ok[card]=true ;
				}
				else{
					ok[card]=false ;
				}
				allok = allok && ok[card] ;
			}
		}
		i++ ;
	}
	while((i< RESEND_CNT_ARM)&&(!allok)) ;
	return(allok) ;
}
bool CHK_ARM_CMD(uint8 cmd,bool *CardStatus)
{		
	bool ok[]={false,false} ;
	bool allok ;
	uint32 i=0;
	do{
		allok=true ;
		for(uint8 card =0 ; card < CardNo ; card++){
			if((Set3701_ARM.CardStatus[card]) && !ok[card]){
				uint8 rcmd=RD_ARM_CMD(card) ;
				if((rcmd == cmd)||(rcmd == ARM_RESEND) ){
					ok[card]=true ;
				}
				else{
					ok[card]=false ;
				}
				allok = allok && ok[card] ;
			}
		}
		i++ ;
	}
	while((i< RESEND_CNT_ARM)&&(!allok)) ;
	return(allok) ;
}
