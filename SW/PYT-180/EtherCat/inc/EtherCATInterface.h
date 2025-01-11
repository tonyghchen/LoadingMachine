/******************************************************************************
 *	File	:	EtherCatInterface.h
 *	Version :	1.00
 *	Date	:	2022/11/20
 *	Author	:	chan-fa
 *
 * @copyright (C) 
 *
 ******************************************************************************/
#ifndef _ETHERCATINTERFACE_H
#define _ETHERCATINTERFACE_H



#include <stdint.h>

#define EC_OP_PP	1
#define EC_OP_IP	2
#define EC_OP_CSP	3


typedef void (ETHERCAT_MASTER_PDO_CB)(void);

typedef enum
{
	EC_ERR_MASTER_INIT_LIB=-12,
	EC_ERR_SLAVE_INIT=11,
	EC_ERR_SPI_SIZE_OVERFLOW=-10,
	EC_ERR_SETDCSYNC=-9,
	EC_ERR_BOUNDARY=-8,
	EC_ERR_MALLOC=-7,
	EC_ERR_SERVO_INDEX=-6,		
	EC_ERR_SLAVE_UNKNOWN=-5,
	EC_ERR_PDO_RD=-4,
	EC_ERR_PDO_WR=-3,
	EC_ERR_CMD_RD=-2,
	EC_ERR_CMD_WR=-1,
	EC_ERR_NONE=0,

} EC_ERR_TYPE;  


void * vZeroMalloc(int size);

int EtherCatGetVidPid(uint8_t u8DeviceIdx, uint32_t *pu32Vid, uint32_t *pu32Pid);

uint8_t EtherCatMasterGetDriverCnt(void);
uint8_t EtherCatMasterGetDriverStartIdx(void);
uint8_t EtherCatMasterGetDriverEndIdx(void);


int  EtherCatMasterOpen(uint32_t spi_clock, uint32_t u32CanOpenOpMode, uint32_t u32ActiveCode, uint32_t DCTimes_us, ETHERCAT_MASTER_PDO_CB callback);

int  EtherCatMasterRunning(void);
int  EtherCatMasterStop(void);

int EtherCatSlaveSdoRead(uint8_t Slave, \
		uint16_t Index, \
		uint8_t SubIndex, \
		uint16_t size, \
		uint8_t *Data);
		
int EtherCatSlaveSdoWrite (uint8_t Slave, \
		uint16_t Index, \
		uint8_t SubIndex, \
		uint16_t size, \
		uint8_t *Data);		

int EtherCatGetDevicesCnt(void);

int EtherCatGetDOutCnt(void);
int EtherCatGetDInCnt(void);
int EtherCatGetAInCnt(void);
int EtherCatGetAOutCnt(void);

int EtherCatGetDInVal(uint8_t u8Idx, uint32_t *pu32Data);
int EtherCatGetAInVal(uint8_t u8Idx, uint32_t *pu32Data);

int EtherCatSetDOutVal(uint8_t u8Idx, uint32_t u32Data);
int EtherCatSetAOutVal(uint8_t u8Idx, uint32_t u32Data);

/* Read/Write function fot Specifal registers */

int EtherCatGetCtrlWord(uint8_t u8ServerIdx, uint16_t *pu16Data);
int EtherCatGetTargetPos(uint8_t u8ServerIdx, uint32_t *pu32Data);

int EtherCatGetStatusWord(uint8_t u8ServerIdx, uint16_t *pu16Data);
int EtherCatGetActualPos(uint8_t u8ServerIdx, uint32_t *pu32Data);
int EtherCatGetActualTorque(uint8_t u8ServerIdx, uint16_t *pu16Data);
int EtherCatGetErrorCode(uint8_t u8ServerIdx, uint16_t *pu16Data);
int EtherCatGetTouchProbeState(uint8_t u8ServerIdx, uint16_t *pu16Data);
int EtherCatGetTouchProbe1Pos(uint8_t u8ServerIdx, uint32_t *pu32Data);
int EtherCatGetTouchProbe2Pos(uint8_t u8ServerIdx, uint32_t *pu32Data);
int EtherCatGetFollowingErrorActualValue(uint8_t u8ServerIdx, uint32_t *pu32Data);

int EtherCatSetCtrlWord(uint8_t u8ServerIdx, uint16_t u16Data);
int EtherCatSetTargetPos(uint8_t u8ServerIdx, uint32_t u32Data);
int EtherCatSetTouchProbeMode(uint8_t u8ServerIdx, uint16_t u16Data);

int EtherCatSetStatusWord(uint8_t u8ServerIdx, uint32_t u32Data);
int EtherCatSetActualPos(uint8_t u8ServerIdx, uint32_t u32Data);
int EtherCatSetErrorCode(uint8_t u8ServerIdx, uint32_t u32Data);


#endif	// #ifndef _ETHERCATINTERFACE_H
