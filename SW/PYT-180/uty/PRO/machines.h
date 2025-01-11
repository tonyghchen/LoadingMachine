	uint8	axis_no;
	uint8	p3701[MAX_AXIS];
	uint8	motor[MAX_AXIS];		//1:代表在開啟馬達狀態/0:代表在關閉馬達狀態

	uint8	is_home[MAX_AXIS];		//當為1時,代表該軸目前正在原點
	uint8	go_home[MAX_AXIS];		//當某軸欲回原點時,設定其為1;當該原點中斷發生時,被清除為0
	uint8	running[MAX_AXIS];
	uint16	manval[MAX_AXIS];		//手動

	char	axis_str[MAX_AXIS][10] ;
	uint8	sign[MAX_AXIS]	, dst_pos_sign[MAX_AXIS]	 , lsign[MAX_AXIS] ;
	uint32	axis_val[MAX_AXIS], dst_pos[MAX_AXIS], laxis_val[MAX_AXIS];
	uint32	motor_grads[MAX_AXIS];
	uint8	prev_mov[MAX_AXIS], prev_sign[MAX_AXIS];
	uint16	Rate[MAX_AXIS] ;
	uint16	G1Rate[MAX_AXIS] ;
	uint8	home_seq[MAX_AXIS],home_seq_sign[MAX_AXIS] ;
	uint8	repair_spd, repair_dst, pos_zone, gain_val, man_gain;
	uint8	g2comb;

	uint16	op_mode;

	uint8	scrn_off;
	uint8	language, gray_color;
	uint16	file;

	uint8	speed_mode; //紀錄目前的模式為AUTO/FAST
	uint16	speed[2]; //紀錄FAST/AUTO設定的速度

	uint8	run_state;
	uint8	pass_x_home, home_err;
	uint8	stop_machine;
	uint8    stop_machine_delay1;
	uint8	th_stop;
	uint8	miss_flag;
	uint8	th_mask;

	uint16	set_miss, cur_miss;  //設定失誤量/目前失誤量
	uint32	set_quan, cur_quan;	 //設定生產量/目前生產量
	uint32	rec_th[4], dcur_th[4] , cur_thy[4];
	uint8	chk_th[4], pass_th[4],chk_th_stop_axis[4];

	uint8	in_loop;
	uint16	loop_stack[MAX_LOOP];
	uint16	loop_times[MAX_LOOP];
	uint16	loop_cnt[MAX_LOOP];
	uint16	loop_ptr;

	uint16	last_line;
	uint8	prog_mody;

	uint8	safe_sw, safe_err, bysafe_plugin;
	uint8	hand_plugin, hand_sel;
	uint16	hand_scale, handval[MAX_AXIS]; //手輪

	uint8	y_scale, y_suspend;
	uint8	wire_on, pwr_on;
	uint16	cnt8254, cur8254;
	uint8	adc_level, set8254;
	uint8	safety_door;
	uint8	th_test;
	uint8	ret[MAX_AXIS] ;
	uint8	xgrid_deg  ;
	uint16	Y0,Y1 ;
	uint16    Jmpnn ;
	uint8	FAST,TIMER;
	uint16	dec_dist ,LINE;
	uint8	BUZZER,BATCH ;
	uint16	Type ,Type1;
	uint16	Delay ;
	uint16	ScrnSav ;
	bool	flg_ScrnSav ;
	uint16	wZeroSpd[MAX_AXIS] ;
	uint8	ZrtMode[MAX_AXIS] ;
	uint8	Unit[MAX_AXIS] ;
	uint32 Max[MAX_AXIS] ;
	uint32 Min[MAX_AXIS] ;
	uint8 	Max_sign[MAX_AXIS] ;
	uint8 	Min_sign[MAX_AXIS] ;
	uint16 AxisMap[MAX_AXIS] ;
	uint8    AHome_sign;
	uint16   MANUFACTORY ;
	uint32    AHome ;
	char SN[9] ;
	uint8     flag_virtual ;
	uint16    AxisDelay[MAX_AXIS] ;
	uint8	ZRTSET_sign[MAX_AXIS];
	uint32    ZRTSET[MAX_AXIS] ;
	uint8   Comment[16] ;
	uint8	NEAR,YGAP ,AGAP , TOUCH_Y_NEAR;
	unsigned int TargetY ;
	uint32    lmov2TargetY ;
	uint8     X_SPD ;
	uint8 	HomeInt,TouchInt ;
	uint8     ROTQ_MDY,SPIN_MDY ;
	uint8     UsbDisk ;
	uint8     ONE ;
	bool KStepMode ;
	bool KStepOn ;
	uint32 NSN ;
	uint32 MONTH[15];
	uint32 PASS[15];
	uint16 RUNDAYS ;
//	uint8 PRODDELAY ;
//	uint8 XMINUS;
//	uint8 KEYLOCK;
//	uint8 OilChk;
	uint16 PRODPASS ;
	uint16  Spg_LEN ;
	uint16  SORTOR_S;
	uint16  MDY_SPD ;
	uint16 Toleranc ;
	uint16 SORTOR_H ;
	uint16 STOP_CON ;
	uint16 CUT_POS  ;
	uint16 bCUT_POS ;
	uint16 OilON ;
	uint16 OilOFF ;
	uint16 X_2016_Y0 ;
	uint16 X_2016_Y1 ;
	uint32 Para1Val[20] ;
	uint8 X_Encoder ,Y_Encoder ;
	uint8    ToPos[MAX_AXIS] ;
	uint8 FEEDER ;
	uint8 SimFast ;
	uint16 	SPIN_ZRT ;
	BYTE	axis_nox[2] ;
	BYTE 	ManSel ;
	uint16 UnitY0[MAX_AXIS] ;
	uint8 	ABDir[MAX_AXIS] ;
	uint16	wZeroSpd2[MAX_AXIS] ;
	uint8	wZeroSpd2_sign[MAX_AXIS] ;
	bool XXScale ;
	uint8 XXScaleSel ;
	uint8 ImmNo[MAX_AXIS] ;
	uint8 bImmNo[MAX_AXIS] ;
	uint16 ENCR0[MAX_AXIS] ;
	uint16 ENCR1[MAX_AXIS] ;
	uint16 bENCR0[MAX_AXIS] ;
	uint16 bENCR1[MAX_AXIS] ;
	uint16 ZRTPreM[MAX_AXIS] ;
	uint8 BIOSVendor ;
