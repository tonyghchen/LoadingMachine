/******************************************************************************
 *	File	:	Utility.h
 *	Version :	1.52
 *	Date	:	2021/11/23
 *	Author	:	XFORCE
 *
 * @copyright (C) 2021 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/
#ifndef _ECM_UTILITY_H_
#define _ECM_UTILITY_H_
#ifdef __cplusplus
extern "C"
{
#endif

#define FIFO_QUEUE_SIZE		16384
/* FIFO */
/*
#define TEST_PDO_TO_FIFO_ONCE	1
#define TEST_RXFIFO_CNT			40
#define TEST_TXFIFO_CNT			TEST_PDO_TO_FIFO_ONCE
*/
int32_t CalVel(double dfAccStep, int32_t nFeedSpeed, int32_t nCostTime);
int32_t CalIncPos(int32_t nAccStep, int32_t nAccStepDivi, int32_t nAccTime, int32_t nCostTime, int32_t nStopTime);
int32_t SdoShowPdoConfig(int32_t nSlvB, int32_t nSlvE, uint16_t SmaIdx);
int32_t ConfigDrive(int32_t nList, int32_t nSlvB, int32_t nSlvE, int32_t nJustAssign, int32_t nPDOCnt , uint16_t RxMapIdx , uint16_t TxMapIdx, int nMode);
int32_t SetDriverCmdOpMode(int32_t nSlvBegin, int32_t nSlvEnd, uint8_t u8Mode, int32_t nAxisPerSlv);//NOTE : define N_DRV_IN_ONE_SLV at PdoDefine.h
int32_t ECM_CheckMEMSpace(int32_t nPdoCntOnce);
int32_t Cia402Control(int32_t nSevoOn , uint16_t u16Sate, uint16_t *u16Ctrol);
int32_t CustomizedSII(uint8_t u8OP, int32_t nOffset, int32_t nSize);
int AlignmentAndWaitServoOn(int *pnPos);
int ServoOn(int nCh, int *pnPos);
int ServoOff(void);
int SetModeParam(int nSlv, uint8_t u8IpoTime, int8_t n8IpoTimeIndex);
int ShowModeParam(int nSlv);
int SetStateAndCheck(int nSlv, uint8_t u8TarState, int nWaitSec);
int ECM_SetPpParam(int nSlv, uint32_t u32MaxSpeed, uint32_t u32Speed, uint32_t u32Acc,  uint32_t u32Dec);
int ECM_SetPtParam(int nSlv, uint32_t u32Slope, uint16_t u16MaxTorque);
int ECM_SetHomeParam(int nSlv, int8_t n8Method, int16_t n16Offset, uint32_t u32Speed_1st, uint32_t u32Speed_2nd, uint32_t u32Acc);
int ECM_PP(int nSlv, int32_t n32Tar, int nWaitReached);
int ECM_PV(int nSlv, int16_t n16Tar, int nWaitReached);
int ECM_PT(int nSlv, int16_t n16Tar, int nWaitReached);
int ECM_GoHome(int nSlv);
int FindObjOffset(uint16_t SmaIdx, uint32_t u32Obj, uint32_t u32ObjMask, uint32_t *pOffsetList);


#ifdef __cplusplus
}
#endif

#endif
