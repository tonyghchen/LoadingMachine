//2012_0502_���w����A�����X�b�n����R�O(���w���U�b)--------------------------------------
void T_Stop_Make_Cmd(ProgType_t HUGE *p_buf,ActTbl_t HUGE *a_tbl, WORD &idx)
{	
	//�p��쥻�U�b�������
	for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
		if((p_buf->dval[axis]!=PROG_VAL_NULL)	&&	MachineStatus.motor[axis]){
			T_Stop_Flag[T_Stop_idx][axis]=true;
			ADD_WaitMotorNear(a_tbl, idx, axis,1);
		}
		else{
			T_Stop_Flag[T_Stop_idx][axis]=false;
		}
	}
	//�[�J����ɡA�U�b�����m�R�O
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
	uint32 nowVAL=0, RawVAL=0;		//�ثe�����m ,  �쥻�����m

		if(T_Stop_HaveTouch_Flag){
							
			for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
				if(T_Stop_Flag[T_Stop_MdyVAL_idx][axis]){
					
					nowVAL	=	T_Stop_AxisNowVAL[axis];		//����ɪ���m
					if(axis_type ==	INTEL8051_AXIS){			//���w�浲����m
						RawVAL	=	T_STOP_AXIS2016_16(axis,T_Stop_HaveVAL[T_Stop_MdyVAL_idx][axis]);
						//if(axis==AXIS_A)Sprintf("16�ֿn:AXIS_B:%d",T_Stop_DwAll_16[axis]);
					}
					else{
						RawVAL	=	T_STOP_AXIS2016_32(axis,T_Stop_HaveVAL[T_Stop_MdyVAL_idx][axis]);
						//if(axis==AXIS_A)Sprintf("32�ֿn:AXIS_B:%d",T_Stop_DwAll_32[axis]);
					}
					
					//���v���
					if(RawVAL<nowVAL	&&	axis_type==INTEL8051_AXIS)	T_Stop_MdyVAL[axis] =	(0x10000L-nowVAL)+RawVAL;			//16Bits �p"������m"Overflow,�Ӱ����m�٥�Overflow���⦡
					else if(RawVAL<nowVAL	&&	axis_type==ARM_AXIS)		T_Stop_MdyVAL[axis]	= (0xffffffff-nowVAL+1)+RawVAL;		//32Bits ...					
					else T_Stop_MdyVAL[axis]	=	RawVAL-nowVAL;
					
					
					/*if(axis==AXIS_B){
						if(axis==AXIS_B)Sprintf("16�ֿn:AXIS_B:%d",T_Stop_DwAll_16[axis]);
						Sprintf("�p��end[%d] now=%d, Raw=%d, Zrt=%d",axis,nowVAL,RawVAL,Axis_Zrt2016VAL[axis] );					
						Sprintf("�@��%d��. �������:%d",T_Stop_Dw[axis],T_Stop_HaveVAL[T_Stop_MdyVAL_idx][axis]);
						Sprintf("���v���[%d]___%d 		",axis,T_Stop_MdyVAL[axis] );
					}*/
					
					//�p�G��AXIS_A�B����u�A�hAXIS_Y�ݭn�ɥ�					
					if(CHK_ROTATE_A(axis)){
						BYTE dir_Y= OFFSET_Y_dir(PLUS_SIGN) ;
						T_Stop_MdyVAL_Y=T_Stop_MdyVAL[AXIS_A];
						if(dir_Y == MINUS_SIGN){
							T_Stop_MdyVAL_Y= -T_Stop_MdyVAL_Y ;
						}															
					}
					else{T_Stop_MdyVAL_Y=0;}	//��l						
				}
				else{T_Stop_MdyVAL[axis]=0;}	//��l
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
		//�ثe�ר�ĴX�ձ��w
		T_Stop_MdyVAL_idx++;
		if(T_Stop_MdyVAL_idx>T_Stop_idxLast){T_Stop_MdyVAL_idx=0;}
		//�֥[�C���u®���
		for(int axis=AXIS_Z; axis<MachineStatus.axis_no; axis++){
			if(axis_type ==	INTEL8051_AXIS)T_Stop_DwAll_16[axis]+=T_Stop_Dw[axis];	// + �@���u®���`��� 
			else{T_Stop_DwAll_32[axis]+=T_Stop_Dw[axis];}
		}
}


void T_Stop_Offset_Cmd(ActTbl_t HUGE *a_tbl, DWORD x_ref)
{	
	DWORD ref=0, ref_Max=x_ref;
	uint8 offset_idx=1;		//�ܤ֦�X�b�ݭn�ɨ����
	//�@���X�b�ɨ����,�íp��ref
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
	//�]�w�R�O
	for(uint8 xaxis=AXIS_X; xaxis<MachineStatus.axis_no; xaxis++){		
		if(xaxis==AXIS_Y)xaxis=AXIS_Z;	//Y���ɨ����
		if(	T_Stop_MdyVAL[xaxis] ){
			offset_idx--;
		
			bool run=true;
			//�p�G��AXIS_A�B����u�A�hAXIS_Y�ݭn�ɥ�					
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
		if(xaxis!=AXIS_X)T_Stop_MdyVAL[xaxis]=0;				//�ɧ����l(X�b���M�s)
	}
}


//------------------------------------------------------------------			

