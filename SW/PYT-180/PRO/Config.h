#include 	"c_config.h"
//config9
#define FLOC_X_SPD			(FLOC_RATE_D+LEN_RATE_D)
#define LEN_X_SPD			sizeof(MachineStatus.X_SPD)
//config10
#define FLOC_ROTQ_MDY  	 	(FLOC_X_SPD+LEN_X_SPD)
#define LEN_ROTQ_MDY		sizeof(MachineStatus.ROTQ_MDY)
#define FLOC_SPIN_MDY		(FLOC_ROTQ_MDY+LEN_ROTQ_MDY)
#define LEN_SPIN_MDY		sizeof(MachineStatus.SPIN_MDY)
//config11
#define FLOC_UsbDisk		(FLOC_SPIN_MDY+LEN_SPIN_MDY)
#define LEN_UsbDisk			sizeof(MachineStatus.UsbDisk)
//config12
#define FLOC_ONE			(FLOC_UsbDisk+LEN_UsbDisk)
#define LEN_ONE				sizeof(MachineStatus.ONE)
//config13
#define FLOC_MotorType		(FLOC_ONE+LEN_ONE)
#define LEN_MotorType		sizeof(MachineStatus.MotorType)
#define FLOC_MotorNEAR		(FLOC_MotorType+LEN_MotorType)
#define LEN_MotorNEAR		sizeof(MachineStatus.MotorNEAR)
//config14
#define FLOC_X_Encoder		(FLOC_MotorNEAR+LEN_MotorNEAR)
#define LEN_X_Encoder		sizeof(MachineStatus.X_Encoder)
//config15
#define FLOC_Y_Encoder		(FLOC_X_Encoder+LEN_X_Encoder)
#define LEN_Y_Encoder		sizeof(MachineStatus.Y_Encoder)

//config16
//各軸:6/8
#define FLOC_ToPos			(FLOC_Y_Encoder+LEN_Y_Encoder)
#define LEN_ToPos			sizeof(MachineStatus.ToPos[0])

//config17
#define FLOC_FEEDER			(FLOC_ToPos+LEN_ToPos*MAX_PROG_AXIS)
#define LEN_FEEDER			sizeof(MachineStatus.FEEDER)
//config18
#define FLOC_SPIN_ZRT		(FLOC_FEEDER+LEN_FEEDER)
#define LEN_SPIN_ZRT		sizeof(MachineStatus.SPIN_ZRT)
//config19
#define FLOC_SimFast		(FLOC_SPIN_ZRT+LEN_SPIN_ZRT)
#define LEN_SimFast			sizeof(MachineStatus.SimFast)
//config20
#define FLOC_BATCHn			(FLOC_SimFast+LEN_SimFast)
#define LEN_BATCHn			sizeof(MachineStatus.BATCHn)
//config21
#define FLOC_TAIDAMotor		(FLOC_BATCHn+LEN_BATCHn)
#define LEN_TAIDAMotor		sizeof(MachineStatus.TAIDAMotor)
//config22
#define FLOC_PayOff			(FLOC_TAIDAMotor+LEN_TAIDAMotor)  
#define LEN_PayOff			(sizeof(MachineStatus.PayOff))
//config23_6軸、8軸軟體到config23皆相同
#define FLOC_SwitchT		(FLOC_PayOff+LEN_PayOff)  
#define LEN_SwitchT			(sizeof(MachineStatus.SwitchT))

//config24
#ifndef HNCNC6
//8軸銜接(753+2*8+2*8)
//(0)
#define FLOC_ManSpeed_PMfun8	(FLOC_SwitchT+LEN_SwitchT)  
#define LEN_ManSpeed_PMfun8		(sizeof(MachineStatus.ManSpeed_PMfun[0]))
//(1)
#define FLOC_SPDPlus8			(FLOC_ManSpeed_PMfun8+LEN_ManSpeed_PMfun8*3)
#define LEN_SPDPlus8			(sizeof(MachineStatus.SPDPlus[0]))
#define FLOC_SPDMinus8			(FLOC_SPDPlus8+LEN_SPDPlus8*MAX_AXIS)
#define LEN_SPDMinus8			(sizeof(MachineStatus.SPDMinus[0]))
#define FLOC_SPDFun8			(FLOC_SPDMinus8+LEN_SPDMinus8*MAX_AXIS)
#define LEN_SPDFun8				(sizeof(MachineStatus.SPDFun[0]))
//(2)
#define FLOC_CutDist8			(FLOC_SPDFun8+LEN_SPDFun8*MAX_AXIS)  
#define LEN_CutDist8			(sizeof(MachineStatus.CutDist))
//(3)
#define FLOC_bTblSETSPD8		(FLOC_CutDist8+LEN_CutDist8)
#define LEN_bTblSETSPD8			(sizeof(MachineStatus.bTblSETSPD[0][0]))
#define FLOC_bTblSPDPlus8		(FLOC_bTblSETSPD8+LEN_bTblSETSPD8*MAX_AXIS*ItemNo_bTblSETSPD)
#define LEN_bTblSPDPlus8		(sizeof(MachineStatus.bTblSPDPlus[0][0]))
#define FLOC_bTblSPDMinus8		(FLOC_bTblSPDPlus8+LEN_bTblSPDPlus8*MAX_AXIS*ItemNo_bTblSETSPD)
#define LEN_bTblSPDMinus8		(sizeof(MachineStatus.bTblSPDMinus[0][0]))
#define FLOC_bTblSPDFun8		(FLOC_bTblSPDMinus8+LEN_bTblSPDMinus8*MAX_AXIS*ItemNo_bTblSETSPD)
#define LEN_bTblSPDFun8			(sizeof(MachineStatus.bTblSPDFun[0][0]))
//(4)
#define FLOC_WorkMode8			(FLOC_bTblSPDFun8+LEN_bTblSPDFun8*MAX_AXIS*ItemNo_bTblSETSPD)
#define LEN_WorkMode8			(sizeof(MachineStatus.WorkMode))
//(5)
#define FLOC_MANUFACTORY8		(FLOC_WorkMode8+LEN_WorkMode8)
#define LEN_MANUFACTORY8		(sizeof(MachineStatus.MANUFACTORY))
#define FLOC_keyboard_type8		(FLOC_MANUFACTORY8+LEN_MANUFACTORY8)
#define LEN_keyboard_type8		(sizeof(MachineStatus.keyboard_type))
//(6)
#define FLOC_G1RATE8			(FLOC_keyboard_type8+LEN_keyboard_type8)
#define LEN_G1RATE8				(sizeof(MachineStatus.G1Rate[0]))
//(7)
#define FLOC_WileMode8			(FLOC_G1RATE8+LEN_G1RATE8*MAX_AXIS)
#define LEN_WileMode8			(sizeof(MachineStatus.WileMode))
//(8)
#define FLOC_CursorMode8		(FLOC_WileMode8+LEN_WileMode8)
#define LEN_CursorMode8			(sizeof(MachineStatus.CursorMode))
//(9)
#define FLOC_ZRTPreM8			(FLOC_CursorMode8+LEN_CursorMode8)
#define LEN_ZRTPreM8			(sizeof(MachineStatus.ZRTPreM[0]))
//(10)
#define FLOC_ABDir8				(FLOC_ZRTPreM8+LEN_ZRTPreM8*MAX_AXIS)
#define LEN_ABDir8				(sizeof(MachineStatus.ABDir[0]))

#define FLOC_ENCR0				(FLOC_ABDir8+LEN_ABDir8*MAX_AXIS)
#else
//6軸
#define FLOC_ENCR0			(FLOC_SwitchT+LEN_SwitchT)
#endif
#define LEN_ENCR0			(sizeof(MachineStatus.ENCR0[0]))
#define FLOC_ENCR1			(FLOC_ENCR0+LEN_ENCR0*MAX_AXIS)
#define LEN_ENCR1			(sizeof(MachineStatus.ENCR1[0]))
//config25
#define FLOC_CutDist		(FLOC_ENCR1+LEN_ENCR1*MAX_AXIS)  
#define LEN_CutDist			(sizeof(MachineStatus.CutDist))
//config26
#define FLOC_MPG_X100		(FLOC_CutDist+LEN_CutDist)  
#define LEN_MPG_X100		(sizeof(MachineStatus.MPG_X100))
//config27
#define FLOC_ManSpeed_PMfun	(FLOC_MPG_X100+LEN_MPG_X100)  
#define LEN_ManSpeed_PMfun	(sizeof(MachineStatus.ManSpeed_PMfun[0]))
#define FLOC_RORSpeed_PMfun	(FLOC_ManSpeed_PMfun+LEN_ManSpeed_PMfun*3)  
#define LEN_RORSpeed_PMfun	(sizeof(MachineStatus.RORSpeed_PMfun[0]))
#define FLOC_DefSpeed_PMfun	(FLOC_RORSpeed_PMfun+LEN_RORSpeed_PMfun*3)  
#define LEN_DefSpeed_PMfun	(sizeof(MachineStatus.DefSpeed_PMfun[0]))
//config28
#define FLOC_ZRTCORR		(FLOC_DefSpeed_PMfun+LEN_DefSpeed_PMfun*3)
#define LEN_ZRTCORR			(sizeof(MachineStatus.ZrtCorr[0]))
//config29
#define FLOC_SPDPlus		(FLOC_ZRTCORR+LEN_ZRTCORR*MAX_PROG_AXIS)
#define LEN_SPDPlus			(sizeof(MachineStatus.SPDPlus[0]))
#define FLOC_SPDMinus		(FLOC_SPDPlus+LEN_SPDPlus*8)
#define LEN_SPDMinus		(sizeof(MachineStatus.SPDMinus[0]))
#define FLOC_SPDFun			(FLOC_SPDMinus+LEN_SPDMinus*8)
#define LEN_SPDFun			(sizeof(MachineStatus.SPDFun[0]))
//config30
#define FLOC_WileSTOP		(FLOC_SPDFun+LEN_SPDFun*8)
#define LEN_WileSTOP		(sizeof(MachineStatus.WileSTOP))
//config31
#define FLOC_Max			(FLOC_WileSTOP+LEN_WileSTOP)
#define LEN_Max				(sizeof(MachineStatus.Max_sign[0])+sizeof(MachineStatus.Max[0]))
//config32
#define FLOC_Min			(FLOC_Max+LEN_Max*MAX_PROG_AXIS)
#define LEN_Min				(sizeof(MachineStatus.Min_sign[0])+sizeof(MachineStatus.Min[0]))
//config33
#define FLOC_Touch_Stop_Flag (FLOC_Min+LEN_Min*MAX_PROG_AXIS)
#define LEN_Touch_Stop_Flag	 (sizeof(MachineStatus.Touch_Stop_Flag))
//config34
#define FLOC_Max_D			(FLOC_Touch_Stop_Flag+LEN_Touch_Stop_Flag)
#define LEN_Max_D			(sizeof(MachineStatus.Max_sign[AXIS_D])+sizeof(MachineStatus.Max[AXIS_D]))
#define FLOC_Min_D			(FLOC_Max_D+LEN_Max_D)
#define LEN_Min_D			(sizeof(MachineStatus.Min_sign[AXIS_D])+sizeof(MachineStatus.Min[AXIS_D]))
//config35
#define FLOC_WileMode		(FLOC_Min_D+LEN_Min_D)
#define LEN_WileMode		(sizeof(MachineStatus.WileMode))
//config36
#define FLOC_CursorMode		(FLOC_WileMode+LEN_WileMode)
#define LEN_CursorMode		(sizeof(MachineStatus.CursorMode))
//config37
#define FLOC_MANUFACTORY	(FLOC_CursorMode+LEN_CursorMode)
#define LEN_MANUFACTORY		(sizeof(MachineStatus.MANUFACTORY))
#define FLOC_keyboard_type	(FLOC_MANUFACTORY+LEN_MANUFACTORY)
#define LEN_keyboard_type	(sizeof(MachineStatus.keyboard_type))
//config38
#define FLOC_G1RATE			(FLOC_keyboard_type+LEN_keyboard_type)
#define LEN_G1RATE			(sizeof(MachineStatus.G1Rate[0]))
//config39
#define FLOC_bTblSETSPD		(FLOC_G1RATE+LEN_G1RATE*MAX_AXIS)
#define LEN_bTblSETSPD		(sizeof(MachineStatus.bTblSETSPD[0][0]))
#define FLOC_bTblSPDPlus	(FLOC_bTblSETSPD+LEN_bTblSETSPD*MAX_AXIS_8*ItemNo_bTblSETSPD)
#define LEN_bTblSPDPlus		(sizeof(MachineStatus.bTblSPDPlus[0][0]))
#define FLOC_bTblSPDMinus	(FLOC_bTblSPDPlus+LEN_bTblSPDPlus*MAX_AXIS_8*ItemNo_bTblSETSPD)
#define LEN_bTblSPDMinus	(sizeof(MachineStatus.bTblSPDMinus[0][0]))
#define FLOC_bTblSPDFun		(FLOC_bTblSPDMinus+LEN_bTblSPDMinus*MAX_AXIS_8*ItemNo_bTblSETSPD)
#define LEN_bTblSPDFun		(sizeof(MachineStatus.bTblSPDFun[0][0]))
//config40
#define FLOC_WorkMode		(FLOC_bTblSPDFun+LEN_bTblSPDFun*MAX_AXIS_8*ItemNo_bTblSETSPD)
#define LEN_WorkMode		(sizeof(MachineStatus.WorkMode))
//config41
#define FLOC_TDecMode		(FLOC_WorkMode+LEN_WorkMode)
#define LEN_TDecMode		(sizeof(MachineStatus.TDecMode_sign)+sizeof(MachineStatus.TDecMode))
#define FLOC_TDecDis		(FLOC_TDecMode+LEN_TDecMode)
#define LEN_TDecDis			(sizeof(MachineStatus.TDecDis))
//config42
#define FLOC_TDecDisA		(FLOC_TDecDis+LEN_TDecDis)
#define LEN_TDecDisA		(sizeof(MachineStatus.TDecDisA[0]))
//config43
#define FLOC_ZRTPreM		(FLOC_TDecDisA+LEN_TDecDisA*4)
#define LEN_ZRTPreM			(sizeof(MachineStatus.ZRTPreM[0]))
//config44
#define FLOC_REPAIR_Y		(FLOC_ZRTPreM+LEN_ZRTPreM*MAX_AXIS)
#define LEN_REPAIR_Y		sizeof(MachineStatus.repair_y)
//config45
#define FLOC_SPDRate		(FLOC_REPAIR_Y+LEN_REPAIR_Y)
#define LEN_SPDRate			sizeof(MachineStatus.SPDRate[0])
//config46
#define FLOC_WIREGAP		(FLOC_SPDRate+LEN_SPDRate*MAX_AXIS_8)
#define LEN_WIREGAP			sizeof(MachineStatus.WireGap)
//config47
#define FLOC_GEARY			(FLOC_WIREGAP+LEN_WIREGAP)
#define LEN_GEARY				sizeof(MachineStatus.gear_y[0])
//config48
#define FLOC_DISTY			(FLOC_GEARY+LEN_GEARY*2)
#define LEN_DISTY				sizeof(MachineStatus.dist_y)
//config49
#define FLOC_SPDLinkMode 	(FLOC_DISTY+LEN_DISTY)
#define LEN_SPDLinkMode		sizeof(MachineStatus.SPDLinkMode)
//config50
#define FLOC_NULL_LOWSPD	(FLOC_SPDLinkMode+LEN_SPDLinkMode)
#define LEN_NULL_LOWSPD		sizeof(MachineStatus.LOWSPD[0])
//config51
#define FLOC_ABDir			(FLOC_NULL_LOWSPD+LEN_NULL_LOWSPD)
#define LEN_ABDir				sizeof(MachineStatus.ABDir[0])
//config52:6軸、8軸設定檔切齊
#define FLOC_ConfigAlign	(FLOC_ABDir+LEN_ABDir*MAX_AXIS)
#ifdef HNCNC6
#define LEN_ConfigAlign	(1423-869)
#else
#define LEN_ConfigAlign	0
#endif
//config53
#define FLOC_TDelay			(FLOC_ConfigAlign+LEN_ConfigAlign)
#define LEN_TDelay			sizeof(MachineStatus.TDelay)
//config54
#define FLOC_MotFunc		(FLOC_TDelay+LEN_TDelay)
#define LEN_MotFunc			sizeof(MachineStatus.MotFunc[0])
//config55
#define FLOC_UsePMfun		(FLOC_MotFunc+LEN_MotFunc*MAX_AXIS_8)
#define LEN_UsePMfun		sizeof(MachineStatus.UsePMfun)
//config56
#define FLOC_nY0				(FLOC_UsePMfun+LEN_UsePMfun)
#define LEN_nY0					sizeof(MachineStatus.nY0[0])
//config57
#define FLOC_LOWSPD			(FLOC_nY0+LEN_nY0*MAX_AXIS_8)
#define LEN_LOWSPD			sizeof(MachineStatus.LOWSPD[0])
//config58
#define FLOC_ZrtPos			(FLOC_LOWSPD+LEN_LOWSPD*MAX_AXIS_8)
#define LEN_ZrtPos			sizeof(MachineStatus.ZrtPos[0])
#define FLOC_ZrtCye			(FLOC_ZrtPos+LEN_ZrtPos*MAX_AXIS_8)
#define LEN_ZrtCye			(sizeof(MachineStatus.ZrtCye_sign[0])+sizeof(MachineStatus.ZrtCye[0]))
#define FLOC_GEAR0			(FLOC_ZrtCye+LEN_ZrtCye*MAX_AXIS_8)
#define LEN_GEAR0				sizeof(MachineStatus.GEAR0[0])
#define FLOC_GEAR1			(FLOC_GEAR0+LEN_GEAR0*MAX_AXIS_8)
#define LEN_GEAR1				sizeof(MachineStatus.GEAR1[0])
//config59
#define FLOC_SensorHighLow	(FLOC_GEAR1+LEN_GEAR1*MAX_AXIS_8)
#define LEN_SensorHighLow		sizeof(MachineStatus.SensorHighLow[0])
//config60
#define FLOC_nMotorType	(FLOC_SensorHighLow+LEN_SensorHighLow*MAX_AXIS_8)
#define LEN_nMotorType	sizeof(MachineStatus.nMotorType[0])
//config61
#define FLOC_AxisNo	(FLOC_nMotorType+LEN_nMotorType*MAX_AXIS_8)
#define LEN_AxisNo	sizeof(MachineStatus.AxisNo)
//config62
#define FLOC_PassYear		FLOC_AxisNo+LEN_AxisNo
#define LEN_PassYear		(sizeof(MachineStatus.PassYear))
#define FLOC_PassMon		FLOC_PassYear+LEN_PassYear
#define LEN_PassMon			(sizeof(MachineStatus.PassMon))
#define FLOC_PassDay		FLOC_PassMon+LEN_PassMon
#define LEN_PassDay			(sizeof(MachineStatus.PassDay))
#define FLOC_NSN				(FLOC_PassDay+LEN_PassDay)
#define LEN_NSN					sizeof(MachineStatus.NSN)
#define FLOC_EnPassWd		(FLOC_NSN+LEN_NSN)
#define LEN_EnPassWd		(sizeof(MachineStatus.EnPassWd))
#define FLOC_PRODPASS		(FLOC_EnPassWd+LEN_EnPassWd)
#define LEN_PRODPASS		(sizeof(MachineStatus.PRODPASS))





//config63
#define FLOC_ChkToPos		(FLOC_PRODPASS+LEN_PRODPASS)
#define LEN_ChkToPos		(sizeof(MachineStatus.ChkToPos[0]))
//config64
#define FLOC_G2Mode		(FLOC_ChkToPos+LEN_ChkToPos*MAX_AXIS_8)
#define LEN_G2Mode			(sizeof(MachineStatus.G2Mode))
//config65
#define FLOC_SPDMode		(FLOC_G2Mode+LEN_G2Mode)
#define LEN_SPDMode			(sizeof(MachineStatus.SPDMode))
//config66
#define FLOC_IDMS		(FLOC_SPDMode+LEN_SPDMode)
#define LEN_IDMS		(sizeof(MachineStatus.IDMS[0]))
//config67
#define FLOC_CusRate				(FLOC_IDMS+LEN_IDMS*MAX_AXIS_8)
#define LEN_CusRate					sizeof(MachineStatus.CusRate[0])
//config68
#define FLOC_PRODDELAY		(FLOC_CusRate+LEN_CusRate*MAX_AXIS_8)
#define LEN_PRODDELAY		(sizeof(MachineStatus.PRODDELAY))
//config69
#define FLOC_XMINUS		(FLOC_PRODDELAY+LEN_PRODDELAY)
#define LEN_XMINUS		(sizeof(MachineStatus.XMINUS))
//config70
#define FLOC_KEYLOCK		(FLOC_XMINUS+LEN_XMINUS)
#define LEN_KEYLOCK		(sizeof(MachineStatus.KEYLOCK))

//config71
#define FLOC_FileRate		(FLOC_KEYLOCK+LEN_KEYLOCK+200)
#define LEN_FileRate		(sizeof(MachineStatus.FileRate[0]))

//config72
#define FLOC_Touch_rate		(FLOC_FileRate+LEN_FileRate+250)
#define LEN_Touch_rate		(sizeof(MachineStatus.Touch_rate))

//config73
#define FLOC_FileFastRate		(FLOC_Touch_rate+LEN_Touch_rate)
#define LEN_FileFastRate		(sizeof(MachineStatus.FileFastRate[0]))

//config74
#define FLOC_SlideLimit		(FLOC_Touch_rate+LEN_Touch_rate+250)
#define LEN_SlideLimit		(sizeof(MachineStatus.SlideLimit))

//config75
#define FLOC_AirOff		(FLOC_SlideLimit+LEN_SlideLimit)
#define LEN_AirOff		(sizeof(MachineStatus.AirOff))

//config76
#define FLOC_WireTime		(FLOC_AirOff+LEN_AirOff)
#define LEN_WireTime		(sizeof(MachineStatus.WireTime))

//config77
#define FLOC_OilChk		(FLOC_WireTime+LEN_WireTime)
#define LEN_OilChk		(sizeof(MachineStatus.OilChk))



