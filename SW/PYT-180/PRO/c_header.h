#define BC_COMPILER		0
#define VC_COMPILER		1
#define DJ_COMPILER		2
#define COMPILER		DJ_COMPILER
#define NEWLOGO         1
#if COMPILER == BC_COMPILER	//VVVVVVVVVVVVVVVVVV//
#define _O_CREAT		O_CREAT                 //
#define _O_BINARY		O_BINARY                //
#define _O_RDWR			O_RDWR                  //
#define _S_IREAD		S_IREAD                 //
#define _S_IWRITE		S_IWRITE                //
#define _O_RDONLY		O_RDONLY                //
#define _O_TRUNC		O_TRUNC                 //
#endif	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//


#define CCYFILE  "D:\\CCYFILE.DAT"
#define CCYFILE_D  "D:\\CCYFILE.DAT"
#define CCYFILE_C  "C:\\CCYFILE.DAT"
#define TOUFILE  "D:\\TOUFILE.DAT"
#define HUANG01  "D:\\HUANG01.DAT"
#define HUANG01_D  "D:\\HUANG01.DAT"
#define HUANG01_C  "C:\\HUANG01.DAT"
#define HUANG01EX_C  "C:\\HUANGEX.DAT"
#define HUANG01EX_D  "D:\\HUANGEX.DAT"
#define COMMENT_D  "D:\\COMMENT.DAT"
#define COMMENT_C  "C:\\COMMENT.DAT"
#define SPEED_C  "C:\\SPEED.DAT"
#define CONFIG_C   "C:\\CONFIG.DAT" 
#define CONFIG_D   "D:\\CONFIG.DAT" 
#define ERRFILE  "C:\\ERRMSG.DAT"
#define BACKUP   "C:\\BACKUP.DAT"
#include "C_HNCNC68.h"
#include "pcb.h"
#include "c_cond.h"

#if (REC_TIME_INTERVAL)
#include "c_rec_time.h"
#endif

#if (SAVE_AXIS_CMD)
#include "c_axis_cmd.h"
#endif



//	#include <dos.h>
	#include <stdlib.h>	  // malloc()
	#include <stdio.h>	  // fopen()
	#include <setjmp.h>
//	#include <bios.h>	  // bioskey()
	#include <string.h>		// memcpy
//  	#include <conio.h>		// RED,WHITE
	#include <stdarg.h>
#if COMPILER == DJ_COMPILER
//	#include <dpmi.h>
//	#include <go32.h>
//	#include <sys/farptr.h>
//	#include <grx20.h>
#else
	//#include <alloc.h>		// farmalloc()
#endif
	#include "c_timer0.h"

#define MANMS 50

#define POINTWIDTH			3
#define BIGNWIDTH			10
#define BIGNWIDTHB			2
#define BIGNHEIGHT			20
#define BIGNBYTES			(BIGNWIDTHB*BIGNHEIGHT)
#define BIGNSPACE			6

#define BIG30NWIDTH 		15
#define BIG30NWIDTHB		2
#define BIG30NHEIGHT		30
#define BIG30NBYTES 		(BIG30NWIDTHB*BIG30NHEIGHT)
#define BIG30NSPACE 		6

#define BIG48NWIDTH 		24
#define BIG48NWIDTHB		3
#define BIG48NHEIGHT		48
#define BIG48NBYTES 		(BIG48NWIDTHB*BIG48NHEIGHT)
#define BIG48NSPACE 		6


#define SMALLNWIDTH 		7
#define SMALLNWIDTHB		1
#define SMALLNHEIGHT		16
#define SMALLNBYTES 		(SMALLNWIDTHB*SMALLNHEIGHT)
#define SMALLNSPACE 		4

#define MEDNWIDTH			9
#define MEDNWIDTHB			2

#define MEDNHEIGHT			18
#define MEDNBYTES			(MEDNWIDTHB*MEDNHEIGHT)
#define MEDNSPACE			5

#define NBYTES		0
#define NHEIGHT 	1
#define NWIDTH		2
#define NWIDTHB 	3
#define NSPACE		4
#define POINTYOFF	5
#define MAX_LENCHK_BUF 200
#define MAX_LENCHK_XMS 10000	// ≥Ê¶ÏK


//#include "c_const_crt.h"
#include "const_uty_1.h"
#include "ncrt.h"       
#include "ncnc.h"       
#include "struct.h"     
#include "vars.h"       
#include "c_rs232.h"    
//#include "c_showet.h"   
//#include "c_df_rgb.h"   
//#include "c_index.h"    
//#include "config.h"     
//#include "Pque.h"       
       
#include "uty1.pro"
#include "usort.pro"
#include "new.pro"
#include "uty2_2.pro"
//#include "disp_para.pro"
#include "ya_abs.pro"
//#include "pass.pro"
//#include "marker.pro"
//#include "iprintf.pro"
#include "manmov.pro"
//#include "lcomment.pro"
#include "const.h"
#include "c_graf.h"
//#include "c_printer.h"
#include "c_pc.h"

#include "RUN_cmd.pro"
#include "RUN_vars.h"
#include "n_vars.h"

#include "disp_para.h"                                    
                                    
//#if COMPILER == DJ_COMPILER         
#include "DosMem_p.pro"             
//#else                               
//#include "DosMem.pro"
//#endif
#include "ncnc.pro"
#define RUN_MSG_W	((2+2)*ASC_CHAR_W+200)
#define RUN_MSG_H	((3+3+2)*ASC_CHAR_H-10)
#define RUN_MSG_LX	(405)



#define START_X_LIMIT  10
#define isCode1234(Code)       ((Code ==1) || (Code ==2) || (Code ==3) || (Code ==4))
#define INIT_LOOP() 																																						\
	ini_loopchk(false) ;																																					\
	for( loop_no=0, line=0; ProgBuf[line].bygcode; line++ ){																			\
		if(isCode1234(ProgBuf[line].bygcode)){																											\
			for(BYTE axis= AXIS_Z;axis < MAX_PROG_AXIS ;	axis++){																		\
				if(MachineStatus.motor[axis]&&(ProgBuf[line].dval[axis] !=	PROG_VAL_NULL)){						\
						zabcend[axis]=BcdToBin(5, ProgBuf[line].dval[axis]);																\
						zabcend[axis]*=((ProgBuf[line].bysign[axis] & 0x7f)==PLUS_SIGN? 1:-1)	;							\
				}																																												\
			}																																													\
		}																																														\
		else if( ProgBuf[line].bygcode == 5 ){ 																											\
			EPT_IDX(loop_no, loop_s);																																	\
			EPT_IDX(loop_no, loop_e);																																	\
			loop_s[loop_no] = (WORD)BcdToBin(3, ProgBuf[line].dval[START_X]);													\
			loop_e[loop_no] = (WORD)BcdToBin(3, ProgBuf[line].dval[END_X]);														\
			for(BYTE axis= AXIS_Z;axis < MAX_PROG_AXIS ;	axis++){																		\
					looppos[loop_no][axis]=zabcend[axis] ;																								\
			}																																													\
			loop_no++;																																								\
		}																																														\
	}																																															\
	if( ProgBuf[line].wjmp == PROG_VAL_NULL )  ret_line = PROG_VAL_NULL; 													\
	else  ret_line = BcdToBin(3, ProgBuf[line].wjmp);

#define GET_LOOP_POS()																															\
	for(int i=0; i < loop_no; i++ ){																									\
		if( loop_s[i] == line ){																												\
			a_tbl[idx].cmd		  = LOOP_START; 																						\
			a_tbl[idx].mov		  = BcdToBin(4, ProgBuf[loop_e[i]].dval[AXIS_Y]);						\
			a_tbl[idx].u.loop_idx = idx + 1;																							\
			a_tbl[idx].sdchk_pos	  = 0;																									\
			a_tbl[idx].next 	  = 0;																											\
			idx++;		EPT_IDX(idx, ActTbl);																								\
			looppos[i][0] = sds;																													\
			loop_e_air[i] = p_buf->byair;																									\
			loopstart_idx=i ;																															\
			ini_loopchk(true) ;																														\
		}																																								\
	}

#define GET_RET_IDX()  if( ret_line == line ){ RetTblIdx = idx;   ret_pos = sds; }



#define FILL_TO_SPD()\
{\
	uint8 sp = PAGE_CHARS-StrLen_S(DispBuf)-4-3-8;	\
	for( ; sp; sp-- ){\
		FILL_DISP_BUF(' ');\
	}\
	EPT_BC(pDispBuf_value,pDispBuf);\
	*pDispBuf_value = 0;\
}
#define FILL_SPD()\
{\
	FILL_DISP_BUF(' ');\
	if(!Has_spd(prog) ){\
		Fill_pDispBuf("   ");\
	}\
	else{\
		if (prog->bygcode ==4){\
			pDispBuf_value += BcdToStrBuf(2, prog->wspd, pDispBuf);\
			ADD_DOT_01(pDispBuf_value);\
		}\
		else {\
			pDispBuf_value += BcdToStrBuf(3, prog->wspd, pDispBuf);\
		}\
	}\
}
#define FILL_TOUCH()\
{\
	FILL_DISP_BUF(' ');\
	FILL_DISP_BUF(THMark[(prog->byth)%=(sizeof(THMark)/sizeof(THMark[0]))]);\
	if( !(prog->byth==TH1_STP ||\
	      prog->byth==TH2_STP ||\
	      prog->byth==TH3_STP ||\
	      prog->byth==TH4_STP) ) prog->bytd = 0;\
	FILL_DISP_BUF(TDMark[(prog->bytd)%=(sizeof(TDMark)/sizeof(TDMark[0]))]);\
}

#define FILL_AIRS()\
{\
	for(int i=0; i < 4; i++ ){\
		FILL_DISP_BUF((((prog->byair)&(0x01<<i))?'1':'0'));\
	}\
	FILL_DISP_BUF((((prog->byair)&0x10)?THMark[5]:' '));\
	FILL_DISP_BUF((((prog->byair)&0x20)?THMark[6]:' '));\
	FILL_DISP_BUF((((prog->byair)&0x40)?THMark[1]:' '));\
	FILL_DISP_BUF((((prog->byair)&0x80)?THMark[2]:' '));\
}				


#define CHK_CACL_DELAY()  ( !(DispDelay&0x1f) )

#define CHECK_SIGN()														\
	if( (ptr)->sign ){														\
		EPT_BC(pbuffer_value,buf) ;												\
		*pbuffer_value++ = (*(BYTE *)((ptr)->sign) & 0x7f)==PLUS_SIGN?'+':'-';	\
		EPT_BC(pbuffer_value,pbuffer) ;												\
		*pbuffer_value = 0;														\
	}


#define KEYIN_NUM(n,CAST)								\
	n = (CAST *)(ptr)->var; 							\
	if( CurCursor.first ){								\
		CurCursor.first = 0;							\
		*n =num;										\
	}													\
	else{												\
		*n <<= 4;										\
		*n += num;										\
		*n &= (CAST)mask[((ptr)->nibble)-1];			\
	}






#if CCY_CHECK==1	//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
#define COMP_MARK(p,off)												   				\
	( (*(p+off+0)==CYCH0) && (*(p+off+2)==CYCH1) && (*(p+off+4)==CYCH2) && \
	(*(p+off+6)==CYCH3) && (*(p+off+8)==CYCH4) )

#define WR_MARK(p,off)				\
	*(p+off+0) = CYCH0; 				\
	*(p+off+2) = CYCH1; 				\
	*(p+off+4) = CYCH2; 				\
	*(p+off+6) = CYCH3; 				\
	*(p+off+8) = CYCH4;

#define CLR_MARK(p,off) 				\
	*(p+off+0) = 'X';					\
	*(p+off+2) = 'X';					\
	*(p+off+4) = 'X';					\
	*(p+off+6) = 'X';					\
	*(p+off+8) = 'X';

#define COMP_OVER_USED(n)								\
	( (*(n+0)>=USEDT_HB) || (*(n+1)>=USEDT_HB) )

#define CACUL_USED_TIMES(n) 						\
	if( (*(n+2)>=100) || (*(n+3)>=100) ){		\
		*(n+0) += 1;										\
		*(n+1) += 1;										\
		*(n+2)	= 0;									\
		*(n+3)	= 0;									\
	}														\
	else{													\
		*(n+2) += 1;										\
		*(n+3) += 1;										\
	}

#define CLR_USED_TIMES(n)	\
	*(n+0) = 0; 					\
	*(n+1) = 0; 					\
	*(n+2) = 0; 					\
	*(n+3) = 0;

#define WR_USED_TIMES(n,d)	\
	*(n+0) = d; 					\
	*(n+1) = d; 					\
	*(n+2) = 99;					\
	*(n+3) = 99;		
#endif	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if 0
#define WHITE_VGA256		0xf
#define BLUE_VGA256 		0x1
#define LIGHTBLUE_VGA256	0x9
#define BLACK_VGA256		0x0
#define CYAN_VGA256 		0x3
#define LIGHTCYAN_VGA256	0xb
#define YELLOW_VGA256		0xe
#define RED_VGA256			0x4
#define LIGHTRED_VGA256 	0xc
#define DARKGRAY_VGA256 	0x18
#define LIGHTGRAY_VGA256	0x1d
#define GREEN_VGA256		0x2
#define LIGHTGREEN_VGA256	0xa
#endif

#define	NEED_AIRTBL(p_buf)	((((p_buf)->dval[AIR_START_X]	!= 0) || ((p_buf)->dval[AIR_END_X] != 0))&&	\
							(((p_buf)->dval[AIR_START_X]	!= (p_buf)->dval[START_X]) ||								\
							 ((p_buf)->dval[AIR_END_X]!=	(p_buf)->dval[END_X])											\
							))

#define RUN_MISS_SET_AIR																			\
		case MISS_SET_AIR:																			\
			if(	!MachineStatus.miss_flag )	break;
#if 1
#define RUN_SET_AIR																	\
		case SET_AIR:																	\
			wDosMem(pc_base+OUTL ,MachineStatus.air_buf |= a_tbl->u.air);	\
			break;
#else
		case SET_AIR:																										\
			MachineStatus.air_buf &= MachineStatus.th_mask;														\
			wDosMem(pc_base+OUTL,(MachineStatus.air_buf |= (a_tbl->u.air&(~MachineStatus.th_mask))));	\
			break;
#endif
		
#define RUN_CLR_AIR																							\
		case CLR_AIR:																							\
			wDosMem(pc_base+OUTL , (MachineStatus.air_buf &= a_tbl->u.air));						\
			break;																								\
		case CLR_LOOP_AIR:																						\
			if(	MachineStatus.in_loop ){  																\
				wDosMem(pc_base+OUTL , (MachineStatus.air_buf &= a_tbl->u.air));					\
			}																										\
			break;			

#define RUN_SET_TOUCH			\
	case SET_TOUCH:				\
		RUN_SET_TOUCH1			\
	break ;

	
	
	
	
#define RUN_SET_TOUCH2																	\
	if(NewH){																\
	th = a_tbl->u.t.touch ;													\
	ini_th_stopy() ;														\
	if(	th==TH1_STP	|| th==TH1_CHK ){										\
		MachineStatus.rec_th[0]	 = 	PROG_VAL_NULL;							\
		MachineStatus.pass_th[0] = 0;										\
		MachineStatus.chk_th[0]	 = th;										\
		MachineStatus.chk_th_stop_axis[0]  = a_tbl->u.t.stop_axis;			\
		if(th== TH1_CHK){													\
			DISABLE_TOUCH_STOP(1) ;											\
		}																	\
		else{																\
			TOUCH_STOP(1,	STOPY) ;										\
		}																	\
		ENABLE_TOUCH_INT(1) ;												\
		MachineStatus.air_buf	 |=	MASK_BIT6 ;								\
		wDosMem(pc_base+OUTL ,MachineStatus.air_buf) ;						\
	}																		\
	else if( th==TH2_STP ||	th==TH2_CHK	){									\
		MachineStatus.rec_th[1]	 =  PROG_VAL_NULL ;							\
		MachineStatus.pass_th[1] = 0 ;										\
		MachineStatus.chk_th[1]	 = th ;										\
		MachineStatus.chk_th_stop_axis[1]  = a_tbl->u.t.stop_axis ;			\
		if(th== TH2_CHK){													\
			DISABLE_TOUCH_STOP(2) ;											\
		}																	\
		else{																\
			TOUCH_STOP(2,	STOPY) ;										\
		}																	\
		ENABLE_TOUCH_INT(2) ;												\
		MachineStatus.air_buf	 |=	MASK_BIT7 ;								\
		wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						\
	}																		\
	else if( th	== TH3_STP ){												\
		MachineStatus.rec_th[2]	 =PROG_VAL_NULL ;							\
		MachineStatus.pass_th[2] = 0 ;										\
		MachineStatus.chk_th[2]	 = th ;										\
		MachineStatus.chk_th_stop_axis[2]  = a_tbl->u.t.stop_axis ;			\
		TOUCH_STOP(3,	STOPY) ;											\
		ENABLE_TOUCH_INT(3) ;												\
		MachineStatus.air_buf	 |=	MASK_BIT4 ;								\
		wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						\
	}																		\
	else if( th	== TH4_STP ){												\
		MachineStatus.rec_th[3]	 = PROG_VAL_NULL ;							\
		MachineStatus.pass_th[3] = 0 ;										\
		MachineStatus.chk_th[3]	 = th ;										\
		MachineStatus.chk_th_stop_axis[3]  = a_tbl->u.t.stop_axis ;			\
		TOUCH_STOP(4,	STOPY) ;											\
		ENABLE_TOUCH_INT(4) ;												\
		MachineStatus.air_buf	 |=	MASK_BIT5 ;								\
		wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						\
	}																		\
	if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == RUN_MODE){			\
		nSet8254(a_tbl->spd_th.sc8254);										\
	}																		\
	else if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == TEST_MODE){	\
		TouchSPD.change = true;												\
		TouchSPD.spd    = a_tbl->spd_th.spd;								\
		TouchSPD.speed  = a_tbl->spd_th.speed;								\
		MachineStatus.set8254 = 1;											\
		update_sc(1);														\
	}																		\
	}																		
	
	
	
	
#define RUN_CLR_TOUCH		\
	case CLR_TOUCH:			\
		RUN_CLR_TOUCH1		\
		INI_BREAK_PROC		\
	break;
	
#define RUN_CLR_TOUCH1																								\
	if(NewH)																									\
	{																						\
	ini_th_stopy() ;																		\
	th = a_tbl->u.t.touch ;																	\
	if(	th==TH1_STP	|| th==TH1_CHK ){														\
		DISABLE_TOUCH_STOP(1)																\
		ResetDriverClear() ;																\
		if(chk_utouch(0,a_tbl->utouch.start,a_tbl->utouch.end) ){							\
			if(	th==TH1_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	1 ;	\
			DISABLE_INPORT_INT(MASK_BIT6) ;													\
			MachineStatus.air_buf &= (~MASK_BIT6) ;											\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									\
			if(!MachineStatus.pass_th[0]){													\
				flag_ClrTouchPos[0]=true ;													\
			}																				\
			miss = 1 ;																		\
		}																					\
		MachineStatus.pass_th[0] = 0 ;														\
		MachineStatus.chk_th[0]	 = 0 ;														\
	}																						\
	else if( th==TH2_STP ||	th==TH2_CHK	){													\
		DISABLE_TOUCH_STOP(2)																\
		ResetDriverClear() ;																\
		if(	chk_utouch(1,a_tbl->utouch.start,a_tbl->utouch.end) ){							\
			if(	th==TH2_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	2 ;	\
			DISABLE_INPORT_INT(MASK_BIT7) ;													\
			MachineStatus.air_buf &= (~MASK_BIT7) ;											\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									\
			if(!MachineStatus.pass_th[1]){													\
				flag_ClrTouchPos[1]=true ;													\
			}																				\
			miss = 1 ;																		\
		}																					\
		MachineStatus.pass_th[1] = 0 ;														\
		MachineStatus.chk_th[1]	 = 0 ;														\
	}																						\
	else if( th	== TH3_STP ){																\
		DISABLE_TOUCH_STOP(3)																\
		ResetDriverClear() ;																\
		if(chk_utouch(2,a_tbl->utouch.start,a_tbl->utouch.end) ){							\
			if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 3 ;				\
			DISABLE_INPORT_INT(MASK_BIT3) ;													\
			MachineStatus.air_buf &= (~MASK_BIT4) ;											\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									\
			if(!MachineStatus.pass_th[2]){													\
				flag_ClrTouchPos[2]=true ;													\
			}																				\
			miss = 1 ;																		\
		}																					\
		MachineStatus.pass_th[2] = 0 ;														\
		MachineStatus.chk_th[2]	 = 0 ;														\
	}																						\
	else if( th	== TH4_STP ){																\
		DISABLE_TOUCH_STOP(4)																\
		ResetDriverClear() ;																\
		if(	chk_utouch(3,a_tbl->utouch.start,a_tbl->utouch.end) ){							\
			if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 4 ;				\
			DISABLE_INPORT_INT(MASK_BIT4) ;													\
			MachineStatus.air_buf &= (~MASK_BIT5) ;											\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									\
			if(!MachineStatus.pass_th[3]){													\
				flag_ClrTouchPos[3]=true ;													\
			}																				\
			miss = 1 ;																		\
		}																					\
		MachineStatus.pass_th[3] = 0 ;														\
		MachineStatus.chk_th[3]	 = 0 ;														\
	}																						\
	if(	!MachineStatus.miss_flag &&	miss ){													\
		MachineStatus.miss_flag	= 1 ;														\
		if(	MachineStatus.set_miss ){														\
		    uint8 sign=PLUS_SIGN ;															\
			addcurmiss_cmd();\
			flag_DispMissNo=true ;															\
		}																					\
	}																						\
	if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == RUN_MODE){							\
		nSet8254(a_tbl->spd_th.sc8254);														\
	}																						\
	else if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == TEST_MODE){					\
		TouchSPD.change = false;															\
		TouchSPD.spd    = 0;																\
		TouchSPD.speed  = 0;																\
		MachineStatus.set8254 = 1;															\
		update_sc(1);																		\
	}																						\
	}																												\
	else{																											\
	ini_th_stopy() ;																									\
	th = a_tbl->u.t.touch ;																							\
	if(	th==TH1_STP	|| th==TH1_CHK ){																			\
		if(chk_utouch(0,a_tbl->utouch.start,a_tbl->utouch.end) ){											\
			if(	th==TH1_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	1 ;	\
			DISABLE_INPORT_INT(MASK_BIT6) ;																		\
			MachineStatus.air_buf &= (~MASK_BIT6) ;																\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;													\
			if(!MachineStatus.pass_th[0]){																			\
				flag_ClrTouchPos[0]=true ;																			\
			}																												\
			miss = 1 ;																									\
		}																													\
		MachineStatus.pass_th[0] = 0 ;																				\
		MachineStatus.chk_th[0]	 = 0 ;																			\
	}																														\
	else if( th==TH2_STP ||	th==TH2_CHK	){																		\
		if(	chk_utouch(1,a_tbl->utouch.start,a_tbl->utouch.end) ){										\
			if(	th==TH2_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	2 ;	\
			DISABLE_INPORT_INT(MASK_BIT7) ;																		\
			MachineStatus.air_buf &= (~MASK_BIT7) ;																\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;													\
			if(!MachineStatus.pass_th[1]){																			\
				flag_ClrTouchPos[1]=true ;																			\
			}																												\
			miss = 1 ;																									\
		}																													\
		MachineStatus.pass_th[1] = 0 ;																				\
		MachineStatus.chk_th[1]	 = 0 ;																			\
	}																														\
	else if( th	== TH3_STP ){																						\
		if(chk_utouch(2,a_tbl->utouch.start,a_tbl->utouch.end) ){											\
			if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 3 ;							\
			DISABLE_INPORT_INT(MASK_BIT3) ;																		\
			MachineStatus.air_buf &= (~MASK_BIT4) ;																\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;													\
			if(!MachineStatus.pass_th[2]){																			\
				flag_ClrTouchPos[2]=true ;																			\
			}																												\
			miss = 1 ;																									\
		}																													\
		MachineStatus.pass_th[2] = 0 ;																				\
		MachineStatus.chk_th[2]	 = 0 ;																			\
	}																														\
	else if( th	== TH4_STP ){																						\
		if(	chk_utouch(3,a_tbl->utouch.start,a_tbl->utouch.end) ){										\
			if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 4 ;							\
			DISABLE_INPORT_INT(MASK_BIT4) ;																		\
			MachineStatus.air_buf &= (~MASK_BIT5) ;																\
			wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;													\
			if(!MachineStatus.pass_th[3]){																			\
				flag_ClrTouchPos[3]=true ;																			\
			}																												\
			miss = 1 ;																									\
		}																													\
		MachineStatus.pass_th[3] = 0 ;																				\
		MachineStatus.chk_th[3]	 = 0 ;																			\
	}																														\
	if(	!MachineStatus.miss_flag &&	miss ){																	\
		MachineStatus.miss_flag	= 1 ;																				\
		if(	MachineStatus.set_miss ){																			\
		    uint8 sign=PLUS_SIGN ;																					\
			addcurmiss_cmd();\
			flag_DispMissNo=true ;																					\
		}																													\
	}																														\
	if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == RUN_MODE){										\
		nSet8254(a_tbl->spd_th.sc8254);																			\
	}																														\
	else if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == TEST_MODE){								\
		TouchSPD.change = false;																						\
		TouchSPD.spd    = 0;																							\
		TouchSPD.speed  = 0;																							\
		MachineStatus.set8254 = 1;																					\
		update_sc(1);																									\
	}																										\
	}
	
	
	
	
#define RUN_MISS_UPDATE_LINE																		\
		case MISS_UPDATE_LINE:                                                       \
			if(	!MachineStatus.miss_flag )	break;

#define RUN_UPDATE_LINE																				\
		case UPDATE_LINE:  								                                  \
			MachineStatus.last_line	= a_tbl->u.line;                            		\
			RUN_UPDATE_LINE1

