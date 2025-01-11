/******************************************************************************
 *	File	:	ec_cmd_isr.h
 *	Version :	1.00
 *	Date	:	2022/04/30
 *	Author	:	chan-fa
 *
 * @copyright (C) 
 *
 ******************************************************************************/
#ifndef _EC_CMD_ISR_H_
#define _EC_CMD_ISR_H_


#include <stdint.h>
#include "trace_config.h"


typedef int32_t (EC_CMDRESPONSE_CALLBACK)(int nret, void *pArg1, void*pArg2, void *pArg3, void*pArg4, void *pArg5);

void EC_CmdStackReset(void);	
void EC_CmdResponsePop (void);
int  EC_CmdResponsePush(EC_CMDRESPONSE_CALLBACK pCallStack, void *pArg1, void*pArg2, void *pArg3, void*pArg4, void *pArg5);


int32_t SpiDataExchangeISR(uint8_t *RetIdx, uint8_t *RetCmd);
int32_t ECM_EcatPdoFifoDataExchangeAdvISR(uint8_t u8Op, uint8_t u8Cnt, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pu8RxPdoFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt, uint8_t *IsSlvAlive);


#endif	// #ifndef _EC_CMD_ISR_H_
