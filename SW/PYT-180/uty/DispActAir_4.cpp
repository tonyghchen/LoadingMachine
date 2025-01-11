void DispActAir (short set)
{
	short i;

	if( CurCursor.ID == MAN_AIR_CURSOR ){
		INI_DISP_BUF();
		for( i=0; i < 8; i++ ){
			if( (MachineStatus.man_air>>i)&0x01 ) pDispBuf += BinToStrBuf(1, i+1, pDispBuf);
			else								  pDispBuf += StrCpy(pDispBuf, " ");
		}
		FILL_DISP_BUF(0);
		DispStrLine_q(EDIT_BOX_LX2+AIR_LOC_POS*ASC_CHAR_W[0], EDIT_BOX_LY+2, YELLOW_USR, RED_USR, DispBuf);
	}
	else{
		char *buf  ;
		buf= (isEN550 || isEN508)? (char *)AIR_STR_EN550:(char *)AIR_STR ;
		DispStrLine_q(EDIT_BOX_LX2+AIR_LOC_POS*ASC_CHAR_W[0],
					  EDIT_BOX_LY+2, MAGENTA_USR, GRAY_14, buf);
	}

	if( set ){
		wDosMem(pc_base+OUTL, MachineStatus.man_air) ;
		enable_all_touch() ;
	}


#if DDRAW
	while(exe_proc_queue()) ;
#endif
}

