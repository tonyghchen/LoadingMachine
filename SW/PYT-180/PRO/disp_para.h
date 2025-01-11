//馬達功能
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
	{" X-凸輪" , " X-送料" , " X-轉芯" , " X-翻線" , " X-捲取" , " X-切刀" , " X-夾耳" , " X-滑座" , "X-翻線1" , " X-折角", " X-平移"} ,//新增平移功能
	{" X-CAM " , " X-FEED" , " X-ROTQ" , " X-ROTW" , " X-SPIN" , " X-CUT " , " X-HOOK" , "X-SLIDE" , "X-ROTW1" , "X-ANGLE", " X-STM "} ,
}
#endif
;

EXTERN char *MotorSysPara[][2]
#ifdef GLOBAL
={
	{"MOTOR NO"  , "MOT NAME"},
	{"馬達編號"  , "馬達名稱"} ,
	{"N\x6  MOT.", "NOM MOT."},
}
#endif
;
//  (馬達格數)motor_grads[axis],(馬達型態)nMotorType[axis],(馬達功能)MotFunc[axis],(原點順序)home_seq_sign[axis] home_seq[axis],
//  (原點模式)ZrtMode[axis] ,(新設原點)ZRTSET_sign[axis]ZRTSET[axis],(原點對應)ZrtCorr[axis],MotorNEAR
EXTERN char *MotorSysPara_pass[][10]								  
#ifdef GLOBAL
={
	{"MOT GRID",	"MOT TYPE",	"MOT FUNC"		,"HOME SEQ","ZRT MODE","ZRT  SET","ZRT CORR","AXIS MAX","AXIS min","MOT NEAR"},
	{"馬達格數",	"馬達型態", "馬達\xa5\x5c能","原點順序","原點模式","新設原點","原點對應","最大極限","最小極限","回報信號"},
	{"MOT GRID",	"MOD MOT ", "MOT FUNC"		,"HOME SEQ","ZRT MODE","ZRT  SET","ZRT CORR","AXIS MAX","AXIS min","MOT NEAR"},
}
#endif
;

// ZrtPos
EXTERN char *MotorPara2_pass[][9]  
#ifdef GLOBAL
={
	{"ZRT  POS","ZRT  CYE","GEAR 0  ","GEAR 1  ","ENCR0   ","ENCR1   ","A/B Dir ","Sensor  ","ChkToPos"},
	{"原點位置","原點圈數","齒輪比0 ","齒輪比1 ","分周分子","分周分母","A/B反向 ","原點信號","定位檢查"},
	{"ZRT  POS","ZRT  CYE","GEAR 0  ","GEAR 1  ","ENCR0   ","ENCR1   ","A/B Dir ","Sensor  ","ChkToPos"},
}
#endif
;

EXTERN char *TDecPara[][4]
#ifdef GLOBAL
={
   {"T1DecDis","T2DecDis","T3DecDis","T4DecDis",} ,
   {"T1減距離","T2減距離","T3減距離","T4減距離",} ,
   {"T1DecDis","T2DecDis","T3DecDis","T4DecDis",} ,
}
#endif
;
EXTERN char *ColPara2_02[][4]
#ifdef GLOBAL
={
   {"HAND SPD","Wire Gap","LINE    ","LOGO    "} ,
   {"手輪速度","送線間隙","LINE    ","LOGO    "} ,
   {"VEL. MAN","Wire Gap","LINE    ","LOGO    "} ,
}
#endif
;
EXTERN char *ColPara2_03[][4]
#ifdef GLOBAL
={			//   ONE  dec_dist    ROTQ_MDY   SPIN_MDY
   {"ONE     ","LOCK PNO","ROTQ MDY","SPIN MDY"} ,
   {"單一生產","鎖生產量","轉芯校正","捲取校正"} ,
   {"PRODSING","LOCK PNO","MOD.ROTQ","MOD.SPIN"} ,
}
#endif
;
EXTERN char *ColPara2_04[][4]
#ifdef GLOBAL
={
   {"BATCH   ","SIM FAST","X-Encode","MOT   NO"} ,
   {"批量    ","模擬FAST","X-編碼器","馬達型號"} ,
   {"BATCH   ","SIM FAST","X-Encode","MOT   NO"} ,
}
#endif
;
EXTERN char *ColPara2_05[][2]
#ifdef GLOBAL
={
   {"Switch T","T  Delay"} ,
   {"寸動盒 T","探針延遲"} ,
   {"Switch T","T  Delay"} ,
}
#endif
;

EXTERN char *ColPara3_01[][1]
#ifdef GLOBAL
={
   {"Axis No "} ,
   {"開啟軸數"} ,
   {"Axis No "} ,
}
#endif
;
EXTERN char *ColPara4_01[][2]
#ifdef GLOBAL
={
   {"Ser No. "," Pass Wd"} ,
   {" 序 號  ","啟動密碼"} ,
   {"Ser No. "," Pass Wd"} ,
}
#endif
;
EXTERN char *ColPara4_02[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-1"} ,
   {"YYYYMMDD"," 密 碼-1"} ,
   {"YYYYMMDD","PassWd-1"} ,
}
#endif
;
EXTERN char *ColPara4_03[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-2"} ,
   {"YYYYMMDD"," 密 碼-2"} ,
   {"YYYYMMDD","PassWd-2"} ,
}
#endif
;
EXTERN char *ColPara4_04[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-3"} ,
   {"YYYYMMDD"," 密 碼-3"} ,
   {"YYYYMMDD","PassWd-3"} ,
}
#endif
;
EXTERN char *ColPara4_05[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-4"} ,
   {"YYYYMMDD"," 密 碼-4"} ,
   {"YYYYMMDD","PassWd-4"} ,
}
#endif
;
EXTERN char *ColPara4_06[][2]
#ifdef GLOBAL
={
   {"YYYYMMDD","PassWd-5"} ,
   {"YYYYMMDD"," 密 碼-5"} ,
   {"YYYYMMDD","PassWd-5"} ,
}
#endif
;
EXTERN char *ColPara4_07_01[][2]
#ifdef GLOBAL
={
   {"Sys Date","Sys Time"} ,
   {"系統日期","系統時間"} ,
   {"Sys Date","Sys Time"} ,
}
#endif
;
EXTERN char *ColPara4_07_02[][2]
#ifdef GLOBAL
={
   {"Set Date","Set Time"} ,
   {"設定日期","設定時間"} ,
   {"Set Date","Set Time"} ,
}
#endif
;

#define MOTOR_GRADS_BCD 6
