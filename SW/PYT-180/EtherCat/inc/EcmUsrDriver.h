/******************************************************************************
 *	File	:	EcmUsrDriver.h
 *	Version :	1.52
 *	Date	:	2021/11/23
 *	Author	:	XFORCE
 *
 *	ECM-XF basic driver example - Header file
 *
 *	Demonstrate how to implement API type user driver
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/

#ifndef _ECM_USR_DRV_H_
#define _ECM_USR_DRV_H_

#include <stdio.h>
#include <string.h>
#include "EcmDriver.h"

#ifdef ECMXFUSBDRV_EXPORTS
#define ECM_DLL_SYMBOL
#else
#define ECM_DLL_SYMBOL
#endif
#define ECM_DLL_FUNCTYPE

/*
 *
 * Example
 * 36MHz
 * 112 bytes data
 * 32 bytes header
 * (112+32)*8/24 = 32us
 * 32us + 50us = 82us(SPI communication time)
 *
 * NOTE:
 * if(SPI communication time > ECAT Cycle time)
 * Send more than one PDO in one SPI datagram
 *
 * */
#define TEST_SPI_DATA_SIZE		112
#define TEST_SPI_IDLE_TIME		150    // org 150
#define TEST_SPI_CRC_TYPE		ECM_CRC_TYPE_NONE //ECM_CRC_TYPE_NONE


#ifdef __cplusplus
extern "C"
{
#endif
#define CIA402_SW_STATE_MASK						0x6F
#define CIA402_SW_NOTREADYTOSWITCHON				0x00
#define CIA402_SW_SWITCHEDONDISABLED				0x40
#define CIA402_SW_READYTOSWITCHON					0x21
#define CIA402_SW_SWITCHEDON						0x23
#define CIA402_SW_OPERATIONENABLED					0x27
#define CIA402_SW_QUICKSTOPACTIVE					0x07
#define CIA402_SW_FAULTREACTIONACTIVE				0x0F
#define CIA402_SW_FAULT								0x08
typedef struct ECM_PACK spi_cmd_package_t{
	SPI_CMD_HEADER	Head;
	uint8_t			Data[TEST_SPI_DATA_SIZE];
	uint32_t		Crc;
	uint32_t		StopWord;
} SPI_CMD_PACKAGE_T;
typedef struct ECM_PACK spi_ret_package_t{
	SPI_RET_HEADER	Head;
	uint8_t			Data[TEST_SPI_DATA_SIZE];
	uint32_t		Crc;
	uint32_t		StopWord;
} SPI_RET_PACKAGE_T;
int32_t EcmUniversalCmd(	uint8_t u8Cmd, \
				uint8_t u8Param, \
				uint8_t u8Param0, \
				uint8_t u8Param1, \
				uint8_t u8Param2, \
				uint8_t u8Param3, \
				uint8_t *pu8Return, \
				uint8_t *pu8Status, \
				uint8_t *pu8ErrStatus, \
				uint16_t *pu16ReturnDataSize, \
				uint8_t *pu8ReturnData);
int32_t ECM_WaitAsyncDone(int32_t nMS);
int32_t ECM_IsAsyncBusy(void);
int32_t SpiDataExchange(uint8_t *RetIdx, uint8_t *RetCmd);
int32_t ECM_GetFirmwareVersion(uint8_t *pVersion);
int32_t ECM_CheckDCStable(void);
int32_t ECM_IsSlaveAlive(uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt);
int32_t ECM_ClearErrorStatus(int nClear, uint8_t *pEcmErrorStatus, uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt);
int32_t ECM_InfoUpdate(uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt);
int32_t ECM_EcatInit(uint16_t DCActCode, uint32_t CycTime);
int32_t ECM_GetRetStatus(uint8_t *pStatus);
int32_t ECM_GetRetErrStatus(uint8_t *pErrStatus);
uint8_t ECM_InitLibrary(uint16_t *pu16SpiDataSize);
void ECM_CloseLibrary(void);
int32_t  ECM_EcatConfigDC(void);
int32_t ECM_EcatSetDCSync(uint8_t u8SlvIdx, uint16_t DCActCode, uint32_t CycTime);
int32_t ECM_EcatReconfig(void);
int8_t ECM_EcatSlvCntGet(void);
int32_t ECM_EcatStateSet(uint8_t u8Slave, uint8_t u8State);
int32_t ECM_EcatStateUpdate(void);
int32_t ECM_EcatStateGet(uint8_t u8Slave, uint8_t *pu8State);
int32_t ECM_EcatPdoConfigSet( uint8_t Slave, PDO_CONFIG_HEAD *pConfigData);
int32_t ECM_EcatPdoConfigReq(uint8_t Slave, uint16_t SmaIdx);
int32_t ECM_EcatPdoConfigGet(PDO_CONFIG_HEAD *pBuf);
int32_t ECM_EcatSdoReq(uint8_t OP, uint8_t Slave, uint16_t Index, uint8_t SubIndex, uint16_t size, int32_t Timeout, uint8_t *Data);
int32_t ECM_EcatSdoCAReq(uint8_t OP, uint8_t Slave, uint16_t Index, uint8_t SubIndex, uint16_t size, int32_t Timeout, uint8_t *Data);
int32_t ECM_EcatSdoGet(uint8_t *pBuf);
int32_t ECM_EcatSdoWrite(uint8_t Slave,  uint16_t Index,  uint8_t SubIndex,  uint16_t size,  int32_t Timeout,  uint8_t *Data);
int32_t ECM_EcatSdoRead(uint8_t Slave, uint16_t Index, uint8_t SubIndex, uint16_t size, int32_t Timeout, uint8_t *Data);
int32_t ECM_Drv402SM_AdvConfig(uint8_t TblIdx, uint8_t SlvIdx, uint8_t ContrlWordOffset, uint8_t StateWordOffset);
int32_t ECM_Drv402SM_Enable(uint8_t TblIdx, uint8_t SlvIdx);
int32_t ECM_Drv402SM_Disable(uint8_t TblIdx, uint8_t SlvIdx);
int32_t ECM_Drv402SM_StateSet(uint8_t TblIdx, uint8_t State);
int32_t ECM_Drv402SM_StateGet(uint8_t TblIdx, uint8_t *pState);
int32_t ECM_Drv402SM_StateCheck(uint8_t TblIdx, uint8_t ExceptState, int32_t TimeOutMS);
int32_t ECM_FifoRxPdoSizeGet(void);
int32_t ECM_FifoTxPdoSizeGet(void);

uint8_t ECM_EcatPdoDataExchange(uint8_t u8OP, uint8_t *pRxData, uint8_t *pTxData, uint16_t *pu16DataSize);
int32_t ECM_EcatPdoFifoDataExchange(uint8_t u8FifoThreshold, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt);
int32_t ECM_EcatPdoFifoDataExchangeAdv(uint8_t u8Op, uint8_t u8Cnt, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pu8RxPdoFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt, uint8_t *IsSlvAlive);
int32_t ECM_EcatPdoFifoIsFull(uint8_t u8FifoThreshold);
int32_t ECM_EcatEepromReq(uint16_t OP, uint16_t slave, uint16_t eeproma, uint16_t data, uint32_t timeout);
int32_t ECM_EcatEepromGet(uint64_t *pu64Data);
int32_t ECM_GetPDOConfig(int32_t Slave, int32_t SmaIdx, PDO_CONFIG_HEAD *pPdoConfigBuf);
//int32_t ECM_ShowPDOConfig(int32_t Slave, int32_t SmaIdx);
int32_t ECM_ShowPDOConfig(int32_t Slave, int32_t SmaIdx);
int32_t ECM_StateCheck(uint8_t u8Slave, uint8_t u8ExpectState, int32_t TimeOutMS);
int32_t ECM_EcatDatagramReq(
        ecm_datagram_commad_t cmd,
		uint16_t position,
		uint16_t offset,
		uint32_t logicalAddress,
		uint16_t length,
		int32_t Timeout,
		uint8_t *Data);
int32_t ECM_EcatDatagramGet(uint8_t *pBuf);
int32_t ECM_SlaveInfoGet(uint8_t slave, uint8_t info, uint8_t *pBuf);

int32_t ECM_SetTxFIFOCnt(uint8_t u8TxCnt);
int32_t ECM_SetRxFIFOCnt(uint8_t u8RxCnt);
int32_t ECM_GetTxFIFOCnt(uint8_t *pu8Cnt);
int32_t ECM_GetRxFIFOCnt(uint8_t *pu8Cnt);

int32_t ECM_ClearFIFO(uint8_t u8TxRx);
int32_t ECM_EnableFIFO(uint8_t u8Enable);
int32_t ECM_InitFIFO(void);
int32_t ECM_SetSpiDataSize(uint16_t u16SpiDataSize);
int32_t ECM_GetSpiDataSize(uint16_t *pu16SpiDataSize);

int32_t EcmSpiPackSizeCal(int32_t nSizeLimit);

int32_t ECM_EcatRawCmdReq(uint16_t OP,  \
		uint16_t length, \
		uint16_t ADP, \
		uint16_t ADO, \
		uint32_t LogAdr, \
		int32_t timeout, \
		uint8_t *data);
uint16_t ECM_EcatRawCmdGet(uint8_t *pBuf);
uint16_t ECM_EcatRawCmdRead(uint16_t OP,  \
		uint16_t length, \
		uint16_t ADP, \
		uint16_t ADO, \
		uint32_t LogAdr, \
		int32_t timeout, \
		uint8_t *data);
int32_t ECM_EcatWkcErrorMaxSet(uint8_t u8Max);
int32_t ECM_EcatWkcErrorMaxGet(uint8_t *pu8Max);
int32_t ECM_GetLogTime(uint8_t u8Timer, uint8_t u8Idx, uint8_t u8Type);
int32_t ECM_ShowReturnField(void);
int32_t ECM_ShowCmdField(void);
//int32_t ECM_EcatSdoSetPdoConfig(uint8_t Slave, PDO_CONFIG_HEAD *pConfigData);
int32_t ECM_EcatSdoSetPdoConfig(PDO_CONFIG_HEAD *pConfigData);
int32_t ECM_EcatConfigMap(void);
int32_t ECM_EcatConfigSM(uint8_t slave, uint8_t nSM, uint16_t StartAddr, uint16_t SMlength, uint8_t ControlReg, uint8_t Activate);
int32_t ECM_EcatConfigFMMU(uint8_t slave, uint8_t FMMU0func, uint8_t FMMU1func, uint8_t FMMU2func, uint8_t FMMU3func);
int32_t ECM_Reset(void);
int32_t ECM_SkipNetInit(void);
int32_t ECM_ResetPhy(void);
int32_t ECM_ManualEmacInit(void);
int32_t ECM_ForceClearAsyncBusy(void);
/*
 * u32CompIntEnable : Complex interrupt
 * 		BIT31	:	EtherCAT package receive
 * 		BIT25	:	RxFIFO Low threshold
 *		BIT24	:	TxFIFO High threshold
 *		BIT23	:	CRC	error
 *		BIT22	:	EtherCAT working counter error
 * u8GpioIntEnable : GPIO0~7 input interrupt
 * 		BIT0	:	GPIO00 INT 		( marco : ECM_HEAD_INTFALG_GPIO00 )
 * 		BIT1	:	GPIO01 INT 		( marco : ECM_HEAD_INTFALG_GPIO01 )
 * 		BIT2	:	GPIO02 INT 		( marco : ECM_HEAD_INTFALG_GPIO02 )
 * 		BIT3	:	GPIO03 INT 		( marco : ECM_HEAD_INTFALG_GPIO03 )
 * 		BIT4	:	GPIO04 INT 		( marco : ECM_HEAD_INTFALG_GPIO04 )
 * 		BIT5	:	GPIO05 INT 		( marco : ECM_HEAD_INTFALG_GPIO05 )
 * 		BIT6	:	GPIO06 INT 		( marco : ECM_HEAD_INTFALG_GPIO06 )
 * 		BIT7	:	GPIO07 INT 		( marco : ECM_HEAD_INTFALG_GPIO07 )
 * u8PeripIntEnable : GPIO8~11 & QEI interrupt
 * 		BIT0	:	GPIO08 INT 		( marco : ECM_HEAD_INTFALG_GPIO08 )
 * 		BIT1	:	GPIO09 INT 		( marco : ECM_HEAD_INTFALG_GPIO09 )
 * 		BIT2	:	GPIO10 INT 		( marco : ECM_HEAD_INTFALG_GPIO10 )
 * 		BIT3	:	GPIO11 INT 		( marco : ECM_HEAD_INTFALG_GPIO11 )
 * 		BIT4	:	QEI	index INT 	( marco : ECM_HEAD_INTFALG_QEI_IDX )
 * 		BIT5	:	QEI	compare INT ( marco : ECM_HEAD_INTFALG_QEI_CMP )
 * 		BIT6	:	QEI	Over/Under flow INT ( marco : ECM_HEAD_INTFALG_QEI_OUF )
 * 		BIT7	:	QEI	direction change INT ( marco : ECM_HEAD_INTFALG_QEI_DIR )
 * u8INTActiveHigh : INT0/INT1 interrupt signal polar
 * 		BIT0	:	INT0 signal polar	(0 for Active low, others vice versa)
 * 		BIT1	:	INT1 signal polar	(0 for Active low, others vice versa)
 * ECM-XF Interrupt user note :
 * 			Use the u32CompIntClr filed and u8GpioIntClr field of command header to CLEAR interrupt flags.
 * 			Use the u32CompIntFlag field and u8GpioIntFlag field of command header to GET interrupt flags.
 * */
int32_t ECM_SetEcatIntEnable(uint32_t u32CompIntEnable, uint8_t u8GpioIntEnable, uint8_t u8PeripIntEnable, uint8_t u8INTActiveHigh);
int32_t ECM_GetEcatIntEnable(uint32_t *pu32CompIntEnable, uint8_t *pu8GpioIntEnable, uint8_t *pu8PeripIntEnable, uint8_t *pu8INTActiveHigh);

int32_t ECM_RtaInit(uint8_t u8RuleCnt, uint8_t u8BufSize);
void ECM_RtaClose(void);
void ECM_RtaSetEnable(uint8_t u8Enable);
int32_t ECM_RtaGetRunFlag(uint8_t *pu8RtaRuning);
int32_t ECM_RtaSetBuf(uint8_t u8Offset, uint8_t u8Size, uint8_t *pBuf);
int32_t ECM_RtaGetBuf(uint8_t u8Offset, uint8_t u8Size, uint8_t *pBuf, uint8_t *pCondition);
int32_t ECM_RtaSetRule(uint8_t u8Idx, uint8_t u8Cnt, RTA_RULE *pRule);

int ECM_GetNetLinkPin(int *pPinStatus);
int ECM_SetSpiTransIdleTime(int TimeUS);
int ECM_GetSpiTransIdleTime(int TimeUS);

#define SPI_CRC_ERROR_CONTI_MAX	10

extern uint8_t u8TxBuf[PKG_MAX_SIZE];
extern uint8_t u8RxBuf[PKG_MAX_SIZE];
extern uint8_t g_u8RxPDO[PKG_MAX_SIZE];
extern SPI_RET_PACKAGE_T *pRet;
extern SPI_CMD_PACKAGE_T *g_pFifoCmd ;

extern uint8_t g_u8CrcType;
extern uint8_t g_u8CrcErrConti;
extern uint8_t g_u8EcmStatus;
extern uint8_t g_u8RxPDOFifoCnt;
extern uint8_t g_u8TxPDOFifoCnt;
extern uint8_t g_u8CrcErrCnt;
extern uint8_t g_u8WkcErrCnt;

#ifdef __cplusplus
}
#endif

#endif
