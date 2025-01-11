#include	"c_struct.h"




typedef struct
{
  //config0:		
		
	
 
  //config24:(uty)6軸:(2+2)*8=32b	,8軸:()+32b	
  //uint16 	ENCR0[MAX_AXIS],bENCR0[MAX_AXIS] ;
  //uint16 	ENCR1[MAX_AXIS],bENCR1[MAX_AXIS] ;

  //config25:6軸:4b					,8軸:4b(浪費),併在config24(2)
	uint32	CutDist ;

  //config26:6軸:2b					,8軸:2b	
	uint16 	MPG_X100 ;	

  //config27:(1*3)*3=9b
	uint8 	ManSpeed_PMfun[3],bManSpeed_PMfun[3];//8軸:3b(浪費),併在config24(0)
	uint8 	RORSpeed_PMfun[3],bRORSpeed_PMfun[3] ;
	uint8 	DefSpeed_PMfun[3],bDefSpeed_PMfun[3] ;
	
	WORD  WORD_ManSpeed_PMfun[3] ; 

  //config28:6軸:1*6=6b				,8軸:1*8=8b
	uint8 	ZrtCorr[MAX_PROG_AXIS];

  //config29:6軸:(1*8)*3=24b		,8軸:24b(浪費),併在config24(1)
	uint8 	SPDPlus[MAX_AXIS_8],bSPDPlus[MAX_AXIS_8];
	uint8 	SPDMinus[MAX_AXIS_8],bSPDMinus[MAX_AXIS_8];
	uint8 	SPDFun[MAX_AXIS_8],bSPDFun[MAX_AXIS_8];
	
	WORD  WORD_SPDPlus[MAX_AXIS_8];
	WORD  WORD_SPDMinus[MAX_AXIS_8];
	WORD  WORD_SPDFun[MAX_AXIS_8];

  //config30:1b
	uint8 WileSTOP;

  //config31:(uty)6軸(1+4)*6=30b	,8軸:(1+4)*8=40b
  //uint32 	Max[MAX_AXIS] ;
  //uint8 	Max_sign[MAX_AXIS] ;

  //config32:(uty)6軸(1+4)*6=30b	,8軸:(1+4)*8=40b
  //uint32 	Min[MAX_AXIS] ;
  //uint8 	Min_sign[MAX_AXIS] ;	

  //config33:1b
	uint8 	Touch_Stop_Flag;

  //config34:(uty)6軸(1+4)*2=10b	,8軸:10b(浪費),併在config31,config32	
  //		Max[AXIS_D],Max_sign[AXIS_D] ;
  //		Min[AXIS_D],Min_sign[AXIS_D] ;	

  //config35:6軸:1b					,8軸:1b(浪費),併在config24(7)
	uint8 	WileMode;

  //config36:6軸:1b					,8軸:1b(浪費),併在config24(8)	
	uint8 	CursorMode;	

  //config37:(uty)6軸:2b+1b=3b		,8軸:3b(浪費),併在config24(5)
  //uint16	MANUFACTORY ;
  	uint8 	keyboard_type;

  //config38:(uty)6軸:2*6=12b		,8軸:2*8=16b(浪費),併在config24(6)
  //uint16	G1Rate[MAX_AXIS] ;

  //config39:6軸:(2+1+1+1)*8*10=400b,8軸:(2+1+1+1)*8*10=400b(浪費),併在config24(3)
	WORD 	bTblSETSPD[MAX_AXIS_8][ItemNo_bTblSETSPD] ;
	uint8 	bTblSPDPlus[MAX_AXIS_8][ItemNo_bTblSETSPD] ;
	uint8 	bTblSPDMinus[MAX_AXIS_8][ItemNo_bTblSETSPD] ;
	uint8 	bTblSPDFun[MAX_AXIS_8][ItemNo_bTblSETSPD] ;

	WORD 	TblSETSPD[10] ; 
	WORD 	TblSPDPlus[10] ;
	WORD 	TblSPDMinus[10] ;
	WORD 	TblSPDFun[10] ;

  //config40:6軸:1b					,8軸:1b(浪費),併在config24(4)
	uint8 	WorkMode ;
	uint8 	lWorkMode ;			//不存	

  //config41:(4+1+4)=9b
	DWORD 	TDecMode ;			//沒用
	uint8 	TDecMode_sign ;	//沒用
	DWORD 	TDecDis ;  			//沒用

  //config42:4*4=16b
	DWORD 	TDecDisA[4] ;

  //config43:(uty)6軸:2*6=12b		,8軸:2*8=16b(浪費),併在config24(9)	
  //uint16 	ZRTPreM[MAX_AXIS] ;

  //config44:4b
 	DWORD 	repair_y;//整定速度

  //config45:1*8=8b  	
	uint8 	SPDRate[MAX_AXIS_8],bSPDRate[MAX_AXIS_8]; //加減比率
	
	WORD  	WORD_SPDRate[MAX_AXIS_8];

  //config46:2b	
	WORD  	WireGap ;//送線間隙

  //config47:4*2=8b
 	DWORD 	gear_y[2];//Y軸齒比(外接encoder)

  //config48:4b 
 	DWORD 	dist_y;//整定距離

  //config49:1b
	uint8 	SPDLinkMode;//聯動模式

  //config50:1b 
	//NULL(原本共用一個LOWSPD改成每軸都有config57)

  //config51:(uty)6軸:1*7=7b		,8軸:1*8=8b(浪費),併在config24(10)	 
  //uint8 	ABDir[MAX_AXIS] ;
 
  //config52:6軸、8軸切齊

  //config53:	
	DWORD		TDelay;	//探針延遲
    	
  //config54:	
	uint8 	MotFunc[MAX_AXIS_8] ; //馬達功能
	
	//config55:	
	uint8 	UsePMfun ; //加減速

	//config56:	
	DWORD		nY0[MAX_AXIS_8];//Y0:單位換算(目前只用Y軸、其他保留)	
	
	//config57:	
  uint8 	LOWSPD[MAX_AXIS_8],bLOWSPD[MAX_AXIS_8] ;//最小加減速
  WORD  	WORD_LOWSPD[MAX_AXIS_8];

	//config58:
	DWORD 	GEAR0[MAX_AXIS_8] ;//齒輪比0 (Y軸格數:外接Encoder格數 = 齒輪比0:齒輪比1)
	DWORD 	GEAR1[MAX_AXIS_8] ;//齒輪比1
	DWORD  	ZrtPos[MAX_AXIS_8];//原點位置
	DWORD  	ZrtCye[MAX_AXIS_8];//原點圈數
	uint8  	ZrtCye_sign[MAX_AXIS_8];//原點圈數sign
	
	//config59:
	uint8		SensorHighLow[MAX_AXIS_8];//原點信號

	//config60:
	uint8		nMotorType[MAX_AXIS_8];	//馬達型態
	
	//config61:
	uint8		AxisNo;						//開啟軸數
  
  //config62:
  uint8 	PassYear,PassMon,PassDay ;
	uint8 	EnPassWd ;
  
  //config63:
  uint32	ChkToPos[MAX_AXIS_8];//定位檢查
  
 //config64:
	uint16 IDMS[MAX_AXIS_8] ; //BCD 加減速
	uint8 G2Mode;    //0:儘量讓x軸保持定速(其他軸可能超出生產速率),1:各軸不超出生產速率
 // config65:
	uint8       SPDMode ;
  //config67:	
	uint16 	CusRate[MAX_AXIS_8] ; //自訂速率
   //config68:	
	uint8	PRODDELAY ; //生產延遲
    //config69:	
	uint8	XMINUS ; //X軸反向
	 //config70:	
	uint8	KEYLOCK ; //鍵盤鎖住
  //config72:	
	uint16	Touch_rate ; //探針鎖定速率
	
	uint16 	FileRate[100] ; //自訂速率
	uint16 	FileFastRate[100] ; //自訂速率
  //uint32 MONTH[15];
	//uint32 PASS[15];
	//uint16 RUNDAYS ;
	//uint32 PRODPASS ;
  //config74:	
	uint8	SlideLimit ; //滑座極限修改成參數
  //config75:	
	uint8	AirOff ; //汽缸解除
  //config76:	
	uint8	WireTime ; //線架時間
	 //config77:	
	uint8	OilChk ; //供油檢測
  
  
  //未儲存參數:
  //uint8	BiosRst,lBiosRst;									//BIOS重置
  bool	touch_before_err;									//探針前錯誤
  bool 	havePM_Open[MAX_AXIS_8];					//各軸是否使用加減速
	uint32 SystemDate,SystemTime[3];				//系統日期,系統時間
  uint32 SetSystemDate[3],SetSystemTime[3];	//設定日期,設定時間
  
  	
  uint32	BATCHn; //新加批量功能,格式:最低4位元代表配合的AIR編號,其餘為批量數目	
	uint32 	PayOff ;
	uint8 	SwitchT ;
	uint8 	bSwitchT ;

	uint8	air_buf, man_air;
	uint16 	MotorType,MotorNEAR ;
	uint8  bMotorNEAR[MAX_AXIS] ;
	uint8 	TAIDAMotor ;
  	
  	
	uint32	bmotor_grads[MAX_AXIS];
	uint8 	SPDMotorID ;
	int NewVal[MAX_AXIS];
	SDWORD NewValtmp[MAX_AXIS];
	uint8		axis_lval[MAX_AXIS] ;
	uint8		axis_llval[MAX_AXIS] ;
	double MaxV[MAX_AXIS_8] ;
	double acc[MAX_AXIS_8] ;
	uint16 Tidms[MAX_AXIS_8][1] ;//500
	uint16 bIDMS[MAX_AXIS_8] ;  //binary 加減速
	uint16 Autoidms[MAX_AXIS_8][1] ;//500
#include "machines.h"
}MachineStatus_t;

//2012_0613_ETP_Bound_Check------------------------------------------
/*		
//machines.h		//打x代表，有LOAD/SAVE_FILE
	uint8	p3701[MAX_AXIS];
x	uint8	motor[MAX_AXIS];		//1:代表在開啟馬達狀態/0:代表在關閉馬達狀態

	uint8	is_home[MAX_AXIS];		//當為1時,代表該軸目前正在原點
	uint8	go_home[MAX_AXIS];		//當某軸欲回原點時,設定其為1;當該原點中斷發生時,被清除為0
	uint8	running[MAX_AXIS];
x	uint16	manval[MAX_AXIS];		//手動
	uint8	sign[MAX_AXIS]	, dst_pos_sign[MAX_AXIS]	 , lsign[MAX_AXIS] ;
	uint32	axis_val[MAX_AXIS], dst_pos[MAX_AXIS], laxis_val[MAX_AXIS];
x	uint32	motor_grads[MAX_AXIS];
	uint8	prev_mov[MAX_AXIS], prev_sign[MAX_AXIS];
x	uint16	Rate[MAX_AXIS] ;
x	uint8	home_seq[MAX_AXIS],home_seq_sign[MAX_AXIS] ;
x	uint16	speed[2]; //紀錄FAST/AUTO設定的速度	
	uint32	rec_th[4], dcur_th[4] , cur_thy[4];
	uint8	chk_th[4], pass_th[4],chk_th_stop_axis[4];
	uint16	loop_stack[MAX_LOOP];
	uint16	loop_times[MAX_LOOP];
	uint16	loop_cnt[MAX_LOOP];
	uint16	handval[MAX_AXIS]; //手輪
x	uint16	wZeroSpd[MAX_AXIS] ;
x	uint8	ZrtMode[MAX_AXIS] ;
x	uint8	Unit[MAX_AXIS] ;
	
x	uint32 Max[MAX_AXIS] ;
x	uint32 Min[MAX_AXIS] ;
x	uint8 	Max_sign[MAX_AXIS] ;
x	uint8 	Min_sign[MAX_AXIS] ;	
x	uint16    AxisDelay[MAX_AXIS] ;
x	uint8	ZRTSET_sign[MAX_AXIS];
x	uint32    ZRTSET[MAX_AXIS] ;	
x	uint8    ToPos[MAX_AXIS] ;	
x	uint16 ENCR0[MAX_AXIS] ;
x	uint16 ENCR1[MAX_AXIS] ;
x	uint16 bENCR0[MAX_AXIS] ;
x	uint16 bENCR1[MAX_AXIS] ;	
//Struct.h		
	uint8 ManSpeed_PMfun[3] ;
	uint8 bManSpeed_PMfun[3] ;
	uint8 ZrtCorr[6];
	uint8 SPDPlus[8];
	uint8 SPDMinus[8];
	uint8 SPDFun[8];
	uint8 bSPDPlus[8];
	uint8 bSPDMinus[8];
	uint8 bSPDFun[8];
	WORD  WORD_SPDPlus[8];
	WORD  WORD_SPDMinus[8];
	WORD  WORD_SPDFun[8];
	WORD  WORD_ManSpeed_PMfun[3] ;
*/




struct SIM_MOTOR{
	DWORD  dabsloc[MAX_AXIS] ;
	WORD    wlval2016[MAX_AXIS] ;
	SDWORD  totalmov[MAX_AXIS] ;
} ;

struct STBATCHn{
	uint8 flag ;
	uint32 no ;
	uint32 Cno ;
	uint8 airON ;
	struct TIMER timeout ;
	uint8 airno ;
} ;





#if CHK_MAN_MOV
struct ST_CHK_MAN_MOV{
	bool boenable ;
	bool boflg[MAX_AXIS] ;
	WORD wabs2016[MAX_AXIS] ;
	WORD wincval[MAX_AXIS] ;
} ;	
#endif



struct ST_EXTENCODER{
	BYTE  mode ;  // 0:只有Y軸移動1:只有A軸移動2:A和Y軸都有移動
	bool first ;
	DWORD save_yabsloc ;
	DWORD save_lyabsloc ;
	DWORD save_aabsloc ;
	DWORD save_laabsloc ;
	SDWORD save_ymov ;
	bool    updategap ;
	SDWORD  curgap ;
	SDWORD  plus_maxgap ;
	SDWORD  minus_maxgap;
	DWORD   meangap ;
	DWORD   nogap ;
	bool	dir;
} ;
struct SET3701_ARM{
	DWORD speed[MAX_AXIS] ;
	DWORD dist[MAX_AXIS] ;
	BYTE  dir[MAX_AXIS] ;
} ;
struct OVER_RPM{
	BYTE axis ;
	SDWORD val ;
} ;
struct FLASH_CURSOR{
	uint8 str[20] ;
	uint16 x,y,bcol,fcol;
	bool state ;
} ;
struct ROLLDATA
{
	unsigned char huge  *pcx[30] ;
	char palette[48*3] ;
} ;

