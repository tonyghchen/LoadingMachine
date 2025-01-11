#include "header.h"

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
	static WORD ChkSel, ChkCount;
/*
		if(NewH&&(MachineStatus.op_mode==MAN_MODE)&&MachineStatus.bysafe_plugin&&MachineStatus.safe_sw == SAFE_TEST) { //新增新主板安全裝置測試
			SAFE_TEST_new();
		}

	UC bb=rDosMem(pc_base+0xf5) ; 
	if( MachineStatus.op_mode&(MAN_MODE+RUN_MODE+TEST_MODE+STEP_MODE+TMODY_MODE+SMODY_MODE) ){
		
		if( ++ChkCount > 25 ){
			switch( ++ChkSel&3 )
			{
			case 0:
				//ChkOverFlowStop();
				if(flag_RRealAxis&&(MachineStatus.op_mode&(MAN_MODE))){
					//RRealAxis() ;
				}
				break;
			case 1:
				if(PORT_EX0 || PORT_STOPRUN){
					// debounce
					for(long l=0 ; l< DEBOUNCE_TIME; l++) ;

					if( PORT_EX0){
						//ChkExStop();
							printf("ExStop__");
					}
					else if(PORT_STOPRUN&& (slide_axis==0) &&(MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE))){
						flagStopRun=true ;
					}
				}
				break;
			case 2:
				if (ReadAbs_Err){
					//DispReadAbsMotorFailure();
					ReadAbs_Err = false;
				}
				if( MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE) )
					//ChkStopWire(); //新線架加速
				if( FileRWErr )
					//DispFileRWError_q(FileRWErr);
				if( RW3701Err ){
					//DispRW3701Error(0,RW3701Err);
					//DispErr(false,true) ;
					RW3701Err=0 ;
				}
				if(RESEND3701Err){
					//DispRW3701Error(1,RESEND3701Err);
					//DispErr(false,true) ;
					RESEND3701Err=0 ;
				}
				if(DS3701Err){
					//DispRW3701Error(2,DS3701Err);
					//DispErr(false,true) ;
					DS3701Err=0 ;
				}
				if(Err_ExtEncoder){
					//DispExtEncoderError() ;
					Err_ExtEncoder=false ;
				}
				
				if(NewH){//新主版回報信號
					if(chk_unconnector){ //生產和手動檢查
						chk_unconnector= false ;				
						for(int axis=0 ; axis < MachineStatus.axis_no; axis++){
							if(((axis !=AXIS_Y)&& MachineStatus.motor[axis]) || ((axis == AXIS_Y) && !MachineStatus.y_suspend)){
								if(!MachineStatus.bMotorNEAR[axis]){
									if(bb & 0x1){
										//DispMotorUnconnectError(axis) ;
									}		
								}
							}
							bb>>=1 ;
						}
						
						if( PORT_OIL0 && !MachineStatus.OilChk){//供油檢測解除 //改和馬達線掉了相同判斷
							//ChkOilStop();
							printf("Oil__");
						}
					}
				//ChkOverFlowStop();
				}
				break;
			case 3:
				if( MachineStatus.op_mode&(RUN_MODE+TEST_MODE+STEP_MODE) ){
					if( MachineStatus.dcur_th[0] || MachineStatus.dcur_th[1] )
						;//DispTouchPos();
					else if( MachineStatus.dcur_th[2] || MachineStatus.dcur_th[3] )
						//DispTouchPos();
					if( MachineStatus.safety_door ){
						if( MachineStatus.op_mode&(RUN_MODE) ){
							if( PORT_SAFETY_DOOR0 ){
								// debounce
								for(long l=0 ; l < DEBOUNCE_TIME ; l++) ;
							}
							if(PORT_SAFETY_DOOR0 ){
								//ChkDoorStop();
							printf("SafeDoor__");
							}
						}
					}
				}
				else if( MachineStatus.op_mode&MAN_MODE ){
					//檢查探針是否被觸發
					if(NewH){
						if((rDosMem(pc_base+INL) &0x40)){
							//ShowTouchTest(1) ;
							printf("touch1_");
						}
						if((rDosMem(pc_base+INL) &0x80)){
							//ShowTouchTest(2) ;
							printf("touch2_");
						}
						if((rDosMem(pc_base+INL) &0x8)){
							//ShowTouchTest(3) ;
							printf("touch3_");
						}
						if((rDosMem(pc_base+INL) &0x10)){
							//ShowTouchTest(4) ;
							printf("touch4_");
						}
					}
				}
				//chk_ScrnSav() ;
				break;
			}
			ChkCount = 0;
		}
	}
	*/
	/*
	chk_ErrMsg() ;
	update_flash() ;
	*/
	update_run_DDA() ;

}
void  always_run()
{	
	/*
	BgPrintf() ;
	if(NewH && MachineStatus.op_mode == MAN_MODE){
		if(CHK_ROTW(AXIS_A)&& MachineStatus.motor[AXIS_A] && !(rDosMem(pc_base+INM) &0x08)&& KeyLockCHG && keyswap ){//外接盒新增回原點修正
		//is_first_a=false ;
		DispManualSet_q() ;
		
	int tcurloc = BcdToBin(8,MachineStatus.axis_val[AXIS_A] ,MachineStatus.sign[AXIS_A]);
		EnableHomeInt(AXIS_A,BITmask[7-AXIS_A],ENABLE_STOP)  ; // 設定外接原點A亮燈時,使得A軸煞車
		if(!ChkDriverClear((uint8)AXIS_A)){
			do{
				update_run_DDA() ;
				FORCE_PROC_QUEUE
				if(set_ScrnSav()){
					continue ;
				}
//				CalNextManMov() ;
				if(DDAState ==0 && STEP_DDAState==0){
					if( Reset )SoftReset();
					if(tcurloc>=0){MANMOV_AXIS((AXIS_A), MINUS_SIGN, (KEY_PLUS_A),AXIS_A_REPEAT,0,0);}
					else {MANMOV_AXIS((AXIS_A), PLUS_SIGN, (KEY_PLUS_A),AXIS_A_REPEAT,0,0);}

				}
			}
			while(!ChkDriverClear((uint8)AXIS_A));
		}
		DDAState=0 ;
		DisableHomeInt(AXIS_A,0)  ; // 關掉外接原點A亮燈時,使得A軸煞車
		ResetDriverClear() ;


		{
//			DisableHomeInt(AXIS_A) ;
			ClrMsgWin_q();
			//尋找右邊的原點
			DispMsgWin_q(-1, -1, MSG_WIN, "自動回原點中....." ,
			 							  " Automatic Go Home .... ",
			 							  " Automatic Go Home .... ");
										  
			FORCE_PROC_QUEUE
			
			
			Adjust_AZero_NewH() ;
			set_zrt_power_on(AXIS_A) ;
		}
		sTimerSet(10) ;
		ClrKeyBuf() ;
		ClrMsgWin_q();
		
		MachineStatus.sign[AXIS_A]	   = PLUS_SIGN;
		MachineStatus.axis_val[AXIS_A] = 0;
		DispCurAxis_q(1);
		FORCE_PROC_QUEUE
		Clr2016s(AXIS_A) ;
		}
	}	
	*/
	/*
	//printf("%d\n",rDosMem(pc_base+0xc24));
		if(rDosMem(pc_base+0xc24)!=0x7){
			wr_rs232(4);wr_rs232(3);wr_rs232(1) ;	
			d();
		}
		else{
			wr_rs232(4);wr_rs232(3);wr_rs232(0) ;	
			d();
		}
	if(MachineStatus.op_mode ==MAN_MODE){
		wr_rs232(4); wr_rs232(1); wr_rs232(1);
		d();
		wr_rs232(4); wr_rs232(14); wr_rs232(1);
		d();
	}
	else{
		wr_rs232(4); wr_rs232(1); wr_rs232(0);
			d();
		wr_rs232(4); wr_rs232(14);wr_rs232(0);
			d();
	}
	*/
	if(MachineStatus.op_mode == MAN_MODE){//測試燈修改
		if(ReadAdc100() < 3){
			if(!EnableTest){
				//點亮test LED
				EnableTest=true ;
					wr_rs232(4); wr_rs232(4); wr_rs232(1);
			d();
			}
		}
		else{
			if(EnableTest){
				EnableTest=false ;
					wr_rs232(4); wr_rs232(4); wr_rs232(0);
			d();
			}
		}
	}
/*

	if( MachineStatus.op_mode&(RUN_MODE) ){
		if( MachineStatus.set8254 ){
			nSet8254(MachineStatus.cur8254);
			MachineStatus.set8254 = 0;
		}
	}
	else if( MachineStatus.op_mode&(TEST_MODE) ){
		if (flag_TouchSPDChange ){
			flag_TouchSPDChange  = false;
			update_sc(1) ;
		}
		else {
			update_sc(0) ;
		}
	}
	else if( MachineStatus.op_mode&STEP_MODE ){
		if(IsTimeUp(time_out_step)){
			if( GetNextKey() != KEY_HAND_RIGHT ){
				SetClock(STEP_CLOCK);
			}
		}
	}
	
//ReMake-------------------
	if(ReMake_flag){	
		ReMakeActTable();
		ReMake_flag=false;
		flag_complete_spring=true ;	
	}


	if(flag_RRealAxis&&(MachineStatus.op_mode & RUN_MODE)){
		uint16 cur_x=dReadAbsPos(AXIS_X) ;
		if(SaveRBuf.axis_x < cur_x ){
			SaveRBuf.axis_x= cur_x ;
			
			EPT_IDX(SaveRBuf.idx,	SaveRBuf.buf) ;
			SaveRBuf.buf[SaveRBuf.idx][0]=cur_x ;
			for(uint8 axis =1 ; axis < MachineStatus.axis_no ; axis++){
				
				EPT_IDX(SaveRBuf.idx,	SaveRBuf.buf) ;
				EPT_IDX(axis,	SaveRBuf.buf[0]) ;
				SaveRBuf.buf[SaveRBuf.idx][axis]=dReadAbsPos(axis) ;
			}
			SaveRBuf.idx++ ;
			if(SaveRBuf.idx==16000){SaveRBuf.idx=0;}
		} 
	}
	
	if(stBATCHn.airON){
		if(IsTimeUp(stBATCHn.timeout)){
			stBATCHn.airON=0 ;
			SetAir(stBATCHn.airno,0) ;
		}
	}

	//if( (!(MachineStatus.op_mode & PARA_MODE))&&(slide_axis)&& key_flg &&(PORT_STOPRUN ||((Get_Zrt_io(slide_axis)==0)&& !in_movToZeroAll))){
	if( (!(MachineStatus.op_mode & PARA_MODE))&&(slide_axis)&& key_flg &&(PORT_STOPRUN) && MachineStatus.motor[slide_axis] && MachineStatus.SlideLimit){//伺服滑座極限修正
		key_flg=false ;
		DispSlideError() ;
		ResetDriverClear();
	}
	else if( (!(MachineStatus.op_mode & PARA_MODE))&& (key_flg) &&(PORT_STOPRUN) && (!slide_axis)){//UV1新增阿德伺服切刀錯誤
		key_flg=false ;
		DispServoCutterError();
	}
	if(flag_VerifyProg){
		flag_VerifyProg=false ;
		VerifyProg(MachineStatus.speed_mode,0,0);
	}
	if(flagSPIN_ZRT){
		MovToZeroAll(1) ;
		virtual_move(false) ;
		flagSPIN_ZRT=false ;
	}
	if(disp_y){
		static SDWORD lmov ;
		SDWORD mov= (WORD)dReadAbsPos(AXIS_Y) ;
		static long cnt=0 ;
		cnt++ ;
		if((mov != lmov)||(cnt == 0x1234)){
			if(cnt == 0x1234){
				st_extencoder.updategap=true ;
			}
			cnt=0 ;
			lmov = mov ;
			INI_DISP_BUF();
			SDWORD encoder_mov = mov ;
			mov= ExtGrid2_Grid(mov); //外界encoder的格數轉換成馬達格數
			pDispBuf_value +=	BinToStrBuf(6, mov, pDispBuf);
			FILL_DISP_BUF(' ') ;
			pDispBuf_value +=	BinToStrBuf(6, encoder_mov, pDispBuf);
			FILL_DISP_BUF(0);
			DispStrLine_q(0, 0,	WIN_TEXT_FCOLOR, WIN_TEXT_BCOLOR, DispBuf);
		}
	}

	
	
	
#if CHK_MAN_MOV
	if(chk_man_mov.boenable){
		ChkManMov() ;
	}
#endif	
	//檢查鍵盤輸入手輪輸入,並依照不同工作模式更新資料
	ngetkey() ;
	chk_off_power(1) ;
	if(ChkExtRstSW_IO()){
		flag_run= false ;
		SoftReset(); 
	}
#if SW_SIM_MOTOR
	Updatesim_motorabsloc() ;
#endif


	
	if( Reset||MachineStatus.safe_err ){
		flag_run= false ;
		if(Reset)SoftReset();
	}
	
	*/
	if( KeyBufRIdx != KeyBufWIdx ){
		if(NewH &&DDAState ==0){
			// have a key 重新設定time out時間
			if(!set_ScrnSav()){
				KeyProcMap();
			}
		}
	}
	/*

	
	for(int i=0 ; i < 4 ; i++){
		if(flag_ClrTouchPos[i]){
			flag_ClrTouchPos[i]= false ;
			int loc=1 ;
			for(int j=0 ; j < i ; j++){
				loc*=2 ;
			}
			ClrTouchPos(1,loc) ;
		}
	}
	if(flag_DispMissNo){
		flag_DispMissNo=false ;
		DispMissNo_q() ;
	}
	if( MachineStatus.th_stop ){
		TouchErrStop();
	}
	if(st_DispStatusBar.flag){
		st_DispStatusBar.flag=false ;
		INI_DISP_BUF();
		if(st_DispStatusBar.axis	< AXIS_A){
			FILL_DISP_BUF2(('X'+st_DispStatusBar.axis), ':');
		}
		else{
			FILL_DISP_BUF2(('A'+st_DispStatusBar.axis-AXIS_A), ':');
		}
		if(	(long)st_DispStatusBar.dst_pos > 0 ){
			FILL_DISP_BUF('+');
			pDispBuf_value +=	BinToStrBuf(6, st_DispStatusBar.dst_pos, pDispBuf);
		}
		else{
			FILL_DISP_BUF('-');
			pDispBuf_value +=	BinToStrBuf(6, -(long)st_DispStatusBar.dst_pos, pDispBuf);
		}
		Fill_pDispBuf(" 前工作尚未完成 !" ,
        "Prior	work have not finished !");
		FILL_DISP_BUF(0);
		DispStatusBar_q(DispBuf);
	}

*/
}
