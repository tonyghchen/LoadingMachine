//2012_0502_探針停各軸---------------------------------------------
EXTERN  uint8 T_Stop_idx;			//共?組探針
EXTERN  uint8 T_Stop_idxLast;		//最後一組探針
EXTERN  uint8 T_Stop_MdyVAL_idx;	//目前?組探針
EXTERN  bool T_Stop_Flag[20][MAX_AXIS_8];		//紀錄要停止的馬達----20為探針最多組數	
EXTERN  bool T_Stop_HaveTouch_Flag;				//探針是否有探到

EXTERN  SDWORD T_Stop_HaveVAL[20][MAX_AXIS_8];	//用於T_Stop_MdyVAL_Cmd，紀錄馬達原本要的位置
EXTERN  SDWORD T_Stop_MdyVAL[MAX_AXIS_8];		//用於T_Stop_MdyVAL_Cmd，補走格數(修正用)
EXTERN  SDWORD T_Stop_MdyVAL_Y;					//用於T_Stop_MdyVAL_Cmd，Y補走格數(經A軸運算後得Y補走格數)


EXTERN  bool T_Stop_Amov_flag;		//mode==2, 在G6開啟補償

EXTERN uint32 Axis_Zrt2016VAL[MAX_AXIS_8];		//存Zrt後2016數值
EXTERN uint32 T_Stop_AxisNowVAL[MAX_AXIS_8];	//axis Touch到的位置
EXTERN uint32 T_Stop_Axis;						//目前探針停軸狀態
EXTERN bool T_Stop_MotorStop_flg;				//目前探針預停軸_是否都停----開始計算補償格數



EXTERN uint32 T_Stop_Dw[MAX_AXIS_8];			//各軸_一條彈簧的總格數
EXTERN uint32 T_Stop_DwTouch[20][MAX_AXIS_8];	//各軸_"探針行起始"的格數(上一行走到的格數)
EXTERN uint32 T_Stop_DwAll_32[MAX_AXIS_8];		//各軸_目前累積_完成彈簧的總格數_32bit,適用ARM
EXTERN uint16 T_Stop_DwAll_16[MAX_AXIS_8];		//各軸_目前累積_完成彈簧的總格數_16bit,適用8051


//原點位置+(目前累積)+結束格數	
#define T_STOP_AXIS2016_32(axis, val)		(Axis_Zrt2016VAL[axis] + (T_Stop_DwAll_32[axis]) + val)
#define T_STOP_AXIS2016_16(axis, val)		(uint16)((uint16)Axis_Zrt2016VAL[axis] + (T_Stop_DwAll_16[axis]) + (uint16)val)



