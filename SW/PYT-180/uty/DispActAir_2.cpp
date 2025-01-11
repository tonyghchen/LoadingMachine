void DispActAir (short set)
{
	short i;

	if( CursorLoc == MAN_AIR_CURSOR ){
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
		buf= (char *)AIR_STR ;
		DispStrLine_q(EDIT_BOX_LX2+AIR_LOC_POS*ASC_CHAR_W,
					  EDIT_BOX_LY+2, MAGENTA_USR, GRAY_14, buf);
#else
		if(!AirTblOn){
			buf= AIR_STR ;
			DispStrLine_q(EDIT_BOX_LX2+AIR_LOC_POS*ASC_CHAR_W,
						  EDIT_BOX_LY+2, MAGENTA_USR, GRAY_14, buf);
		}
		else{
			buf= (BYTE *)AirScrn[idx_language] ;
			DispStrLine_q(EDIT_BOX_LX2+(AIR_LOC_POS-3)*ASC_CHAR_W,
						  EDIT_BOX_LY+2, MAGENTA_USR, GRAY_14, (BYTE *)buf);
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
