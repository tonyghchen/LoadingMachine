
/*

void INI_Sprintf()
{
    		y_Sprintf=25 ;
}
void Init3701 (void)
{
	for(uint8 axis=0; axis <	MachineStatus.axis_no; axis++ ){
		//Set3701(axis, 0, 0,	0,0,true,0);	新620
	}
}

void Init3702 (void)
{
		SetAllGain(MachineStatus.man_gain, 1);
}
*/
void SetAllGain	(uint8 val, uint8	m)
{
// 	uint8   axis;
// 	uint32  i;

// 	m=m	;
// 	if(axis_type ==	INTEL8051_AXIS){
// 		for( axis=0; axis <	MachineStatus.axis_no; axis++ ){
// 			new_base(pc_base+Base3701[axis]);
// 			wDosMem_base(DATA51_L , MachineStatus.pos_zone);
// 			wDosMem_base(DATA51_M , val);
// 			wDosMem_base(W_CMD_51 , CMD51_NEAR_GAIN);

// 			for( i=0; i	< LOOP_TIMES; i++ ){
// 				if(	rDosMem_base(R_CMD_51) ==	ST51_NEAR_OK )	break;
// 			}
// 			if((i>=LOOP_TIMES)){
// 				RW3701Err |= (1 << axis);
// //				FillErr() ;
// 			}
// 			wDosMem_base(W_CMD_51 , CMD51_NONE);
// 		}
// 	}
// 	else if(axis_type == ARM_AXIS){
// 	}

}
/*
void Server_onoff(uint8 onoff)
{
// onoff: 1 ---ON
//        0 ---OFF
	uint8   axis;
	uint32  i;
	if(axis_type ==	INTEL8051_AXIS){
		for( axis=0; axis <	MachineStatus.axis_no; axis++ ){
			new_base(pc_base+Base3701[axis]);
			wDosMem_base(W_CMD_51 , onoff+0xf);

			for( i=0; i	< LOOP_TIMES; i++ ){
				if(	rDosMem_base(R_CMD_51) ==	ST51_NEAR_OK )	break;
			}
			wDosMem_base(W_CMD_51 , CMD51_NONE);
		}
	}
	else if(axis_type == ARM_AXIS){
		SendToArmCmd(0x30+onoff*0x10) ;
	}
}
void Server_onoff(uint8 axis , uint8 onoff)
{
// onoff: 1 ---ON
//        0 ---OFF
	uint8  *base;
	uint32  i;
	if(axis_type ==	INTEL8051_AXIS){
		new_base(pc_base+Base3701[axis]);
		wDosMem_base(W_CMD_51 , onoff+0xf);

		for( i=0; i	< LOOP_TIMES; i++ ){
			if(	rDosMem_base(R_CMD_51) ==	ST51_NEAR_OK )	break;
		}
		wDosMem_base(W_CMD_51 , CMD51_NONE);
	}
	else if(axis_type == ARM_AXIS){
		SendToArmCmd(0x30+(axis+1)+onoff*0x10) ;
	}
}



void InitMotorIo (void)
{
	if(axis_type ==	INTEL8051_AXIS){

		for(uint8 m=0; m	< (MAX_AXIS+2)/3; m++ ){
			wDosMem_pc_base(Base3701[m*3+0]+PARA_51 , Para51[m] = 0xff); // disable home interrupt
			//*(tt=pc_base+Base3701[m*3+1]+PARA_51)	= 0xff;	  //沒作用
			//*(tt=pc_base+Base3701[m*3+2]+PARA_51)	= 0xff;	  //沒作用
		}
		wDosMem_pc_base(BaseMotorADC[0] , 0xff);
		wDosMem_pc_base(MOTOR1_8254 ,  1);
		wDosMem_pc_base(MOTOR4_8254 ,  1);
	}
	else if(axis_type == ARM_AXIS){
		wDosMem(ARM_IEP ,Para51[0]= 0xff) ;   // disable home interrupt
	}
	Set8254(MachineStatus.cnt8254);
}

void DispMsgWin_q(SCRN_XY x, SCRN_XY y, BYTE	type, Cptr msg_chinese, Cptr msg_english,Cptr msg_Italian)
{
		x;y;
		INI_DISP_BUF();
		Fill_pDispBuf( msg_chinese, msg_english,msg_Italian);
		FILL_DISP_BUF(0);
		DispMsgWin_q(-1, -1, type, DispBuf);
}
void DispMsgWin_q(int16 x, int16 y, uint8	type, Cptr msg_chinese, Cptr msg_english)
{
		x;y;
		INI_DISP_BUF();
		Fill_pDispBuf( msg_chinese, msg_english);
		FILL_DISP_BUF(0);
		if(CurGrSetMode!= 1280){
			DispMsgWin_q(-1, -1, type, DispBuf);
		}
		else{
			DispMsgWin_q(x, y, type, DispBuf); 
		}
}
void DispMsgWin_q(int16 x, int16 y, uint8	type, Cptr msg)
{
	char tDispBuf[200] ;
	if(msg == DispBuf){
		strcpy_S(tDispBuf,msg) ;
	}
	FORCE_PROC_QUEUE
	if(msg == DispBuf){
		strcpy_S(msg,tDispBuf) ;
	}
	uint16 len;

	len	= StrLen(msg);
	if((type == ERR_WIN)|| (type &0x80)){
		//儲存錯誤信息
		type&=0x7f ;
		memcpy(ErrMsg,msg,len) ;
		*(ErrMsg+len)=0 ;
	}

	uint8 *dptr=  (uint8 *)malloc(2*sizeof(uint16)+1*sizeof(uint8)+len+1+LEN_CHKSUM) ;
	uint8 *tptr= dptr ;
	SAVE_VAL(uint16 , x) ;
	SAVE_VAL(uint16 ,	y) ;
	SAVE_VAL(uint8 , type) ;
	SAVE_STRING(msg,len) ;
	SAVE_CHKSUM
	FILL_PROC_QUEUE(DISP_MSG_WIN_proc,tptr)	;
}

*/
//設定Speed Count值,其值愈小速度愈快(但0為停止不動)
//       =0xd-------全速執行
//       =2*0xd-----執行速度減半
void Set8254 (uint16 cnt)
{
	if(	cnt	!= Old54Val	){
		if(axis_type ==	INTEL8051_AXIS){
			if(	!cnt ){
				wDosMem_pc_base(INTEL8051_SCL , 0);	  // Speed counter(low uint8) SCL----address base+0x90
				wDosMem_pc_base(INTEL8051_SCH , 0);	  //Speed counter(high uint8)SCH----address base+0x98
			}
			else{
				wDosMem_pc_base(INTEL8051_SCL , (uint8)cnt);
				wDosMem_pc_base(INTEL8051_SCH , (uint8)(cnt/256));
			}
		}
		else{
			if(	!cnt ){
				wDosMem_pc_base(ARM_SCL , 0);	  // Speed counter(low uint8) SCL----address	base+0x90
				wDosMem_pc_base(ARM_SCH , 0);	  //Speed counter(high uint8)SCH----address base+0x98
			}
			else{
				wDosMem_pc_base(ARM_SCL , (uint8)cnt);
				wDosMem_pc_base(ARM_SCH , (uint8)(cnt/256));
			}
		}

		Old54Val = cnt;
	}
}
void ClrMsgWin (void)
{

	//FILL_PROC_QUEUE(CLR_MSG_WIN_proc,NULL) ;

}
void ClrMsgWin_q (void)
{

	//FILL_PROC_QUEUE(CLR_MSG_WIN_proc,NULL) ;

}
