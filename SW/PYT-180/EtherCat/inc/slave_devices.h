/******************************************************************************
 *	File	:	slave_devices.h
 *	Version :	1.00
 *	Date	:	2022/03/29
 *	Author	:	chan-fa
 *
 * @copyright (C) 
 *
 ******************************************************************************/
#ifndef _SLAVE_DEVICES_H_
#define _SLAVE_DEVICES_H_

#include "ec_master.h"


#define	ECM_DEVICE_NONE			0x00
#define	ECM_DEVICE_COUPLER		0x01
#define	ECM_DEVICE_DIN			0x02	// Slave to Master
#define	ECM_DEVICE_DOUT			0x03	// Master to Slave
#define	ECM_DEVICE_AIN			0x04	// Slave to Master
#define	ECM_DEVICE_AOUT			0x05	// Master to Slave
#define	ECM_DEVICE_AC_SERVO_IN	0x06	// Slave to Master
#define	ECM_DEVICE_AC_SERVO_OUT	0x07	// Master to Slave

#define ECM_SERVER_OP_MODE_CSP  		(EC_OP_CSP<<8)

#define ECM_RXPDO_TXPDO_REG_NONE    	(0x00<<16)
#define ECM_RXPOD_REG_CTLWORD			(0x01<<16)
#define ECM_RXPDO_REG_TOUCH_PROBE_MODE 	(0x02<<16)
#define ECM_RXPDO_REG_TARGET_POS 		(0x03<<16)
	
#define ECM_TXPDO_REG_STATUSWORD 		(0x80<<16)	
#define ECM_TXPDO_REG_ACTUAL_POS 		(0x81<<16)	
#define ECM_TXPDO_REG_ACTUAL_TORQUE 	(0x82<<16)	
#define ECM_TXPDO_REG_ERROR_CODE 		(0x83<<16)	
#define ECM_TXPDO_REG_TOUCH_PROBE_STATE (0x84<<16)
#define ECM_TXPDO_REG_TOUCH_PROBE_1_POSITIVE_EDGE (0x85<<16)
#define ECM_TXPDO_REG_TOUCH_PROBE_2_POSITIVE_EDGE (0x86<<16)
#define ECM_TXPDO_REG_FOLLOWING_ERROR_ACTUAL_VALUE (0x87<<16)	
#define ECM_TXPDO_REG_TARGET_POS        (0x88<<16)

#define ECM_DEVICE_TYPE(attr) (attr&0xff)
#define ISDEVICEEND(attr) (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_NONE)
#define ISCOUPLER(attr)   (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_COUPLER)
#define ISDATAIN(attr) 	  (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_DIN)
#define ISDATAOUT(attr)   (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_DOUT)
#define ISANALOGIN(attr)  (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_AIN)
#define ISANALOGOUT(attr) (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_AOUT)

#define IsServerIn(attr)  (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_AC_SERVO_IN)
#define IsServerOut(attr) (ECM_DEVICE_TYPE(attr) == ECM_DEVICE_AC_SERVO_OUT)

#define SERVERREGIDX(attr) ((attr>>16)&0xff)

typedef struct st_device_type_count
{
	// output : master to slave
	// input  : slave to master
	uint8_t u8Coupler;
	uint8_t u8DIn;
	uint8_t u8DOut;	
	uint8_t u8AIn;
	uint8_t u8AOut;
	uint8_t u8ServerIn;
	uint8_t u8ServerOut;
	
	uint8_t u8FirstServerIndex;
	uint8_t u8ServerCnt;
	uint8_t u8AllIn;
	uint8_t u8AllOut;
} DEVICE_TYPE_COUNT_T;


typedef struct st_slave_pdo_index{
	uint32_t    u32Data;
	
	/*
	 * Mask for DIn/DOut/AIn/AOut, 
	 * index for server
	 */
	uint32_t    u32Mask;		
} SLAVE_PDO_INDEX_T;

typedef struct st_servo_parameters {
	uint32_t	u32PPR;
} SERVO_PARAMETERS_T;



typedef struct st_slave_device_table {
	uint32_t 					u32VID;
	uint32_t    				u32PID;
	const ST_SLAVE_OBJECT_INFO_T*pstObjectInfo;	
} SLAVE_DEVICE_TABLE_T;



typedef struct st_slave_info{
	uint8_t  			  u8Counts;
	SLAVE_DEVICE_TABLE_T **pstSlaveDevice;
} ST_SLAVE_INFO;

int ec_slave_probe (int nSlaveCnt, uint32_t u32CanOpenOpMode, EC_MASTER_T *pstECMMaster);


#endif	// #ifndef _COMPILER_H_
