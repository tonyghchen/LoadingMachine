/******************************************************************************
 *	File	:	ec_master.h
 *	Version :	1.00
 *	Date	:	2022/04/23
 *	Author	:	chan-fa
 *
 * @copyright (C) 
 *
 ******************************************************************************/
#ifndef _ECM_MASTER_H_
#define _ECM_MASTER_H_

#include "EcmUsrDriver.h"


#include <stdint.h>

#include "EtherCatInterface.h"


typedef enum {
	EC_CMD_STATE_NONE=0,
	EC_CMD_STATE_START,
	EC_CMD_STATE_WAIT,
	EC_CMD_STATE_FINISHED
} EC_CMD_STATE_T;


typedef struct st_slave_object_info {
	uint32_t     u32Attr;
	uint32_t     u32Data;
} ST_SLAVE_OBJECT_INFO_T ;


typedef struct st_pdo_assign_info{
	uint16_t u16AssignAddr;		// 0x1C10 ~ 0x1C13
	uint16_t u16MappingAddr;		
	uint8_t  u8ODEntryCnt;
	uint8_t  u8DataSizes;
	uint8_t  u8DataOffset;
	uint8_t  u8Dummy;
	uint16_t u16ServerPDOffsetIdx;
	const ST_SLAVE_OBJECT_INFO_T *pstODEntry;	
} ST_PDO_ASSIGN_INFO_T ;

typedef struct ec_server_attr
{
	ST_PDO_ASSIGN_INFO_T RxPDO;
	ST_PDO_ASSIGN_INFO_T TxPDO;	
} EC_SERVER_ATTR_T;

typedef struct ec_slave_pdo_offset
{
	uint8_t  u8Bytes;		// [0]:Counts of total PDO item, [x]:Bytes
	uint8_t  u8Dummy;
	uint16_t u16Offset;		// [0]:Total Bytes of Entry, [x]:offset of PDO	
} EC_SLAVE_PDO_OFFSET_T;

typedef struct ec_slave_pdo_reg_idx
{
	uint8_t  u8Idx;		// [0]:Counts, [x]:index of registers
} EC_SLAVE_PDO_REG_IDX_T;


typedef struct ec_slave_od{
	EC_SLAVE_PDO_OFFSET_T *DIn;
	EC_SLAVE_PDO_OFFSET_T *DOut;
	EC_SLAVE_PDO_OFFSET_T *AIn;
	EC_SLAVE_PDO_OFFSET_T *AOut;
	EC_SLAVE_PDO_OFFSET_T *ServerTx;		// 所有ServerIn的items
	EC_SLAVE_PDO_OFFSET_T *ServerRx;

	EC_SLAVE_PDO_OFFSET_T *Rx;				// Master to Slave
	EC_SLAVE_PDO_OFFSET_T *Tx;				// Slave to Master
	
	EC_SLAVE_PDO_REG_IDX_T *RxCtrlWordReg;	// pointer to control word reg.	
	EC_SLAVE_PDO_REG_IDX_T *RxTargetPosReg;	// pointer to target position 
	EC_SLAVE_PDO_REG_IDX_T *RxTouchProbeModeReg;// pointer to touch probe mode. 	
	
	EC_SLAVE_PDO_REG_IDX_T *TxStatusWordReg;	// pointer to Staus word reg.	
	EC_SLAVE_PDO_REG_IDX_T *TxActualPosReg;	// pointer to Actual position
	EC_SLAVE_PDO_REG_IDX_T *TxActualTorqueReg;	// pointer to Actual Torque	
	EC_SLAVE_PDO_REG_IDX_T *TxErrorCodeReg;	// pointer to Actual position
	EC_SLAVE_PDO_REG_IDX_T *TxTouchProbeStateReg;	// pointer to Touch probe state 
	EC_SLAVE_PDO_REG_IDX_T *TxTouchProbe2PositiveEdgeReg;	// pointer to Touch probe 2 positive edge position stored 
	EC_SLAVE_PDO_REG_IDX_T *TxTouchProbe1PositiveEdgeReg;	// pointer to Touch probe 1 positive edge position stored 	
	EC_SLAVE_PDO_REG_IDX_T *TxFollowingErrorActualValueReg;	// pointer to Follow error
	EC_SLAVE_PDO_REG_IDX_T *TxTargetPosReg;	// pointer to target position     
}EC_SLAVE_OD;


typedef struct ec_slave_vid_pid {
	uint32_t 	u32Vid;
	uint32_t 	u32Pid;
} EC_SLAVE_VID_PID_T;

typedef struct ec_slave_st {
	uint8_t  u8RequestState;
	uint8_t  u8CurrentState;	
	uint16_t u16ErrorCode;
	uint8_t  u8ErrorRegister;
	
} EC_SLAVE_T;


/** EtherCAT master phase.
 */
typedef enum {
    EC_MASTER_UNKNOWN, 
	EC_MASTER_INIT,
	EC_MASTER_REQUEST_SLAVE_FSM_INIT,
	EC_MASTER_REQUEST_SLAVE_FSM_PREOP,
	EC_MASTER_REQUEST_SLAVE_FSM_SAFEOP,
	EC_MASTER_REQUEST_SLAVE_FSM_OP,
} EC_MASTER_PHASE_T;

typedef struct ec_master_config_st
{
	uint32_t u32SPIClock;
	uint32_t u32CanOpenOpMode;
	uint32_t u32ActiveCode;
	uint32_t u32DCTimes_us;	
	uint32_t u32RxPDOBufferSize;
	uint32_t u32TxPDOBufferSize;		
} EC_MASTER_CONFIG_T;

typedef struct ec_master_st{
	EC_MASTER_CONFIG_T configs;
	
	uint8_t  u8FirmwareVersion;

	EC_MASTER_PHASE_T  u8CurrentState;
	
	uint8_t  u8SlaveCnt; /**< Number of slaves on the bus. */	
	EC_SLAVE_VID_PID_T *pstSlaveVidPidTable;
	
	EC_SLAVE_OD	stSlaveOD;
	
	// for Server
	uint8_t u8ServerCnt;	
	uint8_t u8ServerStartIdx;
	uint8_t u8ServerEndIdx;
	EC_SERVER_ATTR_T *pstServerAttr;
	
	// for PDO
	uint8_t RxPDOData[TEST_SPI_DATA_SIZE];
	uint8_t TxPDOData[TEST_SPI_DATA_SIZE];
	
	// for User
	ETHERCAT_MASTER_PDO_CB *pPDOCallback;
} EC_MASTER_T;

extern EC_MASTER_T gMasterInfo;
extern uint32_t    gSPIPackageCount;


// Macro
#define RxPDOData	gMasterInfo.RxPDOData
#define TxPDOData	gMasterInfo.TxPDOData
#define RxPDODATASIZE() gMasterInfo.stSlaveOD.Rx[0].u16Offset
#define TxPDODATASIZE() gMasterInfo.stSlaveOD.Tx[0].u16Offset

#define ODDATAIDX(x)    (x>>16)
#define ODDATASUBIDX(x) ((x>>8)&0xff)
#define ODDATABITS(x)   (x&0xff)
#define ODDATABYTES(x)  (ODDATABITS(x)>>3)


/* IRQ Hook */
void PendSV_Handler_Hook (void);
void SysTick_Handler_Hook (void);
void GPA_IRQHandler_Hook (void);
void GPE_IRQHandler_Hook (void);

void Trigger_PendSV_Interrupt(void);
void Trigger_SysTick_Interrupt(void);

void EC_Master_ProcessCmd(int isCmdFinished, int nret);
void EC_Master_MotionRunningEnable(int enabled);
void EC_Master_MotionRunningToggle(void);

int EC_Master_SetServerStartIndex(uint8_t index);
int EC_Master_SetServerEndIndex(uint8_t index);
void EC_Master_IncServerCount(void);


#endif	// #ifndef _ECM_MASTER_H_
