//2012_0502_���w���U�b---------------------------------------------
EXTERN  uint8 T_Stop_idx;			//�@?�ձ��w
EXTERN  uint8 T_Stop_idxLast;		//�̫�@�ձ��w
EXTERN  uint8 T_Stop_MdyVAL_idx;	//�ثe?�ձ��w
EXTERN  bool T_Stop_Flag[20][MAX_AXIS_8];		//�����n������F----20�����w�̦h�ռ�	
EXTERN  bool T_Stop_HaveTouch_Flag;				//���w�O�_������

EXTERN  SDWORD T_Stop_HaveVAL[20][MAX_AXIS_8];	//�Ω�T_Stop_MdyVAL_Cmd�A�������F�쥻�n����m
EXTERN  SDWORD T_Stop_MdyVAL[MAX_AXIS_8];		//�Ω�T_Stop_MdyVAL_Cmd�A�ɨ����(�ץ���)
EXTERN  SDWORD T_Stop_MdyVAL_Y;					//�Ω�T_Stop_MdyVAL_Cmd�AY�ɨ����(�gA�b�B���oY�ɨ����)


EXTERN  bool T_Stop_Amov_flag;		//mode==2, �bG6�}�Ҹ��v

EXTERN uint32 Axis_Zrt2016VAL[MAX_AXIS_8];		//�sZrt��2016�ƭ�
EXTERN uint32 T_Stop_AxisNowVAL[MAX_AXIS_8];	//axis Touch�쪺��m
EXTERN uint32 T_Stop_Axis;						//�ثe���w���b���A
EXTERN bool T_Stop_MotorStop_flg;				//�ثe���w�w���b_�O�_����----�}�l�p����v���



EXTERN uint32 T_Stop_Dw[MAX_AXIS_8];			//�U�b_�@���u®���`���
EXTERN uint32 T_Stop_DwTouch[20][MAX_AXIS_8];	//�U�b_"���w��_�l"�����(�W�@�樫�쪺���)
EXTERN uint32 T_Stop_DwAll_32[MAX_AXIS_8];		//�U�b_�ثe�ֿn_�����u®���`���_32bit,�A��ARM
EXTERN uint16 T_Stop_DwAll_16[MAX_AXIS_8];		//�U�b_�ثe�ֿn_�����u®���`���_16bit,�A��8051


//���I��m+(�ثe�ֿn)+�������	
#define T_STOP_AXIS2016_32(axis, val)		(Axis_Zrt2016VAL[axis] + (T_Stop_DwAll_32[axis]) + val)
#define T_STOP_AXIS2016_16(axis, val)		(uint16)((uint16)Axis_Zrt2016VAL[axis] + (T_Stop_DwAll_16[axis]) + (uint16)val)



