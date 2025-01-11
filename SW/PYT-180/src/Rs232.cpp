/***********
;
;		filename : rs232.c
;		---- assembly io routines for
;
;
;		create date : 89/07/10
;		modify date : 93/11/11
;
;***********/
#include "header.h"
#define COMNO		2
#define ON			1
#define OFF			0
#define RS_BUF_MAX			0x500
#define TR_BUF_MAX			0x50
#define RBR_8250			0
#define THR_8250			0
#define IER_8250			1
#define IIR_8250			2
#define LCR_8250			3
#define MCR_8250			4
#define LSR_8250			5
#define MSR_8250			6
#define DLL_8250			0
#define DLM_8250			1
#define BASED_8259A 		0x20
#define EOI 				0x20
//#define DI		 asm		cli ;
//#define EI		 asm		sti ;

// COM1
int int0c_NewH() 
{	
	static int no =0 ;
	static UC lch ;
	UC ch ;
	//inportb(rs232_base[0] + IIR_8250) ;
	if((inportb(rs232_base[0] + LSR_8250) & 0x01)){
		// have a byte in receiver buffer
		ch = inportb(rs232_base[0] + RBR_8250) ;
		if(no == 0){
			lch=ch ;
			no++ ;
		}
		else{
			no=0 ;
			if((!keylock && !keyswap) || lch==2){
				switch(lch)
				{
					case 0:			
						if(ch ==KEY_DUMMY_RESET){  // reset	key
							SetDriverClear() ;
							Reset =	1;
						}
						if(	((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx)){
							KeyBuf[KeyBufWIdx]= ch ;
							if(KeyBufWIdx+1 >= MAX_KEY_BUF){
								KeyBufWIdx=0;
							}
							else{
								KeyBufWIdx++ ;
							}
						}
						break ;
					case 1:
						break ;
					case 2:
						KeyInput = ch ; 
						KeyLockCHG=true;
						break ;
					case 4://鍵盤會傳前置碼為4,忽略
						break ;
					default:
						lch=ch ;
						no=1 ;
						break ;
				}
			}
		}
	}
}
// COM1
int int0c() 
{
	UC ch ;
	inportb(rs232_base[0] + IIR_8250) ;
	if((inportb(rs232_base[0] + LSR_8250) & 0x01)){
		// have a byte in receiver buffer
		ch = inportb(rs232_base[0] + RBR_8250) ;
		UC tt= (rDosMem(pc_base+INM)) ;
		if( (tt& 0x48) == 0x48){
			//  檢查是否按下 reset key
			fSaveKeyBuf(ch) ;
			if(ch ==  KEY_DUMMY_RESET){
				Reset=1 ;
			}
			// 檢查安全開關是否發生訊號
			if((ch &0xf0) == 0xd0){
				// 安全裝置錯誤回報0xd0+第幾支sensor
				// 安全裝置test回報0xd8+第幾支sensor
				MachineStatus.safe_err = (ch&0x0f) + 1;
			}
			else if((BYTE)((ERP_BufWIdx+1)%MAX_ERP_BUF) !=ERP_BufRIdx){
				
				EPT_IDX(ERP_BufWIdx, ERPBuf);
				ERPBuf[ERP_BufWIdx]= ch ;
				if(ERP_BufWIdx+1 >= MAX_ERP_BUF){
					ERP_BufWIdx=0;
				}
				else{
					ERP_BufWIdx++ ;
				}
			}
		}
	}
	/* check transfer */
	if((cts_flg[0] == ON) && (inportb(rs232_base[0] +LSR_8250) & 0x20)){
		if(tr_buf_len[0]){
			/* send a byte from tr_buf to 8250 */
			outportb(rs232_base[0] +THR_8250 , tr_buf[0][tr_buf_ridx[0]++]) ;
			tr_buf_len[0]-- ;
			if(tr_buf_ridx[0] == TR_BUF_MAX){
				tr_buf_ridx[0] = 0 ;
			}
		}
		else{
			tr_flg[0] = OFF ;
			outportb(rs232_base[0] + IER_8250 , 0x9) ;
		}
	}
	if((inportb(rs232_base[0] + MSR_8250) & 0x10)){
		cts_flg[0]  = ON ;
		if(tr_buf_len[0] ){
			outportb(rs232_base[0] + IER_8250 , 0x0b) ;
			tr_flg[0] = ON ;
		}
	}
	outportb(BASED_8259A ,EOI) ;
}




// COM2
int int0b_NewH() 
{
	UC ch ;
	inportb(rs232_base[1] + IIR_8250) ;
	if((inportb(rs232_base[1] + LSR_8250) & 0x01)){
		// have a byte in receiver buffer
		ch = inportb(rs232_base[1] + RBR_8250) ;
		xPrintf("Com2=",ch) ;
		strPrintf("\n") ;
		static uint8 ReadKeyDate_idx=0;
		
		UC tt= (rDosMem(pc_base+INM)) ;
		
		if (in_ReadAbsMotor){ //讀絕對直馬達_直接進keybuf
			if(	((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx)){
				EPT_IDX(KeyBufWIdx,	KeyBuf);
				KeyBuf[KeyBufWIdx]= ch ;
				if(KeyBufWIdx+1 >= MAX_KEY_BUF){
					KeyBufWIdx=0;
				}
				else{
					KeyBufWIdx++ ;
				}
			}
		}
		else if (ReadKeyDate_flag){ //讀KEY日期				
			EPT_IDX(ReadKeyDate_idx, ReadKeyDate_val);
			if(ReadKeyDate_idx<3)ReadKeyDate_val[ReadKeyDate_idx++]=ch;
			
			if(ReadKeyDate_idx==3){
				ReadKeyDate_flag=false;
				ReadKeyDate_idx=0;			
			}
		}
		else if( ((tt& 0x48) == 0x48)){
			fSaveKeyBuf(ch) ;
			//  檢查是否按下 reset key
			if(ch == KEY_DUMMY_RESET){
				Reset=1 ;
			}
			
			// 檢查安全開關是否發生訊號
			if((ch &0xf0) == 0xd0){
				// 安全裝置錯誤回報0xd0+第幾支sensor
				// 安全裝置test回報0xd8+第幾支sensor
				MachineStatus.safe_err = (ch&0x0f) + 1;
#if 0
		ttbug.buf1[ttbug.widx] = (uint8)ch;
		ttbug.widx++;
		if (ttbug.widx >100)ttbug.widx = 0;
#endif
			}
			else if(	((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx)){
				EPT_IDX(KeyBufWIdx,	KeyBuf);
				KeyBuf[KeyBufWIdx]= ch ;
				if(KeyBufWIdx+1 >= MAX_KEY_BUF){
					KeyBufWIdx=0;
				}
				else{
					KeyBufWIdx++ ;
				}
			}
		}
		else if (((tt&0x40)==0) || ((tt&0x08)==0)){
			if (MachineStatus.flg_ScrnSav){
				ScrnSav_KeyWakeUp = true;
			}
		}
		Sprintf("%d",tt);
	}
	/* check transfer */
	if((cts_flg[1] == ON) && (inportb(rs232_base[1] +LSR_8250) & 0x20)){
		if(tr_buf_len[1]){
			/* send a byte from tr_buf to 8250 */
			outportb(rs232_base[1] +THR_8250 , tr_buf[1][tr_buf_ridx[1]++]) ;
			tr_buf_len[1]-- ;
			if(tr_buf_ridx[1] == TR_BUF_MAX){
				tr_buf_ridx[1] = 0 ;
			}
		}
		else{
			tr_flg[1] = OFF ;
			outportb(rs232_base[1] + IER_8250 , 0x9) ;
		}
	}
	if((inportb(rs232_base[1] + MSR_8250) & 0x10)){
		cts_flg[1]  = ON ;
		if(tr_buf_len[1] ){
			outportb(rs232_base[1] + IER_8250 , 0x0b) ;
			tr_flg[1] = ON ;
		}
	}
	outportb(BASED_8259A ,EOI) ;
}


// COM2
#if COMPILER == DJ_COMPILER
int int0b() 
#else
void interrupt far int0b(...)
#endif
{
	UC ch ;
	inportb(rs232_base[1] + IIR_8250) ;
	if((inportb(rs232_base[1] + LSR_8250) & 0x01)){
		// have a byte in receiver buffer
		ch = inportb(rs232_base[1] + RBR_8250) ;
		
		static uint8 ReadKeyDate_idx=0;
		
		UC tt= (rDosMem(pc_base+INM)) ;
		
		if (in_ReadAbsMotor){ //讀絕對直馬達_直接進keybuf
			if(	((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx)){
				EPT_IDX(KeyBufWIdx,	KeyBuf);
				KeyBuf[KeyBufWIdx]= ch ;
				if(KeyBufWIdx+1 >= MAX_KEY_BUF){
					KeyBufWIdx=0;
				}
				else{
					KeyBufWIdx++ ;
				}
			}
		}
		else if (ReadKeyDate_flag){ //讀KEY日期				
			EPT_IDX(ReadKeyDate_idx, ReadKeyDate_val);
			if(ReadKeyDate_idx<3)ReadKeyDate_val[ReadKeyDate_idx++]=ch;
			
			if(ReadKeyDate_idx==3){
				ReadKeyDate_flag=false;
				ReadKeyDate_idx=0;			
			}
		}
		else if( ((tt& 0x48) == 0x48)){
			fSaveKeyBuf(ch) ;
			//  檢查是否按下 reset key
			if(ch == KEY_DUMMY_RESET){
				Reset=1 ;
			}
			
			// 檢查安全開關是否發生訊號
			if((ch &0xf0) == 0xd0){
				// 安全裝置錯誤回報0xd0+第幾支sensor
				// 安全裝置test回報0xd8+第幾支sensor
				MachineStatus.safe_err = (ch&0x0f) + 1;
			}
			else if(	((BYTE)((KeyBufWIdx+1)%MAX_KEY_BUF) != KeyBufRIdx)){
				
#if 0   // debug_dprintf       
//鍵盤擷取的速度
				static int lTimerTicks =0 ;
				static int cntcode =1 ;
				dPrintf(cntcode++) ; xPrintf(" code =",ch); dPrintf("dif=",TimerTicks-lTimerTicks) ;strPrintf("\n") ;
				lTimerTicks=TimerTicks ;
#endif				
				
				
				
				
				EPT_IDX(KeyBufWIdx,	KeyBuf);
				KeyBuf[KeyBufWIdx]= ch ;
				if(KeyBufWIdx+1 >= MAX_KEY_BUF){
					KeyBufWIdx=0;
				}
				else{
					KeyBufWIdx++ ;
				}
			}
		}
		else if (((tt&0x40)==0) || ((tt&0x08)==0)){
			if (MachineStatus.flg_ScrnSav){
				ScrnSav_KeyWakeUp = true;
			}
		}
	}
	/* check transfer */
	if((cts_flg[1] == ON) && (inportb(rs232_base[1] +LSR_8250) & 0x20)){
		if(tr_buf_len[1]){
			/* send a byte from tr_buf to 8250 */
			outportb(rs232_base[1] +THR_8250 , tr_buf[1][tr_buf_ridx[1]++]) ;
			tr_buf_len[1]-- ;
			if(tr_buf_ridx[1] == TR_BUF_MAX){
				tr_buf_ridx[1] = 0 ;
			}
		}
		else{
			tr_flg[1] = OFF ;
			outportb(rs232_base[1] + IER_8250 , 0x9) ;
		}
	}
	if((inportb(rs232_base[1] + MSR_8250) & 0x10)){
		cts_flg[1]  = ON ;
		if(tr_buf_len[1] ){
			outportb(rs232_base[1] + IER_8250 , 0x0b) ;
			tr_flg[1] = ON ;
		}
	}
	outportb(BASED_8259A ,EOI) ;
}
#if COMPILER == DJ_COMPILER
int int0d() 
#else
void interrupt far int0d(...)
#endif
{
	INT_RS2321(2)
#ifdef IPD51
		INT_RS2325(2)
#endif
		INT_RS2322(2)

#ifdef HANDSHAKING
		INT_RS2324(2)
#endif
		INT_RS2323(2)
		ch=ch ;
}


void init_rs232()
{
	init_rs_tr_buf() ;
	init_rs_tr_flg() ;
	init_8250() ;
	switch(comm_port){
	case 0 :
		init_intvect(&oint0c , 0x0c , int0c) ;
		break ;
	case 1 :
		init_intvect(&oint0b , 0x0b , int0b) ;
		break ;
	case 2 :
		init_intvect(&oint0d , 0x0d , int0d) ;
		break ;
	}
	outportb(BASED_8259A + 1 , inportb(BASED_8259A +1) & mask_8259a[comm_port]) ;
}
void init_rs232_NewH()
{
	init_rs_tr_buf() ;
	init_rs_tr_flg() ;
	init_8250() ;
	switch(comm_port){
	case 0 :
		init_intvect(&oint0c , 0x0c , int0c_NewH) ;
		break ;
	case 1 :
		init_intvect(&oint0b , 0x0b , int0b_NewH) ;
		break ;
	case 2 :
		init_intvect(&oint0d , 0x0d , int0d) ;
		break ;
	}
	outportb(BASED_8259A + 1 , inportb(BASED_8259A +1) & mask_8259a[comm_port]) ;
}
void init_rs_tr_buf()
{
	EPT_IDX(comm_port,	rs_buf_ridx) ;
	EPT_IDX(comm_port,	tr_buf_ridx) ;
	rs_buf_ridx[comm_port] = rs_buf_widx[comm_port] =  rs_buf_len[comm_port] = 0 ;
	tr_buf_ridx[comm_port] = tr_buf_widx[comm_port] =  tr_buf_len[comm_port] = 0 ;
}
void init_rs_tr_flg()
{
	EPT_IDX(comm_port,	rs_flg) ;
	EPT_IDX(comm_port,	tr_flg) ;
	EPT_IDX(comm_port,	cts_flg) ;
	EPT_IDX(comm_port,	rts_flg) ;
	rs_flg[comm_port] = ON ;
	tr_flg[comm_port] = OFF ;
	cts_flg[comm_port] = ON ;
	rts_flg[comm_port] = ON ;
}
//IER_8250  -----0x9   啟動接收
//IER_8250 ------0xb   啟動接收/啟動傳送
void init_8250()
{
	/* out2(enable /disable 8250 interrupt signal to 8259) = 1	*/
	/* rts = 1 , dtr = 1 */
	outportb(rs232_base[comm_port]+MCR_8250 , 0xb) ;
	outportb(rs232_base[comm_port]+IER_8250 , 0x9) ;/* enable receivered data available interrupt */
	inportb(rs232_base[comm_port]+LSR_8250) ;
	inportb(rs232_base[comm_port]+MSR_8250) ;
	inportb(rs232_base[comm_port]+RBR_8250) ; /* read first byte */
}
void on_dtr_rts()
{
	EPT_IDX(comm_port,	rts_flg) ;
	rts_flg[comm_port] = ON ;
	outportb(rs232_base[comm_port] + MCR_8250, 0x0b) ;
}
void wr_rs232(UC ch)
{	
	while(tr_buf_len[comm_port] == TR_BUF_MAX){
	}
	
	EPT_IDX(comm_port,	tr_buf_widx) ;
	EPT_IDX(comm_port,	tr_buf) ;
	EPT_IDX(tr_buf_widx[comm_port],	tr_buf[0]) ;
	
	tr_buf[comm_port][tr_buf_widx[comm_port]++] = ch ;
	if(tr_buf_widx[comm_port] == TR_BUF_MAX){
		tr_buf_widx[comm_port] = 0 ;
	}
	disable();
	tr_buf_len[comm_port]++ ;
	if((cts_flg[comm_port] == ON) && (tr_flg[comm_port] == OFF)){
		
		EPT_IDX(comm_port,	tr_flg) ;
		tr_flg[comm_port] = ON ;
		outportb(rs232_base[comm_port] + IER_8250 , 0x0b) ;
	}
	enable();
}
int rd_rs232()
{
	UC ch ;
	while(rs_buf_len[comm_port] == 0){
	}
	ch = rs_buf[comm_port][rs_buf_ridx[comm_port]++] ;
	if(rs_buf_ridx[comm_port] == RS_BUF_MAX){
		
		EPT_IDX(comm_port,	rs_buf_ridx) ;
		rs_buf_ridx[comm_port] = 0 ;
	}
	disable();
	rs_buf_len[comm_port]-- ;
	if((rts_flg[comm_port] == OFF) && (rs_buf_len[comm_port] < (RS_BUF_MAX - 20))){
		on_dtr_rts() ;
	}
	enable();
	return(ch) ;
}
void quit_rs232()
{
	switch(comm_port){
	case 0 :
		outportb(BASED_8259A + 1 , inportb(BASED_8259A +1) | 0x10) ;
#if COMPILER== DJ_COMPILER		
		res_intvect(&oint0c , 0xc) ;
#else
		res_intvect(oint0c , 0xc) ;
#endif
		break ;
	case 1 :
		outportb(BASED_8259A + 1 , inportb(BASED_8259A +1) | 0x08) ;
#if COMPILER== DJ_COMPILER		
		res_intvect(&oint0b , 0xb) ;
#else
		res_intvect(oint0b , 0xb) ;
#endif
		break ;
	case 2 :
		outportb(BASED_8259A + 1 , inportb(BASED_8259A +1) | 0x20) ;
#if COMPILER== DJ_COMPILER		
		res_intvect(&oint0d , 0xd) ;
#else
		res_intvect(oint0d , 0xd) ;
#endif
		break ;
	}
}
int chk_rs232()
{
	return(rs_buf_len[comm_port]) ;
}
void flush_rs232()
{
	while(chk_rs232()){
		rd_rs232() ;
	}
}

void ini_baud (UI mode)
{
	// 9600 baud rate, even parity, 1 stop bit , 8 data bit ----0xfb
	union REGS call_regs , ret_regs ;
	call_regs.h.ah = 0	  ; /* set parameter */
	call_regs.h.al = mode ;
	call_regs.x.dx =comm_port ;
	int86(0x14 , &call_regs , &ret_regs) ;
}
/* Default 	0x03 = 38,400 BPS 
			0x01 = 115,200 BPS 
			0x02 = 57,600 BPS 
			0x06 = 19,200 BPS
			0x0C = 9,600 BPS 
			0x18 = 4,800 BPS 
			0x30 = 2,400 BPS */
void CHG_BAUD (int com ,int num1, int num2)	
{										
	UC baud[5];                                                         
	uint16 COMPORT=rs232_base[com];	                                    
	uint8 ch3=inportb(COMPORT+3) ;                                      
	                                                                    
	/*修改為---9600||57600*/                                            
	outportb(COMPORT+3,num1);			/*開啟"修改"功能*/              
	outportb(COMPORT+0,num2);			/*Baud rate--Low Byte*/         
	                                                                    
	for(int i=0; i<5; i++){                                             
		baud[i] =inportb(COMPORT+i) ;	/*rs232_base[1]==0x2f8, COM2*/  
	}		                                                            
	outportb(COMPORT+3,ch3);			/*開啟"修改"功能*/
}
	
void ini_baud_9600 (int com)
{	
	CHG_BAUD(com,0x80,0x0c);
}
void ini_baud_57600 (int com)
{	
	CHG_BAUD(com,0x80,0x02);
}









int chk_cts()
{
	return(inportb(rs232_base[comm_port] + MSR_8250) & 0x10) ;
}
void off_dtr_rts()
{
	EPT_IDX(comm_port,	rts_flg) ;
	rts_flg[comm_port] = OFF;
	outportb(rs232_base[comm_port] + MCR_8250, 0x00) ;
}
int m_rs232()
{
	return(tr_buf_len[comm_port]) ;
}
void dw_rs232()
{
	init_rs_tr_buf() ;
	outportb(rs232_base[comm_port] + IER_8250 , 0x0b) ;
	EPT_IDX(comm_port,	tr_flg) ;
	tr_flg[comm_port] = ON ;
	outportb(rs232_base[comm_port] +THR_8250 , 0) ;
}
#if COMPILER == DJ_COMPILER
void init_intvect(_go32_dpmi_seginfo *oint , UI intvecno,int(*isr)())
{
  	_go32_dpmi_seginfo  new_handler;
	_go32_dpmi_get_protected_mode_interrupt_vector(intvecno, oint);
	disable();
  	new_handler.pm_offset = (int)isr;
  	new_handler.pm_selector = _go32_my_cs();
  	_go32_dpmi_chain_protected_mode_interrupt_vector(intvecno, &new_handler);
	enable();
}
#else	
void init_intvect(void interrupt (**oint)(...) , UI intvecno,void interrupt (*isr)(...))
{
	*oint = getvect(intvecno);
	disable();
	setvect(intvecno,isr);
	enable();
}
#endif
#if COMPILER == DJ_COMPILER
void res_intvect(_go32_dpmi_seginfo *oint ,UI intvecno )
{
	disable() ;
	_go32_dpmi_set_protected_mode_interrupt_vector(intvecno, oint);
	enable() ;
}
#else	
void res_intvect(void interrupt (*oint)(...) ,UI intvecno )
{
	disable() ;
	setvect(intvecno,oint);
	enable() ;
}
#endif

//2012_07讀KEY版本日期---------------
void ReadKeyDate()
{
	ReadKeyDate_flag=true;
	wr_rs232(0x21) ;		//RS232送0x21  可得 3BYTE, YEAR/MONTH/DAY	例：12/05/18 表示2012年5月18日

}		

