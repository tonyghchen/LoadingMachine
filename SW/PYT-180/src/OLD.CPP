#include "header.h"




#if !TOUCH_STOP_SPIN
bool th_chk_AB(unsigned no, unsigned touch)
{
	if(no == 0){
		return(ABC3200[0] && ((touch >= 8) && (touch <= (8+3)))) ;
	}
	else{
		return(ABC3200[1] && ((touch >= (8+4)) && (touch <= (8+4+3)))) ;
	}
}
#endif

#if GAP_MDY
//配合YGAP修正Y的移動值
void YGAP_MDY(DWORD &mov, BYTE dir)
{
		if(dir != YLOC_dir){
			mov += (BcdToBin(2, MachineStatus.YGAP)*1) ;
			YLOC_dir=dir ;
		}
}



void AGAP_MDY(BYTE axis,BYTE dir)
{
	if(CHK_ROTATE_A(axis)){
		if(dir != ALOC_dir){
			if((OFFSET_Y_dir(dir)& 0x7f)== PLUS_SIGN){
				AmdyY = -(BcdToBin(2, MachineStatus.AGAP)) ;
			}
			else{
				AmdyY = (BcdToBin(2, MachineStatus.AGAP)) ;
			}
			ALOC_dir=dir ;
		}
	}
}

void AMDYY(DWORD &mov,BYTE dir)
{
		if(AmdyY){
			mov = mov + (((dir & 0x7f)== PLUS_SIGN)? AmdyY : -AmdyY) ;
			AmdyY=0 ;
		}
}
#endif






void ReadFileAck (BYTE isok, DWORD off,	WORD size, BYTE	*data)
{
	BYTE *dst;
	WORD i;

	FileRWAck	= isok|0x80;
	FileOffAck	= off;
	FileSizeAck	= size;
	dst	= (BYTE	*)FileRWBuf;
	for( i=0; i	< size;	i++	){
		*dst++ = *data++;
	}
}
void WriteFileAck (BYTE	isok, DWORD	off, WORD size)
{
	FileRWAck	= isok|0x80;
	FileOffAck	= off;
	FileSizeAck	= size;
}
BYTE PrnWrAck;
void PrinterAck	(BYTE isok)
{
	PrnWrAck = isok|0x80;
}

//其他地方沒有呼叫
void DispEditBox (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= EDITBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= EDIT_BOX_LX;
	ws.ly				= EDIT_BOX_LY;
	ws.rx				= EDIT_BOX_RX;
	ws.ry				= EDIT_BOX_RY;

	DrawWindow(&ws);
	DrawScrollVBar(VSCROLL_LX, VSCROLL_LY, VSCROLL_RX, VSCROLL_RY, 0);
}
//其他地方沒有呼叫
void DispHelpBox (void)
{
	WinStyle_t ws;

	DefaultButtonStyle(&(ws.frame));
	ws.frame.main_col	= HELPBOX_MAIN_BCOLOR;
	ws.frame.type		= 1;
	ws.lx				= HELP_BOX_LX;
	ws.ly				= HELP_BOX_LY;
	ws.rx				= HELP_BOX_RX;
	ws.ry				= HELP_BOX_RY;

	DrawWindow(&ws);
}











#if	TPROGBUF
void SendProgLine_q (WORD idx, BYTE *buf)
{
	WORD len;

	len	= StrLen(buf);


	BYTE *dptr=  (BYTE *)farmalloc(1*sizeof(WORD)+len+1+LEN_CHKSUM) ;
	BYTE *tptr= dptr ;
	SAVE_VAL(WORD , idx); 
	SAVE_STRING(buf,len) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(SEND_PROG_proc,tptr) ;
}

void SendProgList (void)
{
	WORD i,	q;

	for( q=i=0;	i <	PROG_BUF_LINES;	i++	){
		MakeProgLine(i,	(ProgType_t	*)(ProgBuf+i));



#if	1
		GetProgLine(i, DispBuf);
#else
		SendProgLine(i,	DispBuf);
#endif




		if(	!ProgBuf[i].gcode )		  q	= 1;
		if(	q && i >= PAGE_LINES-1 )  break;
	}
	LastLine_test= i-1;
	CurProgLine_test=YProgoff_test=0 ;
	DispProg(CurProgLine_test,YProgoff_test,PAGE_LINES)	;
}

void DispCurProgList (short	line)
{
	short start, y_off;
	
	start =	CurProgLine_test-YProgoff_test ;
	if(( start <= line)	&&(line	 < (start+PAGE_LINES)) ){
		DispProgLine_test(YProgoff_test,CurProgLine_test,0);
		CurProgLine_test= line ;
		YProgoff_test= line-start ;
		DispProgLine_test(YProgoff_test,CurProgLine_test,1);
	}
	else{
		start =	line - (PAGE_LINES-1)/2;
		if((start+(PAGE_LINES-1)) >	LastLine_test){
			start =	LastLine_test-(PAGE_LINES-1) ;
		}
		YProgoff_test= CurProgLine_test-start ;
		CurProgLine_test= line ;
		DispProg(start,YProgoff_test,PAGE_LINES) ;
	}
}
void SEND_PROG_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD , idx); 
	CHK_CHKSUM
	GetProgLine(idx, dptr);
	farfree(ptr) ;
}
void DispProgList_proc(void *ptr)
{
	BYTE *dptr= (BYTE *)ptr ;
	GET_VAL(WORD,start_idx) ;
	GET_VAL(WORD,y_off) ;
	GET_VAL(WORD,lines) ;
	CHK_CHKSUM

	DispProg(start_idx, y_off, lines);
	farfree(ptr) ;
}
		SendProgList();
		SendProgList();
#endif


#if 0
	if(no_DispCurAirList){
		int first_line = CurAirLine-YAiroff ;
		if( (first_line <= buf_DispCurAirList[rd_DispCurAirList].line)&&
		    (buf_DispCurAirList[rd_DispCurAirList].line < first_line+PAGE_LINES)
		  ){
			DISP_CUR_AIRLINE(0,buf_DispCurAirList[rd_DispCurAirList].line-
							 first_line,buf_DispCurAirList[rd_DispCurAirList].line ,
							  ((buf_DispCurAirList[rd_DispCurAirList].cmd == SET_AIR)||
							  (buf_DispCurAirList[rd_DispCurAirList].cmd == SET_TOUCH))
			) ;
		}
		else{
			CurAirLine=buf_DispCurAirList[rd_DispCurAirList].line ; YAiroff=0 ;
			DispPageAir(0) ;
		}
		rd_DispCurAirList++ ;
		if(rd_DispCurAirList >= NO_DispCurAirList){
			 rd_DispCurAirList=0 ;
		}
		DISABLE() ;
		no_DispCurAirList--;
		ENABLE() ;
	}
#endif
