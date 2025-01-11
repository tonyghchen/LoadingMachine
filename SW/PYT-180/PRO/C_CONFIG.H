#define FLOC_SET_QUAN		0
#define LEN_SET_QUAN		sizeof(MachineStatus.set_quan)

#define FLOC_SPEED			(FLOC_SET_QUAN+LEN_SET_QUAN)
#define LEN_SPEED			sizeof(MachineStatus.speed[0])

#define FLOC_MAN_GAIN		(FLOC_SPEED+LEN_SPEED*2)
#define LEN_MAN_GAIN		sizeof(MachineStatus.man_gain)

#define FLOC_POS_ZONE		(FLOC_MAN_GAIN+LEN_MAN_GAIN)
#define LEN_POS_ZONE		sizeof(MachineStatus.pos_zone)

#define FLOC_CNT8254		(FLOC_POS_ZONE+LEN_POS_ZONE)
#define LEN_CNT8254 		sizeof(MachineStatus.cnt8254)

//各軸:6+D/8
#define FLOC_MANVAL 		(FLOC_CNT8254+LEN_CNT8254)
#define LEN_MANVAL			sizeof(MachineStatus.manval[0])

//各軸:6+D/8
#define FLOC_MOTOR_GRADS	(FLOC_MANVAL+LEN_MANVAL*MAX_PROG_AXIS)
#define LEN_MOTOR_GRADS 	sizeof(MachineStatus.motor_grads[0])

//各軸:6+D/8
#define FLOC_RATE			(FLOC_MOTOR_GRADS+LEN_MOTOR_GRADS*MAX_PROG_AXIS)
#define LEN_RATE			sizeof(MachineStatus.Rate[0])

//各軸:6+D/8
#define FLOC_HOME_SEQ		(FLOC_RATE+LEN_RATE*MAX_PROG_AXIS)
#define LEN_HOME_SEQ		(sizeof(MachineStatus.home_seq[0])+sizeof(MachineStatus.home_seq_sign[0]))

#define FLOC_FILE			(FLOC_HOME_SEQ+LEN_HOME_SEQ*MAX_PROG_AXIS)
#define LEN_FILE			sizeof(MachineStatus.file)

#define FLOC_LANGUAGE		(FLOC_FILE+LEN_FILE)
#define LEN_LANGUAGE		sizeof(MachineStatus.language)

#define FLOC_SPEED_MODE 	(FLOC_LANGUAGE+LEN_LANGUAGE)
#define LEN_SPEED_MODE		sizeof(MachineStatus.speed_mode)

#define FLOC_SET_MISS		(FLOC_SPEED_MODE+LEN_SPEED_MODE)
#define LEN_SET_MISS		sizeof(MachineStatus.set_miss)

#define FLOC_G2_COMB		(FLOC_SET_MISS+LEN_SET_MISS)
#define LEN_G2_COMB 		sizeof(MachineStatus.g2comb)

//各軸:4+D/6:XY沒
#define FLOC_MOTORZABCSW	(FLOC_G2_COMB+LEN_G2_COMB)
#define LEN_MOTORZABCSW 	sizeof(MachineStatus.motor[0])

#define FLOC_REPAIR_SPD		(FLOC_MOTORZABCSW+LEN_MOTORZABCSW*(MAX_PROG_AXIS-2))
#define LEN_REPAIR_SPD		sizeof(MachineStatus.repair_spd)

#define FLOC_REPAIR_DST		(FLOC_REPAIR_SPD+LEN_REPAIR_SPD)
#define LEN_REPAIR_DST 		sizeof(MachineStatus.repair_dst)

#define FLOC_XGRID_DEG		(FLOC_REPAIR_DST+LEN_REPAIR_DST)
#define LEN_XGRID_DEG		sizeof(MachineStatus.xgrid_deg)

#define FLOC_GAIN_VAL		(FLOC_XGRID_DEG+LEN_XGRID_DEG)
#define LEN_GAIN_VAL		sizeof(MachineStatus.gain_val)

#define FLOC_FAST			(FLOC_GAIN_VAL+LEN_GAIN_VAL)
#define LEN_FAST			sizeof(MachineStatus.FAST)

#define FLOC_Y0				(FLOC_FAST+LEN_FAST)
#define LEN_Y0				sizeof(MachineStatus.Y0)

#define FLOC_Y1  			(FLOC_Y0+LEN_Y0)
#define LEN_Y1				sizeof(MachineStatus.Y1)

#define FLOC_SAFETY_DOOR	(FLOC_Y1+LEN_Y1)
#define LEN_SAFETY_DOOR		sizeof(MachineStatus.safety_door)

#define FLOC_TIMER  		(FLOC_SAFETY_DOOR+LEN_SAFETY_DOOR)
#define LEN_TIMER 			sizeof(MachineStatus.TIMER)

#define FLOC_DEC_DIST		(FLOC_TIMER+LEN_TIMER)
#define LEN_DEC_DIST		sizeof(MachineStatus.dec_dist)

#define FLOC_BUZZER			(FLOC_DEC_DIST+LEN_DEC_DIST)
#define LEN_BUZZER			sizeof(MachineStatus.BUZZER)

#define FLOC_BATCH			(FLOC_BUZZER+LEN_BUZZER)
#define LEN_BATCH 			sizeof(MachineStatus.BATCH)

#define FLOC_FLAG_VIRTUAL	(FLOC_BATCH+LEN_BATCH)
#define LEN_FLAG_VIRTUAL	sizeof(MachineStatus.flag_virtual)

#define FLOC_Type			(FLOC_FLAG_VIRTUAL+LEN_FLAG_VIRTUAL)
#define LEN_Type			sizeof(MachineStatus.Type)

// Delay 移做新達新科logo的選擇
#define FLOC_DELAY			(FLOC_Type+LEN_Type)
#define LEN_DELAY			sizeof(MachineStatus.Delay)

#define FLOC_SCRNSAV		(FLOC_DELAY+LEN_DELAY)
#define LEN_SCRNSAV			sizeof(MachineStatus.ScrnSav)

//config1
//各軸:6+D/8
#define FLOC_ZEROSPD		(FLOC_SCRNSAV+LEN_SCRNSAV)
#define LEN_ZEROSPD			sizeof(MachineStatus.wZeroSpd[0])
//各軸:6/8
#define FLOC_ZRTMODE		(FLOC_ZEROSPD+LEN_ZEROSPD*MAX_PROG_AXIS)
#define LEN_ZRTMODE			sizeof(MachineStatus.ZrtMode[0])
#define FLOC_Y_SUSPEND		(FLOC_ZRTMODE+LEN_ZRTMODE*MAX_PROG_AXIS)
#define LEN_Y_SUSPEND		sizeof(MachineStatus.y_suspend)
#define FLOC_SAFE_SW		(FLOC_Y_SUSPEND+LEN_Y_SUSPEND)
#define LEN_SAFE_SW			sizeof(MachineStatus.safe_sw)
//各軸:6/8
#define FLOC_UNIT			(FLOC_SAFE_SW+LEN_SAFE_SW)
#define LEN_UNIT			sizeof(MachineStatus.Unit[0])

//config2
#define FLOC_AHome			(FLOC_UNIT+LEN_UNIT*MAX_PROG_AXIS)
#define LEN_AHome			(sizeof(MachineStatus.AHome)+sizeof(MachineStatus.AHome_sign))
//config3
#define FLOC_SN  			(FLOC_AHome+LEN_AHome)
#define LEN_SN 				8

//config4
//各軸:6/8
#define FLOC_AXISDELAY 		(FLOC_SN+LEN_SN)
#define LEN_AXISDELAY 		sizeof(MachineStatus.AxisDelay[0])

//config5
//各軸:6/8
#define FLOC_ZRTSET			(FLOC_AXISDELAY+LEN_AXISDELAY*MAX_PROG_AXIS)
#define LEN_ZRTSET			(sizeof(MachineStatus.ZRTSET[0])+sizeof(MachineStatus.ZRTSET_sign[0]))
//config6
#define FLOC_NEAR  			(FLOC_ZRTSET+LEN_ZRTSET*MAX_PROG_AXIS)
#define LEN_NEAR   			sizeof(MachineStatus.NEAR)
#define FLOC_YGAP  			(FLOC_NEAR+LEN_NEAR)
#define LEN_YGAP   			sizeof(MachineStatus.YGAP)
//config7
#define FLOC_AGAP  			(FLOC_YGAP+LEN_YGAP)
#define LEN_AGAP   			sizeof(MachineStatus.AGAP)
#define FLOC_TOUCH_Y_NEAR	(FLOC_AGAP+LEN_AGAP)
#define LEN_TOUCH_Y_NEAR	sizeof(MachineStatus.TOUCH_Y_NEAR)
//config8
#define FLOC_HOME_SEQ_D		(FLOC_TOUCH_Y_NEAR+LEN_TOUCH_Y_NEAR)
#define LEN_HOME_SEQ_D		(sizeof(MachineStatus.home_seq[AXIS_D])+sizeof(MachineStatus.home_seq_sign[AXIS_D]))
#define FLOC_ZEROSPD_D		(FLOC_HOME_SEQ_D+LEN_HOME_SEQ_D)
#define LEN_ZEROSPD_D		sizeof(MachineStatus.wZeroSpd[AXIS_D])
#define FLOC_MANVAL_D 		(FLOC_ZEROSPD_D+LEN_ZEROSPD_D)
#define LEN_MANVAL_D		sizeof(MachineStatus.manval[AXIS_D])
#define FLOC_MOTORZABCSW_D	(FLOC_MANVAL_D+LEN_MANVAL_D)
#define LEN_MOTORZABCSW_D 	sizeof(MachineStatus.motor[AXIS_D])
#define FLOC_RATE_D			(FLOC_MOTORZABCSW_D+LEN_MOTORZABCSW_D)
#define LEN_RATE_D			sizeof(MachineStatus.Rate[AXIS_D])

