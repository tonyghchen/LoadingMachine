/******************************************************************************
 *	File	:	EcmUsrDriver.c
 *	Version :	1.60
 *	Date	:	2022/02/08
 *	Author	:	XFORCE
 *
 *	ECM-XF basic driver example - Source file
 *
 *	Demonstrate how to implement API type user driver
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/
 
#ifdef __GNUC__ 
#include <pthread.h>
#endif

#include "EcmUsrDriver.h"
#include "platform.h"
#include "trace_config.h"

pthread_mutex_t g_mutex;
uint8_t u8TxBuf[PKG_MAX_SIZE]={0};
uint8_t u8RxBuf[PKG_MAX_SIZE]={0};
uint8_t g_u8RxPDO[PKG_MAX_SIZE] = { 0 };
SPI_CMD_PACKAGE_T *pCmd=(SPI_CMD_PACKAGE_T *)u8TxBuf;
SPI_RET_PACKAGE_T *pRet=(SPI_RET_PACKAGE_T *)u8RxBuf;
SPI_CMD_PACKAGE_T *g_pFifoCmd = (SPI_CMD_PACKAGE_T *)g_u8RxPDO;

int g_nSpiIdleTime = TEST_SPI_IDLE_TIME;
uint8_t g_u8CrcType=ECM_CRC_TYPE_NONE;

uint8_t g_u8CrcErrConti;
uint8_t g_u8EcmStatus;
uint8_t g_u8RxPDOFifoCnt;
uint8_t g_u8TxPDOFifoCnt;
uint8_t g_u8CrcErrCnt;
uint8_t g_u8WkcErrCnt;

uint8_t g_u8LastAsyncCmd=0;

/*
 * crc32.c
 *
 *  Created on: 2020/3/19
 *      Author: bhliong.tw
 */

const uint32_t crc32_tab[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

/*
 * A function that calculates the CRC-32 based on the table above is
 * given below for documentation purposes. An equivalent implementation
 * of this function that's actually used in the kernel can be found
 * in sys/libkern.h, where it can be inlined.
 */
uint32_t crc32(const void *buf, size_t size)
{
	const uint8_t *p = (const uint8_t *)buf;
	uint32_t crc;
	crc = ~0U;
	while (size--)
		crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);
	return crc ^ ~0U;
}

int32_t ECM_GetRetStatus(uint8_t *pStatus)
{
	*pStatus = pRet->Head.u8Status;
	return 1;
}
int32_t ECM_GetRetErrStatus(uint8_t *pErrStatus)
{
	*pErrStatus = pRet->Head.u8ErrorStatus;
	return 1;
}

int32_t ECM_ClearErrorStatus(int nClear, uint8_t *pEcmErrorStatus, uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt)
{
	pCmd->Head.u8Cmd = ECM_CMD_INFO_UPDATE_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	if(nClear){
		pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	}else{
		pCmd->Head.u8Ctrl &= ~ECM_CTL_CLR_ALL_ERR_MASK;
	}
	if(SpiDataExchange(0,0) == 1){
		pCmd->Head.u8Ctrl &= ~ECM_CTL_CLR_ALL_ERR_MASK;
		if(pRet->Head.u8ErrorStatus & 0xF8){
			MSG_DBG("INFOUPDATE : Cmd:%d LastCmd:%d ErrorStatus(0x%X)\r\n", pRet->Head.u8Cmd, g_u8LastAsyncCmd, pRet->Head.u8ErrorStatus);
		}
		if(pEcmErrorStatus)
			*pEcmErrorStatus = pRet->Head.u8ErrorStatus;
		if(pEcmStatus)
			*pEcmStatus = pRet->Head.u8Status;
		if(pRxPDOFifoCnt)
			*pRxPDOFifoCnt  = pRet->Head.u8RxFifoCnt;
		if(CrcErrCnt)
			*CrcErrCnt = pRet->Head.u8CrcErrCnt;
		if(WkcErrCnt)
			*WkcErrCnt = pRet->Head.u8WkcErrCnt;
		return 1;
	}
	pCmd->Head.u8Ctrl &= ~ECM_CTL_CLR_ALL_ERR_MASK;
	return 0;
}
/*
 * Desc
 * 		Show error status and set clean flag
 * Param
 * 		nCleanFlag
 * 			0 : Don't clear error
 * 			1 : Clear error
 * Return
 * 		1 : No error
 * 		-1: Error occur
 * */
int32_t ECM_PrintErrStatus(int32_t nCleanFlag)
{
	if(pRet->Head.u8ErrorStatus & 0xF8){
		MSG_DBG("=====\r\nCmd:%d LastAsyncCmd:%d  Error!!! - ", pRet->Head.u8Cmd, g_u8LastAsyncCmd);
		if(pRet->Head.u8ErrorStatus & ECM_ERR_ASYNC_CMD_MASK){
			MSG_DBG("ASYNC CMD\r\n=====\r\n");
		}
		if(pRet->Head.u8ErrorStatus & ECM_ERR_SPI_MASK){
			MSG_DBG("SPI\r\n=====\r\n");
		}
		if(pRet->Head.u8ErrorStatus & ECM_ERR_FIFO_MASK){
			MSG_DBG("FIFO\r\n=====\r\n");
		}
		if(pRet->Head.u8ErrorStatus & ECM_ERR_CRC_MASK){
			MSG_DBG("CRC\r\n=====\r\n");
		}
		if(pRet->Head.u8ErrorStatus & ECM_ERR_CMD_MASK){
			MSG_DBG("CMD\r\n=====\r\n");
		}
		if(nCleanFlag){
			pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
		}else{
			pCmd->Head.u8Ctrl &= ~ECM_CTL_CLR_ALL_ERR_MASK;
		}
		//MSG_DBG("Enter any key to continue\r\n");
		//WAIT_KEY();
		return -1;
	}else{
		//pCmd->Head.u8Ctrl &= ~ECM_CTL_CLR_ALL_ERR_MASK;
		return 1;
	}
}
int32_t EcmSpiPackSizeCal(int32_t nSizeLimit)
{
	int32_t i,j;
	int32_t nStart=-1,nEnd=-1;
	int32_t nSize=0;
	SPI_RET_PACKAGE_T *pSpiRet = (SPI_RET_PACKAGE_T *)u8RxBuf;
	uint8_t u8Word[8];
	if(nSizeLimit<32){
		return -1;
	}
	if(nSizeLimit>PKG_MAX_SIZE){
		return -2;
	}
	for(i=0; i<nSizeLimit; i++){
		UserSpiDataExchange(u8TxBuf, u8RxBuf, 1);
		for(j=7;j>0;j--){
			u8Word[j] = u8Word[j-1];
		}
		u8Word[0] = u8RxBuf[0];
		//Start Word
		if( u8Word[7]==0x59 && \
			u8Word[6]==0x58 && \
			u8Word[5]==0x57 && \
			u8Word[4]==0x56 && \
			u8Word[3]==0xA4 && \
			u8Word[2]==0xA3 && \
			u8Word[1]==0xA2 && \
			u8Word[0]==0xA1){
			if(nStart < 0){
				nStart = (i-3);
			}else{
				nEnd = (i-4);
				nSize = nEnd-nStart+1;
				break;
			}
		}
		//Stop Word
		if(u8Word[0]==0x56 && u8Word[1]==0x57 && u8Word[2]==0x58 && u8Word[3]==0x59){
			UserDelay(200);
		}
	}
	if(nSize){
		// Already sent 4bytes start word, so do the rest bytes
		UserSpiDataExchange(&u8TxBuf[4], &u8RxBuf[4], nSize-4);
		UserDelay(200);
	}
	g_u8CrcType = (pSpiRet->Head.u8Status & ECM_STA_CRC_TYPE_MASK);
	MSG_DBG("SPI total package size %d\r\n",nSize);
	MSG_DBG("SPI CRC Type %d\r\n",g_u8CrcType);
	return nSize;
}
/*
 * Return
 * 			-2	:	CRC continue error reach MAX
 * 			-1	:	CRC continue error reach MAX and print info
 * 			0	:	CRC error
 * 			1	:	Successful
 * */
int32_t SpiDataExchange(uint8_t *RetIdx, uint8_t *RetCmd)
{
	//int32_t i=0;
	uint32_t unCrcResult=0;
	if(g_u8CrcErrConti == SPI_CRC_ERROR_CONTI_MAX){
		MSG_DBG("g_u8CrcErrConti reached MAX(%d)\n",SPI_CRC_ERROR_CONTI_MAX);
		g_u8CrcErrConti++;
		return -1;
	}else if(g_u8CrcErrConti > SPI_CRC_ERROR_CONTI_MAX){
		return -2;
	}
	pCmd->Head.u32StartWord = ECM_START_WORD;
//	if(pCmd->Head.u8Cmd == ECM_CMD_CRC_TYPE_SET){
//		pCmd->Crc =  ECM_CRC_MAGIC_NUM;
//	}else{
	if(g_u8CrcType == ECM_CRC_TYPE_32){
#ifdef ECM_VERC_CHKSUM
		pCmd->Crc =  crc32(u8TxBuf, pCmd->Head.u16Size+24);
#else
		pCmd->Crc =  crc32(u8TxBuf, sizeof(SPI_CMD_PACKAGE_T)-8);
#endif
	}else{
		pCmd->Crc =  ECM_CRC_MAGIC_NUM;
	}
//	}
	pCmd->StopWord = ECM_STOP_WORD;
	//pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	UserSpiDataExchange(u8TxBuf, u8RxBuf, sizeof(SPI_CMD_PACKAGE_T));
	
	if(g_nSpiIdleTime)
		UserDelay(g_nSpiIdleTime);
	/*if (pRet->Head.u8ErrorStatus & ECM_CTL_CLR_ALL_ERR_MASK) {
		MSG_DBG("u8ErrorStatus : 0x%X\n", pRet->Head.u8ErrorStatus);
		getchar();
	}*/
	if(g_u8CrcType == ECM_CRC_TYPE_32){
#ifdef ECM_VERC_CHKSUM
		unCrcResult = crc32(u8RxBuf, pRet->Head.u16Size+24);		
#else
		unCrcResult = crc32(u8RxBuf, sizeof(SPI_RET_PACKAGE_T)-8);
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
	}else{
		MSG_DBG("CRC error 0x%x(%d) != 0x%x(%d) size(%d)\n", pRet->Crc,pRet->Crc,unCrcResult,unCrcResult,pRet->Head.u16Size, pRet->Data[0]);
	}
	// CRC Check Fail.
	g_u8CrcErrConti++;
	return 0;
}
int SpiFifoDataExchange(uint8_t *RetIdx, uint8_t *RetCmd)
{
//	int i = 0;
	unsigned int unCrcResult = 0;
	if (g_u8CrcErrConti == SPI_CRC_ERROR_CONTI_MAX) {
		MSG_DBG("g_u8CrcErrConti reached MAX(%d)\n", SPI_CRC_ERROR_CONTI_MAX);
		g_u8CrcErrConti++;
		return -1;
	}
	else if (g_u8CrcErrConti > SPI_CRC_ERROR_CONTI_MAX) {
		return -2;
	}
	g_pFifoCmd->Head.u32StartWord = ECM_START_WORD;
	g_pFifoCmd->StopWord = ECM_STOP_WORD;
	g_pFifoCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;	
	if (g_pFifoCmd->Head.u8Cmd == ECM_CMD_CRC_TYPE_SET) {
		g_pFifoCmd->Crc = ECM_CRC_MAGIC_NUM;
	}
	else {
		if (g_u8CrcType == ECM_CRC_TYPE_32) {
#ifdef ECM_VERC_CHKSUM
			g_pFifoCmd->Crc = crc32(g_u8RxPDO, g_pCmd->Head.u16Size + 24);
#else
			g_pFifoCmd->Crc = crc32(g_u8RxPDO, sizeof(SPI_CMD_PACKAGE_T) - 8);
#endif
		}
		else {
			g_pFifoCmd->Crc = ECM_CRC_MAGIC_NUM;
		}
	}
	//g_pFifoCmd->StopWord = ECM_STOP_WORD;
	//g_pFifoCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	UserSpiDataExchange(g_u8RxPDO, u8RxBuf, sizeof(SPI_CMD_PACKAGE_T));

#ifdef TEST_SPI_IDLE_TIME
	UserDelay(TEST_SPI_IDLE_TIME);
#endif

	if (g_u8CrcType == ECM_CRC_TYPE_32) {
#ifdef ECM_VERC_CHKSUM
		unCrcResult = crc32(u8RxBuf, pRet->Head.u16Size + 24);
#else
		unCrcResult = crc32(u8RxBuf, sizeof(SPI_RET_PACKAGE_T) - 8);
#endif
	}
	else {
		unCrcResult = ECM_CRC_MAGIC_NUM;
	}
	if (pRet->Crc == unCrcResult) {
		g_u8EcmStatus = pRet->Head.u8Status;
		g_u8RxPDOFifoCnt = pRet->Head.u8RxFifoCnt;
		g_u8TxPDOFifoCnt = pRet->Head.u8TxFifoCnt;
		if (RetIdx) {
			*RetIdx = pRet->Head.u8Idx;
		}
		if (RetCmd) {
			*RetCmd = pRet->Head.u8Cmd;
		}
		g_u8CrcErrConti = 0;
		return 1;
	}
	else if (pRet->Crc == ECM_CRC_INIT_NUM) {
		MSG_DBG("Data not ready, maybe need more SPI idle time\n");
	}
	else {
		MSG_DBG("CRC error 0x%x(%d) != 0x%x(%d) size(%d)\n", pRet->Crc, pRet->Crc, unCrcResult, unCrcResult, pRet->Head.u16Size);
	}
	g_u8CrcErrConti++;
	return 0;
}
/*
 * Return
 * 			0	:	Timeout
 * 			1	:	Get valid return
 * */
int32_t EcmCmdTransceiver(int32_t nTryCnt)
{
	int32_t i,nret;
	uint8_t IdxCheck, CmdCheck;
	for(i=0;i<nTryCnt;i++){
		nret = SpiDataExchange(&IdxCheck, &CmdCheck);
		if(nret == 1){
			if(pCmd->Head.u8Idx == IdxCheck){
				//if(pCmd->Head.u8Cmd == CmdCheck){
					return ECM_PrintErrStatus(1);
				/*}else{
					MSG_DBG("Command code error %d != %d\r\n",pCmd->Head.u8Cmd ,CmdCheck);
					return 0;
				}*/
			}/*else{
				MSG_DBG("EcmCmdTransceiver Idx(%d | %d) Cmd(%d | %d)\n",pCmd->Head.u8Idx, IdxCheck,pCmd->Head.u8Cmd, CmdCheck);
			}*/
		}else if(nret < 0){
			MSG_DBG("EcmCmdTransceiver: SpiDataExchange return %d\n",nret);
			return 0;
		}
	}
	MSG_DBG("EcmCmdTransceiver: SpiDataExchange TIMEOUT\n");
	return 0;
}
/*
 * Return
 * 			0	:	Timeout
 * 			1	:	Get valid return
 * 			-1	:	Get valid return but command response error
 *			-2	:	WaitAyncDone error
 *			-3	:	Param error
 * */
int32_t EcmCmdTransceiver_WaitAyncDone(int32_t nTryCnt, uint16_t *pu16ReturnDataSize, uint8_t *pu8ReturnData)
{
	int32_t nret=0;
	g_u8LastAsyncCmd = pCmd->Head.u8Cmd;
	nret=EcmCmdTransceiver(nTryCnt);
	if(nret == 1){
		if(pu8ReturnData){
			memcpy(pu8ReturnData, pRet->Data, pRet->Head.u16Size);
			if(pu16ReturnDataSize){
				*pu16ReturnDataSize = pRet->Head.u16Size;
				return 1;//If the command want to get data back, so it's not an AsyncCommand. return immediately
			}else{
				return -3;
			}
		}
		if(ECM_WaitAsyncDone(nTryCnt)){
			return ECM_PrintErrStatus(1);//Show error message and set clean flag
		}else{
			MSG_DBG("WaitAsyncDone timeout CMD(%d)\n",pCmd->Head.u8Cmd);
			nret = -2;
		}
	}
	return nret;
}
/*	Return
 * 			0	:	Timeout
 * 			1	:	Get valid return
 * 			-1	:	Get valid return but command response error
 *			-2	:	WaitAyncDone error *
 * */
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
				uint8_t *pu8ReturnData)
{

	int32_t nret=0;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = u8Cmd;
	pCmd->Head.u8Param = u8Param;
	pCmd->Head.u8Data[0] = u8Param0;
	pCmd->Head.u8Data[1] = u8Param1;
	pCmd->Head.u8Data[2] = u8Param2;
	pCmd->Head.u8Data[3] = u8Param3;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret=EcmCmdTransceiver_WaitAyncDone(1000, pu16ReturnDataSize, pu8ReturnData);
	if(nret > 0){
		if(pu8Return){
			*pu8Return = pRet->Head.u8Return;
		}
		if(pu8Status){
			*pu8Status = pRet->Head.u8Status;
		}
		if(pu8ErrStatus){
			*pu8ErrStatus = pRet->Head.u8ErrorStatus;
		}
	}
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
/*
 * Return
 * 0	:	CRC Error or DC unstable
 * 1	:	DC stable
 * */
int32_t ECM_CheckDCStable(void)
{
	uint8_t u8EcmStatus;
	if(ECM_InfoUpdate(&u8EcmStatus, NULL, NULL, NULL)){
		if(u8EcmStatus & ECM_STA_DC_STABLE){
			return 1;
		}
	}
	return 0;
}
/*
 * Is ECM-XF WKC continue error event occur and Update ECM info
 * Return
 * -1	:	CRC Error
 * 0	:	Miss flag ECM_STA_ECAT_CONFIG_MASK or ECM_STA_FIFO_EN_MASK
 * 1	:	WKC continue error is not occur
 * */
int32_t ECM_IsSlaveAlive(uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt)
{
	uint8_t u8EcmStatus;
	if(ECM_InfoUpdate(&u8EcmStatus, pRxPDOFifoCnt, CrcErrCnt, WkcErrCnt)){
		if((u8EcmStatus & (ECM_STA_ECAT_CONFIG_MASK | ECM_STA_FIFO_EN_MASK)) == (ECM_STA_ECAT_CONFIG_MASK | ECM_STA_FIFO_EN_MASK)){
			return 1;
		}else{
			MSG_DBG("u8EcmStatus 0x%X\r\n",u8EcmStatus);
			return 0;
		}
	}else{
		return -1;
	}
}
/*
 * Return
 * 0	:	CRC Error
 * 1	:	Get valid info
 * */
int32_t ECM_InfoUpdate(uint8_t *pEcmStatus, uint8_t *pRxPDOFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt)
{
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_INFO_UPDATE_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	//Don't update ec_state, if update ec_state that will be an async command
	pCmd->Head.u8Ctrl &= ~ECM_CTL_UPDATE_EC_STATE_MASK;
	if(SpiDataExchange(0,0) == 1){
		if(pRet->Head.u8ErrorStatus & 0xF8){
			MSG_DBG("INFOUPDATE : Cmd:%d LastCmd:%d ErrorStatus(0x%X)\r\n", pRet->Head.u8Cmd, g_u8LastAsyncCmd, pRet->Head.u8ErrorStatus);
		}
		if(pEcmStatus)
			*pEcmStatus = pRet->Head.u8Status;
		if(pRxPDOFifoCnt)
			*pRxPDOFifoCnt  = pRet->Head.u8RxFifoCnt;
		if(CrcErrCnt)
			*CrcErrCnt = pRet->Head.u8CrcErrCnt;
		if(WkcErrCnt)
			*WkcErrCnt = pRet->Head.u8WkcErrCnt;
		pthread_mutex_unlock(&g_mutex);
		return 1;
	}
	pthread_mutex_unlock(&g_mutex);
	return 0;
}

int32_t ECM_SetCrcType(uint8_t u8Type)
{
	int32_t nret=0,i=0;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_CRC_TYPE_SET;
	pCmd->Head.u8Idx++;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Param = u8Type;
	for(i=0;i<10;i++){
		nret=SpiDataExchange(NULL, NULL);
		g_u8CrcType = (pRet->Head.u8Status & ECM_STA_CRC_TYPE_MASK);
		MSG_DBG("ECM_SetCrcType CrcType : 0x%X\n", g_u8CrcType);
		if(g_u8CrcType == u8Type){
			nret = 1;			
			break;
		}
	}
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
/*
 * Return
 * 	0		:	Error
 * 	Others	:	ECM firmware version
 *
 * */
uint8_t ECM_InitLibrary(uint16_t *pu16SpiDataSize)
{
	int32_t i=0,j=0;
	int32_t nret;
	uint8_t u8Version;
	memset(u8TxBuf,0,PKG_MAX_SIZE);
	memset(u8RxBuf,0,PKG_MAX_SIZE);
	pCmd=(SPI_CMD_PACKAGE_T *)u8TxBuf;
	pRet=(SPI_RET_PACKAGE_T *)u8RxBuf;
	//pCmd->Head.u8Ctrl = ECM_CTL_CLR_ALL_ERR_MASK;
	g_u8CrcErrConti=0;
	g_u8TxPDOFifoCnt=0;
	pthread_mutex_init(&g_mutex, NULL);
	if(pu16SpiDataSize){
		MSG_DBG("ECM_SetSpiDataSize Begin(Size=%d)\n", *pu16SpiDataSize);
		nret = ECM_SetSpiDataSize(*pu16SpiDataSize);
		if(nret <= 0){
			MSG_DBG("ECM_SetSpiDataSize failed\r\n");
			return 0;
		}
		MSG_DBG("ECM_SetSpiDataSize End\n");
		ECM_ClearErrorStatus(1, 0, 0, 0, 0, 0);
		MSG_DBG("ECM_GetSpiDataSize Begin\n");
		nret = ECM_GetSpiDataSize(pu16SpiDataSize);
		if(nret <= 0){
			MSG_DBG("ECM_GetSpiDataSize failed\r\n");
			return 0;
		}
		MSG_DBG("ECM_GetSpiDataSize End\n");
	}
	if(g_u8CrcType != TEST_SPI_CRC_TYPE){
		MSG_DBG("ECM_SetCrcType Begin\n");
		nret = ECM_SetCrcType(ECM_CRC_TYPE_32);
		if(nret <= 0){
			MSG_DBG("ECM_SetCrcType failed\r\n");
			return 0;
		}
		MSG_DBG("ECM_SetCrcType End\n");
	}
	nret = ECM_GetFirmwareVersion(&u8Version);
	if(nret == 0){
		MSG_DBG("ECM_GetFirmwareVersion failed\r\n");
		return 0;
	}else{
		MSG_DBG("Version 0x%X\n",u8Version);
	}
	for(i=0;i<10;i++){
		//pCmd->Head.u8Ctrl = ECM_CTL_CLR_ALL_ERR_MASK;
		if(ECM_InfoUpdate(0, 0, 0, 0)){
			MSG_DBG("Check ASYNC command");
			// FIFO has been initiated
			while(pRet->Head.u8Status & ECM_STA_ASYNC_OP_BUSY_MASK){
				if(j%10 == 9)
					MSG_DBG("\rCheck ASYNC command");
				else
					MSG_DBG(".");
				UserDelay(10000);
				if(j>=1000){
					MSG_DBG("\r\nWait ASYNC done timeout\r\n");
					MSG_DBG("u8CrcErrCnt 0x%X\n",pRet->Head.u8CrcErrCnt);
					MSG_DBG("u8Status 0x%X\n",pRet->Head.u8Status);
					MSG_DBG("u8ErrorStatus 0x%X\n",pRet->Head.u8ErrorStatus);
					//return 0;
				}
				j++;
				ECM_InfoUpdate(0, 0, 0, 0);
			}
			MSG_DBG("\r\nPASS\r\n");
			// FIFO has been initiated
			if(pRet->Head.u8Status & ECM_STA_FIFO_EN_MASK){
				MSG_DBG("FIFO has been initiated\n");
			}
			MSG_DBG("Disable FIFO\n");
			ECM_EnableFIFO(0);
			ECM_ClearFIFO(0);
			// Communication has been initiated
			if(pRet->Head.u8Status & ECM_STA_ECAT_CONFIG_MASK){
				MSG_DBG("Initialization state : ");
				ECM_EcatStateSet(0xFF, EC_STATE_INIT);
				MSG_DBG("DONE\r\n");
			}
			return u8Version;
		}
	}
	return 0;
}
void ECM_CloseLibrary()
{
	// Release resources used by the critical section object.
	pthread_mutex_destroy(&g_mutex);
}
int32_t ECM_GetFirmwareVersion(uint8_t *pVersion)
{
	int32_t nret=0;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FW_VERSION_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Ctrl = 0;
	nret=EcmCmdTransceiver(1000);
	*pVersion = pRet->Head.u8Return;
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
/*
 * Return
 * 0	: Idle
 * 1	: Busy
 * -1	: Error
 * */
int32_t ECM_IsAsyncBusy(void)
{
	pCmd->Head.u8Cmd = ECM_CMD_INFO_UPDATE_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	//Don't update ec_state, if update ec_state that will be an async command
	pCmd->Head.u8Ctrl &= ~ECM_CTL_UPDATE_EC_STATE_MASK;
	if (SpiDataExchange(0, 0) == 1) {
		if (pRet->Head.u8Status & ECM_STA_ASYNC_OP_BUSY_MASK) {
			return 1;
		}
		else {
			return 0;
		}
	}
	return -1;
}
int32_t ECM_WaitAsyncDone(int32_t nMS)
{
	int32_t i=0;
	for(i=0;i<nMS;i++){
		if(ECM_IsAsyncBusy()==0){
			return 1;
		}else{
			UserDelay(1000);//1ms
		}
	}
	return 0;
}
int32_t ECM_SetSpiDataSize(uint16_t u16SpiDataSize)
{
	int32_t nTest=0;
	int32_t nOrgSpiPackSize;
	SPI_CMD_HEADER	*pSpiPackHead;
	uint32_t		*pSpiPackCrc;
	uint32_t		*pSpiPackStopWord;
	for(nTest=0;nTest<10;nTest++){
		nOrgSpiPackSize = EcmSpiPackSizeCal(PKG_MAX_SIZE);
		if(nOrgSpiPackSize > 0){
			break;
		}
	}
	if(nOrgSpiPackSize == 0){
		return 0;
	}
	pthread_mutex_lock(&g_mutex);
	pSpiPackHead = (SPI_CMD_HEADER *)u8TxBuf;
	pSpiPackHead->u8Cmd = ECM_CMD_SPI_RECONFIG_OP;
	pSpiPackHead->u16Size = u16SpiDataSize;
	pSpiPackHead->u8Idx++;
	pSpiPackHead->u32StartWord = ECM_START_WORD;
	pSpiPackCrc = (uint32_t *)&u8TxBuf[nOrgSpiPackSize-8];
	pSpiPackStopWord = (uint32_t *)&u8TxBuf[nOrgSpiPackSize-4];
	*pSpiPackCrc = ECM_CRC_MAGIC_NUM;
	*pSpiPackStopWord = ECM_STOP_WORD;
	UserSpiDataExchange(u8TxBuf, u8RxBuf, nOrgSpiPackSize);
	pthread_mutex_unlock(&g_mutex);
	UserDelay(100000);//100ms
	return 1;
}

int32_t ECM_GetSpiDataSize(uint16_t *pu16SpiDataSize)
{
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_SPI_PACK_SIZE_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	if(EcmCmdTransceiver(1000)){
		memcpy(pu16SpiDataSize , pRet->Data, 2);
		pthread_mutex_unlock(&g_mutex);
		return 1;
	}
	pthread_mutex_unlock(&g_mutex);
	return 0;
}

int32_t ECM_SetTxFIFOCnt(uint8_t u8TxCnt)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_SET_TX_CNT;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = u8TxCnt;
	nret =  EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_SetRxFIFOCnt(uint8_t u8RxCnt)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_SET_RX_CNT;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = u8RxCnt;
	nret =  EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_GetTxFIFOCnt(uint8_t *pu8Cnt)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_GET_TX_CNT;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	*pu8Cnt = pRet->Head.u8Return;
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_GetRxFIFOCnt(uint8_t *pu8Cnt)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_GET_RX_CNT;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	*pu8Cnt = pRet->Head.u8Return;
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_EnableFIFO(uint8_t u8Enable)
{
	int32_t nret;
	//MSG_DBG ("__FUNCTION__ = %s\n", __FUNCTION__);
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_ENABLE;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = u8Enable;
	nret =  EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_ClearFIFO(uint8_t u8TxRx)
{
	int32_t nret;
	//MSG_DBG ("__FUNCTION__ = %s\n", __FUNCTION__);
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_CLR_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = u8TxRx;
  pCmd->Head.u32CompIntClr = (uint32_t)((uint32_t)1<<31);	
	nret =  EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_InitFIFO(void)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_INIT;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret=EcmCmdTransceiver_WaitAyncDone(1000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_EcatInit(uint16_t DCActCode, uint32_t CycTime)
{
	int32_t nret ;
	EC_DCSYNC_H *pDcSyncCmd = (EC_DCSYNC_H *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pDcSyncCmd->Slave = ECM_INDEX;
	pDcSyncCmd->Mode = (DCActCode)&0xff;
	pDcSyncCmd->Act = (DCActCode>>8)&0xff;
	pDcSyncCmd->CyclTime0 = CycTime;
	pDcSyncCmd->CyclTime1 = 0;
	pDcSyncCmd->CyclShift = (CycTime/4)+(62500*2);
	pDcSyncCmd->Paddle = 0x81;//Disable FIFO first
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_INIT_OP;
	pCmd->Head.u16Size = sizeof(EC_DCSYNC_H);
	pCmd->Head.u8Idx++;
	//pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	nret = EcmCmdTransceiver_WaitAyncDone(10000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_EcatInitDC(void)
{
	int32_t nret ;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_INIT_DC_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver_WaitAyncDone(10000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_EcatSetDCSync(uint8_t u8SlvIdx, uint16_t DCActCode, uint32_t CycTime)
{
	int32_t nret;
	EC_DCSYNC_H *pDcSyncCmd = (EC_DCSYNC_H *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pDcSyncCmd->Slave = u8SlvIdx;
	pDcSyncCmd->Mode = (DCActCode)&0xff;
	pDcSyncCmd->Act = (DCActCode>>8)&0xff;
	pDcSyncCmd->CyclTime0 = CycTime;
	pDcSyncCmd->CyclTime1 = CycTime;
	pDcSyncCmd->CyclShift = (CycTime/2);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_DCSYNC;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver_WaitAyncDone(10000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_EcatReconfig()
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_RECONFIG_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver_WaitAyncDone(10000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int8_t ECM_EcatSlvCntGet()
{
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_SLV_CNT_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	if(EcmCmdTransceiver(1000)==1){
		pthread_mutex_unlock(&g_mutex);
		return pRet->Head.u8Return;
	}
	pthread_mutex_unlock(&g_mutex);
	return -1;
}

int32_t ECM_EcatStateSet(uint8_t u8Slave, uint8_t u8State)
{
	int32_t nret;
	//MSG_DBG ("__FUNCTION__ = %s\n", __FUNCTION__);
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_STATE_SET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = u8Slave;
	pCmd->Head.u8Data[0] = u8State;
	pCmd->Head.u8Ctrl |= ECM_CTL_UPDATE_EC_STATE_MASK;
	nret=EcmCmdTransceiver_WaitAyncDone(1000000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_EcatStateUpdate(void)
{
	int32_t nret=0;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_STATE_UPDATE;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret=EcmCmdTransceiver_WaitAyncDone(1000000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_EcatStateGet(uint8_t u8Slave, uint8_t *pu8State)
{
	//int32_t i=0;
	ECM_EcatStateUpdate();
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_STATE_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = u8Slave;
	if(EcmCmdTransceiver(10000) == 1){
		*pu8State = pRet->Head.u8Return;
		pthread_mutex_unlock(&g_mutex);
		return 1;
	}
	pthread_mutex_unlock(&g_mutex);
	return 0;
}
int32_t ECM_EcatStateCheck(uint8_t u8Slave, uint8_t u8State)
{
	int32_t nret=0;
	//int8_t n8Return;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_STATE_CHECK;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = u8Slave;
	pCmd->Head.u8Data[0] = u8State;
	nret=EcmCmdTransceiver_WaitAyncDone(10000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
/*
 * return
 * 1 	:	set state done
 * -2	:	set state fail
 * 0	:	wait state timeout
*/
int32_t ECM_StateCheck(uint8_t u8Slave, uint8_t u8ExpectState, int32_t TimeOutMS)
{
	uint8_t u8State;
	int32_t i=0;
	int32_t ret=0;
	for(i=0;i<(TimeOutMS/100);i++){
		ret = ECM_EcatStateGet(u8Slave, &u8State);
		if(ret > 0){
			if(u8State == u8ExpectState){
				return 1;
			}else{
				ret = ECM_EcatStateSet(u8Slave, u8ExpectState);
				if(ret != 1){
					return -2;
				}
			}
		}
		UserDelay(100000);//100ms
	}
	return 0;
}
int32_t ECM_EcatPdoConfigSet( uint8_t Slave, PDO_CONFIG_HEAD *pConfigData)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_PDO_CONFIG_SET;
	pCmd->Head.u16Size = sizeof(PDO_CONFIG_HEAD);
	pCmd->Head.u8Idx++;
	pConfigData->Slave = Slave;
	memcpy(pCmd->Data, pConfigData, sizeof(PDO_CONFIG_HEAD));
	nret = EcmCmdTransceiver_WaitAyncDone(1000,0,0);
	pthread_mutex_unlock(&g_mutex);
	if(nret == -2){
		MSG_DBG("Get SDO abort code\r\n");
	}
	return nret;
}
int32_t ECM_EcatPdoConfigReq(uint8_t Slave, uint16_t SmaIdx)
{
	int32_t nret;
    PDO_CONFIG_HEAD *pTxCmd = (PDO_CONFIG_HEAD *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_PDO_CONFIG_REQ;
	pCmd->Head.u16Size = sizeof(PDO_CONFIG_HEAD);
	pCmd->Head.u8Idx++;
	pTxCmd->Slave = Slave;
	pTxCmd->SmaIdx = SmaIdx;
	nret = EcmCmdTransceiver_WaitAyncDone(1000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_EcatPdoConfigGet(PDO_CONFIG_HEAD *pBuf)
{
	int32_t nret;
	//uint8_t IdxCheck;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_PDO_CONFIG_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	if(nret == 1){
		memcpy(pBuf,pRet->Data,pRet->Head.u16Size);
	}
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_EcatSdoReq(uint8_t OP, \
		uint8_t Slave, \
		uint16_t Index, \
		uint8_t SubIndex, \
		uint16_t size, \
		int32_t Timeout, \
		uint8_t *Data)
{
	int32_t nret;
	SDO_CMD_HEAD *pSdoCmd = (SDO_CMD_HEAD *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_SDO_REQ;
	pCmd->Head.u8Idx++;
	if(OP == ECM_SDO_OP_WR){
		pCmd->Head.u16Size = 12+size;
		memcpy(pSdoCmd->Data,Data,size);
	}else{
		pCmd->Head.u16Size = 12;
	}
	//pCmd->Head.u8Ctrl = 0;
	pSdoCmd->OP = OP;
	pSdoCmd->Slave = Slave;
	pSdoCmd->Index = Index;
	pSdoCmd->SubIndex = SubIndex;
	pSdoCmd->size = size;
	pSdoCmd->Timeout = Timeout;
	pSdoCmd->CA = 0;
	nret = EcmCmdTransceiver_WaitAyncDone(1000,0,0);
	pthread_mutex_unlock(&g_mutex);
	if(nret == -2){
		MSG_DBG("Get SDO abort code\r\n");
	}
	return nret;
}

int32_t ECM_EcatSdoCAReq(uint8_t OP, \
		uint8_t Slave, \
		uint16_t Index, \
		uint8_t SubIndex, \
		uint16_t size, \
		int32_t Timeout, \
		uint8_t *Data)
{
	int32_t nret;
	SDO_CMD_HEAD *pSdoCmd = (SDO_CMD_HEAD *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_SDO_REQ;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Ctrl = 0;
	pSdoCmd->OP = OP;
	pSdoCmd->Slave = Slave;
	pSdoCmd->Index = Index;
	pSdoCmd->SubIndex = SubIndex;
	pSdoCmd->size = size;
	pSdoCmd->Timeout = Timeout;
	pSdoCmd->CA = 1;
	if(OP == ECM_SDO_OP_WR){
		pCmd->Head.u16Size = 12+size;
		memcpy(pSdoCmd->Data,Data,size);
	}else{
		pCmd->Head.u16Size = 12;
	}
	nret = EcmCmdTransceiver_WaitAyncDone(1000,0,0);
	pthread_mutex_unlock(&g_mutex);
	if(nret == -2){
		MSG_DBG("Get SDO abort code\r\n");
	}
	return nret;
}

int32_t ECM_EcatSdoGet(uint8_t *pBuf)
{
	uint16_t u16Size;
	if(EcmUniversalCmd(ECM_CMD_ECAT_SDO_GET,0,0,0,0,0,NULL,NULL,NULL,&u16Size,pBuf)==1){
		return u16Size;
	}
	return 0;
}

int32_t ECM_EcatSdoWrite(uint8_t Slave, \
		uint16_t Index, \
		uint8_t SubIndex, \
		uint16_t size, \
		int32_t Timeout, \
		uint8_t *Data)
{
	return ECM_EcatSdoReq( ECM_SDO_OP_WR, Slave, Index, SubIndex, size, Timeout, Data);
}

int32_t ECM_EcatSdoRead(uint8_t Slave, \
		uint16_t Index, \
		uint8_t SubIndex, \
		uint16_t size, \
		int32_t Timeout, \
		uint8_t *Data)
{
	int32_t nret = ECM_EcatSdoReq( ECM_SDO_OP_RD, Slave, Index, SubIndex, size, Timeout, Data);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoReq READ error\n");
		return nret;
	}
	return ECM_EcatSdoGet(Data);
}
int32_t ECM_Drv402SM_AdvConfig(uint8_t TblIdx, uint8_t SlvIdx, uint8_t ContrlWordOffset, uint8_t StateWordOffset)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_402_CONFIG_SET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Param = TblIdx;
	pCmd->Head.u8Data[0] = ContrlWordOffset;
	pCmd->Head.u8Data[1] = StateWordOffset;
	pCmd->Head.u8Data[2] = (CIA402_FSM_CTL_ENABLE_MASK | CIA402_FSM_CTL_FAULT_AUTORST_MASK);
	pCmd->Head.u8Data[3] = SlvIdx;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_Drv402SM_Enable(uint8_t TblIdx, uint8_t SlvIdx)
{
	int32_t nret ;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_402_CTL_SET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Param = TblIdx;
	pCmd->Head.u8Data[0] = (CIA402_FSM_CTL_ENABLE_MASK | CIA402_FSM_CTL_FAULT_AUTORST_MASK);
	pCmd->Head.u8Data[1] = 0x5A;
	pCmd->Head.u8Data[2] = TblIdx+1;
	pCmd->Head.u8Data[3] = SlvIdx;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_Drv402SM_Disable(uint8_t TblIdx, uint8_t SlvIdx)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_402_CTL_SET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Param = TblIdx;
	pCmd->Head.u8Data[0] = 0;
	pCmd->Head.u8Data[1] = 0x5A;
	pCmd->Head.u8Data[2] = TblIdx+1;
	pCmd->Head.u8Data[3] = SlvIdx;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_Drv402SM_StateSet(uint8_t TblIdx, uint8_t State)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_402_STATE_SET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Param = TblIdx;
	pCmd->Head.u8Data[0] = State;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_Drv402SM_StateGet(uint8_t TblIdx, uint8_t *pState)
{
	int32_t nret;
	//int32_t i;
	//uint8_t IdxCheck;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_402_STATE_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Param = TblIdx;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	if(nret == 1){
		*pState = pRet->Head.u8Return;
	}
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_Drv402SM_StateCheck(uint8_t TblIdx, uint8_t ExpectState, int32_t TimeOutMS)
{
	int32_t i;
	uint8_t State;
	i=ECM_Drv402SM_StateSet(TblIdx, ExpectState);
	if(i<0){
		return i;
	}
	if(ECM_Drv402SM_StateGet(TblIdx, &State) == 1){
		if((State & CIA402_SW_STATE_MASK) == ExpectState){
			return 1;
		}
	}
	MSG_DBG("(%d) 0x%X 0x%X\r\n",TblIdx,State,ExpectState);
	return 0;
}
int32_t ECM_FifoRxPdoSizeGet()
{
	int32_t nret;
	uint16_t PdoSize = 0;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_PACK_SIZE_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = 0;	//	0:	RX
							//	1:	TX
	nret = EcmCmdTransceiver(1000);
	if(nret == 1){
		memcpy(&PdoSize, pRet->Data, 2);
	}
	pthread_mutex_unlock(&g_mutex);
	return PdoSize;
}
int32_t ECM_FifoTxPdoSizeGet()
{
	int32_t nret;
	uint16_t PdoSize = 0;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_PACK_SIZE_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = 1;	//	0:	RX
							//	1:	TX
	nret = EcmCmdTransceiver(1000);
	if(nret == 1){
		memcpy(&PdoSize, pRet->Data, 2);		
	}
	pthread_mutex_unlock(&g_mutex);
	return PdoSize;
}
uint8_t ECM_EcatPdoDataExchange(uint8_t u8OP, uint8_t *pRxData, uint8_t *pTxData, uint16_t *pu16DataSize)
{
	uint8_t IdxCheck;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_PDO_DATA_OP;
	pCmd->Head.u16Size = *pu16DataSize;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Data[0] = u8OP;
	pCmd->Head.u8Param = 0;
	if((u8OP & ECM_PDO_WR_OP) == ECM_PDO_WR_OP){
		memcpy(pCmd->Data, pRxData, pCmd->Head.u16Size);
	}
	if(SpiDataExchange(&IdxCheck, 0) == 1) {
		if (pRet->Head.u8Cmd == ECM_CMD_ECAT_PDO_DATA_OP) {
			if ((pRet->Head.u8Return & ECM_PDO_RD_OP) == ECM_PDO_RD_OP) {
				memcpy(pTxData, pRet->Data, pRet->Head.u16Size);
				*pu16DataSize = pRet->Head.u16Size;
			}
			pthread_mutex_unlock(&g_mutex);
			return pRet->Head.u8Return;
		}else{
			pthread_mutex_unlock(&g_mutex);
			return ECM_PDO_WR_OP;
		}
	}
	pthread_mutex_unlock(&g_mutex);
	return 0;
}
int32_t ECM_EcatPdoFifoIsFull(uint8_t u8FifoThreshold)
{
	// Notice : FIFO count update has two times delay
	if(pRet->Head.u8RxFifoCnt >= u8FifoThreshold-2){
		return 1;// FIFO count threshold reached
	}else{
		return 0;
	}
}
int32_t ECM_EcatPdoFifoDataExchange(uint8_t u8FifoThreshold, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pu8RxPdoFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt)
{
	// Notice : FIFO count update has two times delay
	pthread_mutex_lock(&g_mutex);
	if(pRet->Head.u8RxFifoCnt >= u8FifoThreshold-2){
		return -2;// FIFO count threshold reached
	}
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_PDO_DATA_FIFO_OP;
	pCmd->Head.u16Size = u16DataSize;
	pCmd->Head.u8Param = 1;
	pCmd->Head.u8Data[0] = (ECM_FIFO_WR | ECM_FIFO_RD);
	pCmd->Head.u8Idx++;
	memcpy(pCmd->Data, pRxData, pCmd->Head.u16Size);
	if(SpiDataExchange(0,0) <= 0){
		pthread_mutex_unlock(&g_mutex);
		return -1;//CRC error
	}
	if(pu8RxPdoFifoCnt)
		*pu8RxPdoFifoCnt=pRet->Head.u8RxFifoCnt;
	if(CrcErrCnt)
		*CrcErrCnt = pRet->Head.u8CrcErrCnt;
	if(WkcErrCnt)
		*WkcErrCnt = pRet->Head.u8WkcErrCnt;
	if(pRet->Head.u8Cmd == ECM_CMD_ECAT_PDO_DATA_FIFO_OP){
		if(pRet->Head.u8Return & ECM_FIFO_RD){
			if(pRet->Head.u16Size){
				memcpy(pTxData, pRet->Data, pRet->Head.u16Size);
			}else{
				pthread_mutex_unlock(&g_mutex);
				return -4;
			}
			pthread_mutex_unlock(&g_mutex);
			return pRet->Head.u16Size;
		}
		if(pRet->Head.u8Return & 0x80){
			pthread_mutex_unlock(&g_mutex);
			MSG_DBG("FifoPdo return 0x%X\r\n",pRet->Head.u8Return);
			return 0;
		}
	}else{
		pthread_mutex_unlock(&g_mutex);
		return -3;
	}
	pthread_mutex_unlock(&g_mutex);
	return -6;
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
int32_t ECM_EcatPdoFifoDataExchangeAdv(uint8_t u8Op, uint8_t u8Cnt, uint8_t *pRxData, uint8_t *pTxData, uint16_t u16DataSize, uint8_t *pu8RxPdoFifoCnt, uint8_t *CrcErrCnt, uint8_t *WkcErrCnt, uint8_t *IsSlvAlive)
{
	static uint8_t u8LastOp=ECM_FIFO_WR;
	uint8_t u8RetOp=0;
	uint32_t u32TargetPos;
	//pthread_mutex_lock(&g_mutex);
	g_pFifoCmd->Head.u8Cmd = ECM_CMD_ECAT_PDO_DATA_FIFO_OP;
	g_pFifoCmd->Head.u16Size = u8Cnt*u16DataSize;
	g_pFifoCmd->Head.u8Param = u8Cnt;
	g_pFifoCmd->Head.u8Data[0] = u8Op;
	g_pFifoCmd->Head.u8Idx++;
	if(u8Op & ECM_FIFO_WR){
		if (pRxData) {
			memcpy(g_pFifoCmd->Data, pRxData, g_pFifoCmd->Head.u16Size);

		}
	}
	//
	if(SpiFifoDataExchange(0,0) <= 0){
		u8LastOp = u8Op;
		//pthread_mutex_unlock(&g_mutex);
		return -1;//CRC error
	}
	
	u32TargetPos = *(uint32_t*)&g_pFifoCmd->Data[28];		//MSG_DBG("Driver %d: Target Pos:%04X(%d), \n", 3, u32TargetPos, u32TargetPos);								

	if(pu8RxPdoFifoCnt){
		if(u8Op & ECM_FIFO_WR){
			*pu8RxPdoFifoCnt = (pRet->Head.u8RxFifoCnt+u8Cnt);
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
						memcpy(pTxData, pRet->Data, pRet->Head.u16Size);
					}
					u8RetOp |= 1;
				}else{
					MSG_DBG("Zero size - check SPI idle time(0x%X)\r\n",pRet->Head.u8ErrorStatus);
				}
			}
			if((u8LastOp & ECM_FIFO_WR) == (pRet->Head.u8Return & ECM_FIFO_WR)){
				u8RetOp |= 2;
			}
		}
	}
	u8LastOp = u8Op;
	//pthread_mutex_unlock(&g_mutex);
	return u8RetOp;
}
int32_t ECM_EcatEepromReq(
		uint16_t OP, \
		uint16_t slave, \
		uint16_t eeproma, \
		uint16_t data, \
		uint32_t timeout)
{
	int32_t nret ;
	ECM_EEPROM_REQ_T *pEepromReq = (ECM_EEPROM_REQ_T *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_EEPROM_REQ;
	pCmd->Head.u8Idx++;
	pEepromReq->OP = OP;
	pEepromReq->slave = slave;
	pEepromReq->eeproma = eeproma;
	pEepromReq->data = data;
	pEepromReq->timeout = timeout;
	pCmd->Head.u16Size = sizeof(ECM_EEPROM_REQ_T);
	nret = EcmCmdTransceiver_WaitAyncDone(timeout+100, NULL, NULL);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_EcatEepromGet(uint64_t *pu64Data)
{
	int32_t nret;
	uint16_t u16DataSize=0;
	if(ECM_WaitAsyncDone(1000) == 0)
			return 0;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_EEPROM_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver_WaitAyncDone(1000,&u16DataSize,(uint8_t *)pu64Data);
	pthread_mutex_unlock(&g_mutex);
	if(nret == -2){
		MSG_DBG("Get SDO abort code\r\n");
	}
	return nret;
}
int32_t ECM_GetPDOConfig(int32_t Slave, int32_t SmaIdx, PDO_CONFIG_HEAD *pPdoConfigBuf)
{
	int32_t nret = ECM_EcatPdoConfigReq(Slave, SmaIdx);
	if(nret <= 0){
		return 0;
	}
	nret = ECM_EcatPdoConfigGet(pPdoConfigBuf);
	if(nret <= 0){
		return 0;
	}
	return 1;
}
int32_t ECM_ShowPDOConfig(int32_t Slave, int32_t SmaIdx)
{
	int32_t i=0,j=0,k=0;
	PDO_CONFIG_HEAD PdoConfigBuf;
	int32_t nret = ECM_GetPDOConfig(Slave, SmaIdx, &PdoConfigBuf);
	if(nret <= 0){
		return 0;
	}
	MSG_DBG("(%d) 0x%X : \r\n",Slave, SmaIdx);
	for(i=0;i<PdoConfigBuf.PDOCnt;i++){
		MSG_DBG("PDO%d - MapIdx(0x%X)\r\n", i, PdoConfigBuf.MapIdx[i]);
		if (i)
			k += PdoConfigBuf.ObjsCnt[i - 1];
		else
			k = 0;
		for(j=0; j<PdoConfigBuf.ObjsCnt[i]; j++){
			MSG_DBG("\t0x%04X%02X%02X\r\n", PdoConfigBuf.Table[k+j].u16Idx, PdoConfigBuf.Table[k + j].u8SubIdx, PdoConfigBuf.Table[k + j].u8BitSize);
		}
	}
	return 1;
}

int32_t ECM_EcatDatagramReq(
        ecm_datagram_commad_t cmd,
		uint16_t position,
		uint16_t offset,
        uint32_t logicalAddress,
		uint16_t length,
		int32_t Timeout,
		uint8_t *Data)
{
	int nret ;
	EC_RAW_API_PARAM_H *pDatagramCmd = (EC_RAW_API_PARAM_H *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_RAW_ECAT_FUNC_REQ;
	pCmd->Head.u8Idx++;
    pCmd->Head.u16Size = sizeof(EC_RAW_API_PARAM_H) - 256 + length;
	pDatagramCmd->OP = cmd;
	pDatagramCmd->ADO = offset;
	pDatagramCmd->ADP = position;
	pDatagramCmd->LogAdr = logicalAddress;
	pDatagramCmd->length = length;
	pDatagramCmd->timeout = Timeout;
    memcpy(pDatagramCmd->data,Data,length);
	nret = EcmCmdTransceiver_WaitAyncDone(1000,0,0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_EcatDatagramGet(uint8_t *pBuf)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_RAW_ECAT_FUNC_GET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	if(nret == 1){
		memcpy(pBuf, pRet->Data, pRet->Head.u16Size);
	}
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_SlaveInfoGet(uint8_t slave, uint8_t info, uint8_t *pBuf)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_SLV_INFO_GET;
    pCmd->Head.u8Param = slave;
	pCmd->Head.u16Size = 0;
    pCmd->Head.u8Data[0] = info;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	if(nret == 1){
		memcpy(pBuf, pRet->Data, pRet->Head.u16Size);
	}
	pthread_mutex_unlock(&g_mutex);
	return nret;
}


int32_t ECM_SetFIFOExtDataSize(uint8_t nByteSize)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_EXPDO_DATA_CNT_SET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Param = nByteSize;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_SetEcatIntEnable(uint32_t u32CompIntEnable, uint8_t u8GpioIntEnable, uint8_t u8PeripIntEnable, uint8_t u8INTActiveHigh)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_INT_SET_ENABLE;
	pCmd->Head.u16Size = 6;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = (u8INTActiveHigh & 3);
	memcpy( pCmd->Data, &u32CompIntEnable, 4);
	pCmd->Data[4] = u8GpioIntEnable;
	pCmd->Data[5] = u8PeripIntEnable;
  pCmd->Head.u32CompIntClr = (uint32_t)((uint32_t)1<<31);	
	nret = EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}


int32_t ECM_GetEcatIntEnable(uint32_t *pu32CompIntEnable, uint8_t *pu8GpioIntEnable, uint8_t *pu8PeripIntEnable, uint8_t *pu8INTActiveHigh)
{
	uint8_t pBuf[6];
	uint16_t u16Size = 0;
	if(EcmUniversalCmd(ECM_CMD_ECAT_INT_GET_ENABLE,0,0,0,0,0,pu8INTActiveHigh,NULL,NULL,&u16Size,pBuf)==1){
		if(u16Size == 6){
			memcpy(pu32CompIntEnable,pBuf,4);
			pu8GpioIntEnable[0] = pBuf[4];
			pu8PeripIntEnable[0] = pBuf[5];
		}
	}
	return u16Size;
}

int32_t ECM_FifoClear(void){
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_FIFO_CLR_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(1000);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
/*
 * Structure EC_RAW_API_PARAM_H is big, so please check SPI data size first.
 *
 * */
int32_t ECM_EcatRawCmdReq(uint16_t OP,  \
		uint16_t length, \
		uint16_t ADP, \
		uint16_t ADO, \
		uint32_t LogAdr, \
		int32_t timeout, \
		uint8_t *data)
{
	int32_t nret;
	EC_RAW_API_PARAM_H *pRawCmd = (EC_RAW_API_PARAM_H *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_RAW_ECAT_FUNC_REQ;
	pCmd->Head.u8Idx++;
	pCmd->Head.u16Size = sizeof(EC_RAW_API_PARAM_H);
	memcpy(pRawCmd->data,data,length);
	pRawCmd->OP = OP;
	pRawCmd->length = length;
	pRawCmd->ADP = ADP;
	pRawCmd->ADO = ADO;
	pRawCmd->LogAdr = LogAdr;
	pRawCmd->timeout = timeout;
	nret = EcmCmdTransceiver_WaitAyncDone(10000,0,0);
	pthread_mutex_unlock(&g_mutex);
	if(nret == -2){
		MSG_DBG("ECM_EcatRawCmdReq error\r\n");
	}
	return nret;
}
uint16_t ECM_EcatRawCmdGet(uint8_t *pBuf)
{
	uint16_t u16Size;
	if(EcmUniversalCmd(ECM_CMD_RAW_ECAT_FUNC_GET,0,0,0,0,0,NULL,NULL,NULL,&u16Size,pBuf)==1){
		return u16Size;
	}
	return 0;
}
uint16_t ECM_EcatRawCmdRead(uint16_t OP,  \
		uint16_t length, \
		uint16_t ADP, \
		uint16_t ADO, \
		uint32_t LogAdr, \
		int32_t timeout, \
		uint8_t *data)
{
	int32_t nret = ECM_EcatRawCmdReq(OP,length,ADP,ADO,LogAdr,timeout,data);
	if(nret <= 0){
		MSG_DBG("ECM_EcatRawCmdRead REQ error\n");
		return 0;
	}
	return ECM_EcatRawCmdGet(data);
}
int32_t ECM_EcatWkcErrorMaxSet(uint8_t u8Max)
{
	return EcmUniversalCmd(ECM_CMD_ECAT_WKC_CONTI_ERR_MAX_SET,u8Max,0,0,0,0,NULL,NULL,NULL,NULL,NULL);
}
int32_t ECM_EcatWkcErrorMaxGet(uint8_t *pu8Max)
{
	return EcmUniversalCmd(ECM_CMD_ECAT_WKC_CONTI_ERR_MAX_GET,0,0,0,0,0,pu8Max,NULL,NULL,NULL,NULL);
}
int32_t ECM_GetLogTime(uint8_t u8Timer, uint8_t u8Idx, uint8_t u8Type)
{
	int32_t n32Data;
	uint16_t u16DataLength;
	int32_t nret;
	nret = EcmUniversalCmd(ECM_CMD_GET_TIMER_TIME,u8Timer,u8Idx,u8Type,0,0,NULL,NULL,NULL,&u16DataLength,(uint8_t *)&n32Data);
	MSG_DBG("nret = %d, Len = %d, Data = %d\r\n",nret,u16DataLength,n32Data);
	return n32Data;
}
int32_t ECM_ShowReturnField()
{
	MSG_DBG("ECM_ShowReturnField\n");
	MSG_DBG("u8Idx %d\n",pRet->Head.u8Idx);
	MSG_DBG("u8Cmd %d\n",pRet->Head.u8Cmd);
	MSG_DBG("u16Size %d\n",pRet->Head.u16Size);
	MSG_DBG("u8CrcErrCnt 0x%X\n",pRet->Head.u8CrcErrCnt);
	MSG_DBG("u8WkcErrCnt0x%X\n",pRet->Head.u8WkcErrCnt);
	MSG_DBG("u8EcState 0x%X\n",pRet->Head.u8EcState);
	MSG_DBG("u8ErrorStatus 0x%X\n",pRet->Head.u8ErrorStatus);
	MSG_DBG("u8Status 0x%X\n",pRet->Head.u8Status);
	MSG_DBG("u8Return 0x%X\n",pRet->Head.u8Return);
	MSG_DBG("u8RxFifoCnt %d\n",pRet->Head.u8RxFifoCnt);
	MSG_DBG("u8TxFifoCnt %d\n",pRet->Head.u8TxFifoCnt);
	MSG_DBG("u16Size %d\n",pRet->Head.u16Size);
	return 0;
}
int32_t ECM_ShowCmdField()
{
	MSG_DBG("ECM_ShowCmdFeild\n");
	MSG_DBG("u8Idx %d\n",pCmd->Head.u8Idx);
	MSG_DBG("u8Cmd %d\n",pCmd->Head.u8Cmd);
	MSG_DBG("u8Param 0x%X\n",pCmd->Head.u8Param);
	MSG_DBG("u8Data0 0x%X\n", pCmd->Head.u8Data[0]);
	MSG_DBG("u16Size %d\n",pCmd->Head.u16Size);
	MSG_DBG("u16Reserve 0x%X\n",pCmd->Head.u16Reserve);
	MSG_DBG("u8Ctrl 0x%X\n",pCmd->Head.u8Ctrl);
	return 0;
}
int32_t ECM_EcatSdoSetPdoConfig(PDO_CONFIG_HEAD *pConfigData)
{
	int j,k,l,nret;
	uint8_t u8Zero=0;
	nret = ECM_EcatSdoWrite(pConfigData->Slave, pConfigData->SmaIdx, 0, 1, 2000000000, (uint8_t *)&u8Zero);
	if(nret <= 0){
		return -1;
	}
	for(j = 0; j < pConfigData->PDOCnt; j++){
		// clear pdo count
		nret = ECM_EcatSdoWrite(pConfigData->Slave, pConfigData->MapIdx[j], 0, 1, 2000000000, (uint8_t *)&u8Zero);
		if (nret <= 0) {
			return -2;
		}
		if (j) {
			if (pConfigData->ObjsCnt[j - 1] == 0) {
				return -3;
			}
			l += pConfigData->ObjsCnt[j - 1];
		}
		else {
			l = 0;
		}
		for (k = 0; k < pConfigData->ObjsCnt[j]; k++) {
			MSG_DBG("\t(%d) 0x%X\n", k, *(uint32_t*)&pConfigData->Table[l+k]);
			nret = ECM_EcatSdoWrite(pConfigData->Slave, pConfigData->MapIdx[j], k + 1, 4, 2000000000, (uint8_t *)&(pConfigData->Table[l+k]));
			if (nret <= 0) {
				return -1;
			}
		}
		if(pConfigData->ObjsCnt[j]) {
			nret = ECM_EcatSdoWrite(pConfigData->Slave, pConfigData->MapIdx[j], 0, 1, 2000000000, (uint8_t *)&(pConfigData->ObjsCnt[j]));
			if(nret <= 0){
				return -1;
			}
		}
		nret = ECM_EcatSdoWrite(pConfigData->Slave, pConfigData->SmaIdx, j+1, 2, 2000000000, (uint8_t *)&(pConfigData->MapIdx[j]));
		if(nret <= 0){
			return -1;
		}
	}
	nret = ECM_EcatSdoWrite(pConfigData->Slave, pConfigData->SmaIdx, 0, 1, 2000000000, (uint8_t *)&(pConfigData->PDOCnt));
	if(nret <= 0){
		return -1;
	}
	return 1;
}
/*int32_t ECM_EcatSdoSetPdoConfig(uint8_t Slave, PDO_CONFIG_HEAD *pConfigData)
{
	int32_t j,k,nret;
	uint8_t u8Zero=0;
	MSG_DBG("\r\n========== 0x%X ==========\r\n",pConfigData->SmaIdx);
	nret = ECM_EcatSdoWrite(Slave, pConfigData->SmaIdx, 0, 1, 2000000000, (uint8_t *)&u8Zero);
	if(nret <= 0){
		return -1;
	}
	for(j = 0; j < pConfigData->PDOCnt; j++){
		MSG_DBG(" (%d) 0x%X\n",j,pConfigData->MapIdx[j]);
		if(pConfigData->ObjsCnt[j]){
			nret = ECM_EcatSdoWrite(Slave, pConfigData->MapIdx[j], 0, 1, 2000000000, (uint8_t *)&u8Zero);
			if(nret <= 0){
				return -1;
			}
			for(k=0;k<pConfigData->ObjsCnt[j];k++){
				MSG_DBG("    (%d) 0x%X\n",k,pConfigData->Table[j][k]);
				nret = ECM_EcatSdoWrite(Slave, pConfigData->MapIdx[j], k+1, 4, 2000000000, (uint8_t *)&(pConfigData->Table[j][k]));
				if(nret <= 0){
					return -1;
				}
			}
			nret = ECM_EcatSdoWrite(Slave, pConfigData->MapIdx[j], 0, 1, 2000000000, (uint8_t *)&(pConfigData->ObjsCnt[j]));
			if(nret <= 0){
				return -1;
			}
		}
		nret = ECM_EcatSdoWrite(Slave, pConfigData->SmaIdx, j+1, 2, 2000000000, (uint8_t *)&(pConfigData->MapIdx[j]));
		if(nret <= 0){
			return -1;
		}
	}
	nret = ECM_EcatSdoWrite(Slave, pConfigData->SmaIdx, 0, 1, 2000000000, (uint8_t *)&(pConfigData->PDOCnt));
	if(nret <= 0){
		return -1;
	}
	return 1;
}*/
int32_t ECM_WarmReset(void)
{
	if (EcmUniversalCmd(127, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL) == 1) {
		return 0;
	}
	return 0;
}
int32_t  ECM_EcatConfigDC(void)
{
	int32_t nret ;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_INIT_DC_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	//pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	nret = EcmCmdTransceiver_WaitAyncDone(1000000, 0, 0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_EcatConfigMap(void)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_CONFIG_MAP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	//pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	nret = EcmCmdTransceiver_WaitAyncDone(1000000, 0, 0);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_EcatConfigSM(uint8_t slave, uint8_t nSM, uint16_t StartAddr, uint16_t SMlength, uint8_t ControlReg, uint8_t Activate)
{
	int32_t nret ;
	ECM_CONFIG_SM_T *pConfigSmParam = (ECM_CONFIG_SM_T *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pConfigSmParam->Activate=Activate;
	pConfigSmParam->ControlReg=ControlReg;
	pConfigSmParam->SMlength=SMlength;
	pConfigSmParam->StartAddr=StartAddr;
	pConfigSmParam->nSM=nSM;
	pConfigSmParam->slave=slave;
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_CONFIG_SM;
	pCmd->Head.u16Size = sizeof(ECM_CONFIG_SM_T);
	pCmd->Head.u8Idx++;
	//pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	nret = EcmCmdTransceiver_WaitAyncDone(1000000, 0, 0);
	pthread_mutex_unlock(&g_mutex);
	return nret;

}
int32_t ECM_EcatConfigFMMU(uint8_t slave, uint8_t FMMU0func, uint8_t FMMU1func, uint8_t FMMU2func, uint8_t FMMU3func)
{
	int32_t nret;
	ECM_CONFIG_FMMU_T *pConfigFmmuParam = (ECM_CONFIG_FMMU_T *)pCmd->Data;
	pthread_mutex_lock(&g_mutex);
	pConfigFmmuParam->FMMU0func=FMMU0func;
	pConfigFmmuParam->FMMU1func=FMMU1func;
	pConfigFmmuParam->FMMU2func=FMMU2func;
	pConfigFmmuParam->FMMU3func=FMMU3func;
	pConfigFmmuParam->slave=slave;
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_CONFIG_FMMU;
	pCmd->Head.u16Size = sizeof(ECM_CONFIG_FMMU_T);
	pCmd->Head.u8Idx++;
	//pCmd->Head.u8Ctrl |= ECM_CTL_CLR_ALL_ERR_MASK;
	nret = EcmCmdTransceiver_WaitAyncDone(1000000, 0, 0);
	pthread_mutex_unlock(&g_mutex);
	return nret;

}
int32_t ECM_Reset()
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_WARM_RESET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = SpiDataExchange(0, 0);
	pthread_mutex_unlock(&g_mutex);
	if(nret == 1){
		UserDelay(1000000);//1s
	}else if(nret < 0){
		return 0;
	}
	return 1;
}
int32_t ECM_SkipNetInit()
{
	int32_t nret ;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ASYNCCMD_RESET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = 2;
	nret = EcmCmdTransceiver(100);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_ResetPhy()
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_EMAC_RESET_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = 1;
	nret = EcmCmdTransceiver(100);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_ManualEmacInit()
{
	int32_t nret ;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_EMAC_INIT_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	nret = EcmCmdTransceiver(100);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_ForceClearAsyncBusy()
{
	int32_t nret ;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ASYNCCMD_RESET;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = 1;
	nret = EcmCmdTransceiver(100);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}

int32_t ECM_RtaInit(uint8_t u8RuleCnt, uint8_t u8BufSize)
{
	return EcmUniversalCmd(	ECM_CMD_ECAT_RTA_INIT, 0, u8RuleCnt, u8BufSize, 0, 0, 0, 0, 0, 0, 0);
}
void ECM_RtaClose()
{
	EcmUniversalCmd(ECM_CMD_ECAT_RTA_CLOSE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);	
}
void ECM_RtaSetEnable(uint8_t u8Enable)
{	
	EcmUniversalCmd(ECM_CMD_ECAT_RTA_SETENABLE, u8Enable, 0, 0, 0, 0, 0, 0, 0, 0, 0);	
}
int32_t ECM_RtaGetRunFlag(uint8_t *pu8RtaRuning)
{
	return EcmUniversalCmd(ECM_CMD_ECAT_RTA_GETRUNFLAG, 0, 0, 0, 0, 0, pu8RtaRuning, 0, 0, 0, 0);
}
int32_t ECM_RtaSetBuf(uint8_t u8Offset, uint8_t u8Size, uint8_t *pBuf)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_RTA_SET_BUF;
	pCmd->Head.u16Size = u8Size;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Data[0] = u8Offset;//Offset(Bytes)
	pCmd->Head.u8Data[1] = u8Size;
	memcpy(pCmd->Data, pBuf, u8Size);
	nret = EcmCmdTransceiver(100);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_RtaGetBuf(uint8_t u8Offset, uint8_t u8Size, uint8_t *pBuf, uint8_t *pCondition)
{
	int32_t nret;
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_RTA_GETRUNFLAG;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Param = 3;
	pCmd->Head.u8Data[0] = u8Offset;//Offset(Bytes)
	pCmd->Head.u8Data[1] = u8Size;
	nret = EcmCmdTransceiver(100);
	if(nret == 1){
		memcpy(pBuf, pRet->Data, u8Size);
		*pCondition = pRet->Head.u8Return;
	}
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int32_t ECM_RtaSetRule(uint8_t u8Idx, uint8_t u8Cnt, RTA_RULE *pRule)
{
	int32_t nret;
	uint8_t u8Size = u8Cnt*sizeof(RTA_RULE);
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_ECAT_RTA_SET_RULE;
	pCmd->Head.u16Size = u8Size;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Data[0] = u8Idx;//Offset(Index)
	pCmd->Head.u8Data[1] = u8Cnt;
	memcpy(pCmd->Data, (uint8_t *)pRule, u8Size);
	nret = EcmCmdTransceiver(100);
	pthread_mutex_unlock(&g_mutex);
	return nret;
}
int ECM_GetNetLinkPin(int *pPinStatus)
{
	pthread_mutex_lock(&g_mutex);
	pCmd->Head.u8Cmd = ECM_CMD_INFO_UPDATE_OP;
	pCmd->Head.u16Size = 0;
	pCmd->Head.u8Idx++;
	pCmd->Head.u8Ctrl &= ~ECM_CTL_UPDATE_EC_STATE_MASK;
	if (SpiDataExchange(0, 0) == 1) {
		if (pRet->Head.u8ErrorStatus & ECM_ERR_LINK_PIN_MASK) {
			*pPinStatus = 1;
		}
		else {
			*pPinStatus = 0;
		}
		pthread_mutex_unlock(&g_mutex);
		return 1;
	}
	pthread_mutex_unlock(&g_mutex);
	return 0;
}
int ECM_SetSpiTransIdleTime(int TimeUS)
{
	g_nSpiIdleTime = TimeUS;
	return g_nSpiIdleTime;
}

int ECM_GetSpiTransIdleTime(int TimeUS)
{
	return g_nSpiIdleTime;
}
//	(C) COPYRIGHT 2020 NEXTW Technology Corp.
