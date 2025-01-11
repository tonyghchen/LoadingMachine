/******************************************************************************
 *	File	:	platform.h
 *	Version :	0.2
 *	Date	:	2020/09/03
 *	Author	:	User
 *
 *	Hardware dependency function - Header file
 *
 *	Provide necessary function for EcmUsrDriver
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/
#ifndef _ECM_PLATFORM_H_
#define _ECM_PLATFORM_H_

#include <stdio.h>
#define SPI_MASTER_TX_DMA_CH 0
#define SPI_MASTER_RX_DMA_CH 1
#ifdef __cplusplus
extern "C"
{
#endif

void UserSys_Init(uint32_t u32SpiFreq);
void UserSys_Close(void);
int UserSpiDataExchange(uint8_t *pTxBuf, uint8_t *pRxBuf, uint32_t u32PackSize);
int UserSpiDataExchangeISR(uint8_t *pTxBuf, uint8_t *pRxBuf, uint32_t u32PackSize);
int UserDelay(uint32_t MircoSec);
uint32_t UserSetCrcType(uint32_t u32CrcType);
uint32_t UserCalCrc(uint8_t *pu8Addr, uint32_t u32Size);

void SysTick_open(void);
void SysTick_enable(void);
void SysTick_disable(void);

#ifdef __cplusplus
}
#endif

#endif //_ECM_PLATFORM_H_
//	(C) COPYRIGHT 2020 NEXTW Technology Corp.
