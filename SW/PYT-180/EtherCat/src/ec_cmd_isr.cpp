// -------------------------------------------------------------------------
//  File        : ec_cmd_isr.cpp
//              :
//  Library     :
//              :
//  Developer   : 
//              :
//  Purpose     : Control Functions for Request & response cmds.
//              :
//  Limitation  :
//              :
//  Note        :
//              :
// -------------------------------------------------------------------------
//  (c) Copyright 2022; 
//
//  All rights reserved.  Protected by international copyright laws.
//  Knowledge of the source code may NOT be used to develop similar product
//  Your honesty is greatly appreciated.
// -------------------------------------------------------------------------
//  Modification History :
// -------------------------------------------------------------------------
//  Version | Mdy Date : | Descriptions
//          | mm/dd/yyyy |
//  V0.00   | 04/30/2022 | First release
// -------------------------------------------------------------------------



/***************************************************************************
Include files
***************************************************************************/
#include "NuMicro.h"
#include "EcmUsrDriver.h"
#include "platform.h"
#include "Utility.h"
#include "PdoDefine.h"
#include "ec_master.h"
#include "ec_cmd_isr.h"
#include "trace_config.h"


/***************************************************************************
Constant define
***************************************************************************/
#define MAX_ECM_CALLSTACK 	5



/***************************************************************************
Function Prototype (External)
***************************************************************************/



/***************************************************************************
Function Prototype (Local)
***************************************************************************/



/***************************************************************************
Variable Define (External)
***************************************************************************/



/***************************************************************************
Variable Define (Global)
***************************************************************************/



/***************************************************************************
Variable Define (Local)
***************************************************************************/
typedef struct st_ecm_callstack_item
{
	EC_CMDRESPONSE_CALLBACK *pCallBack;
	void *pArg[5];
} ST_ECM_CALLSTACK_ITEM_T;


typedef struct st_ecm_callstack_info
{
	ST_ECM_CALLSTACK_ITEM_T stItems[MAX_ECM_CALLSTACK];
	uint8_t u8Index;
} ST_ECM_CALLSTACK_INFO_T;
static ST_ECM_CALLSTACK_INFO_T gECMCallStackInfo;


void EC_CmdStackReset(void)
{	
	gECMCallStackInfo.u8Index = 0;
}


void EC_CmdResponsePop (void)
{
	ST_ECM_CALLSTACK_ITEM_T *pItem;
	int nret=0, i ;
	//MSG_DBG("Cmd P\n");
	if (gECMCallStackInfo.u8Index == 0){
		TRACE_MSG("Cmd Pop=0\n");
	}
	for( i=gECMCallStackInfo.u8Index; i > 0; i--){
		pItem = &gECMCallStackInfo.stItems[i-1];		
		nret = pItem->pCallBack(nret, 
		                       pItem->pArg[0], pItem->pArg[1], pItem->pArg[2],
							   pItem->pArg[3], pItem->pArg[4]);
	}
	EC_CmdStackReset();
	EC_Master_ProcessCmd(1, nret);
}



/*
 * Return
 * 1	: successful.
 * <0	: error
 * */
int EC_CmdResponsePush(EC_CMDRESPONSE_CALLBACK pCallStack, void *pArg1, void*pArg2, void *pArg3, void*pArg4, void *pArg5)
{
	ST_ECM_CALLSTACK_ITEM_T *pItem;
	if (gECMCallStackInfo.u8Index >= MAX_ECM_CALLSTACK){
		TRACE_MSG("cmd push:over\n");
		return (-1);
	}

	pItem = &gECMCallStackInfo.stItems[gECMCallStackInfo.u8Index++];
	pItem->pCallBack = pCallStack;	
	pItem->pArg[0] = pArg1;
	pItem->pArg[1] = pArg2;
	pItem->pArg[2] = pArg3;
	pItem->pArg[3] = pArg4;
	pItem->pArg[4] = pArg5;
	//TRACE_MSG("p:%d\n", gECMCallStackInfo.u8Index);
	return (1);
}




/*
 * Return
 * 			-2	:	CRC continue error reach MAX
 * 			-1	:	CRC continue error reach MAX and print info
 * 			0	:	CRC error
 * 			1	:	Successful
 * */
int32_t SpiDataExchangeISRResponse(int nret, void *pretidx, void *pretcmd, void*pArg3, void*pArg4, void*pArg5)
{
	static int gu8SkipFirstCRCErr = 1;
	uint8_t *RetIdx = (uint8_t *)pretidx;
	uint8_t *RetCmd = (uint8_t *)pretcmd;
	uint32_t unCrcResult=0;
	uint8_t u8MaskErrorStatus;

	//TRACE_MSG("40");
#ifdef TEST_SPI_IDLE_TIME
	//UserDelay(TEST_SPI_IDLE_TIME);
#endif
	//TRACE_MSG("Delay:e");
	u8MaskErrorStatus = pRet->Head.u8ErrorStatus & ECM_CTL_CLR_ALL_ERR_MASK;
	if (u8MaskErrorStatus) {
		if ((u8MaskErrorStatus & ECM_CTL_CLR_CRC_ERR_MASK) && gu8SkipFirstCRCErr){
			gu8SkipFirstCRCErr = 0;
		}
		else{
			MSG_DBG("u8ErrorStatus : 0x%X, press any key\n", pRet->Head.u8ErrorStatus);
			//WAIT_KEY();
		}
	}
	if (g_u8CrcType == ECM_CRC_TYPE_32){
#ifdef ECM_VERC_CHKSUM
		unCrcResult = crc32(u8RxBuf, sizeof(SPI_RET_PACKAGE_T)-8);
#else
		//unCrcResult =  crc32(u8RxBuf, pRet->Head.u16Size+24);
		unCrcResult =  UserCalCrc(u8RxBuf, sizeof(SPI_RET_PACKAGE_T)-8);		
#endif
	}else{
		unCrcResult = ECM_CRC_MAGIC_NUM;
	}
	if(pRet->Crc == unCrcResult){
		g_u8EcmStatus = pRet->Head.u8Status;
		g_u8RxPDOFifoCnt  = pRet->Head.u8RxFifoCnt;
		g_u8TxPDOFifoCnt  = pRet->Head.u8TxFifoCnt;
		g_u8CrcErrCnt = pRet->Head.u8CrcErrCnt;
		g_u8WkcErrCnt = pRet->Head.u8WkcErrCnt;
		if(RetIdx){
			*RetIdx = pRet->Head.u8Idx;
		}
		if(RetCmd){
			*RetCmd = pRet->Head.u8Cmd;
		}
		g_u8CrcErrConti=0;
		return 1;
	}else if(pRet->Crc == ECM_CRC_INIT_NUM){
		MSG_DBG("Data not ready, maybe need more SPI idle time\n");
		nret = 0;
	}else{
		MSG_DBG("CRC error 0x%x(%d) != 0x%x(%d) size(%d)\n",pRet->Crc,pRet->Crc,unCrcResult,unCrcResult,pRet->Head.u16Size);
		nret = 0;		
	}
	// CRC Check Fail.
	g_u8CrcErrConti++;
	return nret;
}



/*
 * Return
 * 			-2	:	CRC continue error reach MAX
 * 			-1	:	CRC continue error reach MAX and print info
 * 			0	:	CRC error
 * 			1	:	Successful
 * */
int32_t SpiFiFoDataExchangeISR(uint8_t *RetIdx, uint8_t *RetCmd)
{
	int nret;
	if(g_u8CrcErrConti == SPI_CRC_ERROR_CONTI_MAX){
		MSG_DBG("g_u8CrcErrConti reached MAX(%d)\n",SPI_CRC_ERROR_CONTI_MAX);
		g_u8CrcErrConti++;
		return -1;
	}else if(g_u8CrcErrConti > SPI_CRC_ERROR_CONTI_MAX){
		return -2;
	}
	g_pFifoCmd->Head.u32StartWord = ECM_START_WORD;
	g_pFifoCmd->StopWord = ECM_STOP_WORD;
	g_pFifoCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;	
	if(g_pFifoCmd->Head.u8Cmd == ECM_CMD_CRC_TYPE_SET){
		g_pFifoCmd->Crc =  ECM_CRC_MAGIC_NUM;
	}else{
	if(g_u8CrcType == ECM_CRC_TYPE_32){
#ifdef ECM_VERC_CHKSUM
		g_pFifoCmd->Crc =  crc32(g_u8RxPDO, pCmd->Head.u16Size+24);
#else
		//pCmd->Crc =  crc32(u8TxBuf, sizeof(SPI_CMD_PACKAGE_T)-8);
		g_pFifoCmd->Crc =  UserCalCrc(g_u8RxPDO, sizeof(SPI_CMD_PACKAGE_T)-8);				
#endif
	}else{
		g_pFifoCmd->Crc =  ECM_CRC_MAGIC_NUM;
	}
	}

	EC_CmdResponsePush(SpiDataExchangeISRResponse, 
				        (void*)RetIdx, 
					    (void*)RetCmd,
					    NULL,
					    NULL,
					    NULL
					    );	
	nret = UserSpiDataExchangeISR(g_u8RxPDO, u8RxBuf, sizeof(SPI_CMD_PACKAGE_T));	
	if (nret < 0){
		return (nret);
	}
	
	return 1;
}



static uint8_t g_u8ECMPdoFifoDataExchange_LastOp=ECM_FIFO_WR;
static uint8_t g_u8ECMPdoFifoDataExchange_Op;
static uint8_t g_u8ECMPdoFifoDataExchange_Cnt;
/*
 * Return
 * 0	: LastCmd is not ECM_CMD_ECAT_PDO_DATA_FIFO_OP
 * 4	: read and write fail
 * 5	: read ok
 * 6	: write ok
 * 7	: read and write ok
 * <0	: error
 * -2　	: spi fail
 * */
int32_t ECM_EcatPdoFifoDataExchangeAdvResponse(int nret, void *ptxdata, void *pu8rxpdofifocnt, void *pCrcErrCnt, void *pWkcErrCnt, void *pIsSlvAlive)
{
static uint32_t u32PreSPIPackageCount;	
	uint8_t *pTxData = (uint8_t *)ptxdata;
	uint8_t *pu8RxPdoFifoCnt = (uint8_t *)pu8rxpdofifocnt;
	uint8_t *CrcErrCnt = (uint8_t *)pCrcErrCnt;
	uint8_t *WkcErrCnt = (uint8_t *)pWkcErrCnt;
	uint8_t *IsSlvAlive = (uint8_t *)pIsSlvAlive;
	
	uint8_t u8RetOp=0;

	if (nret < 0){
		return -2;
	}
	if(pu8RxPdoFifoCnt){
		if(g_u8ECMPdoFifoDataExchange_Op & ECM_FIFO_WR){
			*pu8RxPdoFifoCnt = (pRet->Head.u8RxFifoCnt+g_u8ECMPdoFifoDataExchange_Cnt);
		}else{
			*pu8RxPdoFifoCnt = pRet->Head.u8RxFifoCnt;
		}
	}
	if(CrcErrCnt)
		*CrcErrCnt = pRet->Head.u8CrcErrCnt;
	if(WkcErrCnt)
		*WkcErrCnt = pRet->Head.u8WkcErrCnt;
	if(IsSlvAlive){
		if((pRet->Head.u8Status & (ECM_STA_ECAT_CONFIG_MASK | ECM_STA_FIFO_EN_MASK)) == (ECM_STA_ECAT_CONFIG_MASK | ECM_STA_FIFO_EN_MASK)){
			*IsSlvAlive = 1;
		}else{
			*IsSlvAlive = 0;
		}
	}
	if(pRet->Head.u8ErrorStatus & ECM_ERR_FIFO_MASK){
		MSG_DBG("ERR(0x%X) - Fifo(%d)\n",pRet->Head.u8ErrorStatus,pRet->Head.u8RxFifoCnt);
	}
	if (!(pRet->Head.u8Status & ECM_STA_NOP_CMD_MASK)) {
		if(pRet->Head.u8Cmd == ECM_CMD_ECAT_PDO_DATA_FIFO_OP){
			u8RetOp = 4;
			if(pRet->Head.u8Return & ECM_FIFO_RD){
				if(pRet->Head.u16Size){
					if(pTxData){
						if ((u32PreSPIPackageCount+1) == gSPIPackageCount){
							memcpy(pTxData, pRet->Data, pRet->Head.u16Size);
							//MSG_DBG("PDO copy");							
						}
					}
					u8RetOp |= 1;
				}else{
					MSG_DBG("Zero size - check SPI idle time(0x%X)\r\n",pRet->Head.u8ErrorStatus);
					WAIT_KEY();
				}
			}
			if((g_u8ECMPdoFifoDataExchange_LastOp & ECM_FIFO_WR) == (pRet->Head.u8Return & ECM_FIFO_WR)){
				u8RetOp |= 2;
			}
		}
	}
	g_u8ECMPdoFifoDataExchange_LastOp = g_u8ECMPdoFifoDataExchange_Op;
	u32PreSPIPackageCount = gSPIPackageCount;	
	return u8RetOp;
}



/*
 * Return
 * 0	: LastCmd is not ECM_CMD_ECAT_PDO_DATA_FIFO_OP
 * 4	: read and write fail
 * 5	: read ok
 * 6	: write ok
 * 7	: read and write ok
 * <0	: error
 * */
int32_t ECM_EcatPdoFifoDataExchangeAdvISR(uint8_t u8Op, uint8_t u8Cnt, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pu8RxPdoFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt, uint8_t *IsSlvAlive)
{
	uint8_t u8RetOp=0;
	//TRACE_MSG("00");	
	g_u8ECMPdoFifoDataExchange_Op = u8Op;
	g_u8ECMPdoFifoDataExchange_Cnt = u8Cnt;
	g_pFifoCmd->Head.u8Cmd = ECM_CMD_ECAT_PDO_DATA_FIFO_OP;
	g_pFifoCmd->Head.u16Size = u8Cnt*u16DataSize;
	g_pFifoCmd->Head.u8Param = u8Cnt;
	g_pFifoCmd->Head.u8Data[0] = u8Op;
	g_pFifoCmd->Head.u8Idx++;
#if (APP_ENABLE_ECHERCAT_INT1 == 1)	
	g_pFifoCmd->Head.u32CompIntClr = (uint32_t)((uint32_t)1<<31);
#endif	
	if (u8Op & ECM_FIFO_WR){
		if (pRxData) {
			memcpy(g_pFifoCmd->Data, pRxData, g_pFifoCmd->Head.u16Size);
		}
	}

	EC_CmdResponsePush(ECM_EcatPdoFifoDataExchangeAdvResponse, 
					    (void*)pTxData, 
					    (void*)pu8RxPdoFifoCnt,
					    (void*)CrcErrCnt,
					    (void*)WkcErrCnt,
					    (void*)IsSlvAlive
					    );	
						
	if (SpiFiFoDataExchangeISR(0,0) <= 0){
		MSG_ERR("CRC error\r\n");
		g_u8ECMPdoFifoDataExchange_LastOp = u8Op;
		return -1;//CRC error
	}

	return u8RetOp;
}
