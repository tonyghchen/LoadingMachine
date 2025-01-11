//#include <math.h>

/*
void FillSpeed_PMfun(ActTbl_t HUGE *a_tbl ,WORD	&idx,uint8 Speed_P,uint8 Speed_M,uint8 Speed_fun)
{
	if((RetTblIdx !=0)&&(idx <RetTblIdx)){
		RetTblIdx++ ;
	}
	EPT_IDX(idx, ActTbl);
	a_tbl[idx].cmd=	SETSPEED_PMFUN	;
	a_tbl[idx].mov=Speed_P ;
	a_tbl[idx].ref=Speed_M ;
	a_tbl[idx].sdchk_pos=Speed_fun ;
	a_tbl[idx].next=0 ;
	idx++ ;			
}
void load_ManSpeed_PMfun(void)
{
#ifdef HNCNC6
	LOAD_FIELD2(FLOC_ManSpeed_PMfun +sizeof(MachineStatus.ManSpeed_PMfun[0])*0,ManSpeed_PMfun[0]) ;
	LOAD_FIELD2(FLOC_ManSpeed_PMfun +sizeof(MachineStatus.ManSpeed_PMfun[0])*1,ManSpeed_PMfun[1]) ;
	LOAD_FIELD2(FLOC_ManSpeed_PMfun +sizeof(MachineStatus.ManSpeed_PMfun[0])*2,ManSpeed_PMfun[2]) ;
#else
	LOAD_FIELD2(FLOC_ManSpeed_PMfun8+sizeof(MachineStatus.ManSpeed_PMfun[0])*0,ManSpeed_PMfun[0]) ;
	LOAD_FIELD2(FLOC_ManSpeed_PMfun8+sizeof(MachineStatus.ManSpeed_PMfun[0])*1,ManSpeed_PMfun[1]) ;
	LOAD_FIELD2(FLOC_ManSpeed_PMfun8+sizeof(MachineStatus.ManSpeed_PMfun[0])*2,ManSpeed_PMfun[2]) ;
#endif
}
void save_ManSpeed_PMfun(void)
{
#ifdef HNCNC6
	SAVE_FIELD2(FLOC_ManSpeed_PMfun +sizeof(MachineStatus.ManSpeed_PMfun[0])*0,ManSpeed_PMfun[0]) ;
	SAVE_FIELD2(FLOC_ManSpeed_PMfun +sizeof(MachineStatus.ManSpeed_PMfun[0])*1,ManSpeed_PMfun[1]) ;
	SAVE_FIELD2(FLOC_ManSpeed_PMfun +sizeof(MachineStatus.ManSpeed_PMfun[0])*2,ManSpeed_PMfun[2]) ;
#else
	SAVE_FIELD2(FLOC_ManSpeed_PMfun8+sizeof(MachineStatus.ManSpeed_PMfun[0])*0,ManSpeed_PMfun[0]) ;
	SAVE_FIELD2(FLOC_ManSpeed_PMfun8+sizeof(MachineStatus.ManSpeed_PMfun[0])*1,ManSpeed_PMfun[1]) ;
	SAVE_FIELD2(FLOC_ManSpeed_PMfun8+sizeof(MachineStatus.ManSpeed_PMfun[0])*2,ManSpeed_PMfun[2]) ;
#endif
}
void SetSpeed_PMfun(uint8 bSpeed_PMfun[])
{
	OUTB2ARM(pc_base+0xB0, bSpeed_PMfun[0]) ;
	OUTB2ARM(pc_base+0xB1, bSpeed_PMfun[1]) ;
	OUTB2ARM(pc_base+0xB2, bSpeed_PMfun[2]) ;
	if((MachineStatus.op_mode == TEST_MODE)|| (MachineStatus.op_mode == STEP_MODE)){
		DispSet3701_ARM.bSpeed_PMfun[0]=bSpeed_PMfun[0] ;
		DispSet3701_ARM.bSpeed_PMfun[1]=bSpeed_PMfun[1] ;
		DispSet3701_ARM.bSpeed_PMfun[2]=bSpeed_PMfun[2] ;
	}
}
void CvtManSpeed_PMfun()
{
	MachineStatus.bManSpeed_PMfun[0]= MachineStatus.ManSpeed_PMfun[0];
	MachineStatus.bManSpeed_PMfun[1]= MachineStatus.ManSpeed_PMfun[1];
	MachineStatus.bManSpeed_PMfun[2]= MachineStatus.ManSpeed_PMfun[2];
}
void ManSpeed_PMfunMody (void)
{
	WORD *w;
	CursorData_t *ptr= *(CurCursor.ptr) ;
	w = (WORD *)(ptr)->var;
	if( *w >= 0x256 ) *w = 0;	
	
	WORD num = (WORD)(w-&MachineStatus.WORD_ManSpeed_PMfun[0])	;
	
	EPT_IDX(num, MachineStatus.ManSpeed_PMfun);
	MachineStatus.ManSpeed_PMfun[num]=BcdToBin(3,MachineStatus.WORD_ManSpeed_PMfun[num]);
	
	CvtManSpeed_PMfun() ;
	open_config("rb+") ;
	save_ManSpeed_PMfun() ;
	close_config() ;
}
void CvtSPDPlus(int idx)
{  
	EPT_IDX(idx, MachineStatus.bSPDPlus); 	
	MachineStatus.bSPDPlus[idx]= MachineStatus.SPDPlus[idx];
}
void CvtSPDMinus(int idx)
{
	EPT_IDX(idx, MachineStatus.bSPDMinus); 
	MachineStatus.bSPDMinus[idx]= MachineStatus.SPDMinus[idx];
}
void CvtSPDFun(int idx)
{
	EPT_IDX(idx, MachineStatus.bSPDFun); 
	MachineStatus.bSPDFun[idx]= MachineStatus.SPDFun[idx];
}
void CvtSPDRate(int idx)
{
	EPT_IDX(idx, MachineStatus.bSPDRate); 
	MachineStatus.bSPDRate[idx]= MachineStatus.SPDRate[idx];
}
void SPDPlusMody (void)
{
	WORD *w;
	CursorData_t *ptr= *(CurCursor.ptr) ;
	w = (WORD *)(ptr)->var;
	if( *w >= 0x256 ) *w = 0;
			
	WORD axis = (WORD)(w-&MachineStatus.WORD_SPDPlus[AXIS_X])	;
	
	EPT_IDX(axis, MachineStatus.SPDPlus); 
	MachineStatus.SPDPlus[axis]=BcdToBin(3,MachineStatus.WORD_SPDPlus[axis]);
	CvtSPDPlus(axis) ;
	open_config("rb+") ;
	save_SPDPlus(axis) ;
	close_config() ;
}
void SPDMinusMody (void)
{
	WORD *w;
	CursorData_t *ptr= *(CurCursor.ptr) ;
	w = (WORD *)(ptr)->var;	
	if( *w >= 0x256 ) *w = 0;
	WORD axis = (WORD)(w-&MachineStatus.WORD_SPDMinus[AXIS_X])	;
	
	EPT_IDX(axis, MachineStatus.SPDMinus); 
	MachineStatus.SPDMinus[axis]=BcdToBin(3,MachineStatus.WORD_SPDMinus[axis]);		
	CvtSPDMinus(axis) ;
	open_config("rb+") ;
	save_SPDMinus(axis) ;
	close_config() ;
}
void SPDFunMody (void)
{
	WORD *w;
	CursorData_t *ptr= *(CurCursor.ptr) ;
	w = (WORD *)(ptr)->var;	
	if( *w >= 0x256 ) *w = 0;
	WORD axis = (WORD)(w-&MachineStatus.WORD_SPDFun[AXIS_X])	;
	
	EPT_IDX(axis, MachineStatus.SPDFun); 
	MachineStatus.SPDFun[axis]=BcdToBin(3,MachineStatus.WORD_SPDFun[axis]);	
	CvtSPDFun(axis) ;	
	open_config("rb+") ;
	save_SPDFun(axis) ;
	close_config() ;
}
void SPDRateMody (void)
{
	WORD *w;
	CursorData_t *ptr= *(CurCursor.ptr) ;
	w = (WORD *)(ptr)->var;	
	if( *w > 0x100 ) *w = 0;
	WORD axis = (WORD)(w-&MachineStatus.WORD_SPDRate[AXIS_X])	;
	
	EPT_IDX(axis, MachineStatus.SPDRate); 
	MachineStatus.SPDRate[axis]=BcdToBin(3,MachineStatus.WORD_SPDRate[axis]);	
	CvtSPDRate(axis) ;	
	open_config("rb+") ;
	save_SPDRate(axis) ;
	close_config() ;
}
struct SPDPM_BUF
{
	bool have_mov[MAX_AXIS] ;
	uint8 bSPDPlus[MAX_AXIS] ;
	uint8 bSPDMinus[MAX_AXIS] ;
	uint8 bSPDFun[MAX_AXIS] ;
};
void SetSPDPMBuf(int axis,int rpm,struct SPDPM_BUF &SPDPMBuf)
{
	uint8 bTblSPDPlus,bTblSPDMinus ,bTblSPDFun ;
	SPDPMBuf.have_mov[axis]=true;
	bool match=false ;
	if((MachineStatus.bTblSETSPD[axis][0] !=0)&& (MachineStatus.bTblSETSPD[axis][1] !=0)){
		int match_idx=0 ;
		int last_idx ;
		match=true ;
		for(; match_idx < ItemNo_bTblSETSPD ; match_idx++){
			if(MachineStatus.bTblSETSPD[axis][match_idx] !=0){
				last_idx = match_idx ;
				if(rpm <= MachineStatus.bTblSETSPD[axis][match_idx]){
					break ;
				}
			}
		} 
		if(match_idx==0){
			bTblSPDPlus= (uint8)0 ;
			bTblSPDMinus=(uint8)0 ;
			bTblSPDFun  =(uint8)0 ;
		}
		else if(match_idx ==ItemNo_bTblSETSPD){
			bTblSPDPlus= (uint8)(MachineStatus.bTblSPDPlus[axis][last_idx]) ;
			bTblSPDMinus=(uint8)(MachineStatus.bTblSPDMinus[axis][last_idx]) ;
			bTblSPDFun=(uint8)(MachineStatus.bTblSPDFun[axis][last_idx]) ;
			
		}
		else{
			//按比率計算
			float	rate = 1.0*(MachineStatus.bTblSETSPD[axis][match_idx]-rpm)/(MachineStatus.bTblSETSPD[axis][match_idx]-MachineStatus.bTblSETSPD[axis][match_idx-1]) ;
			if(rate >1.0){
				rate=1.0 ;
			}
			bTblSPDPlus	 = (uint8)((MachineStatus.bTblSPDPlus[axis][match_idx] -(MachineStatus.bTblSPDPlus[axis][match_idx]  - MachineStatus.bTblSPDPlus[axis][match_idx-1])  * rate)+0.5) ;
			bTblSPDMinus = (uint8)((MachineStatus.bTblSPDMinus[axis][match_idx]-(MachineStatus.bTblSPDMinus[axis][match_idx] - MachineStatus.bTblSPDMinus[axis][match_idx-1]) * rate)+0.5) ;
			bTblSPDFun	 = (uint8)((MachineStatus.bTblSPDFun[axis][match_idx]  -(MachineStatus.bTblSPDFun[axis][match_idx]   - MachineStatus.bTblSPDFun[axis][match_idx-1])   * rate)+0.5) ;
		}
	}
	if(match){
		SPDPMBuf.bSPDPlus[axis]=bTblSPDPlus ;
		SPDPMBuf.bSPDMinus[axis]=bTblSPDMinus ;
		SPDPMBuf.bSPDFun[axis]=bTblSPDFun ;
	}
	else{
		SPDPMBuf.bSPDPlus[axis]=MachineStatus.bSPDPlus[axis] ;
		SPDPMBuf.bSPDMinus[axis]=MachineStatus.bSPDMinus[axis] ;
		SPDPMBuf.bSPDFun[axis]=MachineStatus.bSPDFun[axis] ;
	}
}
DWORD cal_newref(DWORD ref,uint8 pspd,uint8 mspd,uint8 spdfun,uint8 spdrate)
{
	DWORD newref=0;
	
	float set_idx = (float)spdfun/20 ;
	int   t_idx = (set_idx<=2)?0:((set_idx<=3)?1:2) ;
	float extra_ref = (float)((Spd_Table_ACC_Time[t_idx][pspd-1]+Spd_Table_ACC_Time[t_idx][mspd-1])*(spdfun-(20*(t_idx+1))))/580 ;
	DWORD mdy = (DWORD)((ref*4)-((float)spdrate/100)*extra_ref) ;
	
	if(mdy >(pspd+mspd)){
		newref=mdy/4 ;  
	}
	else{
		newref=(pspd+mspd)/4 ;
	}
	return newref;	
}

void GenPMfun (ActTbl_t HUGE  *a_tbl, WORD &idx)
{
	struct SPDPM_BUF SPDPMBuf;
	uint8 use_axis_PLUS, use_axis_MINUS, use_axis_FUN, axis,use_axis_LOWSPD;			
	WORD pmidx=0, a_idx=0;

	while(a_tbl[a_idx].cmd!=END_ACT){
		
		//每行各軸狀態
		while(a_tbl[a_idx].cmd!=UPDATE_LINE	&&	a_tbl[a_idx].cmd!=LOOP_UPDATE_LINE	&&a_tbl[a_idx].cmd!=END_ACT	&&	a_tbl[a_idx].cmd!=T_STOP_OFFSET		&&a_tbl[a_idx].cmd!=T_STOP_OFFSETA){//"UPDATE_LINE==7","LOOP_UPDATE_LINE==33"
			
			EPT_IDX(pmidx, PM_tbl);
			if(((a_tbl[a_idx].cmd<=MOVE_E))||			//MOVE_X==0, MOVE_Y,...MOVE_C==6
			   ((a_tbl[a_idx].cmd>=ZRT_Z) && (a_tbl[a_idx].cmd<=ZRT_E))||
			   ((a_tbl[a_idx].cmd>=LOOP_X) && (a_tbl[a_idx].cmd<=LOOP_E))||			//LOOP_X==26, LOOP_Y,...LOOP_C==
			   (a_tbl[a_idx].cmd==OFFSET_Y)||										//OFFSET_Y==41
			   (a_tbl[a_idx].cmd==OFFSET_Y_M)||			   
			   (a_tbl[a_idx].cmd==MODIFY_Y)||
			   (a_tbl[a_idx].cmd==SAVE_Y_MOV)||			   			   
			   (a_tbl[a_idx].cmd==INCY)){											//INCY==43
				
				axis=chk_PMfun_axis(a_tbl[a_idx].cmd);		//確認命令屬於哪一軸
				//long temp_rpm = absval(cal_rpm(axis,a_tbl[a_idx].ref,a_tbl[a_idx].mov));
				SetSPDPMBuf(axis,absval(cal_rpm(axis,a_tbl[a_idx].ref,a_tbl[a_idx].mov)),SPDPMBuf) ;
				uint8 PLUS_SPD=SPDPMBuf.bSPDPlus[axis],	Minus_SPD=SPDPMBuf.bSPDMinus[axis];
				uint8 LOW_SPD =MachineStatus.bLOWSPD[axis];
				DWORD  axis_ref=a_tbl[a_idx].ref;
				
				if(a_tbl[a_idx].next==0){
					
					//加減速修整
					MDY_PM(PLUS_SPD,Minus_SPD,axis_ref,LOW_SPD);				
											
					//axis的加減速狀態
					FillSpeed_PMfun(PM_tbl,pmidx,PLUS_SPD,Minus_SPD,SPDPMBuf.bSPDFun[axis]) ;				
					a_tbl[a_idx].ref=axis_ref ;
					//移動命令_寫入(寫完加減速命令)
					EPT_IDX(pmidx, PM_tbl);
					PM_tbl[pmidx++]=a_tbl[a_idx++];		

				}
				else if(a_tbl[a_idx].next==1){
					uint8 next1_times=0;
					for(int i=0; i<MAX_AXIS; i++){ //清空now_mov
						SPDPMBuf.have_mov[i]=false;
					}
					for(int i=a_idx; a_tbl[i].next!=0; i++){		//將所有next=1的值填入now
						axis=chk_PMfun_axis(a_tbl[i].cmd);		    //確認命令屬於哪一軸
						SetSPDPMBuf(axis,absval(cal_rpm(axis,a_tbl[i].ref,a_tbl[i].mov)),SPDPMBuf) ;
						next1_times++;
					}
					
					
					//寫加減速
					use_axis_PLUS		= check_use_axis_set(SPDPMBuf.have_mov,SPDPMBuf.bSPDPlus,0);				//--決定用哪軸的加速(選最大)
					use_axis_MINUS	= check_use_axis_set(SPDPMBuf.have_mov,SPDPMBuf.bSPDMinus,0);				//--決定用哪軸的減速(選最大)
					use_axis_FUN		= check_use_axis_set(SPDPMBuf.have_mov,SPDPMBuf.bSPDFun,0);					//--決定用哪軸的功能(選最大)
					use_axis_LOWSPD	= check_use_axis_set(SPDPMBuf.have_mov,MachineStatus.bLOWSPD,0);	  //--決定用哪軸的最小加減速(選最大)
					
					PLUS_SPD	= SPDPMBuf.bSPDPlus[use_axis_PLUS];
					Minus_SPD	= SPDPMBuf.bSPDMinus[use_axis_MINUS];
					LOW_SPD		= MachineStatus.bLOWSPD[use_axis_LOWSPD];
					
					//加減速修整
					MDY_PM(PLUS_SPD,Minus_SPD,axis_ref,LOW_SPD);	
					FillSpeed_PMfun(PM_tbl,pmidx,PLUS_SPD,Minus_SPD,SPDPMBuf.bSPDFun[use_axis_FUN]) ;
					
					for(int i=1; i<=next1_times; i++){		//times---屬next1組的數目
						a_tbl[a_idx].ref=axis_ref ;
						EPT_IDX(pmidx, PM_tbl);		
						PM_tbl[pmidx++]=a_tbl[a_idx++];		//移動命令_寫入(寫完加減速命令)	
					}
				}
			}
		 	else{
		 		EPT_IDX(pmidx, PM_tbl);	
				PM_tbl[pmidx++]=a_tbl[a_idx++];		//非移動命令_寫入

			}					
		}
		if(a_tbl[a_idx].cmd==END_ACT){break;}
		EPT_IDX(pmidx, PM_tbl);
		PM_tbl[pmidx++]=a_tbl[a_idx++];		//UPDATE_LINE命令_寫入
	}
	EPT_IDX(pmidx, PM_tbl);		
	PM_tbl[pmidx++]=a_tbl[a_idx++];		//END_ACT命令_寫入
	
	for(int i=0; i<pmidx; i++){
		a_tbl[i]=PM_tbl[i];
	}
	idx=pmidx;	
}
uint8 chk_PMfun_axis(uint16 cmd)
{
	uint8 axis;	
	if((cmd==OFFSET_Y)||(cmd==OFFSET_Y_M)||(cmd==MODIFY_Y)||(cmd==SAVE_Y_MOV)||(cmd==INCY)){
		axis=AXIS_Y;
	}
	else if((cmd>=ZRT_Z)&&(cmd<=ZRT_E)){
		axis=cmd-ZRT_Z+AXIS_Z;
	}	
	else if((cmd>=LOOP_X)&&(cmd<=LOOP_E)){
		axis=cmd-LOOP_X;
	}
	else{axis=cmd;}

	if(axis>=8){
			StopMotor();
			ToManProc();

			DispMsgWin_q(-1, -1, MSG_WIN, "各軸加減速_命令錯誤", 
									  "Mulit-Axis PMfun CMD Err"
									  "Mulit-Axis PMfun CMD Err");

			WAIT_NEW_KEY();
			ClrMsgWin_q();		
	}	
	return(axis);
}
uint8 check_use_axis_set(bool have_mov[], uint8 pm_set[], bool choose)
{
	uint8 use_axis=0, have_set=(choose==0)?0:999, axis;

	for(axis=0; axis<MAX_AXIS; axis++){
		if(have_mov[axis]!=false){
			switch(choose){
				case 0:
					if(pm_set[axis]	>=	have_set){
						have_set=pm_set[axis];
						use_axis = axis;
					}
					break;
				case 1:
					if(pm_set[axis]	<=	have_set){
						have_set=pm_set[axis];
						use_axis = axis;
					}
					break;	
			}       
		}           
	}               
	return (use_axis);
}
void MDY_PM(uint8 &PLUS_SPD,uint8 &Minus_SPD,DWORD &axis_ref,uint8 LOW_SPD)
{
	float avg_pm = (PLUS_SPD+Minus_SPD)/2;
	if(avg_pm > axis_ref){
		float oref = (float)axis_ref;
		float oP = (float)PLUS_SPD;
		float oM = (float)Minus_SPD;
		float new_axis = avg_pm*sqrt((oref/avg_pm));
		axis_ref = (DWORD)(new_axis+0.5);
		PLUS_SPD  = (uint8)(((float)(axis_ref*2)*oP /(oP+oM))+0.5);
		Minus_SPD = (uint8)(((float)(axis_ref*2)*oM /(oP+oM))+0.5);
		
		if (axis_ref < LOW_SPD){	//修改後還比最小加減速
			Minus_SPD = PLUS_SPD = axis_ref = LOW_SPD;
		}
	}
}
*/
