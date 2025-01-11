//���F�\��
#define CAM_FUNC      	0x0
#define FEED_FUNC     	0x1
#define ROTQ_FUNC       0x2
#define ROTW_FUNC       0x3
#define SPIN_FUNC       0x4
#define CUTTER_FUNC     0x5
#define HOOK_FUNC       0x6
#define SLIDE_FUNC			0x7
#define ROTW1_FUNC			0x8
#define ANGLE_FUNC      0x9
#define NULL_FUNC      	0

#define MAX_FUNC				10

EXTERN char  FuncName[][MAX_FUNC+1][8]
#ifdef GLOBAL
={
	{" X-CAM " , " X-FEED" , " X-ROTQ" , " X-ROTW" , " X-SPIN" , " X-CUT " , " X-HOOK" , "X-SLIDE" , "X-ROTW1" , "X-ANGLE", " X-STM "} ,
	{" X-�Y��" , " X-�e��" , " X-���" , " X-½�u" , " X-����" , " X-���M" , " X-����" , " X-�Ʈy" , "X-½�u1" , " X-�騤", " X-����"} ,//�s�W�����\��
	{" X-CAM " , " X-FEED" , " X-ROTQ" , " X-ROTW" , " X-SPIN" , " X-CUT " , " X-HOOK" , "X-SLIDE" , "X-ROTW1" , "X-ANGLE", " X-STM "} ,
}
#endif
;

EXTERN char *MotorSysPara[][2]
#ifdef GLOBAL
={
	{"MOTOR NO"  , "MOT NAME"},
	{"���F�s��"  , "���F�W��"} ,
	{"N\x6  MOT.", "NOM MOT."},
}
#endif
;
//  (���F���)motor_grads[axis],(���F���A)nMotorType[axis],(���F�\��)MotFunc[axis],(���I����)home_seq_sign[axis] home_seq[axis],
//  (���I�Ҧ�)ZrtMode[axis] ,(�s�]���I)ZRTSET_sign[axis]ZRTSET[axis],(���I����)ZrtCorr[axis],MotorNEAR
EXTERN char *MotorSysPara_pass[][10]								  
#ifdef GLOBAL
={
	{"MOT GRID",	"MOT TYPE",	"MOT FUNC"		,"HOME SEQ","ZRT MODE","ZRT  SET","ZRT CORR","AXIS MAX","AXIS min","MOT NEAR"},
	{"���F���",	"���F���A", "���F\xa5\x5c��","���I����","���I�Ҧ�","�s�]���I","���I����","�̤j����","�̤p����","�^���H��"},
	{"MOT GRID",	"MOD MOT ", "MOT FUNC"		,"HOME SEQ","ZRT MODE","ZRT  SET","ZRT CORR","AXIS MAX","AXIS min","MOT NEAR"},
}
#endif
;

// ZrtPos
EXTERN char *MotorPara2_pass[][9]  
#ifdef GLOBAL
={
	{"ZRT  POS","ZRT  CYE","GEAR 0  ","GEAR 1  ","ENCR0   ","ENCR1   ","A/B Dir ","Sensor  ","ChkToPos"},
	{"���I��m","���I���","������0 ","������1 ","���P���l","���P����","A/B�ϦV ","���I�H��","�w���ˬd"},
	{"ZRT  POS","ZRT  CYE","GEAR 0  ","GEAR 1  ","ENCR0   ","ENCR1   ","A/B Dir ","Sensor  ","ChkToPos"},
}
#endif
;

EXTERN char *TDecPara[][4]
#ifdef GLOBAL
={
   {"T1DecDis","T2DecDis","T3DecDis","T4DecDis",} ,
   {"T1��Z��","T2��Z��","T3��Z��","T4��Z��",} ,
   {"T1DecDis","T2DecDis","T3DecDis","T4DecDis",} ,
}
#endif
;
EXTERN char *ColPara2_02[][4]
#ifdef GLOBAL
={
   {"HAND SPD","Wire Gap","LINE    ","LOGO    "} ,
   {"����t��","�e�u����","LINE    ","LOGO    "} ,
   {"VEL. MAN","Wire Gap","LINE    ","LOGO    "} ,
}
#endif
;
EXTERN char *ColPara2_03[][4]
#ifdef GLOBAL
={			//   ONE  dec_dist    ROTQ_MDY   SPIN_MDY
   {"ONE     ","LOCK PNO","ROTQ MDY","SPIN MDY"} ,
   {"��@�Ͳ�","��Ͳ��q","���ե�","�����ե�"} ,
   {"PRODSING","LOCK PNO","MOD.ROTQ","MOD.SPIN"} ,
}
#endif
;
EXTERN char *ColPara2_04[][4]
#ifdef GLOBAL
={
   {"BATCH   ","SIM FAST","X-Encode","MOT   NO"} ,
   {"��q    ","����FAST","X-�s�X��","���F����"} ,
   {"BATCH   ","SIM FAST","X-Encode","MOT   NO"} ,
}
#endif
;
EXTERN char *ColPara2_05[][2]
#ifdef GLOBAL
={
   {"Switch T","T  Delay"} ,
   {"�o�ʲ� T","���w����"} ,
   {"Switch T","T  Delay"} ,
}
#endif
;

EXTERN char *ColPara3_01[][1]
#ifdef GLOBAL
={
   {"Axis No "} ,
   {"�}�Ҷb��"} ,
   {"Axis No "} ,
}
#endif
;
EXTERN char *ColPara4_01[][2]
#ifdef GLOBAL
={
   {"Ser No. "," Pass Wd"} ,
   {" �� ��  ","�ҰʱK�X"} ,
   {"Ser No. "," Pass Wd"} ,
}
#endif
;
EXTERN char *ColPara4_02[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-1"} ,
   {"YYYYMMDD"," �K �X-1"} ,
   {"YYYYMMDD","PassWd-1"} ,
}
#endif
;
EXTERN char *ColPara4_03[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-2"} ,
   {"YYYYMMDD"," �K �X-2"} ,
   {"YYYYMMDD","PassWd-2"} ,
}
#endif
;
EXTERN char *ColPara4_04[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-3"} ,
   {"YYYYMMDD"," �K �X-3"} ,
   {"YYYYMMDD","PassWd-3"} ,
}
#endif
;
EXTERN char *ColPara4_05[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-4"} ,
   {"YYYYMMDD"," �K �X-4"} ,
   {"YYYYMMDD","PassWd-4"} ,
}
#endif
;
EXTERN char *ColPara4_06[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-5"} ,
   {"YYYYMMDD"," �K �X-5"} ,
   {"YYYYMMDD","PassWd-5"} ,
}
#endif
;
EXTERN char *ColPara4_07_01[][2]
#ifdef GLOBAL
={
   {"Sys Date","Sys Time"} ,
   {"�t�Τ��","�t�ήɶ�"} ,
   {"Sys Date","Sys Time"} ,
}
#endif
;
EXTERN char *ColPara4_07_02[][2]
#ifdef GLOBAL
={
   {"Set Date","Set Time"} ,
   {"�]�w���","�]�w�ɶ�"} ,
   {"Set Date","Set Time"} ,
}
#endif
;

#define MOTOR_GRADS_BCD 6
