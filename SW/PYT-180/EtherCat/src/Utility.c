/******************************************************************************
 *	File	:	Utility.c
 *	Version :	1.520
 *	Date	:	2021/11/23
 *	Author	:	XFORCE
 *
 * @copyright (C) 2021 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/

#include "EcmUsrDriver.h"
#include "platform.h"
#include "Utility.h"
#include "PdoDefine.h"
#include <stdlib.h>

#ifdef __GNUC__
#include <unistd.h>
#endif // __GNUC__

#include "app_config.h"
#include "ec_master.h"

uint16_t u16EEPROM_ZERO[18] = {	0x0029, 0x0010,
		0x1000, 0x0000, 0x0026, 0x0101,
		0x1080, 0x0000, 0x0022, 0x0201,
		0x1100, 0x0000, 0x0064, 0x0301,
		0x1400, 0x0000, 0x0020, 0x0401 };
uint16_t u16EEPROM[18] = {	0x0029, 0x0010,
		0x1000, 0x0080, 0x0026, 0x0101,
		0x1080, 0x0080, 0x0022, 0x0201,
		0x1100, 0x0000, 0x0064, 0x0301,
		0x1400, 0x0000, 0x0020, 0x0401};

/*     V
 *     |
 *     |   _______
 *     |  /       \
 *     | /         \
 *___T_|/           \
 *     |             \            /
 *     |              \          /
 *     |               \________/
 *     |
*/
int32_t CalVel(double dfAccStep, int32_t nFeedSpeed, int32_t nCostTime)
{
	static int32_t nVel=0, nDir=1, ConstTime=0, StopTime=0;//, nAcc = 0;
	static double dfVel=0;
	if(StopTime){
		ConstTime = 0;
		nVel = 0;
		StopTime--;
	}else{
		if(ConstTime){
			ConstTime--;
		}else{
			dfVel += nDir*dfAccStep;
			nVel = dfVel;
		}
		if(nDir*dfVel < dfAccStep){
			StopTime = nCostTime;
		}
		if(nDir*nVel >= nFeedSpeed){
			nDir = -1*nDir;
			ConstTime = nCostTime;
		}
	}
	return nVel;
}
int32_t CalIncPos(int32_t nAccStep, int32_t nAccStepDivi, int32_t nAccTime, int32_t nCostTime, int32_t nStopTime)
{
	static int32_t nRunTime=0, nDir=1, nIncPos=0, nAccCnt=0;
	int32_t nAcc=0;
	if(nRunTime < nAccTime){//ACC
		if(nAccCnt == (nAccStepDivi-1)){
			nAcc=nAccStep;
			nAccCnt = 0;
		}else{
			nAccCnt++;
		}
		nIncPos += (nDir*nAcc);
	}else if(nRunTime >= nAccTime && nRunTime < (nAccTime+nCostTime)){//CONST
		nAccCnt = 0;
	}else if(nRunTime >= (nAccTime+nCostTime) && nRunTime < (2*nAccTime+nCostTime)){//DEC
		if(nAccCnt == (nAccStepDivi-1)){
			nAcc=nAccStep;
			nAccCnt = 0;
		}else{
			nAccCnt++;
		}
		nIncPos -= (nDir*nAcc);
	}else if(nRunTime >= (2*nAccTime+nCostTime) && nRunTime < (2*nAccTime+nCostTime+nStopTime)){//STOP
		nAccCnt = 0;
		nIncPos = 0;
	}
	if(nRunTime == (2*nAccTime+nCostTime+nStopTime)){
		nDir = -1*nDir;
		nRunTime = 0;
	}else{
		nRunTime++;
	}
	return nIncPos;
}
int32_t SetDriverCmdOpMode(int32_t nSlvBegin, int32_t nSlvEnd, uint8_t u8Mode, int32_t nAxisPerSlv)
{
	uint8_t u8OpMode;
	int32_t i,j,nret;
	//	SDO example : use SDO write to set driver mode
	for(i=nSlvBegin;i<=nSlvEnd;i++){
		// Send write request
		for(j=0;j<nAxisPerSlv;j++){
			u8OpMode = u8Mode;
			nret = ECM_EcatSdoWrite(i, 0x6060+(j*0x800), 0, 1, 2000000000, &u8OpMode);
			if(nret <= 0){
				MSG_DBG("(%d:%d) ECM_EcatSdoWrite error (%d)\n", i, j, nret);
				return -1;
			}
			u8OpMode = 0;
			// Send read request and get response
			nret = ECM_EcatSdoRead(i, 0x6060+(j*0x800), 0, 1, 2000000000, &u8OpMode);
			if(nret <= 0){
				MSG_DBG("(%d:%d) ECM_EcatSdoRead error (%d)\n", i, j, nret);
				return -2;
			}
			if(u8OpMode != u8Mode){
				MSG_DBG("(%d:%d) OpMode is not correct (%d)\n", i, j,u8OpMode);
				return -3;
			}
		}
	}
	return 1;
}
/*int32_t SetPdoConfTbl(PDO_CONFIG_HEAD *pConfig, uint8_t u8PdoIdx, uint8_t u8TblIdx, uint16_t u16Idx, uint8_t u8SubIdx, uint8_t u8BitSize)
{
	pConfig->Table[u8PdoIdx][u8TblIdx].u16Idx = u16Idx;
	pConfig->Table[u8PdoIdx][u8TblIdx].u8SubIdx = u8SubIdx;
	pConfig->Table[u8PdoIdx][u8TblIdx].u8BitSize = u8BitSize;
	return 1;
}
*/
int32_t SetPdoConfTbl(PDO_CONFIG_HEAD *pConfig, uint8_t u8PdoIdx, uint8_t u8TblIdx, uint16_t u16Idx, uint8_t u8SubIdx, uint8_t u8BitSize)
{
	int32_t nObjCnt = 0;
	int32_t i;
	for ( i = 0; i < u8PdoIdx; i++) {
		if (pConfig->ObjsCnt[i] == 0) {
			return -1;
		}
		nObjCnt += pConfig->ObjsCnt[i];
	}
	pConfig->Table[nObjCnt + u8TblIdx].u16Idx = u16Idx;
	pConfig->Table[nObjCnt + u8TblIdx].u8SubIdx = u8SubIdx;
	pConfig->Table[nObjCnt + u8TblIdx].u8BitSize = u8BitSize;
	return 1;
}

int32_t SdoShowPdoConfig(int32_t nSlvB, int32_t nSlvE, uint16_t SmaIdx)
{
	int32_t i,j,k,nret;
	uint8_t u8PdoCnt=0;
	uint16_t u16PdoIdx[4];
	uint8_t u8PdoObjCnt[4];
	uint32_t u32PdoObj[4][16];
	MSG_DBG("\r\n========== 0x%X ==========\r\n",SmaIdx);
	for(i = nSlvB; i <= nSlvE; i++){
		nret = ECM_EcatSdoRead(i, SmaIdx, 0, sizeof(u8PdoCnt), 2000000000, &u8PdoCnt);
		if(nret <= 0){
			return -1;
		}
		MSG_DBG("Slave(%d)\r\n",i);
		for(j = 0; j < u8PdoCnt; j++){
			nret = ECM_EcatSdoRead(i, SmaIdx, j+1, sizeof(u16PdoIdx[j]), 2000000000, (uint8_t *)&u16PdoIdx[j]);
			if(nret <= 0){
				return -1;
			}
			nret = ECM_EcatSdoRead(i, u16PdoIdx[j], 0, sizeof(u8PdoObjCnt[j]), 2000000000, &u8PdoObjCnt[j]);
			if(nret <= 0){
				return -1;
			}
			MSG_DBG("PdoIdx(0x%X)\r\n",u16PdoIdx[j]);
			for(k=0;k<u8PdoObjCnt[j];k++){
				nret = ECM_EcatSdoRead(i, u16PdoIdx[j], k+1, sizeof(u32PdoObj[j][k]), 2000000000, (uint8_t *)&u32PdoObj[j][k]);
				if(nret <= 0){
					return -1;
				}
				MSG_DBG("\t0x%X\r\n",u32PdoObj[j][k]);
			}
		}
	}
	return 1;
}

int32_t ConfigDrive(int32_t nList, int32_t nSlvB, int32_t nSlvE, int32_t nJustAssign, int32_t nPDOCnt , uint16_t RxMapIdx , uint16_t TxMapIdx, int nMode)
{
	int32_t i,nret;
	PDO_CONFIG_HEAD PDOConfig;
	SdoShowPdoConfig(nSlvB, nSlvE, 0x1C12);
	SdoShowPdoConfig(nSlvB, nSlvE, 0x1C13);

	// RxPDO
	PDOConfig.SmaIdx = 0x1C12;
	PDOConfig.PDOCnt = nPDOCnt;
	for(i=0; i<nPDOCnt; i++){
		if(nJustAssign){
			PDOConfig.MapIdx[i] = RxMapIdx+(0x10*i);
			PDOConfig.ObjsCnt[i] = 0;
		}else{
			PDOConfig.MapIdx[i] = RxMapIdx+(0x10*i);
			PDOConfig.ObjsCnt[i] = 2;
			SetPdoConfTbl(&PDOConfig, i, 0, (0x6040+(0x800*i)), 0, 16);
			if((nMode == 9) || (nMode == 3)){			//	CSV PV
				SetPdoConfTbl(&PDOConfig, i, 1, (0x60FF+(0x800*i)), 0, 32);
			}else if((nMode == 10) || (nMode == 4)){	//	CST PT
				SetPdoConfTbl(&PDOConfig, i, 1, (0x6071+(0x800*i)), 0, 16);
			}else{
				SetPdoConfTbl(&PDOConfig, i, 1, (0x607A+(0x800*i)), 0, 32);
			}
		}
	}
	for(i=nSlvB;i<=nSlvE;i++){
		PDOConfig.Slave = i;
		nret=ECM_EcatSdoSetPdoConfig(&PDOConfig);
		if(nret <= 0){
			MSG_DBG("Set RX PDO error\n");
			return -1;
		}
	}
	MSG_DBG("ECM_EcatPdoConfigSet RX pass\r\n");
	// TxPDO
	PDOConfig.SmaIdx = 0x1C13;
	PDOConfig.PDOCnt = nPDOCnt;
	for(i=0; i<nPDOCnt; i++){
		if(nJustAssign){
			PDOConfig.MapIdx[i] = TxMapIdx+(0x10*i);
			PDOConfig.ObjsCnt[i] = 0;
		}else{
			PDOConfig.MapIdx[i] = TxMapIdx+(0x10*i);
			PDOConfig.ObjsCnt[i] = 2;
			SetPdoConfTbl(&PDOConfig, i, 0, (0x6041+(0x800*i)), 0, 16);			
			if((nMode == 9) || (nMode == 3)){			//	CSV PV
				//SetPdoConfTbl(&PDOConfig, i, 1, (0x60FF+(0x800*i)), 0, 32);
				SetPdoConfTbl(&PDOConfig, i, 1, (0x6064+(0x800*i)), 0, 32);
			}else if((nMode == 10) || (nMode == 4)){	//	CST	PT
				SetPdoConfTbl(&PDOConfig, i, 1, (0x6077+(0x800*i)), 0, 16);
			}else{
				SetPdoConfTbl(&PDOConfig, i, 1, (0x6064+(0x800*i)), 0, 32);
			}
		}
	}
	for(i=nSlvB;i<=nSlvE;i++){
		PDOConfig.Slave = i;
		nret=ECM_EcatSdoSetPdoConfig(&PDOConfig);
		if(nret <= 0){
			MSG_DBG("Set TX PDO error\n");
			return -1;
		}
	}
//	nret=ECM_EcatReconfig();
	nret = ECM_EcatConfigMap();
//	nret = ECM_EcatConfigDC();
//	nret = ECM_EcatSetDCSync(0, 0x300, 1000000);
	if( nret < 0 ){
		MSG_DBG("ECM_EcatSetDCSync : %d\n",nret);
		return -1;
	}
	MSG_DBG("ECM_EcatReconfig pass\r\n");
	if(nList){
		SdoShowPdoConfig(nSlvB, nSlvE, 0x1C12);
		SdoShowPdoConfig(nSlvB, nSlvE, 0x1C13);
	}
	return 1;
}


/*
 * Check memory space
 *
 * */
int32_t ECM_CheckMEMSpace(int32_t nPdoCntOnce)
{
	int32_t nret;
	uint8_t u8RxCnt=0,u8TxCnt=0;
	uint16_t u16RxPDOSize=0,u16TxPDOSize=0,u16SpiDataSize=0;
	MSG_DBG("\r\n=====================\r\n");
	MSG_DBG("  Check : Start\r\n");
	MSG_DBG("=====================\r\n");
	//
	nret = ECM_GetSpiDataSize(&u16SpiDataSize);
	if(nret <= 0){
		MSG_DBG("  ERROR : ECM_GetSpiDataSize error\r\n");
		return -1;
	}
	MSG_DBG("  SPI data size : %d bytes\r\n", u16SpiDataSize);
	//	Check RxFIFO
	u16RxPDOSize = ECM_FifoRxPdoSizeGet();
	if(u16RxPDOSize == 0){
		MSG_DBG("  ERROR : ECM_FifoRxPdoSizeGet error\r\n");
		return -2;
	}
	MSG_DBG("  RxPDO size : %d bytes\r\n", u16RxPDOSize);
	if(ECM_GetRxFIFOCnt(&u8RxCnt)==0){
		MSG_DBG("  ERROR : ECM_GetRxFIFOCnt error\r\n");
		return -3;
	}
	MSG_DBG("  RxFIFO MAX. count : %d\r\n", u8RxCnt);
	MSG_DBG("  RxFIFO queue size : %d bytes\r\n", u16RxPDOSize*u8RxCnt);
	if(u16RxPDOSize*nPdoCntOnce > u16SpiDataSize){
		MSG_DBG("  ERROR : RxPDO size bigger than SPI data size(%d > %d)\r\n",u16RxPDOSize*nPdoCntOnce,u16SpiDataSize);
		return -5;
	}
	//	Check TxFIFO
	u16TxPDOSize = ECM_FifoTxPdoSizeGet();
	if(u16TxPDOSize == 0){
		MSG_DBG("  ERROR : ECM_FifoTxPdoSizeGet error\r\n");
		return -2;
	}
	MSG_DBG("  TxPDO size : %d bytes\r\n", u16TxPDOSize);
	if(ECM_GetTxFIFOCnt(&u8TxCnt)==0){
		MSG_DBG("  ERROR : ECM_GetTxFIFOCnt error\r\n");
		return -3;
	}
	MSG_DBG("  TxFIFO MAX. count : %d\r\n", u8TxCnt);
	MSG_DBG("  TxFIFO queue size : %d bytes\r\n", u16TxPDOSize*u8TxCnt);
	if(u16TxPDOSize*nPdoCntOnce > u16SpiDataSize){
		MSG_DBG("  ERROR : TxPDO size bigger than SPI data size(%d > %d)\r\n",u16TxPDOSize*nPdoCntOnce,u16SpiDataSize);
		return -5;
	}
	if(((u16RxPDOSize*u8RxCnt)+(u16TxPDOSize*u8TxCnt)) > FIFO_QUEUE_SIZE){
		MSG_DBG("  ERROR : FIFO size explosion(%d > %d)\r\n", ((u16RxPDOSize*u8RxCnt)+(u16TxPDOSize*u8TxCnt)), FIFO_QUEUE_SIZE);
		return -4;
	}
	MSG_DBG("\r\n=====================\r\n");
	MSG_DBG("  Check : PASS\r\n");
	MSG_DBG("=====================\r\n");
	return 1;
}
int32_t Cia402Control(int32_t nSevoOn , uint16_t u16Sate, uint16_t *u16Ctrol)
{
	int32_t nret=0;
	if(u16Sate & 0x08){
		if(u16Ctrol[0] == 0x80)
			u16Ctrol[0] = 0;
		else
			u16Ctrol[0] = 0x80;
		return 0;
	}
	if(nSevoOn==1){
		switch(u16Sate & 0x6F){
		case CIA402_SW_SWITCHEDONDISABLED:  //0x40
			*u16Ctrol = 0x06;
			break;
		case CIA402_SW_READYTOSWITCHON:		//0x21
			*u16Ctrol = 0x07;
			break;
		case CIA402_SW_SWITCHEDON:			//0x23
			*u16Ctrol = 0x0F;
			break;
		case CIA402_SW_OPERATIONENABLED:	//0x27
			*u16Ctrol = 0x0F;
			nret = 1;
			break;
		default:
			*u16Ctrol = 0x06;
			break;
		}
	}
	return nret;
}
/*	u8OP    : 	Bit7 for call ECM_EcatInit first
 * 			    Bit1 for read operate
 * 			    Bit0 for write operate
 * 	nOffset :   Two bytes address
 * 	nSize	:	Two bytes length
 *
 * */
int32_t CustomizedSII(uint8_t u8OP, int32_t nOffset, int32_t nSize)
{
	int32_t nret,i,rowidx;
	uint64_t u64Data;
	if(u8OP & 0x80){
		ECM_EcatInit(0, 2000000);
	}
	if(u8OP & 2){
		rowidx=0;
		MSG_DBG("\n==============\n");
		for(i=nOffset;i<(nOffset+nSize);i++){
			nret = ECM_EcatEepromReq(ECM_EEPROM_OP_RD, 0, i, 0, 1000000);
			if(nret == 1){
				nret = ECM_EcatEepromGet(&u64Data);
				if(nret == 1){
					if((rowidx%8) == 0){
						MSG_DBG("(%03d) ",i);
					}
					MSG_DBG(" %04X ",(uint16_t)u64Data);
					if((rowidx%8) == 7){
						MSG_DBG("\n");
					}else{
						MSG_DBG("  ");
					}
					rowidx++;
				}
			}else{
				MSG_DBG("ECM_EcatEepromReq return %d\n",nret);
			}
		}
		MSG_DBG("\n==============\n");
	}
	if(u8OP & 4){//clean SM section
		if(nSize > 18){
			return -1;
		}
		for(i=nOffset;i<(nOffset+nSize);i++){
			nret = ECM_EcatEepromReq(ECM_EEPROM_OP_WR, 0, i, u16EEPROM_ZERO[i-nOffset], 1000000);
			if(nret == 1){
				MSG_DBG("ECM_EEPROM_OP_WR pass\n");
			}else{
				MSG_DBG("ECM_EEPROM_OP_WR return %d\n",nret);
			}
		}
		if(u8OP & 2){
			MSG_DBG("After clean\n");
			rowidx=0;
			MSG_DBG("\n==============\n");
			for(i=nOffset;i<(nOffset+nSize);i++){
				nret = ECM_EcatEepromReq(ECM_EEPROM_OP_RD, 0, i, 0, 1000000);
				if(nret == 1){
					nret = ECM_EcatEepromGet(&u64Data);
					if(nret == 1){
						if((rowidx%8) == 0){
							MSG_DBG("(%03d) ",i);
						}
						MSG_DBG(" %04X ",(uint16_t)u64Data);
						if((rowidx%8) == 7){
							MSG_DBG("\n");
						}else{
							MSG_DBG("  ");
						}
						rowidx++;
					}
				}else{
					MSG_DBG("ECM_EcatEepromReq return %d\n",nret);
				}
			}
			MSG_DBG("\n==============\n");
		}
	}
	if(u8OP & 1){
		if(nSize > 18){
			return -1;
		}
		for(i=nOffset;i<(nOffset+nSize);i++){
			nret = ECM_EcatEepromReq(ECM_EEPROM_OP_WR, 0, i, u16EEPROM[i-nOffset], 2000000000);
			if(nret == 1){
				MSG_DBG("ECM_EEPROM_OP_WR pass\n");
			}else{
				MSG_DBG("ECM_EEPROM_OP_WR return %d\n",nret);
			}
		}
		if(u8OP & 2){
			MSG_DBG("After write\n");
			rowidx=0;
			MSG_DBG("\n==============\n");
			for(i=nOffset;i<(nOffset+nSize);i++){
				nret = ECM_EcatEepromReq(ECM_EEPROM_OP_RD, 0, i, 0, 2000000000);
				if(nret == 1){
					nret = ECM_EcatEepromGet(&u64Data);
					if(nret == 1){
						if((rowidx%8) == 0){
							MSG_DBG("(%03d) ",i);
						}
						MSG_DBG(" %04X ",(uint16_t)u64Data);
						if((rowidx%8) == 7){
							MSG_DBG("\n");
						}else{
							MSG_DBG("  ");
						}
						rowidx++;
					}
				}else{
					MSG_DBG("ECM_EcatEepromReq return %d\n",nret);
				}
			}
			MSG_DBG("\n==============\n");
		}
	}
	return 1;
}
#if 0
int AlignmentAndWaitServoOn(int *pnPos)
{
	int i = 0, nret = 0, AxisIdx = 0, nExit = 1;
	uint8_t u8Data=0,u8FifoCnt=0;
	RXPDO_ST_DEF_T	*pAllDevRx;
	TXPDO_ST_DEF_T	*pAllDevTx;
	pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
	pAllDevRx = (RXPDO_ST_DEF_T *)RxPDOData;
	MSG_DBG("Start AlignmentAndWaitServoOn\n");
	for (i = 0; i < 1000; i++) {
		if (u8FifoCnt < (TEST_RXFIFO_CNT - 2)) {
			nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
			if(nret == 5 || nret == 7){
				nExit = 1;
				//Get valid data
				for (AxisIdx = 0; AxisIdx < TEST_DRV_CNT; AxisIdx++) {
					pnPos[AxisIdx] = pAllDevTx->Axis[AxisIdx].Actual;
					pAllDevRx->Axis[AxisIdx].Target = pnPos[AxisIdx];
					nret = Cia402Control(1, pAllDevTx->Axis[AxisIdx].u16StaWord, &(pAllDevRx->Axis[AxisIdx].u16CtlWord));
					MSG_DBG("(%d) 0x%04X 0x%04X\n" \
						, AxisIdx \
						, pAllDevTx->Axis[AxisIdx].u16StaWord \
						, pAllDevRx->Axis[AxisIdx].u16CtlWord);
					if (nret == 0) {
						nExit = 0;
					}else if (nret == 1){
						MSG_DBG("%d Position offset %d\n",AxisIdx,pnPos[AxisIdx]);
					}						
				}
				if (nExit) {
					MSG_DBG("AlignmentAndWaitServoOn PASS\n");
					return 1;
				}
			}
		}else{
			MSG_DBG("FIFO Full %d\n",u8FifoCnt);
			UserDelay(1000000);
		}
		UserDelay(100000);
	}
	MSG_DBG("AlignmentAndWaitServoOn timeout\n");
	return 0;
}

int ServoOn(int nCh, int *pnPos)
{
	int i = 0, nret = 0, AxisIdx = 0;
	uint8_t u8Data=0,u8FifoCnt=0;
	RXPDO_ST_DEF_T	*pAllDevRx;
	TXPDO_ST_DEF_T	*pAllDevTx;
	pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
	pAllDevRx = (RXPDO_ST_DEF_T *)RxPDOData;
	MSG_DBG("Start ServoOn(%d)\n",nCh);
	AxisIdx = nCh;
	for (i = 0; i < 1000; i++) {
		if (u8FifoCnt < (TEST_RXFIFO_CNT - 2)) {
			nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
			if(nret == 5 || nret == 7){				
				//Get valid data
				pnPos[AxisIdx] = pAllDevTx->Axis[AxisIdx].Actual;
				pAllDevRx->Axis[AxisIdx].Target = pnPos[AxisIdx];
				nret = Cia402Control(1, pAllDevTx->Axis[AxisIdx].u16StaWord, &(pAllDevRx->Axis[AxisIdx].u16CtlWord));
				MSG_DBG("(%d) 0x%04X 0x%04X\n" \
					, AxisIdx \
					, pAllDevTx->Axis[AxisIdx].u16StaWord \
					, pAllDevRx->Axis[AxisIdx].u16CtlWord);
				if (nret == 1){
					MSG_DBG("%d Position offset %d\n",AxisIdx,pnPos[AxisIdx]);
					MSG_DBG("AlignmentAndWaitServoOn PASS\n");
					return 1;
				}
			}
		}else{
			MSG_DBG("FIFO Full %d\n",u8FifoCnt);
			sleep(1);
		}
		usleep(100000);
	}
	MSG_DBG("(%d) ServoOn timeout\n", nCh);
	return 0;
}
int ServoOff()
{
	int i = 0, nret = 0, AxisIdx = 0, nExit = 1;
	uint8_t u8Data=0,u8FifoCnt=0;
	RXPDO_ST_DEF_T	*pAllDevRx;
	TXPDO_ST_DEF_T	*pAllDevTx;
	pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
	pAllDevRx = (RXPDO_ST_DEF_T *)RxPDOData;	
	for (int AxisIdx = 0; AxisIdx < TEST_DRV_CNT; AxisIdx++) {
		pAllDevRx->Axis[AxisIdx].u16CtlWord = 0;
	}
	MSG_DBG("Start ServoOff\n");
	for (i = 0; i < 1000; i++) {
		if (u8FifoCnt < (TEST_RXFIFO_CNT - 2)) {
			nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
			if(nret == 5 || nret == 7){
				nExit = 1;
				for (int AxisIdx = 0; AxisIdx < TEST_DRV_CNT; AxisIdx++) {
					MSG_DBG("(%d) 0x%04X 0x%04X\n" \
						, AxisIdx \
						, pAllDevTx->Axis[AxisIdx].u16StaWord \
						, pAllDevRx->Axis[AxisIdx].u16CtlWord);	
					if((pAllDevTx->Axis[AxisIdx].u16StaWord & 0xF) == 7){
						nExit = 0;
					}
				}
				if (nExit) {
					MSG_DBG("ServoOff PASS\n");
					return 1;
				}
			}
		}else{
			MSG_DBG("FIFO Full %d\n",u8FifoCnt);
			UserDelay(1000000);
		}
		UserDelay(100000);
	}
	MSG_DBG("ServoOff timeout\n");
	return 0;
}
int SetModeParam(int nSlv, uint8_t u8IpoTime, int8_t n8IpoTimeIndex)
{
	int nret=0;
	uint8_t u8Data=u8IpoTime;
	int8_t n8Data=n8IpoTimeIndex;
	u8Data=u8IpoTime;
	nret = ECM_EcatSdoWrite(nSlv, 0x60C2, 1, 1, 2000000000, &u8Data);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x60C2:1)\n");
		return -2;
	}
	MSG_DBG("Set 0x60C2:1 IPO time %d\n",u8Data);
	n8Data=n8IpoTimeIndex;
	nret = ECM_EcatSdoWrite(nSlv, 0x60C2, 2, 1, 2000000000, (uint8_t *)&n8Data);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x60C2:2)\n");
		return -2;
	}
	MSG_DBG("Set 0x60C2:2 IPO time index %d\n",n8Data);
	return 0;
}

int ShowModeParam(int nSlv)
{
	uint8_t u8Data=0;
	int8_t n8Data=0;
	int nret = ECM_EcatSdoRead(nSlv, 0x6061, 0, 1, 10000000, &u8Data);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6061)\n");
		return -2;
	}
	MSG_DBG("0x6061:0 mode of operarion 0x%x\n",u8Data);
	nret = ECM_EcatSdoRead(nSlv, 0x60C2, 1, 1, 10000000, &u8Data);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6061)\n");
		return -2;
	}
	MSG_DBG("0x60C2:1 IPO time %d\n",u8Data);
	nret = ECM_EcatSdoRead(nSlv, 0x60C2, 2, 1, 10000000, (uint8_t *)&n8Data);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6061)\n");
		return -2;
	}
	MSG_DBG("0x60C2:2 IPO time index %d\n",n8Data);
	return 0;
}
int SetStateAndCheck(int nSlv, uint8_t u8TarState, int nWaitSec)
{
	uint8_t u8State, EcmStatus;
	uint16_t u16ALStatus;
	int nret = ECM_EcatStateGet(nSlv, &u8State);
	if(u8State & EC_STATE_ERROR){
		MSG_DBG("Error state\n");
		nret = ECM_EcatStateSet(nSlv, u8State);
		MSG_DBG("ECM_EcatStateSet(%d, 0x%X) return %d\n", nSlv, u8State, nret);
		sleep(1);
		nret = ECM_EcatStateGet(nSlv, &u8State);
		MSG_DBG("(%d) ECM_EcatStateGet return %d, State 0x%X\n", nSlv, nret, u8State);
		if(u8State & EC_STATE_ERROR){
			return -1;
		}
	}
	MSG_DBG("CurState %d\n",u8State);
	if(u8State == u8TarState){
		MSG_DBG("Has reached the status (0x%X)\n",u8State);
		return 1;
	}
	MSG_DBG("Set State to %d\n",u8TarState);
	nret = ECM_EcatStateSet(nSlv, u8TarState);
	if (nret <= 0) {
		MSG_DBG("ECM_EcatStateSet retrun %d, State 0x%X\n",nret,u8TarState);
		return -1;
	}
	for(int nRunCnt = 0; nRunCnt<(5*nWaitSec); nRunCnt++){
		usleep(2000000);//200ms
		nret = ECM_InfoUpdate(&EcmStatus, 0, 0, 0);
		if(nret > 0){
			MSG_DBG("EcmStatus 0x%X\n",EcmStatus);
			if((EcmStatus & ECM_STA_ASYNC_OP_BUSY_MASK) == ECM_STA_ASYNC_OP_BUSY_MASK){
				MSG_DBG("Async busy\n");
			}else{
				nret = ECM_EcatStateGet(nSlv, &u8State);
				if (nret > 0) {
					if(u8State == u8TarState){
						MSG_DBG("Change State done (0x%X)\n",u8State);
						return 1;
					}else{						
						ECM_SlaveInfoGet(nSlv, ECM_SLV_INFO_ALstatuscode, (uint8_t *)&u16ALStatus);
						MSG_DBG("(%d) ALstatuscode 0x%x\n",nSlv,u16ALStatus);
						return 0;
					}
				}
			}
		}
	}
	MSG_DBG("TIMEOUT : ECM_EcatStateGet retrun %d, State 0x%X\n",nret,u8State);
	return 0;
}
int ECM_SetPpParam(int nSlv, uint32_t u32MaxSpeed, uint32_t u32Speed, uint32_t u32Acc,  uint32_t u32Dec)
{
	int nret=0;
	nret = ECM_EcatSdoWrite(nSlv, 0x607F, 0, 4, 2000000000, (uint8_t *)&u32MaxSpeed);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x607F:0)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x6081, 0, 4, 2000000000, (uint8_t *)&u32Speed);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6081:0)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x6083, 0, 4, 2000000000, (uint8_t *)&u32Acc);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6083:0)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x6084, 0, 4, 2000000000, (uint8_t *)&u32Dec);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6084:0)\n");
		return -2;
	}
	return 0;
}
int ECM_SetPtParam(int nSlv, uint32_t u32Slope, uint16_t u16MaxTorque)
{
	int nret=0;
	nret = ECM_EcatSdoWrite(nSlv, 0x6087, 0, 4, 2000000000, (uint8_t *)&u32Slope);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6087:0)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x6072, 0, 2, 2000000000, (uint8_t *)&u16MaxTorque);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6072:0)\n");
		return -2;
	}
	return 0;
}
int ECM_SetHomeParam(int nSlv, int8_t n8Method, int16_t n16Offset, uint32_t u32Speed_1st, uint32_t u32Speed_2nd, uint32_t u32Acc)
{
	int nret=0;
	nret = ECM_EcatSdoWrite(nSlv, 0x6098, 0, 1, 2000000000, (uint8_t *)&n8Method);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6098:0)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x607C, 0, 4, 2000000000, (uint8_t *)&n16Offset);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x607C:0)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x6099, 1, 4, 2000000000, (uint8_t *)&u32Speed_1st);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6099:1)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x6099, 2, 4, 2000000000, (uint8_t *)&u32Speed_2nd);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x6099:2)\n");
		return -2;
	}
	nret = ECM_EcatSdoWrite(nSlv, 0x609A, 0, 4, 2000000000, (uint8_t *)&u32Acc);
	if(nret <= 0){
		MSG_DBG("ECM_EcatSdoRead error (0x609A:0)\n");
		return -2;
	}
	return 0;
}
int ECM_PP(int nSlv, int32_t n32Tar, int nWaitReached)
{
	int nret = 0;
	uint8_t u8FifoCnt=0, u8Ack=0;
	RXPDO_ST_DEF_T	*pAllDevRx = (RXPDO_ST_DEF_T *)RxPDOData;
	TXPDO_ST_DEF_T	*pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
	MSG_DBG("=============\n");
	MSG_DBG("ECM_PP(%d, %d)\n", nSlv, n32Tar);
	MSG_DBG("=============\n");
	pAllDevRx->Axis[nSlv].u16CtlWord = 0x1F;
	pAllDevRx->Axis[nSlv].Target = n32Tar;
	while(1){
		nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
		if(nret == 5 || nret == 7){//Get valid data
			if(pAllDevTx->Axis[nSlv].u16StaWord & (0x0008)){//Error
				MSG_DBG("%d ECM_PP error (Status : 0x%X)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord);
				return -1;
			}			
			if(pAllDevTx->Axis[nSlv].u16StaWord & 0x1000){//Positon acknowledge
				pAllDevRx->Axis[nSlv].u16CtlWord = 0x0F;//Clear Start bit
				u8Ack = 1;
				if(nWaitReached == 0){
					nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
					MSG_DBG("%d Positon acknowledge, clear start bit return %d\n", nSlv, nret);
					return 0;
				}
				MSG_DBG("%d Positon acknowledge, clear start bit return %d\n", nSlv, nret);
			}			
			if(u8Ack == 1){
				if(nWaitReached){
					if(pAllDevTx->Axis[nSlv].u16StaWord & 0x0400){//Position reached
						nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
						MSG_DBG("%d Reached actual pos : %d [ ret %d ]\n", nSlv, pAllDevTx->Axis[nSlv].Actual, nret);
						return 1;
					}
				}
			}
			MSG_DBG("%d SW(0x%04X) POS(%d)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord, pAllDevTx->Axis[nSlv].Actual);
		}else if(nret != 6){//
			MSG_DBG("%d ECM_PP %d, FIFO cnt %d\n", nSlv, nret , u8FifoCnt);
			sleep(1);//1s
		}
		usleep(200000);//200ms
	}
	return 0;
}
int ECM_PV(int nSlv, int16_t n16Tar, int nWaitReached)
{
	int nret = 0;
	uint8_t u8FifoCnt=0;
	RXPDO_ST_DEF_T	*pAllDevRx = (RXPDO_ST_DEF_T *)RxPDOData;
	TXPDO_ST_DEF_T	*pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
	MSG_DBG("=============\n");
	MSG_DBG("%d ECM_PV\n", nSlv);
	MSG_DBG("=============\n");
	pAllDevRx->Axis[nSlv].u16CtlWord = 0x0F;
	pAllDevRx->Axis[nSlv].Target = n16Tar;
	while(1){
		nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
		if(nret == 5 || nret == 7){//Get valid data
			if(pAllDevTx->Axis[nSlv].u16StaWord & (0x0008)){//Error
				MSG_DBG("%d ECM_PV error (Status : 0x%X)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord);
				return -1;
			}			
			if(nWaitReached){
				if(pAllDevTx->Axis[nSlv].u16StaWord & 0x0400){//Velocity reached
					nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
					MSG_DBG("%d Reached actual vel : %d [ ret %d ]\n", nSlv, pAllDevTx->Axis[nSlv].Actual, nret);
					return 1;
				}
			}else{
				if((pAllDevTx->Axis[nSlv].u16StaWord & 0x1000) == 0){//Speed is not equal 0
					nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
					MSG_DBG("%d Velocity acknowledge return %d\n", nSlv, nret);
					MSG_DBG("%d SW(0x%04X) POS(%d)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord, pAllDevTx->Axis[nSlv].Actual);
					return 0;
				}
			}
		}else if(nret != 6){//
			MSG_DBG("%d ECM_PV %d, FIFO cnt %d\n", nSlv, nret , u8FifoCnt);
			sleep(1);//1s
		}
		usleep(200000);//200ms
	}
	return 0;
}
int ECM_PT(int nSlv, int16_t n16Tar, int nWaitReached)
{
	int nret = 0;
	uint8_t u8FifoCnt=0;
	RXPDO_ST_DEF_T	*pAllDevRx = (RXPDO_ST_DEF_T *)RxPDOData;
	TXPDO_ST_DEF_T	*pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
	MSG_DBG("=============\n");
	MSG_DBG("%d ECM_PT\n", nSlv);
	MSG_DBG("=============\n");
	pAllDevRx->Axis[nSlv].u16CtlWord = 0x0F;
	pAllDevRx->Axis[nSlv].Target = n16Tar;
	while(1){
		nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
		if(nret == 5 || nret == 7){//Get valid data
			if(pAllDevTx->Axis[nSlv].u16StaWord & (0x0008)){//Error
				MSG_DBG("%d ECM_PT error (Status : 0x%X)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord);
				return -1;
			}						
			if(nWaitReached){
				if(pAllDevTx->Axis[nSlv].u16StaWord & 0x0400){//Torque reached
					nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
					MSG_DBG("%d Reached actual tor : %d [ ret %d ]\n", nSlv, pAllDevTx->Axis[nSlv].Actual, nret);
					return 1;
				}
			}else{
				MSG_DBG("%d SW(0x%04X) TOR(%d)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord, pAllDevTx->Axis[nSlv].Actual);
				return 0;
			}
		}else if(nret != 6){//
			MSG_DBG("%d ECM_PT %d, FIFO cnt %d\n", nSlv, nret , u8FifoCnt);
			sleep(1);//1s
		}
		usleep(200000);
	}
	return 0;
}
int ECM_GoHome(int nSlv)
{
	int nret = 0;
	uint8_t u8FifoCnt=0;
	RXPDO_ST_DEF_T	*pAllDevRx = (RXPDO_ST_DEF_T *)RxPDOData;
	TXPDO_ST_DEF_T	*pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
	MSG_DBG("=============\n");
	MSG_DBG("%d ECM_GoHome\n", nSlv);
	MSG_DBG("=============\n");
	pAllDevRx->Axis[nSlv].u16CtlWord = 0x1F;
	while(1){
		nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
		if(nret == 5 || nret == 7){//Get valid data
			if(pAllDevTx->Axis[nSlv].u16StaWord & (0x2008)){//Error
				MSG_DBG("%d ECM_GoHome error (Status : 0x%X)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord);
				return -1;
			}
			if((pAllDevTx->Axis[nSlv].u16StaWord & 0x1400) == 0x1400){//GoHome done
				pAllDevRx->Axis[nSlv].u16CtlWord = 0x0F;//Clear Start bit
				nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, sizeof(RXPDO_ST_DEF_T), &u8FifoCnt, 0, 0, 0);
				MSG_DBG("%d GoHome done [ ret %d ]\n", nSlv, nret);
				return 1;
			}						
			MSG_DBG("%d SW(0x%04X) POS(%d)\n", nSlv, pAllDevTx->Axis[nSlv].u16StaWord, pAllDevTx->Axis[nSlv].Actual);
		}else if(nret != 6){//
			MSG_DBG("%d ECM_GoHome %d, FIFO cnt %d\n", nSlv, nret , u8FifoCnt);
			sleep(1);//1s
		}
		usleep(200000);//200ms
	}
	return 0;
}
int FindObjOffset(uint16_t SmaIdx, uint32_t u32Obj, uint32_t u32ObjMask, uint32_t *pOffsetList)
{
	int32_t i,j,k,nret;
	uint8_t u8PdoCnt=0,u8SlvCnt=0;
	uint16_t u16PdoIdx[4];
	uint8_t u8PdoObjCnt[4];
	uint32_t u32PdoObj[4][16];
	int32_t u32Offset = 0;
	int nFoundObjCnt = 0;
	u8SlvCnt = ECM_EcatSlvCntGet();
	if(u8SlvCnt == 0){
		return -1;
	}
	//MSG_DBG("\r\n========== 0x%X ==========\r\n",SmaIdx);
	for(i = 0; i < u8SlvCnt; i++){
		nret = ECM_EcatSdoRead(i, SmaIdx, 0, sizeof(u8PdoCnt), 2000000000, &u8PdoCnt);
		if(nret <= 0){
			continue;
		}
		//MSG_DBG("Slave(%d)\r\n",i);
		for(j = 0; j < u8PdoCnt; j++){
			nret = ECM_EcatSdoRead(i, SmaIdx, j+1, sizeof(u16PdoIdx[j]), 2000000000, (uint8_t *)&u16PdoIdx[j]);
			if(nret <= 0){
				return -1;
			}
			nret = ECM_EcatSdoRead(i, u16PdoIdx[j], 0, sizeof(u8PdoObjCnt[j]), 2000000000, &u8PdoObjCnt[j]);
			if(nret <= 0){
				continue;
			}
			//MSG_DBG("PdoIdx(0x%X)\r\n",u16PdoIdx[j]);
			for(k=0;k<u8PdoObjCnt[j];k++){
				nret = ECM_EcatSdoRead(i, u16PdoIdx[j], k+1, sizeof(u32PdoObj[j][k]), 2000000000, (uint8_t *)&u32PdoObj[j][k]);
				if(nret <= 0){
					return -1;
				}				
				if((u32PdoObj[j][k] & u32ObjMask) == u32Obj){	
					//MSG_DBG("\t0x%X - found %d\r\n",u32PdoObj[j][k], nFoundObjCnt);
					pOffsetList[nFoundObjCnt++] = u32Offset;
				}else{
					//MSG_DBG("\t0x%X\r\n",u32PdoObj[j][k]);
				}
				u32Offset += (u32PdoObj[j][k] & 0xFF);
			}
		}
	}
	return nFoundObjCnt;
}
#endif
