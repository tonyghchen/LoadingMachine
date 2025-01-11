
void FillSpeed_PMfun(ActTbl_t HUGE *a_tbl ,WORD	&idx,uint8 Speed_P,uint8 Speed_M,uint8 Speed_fun)
{
		if((RetTblIdx !=0)&&(idx <RetTblIdx)){
			RetTblIdx++ ;
		}
		a_tbl[idx].cmd=	SETSPEED_PMFUN	;
		a_tbl[idx].mov=Speed_P ;
		a_tbl[idx].ref=Speed_M ;
		a_tbl[idx].sdchk_pos=Speed_fun ;
		a_tbl[idx].next=0 ;
		idx++ ;
	
}

/*
void load_ManSpeed_PMfun(void)
{
	LOAD_FIELD2(FLOC_ManSpeed_PMfun+sizeof(MachineStatus.ManSpeed_PMfun[0])*0,ManSpeed_PMfun[0]) ;
	LOAD_FIELD2(FLOC_ManSpeed_PMfun+sizeof(MachineStatus.ManSpeed_PMfun[0])*1,ManSpeed_PMfun[1]) ;
	LOAD_FIELD2(FLOC_ManSpeed_PMfun+sizeof(MachineStatus.ManSpeed_PMfun[0])*2,ManSpeed_PMfun[2]) ;
}
void save_ManSpeed_PMfun(void)
{
	SAVE_FIELD2(FLOC_ManSpeed_PMfun+sizeof(MachineStatus.ManSpeed_PMfun[0])*0,ManSpeed_PMfun[0]) ;
	SAVE_FIELD2(FLOC_ManSpeed_PMfun+sizeof(MachineStatus.ManSpeed_PMfun[0])*1,ManSpeed_PMfun[1]) ;
	SAVE_FIELD2(FLOC_ManSpeed_PMfun+sizeof(MachineStatus.ManSpeed_PMfun[0])*2,ManSpeed_PMfun[2]) ;
}
void SetSpeed_PMfun(uint8 bSpeed_PMfun[])
{
	OUTB2ARM(pc_base+0xB0, bSpeed_PMfun[0]) ;
	OUTB2ARM(pc_base+0xB1, bSpeed_PMfun[1]) ;
	OUTB2ARM(pc_base+0xB2, bSpeed_PMfun[2]) ;
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
	MachineStatus.ManSpeed_PMfun[num]=BcdToBin(3,MachineStatus.WORD_ManSpeed_PMfun[num]);
	
	CvtManSpeed_PMfun() ;
//	open_config("rb+") ;
	save_ManSpeed_PMfun() ;
	close_config() ;
}




void load_SPDPlus(int idx)
{
	LOAD_FIELD(FLOC_SPDPlus+idx*LEN_SPDPlus,LEN_SPDPlus,SPDPlus[idx]) ;
}
void save_SPDPlus(int idx)
{
	SAVE_FIELD(FLOC_SPDPlus+idx*LEN_SPDPlus,LEN_SPDPlus,SPDPlus[idx]) ;
}

void load_SPDMinus(int idx)
{
	LOAD_FIELD(FLOC_SPDMinus+idx*LEN_SPDMinus,LEN_SPDMinus,SPDMinus[idx]) ;
}
void save_SPDMinus(int idx)
{
	SAVE_FIELD(FLOC_SPDMinus+idx*LEN_SPDMinus,LEN_SPDMinus,SPDMinus[idx]) ;
}
void load_SPDFun(int idx)
{
	LOAD_FIELD(FLOC_SPDFun+idx*LEN_SPDFun,LEN_SPDFun,SPDFun[idx]) ;
}
void save_SPDFun(int idx)
{
	SAVE_FIELD(FLOC_SPDFun+idx*LEN_SPDFun,LEN_SPDFun,SPDFun[idx]) ;
}


void CvtSPDPlus(int idx)
{   	
	MachineStatus.bSPDPlus[idx]= MachineStatus.SPDPlus[idx];
}
void CvtSPDMinus(int idx)
{
	MachineStatus.bSPDMinus[idx]= MachineStatus.SPDMinus[idx];
}
void CvtSPDFun(int idx)
{
	MachineStatus.bSPDFun[idx]= MachineStatus.SPDFun[idx];
}

void SPDPlusMody (void)
{
	WORD *w;
	CursorData_t *ptr= *(CurCursor.ptr) ;
	w = (WORD *)(ptr)->var;
	if( *w >= 0x256 ) *w = 0;
			
	WORD axis = (WORD)(w-&MachineStatus.WORD_SPDPlus[AXIS_X])	;
	
	MachineStatus.SPDPlus[axis]=BcdToBin(3,MachineStatus.WORD_SPDPlus[axis]);
	CvtSPDPlus(axis) ;
//	open_config("rb+") ;
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

	MachineStatus.SPDMinus[axis]=BcdToBin(3,MachineStatus.WORD_SPDMinus[axis]);		
	CvtSPDMinus(axis) ;
//	open_config("rb+") ;
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

	MachineStatus.SPDFun[axis]=BcdToBin(3,MachineStatus.WORD_SPDFun[axis]);	
	CvtSPDFun(axis) ;	
//	open_config("rb+") ;
	save_SPDFun(axis) ;
	close_config() ;
}

*/

//�[��t--------------------------------------------------------------------------------------------------------------------------	
void GenPMfun (ActTbl_t HUGE  *a_tbl, WORD &idx)
{
	bool have_mov[MAX_AXIS];
	

	uint8 use_axis_PLUS, use_axis_MINUS, use_axis_FUN, axis;			
	WORD pmidx=0, a_idx=0;


	while(a_tbl[a_idx].cmd!=END_ACT){
		
		//�C��U�b���A
		while(a_tbl[a_idx].cmd!=UPDATE_LINE	&&	a_tbl[a_idx].cmd!=LOOP_UPDATE_LINE	&&a_tbl[a_idx].cmd!=END_ACT){	//"UPDATE_LINE==7","LOOP_UPDATE_LINE==33"
			
			if(((a_tbl[a_idx].cmd>=MOVE_X) && (a_tbl[a_idx].cmd<=MOVE_D))||			//MOVE_X==0, MOVE_Y,...MOVE_C==6
			   ((a_tbl[a_idx].cmd>=LOOP_X) && (a_tbl[a_idx].cmd<=LOOP_D))||			//LOOP_X==26, LOOP_Y,...LOOP_C==
			   (a_tbl[a_idx].cmd==OFFSET_Y)||										//OFFSET_Y==41
			   (a_tbl[a_idx].cmd==OFFSET_Y_M)||			   
			   (a_tbl[a_idx].cmd==MODIFY_Y)||
			   (a_tbl[a_idx].cmd==SAVE_Y_MOV)||			   			   
			   (a_tbl[a_idx].cmd==INCY)){											//INCY==43
				
				axis=chk_PMfun_axis(a_tbl[a_idx].cmd);		//�T�{�R�O�ݩ���@�b
				
				
				uint8 PLUS_SPD=MachineStatus.bSPDPlus[axis],	Minus_SPD=MachineStatus.bSPDMinus[axis];
				DWORD  axis_ref=a_tbl[a_idx].ref;
//				if(axis_ref<5){axis_ref=5;}
				if(a_tbl[a_idx].next==0){			
									
					//�[��t�׾�
					if(((PLUS_SPD+Minus_SPD)/2)>axis_ref){
//						PLUS_SPD=Minus_SPD=axis_ref;
//						PLUS_SPD=0 ;
						axis_ref=(PLUS_SPD+Minus_SPD)/2;
					}
					
					//axis���[��t���A
					FillSpeed_PMfun(PM_tbl,pmidx,PLUS_SPD,Minus_SPD,MachineStatus.bSPDFun[axis]) ;				
					a_tbl[a_idx].ref=axis_ref ;
					//���ʩR�O_�g�J(�g���[��t�R�O)
					PM_tbl[pmidx++]=a_tbl[a_idx++];			

				}
				else if(a_tbl[a_idx].next==1){
					uint8 next1_times=0;
					for(int i=0; i<MAX_AXIS; i++){   				 //�M��now_mov
						have_mov[i]=false;
					}
					for(int i=a_idx; a_tbl[i].next!=0; i++){		//�N�Ҧ�next=1���ȶ�Jnow
						axis=chk_PMfun_axis(a_tbl[i].cmd);		    //�T�{�R�O�ݩ���@�b
						have_mov[axis]=true;
						next1_times++;
					}
					
					
					//�g�[��t
					use_axis_PLUS=check_use_axis_set(have_mov,MachineStatus.bSPDPlus);			//--�M�w�έ��b���[�t
					use_axis_MINUS=check_use_axis_set(have_mov,MachineStatus.bSPDMinus);			//--�M�w�έ��b����t
					use_axis_FUN=check_use_axis_set(have_mov,MachineStatus.bSPDFun);				//--�M�w�έ��b���\��
					
					PLUS_SPD=MachineStatus.bSPDPlus[use_axis_PLUS];
					Minus_SPD=MachineStatus.bSPDMinus[use_axis_MINUS];
					
					//�[��t�׾�
					if(((PLUS_SPD+Minus_SPD)/2)>axis_ref){
//						PLUS_SPD=Minus_SPD=axis_ref;
//						PLUS_SPD=0 ;
						axis_ref=(PLUS_SPD+Minus_SPD)/2;
					}
					
					FillSpeed_PMfun(PM_tbl,pmidx,PLUS_SPD,Minus_SPD,MachineStatus.bSPDFun[use_axis_FUN]) ;
					
					for(int i=1; i<=next1_times; i++){		//times---��next1�ժ��ƥ�
						a_tbl[a_idx].ref=axis_ref ;
						PM_tbl[pmidx++]=a_tbl[a_idx++];		//���ʩR�O_�g�J(�g���[��t�R�O)	
					}						
				}		
			}
		 	else{
				PM_tbl[pmidx++]=a_tbl[a_idx++];		//�D���ʩR�O_�g�J

			}					
		}
		if(a_tbl[a_idx].cmd==END_ACT){break;}
		PM_tbl[pmidx++]=a_tbl[a_idx++];		//UPDATE_LINE�R�O_�g�J
	}
	PM_tbl[pmidx++]=a_tbl[a_idx++];		//END_ACT�R�O_�g�J
	
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
	else if((cmd>=LOOP_X)&&(cmd<=LOOP_D)){
		axis=cmd-LOOP_X;
	}
	else{axis=cmd;}
	if(axis>=7){
//			StopMotor();//�s620
//			ToManProc();//�s620

			DispMsgWin_q(-1, -1, MSG_WIN, "�U�b�[��t_�R�O���~", 
									  "Mulit-Axis PMfun CMD Err"
									  "Mulit-Axis PMfun CMD Err");

			WAIT_NEW_KEY();
			ClrMsgWin_q();		
	}	
	return(axis);
}

uint8 check_use_axis_set(bool have_mov[], uint8 pm_set[])
{
	uint8 use_axis=0, have_set=0, axis;

	for(axis=0; axis<MAX_AXIS; axis++){
		if(have_mov[axis]){
			if(pm_set[axis]	>=	have_set){
				have_set=pm_set[axis];
				use_axis = axis;
			}
		}
	}
	return (use_axis);
}


//--------------------------------------------------------------------------------------------------------------------------------	





