//2012_0502_當探針探到，有哪幾軸要停止的命令(探針停各軸)--------------------------------------
void T_Stop_Make_Cmd(ProgType_t HUGE *p_buf,ActTbl_t HUGE *a_tbl, WORD &idx)
{	
	//計算原本各軸欲走格數
	for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
		if((p_buf->dval[axis]!=PROG_VAL_NULL)	&&	MachineStatus.motor[axis]){
			T_Stop_Flag[T_Stop_idx][axis]=true;
			ADD_WaitMotorNear(a_tbl, idx, axis,1);
		}
		else{
			T_Stop_Flag[T_Stop_idx][axis]=false;
		}
	}
	//加入探到時，各軸停止位置命令
	for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
		if(T_Stop_Flag[T_Stop_idx][axis]){
			a_tbl[idx].cmd	 = T_STOP_MDYVAL;
			a_tbl[idx].next	 = 0;			
			idx++ ;
			T_Stop_idx++;
			break;
		}
	}
	T_Stop_idxLast=T_Stop_idx-1;
}

void T_Stop_MdyVAL_Cmd()
{
	uint32 nowVAL=0, RawVAL=0;		//目前停止的位置 ,  原本停止的位置

		if(T_Stop_HaveTouch_Flag){
							
			for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
				if(T_Stop_Flag[T_Stop_MdyVAL_idx][axis]){
					
					nowVAL	=	T_Stop_AxisNowVAL[axis];		//停止時的位置
					if(axis_type ==	INTEL8051_AXIS){			//探針行結束位置
						RawVAL	=	T_STOP_AXIS2016_16(axis,T_Stop_HaveVAL[T_Stop_MdyVAL_idx][axis]);
						//if(axis==AXIS_A)Sprintf("16累積:AXIS_B:%d",T_Stop_DwAll_16[axis]);
					}
					else{
						RawVAL	=	T_STOP_AXIS2016_32(axis,T_Stop_HaveVAL[T_Stop_MdyVAL_idx][axis]);
						//if(axis==AXIS_A)Sprintf("32累積:AXIS_B:%d",T_Stop_DwAll_32[axis]);
					}
					
					//補償格數
					if(RawVAL<nowVAL	&&	axis_type==INTEL8051_AXIS)	T_Stop_MdyVAL[axis] =	(0x10000L-nowVAL)+RawVAL;			//16Bits 如"結束位置"Overflow,而停止位置還未Overflow的算式
					else if(RawVAL<nowVAL	&&	axis_type==ARM_AXIS)		T_Stop_MdyVAL[axis]	= (0xffffffff-nowVAL+1)+RawVAL;		//32Bits ...					
					else T_Stop_MdyVAL[axis]	=	RawVAL-nowVAL;
					
					
					/*if(axis==AXIS_B){
						if(axis==AXIS_B)Sprintf("16累積:AXIS_B:%d",T_Stop_DwAll_16[axis]);
						Sprintf("計算end[%d] now=%d, Raw=%d, Zrt=%d",axis,nowVAL,RawVAL,Axis_Zrt2016VAL[axis] );					
						Sprintf("一條%d格. 結束格數:%d",T_Stop_Dw[axis],T_Stop_HaveVAL[T_Stop_MdyVAL_idx][axis]);
						Sprintf("補償格數[%d]___%d 		",axis,T_Stop_MdyVAL[axis] );
					}*/
					
					//如果有AXIS_A且為轉線，則AXIS_Y需要補正					
					if(CHK_ROTATE_A(axis)){
						BYTE dir_Y= OFFSET_Y_dir(PLUS_SIGN) ;
						T_Stop_MdyVAL_Y=T_Stop_MdyVAL[AXIS_A];
						if(dir_Y == MINUS_SIGN){
							T_Stop_MdyVAL_Y= -T_Stop_MdyVAL_Y ;
						}															
					}
					else{T_Stop_MdyVAL_Y=0;}	//初始						
				}
				else{T_Stop_MdyVAL[axis]=0;}	//初始
			}
			T_Stop_HaveTouch_Flag=false;
			T_Stop_MotorStop_flg=false;
		}
		else {
			for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
				if(MachineStatus.motor[axis]){
					T_Stop_MdyVAL[axis]=0;
					T_Stop_MdyVAL_Y=0;
				}
			}
		}	
		//目前修到第幾組探針
		T_Stop_MdyVAL_idx++;
		if(T_Stop_MdyVAL_idx>T_Stop_idxLast){T_Stop_MdyVAL_idx=0;}
		//累加每條彈簧格數
		for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
			if(axis_type ==	INTEL8051_AXIS)T_Stop_DwAll_16[axis]+=T_Stop_Dw[axis];	// + 一條彈簧的總格數 
			else{T_Stop_DwAll_32[axis]+=T_Stop_Dw[axis];}
		}
}


void T_Stop_Offset_Cmd(ActTbl_t HUGE *a_tbl, DWORD x_ref)
{	
	DWORD ref=0, ref_Max=x_ref;
	uint8 offset_idx=1;		//至少有X軸需要補走格數
	//共有幾軸補走格數,並計算ref
	for(uint8 xaxis=AXIS_Z; xaxis<MachineStatus.axis_no; xaxis++){
		if(T_Stop_MdyVAL[xaxis]){
			offset_idx++;
			
			cal_zrtref(xaxis,ref) ;
			if(T_Stop_MdyVAL[xaxis]<0){
				ref *=-T_Stop_MdyVAL[xaxis] ;
			}
			else{ref *=T_Stop_MdyVAL[xaxis] ;}
			ref /= BcdToBin(MOTOR_GRADS_BCD,MachineStatus.motor_grads[xaxis]) ;
			if(ref>ref_Max)ref_Max=ref;			
		}
	}
	//設定命令
	for(uint8 xaxis=AXIS_X; xaxis<MachineStatus.axis_no; xaxis++){		
		if(xaxis==AXIS_Y)xaxis=AXIS_Z;	//Y不補走格數
		if(	T_Stop_MdyVAL[xaxis] ){
			offset_idx--;
		
			bool run=true;
			//如果有AXIS_A且為轉線，則AXIS_Y需要補正					
			if(CHK_ROTATE_A(xaxis)){									
				bool Y_StartWire	=	(a_tbl->mov >= 30000L)? true : false ;																											
				Set3701(AXIS_Y, PLUS_SIGN, ref_Max, T_Stop_MdyVAL_Y,T_Stop_MdyVAL_Y,false,T_Stop_MdyVAL_Y,0);
				MachineStatus.dst_pos[AXIS_Y]   =0;
				MachineStatus.running[AXIS_Y]	= 1;
				if(	MachineStatus.op_mode==RUN_MODE	) ChkStartWire(Y_StartWire);
			}
			if(offset_idx){run=false;}
			Set3701(xaxis, PLUS_SIGN, ref_Max, T_Stop_MdyVAL[xaxis],T_Stop_MdyVAL[xaxis],run,0,0);
			MachineStatus.dst_pos[xaxis] =	(xaxis==AXIS_X)?(a_tbl->u.dst_pos):0;
			MachineStatus.running[xaxis]	= 1;
														
		}					
		if(xaxis!=AXIS_X)T_Stop_MdyVAL[xaxis]=0;				//補完後初始(X軸不清零)
	}
}


//------------------------------------------------------------------			

