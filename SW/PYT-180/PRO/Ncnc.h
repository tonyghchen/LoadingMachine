#include	"c_ncnc.h"

#define farfree    free
#define BMOTORGRID(axis)	(MachineStatus.motor_grads[axis])
enum
{
	CLR_MISS_QUAN_CURSOR, SET_MISS_QUAN_CURSOR, SPEED_FILE_CURSOR, MAN_CURSOR,
	PROG_CURSOR, MAN_AIR_CURSOR, HELP_CURSOR,
	PASSWORD_CURSOR,
  MOTOR_GRID_CURSOR,PARA1_LINE03_CURSOR,PARA1_LINE04_CURSOR, HOME_SEQ_CURSOR ,ZRTMODE_CURSOR , ZRTSET_CURSOR ,ZRTCORR_CURSOR,MAX_CURSOR,MIN_CURSOR,MotorNEAR_CURSOR,
	
	PARA1_LINE10_CURSOR,PARA1_LINE11_CURSOR,PARA1_LINE12_CURSOR,PARA1_LINE13_CURSOR,
  
  PARA2_LINE01_CURSOR,PARA2_LINE02_CURSOR,PARA2_LINE03_CURSOR,PARA2_LINE04_CURSOR,PARA2_LINE05_CURSOR,PARA2_LINE06_CURSOR,PARA2_LINE07_CURSOR,PARA2_LINE08_CURSOR,PARA2_LINE09_CURSOR,PARA2_LINE10_CURSOR,PARA2_LINE11_CURSOR,PARA2_LINE12_CURSOR,PARA2_LINE13_CURSOR,PARA2_LINE14_CURSOR,
  
  PARA3_LINE01_CURSOR,
  
  PARA4_LINE01_CURSOR,PARA4_LINE02_CURSOR,PARA4_LINE03_CURSOR,PARA4_LINE04_CURSOR,PARA4_LINE05_CURSOR,PARA4_LINE06_CURSOR,PARA4_LINE07_CURSOR,
  
  YGRID_MM_CURSOR ,
	DISK_IO_CURSOR , AIR_CURSOR ,JMPNN_CURSOR ,NOPASSWORD_CURSOR,TDecDis_CURSOR,
	UNIT_CURSOR ,RATE_CURSOR,G1RATE_IDMS_CURSOR,ZEROSPD_CURSOR,AXISDELAY_CURSOR,TOPOS_CURSOR,ZRTPreM_CURSOR ,nY0_CURSOR ,CusRate_CURSOR,
	BiosRst_CURSOR,NEAR_CURSOR ,SPIN_ZRT_CURSOR ,WILE_MODE_CURSOR,PRODPASS_CURSOR,OilChk_CURSOR,
		
	INDEX_FILE_CURSOR ,INDEX_CONTENT_CURSOR ,
	
	SPDPlus_CURSOR, SPDMinus_CURSOR, SPDFun_CURSOR,LOWSPD_CURSOR,PARAEXT11_CURSOR,SPDLink_CURSOR,PARAEXT12_CURSOR,PARAEXT13_CURSOR,		//�[��t�Ѽ�
	SPDMotorID_CURSOR,
	SPDTbl0_CURSOR,SPDTbl1_CURSOR,SPDTbl2_CURSOR,SPDTbl3_CURSOR,SPDTbl4_CURSOR,SPDTbl5_CURSOR,SPDTbl6_CURSOR,SPDTbl7_CURSOR,SPDTbl8_CURSOR,SPDTbl9_CURSOR,
	MARKER_CURSOR,
};

enum
{
	LIMIT_TYPE, BYTE_TYPE, WORD_TYPE, DWORD_TYPE, GCODE_TYPE, N_TYPE, ZRT_TYPE,ASCII_TYPE ,
	AIR_TYPE, MAN_AIR_TYPE, SEQ_TYPE, SPEED_TYPE,SPEED_G123_TYPE, SPEED_G4_TYPE, Y_TYPE,ZABC_TYPE , PASSWORD_TYPE,AXIS_X_TYPE,DWORD_S1_TYPE,BYTE_TYPE_DOT1,WORD_TYPE_DOT1,WORD_TYPE_DOT2,DWORD_TYPE_DOT1,DWORD_TYPE_DOT2,
	MARKER_TYPE
};



enum
{
	MOVE_X, MOVE_Y, MOVE_Z, MOVE_A, MOVE_B, MOVE_C,MOVE_D,MOVE_E,
	UPDATE_LINE, SET_AIR, CLR_AIR, SET_TOUCH, CLR_TOUCH, CLR_LOOP_AIR,
	ZRT_Z,ZRT_A,ZRT_B ,ZRT_C,ZRT_D ,ZRT_E ,

	MISS_X, MISS_Y, MISS_Z, MISS_A, MISS_B, MISS_C,MISS_D,MISS_E,
	MISS_UPDATE_LINE, MISS_SET_AIR,

	LOOP_X, LOOP_Y, LOOP_Z, LOOP_A, LOOP_B, LOOP_C,LOOP_D ,LOOP_E ,
	LOOP_UPDATE_LINE, LOOP_START, LOOP_CHECK, LOOP_END,

	MID_CHK, END_ACT, NULL_ACT_CMD, CNT8254_CMD,OFFSET_Y ,OFFSET_Y_M,INCY , 
	SET_DELAY ,WAIT_DELAY , WAIT_MOTOR_NEAR_IN_LOOP,WAIT_MOTOR_NEAR_X,WAIT_MOTOR_NEAR_Y,WAIT_MOTOR_NEAR,WAIT_MOTOR_HOOK ,WAIT_ZRT_X ,
	LOC_PLUS_MINUS, LOC_MINUS_PLUS , MODIFY_Y,SAVE_Y , SAVE_Y_MOV,WAIT_MOTOR_NEAR_SERVO,CHK_SPIN_ZRT,WAIT_SPIN_ZRT,
	SETSPEED_PMFUN ,
	T_STOP_MDYVAL,T_STOP_OFFSET,T_STOP_OFFSETA,
	WAIT_EXTERNAL_ENCODER,WAIT_STOP_Y_MOTOR ,
	CHK_TOUCH,DISABLE_REPAIR_Y,
	
	Airtbl_SET_AIR,Airtbl_CLR_AIR,Airtbl_SET_TOUCH,Airtbl_CLR_TOUCH,
};

/*
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x����  �x �x�W�@���x �x����  �x   �x  7   �x �x  8   �x �x  9   �x   �x���I  �x �x      �x �x�Ͳ�  �x �x��B  �x �x����  �x �x����  �x
�x      �x �x      �x �x      �x   �x STU  �x �x VW   �x �x XYZ  �x   �x      �x �x      �x �x�Ҧ�  �x �x      �x �x      �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x60     0x61     0x62       0x63     0x64     0x65       0x66     0x67     0x68     0x69     0x77     0x70  
         �z�w�w�w�w�w�w�{ 		     	 �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
         �x�W�@���x            �x  4   �x �x  5   �x �x  6   �x   �x��@/ �x �x�{��  �x �x���/ �x �x�e�u  �x �x�Ȱ�  �x �x�Ȱ�  �x
         �x      �x            �x JKL  �x �x MNO  �x �x PQR  �x   �x/�Ͳ� �x �x����  �x �x/�ܳt �x �x�M��  �x �x�e�u  �x �x      �x
         �|�w�w�w�w�w�w�}            �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
           0x51                0x53     0x54     0x55       0x56     0x57     0x58     0x59     0x78     0x71  
         �z�w�w�w�w�w�w�{            �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
         �x  ��   �x            �x  1   �x �x  2   �x �x  3   �x   �x�w��  �x �x����  �x �xŪ��  �x �x  T   �x �x�g�J  �x �x���J  �x
         �x      �x            �x ABC  �x �x DEF  �x �x GHI  �x   �x�˸m  �x �x�ƻs  �x �x�Ϻ�  �x �x      �x �x�Ϻ�  �x �x      �x
         �|�w�w�w�w�w�w�}            �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
           0x41                0x43     0x44     0x45       0x46     0x47     0x48     0x49     0x79     0x72  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  ��   �x �x  ��   �x �x  ��   �x   �x  +/- �x �x  0   �x �x�ť���x   �x�O��  �x �x����  �x �x  T   �x �x      �x �x���  �x �x����  �x
�x      �x �x      �x �x      �x   �x      �x �x      �x �x      �x   �x      �x �x      �x �x����x �x      �x �x�]�w  �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x30     0x31     0x32       0x33     0x34     0x35       0x36     0x37     0x38     0x39     0x50     0x73  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x      �x �xY�b/  �x �xZ�b/  �x   �xA�b/  �x �xB�b/  �x �xC�b/  �x   �x�]�w  �x �x�Ͳ��q�x �xD�b/  �x �xE�b/  �x �x���  �x �x�Ѽ�  �x
�x      �x �x/���v �x �x/�}�� �x   �x/�}�� �x �x/�}�� �x �x/�}�� �x   �x�Ͳ��q�x �x�k�s  �x �x/�}�� �x �x/�}�� �x �x�e��  �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x20     0x21     0x22       0x23     0x24     0x25       0x52     0x26     0x27     0x28     0x29     0x74  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  +X  �x �x  +Y  �x �x  +Z  �x   �x  +A  �x �x  +B  �x �x  +C  �x   �x�}�l  �x �x�ֳt  �x �x  +D  �x �x  +E  �x �x      �x �x�`��  �x
�x      �x �x      �x �x      �x   �x      �x �x      �x �x      �x   �x����  �x �x���M  �x �x      �x �x      �x �x      �x �x�Ѽ�  �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x10     0x11     0x12       0x13     0x14     0x15       0x42     0x16     0x17     0x18     0x19     0x75  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  -X  �x �x  -Y  �x �x  -Z  �x   �x  -A  �x �x  -B  �x �x  -C  �x   �x����  �x �x      �x �x  -D  �x �x  -E  �x �x      �x �x  R   �x
�x      �x �x      �x �x      �x   �x      �x �x      �x �x      �x   �x����  �x �x      �x �x      �x �x      �x �x      �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
d  0xa0     0x1      0x2        0x3      0x4      0x5        0x40     0x6      0x76     0x8      0x9      0x7   
*/
#define  KEY_HELP						0x60
#define  KEY_PG_UP					0x61
#define  KEY_PG_DOWN				0x51
#define  KEY_CHG_CURSOR 		0x62
#define  KEY_UP 						0x41
#define  KEY_DOWN						0x31
#define  KEY_LEFT						0x30
#define  KEY_RIGHT					0x32

#define  KEY_7							0x63
#define  KEY_4							0x53
#define  KEY_1							0x43
#define  KEY_8							0x64
#define  KEY_5							0x54
#define  KEY_2							0x44
#define  KEY_0							0x34
#define  KEY_9							0x65
#define  KEY_6							0x55
#define  KEY_3							0x45
#define  KEY_SIGN						0x33
#define  KEY_SPACE_BAR			0x35

#define  KEY_SPECIAL				0x20
#define  KEY_PLUS_X 				0x10
#define  KEY_MINUS_X				0xa0

#define  KEY_Y_SCALE				0x21
#define  KEY_PLUS_Y 				0x11
#define  KEY_MINUS_Y				0x01

#define  KEY_Z_SW						0x22
#define  KEY_PLUS_Z 				0x12
#define  KEY_MINUS_Z				0x02

#define  KEY_PLUS_A_S_H 		0xa3
#define  KEY_MINUS_A_S_H		0xa2
#define  KEY_A_SW						0x23
#define  KEY_PLUS_A 				0x13
#define  KEY_MINUS_A				0x03

#define  KEY_B_SW						0x24
#define  KEY_PLUS_B 				0x14
#define  KEY_MINUS_B				0x04

#define  KEY_C_SW						0x25
#define  KEY_PLUS_C 				0x15
#define  KEY_MINUS_C				0x05

#define  KEY_D_SW						0x27
#define  KEY_PLUS_D 				0x17
#define  KEY_MINUS_D				0x76

#define  KEY_E_SW						0x28
#define  KEY_PLUS_E 				0x18
#define  KEY_MINUS_E				0x8

#define  KEY_ZRT						0x66
#define  KEY_SPEED_MODE 		0x68
#define  KEY_STEP						0x69
#define  KEY_TEST						0x77
#define  KEY_STOP						0x70

#define  KEY_RUN1						0x56
#define  KEY_G0 						0x57
#define  KEY_SPD						0x58
#define  KEY_CLR_Y					0x59
#define  KEY_Y_SW						0x78
#define  KEY_SUSPEND				0x71

#define  KEY_SAFE						0x46
#define  KEY_COPY_FILE			0x47
#define  KEY_LOAD_FILE			0x48
#define  KEY_T							0x49
#define  KEY_SAVE_FILE			0x79
#define  KEY_INS						0x72

#define  KEY_WR 						0x36
#define  KEY_JMPNN					0x37
#define  KEY_T_DELAY				0x38
#define  KEY_AIR						0x50
#define  KEY_CAN						0x73

#define  KEY_SETPRODNO			0x52
#define  KEY_PRODNO0				0x26
#define  KEY_AIRSCRN				0x29
#define  KEY_PARA						0x74

#define  KEY_CUTTER					0x16
#define  KEY_START_DEGREE		0x42
#define  KEY_PARA_NOPASS		0x75

#define  KEY_END_DEGREE 		0x40
#define  KEY_DUMMY_RESET_H	0x07
#define  KEY_START					0x06
#define  KEY_MARKER               0x39

#define  KEY_TDECDISA       0xff
#define  KEY_PRINTER				0xff

#define  otherkey					0x80
#define	 keycmd 					0x55 
#define	 poscmd 					0x56 	
#define	 curmiss 					0x57 	//���~�q
#define	 curquan 					0x58 	//�Ͳ��q
#define	 Cmd_Line 					0x59 	//Line
#define  Cmd_Touch1				0x05	//���w1
#define  Cmd_Touch2				0x07	//���w2
#define	 Cmd_RPM 					0x09 	//RPM
#define	 Cmd_Status 			0x0A 	//Status
#define  Cmd_Close_RPM		0x12	//Close RPM

//-----ErrorCode
#define ErrorCodeHeader 0x11
#define Unconnect				0x01
#define HomeError				0x02
#define SlideError			0x03
#define SlideTest				0x04
#define TouchError			0x05
#define TouchTest				0x06
#define OilError				0x07
#define ExtError				0x08
#define EncoderError		0x09
#define ServoError			0x0a
#define CutError				0x0b
#define OverLimite			0x0c
#define OverSoftLimite	0x0d
#define GoHome					0x0e
#define SafeError				0x0f
#define VirtualHome			0x10
#define AdcNotZero			0x11
#define NoMPG						0x12
#define OverMiss				0x13
#define OverQuan				0x14
#define ManualSet				0x15
#define AutoHome				0x16
#define DispHook				0x17


#define  Cmd_Curmiss			0xC1
#define  Cmd_Setmiss			0xC2
#define  Cmd_Curquan			0xC3
#define  Cmd_Setquan			0xC4
#define  Cmd_SetLED				0xA5
/*
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  7   �x �x  8   �x �x  9   �x   �x���I  �x �x      �x �x�Ͳ�  �x �x      �x �x�۶s  �x �x����  �x
�x STU  �x �x VW   �x �x XYZ  �x   �x      �x �x      �x �x�Ҧ�  �x �x      �x �x����  �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x63     0x64     0x65       0x66     0x67     0x68     0x69     0x77     0x70  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  4   �x �x  5   �x �x  6   �x   �x      �x �x�{��  �x �x���/ �x �x�e�u  �x �x�Ȱ�  �x �x���  �x
�x JKL  �x �x MNO  �x �x PQR  �x   �x      �x �x����  �x �x/�ܳt �x �x�M��  �x �x�e�u  �x �x����  �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x53     0x54     0x55       0x56     0x57     0x58     0x59     0x78     0x71  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  1   �x �x  2   �x �x  3   �x   �x�O��  �x �x  ��   �x �x      �x �x  T   �x �x��@/ �x �x���J  �x
�x ABC  �x �x DEF  �x �x GHI  �x   �x      �x �x      �x �x      �x �x      �x �x/�Ͳ� �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x43     0x44     0x45       0x46     0x47     0x48     0x49     0x79     0x72  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x�ť���x �x  0   �x �x  +/- �x   �x  ��   �x �x  ��   �x �x  ��   �x �x  T   �x �x���  �x �x����  �x
�x      �x �x      �x �x      �x   �x      �x �x      �x �x      �x �x����x �x�]�w  �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x33     0x34     0x35       0x36     0x37     0x38     0x39     0x50     0x73  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x���  �x �xY�b/  �x �xZ�b/  �x   �xA�b/  �x �x�Ͳ��q�x �x�]�w  �x �x�t��  �x �x����  �x �x�Ѽ�  �x
�x��b  �x �x/���v �x �x/�}�� �x   �x/�}�� �x �x�k�s  �x �x�Ͳ��q�x �x�]�w  �x �x�ƻs  �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x23     0x24     0x25       0x52     0x26     0x27     0x28     0x29     0x74  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  +X  �x �x  +Y  �x �x  +Z  �x   �x  +A  �x �x      �x �x�}�l  �x �x      �x �x�W�@���x �x����  �x
�x      �x �x      �x �x      �x   �x      �x �x      �x �x����  �x �x      �x �x      �x �x      �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x13     0x14     0x15       0x42     0x16     0x17     0x18     0x19     0x75  
�z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{   �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{ �z�w�w�w�w�w�w�{
�x  -X  �x �x  -Y  �x �x  -Z  �x   �x  -A  �x �x      �x �x����  �x �x      �x �x�U�@���x �x�s��  �x
�x      �x �x      �x �x      �x   �x      �x �x      �x �x����  �x �x      �x �x      �x �x����  �x
�|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}   �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�} �|�w�w�w�w�w�w�}
  0x3      0x4      0x5        0x40     0x6      0x76     0x8      0x9      0x7   
*/

//�p��L
#define  KEY_7_S						0x63
#define  KEY_4_S						0x53
#define  KEY_1_S						0x43
#define  KEY_8_S						0x64
#define  KEY_5_S						0x54
#define  KEY_2_S						0x44
#define  KEY_0_S						0x34
#define  KEY_9_S						0x65
#define  KEY_6_S						0x55
#define  KEY_3_S						0x45
#define  KEY_SIGN_S					0x35
#define  KEY_SPACE_BAR_S		0x33

#define  KEY_SPECIAL_S			0xff
#define  KEY_PLUS_X_S 			0x13
#define  KEY_MINUS_X_S			0x03

#define  KEY_Y_SCALE_S			0x24
#define  KEY_PLUS_Y_S 			0x14
#define  KEY_MINUS_Y_S			0x04

#define  KEY_Z_SW_S					0x25
#define  KEY_PLUS_Z_S 			0x15
#define  KEY_MINUS_Z_S			0x05

#define  KEY_PLUS_A_S_S 		0xff
#define  KEY_MINUS_A_S_S		0xff
#define  KEY_A_SW_S					0x52
#define  KEY_PLUS_A_S 			0x42
#define  KEY_MINUS_A_S			0x40

#define  KEY_ZRT_S					0x66
#define  KEY_SPEED_MODE_S 	0x68
#define  KEY_TEST_S					0x77
#define  KEY_STOP_S					0x70

#define  KEY_G0_S 					0x57
#define  KEY_SPD_S					0x58
#define  KEY_CLR_Y_S				0x59
#define  KEY_Y_SW_S					0x78
#define  KEY_STEP_S					0x71

#define  KEY_WR_S 					0x46
#define  KEY_T_S						0x49
#define  KEY_RUN1_S					0x79
#define  KEY_INS_S					0x72

#define  KEY_UP_S 					0x47
#define  KEY_DOWN_S					0x37
#define  KEY_LEFT_S					0x36
#define  KEY_RIGHT_S				0x38
#define  KEY_T_DELAY_S			0x39
#define  KEY_AIR_S					0x50
#define  KEY_CAN_S					0x73

#define  KEY_PRODNO0_S			0x26

#define  KEY_SETPRODNO_S		0x27
#define  KEY_START_DEGREE_S	0x17
#define  KEY_END_DEGREE_S 	0x76

#define  KEY_SETSPEED_S			0x28

#define  KEY_COPY_FILE_S		0x29
#define  KEY_PG_UP_S				0x19
#define  KEY_PG_DOWN_S			0x09

#define  KEY_PARA_S					0x74
#define  KEY_HELP_S					0x75
#define  KEY_CHG_CURSOR_S 	0x07

#define  KEY_DUMMY_RESET_S	0x80
#define  KEY_START_S				0x06

#define  KEY_DUMMY_RESET				0x07
#define  KEY_RESET_LOCK_ON	0x95
#define  KEY_RESET_LOCK_OFF	0x96

#define  KEY_RETURN	0x19
#define  KEY_NEXT 	0x9
#define  KEY_mytest 	0x67

#define MIN2SEC                	60L					//1��=60��
#define SEC2MS				 	1000L				//1��=1000ms
#define MIN2MS					(MIN2SEC*SEC2MS)
#define AIR_STR					((idx_language==1) ?"  �T��  ":((idx_language ==2)?"  ARIA  ":"  AIR   "))
#define MDY_UPDATE_LINE																		\
		{  																					\
			ProgType_t HUGE	*t_buf= p_buf+1 ;												\
			for(;;){																		\
				if((t_buf->bygcode == ' ') || (t_buf->bygcode == 9)){						\
					a_tbl[idx].u.line++ ;													\
					t_buf++ ;																\
				}																			\
				else{																		\
				   break ;																	\
				}																			\
			}																				\
		}
		

