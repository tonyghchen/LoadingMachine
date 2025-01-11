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
		DispStrLine_q(EDIT_BOX_LX2+AIR_LOC_POS*ASC_CHAR_W, EDIT_BOX_LY+2, YELLOW_USR, RED_USR, DispBuf);
	}
	else{
		char *buf  ;




#if 1
		buf= isSHAXX? (char *)AIR_STR_EN550:(char *)AIR_STR ;
		DispStrLine_q(EDIT_BOX_LX2+AIR_LOC_POS*ASC_CHAR_W,
					  EDIT_BOX_LY+2, RGB8_16(36,68,124), GRAY_14, buf);
#else
		if(!AirTblOn){
			buf= isEN550? (char *)AIR_STR_EN550:(char *)AIR_STR ;
			DispStrLine_q(EDIT_BOX_LX2+AIR_LOC_POS*ASC_CHAR_W,
						  EDIT_BOX_LY+2, MAGENTA_USR, GRAY_14, buf);
		}
		else{
			buf= (uint8 *)((MachineStatus.language) ? AirScrn[1]:AirScrn[0]) ;
			DispStrLine_q(EDIT_BOX_LX2+(AIR_LOC_POS-3)*ASC_CHAR_W,
						  EDIT_BOX_LY+2, MAGENTA_USR, GRAY_14, (uint8 *)buf);
		}
#endif






	}

	if( set ){
		wDosMem(pc_base+OUTL, MachineStatus.man_air) ;
		enable_all_touch() ;
	}



#if DDRAW
	while(exe_proc_queue()) ;
#endif
}

