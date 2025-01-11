/******************************************************************************
 *	File	:	EcmDriver.h
 *	Version :	1.52
 *	Date	:	2021/11/23
 *	Author	:	XFORCE
 *
 *	ECM-XF main header
 *
 *	Define
 *	1. SPI package.
 *	2. Command and data structure
 *	3. the fields of the structure.
 *	4. the flags of the field.
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/
#ifndef _ECM_DRV_H_
#define _ECM_DRV_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

#define pthread_mutex_lock(x) do{}while(0)
#define pthread_mutex_unlock(x) do{}while(0)
#define pthread_mutex_init(x,y) do{}while(0)
#define pthread_mutex_destroy(x) do{}while(0)
typedef void *pthread_mutex_t;

#define ECM_PACK_BEGIN
#define ECM_PACK  __attribute__((__packed__))
#define ECM_PACK_END

#define CIA402_SW_STATE_MASK			0x6F
#define CIA402_SW_NOTREADYTOSWITCHON	0x00
#define CIA402_SW_SWITCHEDONDISABLED	0x40
#define CIA402_SW_READYTOSWITCHON		0x21
#define CIA402_SW_SWITCHEDON			0x23
#define CIA402_SW_OPERATIONENABLED		0x27
#define CIA402_SW_QUICKSTOPACTIVE		0x07
#define CIA402_SW_FAULTREACTIONACTIVE	0x0F
#define CIA402_SW_FAULT					0x08

#define ECM_INDEX						0xFF

#define EC_STATE_NONE					0x00
#define EC_STATE_INIT					0x01
#define EC_STATE_PRE_OP					0x02
#define EC_STATE_BOOT					0x03
#define EC_STATE_SAFE_OP				0x04
#define EC_STATE_OPERATIONAL			0x08
#define EC_STATE_ACK					0x10
#define EC_STATE_ERROR					0x10

#define PDO_FIFO_SIZE				16384
#define PKG_DATA_MIN_SIZE			32
#define PKG_DATA_MAX_SIZE			1408
#ifndef ECM_XFU
#define PKG_DATA_DEFAULT_SIZE		112
#else
#define PKG_DATA_DEFAULT_SIZE		992
#endif
#define PACK_HEAD_SIZE				24
#define CRC_FIELD_SIZE				4
#define PACK_STOPWORD_SIZE			4
#define PKG_MIN_SIZE				64
#define PKG_MAX_SIZE				1440
#ifndef ECM_XFU
#define PKG_DEFAULT_SIZE			144
#else
#define PKG_DEFAULT_SIZE			1024
#endif
#define PDO_FIFO_MAX_CNT			128
#define PDO_FIFO_DEFAULT_CNT		64
#define TXPDO_EXDATA_SIZE			0

#define ECM_ERR_LINK_PIN_MASK			0x01
#define ECM_ERR_LINK_CHK_MASK			0x02
#define ECM_ERR_ECAT_STA_MASK			0x04
#define ECM_ERR_ASYNC_CMD_MASK			0x08
#define	ECM_ERR_SPI_MASK				0x10
#define	ECM_ERR_FIFO_MASK				0x20
#define ECM_ERR_CRC_MASK				0x40
#define ECM_ERR_CMD_MASK				0x80

#define ECM_CRC_TYPE_NONE	0
#define ECM_CRC_TYPE_8		1
#define ECM_CRC_TYPE_16		2
#define ECM_CRC_TYPE_32		3

#define	ECM_STA_CRC_TYPE_MASK			0x03
#define ECM_STA_DC_STABLE				0x04
#define ECM_STA_EMAC_INIT_MASK			0x08
#define ECM_STA_ECAT_CONFIG_MASK		0x10
#define ECM_STA_NOP_CMD_MASK			0x20
#define ECM_STA_FIFO_EN_MASK			0x40
#define ECM_STA_ASYNC_OP_BUSY_MASK		0x80

#define ECM_CTL_UPDATE_EC_STATE_MASK		0x01
#define ECM_CTL_ENABLE_RTA_MASK				0x02
#define ECM_CTL_CLR_ASYNC_OP_ERR_MASK		0x08
#define ECM_CTL_CLR_SPI_ERR_MASK			0x10
#define ECM_CTL_CLR_FIFO_ERR_MASK			0x20
#define ECM_CTL_CLR_CRC_ERR_MASK			0x40
#define ECM_CTL_CLR_CMD_ERR_MASK			0x80
#define ECM_CTL_CLR_ALL_ERR_MASK			0xF8

#define ECM_CRC_INIT_NUM			0x87654321
#define	ECM_CRC_MAGIC_NUM			0x12345678
#define	ECM_START_WORD				0xA1A2A3A4
#define	ECM_STOP_WORD				0x56575859

#define ECM_SDO_OP_WR	0
#define ECM_SDO_OP_RD	1

#define ECM_FIFO_WR			1
#define ECM_FIFO_RD			2
#define ECM_FIFO_WR_DIR		4
#define ECM_FIFO_RD_DIR		8

#define ECM_FIFO_RW			3
#define ECM_FIFO_RWD		6
#define ECM_FIFO_RDW		9

#define ECM_FIFO_RXPDO		0
#define ECM_FIFO_TXPDO		1

#define ECM_PDO_WR_OP		5
#define ECM_PDO_RD_OP		6
#define ECM_PDO_RW_OP		7

#define ECM_STATE_OP_UPDATE		0
#define ECM_STATE_OP_RD			1
#define ECM_STATE_OP_WR			2
#define ECM_STATE_OP_WRandACK	3

#define CIA402_FSM_CTL_ENABLE_MASK			0x10
#define CIA402_FSM_CTL_FAULT_RST_MASK		0x08
#define CIA402_FSM_CTL_FAULT_AUTORST_MASK	0x80

#define ECM_EEPROM_OP_RD			0
#define ECM_EEPROM_OP_WR			1

#define ECM_INTFALG_CRC_ERR_BIT			22
#define ECM_INTFALG_WKC_ERR_BIT			23
#define ECM_INTFALG_TXFIFO_HT_BIT		24
#define ECM_INTFALG_RXFIFO_LT_BIT		25
#define ECM_INTFALG_RECV_PD_BIT			31

#define ECM_INTFALG_CRC_ERR				(1<<ECM_INTFALG_CRC_ERR_BIT)
#define ECM_INTFALG_WKC_ERR				(1<<ECM_INTFALG_WKC_ERR_BIT)
#define ECM_INTFALG_TXFIFO_HT			(1<<ECM_INTFALG_TXFIFO_HT_BIT)
#define ECM_INTFALG_RXFIFO_LT			(1<<ECM_INTFALG_RXFIFO_LT_BIT)
#define ECM_INTFALG_RECV_PD				(1<<ECM_INTFALG_RECV_PD_BIT)


#define ECM_HEAD_INTFALG_GPIO0_7		0xFF
#define ECM_HEAD_INTFALG_GPIO8_B		0x0F
////////////////////////////////////////
#define ECM_HEAD_INTFALG_GPIO00		0x01
#define ECM_HEAD_INTFALG_GPIO01		0x02
#define ECM_HEAD_INTFALG_GPIO02		0x04
#define ECM_HEAD_INTFALG_GPIO03		0x08
#define ECM_HEAD_INTFALG_GPIO04		0x10
#define ECM_HEAD_INTFALG_GPIO05		0x20
#define ECM_HEAD_INTFALG_GPIO06		0x40
#define ECM_HEAD_INTFALG_GPIO07		0x80
////////////////////////////////////////
#define ECM_HEAD_INTFALG_GPIO08			0x01
#define ECM_HEAD_INTFALG_GPIO09			0x02
#define ECM_HEAD_INTFALG_GPIO10			0x04
#define ECM_HEAD_INTFALG_GPIO11			0x08
#define ECM_HEAD_INTFALG_QEI_IDX		0x10
#define ECM_HEAD_INTFALG_QEI_CMP		0x20
#define ECM_HEAD_INTFALG_QEI_OUF		0x40
#define ECM_HEAD_INTFALG_QEI_DIR		0x80

enum{
	ECM_SLV_INFO_vid,
	ECM_SLV_INFO_pid,
	ECM_SLV_INFO_rev,
	ECM_SLV_INFO_name,
	ECM_SLV_INFO_configadr,
	ECM_SLV_INFO_aliasadr,
	ECM_SLV_INFO_state,
	ECM_SLV_INFO_ALstatuscode,
	ECM_SLV_INFO_Obytes,
	ECM_SLV_INFO_Ibytes,
	ECM_SLV_INFO_hasdc,
	ECM_SLV_INFO_DCcycle,
	ECM_SLV_INFO_DCshift,
	ECM_SLV_INFO_DCactive
};
enum{
	ECM_CMD_INFO_UPDATE_OP,
	ECM_CMD_ECAT_INIT_OP,
	ECM_CMD_ECAT_RECONFIG_OP,
	ECM_CMD_ECAT_INIT_DC_OP,
	ECM_CMD_ECAT_PDO_WC_GET,
	ECM_CMD_ECAT_PDO_DATA_FIFO_OP,
	ECM_CMD_ECAT_PDO_DATA_OP,
	ECM_CMD_ECAT_PDO_CONFIG_SET,
	ECM_CMD_ECAT_PDO_CONFIG_REQ,
	ECM_CMD_ECAT_PDO_CONFIG_GET,
	ECM_CMD_ECAT_SDO_REQ,
	ECM_CMD_ECAT_SDO_GET,
	ECM_CMD_ECAT_STATE_SET,
	ECM_CMD_ECAT_STATE_GET,
	ECM_CMD_ECAT_CYCTIME_SET,
	ECM_CMD_ECAT_SLV_INFO_GET,
	ECM_CMD_ECAT_SLV_CNT_GET,
	ECM_CMD_FIFO_CONFIG,
	ECM_CMD_FIFO_ENABLE,
	ECM_CMD_FIFO_PACK_SIZE_GET,
	ECM_CMD_SPI_PACK_SIZE_GET,
	ECM_CMD_SPI_TIMEOUT_SET,
	ECM_CMD_SPI_TIMEOUT_GET,
	ECM_CMD_SPI_RECONFIG_OP,
	ECM_CMD_CRC_ERR_CNT_CLR,
	ECM_CMD_CRC_TYPE_SET,
	ECM_CMD_402_CONFIG_SET,
	ECM_CMD_402_STATE_SET,
	ECM_CMD_402_STATE_GET,
	ECM_CMD_402_CTL_SET,
	ECM_CMD_402_CTL_GET,
	ECM_GPIO_CONFIG_SET,
	ECM_GPIO_FUNC_OP,
	ECM_QEI_FUNC_OP,
	ECM_DAC_FUNC_OP,
	ECM_ADC_FUNC_OP,
	ECM_WDT_FUNC_OP,
	ECM_DCM_PARAM_OP,
	ECM_EEPROM_REQ,
	ECM_EEPROM_GET,
	ECM_CMD_EMAC_RESET_OP,
	ECM_CMD_ECAT_STATE_CHECK,
	ECM_CMD_GET_VALUE,
	ECM_CMD_SET_VALUE,
	ECM_CMD_GET_VAR,
	ECM_CMD_GET_TIMER_TIME,
	ECM_CMD_COMPARE_SET_CONFIG,
	ECM_CMD_COMPARE_GET_CONFIG,
	ECM_CMD_SET_PDO_MAP,
	ECM_CMD_GET_PDO_MAP,
	ECM_CMD_ECAT_DCSYNC,
	ECM_CMD_FIFO_CLR_OP,
	ECM_CMD_FIFO_SET_TX_CNT,
	ECM_CMD_FIFO_GET_TX_CNT,
	ECM_CMD_FIFO_SET_RX_CNT,
	ECM_CMD_FIFO_GET_RX_CNT,
	ECM_CMD_FW_VERSION_GET,
	ECM_CMD_ECAT_STATE_UPDATE,
    ECM_CMD_ECAT_INT_SET_ENABLE,
    ECM_CMD_ECAT_INT_GET_ENABLE,
	ECM_CMD_ECAT_RTA_INIT,
	ECM_CMD_ECAT_RTA_CLOSE,
	ECM_CMD_ECAT_RTA_SET_RULE,
	ECM_CMD_ECAT_RTA_SET_BUF,
	ECM_CMD_ECAT_RTA_SETENABLE,
	ECM_CMD_ECAT_RTA_GETRUNFLAG,
	ECM_CMD_FIFO_INIT,
	ECM_CMD_ECAT_WKC_CONTIERR_SET,
	ECM_CMD_ECAT_WKC_CONTIERR_GET,
	ECM_CMD_ECAT_SDO_ABORTCODE_GET,
	ECM_CMD_ECAT_SET_FIFO_TH,
	ECM_CMD_ECAT_CONFIG_SM,
	ECM_CMD_ECAT_CONFIG_FMMU,
	ECM_CMD_ECAT_CONFIG_MAP,
	ECM_CMD_402_GET_STATUSWORD,
	ECM_CMD_ASYNCCMD_RESET,
	ECM_CMD_WARM_RESET=127,
	ECM_CMD_EMAC_INIT_OP,
	ECM_CMD_EC_INIT_OP,
	ECM_CMD_ECAT_WKC_CONTI_ERR_CNT_GET,
	ECM_CMD_ECAT_WKC_CONTI_ERR_MAX_GET,
	ECM_CMD_ECAT_WKC_CONTI_ERR_MAX_SET,
	ECM_CMD_FIFO_EXPDO_DATA_CNT_SET,
	ECM_CMD_FIFO_EXPDO_DATA_CNT_GET,
	ECM_CMD_FIFO_EXPDO_DATA_TYPE_SET,
	ECM_CMD_FIFO_EXPDO_DATA_TYPE_GET,
	ECM_CMD_RAW_ECAT_FUNC_REQ,
	ECM_CMD_RAW_ECAT_FUNC_GET,
	ECM_CMD_FOE_FUNC_REQ,
	ECM_CMD_FOE_FUNC_GET,
	ECM_CMD_SPI_PACK_SIZE_SET
};
enum{
	ECM_FOE_API_DHOOK,
	ECM_FOE_API_RD,
	ECM_FOE_API_WR
};
typedef enum {
	ECM_RAW_API_APRD = 1,
	ECM_RAW_API_APWR = 2,
	ECM_RAW_API_FPRD = 4,
	ECM_RAW_API_FPWR = 5,
	ECM_RAW_API_BRD = 7,
	ECM_RAW_API_BWR = 8,
	ECM_RAW_API_LRD = 10,
	ECM_RAW_API_LWR = 11,
	ECM_RAW_API_LRW = 12,
	ECM_RAW_API_ARMW = 13,
	ECM_RAW_API_FRMW = 14,
} ecm_datagram_commad_t;
ECM_PACK_BEGIN
typedef struct ECM_PACK ec_dcsync_h
{
	uint8_t Slave;
	uint8_t Paddle;
	uint8_t Mode;
	uint8_t Act;
	uint32_t CyclTime0;
	uint32_t CyclTime1;
	int32_t CyclShift;
} EC_DCSYNC_H;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK sdo_write_t
{
	uint8_t OP;
	uint8_t Slave;
	uint16_t Index;
	uint8_t SubIndex;
	uint8_t CA;
	uint16_t size;
	int32_t Timeout;
	uint8_t Data[256];
}SDO_CMD_HEAD;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK obj_entry_t
{
	uint8_t u8BitSize;
	uint8_t u8SubIdx;
	uint16_t u16Idx;
} OBJ_ENTRY_T;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK pdo_config_t
{
	uint32_t	VID;
	uint32_t	PID;
	uint8_t		Slave;
	uint8_t		PDOCnt;
	uint16_t	SmaIdx;
	uint16_t	MapIdx[4];
	uint16_t	ObjsCnt[4];
	OBJ_ENTRY_T	Table[32];
} PDO_CONFIG_HEAD;
ECM_PACK_END
/*ECM_PACK_BEGIN
typedef struct ECM_PACK pdo_config_t
{
	uint8_t Slave;
	uint8_t PDOCnt;
	uint16_t SmaIdx;
	uint16_t MapIdx[3];
	uint16_t ObjsCnt[3];
	OBJ_ENTRY_T Table[3][8];
} PDO_CONFIG_HEAD;
ECM_PACK_END*/
ECM_PACK_BEGIN
typedef struct ECM_PACK ecm_eeprom_req_t
{
	uint16_t OP;
	uint16_t slave;
	uint16_t eeproma;
	uint16_t data;
	uint32_t timeout;
} ECM_EEPROM_REQ_T;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_cmd_header
{
	uint32_t u32StartWord;
	uint8_t u8Data[4];
	uint16_t u16Reserve;
	uint8_t u8Ctrl;
	uint8_t u8Idx;
	uint8_t u8Cmd;
	uint8_t u8Param;
	uint16_t u16Size;
	uint32_t u32CompIntClr;
	uint8_t u8GpioIntClr[2];
	uint8_t uGpio[2];
} SPI_CMD_HEADER;
ECM_PACK_END
ECM_PACK_BEGIN
#if 0
typedef struct ECM_PACK spi_cmd_package
{
	SPI_CMD_HEADER Head;
	uint8_t Data[];
} SPI_CMD_PACKAGE;
ECM_PACK_END
#endif
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_ret_header
{
	uint32_t u32StartWord;
	uint8_t u8CrcErrCnt;
	uint8_t u8WkcErrCnt;
	uint8_t u8TxFifoCnt;
	uint8_t u8RxFifoCnt;
	uint8_t u8EcState;
	uint8_t u8ErrorStatus;
	uint8_t u8Status;
	uint8_t u8Idx;
	uint8_t u8Cmd;
	uint8_t u8Return;
	uint16_t u16Size;
	uint32_t u32CompIntFlag;
	uint8_t u8GpioIntFlag[2];
	uint8_t u8Gpio[2];
} SPI_RET_HEADER;
ECM_PACK_END
#if 0
ECM_PACK_BEGIN
typedef struct ECM_PACK spi_ret_package
{
	SPI_RET_HEADER Head;
	uint8_t Data[];
} SPI_RET_PACKAGE;
ECM_PACK_END
#endif
ECM_PACK_BEGIN
typedef struct ECM_PACK _cia402_api_param_
{
	uint8_t Ctrl;
	uint8_t TargetState;
	uint8_t ContrlWordOffset;
	uint8_t StatusWordOffset;
} CIA402_API_PARAM;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK _ecm_pdo_ext_data_
{
	uint16_t u16WKC;
	uint8_t u8Idx;
	uint8_t u8Reserve;
} ECM_PDO_EXT_DATA;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct ECM_PACK ec_raw_api_param_h
{
	uint16_t OP;
	uint16_t length;
	uint16_t ADP;
	uint16_t ADO;
	uint32_t LogAdr;
	int32_t timeout;
	int32_t wkc;
	uint8_t data[256];
} EC_RAW_API_PARAM_H;
ECM_PACK_END

ECM_PACK_BEGIN
typedef struct ECM_PACK ecm_config_sm_t
{
	uint8_t slave;
	uint8_t nSM;
	uint16_t StartAddr;
	uint16_t SMlength;
	uint8_t ControlReg;
	uint8_t Activate;
} ECM_CONFIG_SM_T;
ECM_PACK_END

ECM_PACK_BEGIN
typedef struct ECM_PACK ecm_config_fmmu_t
{
	uint8_t slave;
	uint8_t FMMU0func;
	uint8_t FMMU1func;
	uint8_t FMMU2func;
	uint8_t FMMU3func;
} ECM_CONFIG_FMMU_T;
ECM_PACK_END
ECM_PACK_BEGIN
typedef struct   ECM_PACK _rta_rule_ {
    unsigned char u8Condition;		//	bit7		:	Logical AND operation
									//	bit6~bit0	:	Condition6~0
	unsigned char u8Operator;		//	+ - * / % << >> & | ^
	unsigned short u16Operant[2];	// 2bits Source(Tx, Rx, Buf, Local) + 2bits Size + 12bits Offset
	unsigned short u16Result;		// 2bits Source(Rx, Buf, Local) + 2bits Size + 12bits Offset
} RTA_RULE;
ECM_PACK_END
#ifdef __cplusplus
}
#endif

#endif
//	(C) COPYRIGHT 2020 NEXTW Technology Corp.
