#include "header.h"
bool rdflagStopRun()
{
	return(flagStopRun) ;
}
void d()
{
	float a=0 ;
	for(int i=0 ;i < 300000 ; i++){
		a= a+0.5 ;
	}
}
#define TIMER_DISPX   100
void IDLE_RUN (void)
{
// 	static WORD ChkSel, ChkCount;

// 		if(NewH&&(MachineStatus.op_mode==MAN_MODE)&&MachineStatus.bysafe_plugin&&MachineStatus.safe_sw == SAFE_TEST) { //�s�W�s�D�O�w���˸m����
// 			SAFE_TEST_new();
// 		}

// 	UC bb=rDosMem(pc_base+0xf5) ; 
// 	if( MachineStatus.op_mode&(MAN_MODE+RUN_MODE+TEST_MODE+STEP_MODE+TMODY_MODE+SMODY_MODE) ){
// 		
// 		if( ++ChkCount > 25 ){
// 			switch( ++ChkSel&3 )
// 			{
// 			case 0:
// 				//ChkOverFlowStop();
// 				if(flag_RRealAxis&&(MachineStatus.op_mode&(MAN_MODE))){
// 					RRealAxis() ;
// 				}
// 				break;
// 			case 1:
// 				if(PORT_EX0 || PORT_STOPRUN){
// 					// debounce
// 					for(long l=0 ; l< DEBOUNCE_TIME; l++) ;

// 					if( PORT_EX0){
// 							printf("ExStop__");
// 						ChkExStop();
// 					}
// 					else if(PORT_STOPRUN&& (slide_axis==0) &&(MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE))){
// 						flagStopRun=true ;
// 					}
// 				}
// 				break;
// 			case 2:
// 				if (ReadAbs_Err){
// 					//DispReadAbsMotorFailure();
// 					ReadAbs_Err = false;
// 				}
// 				if( MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE) )
// 					ChkStopWire(); //�s�u�[�[�t
// 				if( FileRWErr )
// 					//DispFileRWError_q(FileRWErr);
// 				if( RW3701Err ){
// 					//DispRW3701Error(0,RW3701Err);
// 					//DispErr(false,true) ;
// 					RW3701Err=0 ;
// 				}
// 				if(RESEND3701Err){
// 					//DispRW3701Error(1,RESEND3701Err);
// 					//DispErr(false,true) ;
// 					RESEND3701Err=0 ;
// 				}
// 				if(DS3701Err){
// 					//DispRW3701Error(2,DS3701Err);
// 					//DispErr(false,true) ;
// 					DS3701Err=0 ;
// 				}
// 				if(Err_ExtEncoder){
// 					//DispExtEncoderError() ;
// 					Err_ExtEncoder=false ;
// 				}
// 				
// 				if(NewH){//�s�D���^���H��
// 					if(chk_unconnector){ //�Ͳ��M����ˬd
// 						chk_unconnector= false ;				
// 						for(int axis=0 ; axis < MachineStatus.axis_no; axis++){
// 							if(((axis !=AXIS_Y)&& MachineStatus.motor[axis]) || ((axis == AXIS_Y) && !MachineStatus.y_suspend)){
// 								if(!MachineStatus.bMotorNEAR[axis]){
// 									if(bb & 0x1){
// 										DispMotorUnconnectError(axis) ;
// 									}		
// 								}
// 							}
// 							bb>>=1 ;
// 						}
// 						
// 						if( PORT_OIL0 && !MachineStatus.OilChk){//�Ѫo�˴��Ѱ� //��M���F�u���F�ۦP�P�_
// 							printf("Oil__");
// 							ChkOilStop();
// 						}
// 					}
// 				//ChkOverFlowStop();
// 				}
// 				break;
// 			case 3:
// 				if( MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE) ){
// 					//if( MachineStatus.dcur_th[0] || MachineStatus.dcur_th[1] )
// 					//	DispTouchPos();
// 					//else if( MachineStatus.dcur_th[2] || MachineStatus.dcur_th[3] )
// 					//	DispTouchPos();
// 					if( MachineStatus.safety_door ){
// 						if( MachineStatus.op_mode&(RUN_MODE) ){
// 							if( PORT_SAFETY_DOOR0 ){
// 								// debounce
// 								for(long l=0 ; l < DEBOUNCE_TIME ; l++) ;
// 							}
// 							if(PORT_SAFETY_DOOR0 ){
// 								printf("SafeDoor__");
// 								ChkDoorStop();
// 							}
// 						}
// 					}
// 				}
// 				else if( MachineStatus.op_mode&MAN_MODE ){
// 					//�ˬd���w�O�_�QĲ�o
// 					if(NewH){
// 						if((rDosMem(pc_base+INL) &0x40)){
// 							ShowTouchTest(1) ;
// 						}
// 						if((rDosMem(pc_base+INL) &0x80)){
// 							ShowTouchTest(2) ;
// 						}
// 						if((rDosMem(pc_base+INL) &0x8)){
// 							ShowTouchTest(3) ;
// 						}
// 						if((rDosMem(pc_base+INL) &0x10)){
// 							ShowTouchTest(4) ;
// 						}
// 					}
// 				}
// 				//chk_ScrnSav() ;
// 				break;
// 			}
// 			ChkCount = 0;
// 		}
// 	}
// 	
// 	/*
// 	chk_ErrMsg() ;
// 	update_flash() ;
// 	*/
// 	update_run_DDA() ;

}
void  always_run()
{	
// 	//BgPrintf() ;
// 	if(NewH && MachineStatus.op_mode == MAN_MODE){
// 		if(CHK_ROTW(AXIS_A)&& MachineStatus.motor[AXIS_A] && !(rDosMem(pc_base+INM) &0x08)&& KeyLockCHG && keyswap ){//�~�����s�W�^���I�ץ�
// 		//is_first_a=false ;
// 		DispManualSet_q() ;
// 		
// 	int tcurloc = BcdToBin(8,MachineStatus.axis_val[AXIS_A] ,MachineStatus.sign[AXIS_A]);
// 		EnableHomeInt(AXIS_A,BITmask[7-AXIS_A],ENABLE_STOP)  ; // �]�w�~�����IA�G�O��,�ϱoA�b�٨�
// 		if(!ChkDriverClear((uint8)AXIS_A)){
// 			do{
// 				update_run_DDA() ;
// 				//FORCE_PROC_QUEUE
// 				//if(set_ScrnSav()){
// 				//	continue ;
// 				//}
// //				CalNextManMov() ;
// 				if(DDAState ==0 && STEP_DDAState==0){
// 					if( Reset )SoftReset();
// 					if(tcurloc>=0){MANMOV_AXIS((AXIS_A), MINUS_SIGN, (KEY_PLUS_A),AXIS_A_REPEAT,0,0);}
// 					else {MANMOV_AXIS((AXIS_A), PLUS_SIGN, (KEY_PLUS_A),AXIS_A_REPEAT,0,0);}

// 				}
// 			}
// 			while(!ChkDriverClear((uint8)AXIS_A));
// 		}
// 		DDAState=0 ;
// 		DisableHomeInt(AXIS_A,0)  ; // �����~�����IA�G�O��,�ϱoA�b�٨�
// 		ResetDriverClear() ;


// 		{
// //		DisableHomeInt(AXIS_A) ;
// 			//ClrMsgWin_q();
// 			
// 				dDelay(2) ;
// 			sendError(ManualSet,0,3);
// 			//�M��k�䪺���I
// 			
// 			dDelay(2) ;
// 			sendError(AutoHome,1,3);
// 			//DispMsgWin_q(-1, -1, MSG_WIN, "�۰ʦ^���I��....." ,
// 			// 							  " Automatic Go Home .... ",
// 			// 							  " Automatic Go Home .... ");
// 										  
// 			//FORCE_PROC_QUEUE
// 			
// 			
// 			Adjust_AZero_NewH() ;
// 			set_zrt_power_on(AXIS_A) ;
// 		}
// 		sTimerSet(10) ;
// 		ClrKeyBuf() ;
// 		ClrMsgWin_q();
// 		
// 		MachineStatus.sign[AXIS_A]	   = PLUS_SIGN;
// 		MachineStatus.axis_val[AXIS_A] = 0;
// 		DispCurAxis_q(1);
// 		//FORCE_PROC_QUEUE
// 		Clr2016s(AXIS_A); 		sTimerSet(10) ;
// 		ClrKeyBuf() ;
// 		
// 		//ClrMsgWin_q();
// 		
// 		//is_first_a=false ;	//½�u���^���I��Reset�|���Ƥ�ʾɤަ^���I
// 		//double_chk_is_first_a=false;//����½�u���
// 		//is_first_a=false;
// 		dDelay(2) ;
// 		sendError(AutoHome,0,3);
// 		}
// 	}
// 	/*
// 	//printf("%d\n",rDosMem(pc_base+0xc24));
// 		if(rDosMem(pc_base+0xc24)!=0x7){
// 			wr_rs232(4);wr_rs232(3);wr_rs232(1) ;	
// 			d();
// 		}
// 		else{
// 			wr_rs232(4);wr_rs232(3);wr_rs232(0) ;	
// 			d();
// 		}
// 	if(MachineStatus.op_mode ==MAN_MODE){
// 		wr_rs232(4); wr_rs232(1); wr_rs232(1);
// 		d();
// 		wr_rs232(4); wr_rs232(14); wr_rs232(1);
// 		d();
// 	}
// 	else{
// 		wr_rs232(4); wr_rs232(1); wr_rs232(0);
// 			d();
// 		wr_rs232(4); wr_rs232(14);wr_rs232(0);
// 			d();
// 	}
// 	*/
// 	if(MachineStatus.op_mode == MAN_MODE){//���տO�ק�
// 		if(ReadAdc100() < 3){
// 			if(!EnableTest){
// 				//�I�Gtest LED
// 				EnableTest=true ;
// 					wr_rs232(4); wr_rs232(4); wr_rs232(1);
// 			d();
// 			}
// 		}
// 		else{
// 			if(EnableTest){
// 				EnableTest=false ;
// 					wr_rs232(4); wr_rs232(4); wr_rs232(0);
// 			d();
// 			}
// 		}
// 	}
// /*

// 	if( MachineStatus.op_mode&(RUN_MODE) ){
// 		if( MachineStatus.set8254 ){
// 			nSet8254(MachineStatus.cur8254);
// 			MachineStatus.set8254 = 0;
// 		}
// 	}
// 	else if( MachineStatus.op_mode&(TEST_MODE) ){
// 		if (flag_TouchSPDChange ){
// 			flag_TouchSPDChange  = false;
// 			update_sc(1) ;
// 		}
// 		else {
// 			update_sc(0) ;
// 		}
// 	}
// 	else 
// 	*/if( MachineStatus.op_mode&STEP_MODE ){
// 		if(IsTimeUp(time_out_step)){
// 			if( GetNextKey() != KEY_HAND_RIGHT ){
// 				SetClock(STEP_CLOCK);
// 			}
// 		}
// 	}
// //ReMake-------------------
// 	if(ReMake_flag){	
// 		ReMakeActTable();
// 		ReMake_flag=false;
// 		flag_complete_spring=true ;	
// 	}
// /*

// 	if(flag_RRealAxis&&(MachineStatus.op_mode & RUN_MODE)){
// 		uint16 cur_x=dReadAbsPos(AXIS_X) ;
// 		if(SaveRBuf.axis_x < cur_x ){
// 			SaveRBuf.axis_x= cur_x ;
// 			
// 			EPT_IDX(SaveRBuf.idx,	SaveRBuf.buf) ;
// 			SaveRBuf.buf[SaveRBuf.idx][0]=cur_x ;
// 			for(uint8 axis =1 ; axis < MachineStatus.axis_no ; axis++){
// 				
// 				EPT_IDX(SaveRBuf.idx,	SaveRBuf.buf) ;
// 				EPT_IDX(axis,	SaveRBuf.buf[0]) ;
// 				SaveRBuf.buf[SaveRBuf.idx][axis]=dReadAbsPos(axis) ;
// 			}
// 			SaveRBuf.idx++ ;
// 			if(SaveRBuf.idx==16000){SaveRBuf.idx=0;}
// 		} 
// 	}
// 	
// 	if(stBATCHn.airON){
// 		if(IsTimeUp(stBATCHn.timeout)){
// 			stBATCHn.airON=0 ;
// 			SetAir(stBATCHn.airno,0) ;
// 		}
// 	}
// */
// 	//if( (!(MachineStatus.op_mode & PARA_MODE))&&(slide_axis)&& key_flg &&(PORT_STOPRUN ||((Get_Zrt_io(slide_axis)==0)&& !in_movToZeroAll))){
// 	if( (!(MachineStatus.op_mode & PARA_MODE))&&(slide_axis)&& key_flg &&(PORT_STOPRUN) && MachineStatus.motor[slide_axis] && MachineStatus.SlideLimit){//���A�Ʈy�����ץ�
// 		key_flg=false ;
// 		DispSlideError() ;
// 		ResetDriverClear();
// 	}
// 	else if( (!(MachineStatus.op_mode & PARA_MODE))&& (key_flg) &&(PORT_STOPRUN) && (!slide_axis)){//UV1�s�W���w���A���M���~
// 		key_flg=false ;
// 		DispServoCutterError();
// 	}
// /*
// 	if(flag_VerifyProg){
// 		flag_VerifyProg=false ;
// 		VerifyProg(MachineStatus.speed_mode,0,0);
// 	}
// 	if(flagSPIN_ZRT){
// 		MovToZeroAll(1) ;
// 		virtual_move(false) ;
// 		flagSPIN_ZRT=false ;
// 	}
// 	if(disp_y){
// 		static SDWORD lmov ;
// 		SDWORD mov= (WORD)dReadAbsPos(AXIS_Y) ;
// 		static long cnt=0 ;
// 		cnt++ ;
// 		if((mov != lmov)||(cnt == 0x1234)){
// 			if(cnt == 0x1234){
// 				st_extencoder.updategap=true ;
// 			}
// 			cnt=0 ;
// 			lmov = mov ;
// 			INI_DISP_BUF();
// 			SDWORD encoder_mov = mov ;
// 			mov= ExtGrid2_Grid(mov); //�~��encoder������ഫ�����F���
// 			pDispBuf_value +=	BinToStrBuf(6, mov, pDispBuf);
// 			FILL_DISP_BUF(' ') ;
// 			pDispBuf_value +=	BinToStrBuf(6, encoder_mov, pDispBuf);
// 			FILL_DISP_BUF(0);
// 			DispStrLine_q(0, 0,	WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
// 		}
// 	}

// 	
// 	
// 	
// #if CHK_MAN_MOV
// 	if(chk_man_mov.boenable){
// 		ChkManMov() ;
// 	}
// #endif	
// 	//�ˬd��L��J�����J,�è̷Ӥ��P�u�@�Ҧ���s���
// 	*/
// 	ngetkey() ;
// 	/*
// 	chk_off_power(1) ;
// 	if(ChkExtRstSW_IO()){
// 		flag_run= false ;
// 		SoftReset(); 
// 	}
// #if SW_SIM_MOTOR
// 	Updatesim_motorabsloc() ;
// #endif


// 	
// 	if( Reset||MachineStatus.safe_err ){
// 		flag_run= false ;
// 		if(Reset)SoftReset();
// 	}
// 	
// 	*/
// 	chk_off_power(1) ;
// 	if( KeyBufRIdx != KeyBufWIdx ){
// 		if(NewH &&DDAState ==0){
// 			// have a key ���s�]�wtime out�ɶ�
// 			if(!set_ScrnSav()){
// 				KeyProcMap();
// 			}
// 		}
// 	}

// 	
// 	for(int i=0 ; i < 4 ; i++){
// 		if(flag_ClrTouchPos[i]){
// 			flag_ClrTouchPos[i]= false ;
// 			int loc=1 ;
// 			for(int j=0 ; j < i ; j++){
// 				loc*=2 ;
// 			}
// 			ClrTouchPos(1,loc) ;
// 		}
// 	}
// 	/*
// 	if(flag_DispMissNo){
// 		flag_DispMissNo=false ;
// 		DispMissNo_q() ;
// 	}
// 	*/
// 	if( MachineStatus.th_stop ){
// 		TouchErrStop();
// 	}
// 	/*
// 	if(st_DispStatusBar.flag){
// 		st_DispStatusBar.flag=false ;
// 		INI_DISP_BUF();
// 		if(st_DispStatusBar.axis	< AXIS_A){
// 			FILL_DISP_BUF2(('X'+st_DispStatusBar.axis), ':');
// 		}
// 		else{
// 			FILL_DISP_BUF2(('A'+st_DispStatusBar.axis-AXIS_A), ':');
// 		}
// 		if(	(long)st_DispStatusBar.dst_pos > 0 ){
// 			FILL_DISP_BUF('+');
// 			pDispBuf_value +=	BinToStrBuf(6, st_DispStatusBar.dst_pos, pDispBuf);
// 		}
// 		else{
// 			FILL_DISP_BUF('-');
// 			pDispBuf_value +=	BinToStrBuf(6, -(long)st_DispStatusBar.dst_pos, pDispBuf);
// 		}
// 		Fill_pDispBuf(" have a key ���s�]�wtime out�ɶ�" ,
//         "Prior	work have not finished !");
// 		FILL_DISP_BUF(0);
// 		DispStatusBar_q(DispBuf);
// 	}

// */
}
struct TIMER time_out_delay	;
void RunAutoActTbl (DWORD dcur_x)
{	
// 	BYTE	 axis, miss;
// 	BYTE  th ;
// 	bool  StartWire=false ;
// 	SDWORD  dst_pos_offset_mov ;	
// 	chk_run_touch=0;

// 	dcur_x= dcur_x ;
// 	
// 	pp[0]=(UC*) & RActtbl[0];
// 	BYTE NEXT ,CMD; 
// 	do{
// 		miss=0;
// 	struct Pmove *move=(struct Pmove *)pp[ActTblIdx];
// 	//struct Pnull *null=(struct Pnull *)pp[ActTblIdx];
// 	struct Ploop_s *loop_start=(struct Ploop_s *)pp[ActTblIdx];
// 	struct Ploop_mov *loop_mov=(struct Ploop_mov *)pp[ActTblIdx];
// 	struct Ploop_update *loop_update=(struct Ploop_update *)pp[ActTblIdx];
// 	struct Pset_delay *set_delay=(struct Pset_delay *)pp[ActTblIdx];
// 	struct Pwait_delay *wait_delay=(struct Pwait_delay *)pp[ActTblIdx];
// 	struct Pwait_motor *wait_motor=(struct Pwait_motor *)pp[ActTblIdx];
// 	struct Pupdate *update=(struct Pupdate *)pp[ActTblIdx];
// 	struct PsetAir *get_air=(struct PsetAir *)pp[ActTblIdx];
// 	struct PsetTouch *setTouch=(struct PsetTouch *)pp[ActTblIdx];
// 	struct PclrTouch *clrTouch=(struct PclrTouch *)pp[ActTblIdx];
// 	//struct PclrAir *clr_air=(struct PclrAir *)pp[ActTblIdx];
// 	struct Pend *end=(struct Pend *)pp[ActTblIdx++];
// 		
// 	struct Pmove *Nmove=(struct Pmove *)pp[ActTblIdx];
// 		/* 
// 	struct Pend *Nend=(struct Pend *)pp[ActTblIdx];
// 	struct Pnull *Nnull=(struct Pnull *)pp[ActTblIdx];
// 	struct Ploop_s *NLoop_start=(struct Ploop_s *)pp[ActTblIdx];
// 	struct Ploop_mov *Nloop_mov=(struct Ploop_mov *)pp[ActTblIdx];
// 	struct Ploop_update *Nloop_update=(struct Ploop_update *)pp[ActTblIdx];
// 	struct Pset_delay *Nset_delay=(struct Pset_delay *)pp[ActTblIdx];
// 	struct Pwait_delay *Nwait_delay=(struct Pwait_delay *)pp[ActTblIdx];
// 	struct Pupdate *Nupdate=(struct Pupdate *)pp[ActTblIdx];
// 			*/
// 	CMD=end->cmd;
// 	NEXT=end->next;
// 			//printf("NEXT=%d\n",NEXT);
// 	switch (end->cmd){
// 				
// 			case END_ACT :
// 				//printf("END_ACT:");
// 				//printf("_%d_%d",end->cmd,end->next);
// 				CMD=end->cmd;
// 				NEXT=end->next;
// 				ActTblIdx--;
// 				if(NewH && !safedumpchk&& MachineStatus.bysafe_plugin && MachineStatus.safe_sw == SAFE_ON){
// 					safedumpchk=1;
// 				}			
// 				keydump=0;
// 			break;
// 				
// 				case MOVE_X:
// 				case MOVE_Y:
// 				case MOVE_Z:
// 				case MOVE_A:
// 				case MOVE_B:
// 				case MOVE_C:
// 				case MOVE_D:
// 				case MOVE_E:
// 					CMD=move->cmd;
// 					NEXT=move->next;
// 				SDWORD	dst_pos= move->dst_pos ; //newpara
// 				uint8 axis = (uint8)move->cmd;
// 				uint8 starwire = (uint8)(NEXT & 0x10);
// 				int static cntt=0;
// 				//printf("axis=%d mov=%ld\n",axis,move->mov);
// 				//SDWORD	mov=move->mov ,ref= move->ref,rmov= move->mov;//dst_pos= move->u.dst_pos , //newpara
// 				/*
// 					if (move->cmd == MOVE_Y){
// 						//SET_BREAK_CNT;
// 					}
// 					if(move->cmd <=MOVE_E){
// 						uint8 axis = (uint8)move->cmd;
// 						WaitNearCnt[axis] = 0;
// 					}
// 		*/	
// /*					
// #if	DEBUG_RUNAUTOACTTBL
// 				static int cnt=0 ;
// 				if((move->cmd == MOVE_X)&&	(cnt ==0)){
// 					cnt++ ;
// 					x_loc= Read2016(AXIS_X)	; //�����^���I�ɪ�2016��
// 				}
// #endif		
// */	
// /*			
// 				if((ServoCutter_axis !=0)&& (move->cmd == (MOVE_X+ServoCutter_axis))){
// 					flag_ServoCutter=true ;
// 				}
// 				else{
// 					flag_ServoCutter=false ;
// 				}
// 				x_cnt=y_cnt=0;
// 				//if(a_tbl->cmd != MOVE_Y && axis!=AXIS_Y &&!AutoHook.boauto_mode)MachineStatus.dst_pos[AXIS_Y]=0; //�e�u�S��J�ɬ�0�ץ�(�����ճ]�w���w���S�e�u�ɷ|��ܤW�@�q�e�u�q)
// */
// 				SDWORD	mov=move->mov ,ref= move->ref,rmov= move->mov;//dst_pos= move->u.dst_pos , //newpara
// 				SDWORD   idms=move->idms ;
// 				
// #if 1		//G3�|�y��z�b���I�]��									
// 				if((move->cmd >=MOVE_Z)&&(move->cmd <=MOVE_E)){
// 					int idx= move->cmd -MOVE_X ;
// 					if(loopchk[idx] && MachineStatus.loop_cnt[MachineStatus.loop_ptr-1]){
// 						mov=move->loopmov ;
// 						rmov=move->loopmov;
// 						ref= move->loopref ;
// 						//mov=0 ;
// 						//rmov=0;
// 						//ref= 0 ;
// 						loopchk[idx]=false ;
// 					}
// 				}
// #endif
// /*
// #if 0

// //#ifdef SPD_TOUCH
// 				if (MachineStatus.op_mode == TEST_MODE){
// 					if(move->cmd <=MOVE_E){
// 						if(move->spd_th.ref != 0){
// 							ref = a_tbl->spd_th.ref;
// 						}
// 					}
// 				}
// #endif
// */
// 				//�p���b�]"���w���U�b"�A�ӻݭn�׸�MOV_Z~D
// 				
// 				/*
// 				if(MachineStatus.Touch_Stop_Flag){
// 					if((move->cmd >= MOVE_Z) &&(move->cmd	<= MOVE_E)	&&T_Stop_idx){	
// 						uint8 cmd_axis=move->cmd - MOVE_X;
// 						
// 						EPT_IDX(cmd_axis, T_Stop_MdyVAL);		//T_Stop_MdyVAL
// 						//�˹�A�b�O�_�ɨ�(�Ҧ�2�A�A��)
// 						bool T_Stop_mov_flag=true;	//���w���U�b�Ature�~���v
// 						if(MachineStatus.Touch_Stop_Flag==2 && cmd_axis==AXIS_A	&& CHK_ROTW(AXIS_A)){
// 							if(!T_Stop_Amov_flag){T_Stop_mov_flag=false;}//A�b�ɨ����󦨥�(�Ҧ�2�A�Ȧb�^���I�ɸɨ�)
// 							else{T_Stop_Amov_flag=false;}
// 						}
// 						if(T_Stop_MdyVAL[cmd_axis]	&& T_Stop_mov_flag){					
// //							Sprintf("axis=%d, val=%d, flag=%d",cmd_axis,T_Stop_MdyVAL[cmd_axis],T_Stop_mov_flag);	//�ثe���v���p
// 							mov+=T_Stop_MdyVAL[cmd_axis];				
// 							EPT_IDX(cmd_axis, T_Stop_MdyVAL);
// 							T_Stop_MdyVAL[cmd_axis]=0;		//�ץ������l
// 						}
// 					}
// 				}					
// 				*/
// 				
// 				/*
// 				if((move->cmd == ZRT_Z) ||(move->cmd == ZRT_A) ||	(move->cmd	== ZRT_B)||	(move->cmd	== ZRT_C)|| (move->cmd== ZRT_D)|| (move->cmd== ZRT_E)){
// 					zrt_cnt=0 ;
// 					for(int	i=0	; i	< 5	; i++){
// 						if(move->cmd==(ZRT_Z+i)){
// 							axis= MOVE_Z+i ;
// 							{
// 								DWORD t= dReadAbsPos(AXIS_Z+i) ;
// 								SDWORD loc=0;
// 								if(axis_type ==	INTEL8051_AXIS	&&		((DWORD)t<(DWORD)ZABCD_2016[i]))	loc = SDWORD((DWORD)(0x10000-ZABCD_2016[i])+(DWORD)t);
// 								else if(axis_type==ARM_AXIS		&&		((DWORD)t<(DWORD)ZABCD_2016[i]))	loc = SDWORD((DWORD)(0xffffffff-ZABCD_2016[i]+1)+(DWORD)t);
// 								else loc= SDWORD((DWORD)t-(DWORD)ZABCD_2016[i])	;
// 								//if(axis==AXIS_B)Sprintf("Abs=%d, ZABCD_2016=%d, loc=%d",t,ZABCD_2016[i],loc);
// 								//���թα��b
// 								DWORD grids = BMOTORGRID(axis) ;
// 								while(loc < 0){
// 									loc+= grids ;
// 								}
// 								loc	= loc %grids	;
// 								loc=grids-loc ;
// 								mov	= loc+50 ;

// 	

// 								EPT_IDX((AXIS_Z+i), MachineStatus.go_home);
// 								EPT_IDX((AXIS_Z+i), EnableHomeInt_ZrtMode);
// 								MachineStatus.go_home[AXIS_Z+i]	= 1	;
// 								//�̷Ӧ^���I�Ҧ��]�w���P���X��
// 								switch(MachineStatus.ZrtMode[AXIS_Z+i]){
// 								case 0:
// 								case 1:
// 									EnableHomeInt(AXIS_Z+i)	;
// 									break ;
// 								case 2:
// 									EnableHomeInt_ZrtMode[AXIS_Z+i]= true ;
// 									break ;
// 								}
// 							}
// 							//�p���b�]"���w���U�b"�A�ӻݭn�׸�Zrt_Z~D
// 							if(MachineStatus.Touch_Stop_Flag){
// 								
// 								//�˹�A�b�O�_�ɨ�(�Ҧ�2�A�A��)
// 								bool T_Stop_mov_flag=true;	//���w���U�b�Ature�~���v
// 								if(MachineStatus.Touch_Stop_Flag==2 && axis==AXIS_A	&& CHK_ROTW(AXIS_A)){
// 									if(!T_Stop_Amov_flag){T_Stop_mov_flag=false;}//A�b�ɨ����󦨥�(�Ҧ�2�A�Ȧb�^���I�ɸɨ�)
// 									else{T_Stop_Amov_flag=false;}
// 								}							
// 																
// 								if(T_Stop_idx	&&	T_Stop_MdyVAL[axis]	&&T_Stop_mov_flag){	
// //									Sprintf("mov =%d T_Stop_MdyVAL[axis]=%d",mov , T_Stop_MdyVAL[axis]) ;				
// 									mov+=T_Stop_MdyVAL[axis];				
// 									EPT_IDX(axis, T_Stop_MdyVAL);
// 									T_Stop_MdyVAL[axis]=0;
// 								}
// 							}
// 						}
// 					}
// 				}
// 				else if( miss ){
// 					axis = AXIS_X +	(move->cmd-MISS_X);
// 				}
// 				else{
// 					axis = AXIS_X +	(move->cmd-MOVE_X);
// 				}
// 				if((axis == AutoHook.byaxis) && MachineStatus.in_loop){
// 					bool move_hook = true ;
// 					for(int i=0 ; i < MachineStatus.loop_ptr ; i++){
// 						if(MachineStatus.loop_cnt[i] != 0){
// 							//�j��ĤG���H�W,���n���ʧ���
// 							move_hook=false ;
// 						}
// 					}
// 					if(!move_hook)break ;
// 				}
// 				*/

// 				
// 				
// 				SDWORD ymov=0 ;
// 				if((move->cmd==OFFSET_Y) || (move->cmd == OFFSET_Y_M)|| (move->cmd == INCY)){
// 				/*
// 					SDWORD offset_mov , incy ;
// 					rmov=0 ;
// 					axis= AXIS_Y ;
// 					EPT_IDX(axis, T_Stop_MdyVAL);
// 					//newpara dst_pos= 0 ;
// 					if(move->cmd == OFFSET_Y|| (move->cmd == OFFSET_Y_M)){
// 						offset_mov =  move->mov ;
// 						if(loopchk[AXIS_A] && MachineStatus.loop_cnt[MachineStatus.loop_ptr-1]){
// 							//offset_mov=move->loopmov ; //newpara
// 						}
// 						
// 						//�p�G��AXIS_A�B����u�A�hAXIS_Y�ݭn�ɥ� (���w���U�b)
// 						if(MachineStatus.Touch_Stop_Flag){
// 							
// 							//�˹�A�b�O�_�ɨ�(�Ҧ�2�A�A��)
// 							bool T_Stop_mov_flag=true;	//���w���U�b�Ature�~���v
// 							if(MachineStatus.Touch_Stop_Flag==2 ){
// 								if(!T_Stop_Amov_flag)T_Stop_mov_flag=false;//A�b�ɨ����󦨥�(�Ҧ�2�A�Ȧb�^���I�ɸɨ�)
// 							}
// 																						
// 							if(	CHK_ROTW(AXIS_A) &&	T_Stop_MdyVAL[AXIS_A]	&&T_Stop_idx	&&T_Stop_mov_flag){
// 								offset_mov+=T_Stop_MdyVAL_Y;
// 								T_Stop_MdyVAL_Y=0;
// 							}
// 						}						
// 						
// 						
// 						if((move->cmd == OFFSET_Y_M) && MachineStatus.y_suspend){
// 							offset_mov += MDY_GAPY ;
// 						}
// 						dst_pos_offset_mov=move->dst_pos ;
// 						ref = move->ref ;
// 						ActTblIdx++ ;
// 						move=Nmove ;
// 						Nmove = (struct Pmove *)&(pp[ActTblIdx]);
// 					}
// 					else{
// 						offset_mov = 0 ;
// 					}
// 					if(move->cmd == INCY){
// 						incy = (move->mov) * MachineStatus.loop_cnt[MachineStatus.loop_ptr-1] ;
// 						
// 						//�p�G��AXIS_A�B����u�A�hAXIS_Y�ݭn�ɥ� (���w���U�b)
// 						if(MachineStatus.Touch_Stop_Flag){
// 							
// 							//�˹�A�b�O�_�ɨ�(�Ҧ�2�A�A��)
// 							bool T_Stop_mov_flag=true;	//���w���U�b�Ature�~���v
// 							if(MachineStatus.Touch_Stop_Flag==2 ){
// 								if(!T_Stop_Amov_flag)T_Stop_mov_flag=false;//A�b�ɨ����󦨥�(�Ҧ�2�A�Ȧb�^���I�ɸɨ�)
// 							}							
// 							
// 							if(	CHK_ROTW(AXIS_A) &&	T_Stop_MdyVAL[AXIS_A]	&& T_Stop_idx	&& T_Stop_mov_flag){
// 								incy+=T_Stop_MdyVAL_Y;
// 								T_Stop_MdyVAL_Y=0;
// 							}
// 						}						
// 						
// 						
// 						ref = move->ref ;
// 						ActTblIdx++ ;
// 						move=Nmove ;
// 						Nmove = (struct Pmove *)&(pp[ActTblIdx]);
// 					}
// 					else{
// 						incy =0 ;
// 					}
// 					if(move->cmd == MOVE_Y){
// 						mov =move->mov ;
// 						//�p�G��AXIS_A�B����u�A�hAXIS_Y�ݭn�ɥ� (���w���U�b)
// 						if(MachineStatus.Touch_Stop_Flag){
// 							
// 							bool T_Stop_mov_flag=true;	//���w���U�b�Ature�~���v
// 							if(MachineStatus.Touch_Stop_Flag==2 ){
// 								if(!T_Stop_Amov_flag)T_Stop_mov_flag=false;//A�b�ɨ����󦨥�(�Ҧ�2�A�Ȧb�^���I�ɸɨ�)
// 							}
// 												
// 							if(	CHK_ROTW(AXIS_A) &&	T_Stop_MdyVAL[AXIS_A]	&& T_Stop_idx	&& T_Stop_mov_flag){
// 								incy+=T_Stop_MdyVAL_Y;
// 								T_Stop_MdyVAL_Y=0;
// 							}
// 						}							
// 						
// 						//newpara dst_pos=move->u.dst_pos ;
// 						ref= move->ref ;
// 						ActTblIdx++ ;
// 						move=Nmove ;
// 						Nmove = (struct Pmove *)&(pp[ActTblIdx]);
// 					}
// 					else{
// 						mov = 0 ;
// 						//newpara dst_pos=0 ;
// 					}
// 					if(incy !=0){
// 						mov= mov+incy ;
// 						//newpara Grid2Unit(AXIS_Y,incy) ;
// 						//newpara dst_pos += incy ;
// 					}
// 					if(MachineStatus.y_suspend){
// 						mov = 0 ;
// 						//newpara dst_pos=0 ;
// 					}
// 					
// 					//newpara SET_BREAK_CNT;//��w:�u���ɽu�|DISABLE,���e�u�|��w
// 					
// 					ymov = rmov= mov ;
// 					mov = mov+offset_mov ;
// 					if(CHK_ROTW1(AXIS_A) && (MachineStatus.Y_Encoder != 2) && (MachineStatus.y_suspend)&& (offset_mov)){
// 						if((offset_mov == MDY_GAPY1)&& (dst_pos_offset_mov == MDY_GAPY1)){
// 							mov = 0 ; 
// 						}
// 					}
// 					ActTblIdx-=2 ;
// 					move= (struct Pmove *)&(pp[ActTblIdx++]);
// 					Nmove= (struct Pmove *)&(pp[ActTblIdx]);
// 					*/
// 				}
// 				else{
// 					if(axis==AXIS_Y	&& MachineStatus.y_suspend ) break;
// 					ymov = (axis == AXIS_Y)? move->mov :0 ;
// 				}


// 				bool run = true	;
// 				if((axis_type == ARM_AXIS) && (move->next ==1)&& (Nmove->next	== 1)){
// 					run	= false	;
// 				}
// 					
// 					//if(mov ==0){
// 					//	ref =0 ;
// 					//}
// 					Set3701(axis, PLUS_SIGN, ref, mov,rmov,run,(axis==AXIS_Y)?ymov:0,idms);
// 					//Set3701(move->cmd, PLUS_SIGN, move->ref, move->mov,move->mov,run,0,0);
// 					MachineStatus.dst_pos[axis] =dst_pos; 
// 					MachineStatus.running[move->cmd]	= 1;running_cnt[move->cmd]=0;
// 					if(	axis==AXIS_Y &&	MachineStatus.op_mode==RUN_MODE	) {
// 						if((NEXT & 0x2)){
// 							ChkStartWire(1);//��python�P�_,ARM����=1�ɰe�T��
// 						}
// 					}
// 					//RUN_MISS_SET_AIR
// 					//RUN_SET_AIR
// 					//RUN_CLR_AIR
// 					break;
// 				case SET_AIR://4byte	
// 					//CMD=update->cmd;
// 					//NEXT=update->next;
// 					wDosMem(pc_base+OUTL , (MachineStatus.air_buf |= get_air->u.air));
// 				break;
// 				case CLR_AIR://4byte	
// 					//CMD=update->cmd;
// 					//NEXT=update->next;
// 					wDosMem(pc_base+OUTL , (MachineStatus.air_buf &= get_air->u.air));
// 				break;
// 				case UPDATE_LINE://4byte	
// 					CMD=update->cmd;
// 					NEXT=update->next;
// 					CurLine=update->line;
// 					
// 					//MachineStatus.last_line	=(	MachineStatus.in_loop )? a_tbl->u.line :(WORD)a_tbl->mov;
// 					//RUN_UPDATE_LINE1
// 				break;
// 				
// 				case LOOP_START:
// 					MachineStatus.loop_times[MachineStatus.loop_ptr] = (WORD)(loop_start->mov);//a_tbl
// 					MachineStatus.loop_cnt[MachineStatus.loop_ptr] = 0;
// 					MachineStatus.loop_stack[MachineStatus.loop_ptr] = ActTblIdx ;	//a_tbl->u.loop_idx;
// 					ini_loopchk(false) ;
// 					MachineStatus.loop_ptr++;
// 				break;
// 			case WAIT_MOTOR_NEAR_IN_LOOP :
// 				if(MachineStatus.in_loop){
// 					//printf("3\n");
// 					MWAIT_MOTOR_NEAR(20,timeout_WAIT_MOTOR_NEAR_IN_LOOP)
// 				}
// 				break ;
// 			case LOOP_X:
// 			case LOOP_Y:
// 			case LOOP_Z:
// 			case LOOP_A:
// 			case LOOP_B:
// 			case LOOP_C:
// 			case LOOP_D:
// 			case LOOP_E:
// 				if(	MachineStatus.in_loop ){
// 					axis = AXIS_X +	(loop_mov->cmd-LOOP_X);
// 					
// 				//(���w���U�b)------------------------------		
// 					SDWORD	mov=loop_mov->mov;		
// 					//printf("%ld	\n",mov);
// 					Set3701(axis, PLUS_SIGN, loop_mov->ref, mov,mov,true,(axis==AXIS_Y)? mov:0,loop_mov->idms);
// 					
// 					MachineStatus.dst_pos[axis] =	loop_mov->u.dst_pos;
// 					MachineStatus.running[axis]	= 1;running_cnt[axis]=0;
// 					if(	axis==AXIS_Y &&	MachineStatus.op_mode==RUN_MODE	) 
// 							ChkStartWire(1);//��python�P�_,ARM����=1�ɰe�T��
// 						//ChkStartWire(mov);
// 				}
// 				break;
// 			case LOOP_UPDATE_LINE:
// 				MachineStatus.last_line	=(	MachineStatus.in_loop )? loop_update->u.line :(WORD)loop_update->mov;
// 				RUN_UPDATE_LINE1
// 			case LOOP_CHECK:
// 					//printf("5\n");
// 				if(	!MachineStatus.loop_times[MachineStatus.loop_ptr-1]	){
// 					MachineStatus.in_loop =	0;
// 					MachineStatus.loop_ptr--;
// 				}
// 				else{
// 					MachineStatus.in_loop =	1;
// 					MachineStatus.loop_times[MachineStatus.loop_ptr-1]--;
// 					MachineStatus.loop_cnt[MachineStatus.loop_ptr-1]++;
// 				}
// 				break;
// 			case LOOP_END:
// 				if(	MachineStatus.in_loop ){
// 	//				ActTblIdx =	LoopStar_idx;
// 					ActTblIdx =	MachineStatus.loop_stack[MachineStatus.loop_ptr-1];
// 					ini_loopchk(true) ;
// 					return;
// 				}
// 				ini_loopchk(false) ;
// 				break;
// 			case SET_DELAY:
// 				time_out_delay=	mTimerSet(set_delay->u.Delay);
// 				//time_out_delay=	mTimerSet(1000);
// 				break ;
// 			case WAIT_DELAY:
// 				if((TimerTicks2.timer-time_out_delay.timer) < 0 ){
// 					ActTblIdx--	;
// 				}
// 				break ;
// 				
// 		case SET_TOUCH: 			
// 			//if(CHK_MATCH_LINE(a_tbl)){	
// 				has_SET_TOUCH=true ;									
// 				th = setTouch->t.touch ;													
// 				ini_th_stopy() ;													
// 				if(	th==TH1_STP	|| th==TH1_CHK ){										
// 					MachineStatus.rec_th[0]	 = 	PROG_VAL_NULL;							
// 					MachineStatus.pass_th[0] = 0;										
// 					MachineStatus.chk_th[0]	 = th;										
// 					MachineStatus.chk_th_stop_axis[0]  = setTouch->t.stop_axis;			
// 					if(th== TH1_CHK){													
// 						DISABLE_TOUCH_STOP(1) ;											
// 					}																	
// 					else{																
// 						TOUCH_STOP(1,	STOPY) ;										
// 					}																	
// 					ENABLE_TOUCH_INT(1) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT6 ;								
// 					wDosMem(pc_base+OUTL ,MachineStatus.air_buf) ;						
// 				}																		
// 				else if( th==TH2_STP ||	th==TH2_CHK	){									
// 					MachineStatus.rec_th[1]	 =  PROG_VAL_NULL ;							
// 					MachineStatus.pass_th[1] = 0 ;										
// 					MachineStatus.chk_th[1]	 = th ;										
// 					MachineStatus.chk_th_stop_axis[1]  = setTouch->t.stop_axis ;			
// 					if(th== TH2_CHK){													
// 						DISABLE_TOUCH_STOP(2) ;											
// 					}																	
// 					else{																
// 						TOUCH_STOP(2,	STOPY) ;										
// 					}																	
// 					ENABLE_TOUCH_INT(2) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT7 ;								
// 					wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						
// 				}																		
// 				else if( th	== TH3_STP ){												
// 					MachineStatus.rec_th[2]	 =PROG_VAL_NULL ;							
// 					MachineStatus.pass_th[2] = 0 ;										
// 					MachineStatus.chk_th[2]	 = th ;										
// 					MachineStatus.chk_th_stop_axis[2]  = setTouch->t.stop_axis ;			
// 					TOUCH_STOP(3,	STOPY) ;											
// 					ENABLE_TOUCH_INT(3) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT4 ;								
// 					wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						
// 				}																		
// 				else if( th	== TH4_STP ){												
// 					MachineStatus.rec_th[3]	 = PROG_VAL_NULL ;							
// 					MachineStatus.pass_th[3] = 0 ;										
// 					MachineStatus.chk_th[3]	 = th ;										
// 					MachineStatus.chk_th_stop_axis[3]  = setTouch->t.stop_axis ;			
// 					TOUCH_STOP(4,	STOPY) ;											
// 					ENABLE_TOUCH_INT(4) ;												
// 					MachineStatus.air_buf	 |=	MASK_BIT5 ;								
// 					wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;						
// 				}																		
// 				//if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == RUN_MODE){			
// 				//	nSet8254(a_tbl->spd_th.sc8254);										
// 				//}																		
// 				//else if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == TEST_MODE){	
// 				//	TouchSPD.change = true;												
// 				//	TouchSPD.spd    = a_tbl->spd_th.spd;								
// 				//	TouchSPD.speed  = a_tbl->spd_th.speed;								
// 				//	MachineStatus.set8254 = 1;											
// 				//	update_sc(1);														
// 				//}													
// 				
// 				//RUN_SET_TOUCH2(setTouch)
// 			//}
// 			break;
// 		case CLR_TOUCH:			
// 			if(has_SET_TOUCH){	
// 				
// 				DispCurAxis_q(0);
// 				has_SET_TOUCH=false ;
// 				
// 					ini_th_stopy() ;																		
// 					th = clrTouch->t.touch ;																	
// 					if(	th==TH1_STP	|| th==TH1_CHK ){														
// 						DISABLE_TOUCH_STOP(1)																
// 						ResetDriverClear() ;
// 						if(chk_utouch(0,clrTouch->utouch.start,clrTouch->utouch.end) ){				
// 							if(	th==TH1_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	1 ;	
// 							DISABLE_INPORT_INT(MASK_BIT6) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT6) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[0]){													
// 								flag_ClrTouchPos[0]=true ;												
// 							}																	
// 							miss = 1 ;											
// 						}																					
// 						MachineStatus.pass_th[0] = 0 ;														
// 						MachineStatus.chk_th[0]	 = 0 ;														
// 					}																						
// 					else if( th==TH2_STP ||	th==TH2_CHK	){													
// 						DISABLE_TOUCH_STOP(2)																
// 						ResetDriverClear() ;																
// 						if(	chk_utouch(1,clrTouch->utouch.start,clrTouch->utouch.end) ){							
// 							if(	th==TH2_STP	&& MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	2 ;	
// 							DISABLE_INPORT_INT(MASK_BIT7) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT7) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[1]){													
// 								flag_ClrTouchPos[1]=true ;													
// 							}																			
// 							miss = 1 ;																		
// 						}																					
// 						MachineStatus.pass_th[1] = 0 ;														
// 						MachineStatus.chk_th[1]	 = 0 ;														
// 					}																						
// 					else if( th	== TH3_STP ){																
// 						DISABLE_TOUCH_STOP(3)																
// 						ResetDriverClear() ;																
// 						if(chk_utouch(2,clrTouch->utouch.start,clrTouch->utouch.end) ){							
// 							if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 3 ;				
// 							DISABLE_INPORT_INT(MASK_BIT3) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT4) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[2]){													
// 								flag_ClrTouchPos[2]=true ;													
// 							}																				
// 							miss = 1 ;																		
// 						}																					
// 						MachineStatus.pass_th[2] = 0 ;														
// 						MachineStatus.chk_th[2]	 = 0 ;														
// 					}																						
// 					else if( th	== TH4_STP ){																
// 						DISABLE_TOUCH_STOP(4)																
// 						ResetDriverClear() ;																
// 						if(	chk_utouch(3,clrTouch->utouch.start,clrTouch->utouch.end) ){							
// 							if(	MachineStatus.set_miss == 0x01 )  MachineStatus.th_stop	= 4 ;				
// 							DISABLE_INPORT_INT(MASK_BIT4) ;													
// 							MachineStatus.air_buf &= (~MASK_BIT5) ;											
// 							wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;									
// 							if(!MachineStatus.pass_th[3]){													
// 								flag_ClrTouchPos[3]=true ;													
// 							}																				
// 							miss = 1 ;																		
// 						}																					
// 						MachineStatus.pass_th[3] = 0 ;														
// 						MachineStatus.chk_th[3]	 = 0 ;														
// 					}																						
// 					if(	!MachineStatus.miss_flag &&	miss ){													
// 						MachineStatus.miss_flag	= 1 ;														
// 						if(	MachineStatus.set_miss ){														
// 								uint8 sign=PLUS_SIGN ;													
// 							MachineStatus.cur_miss++;
// 							SendCur_miss();
// 							printf("cur_miss%d\n",MachineStatus.cur_miss);
// 							flag_DispMissNo=true ;															
// 						}																					
// 					}																						
// 					//if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == RUN_MODE){							\
// 					//	nSet8254(a_tbl->spd_th.sc8254);														\
// 					//}																						\
// 					//else if (a_tbl->spd_th.sc8254 && MachineStatus.op_mode == TEST_MODE){					\
// 					//	TouchSPD.change = false;															\
// 					//	TouchSPD.spd    = 0;																\
// 					//	TouchSPD.speed  = 0;																\
// 					//	MachineStatus.set8254 = 1;															\
// 					//	update_sc(1);																		\
// 					//}		
// 				
// 				//RUN_CLR_TOUCH1
// 			}
// 			break;
// 			case CHK_TOUCH:
// 			{
// 				chk_run_touch=1;
// 				BYTE th = setTouch->t.touch;
// 				uint8 idx = 0;
// 				bool TouchStatus;
// 				if(NewH){
// 					TouchStatus=rDosMem(pc_base+DriverClear) &0x2 ;
// 					printf("TouchStatus=%d \n",TouchStatus);
// 					switch (th){
// 						case TH1_STP:
// 							idx=1;
// 							if(TouchStatus)MachineStatus.pass_th[idx-1]=true ;
// 							break;
// 						case TH2_STP:
// 							idx=2;
// 							if(TouchStatus)MachineStatus.pass_th[idx-1]=true ;
// 							break;
// 						case TH3_STP:
// 							idx=3;
// 							if(TouchStatus)MachineStatus.pass_th[idx-1]=true ;
// 							break;
// 						case TH4_STP:
// 							idx=4;
// 							if(TouchStatus)MachineStatus.pass_th[idx-1]=true ;
// 							break;
// 					}			
// 				}
// 				if ((idx!=0 && (MachineStatus.pass_th[idx-1])||TouchStatus)){
// 					MachineStatus.pass_th[idx-1]=true ;
// 					if(MachineStatus.set_miss==0x01	)	MachineStatus.th_stop =	idx;
// 					switch (idx){
// 						case 1:MachineStatus.air_buf &= (~MASK_BIT6) ;break;
// 						case 2:MachineStatus.air_buf &= (~MASK_BIT7) ;break;
// 						case 3:MachineStatus.air_buf &= (~MASK_BIT4) ;break;
// 						case 4:MachineStatus.air_buf &= (~MASK_BIT5) ;break;
// 					}	
// 					wDosMem(pc_base+OUTL , MachineStatus.air_buf) ;	
// 					if(	!MachineStatus.miss_flag){
// 						MachineStatus.miss_flag	= 1;
// 						if(	MachineStatus.set_miss ){
// 							uint8 sign=PLUS_SIGN ;
// 							MachineStatus.cur_miss++;
// 							SendCur_miss();
// 							//printf("cur_miss%d\n",MachineStatus.cur_miss);
// 							flag_DispMissNo=true;
// 						}
// 					}
// 					flag_ClrTouchPos[idx-1]=true ;
// 					if (TouchStatus)MachineStatus.touch_before_err = true;
// 				}
// 				break;
// 			}
// 			default:
// 				break;	
// 			}
// 		}while(((NEXT&0x01) && (*((pp[ActTblIdx])+1)&0x01))||(CMD==SETSPEED_PMFUN) || (CMD==UPDATE_LINE) || (CMD==CHK_TOUCH) || (CMD==DISABLE_REPAIR_Y));	
// }
// void ISR_AUTO_RUN()
// {
// // 	switch( MachineStatus.run_state){
// // 	case CHK_REMAKE_AUTO:
// // 		if(!ReMake_flag){MachineStatus.run_state = CHK_AUTO_RUN;}
// // 		break;		
// // 	case CHK_AUTO_RUN :
// // 		if( (*pp[ActTblIdx] != END_ACT )){
// // 			if(ChkAllMotorFinish()){
// // 				//KeyClrY();
// // 				RunAutoActTbl(0);
// // 			}
// // 		}
// // 		else{
// // 			//
// // 			//	�w�g�����@���u®���R�O
// // 			//	
// // 			//MachineStatus.cur_quan+=1;//�p��
// // 			//printf("Cnt=%d\n",MachineStatus.cur_quan);//���q
// // 			if( MachineStatus.op_mode&(TEST_MODE+STEP_MODE) ){
// // 				if( MachineStatus.prog_mody ){
// // 					//StartRecActtbl=true;
// // 					MachineStatus.op_mode = TMODY_MODE;
// // 					SetClock(OFF_CLOCK);
// // 					KeyTest();
// // 					//ReMake_flag=true;
// // 					MachineStatus.run_state = CHK_REMAKE_AUTO;
// // 					return ;
// // 				}
// // 			}
// // 			if(!MachineStatus.prog_mody){
// // // 				AirTblIdx=0;
// // 				flag_complete_spring_cmd=true ;
// // 				MachineStatus.run_state = CHK_AUTO_END;
// // 				st_extencoder.first= true ;
// // 			}
// // 		}
// // 		break ;
// // 	case CHK_AUTO_END :
// // 	default:
// // 		if(ChkAllMotorFinish()){
// // 			//ClrTouch();
// // 			//__disable_irq();
// // 			//__enable_irq();
// // 			Read_ZABCD_2016() ;	
// // 			if( MachineStatus.stop_machine){
// // 				//�����u®���Ͳ�
// // 				flag_run=false ;
// // 				flag_ReturnManMode=true ;
// // 				DISABLE_BREAK_FUNC;//�ɥ�

// // 				return ;
// // 			}
// // 			else{
// // 				MachineStatus.run_state = CHK_AUTO_RUN;//CHK_REMAKE_AUTO;
// // 				MachineStatus.miss_flag = 0;
// // 				ActTblIdx				= RetTblIdx;
// // 				flag_complete_spring=true ;
// // 				return ;
// // 			}
// // 		}
// // 		break ;
// // 	}
// // 	if(AirTblOn){
// // 		
// // 		// �ˬdtouch & air
// // #ifdef CLR_X_ABSPOS		
// // 		X_ABSPOS=dReadAbsPos(AXIS_X) ;
// // 		WORD wcur_x = (WORD)(X_ABSPOS%BMOTORGRID(AXIS_X));
// // #else
// // 		WORD wcur_x = (WORD)wRead2016(AXIS_X); //+ BcdToBin(2, MachineStatus.repair_dst));
// // #endif
// // 		
// // 		if(wcur_x==0&& (ldir == PLUS_MOVE)) {
// // // 			AirTblIdx=0; //x�b�]�@��(�L���I)��,AirTblIdx�k�s
// // 		}

// // 		if((MachineStatus.axis_val[AXIS_X] > lcur_x) && (ldir == PLUS_MOVE)){		
// // // 			if((AirTbl[AirTblIdx].cmd != END_ACT)&&(MachineStatus.axis_val[AXIS_X]>=AirTbl[AirTblIdx].chk_pos && AirTbl[AirTblIdx].chk_pos>=lcur_x)){	
// // // 				//printf("val=%d  %d\n",MachineStatus.axis_val[AXIS_X],AirTbl[AirTblIdx].chk_pos);	
// // // 				RunAirTbl(MachineStatus.axis_val[AXIS_X],PLUS_MOVE) ;
// // // 			}
// // 			lcur_x = MachineStatus.axis_val[AXIS_X] ;
// // 		}
// // 		else if((MachineStatus.axis_val[AXIS_X] < lcur_x) && (ldir == MINUS_MOVE)){			
// // 			//�O�_���׾�AirTblIdx
// // // 			if((AirTblIdx >0) && (MachineStatus.axis_val[AXIS_X] <= AirTbl[AirTblIdx-1].chk_pos  && AirTbl[AirTblIdx].chk_pos<=lcur_x)){
// // // 				RunAirTbl(MachineStatus.axis_val[AXIS_X],MINUS_MOVE) ;
// // // 			}
// // 			lcur_x=MachineStatus.axis_val[AXIS_X] ;
// // 		}
// // 		else if(MachineStatus.axis_val[AXIS_X] != lcur_x){						
// // 			if((ldir == PLUS_MOVE)&& ((MachineStatus.axis_val[AXIS_X]+2) < lcur_x)){
// // 				//�����ܬ�����
// // 				RunAirTbl(MachineStatus.axis_val[AXIS_X],PLUS_MINUS) ;
// // 				
// // 				ldir=MINUS_MOVE ;
// // 				lcur_x = MachineStatus.axis_val[AXIS_X] ;
// // 			}
// // 			if((ldir ==MINUS_MOVE) && ((MachineStatus.axis_val[AXIS_X]-2) > lcur_x)){
// // 				// �����ܬ�����
// // 				RunAirTbl(MachineStatus.axis_val[AXIS_X],MINUS_PLUS) ;
// // 				
// // 				ldir=PLUS_MOVE ;
// // 				lcur_x= MachineStatus.axis_val[AXIS_X] ;
// // 			}
// // 			
// // 		}
// // 		lcur_x= MachineStatus.axis_val[AXIS_X] ;
// // 	}
}

void ISR_FAST_RUN()
{
	
}
