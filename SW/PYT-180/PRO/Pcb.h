#ifdef GLOBAL
#define EXTERN	  
#else
#define EXTERN	  extern
#endif

#if 0
#define SAVE_ACTTBL			0
#else
#define SAVE_ACTTBL			1
//注意!此開關打開只做debug,完成後須要關閉,否則引將影響正常程式的執行
//#define DEBUG_NCNC
#endif



#if COMPILER == DJ_COMPILER
#define REAL_COLOR       1
#define NORM_WIDTH    1
#else
#define REAL_COLOR       0
#endif


//#define RD_EXT_ENCODER
//#define SAVEVGA3 

//2012_0613_ETP_Bound_Check------------------------------------------
//#define Bound_Check


//檢查陣列宣告是否Overflow
//#define Bound_Checking


#ifdef DEBUG_NCNC
#define DEBUG_CLOCKISR
#endif



//象虎/新達/開創/江南
//#define SETT6


//2012_1010_新增"小鍵盤"&&"LOGO"切換----------------------------
#define HNCNC       	0		//新達
#define KNCNC         	1		//開創
#define RSOUTH         	2  		//江南
#define SETT       	  	3		//象虎
#define SFNCNC		 	4	    //星火
#define JLNCNC		 	5	    //建岭

//#define ITNCNC		  	4		//溢通
//#define CYNCNC			5		//超越
//#define ANDNCNC			6		//人和
//#define TCNCNC			7		//天齊
//#define TMNCNC			8		//台明
//#define CTNCNC			9		//西田
//#define GGNCNC		 0x10	    //廣錦
//#define SFNCNC		 0x11	    //星火
//#define SDNCNC		 0x12	    //三島
//#define AXNCNC		 0x13	    //奧升
//#define SGNCNC		 0x14	    //實在
//#define JLNCNC		 0x15	    //建岭

enum{KEY_H,KEY_S} ; 
//KEY_H:新達大鍵盤
//KEY_S:小鍵盤
#define isKEY_H     (MachineStatus.keyboard_type == KEY_H) 
#define isKEY_S     (MachineStatus.keyboard_type == KEY_S) 




#define SAVEIMAGE         1

#define idx_language   (MachineStatus.language?(MachineStatus.language==3? 2:1):0)
//1: EDGE  ------新版本
//0: LEVEL  -------舊版本

#define LEVEL_INT_EDGE          1







#define DEBUG_RESEND     0
//記錄每次Y軸檢出值
#define NEW_FUN1			1


#define SW_SIM_MOTOR        1
#define NEWV_MDY			0
#define CHK_MAN_MOV			1
#define NEW_INDEX			0

#define LOGO_ON          1

#define GAP_MDY			0
#define SYN_DELAY		0
// 1: 檢查fopen和fclose是否成雙出現
#define FILE_ACCESS			0
#define TOUCH_STOP_SPIN		1

//1:含有檔案說明的功能
#define NEW_FILE			0

//提供無須password的畫面
#define NOPASS				1

//用來偵測FILL_PROC_QUEUE參數傳遞是否有問題
#ifdef DEBUG_NCNC
#define DEBUG_PARAMETER		1
#else
#define DEBUG_PARAMETER		0
#endif


//用來偵測FILL_PROC_QUEUE是否在中斷服務程式有被呼叫,將造成當機或不正常的錯誤發生
#define ISR_FILL_PROC_QUEUE	0


// DDRAW=1 ==>	 debug 用,在執行完FILL_PROC_QUEUE後,馬上執行exe_proc_queue
// DEBUG_RELEASE  0:DEBUG /1:RELEASE
#define DEBUG   				0
#define RELEASE					1
#define DEBUG_RELEASE			RELEASE
#define	TPROGBUF				0
#if (DEBUG_RELEASE ==DEBUG)	//VVVVVVVVVVVVVVVVVVVVVV//
#define SAVE_AXIS_CMD   1						//
#define TRACE_Y			1						//
#define DDRAW			0						//
#define REC_TIME_INTERVAL	1					//
#else	//**************************************//
#define SAVE_AXIS_CMD	0						//
#define TRACE_Y			0						//
#define DDRAW			0						//
#define REC_TIME_INTERVAL	0					//
#endif	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^//




#include	"c_pcb.h"




#define FILL_PROC_QUEUE(fnptr,dptr)			\
	fill_proc_queue(fnptr,dptr,#fnptr) ;
	
	
	
#define DEBUG_LOAD_FIELD			0

#if DEBUG_LOAD_FIELD
	void load_field(unsigned long floc , unsigned long len , BYTE *ptr)
	{
		fseek(fp_config_c,floc, SEEK_SET) ;							
		fread(ptr,1,len,fp_config_c) ;
	}
	#define LOAD_FIELD(floc,len,field)								\
		load_field(floc ,len ,(BYTE *)&MachineStatus.field) ;
	
	void save_field(unsigned long floc , unsigned long len , BYTE *ptr)
	{
		fseek(fp_config_c,floc, SEEK_SET) ;							
		fwrite(ptr,1,len,fp_config_c) ;
		if(DDisk){													
			fseek(fp_config_d,floc, SEEK_SET) ;						
			fwrite(ptr,1,len,fp_config_d) ;		
		}
	}
	#define SAVE_FIELD(floc,len,field)								\
		save_field(floc,len,(BYTE *)&MachineStatus.field) ; 
#else
	#define LOAD_FIELD2(floc,field)																										\
		fseek(fp_config_c,floc, SEEK_SET) ;																							\
		fread(&MachineStatus.field,1,sizeof(MachineStatus.field),fp_config_c) ;       	
	                                                                                	
	                                                                                	
	#define SAVE_FIELD2(floc,field)																										\
		fseek(fp_config_c,floc, SEEK_SET) ;																							\
		fwrite(&MachineStatus.field,1,sizeof(MachineStatus.field),fp_config_c) ;      	\
		if(DDisk){																																			\
			fseek(fp_config_d,floc, SEEK_SET) ;																						\
			fwrite(&MachineStatus.field,1,sizeof(MachineStatus.field),fp_config_d) ;			\
		}                                                                             	
	#define LOAD_FIELD(floc,len,field)								\
		fseek(fp_config_c,floc, SEEK_SET) ;							\
		fread(&MachineStatus.field,1,len,fp_config_c) ;
	
	
	#define SAVE_FIELD(floc,len,field)								\
		fseek(fp_config_c,floc, SEEK_SET) ;							\
		fwrite(&MachineStatus.field,1,len,fp_config_c) ;            \
		if(DDisk){													\
			fseek(fp_config_d,floc, SEEK_SET) ;						\
			fwrite(&MachineStatus.field,1,len,fp_config_d) ;		\
		}
	#endif

#define SET_size_off(file_no)														\
	WORD size = MAX_PROG_LINE * sizeof(ProgType_t);									\
	long off	 = (((long)file_no)*MAX_PROG_LINE) * (long)(sizeof(ProgType_t));

#define FAST_DEGREE(gn) 													\
	if( MachineStatus.speed_mode!=AUTO && MachineStatus.axis_no>=gn ){		\
		AxisStartDegree(gn);												\
	}
#define Xval(val)	(val&0xffffL)
#define REAL_FAST    	((MachineStatus.speed_mode == FAST) && (MachineStatus.SimFast==0))
#define SIM_FAST 		((MachineStatus.speed_mode == FAST) && (MachineStatus.SimFast==1))
#define MALLOC(len)																		\
	uint8 alloc_len ;																	\
	uint8 *dptr= (uint8 *)malloc(alloc_len=len) ;										\
	uint8 *tptr= dptr ;
#if NEWV_MDY
#define SET3701_LOOP_TIMES    5000
#else
#define SET3701_LOOP_TIMES    LOOP_TIMES
#endif

#define RESEND_CNT_ARM             100
#define	CLEAR_HOME_INT(base,mark,no)		\
	wDosMem(base,Para51[no] |=	mark);		\
	wDosMem(base,Para51[no] &=	~mark);
#define	CLEAR_HOME_INT_ARM(base,mark)		\
	wDosMem(base,Para51[0]	|= mark);		\
	wDosMem(base,Para51[0]	&= ~mark);	
#define	CLEAR_HOME_INT_X					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPL, 0x01, 0) ;		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x1)	;	\
	}
#define	CLEAR_HOME_INT_Y					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPL, 0x02, 0) ;		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x2)	;	\
	}
#define	CLEAR_HOME_INT_Z					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPL, 0x04, 0);		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x4)	;	\
	}

#define	CLEAR_HOME_INT_A					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPH, 0x01, 1);		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x8)	;	\
	}

#define	CLEAR_HOME_INT_B					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPH, 0x02, 1);		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x10) ;	\
	}


#define	CLEAR_HOME_INT_C					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPH, 0x04, 1) ;		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x20) ;	\
	}

#define	CLEAR_HOME_INT_D					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPD, 0x01, 2) ;		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x40) ;	\
	}

#define	CLEAR_HOME_INT_E					\
	if(axis_type ==	INTEL8051_AXIS){		\
		CLEAR_HOME_INT(IEPD, 0x02, 2) ;		\
	}										\
	else{									\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x80) ;	\
	}


#define	CLEAR_HOME_INT_6					\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x40) ;	
#define	CLEAR_HOME_INT_7					\
		CLEAR_HOME_INT_ARM(ARM_IEP,0x80) ;	


template <class T>
T Verify0(T a , T default_value)
{
	return((a != 0)? a:default_value) ;
}
void ProcessKeyswap() ;
void ascii_out(SCRN_XY x , SCRN_XY y , WORD color , Cptr buf ,bool reverse ) ;

#define TOUCH_ADDR 	((axis_type == INTEL8051_AXIS)?0x58 : 0x164)
#define CHG_a_tbl_XY																				\
									/*X軸命令和Y軸命令對調  */										\
									has_x =	false;													\
									a_tbl[idx+1]		= a_tbl[idx-1]; /*以 a_tbl[idx+1]當暫存*/	\
									a_tbl[idx-1]		= a_tbl[idx] ;								\
									a_tbl[idx]			= a_tbl[idx+1];								
#define sim_motorY        (sim_motor.dabsloc[AXIS_Y]) 

#define ON_StopMotorLine    wDosMem(pc_base+0x16c,(uint8)	0x00) ; 
#define OFF_StopMotorLine    wDosMem(pc_base+0x16c,(uint8)	0xff) ; 

#define ItemNo_bTblSETSPD   10
#define PARA_LINE_NOPASS	15
#define PARA_LINE_PASS		14
#define PARA2_LINE_PASS		13
#define PARA3_LINE_PASS		1
#define PARA3_LINE_PASS		1

#define PARA4_LINE_PASS		7

#define USE_WIRE_GAP		0

#define Axis_ToPos ((GetSign(p_buf,axis) & 0x80)|| MachineStatus.ToPos[axis] || (ServoCutter_axis && (axis==ServoCutter_axis)))

#define USE_REPAIRY ((PCB3_YEAR >=2014))
#define DISABLE_BREAK_FUNC  if(USE_REPAIRY){wDosMem(pc_base+0x1f0,(uint8)0);}
#define ENABLE_BREAK_FUNC   if(USE_REPAIRY){wDosMem(pc_base+0x1f0,(uint8)1);}
#define ISBREAK ((rDosMem(pc_base+0x1f4)&0x1) !=0)
#define UseRepairY(axis) (USE_REPAIRY && axis==AXIS_Y && MachineStatus.repair_y != 0 && p_buf->byth==TH_NULL)
#define MFill_BreakCnt\
	if (UseRepairY(axis) && Axis_ToPos){\
		a_tbl[idx].break_cnt = Grid2_ExtGrid(dw[axis]) ;\
	}\
	else {\
		a_tbl[idx].break_cnt = 0;\
	}

//開始生產、準備生產下一條彈簧、清除探針
#define INI_BREAK_PROC\
	if (USE_REPAIRY && MachineStatus.repair_y !=0){\
		DISABLE_BREAK_FUNC\
		Clr2016s(AXIS_Y);\
		Target_Break_cnt = 0;\
		Fill_BreakCnt(Target_Break_cnt);\
	}

//RunAutoActTbl:有MOVE_Y即把repair累加值填入	
#define SET_BREAK_CNT\
	if (a_tbl->break_cnt != 0){\
		INI_BREAK_PROC;\
		Target_Break_cnt +=a_tbl->break_cnt;\
		Fill_BreakCnt(Target_Break_cnt);\
		ENABLE_BREAK_FUNC\
	}\
	else {\
		DISABLE_BREAK_FUNC\
	}

#define chk_Continuous(line0,line1) (line1 == line0+1)
#define chk_SameDir(mov0,mov1) ((mov0>0 && mov1>0) || (mov0<0 && mov1<0))

#define CHK_ROTATE_A(axis)   	(((axis == AXIS_A) && CHK_ROTW(AXIS_A)))

#define CHK_SPIN(axis) 	(MachineStatus.MotFunc[axis] == SPIN_FUNC)
#define CHK_HOOK(axis) 	(MachineStatus.MotFunc[axis] == HOOK_FUNC)
#define CHK_CUT(axis) 	(MachineStatus.MotFunc[axis] == CUTTER_FUNC)
#define CHK_SLIDE(axis)	(MachineStatus.MotFunc[axis] == SLIDE_FUNC)
#define CHK_ROTW(axis)	(MachineStatus.MotFunc[axis] == ROTW_FUNC || CHK_ROTW1(axis))
#define CHK_ROTW1(axis)	(MachineStatus.MotFunc[axis] == ROTW1_FUNC)
#define CHK_ROTQ(axis)	(MachineStatus.MotFunc[axis] == ROTQ_FUNC)

#define TOUCH_DELAY(th) ((th==0)?((uint8)MachineStatus.TDelay):(th))
#define SHOW_TOUCH_Y 1


#define SPD_TOUCH
#define USE_20SC ((PCB3_YEAR >=2014))
#define CLOSE_SC ((USE_20SC)?1:0)
#define	CHK_SPD_TOUCH(p_buf)((Has_spd(p_buf)) && (p_buf->byth>TH_NULL) && (p_buf->bygcode==2))

#define MAX_YA_CYCLE    	65536
#define	MAX_SA_CYCLE_POS 131072
#define	SA_ABS_ENCR				16

#define USE_ABOUT 0

#define REVERSE_ONCE (!(PCB3_YEAR >=2014))

#define NEW_COLOR
