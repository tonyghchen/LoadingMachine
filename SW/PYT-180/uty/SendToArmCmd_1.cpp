bool SendToArmCmd(BYTE cmd,BYTE card)
{
	DWORD  i;
	bool err ;
	for(i=0	; i< LOOP_TIMES	; i++){
		if(FILL_PC_CMD_CHK_ARM_CMD(cmd,card)) break ;
	}
	err	= ((i>=LOOP_TIMES)?	true: false);
	for(i=0	; i< LOOP_TIMES	; i++){
		if(FILL_PC_CMD_CHK_ARM_CMD(0,card)) break ;
	}
	return(err)	;
}
