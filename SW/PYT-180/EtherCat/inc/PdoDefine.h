/******************************************************************************
 *	File	:	PdoDefine.h
 *	Version :	1.47
 *	Date	:	2021/05/06
 *	Author	:	XFORCE
 *
 *
 *	Define slave device PDO data structure
 *
 *	You can configure the PDO structure you wanted,
 *	or you can just use the default PDO structure.
 *	No matter what, the example program need to know.
 *
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/
#ifndef _ECM_USR_PDO_DEFINE_H_
#define _ECM_USR_PDO_DEFINE_H_

#include "app_config.h"


//#define TEST_HSP_DEV	1
#define ECM402_ENABLE	1
//

#define N_AXIS_IN_ONE_DRV		1

#define TEST_DRV_CNT			APP_DRV_CNT
#define TEST_IO_CNT				1
#define TEST_SLV_CNT			(TEST_DRV_CNT+TEST_IO_CNT)
#define TEST_AXIS_CNT			(N_AXIS_IN_ONE_DRV*TEST_DRV_CNT)

#define TEST_CTL_WORD_OFFSET	0
#define TEST_STA_WORD_OFFSET	0

typedef struct ECM_PACK _axis_rxpdo_st_def_t
{
#if (APP_USE_DELTA_DRIVER == 1)
	uint16_t	u16CtlWord;		//	0x6x40 - Control word
	int32_t		n32Target;		//	0x6x7A - Target position	
#else	
#if 1
	uint16_t	u16CtlWord;								//	0x6x40 - Control word
	int32_t		n32Target;								//	0x6x7A - Target position	
#else	
	uint16_t	u16CtlWord;								//	0x6x40 - Control word
	int32_t		n32Target;								//	0x6x7A - Target position

		uint32_t		u32ProfileVelocity;			//	0x6x81 - Target position
		uint32_t		u32ProfileAcceleration;	//	0x6x83 - Profile velocity
		uint32_t		u32ProfileDeceleration;	//	0x6x84 - Profile acceleration
		int32_t		n32TargetVelocity;			//	0x6xFF - Profile deceleration
		int16_t		n16TargetTorque;				//	0x6x71 - Target velocity
		int16_t		n16TouchProbeFunction;	//	0x6xb8 - Touch probe function
		uint32_t	u32DigitalOutputs;			//	0x6xFE - Digital outputsn
#endif	
#endif		
}AXIS_RXPDO_ST_DEF_T;
typedef struct ECM_PACK _axis_txpdo_st_def_t
{
#if (APP_USE_DELTA_DRIVER == 1)	
	uint16_t	u16StaWord;		//	0x6x41 - Status word
	int32_t		n32Actual;		//	0x6x64 - Actual position	
#else	
	
#if 1
	uint16_t	u16StaWord;								//	0x6x41 - Status word
	int32_t		n32Actual;								//	0x6x64 - Actual position	
#else	
	uint16_t	u16StaWord;								//	0x6x41 - Status word
	uint16_t	u16StaWord1;							//	0x2100 - Status word 1
	int32_t		n32Actual;								//	0x6x64 - Actual position
	
		int32_t		n32VelocityActual1;			//	0x6x6c - Velocity actual value
		int16_t		n16TorqueActual;				//	0x6x77 - Torque actual value
		int32_t		n32FollowingError;			//	0x6xF4 - Following error
		int16_t		u16TouchProbeStatus;		//	0x6xb9 - Touch probe status
		int32_t		n32TouchProbePos1PositiveValue;		//	0x6xba - Touch probe position 1 positive value
		int32_t		n32TouchProbePosNegativeValue;		//	0x6xbb - Touch probe position 1 negative value
		uint32_t	u32DigitalInput;				//	0x6xfd - Digital input
		uint8_t		u8ErrorRegister;				//	0x1x01 - Error register
		uint8_t		u8ModeOP;								//	0x6x61 - Modes of operation display
								//	0x6063 -
#endif	

#endif							
}AXIS_TXPDO_ST_DEF_T;

typedef struct ECM_PACK _drv_rxpdo_st_def_t
{
	AXIS_RXPDO_ST_DEF_T Axis[N_AXIS_IN_ONE_DRV];
}DRV_RXPDO_ST_DEF_T;

typedef struct ECM_PACK _drv_txpdo_st_def_t
{
	AXIS_TXPDO_ST_DEF_T Axis[N_AXIS_IN_ONE_DRV];
}DRV_TXPDO_ST_DEF_T;

typedef struct ECM_PACK _rxpdo_st_def_t
{
#if TEST_DRV_CNT != 0	
	DRV_RXPDO_ST_DEF_T Drv[TEST_DRV_CNT];
#endif	
#if defined TEST_IO_CNT && TEST_IO_CNT != 0
	uint16_t u16Output[TEST_IO_CNT];
#endif		
}RXPDO_ST_DEF_T;

typedef struct ECM_PACK _txpdo_st_def_t
{
#if TEST_DRV_CNT != 0		
	DRV_TXPDO_ST_DEF_T Drv[TEST_DRV_CNT];
#endif	
#if defined TEST_IO_CNT && TEST_IO_CNT != 0
	uint16_t u16Input[TEST_IO_CNT];
	uint32_t u32AIN[2];
#endif		

}TXPDO_ST_DEF_T;
#endif
