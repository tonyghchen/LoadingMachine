// -------------------------------------------------------------------------
//  File        : ec_master.cpp
//              :
//  Library     :
//              :
//  Developer   : 
//              :
//  Purpose     : Control Functions for EtherCAT master.
//              :
//  Limitation  :
//              :
//  Note        :
//              :
// -------------------------------------------------------------------------
//  (c) Copyright 2022-2023; 
//
//  All rights reserved.  Protected by international copyright laws.
//  Knowledge of the source code may NOT be used to develop similar product
//  Your honesty is greatly appreciated.
// -------------------------------------------------------------------------
//  Modification History :
// -------------------------------------------------------------------------
//  Version | Mdy Date : | Descriptions
//          | mm/dd/yyyy |
//  V0.00   | 04/28/2022 | First release
//  V1.00   | 09/11/2023 | Add EtherCatMasterStop()
// -------------------------------------------------------------------------


/***************************************************************************
Include files
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "NuMicro.h"
#include "EcmUsrDriver.h"
#include "platform.h"
#include "Utility.h"
#include "PdoDefine.h"
#include "app_config.h"
#include "ec_master.h"
#include "ec_cmd_isr.h"
#include "slave_devices.h"

/***************************************************************************
Constant define
***************************************************************************/


/***************************************************************************
Function Prototype (External)
***************************************************************************/
static void EC_Master_InterruptEnable(void);
static void EC_Master_InterruptDisable(void);
int setNextPosition(int nPos, int u8ClockWise) ;

//#ifdef DEBUG_DRIVER_INFO
unsigned int gRxTxBufferOffset;
//#endif

extern "C" {
int32_t SetPdoConfTbl(PDO_CONFIG_HEAD *pConfig, uint8_t u8PdoIdx, uint8_t u8TblIdx, uint16_t u16Idx, uint8_t u8SubIdx, uint8_t u8BitSize);
}
/***************************************************************************
Function Prototype (Local)
***************************************************************************/
static int ec_slave_scan(uint32_t nCanOpenOpMOde);


/***************************************************************************
Variable Define (External)
***************************************************************************/



/***************************************************************************
Variable Define (Global)
***************************************************************************/
EC_MASTER_T gMasterInfo;
uint32_t    gSPIPackageCount;

/***************************************************************************
Variable Define (Local)
***************************************************************************/
static int *gnServerMotorPos;


typedef struct st_fifo_pdo_info
{    
    uint32_t u32Overflow;
    volatile EC_CMD_STATE_T  nCmdState;
    int      nret;                  // return value after command finished.
    uint8_t  u8isCmdWrRd;
    uint8_t  u8Initialed;
    uint8_t  u8BypassFirstEtherCatInt;
    volatile uint8_t  u8EtherCATDataPackageInterrupt;
    IRQn_Type  u8IRQNumber; 
    
    uint32_t u32CallErrCnt; 
    uint32_t u32WriteSuccessCnt;
    uint32_t u32ReadSuccessCnt; 
    uint32_t u32ReadWriteSuccessCnt;    
    uint32_t u32ReadWriteFailCnt;
    uint32_t u32LastCmdNotFiFoCnt;

    uint32_t u32ZeroCnt;
    uint32_t u32WkcErrCnt;
    uint32_t u32CrcErrCnt;  
        
    int      nStartFIFO;
    uint8_t  u8ServrRunning;
    uint8_t  u8FifoCnt;
    uint8_t  u8RetFifoCnt;
    uint8_t  u8IsSlvAlive;
    uint8_t  u8CrcErrCnt;
    uint8_t  u8LastCrcErrCnt;
    uint8_t  u8WkcErrCnt;
    uint8_t  u8LastWkcErrCnt;
    

}ST_FIFO_PDO_INFO_T;


ST_FIFO_PDO_INFO_T gFiFoPDOInfo;


static void HandleResponseCmd (void)
{
    int nret;

    //TRACE_MSG("70");
    if (gFiFoPDOInfo.nCmdState == EC_CMD_STATE_START){
        if (!gFiFoPDOInfo.u8BypassFirstEtherCatInt){        
            if (gMasterInfo.pPDOCallback){
                gMasterInfo.pPDOCallback();
            }  
        }
        else{
            TRACE_MSG("bypass");
        }
        //TRACE_MSG("7SP");
        gFiFoPDOInfo.nCmdState = EC_CMD_STATE_WAIT;
        gFiFoPDOInfo.u8isCmdWrRd = 1;
        EC_CmdStackReset();
        nret = ECM_EcatPdoFifoDataExchangeAdvISR((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, RxPDODATASIZE(), &gFiFoPDOInfo.u8RetFifoCnt, &gFiFoPDOInfo.u8CrcErrCnt, &gFiFoPDOInfo.u8WkcErrCnt, &gFiFoPDOInfo.u8IsSlvAlive);
        if (nret < 0){
            TRACE_MSG("sv:PDO E %d\n", nret);
            EC_Master_ProcessCmd(1, nret);
            return ;
        }            
    }
    else  if (gFiFoPDOInfo.nCmdState == EC_CMD_STATE_FINISHED){
        //TRACE_MSG("7E");        
        gFiFoPDOInfo.nCmdState = EC_CMD_STATE_NONE;        
        nret = gFiFoPDOInfo.nret;
        if (gFiFoPDOInfo.u8isCmdWrRd){
            if (nret < 0){
                gFiFoPDOInfo.u32CallErrCnt++;                       
            }
            else {
                if (nret == 0){
                    gFiFoPDOInfo.u32LastCmdNotFiFoCnt++;                        
                    //printf("Last command is not ECM_CMD_ECAT_PDO_DATA_FIFO_OP\n");
                }
                else if (nret == 4){
                    gFiFoPDOInfo.u32ReadWriteFailCnt++;                     
                    //printf("Read and write error\n");
                }
                else if (nret == 5){
                    gFiFoPDOInfo.u32ReadSuccessCnt++; 
                    gFiFoPDOInfo.u8FifoCnt = gFiFoPDOInfo.u8RetFifoCnt;
                }                               
                else if (nret == 6){
                    gFiFoPDOInfo.u32WriteSuccessCnt++;                          
                }
                else if (nret == 7){
                    gFiFoPDOInfo.u32ReadWriteSuccessCnt++; 
                    gFiFoPDOInfo.u8FifoCnt = gFiFoPDOInfo.u8RetFifoCnt;
                }       
            }
        }
     
        if (gFiFoPDOInfo.nStartFIFO == 1) {
            // Check EtherCAT slave
            if (gFiFoPDOInfo.u8IsSlvAlive == 0) {
                //printf("Maybe Slaves exit OP state\n");
                //break;
                EC_Master_MotionRunningEnable(0);
            }
            // Check ECAT communication quality
            if (gFiFoPDOInfo.u8LastWkcErrCnt != gFiFoPDOInfo.u8WkcErrCnt) {
                gFiFoPDOInfo.u32WkcErrCnt++;                  
            }
            gFiFoPDOInfo.u8LastWkcErrCnt = gFiFoPDOInfo.u8WkcErrCnt;
            // Check SPI communication quality
            if (gFiFoPDOInfo.u8LastCrcErrCnt != gFiFoPDOInfo.u8CrcErrCnt) {
                gFiFoPDOInfo.u32CrcErrCnt++;
            }
            gFiFoPDOInfo.u8LastCrcErrCnt = gFiFoPDOInfo.u8CrcErrCnt;
        }       
    }    
    else{
        //TRACE_MSG("7N");
    }   
}



void PendSV_Handler_Hook (void)
{
    HandleResponseCmd();
}



/***************************************************************************
* Purpose   ....: SysTick_Handler
* Input     ....:
*    @param ....: None
* Output    ....:
*    @param ....: None
* @Return   ....: None
* Note      ....: None
***************************************************************************/
void
SysTick_Handler_Hook (void)
{
    //HandleResponseCmd(); 
    SysTick_disable();
    EC_CmdResponsePop();
    if (gFiFoPDOInfo.u8BypassFirstEtherCatInt){
        NVIC_EnableIRQ(gFiFoPDOInfo.u8IRQNumber);
        gFiFoPDOInfo.u8BypassFirstEtherCatInt = 0;
    }
}


/**
 * @brief       GPIO PA IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The PA default IRQ, declared in startup_M480.s.
 */
#if (APP_USED_PYT_180_DB == 1) 
void GPA_IRQHandler_Hook(void)
{
    /* To check if PA.8 interrupt occurred for EtherCAT Package receiver*/
    if (GPIO_GET_INT_FLAG(PA, BIT8))
    {
        if (gFiFoPDOInfo.u8BypassFirstEtherCatInt){
            NVIC_DisableIRQ(gFiFoPDOInfo.u8IRQNumber);          
        }       
        GPIO_CLR_INT_FLAG(PA, BIT8);
        
#if (APP_ENABLE_ECHERCAT_INT1 == 1)         
        //Trigger_SysTick_Interrupt();
        EC_Master_ProcessCmd(0,0);
#endif          
    }
    else
    {
        /* Un-expected interrupt. Just clear all PB interrupts */
        PA->INTSRC = PA->INTSRC;
    }
}
#else
void GPE_IRQHandler_Hook(void)
{   
    /* To check if PE.0 interrupt occurred for EtherCAT Package receiver*/
    if(GPIO_GET_INT_FLAG(PE, BIT0))
    {
        if (gFiFoPDOInfo.u8BypassFirstEtherCatInt){
            NVIC_DisableIRQ(gFiFoPDOInfo.u8IRQNumber);          
        }       
        GPIO_CLR_INT_FLAG(PE, BIT0);
#if (APP_ENABLE_ECHERCAT_INT1 == 1)         
        EC_Master_ProcessCmd(0,0);
#endif          
    }
    else
    {
        /* Un-expected interrupt. Just clear all PB interrupts */
        PE->INTSRC = PE->INTSRC;
    }
}
#endif

#define portBYTE_ALIGNMENT    8
#define portBYTE_ALIGNMENT_MASK    ( 0x0007 )
static uint32_t gAllocCnt;
void *vZeroMalloc(int xWantedSize)
{
    void *pvReturn ;
    if( xWantedSize & portBYTE_ALIGNMENT_MASK )
    {
        /* Byte alignment required. Check for overflow. */
        if( ( xWantedSize + ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) ) ) > xWantedSize )
        {
            xWantedSize += ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) );
        }
        else
        {
            xWantedSize = 0;
        }
    }    
    pvReturn = vMalloc(xWantedSize);
    if (pvReturn != NULL){
        memset(pvReturn, 0, xWantedSize);
        gAllocCnt +=xWantedSize;
    }
    else{
        //while(1){
        return (NULL);
        //}
    }
    return (pvReturn);
}



void Trigger_PendSV_Interrupt(void)
{
    // Software Trigger PendSv Interrupt.
    SCB->ICSR = (1<<SCB_ICSR_PENDSVSET_Pos);    
}



void Trigger_SysTick_Interrupt(void)
{
    // Software Trigger PendSv Interrupt.
    SCB->ICSR = (1<<SCB_ICSR_PENDSTCLR_Pos);    
}


static void EC_Master_InterruptEnable(void)
{
    // Enable Bit31 : EtherCAT package receive
    ECM_SetEcatIntEnable((uint32_t)1<<31, 0, 0, 0); 
}


static void EC_Master_InterruptDisable(void)
{
    // Disable Bit31 : EtherCAT package receive
    ECM_SetEcatIntEnable(0, 0, 0, 0); 
}

int EC_Master_IsRunning(void)
{
    return (gFiFoPDOInfo.u8ServrRunning);
}

void EC_Master_ProcessCmd(int isCmdFinished, int nret)
{
    //TRACE_MSG("60");
#if (APP_ENABLE_ECHERCAT_INT1 == 1) 
    if (!gFiFoPDOInfo.u8ServrRunning){
        return ;
    }
#endif      
    
    if (isCmdFinished){
        gFiFoPDOInfo.nCmdState = EC_CMD_STATE_FINISHED;
        gFiFoPDOInfo.nret = nret;       
    }
    else{
        gFiFoPDOInfo.nCmdState = EC_CMD_STATE_START;       
    }
    // Software Trigger PendSv Interrupt.
    //Trigger_PendSV_Interrupt();
    HandleResponseCmd();
}



void EC_Master_MotionRunningEnable(int enabled)
{
    if (enabled == 1){
        gFiFoPDOInfo.u8ServrRunning = 1; 
        MSG_DBG("Server Runing : On\n");
    }
    else{
        gFiFoPDOInfo.u8ServrRunning = 0;
        MSG_DBG("Server Runing : Off\n");       
    }
}


void EC_Master_MotionRunningToggle(void)
{
    gFiFoPDOInfo.u8ServrRunning = gFiFoPDOInfo.u8ServrRunning ? 0 : 1;
}



int EC_Master_SetServerStartIndex (uint8_t index)
{
    if (index >= gMasterInfo.u8SlaveCnt){
        return (EC_ERR_SERVO_INDEX);
    }
    
    gMasterInfo.u8ServerStartIdx = index;
    return (EC_ERR_NONE);
}



int EC_Master_SetServerEndIndex(uint8_t index)
{
    if (index >= gMasterInfo.u8SlaveCnt){
        return (EC_ERR_SERVO_INDEX);
    }   
    gMasterInfo.u8ServerEndIdx = index;
    return (EC_ERR_NONE);
}



uint8_t EtherCatMasterGetDriverStartIdx (void)
{
    return gMasterInfo.u8ServerStartIdx ;
}



uint8_t EtherCatMasterGetDriverEndIdx (void)
{
    return gMasterInfo.u8ServerEndIdx;
}



void EC_Master_IncServerCount (void)
{
    gMasterInfo.u8ServerCnt++;
}


uint8_t EtherCatMasterGetDriverCnt (void)
{
    return (gMasterInfo.u8ServerCnt);
}


/*
  * Change this define for your need
  * */
  /* Velocity parameter*/


/* FIFO */
#define TEST_PDO_TO_FIFO_ONCE   1   //2
#if (APP_ENABLE_ECHERCAT_INT1 == 1)
#define TEST_RXFIFO_CNT         5
#else
#define TEST_RXFIFO_CNT         6
#endif
#define TEST_TXFIFO_CNT         5
/* CiA402 */
#define SERVO_ON_STATE          CIA402_SW_OPERATIONENABLED
#define SERVO_OFF_STATE         CIA402_SW_READYTOSWITCHON


#define TEST_MODEOP 8 //CSP Mode

static void setPdoConfigTable(PDO_CONFIG_HEAD *PDOConfig, int32_t nPDOCnt, ST_PDO_ASSIGN_INFO_T *pstPDO)
{
    const ST_SLAVE_OBJECT_INFO_T *pstODEntry;
    int32_t i,j, nObjCnt;
    uint16_t u16MapIdx, u16Idx;
    uint8_t u8BitSize;

    PDOConfig->PDOCnt = nPDOCnt;
    
    PDOConfig->SmaIdx = pstPDO->u16AssignAddr;
    u16MapIdx = pstPDO->u16MappingAddr; 
    nObjCnt = pstPDO->u8ODEntryCnt;
    pstODEntry = pstPDO->pstODEntry;
    
    for(i=0; i< nPDOCnt; i++){
        PDOConfig->MapIdx[i] = u16MapIdx+(0x10*i);
        PDOConfig->ObjsCnt[i] = nObjCnt;
        for(j=0; j < nObjCnt; j++){
            u16Idx = ODDATAIDX(pstODEntry->u32Data);
            u8BitSize = ODDATABITS(pstODEntry->u32Data);
            SetPdoConfTbl(PDOConfig, i, j, (u16Idx+(0x800*i)), 0, u8BitSize);
            pstODEntry++;
        }
    }   
}
  
static int ConfigDriverPDO(int32_t nSlvB, int32_t nSlvE, int32_t nPDOCnt, EC_MASTER_T *pstECMMaster)
{
    PDO_CONFIG_HEAD PDOConfig;
    int32_t i, j, nret; 
    for(i=nSlvB,j=0; i<=nSlvE; i++,j++){
        PDOConfig.Slave = i;
        // setup RxPDO
        setPdoConfigTable(&PDOConfig, nPDOCnt, &pstECMMaster->pstServerAttr[j].RxPDO);
        nret = ECM_EcatSdoSetPdoConfig(&PDOConfig);
        if (nret <= 0){
            MSG_DBG("Set RX PDO error\n");
            return (EC_ERR_PDO_WR);
        }
        
        // setup TxPDO
        setPdoConfigTable(&PDOConfig, nPDOCnt, &pstECMMaster->pstServerAttr[j].TxPDO);
        nret = ECM_EcatSdoSetPdoConfig(&PDOConfig);
        if (nret <= 0){
            MSG_DBG("Set RX PDO error\n");
            return (EC_ERR_PDO_WR);
        }       
    }
    
    nret = ECM_EcatConfigMap();
    if( nret < 0 ){
        MSG_DBG("ECM_EcatSetDCSync : %d\n",nret);
        return (EC_ERR_SETDCSYNC);
    }   
    MSG_DBG("ECM_EcatReconfig pass\r\n");
    SdoShowPdoConfig(nSlvB, nSlvE, 0x1C12);
    SdoShowPdoConfig(nSlvB, nSlvE, 0x1C13);

    return (EC_ERR_NONE);   
}   



int WaitServoOn (int *pnPos)
{
	uint32_t u32TargetPosition[20];	
    int i, nret = 0, nDrvIdx, nExit = 1;
    uint16_t  u16StatusWord, u16CtlWord, u16RxPDOSize, u16OrgCtlWord;
    uint8_t u8FifoCnt=0, u8MonitorDrvNo = 7;
    
    MSG_DBG("Start WaitServoOn\n");
    u16RxPDOSize = RxPDODATASIZE();
 	  //pnPos[3]=0x12345678 ;
    for (nDrvIdx = 0; nDrvIdx < EtherCatMasterGetDriverCnt(); nDrvIdx++) {
         EtherCatSetTargetPos(nDrvIdx, pnPos[nDrvIdx]);	
		}
		for (i = 0; i < 1000; i++) {
			//if (u8FifoCnt < (TEST_RXFIFO_CNT - 2)){
			if (1){
					nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, u16RxPDOSize, &u8FifoCnt, 0, 0, 0);
					if (nret == 5 || nret == 7){
							nExit = 1;
							//Get valid data
							for (nDrvIdx = 0; nDrvIdx < EtherCatMasterGetDriverCnt(); nDrvIdx++) {

											EtherCatGetTargetPos(nDrvIdx, (uint32_t*)&u32TargetPosition[nDrvIdx]);
									if (nDrvIdx == 3){
										MSG_DBG("Driver %d: Target Pos:%04X(%d), Act Pos:%04X(%d)\n", 
										3, u32TargetPosition[3], u32TargetPosition[3], pnPos[3], pnPos[3]);								
									
										}
									EtherCatGetActualPos(nDrvIdx, (uint32_t*)&pnPos[nDrvIdx]);

									//EtherCatSetTargetPos(nDrvIdx, pnPos[nDrvIdx]);
									EtherCatGetStatusWord(nDrvIdx, &u16StatusWord);
									EtherCatGetCtrlWord(nDrvIdx, &u16CtlWord);
									u16OrgCtlWord = u16CtlWord;
									nret = Cia402Control(1, u16StatusWord, &u16CtlWord);
									EtherCatSetCtrlWord(nDrvIdx, u16CtlWord);
									MSG_DBG("(%d,%d) S:0x%04X C:cur:0x%04X, new:0x%04X\n" \
											, nDrvIdx, i\
											, u16StatusWord \
											, u16OrgCtlWord, u16CtlWord);
									if (nret == 0) {
											nExit = 0;
									}else if (nret == 1){
											MSG_DBG("%d Position offset %d\n",nDrvIdx,pnPos[nDrvIdx]);
									}                       
							}
							if (nExit) {
									MSG_DBG("WaitServoOn PASS\n");
									MSG_DBG("Driver %d: Target Pos:%04X(%d), Act Pos:%04X(%d)\n", 
									2, u32TargetPosition[2], u32TargetPosition[2], pnPos[2], pnPos[2]);	


								
									MSG_DBG("Driver %d: Target Pos:%04X(%d), Act Pos:%04X(%d)\n", 
									3, u32TargetPosition[3], u32TargetPosition[3], pnPos[3], pnPos[3]);								
									return 1;
							}
						}
        }
				else{
					//MSG_DBG("FiFo Full:%d\n", u8FifoCnt);
					//        UserDelay(1000000);
					//u8FifoCnt = 0;
				}
        UserDelay(10000);
    }
    MSG_ERR("WaitServoOn timeout\n");
    return 0;
}



int AlignmentPosition (int *pnPos)
{
    int i, DrvIdx, nWrCnt, nret;
    uint16_t u16PDOSize;
    
    nWrCnt = 0;
    u16PDOSize = RxPDODATASIZE();    
    for (i = 0; i < 60; i++) {
        nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_WR | ECM_FIFO_RD), 1, RxPDOData, TxPDOData, u16PDOSize, 0, 0, 0, 0);
       
        if (nret == 5 || nret == 7) {           
            //Get valid data(5) or read/write(7)
            for (DrvIdx = 0; DrvIdx < EtherCatMasterGetDriverCnt(); DrvIdx++) {
                EtherCatSetCtrlWord(DrvIdx, 0xF);
                EtherCatGetActualPos(DrvIdx, (uint32_t*)&pnPos[DrvIdx]);

                // CSP Mode
                EtherCatSetTargetPos(DrvIdx,pnPos[DrvIdx]);
            }
        }
        if (nret == 7) {                
            //Get valid data and write back
            if (nWrCnt) {
                for (DrvIdx = 0; DrvIdx < EtherCatMasterGetDriverCnt(); DrvIdx++) {             
                    MSG_DBG("(%d) Position at %d(0x%X))\r\n", DrvIdx, pnPos[DrvIdx],  pnPos[DrvIdx]);
                }
                return 1;
            }
            nWrCnt++;
        }
        UserDelay(1000);
    }
    MSG_ERR("AlignmentPosition TIMEOUT\n");
    
    return 0;
}

#if 1

/*
 *  Do PDO data exchange and get the 402 state back
 *  Notice : only for single axis in one driver
 * */
int PdoExchangeAndGet402State(uint8_t SlvIdx, uint8_t AxisIdx, uint8_t *pState)
{
#if 1
    int i = 0, nret;
    uint16_t u16PDOSize;
    uint16_t u16StatusWord;

    for (i = 0; i < 60; i++) {
        u16PDOSize = RxPDODATASIZE();
        nret = ECM_EcatPdoFifoDataExchangeAdv((ECM_FIFO_RD), 1, RxPDOData, TxPDOData, u16PDOSize, 0, 0, 0, 0);
        if (nret == 5 || nret == 7) {  
            EtherCatGetStatusWord(SlvIdx, &u16StatusWord);
            *pState = (u16StatusWord & CIA402_SW_STATE_MASK);
            return 1;
        }
        UserDelay(1000);
    }
    return 0;
#else   
    int i = 0;
    uint8_t u8Data;
    TXPDO_ST_DEF_T  *pAllDevTx = (TXPDO_ST_DEF_T *)TxPDOData;
    uint16_t u16PDOSize;
    for (i = 0; i < 60; i++) {
        u16PDOSize = sizeof(RXPDO_ST_DEF_T);
        u8Data = ECM_EcatPdoDataExchange(ECM_PDO_RD_OP, RxPDOData, TxPDOData, &u16PDOSize);
        if ((u8Data & ECM_PDO_RD_OP) == ECM_PDO_RD_OP) {
            *pState = (pAllDevTx->Drv[SlvIdx].Axis[AxisIdx].u16StaWord & CIA402_SW_STATE_MASK);
            return 1;
        }
        UserDelay(1000);
    }
    return 0;
#endif  
}
#endif

static void _ec_delay(int loop)
{
    int i;
    for(i=0; i < loop; i++){
        UserDelay(1000000);
    }
}



static int ec_slave_scan(uint32_t u32CanOpenOPMode)
{
    int nret;
    
    nret = ec_slave_probe(gMasterInfo.u8SlaveCnt, u32CanOpenOPMode, &gMasterInfo);
    if (nret == EC_ERR_NONE){
        uint8_t u8ServerMotorCount = EtherCatMasterGetDriverCnt();
        if (u8ServerMotorCount){
            int nCount = sizeof(int)*u8ServerMotorCount;
            
            gnServerMotorPos = (int*)vZeroMalloc(nCount);
            if (!gnServerMotorPos){
                return (EC_ERR_MALLOC);
            }
 
        }       
    }
        
    return (nret);
}

static int ec_master_init_old(uint32_t spi_clock, uint32_t u32CanOpenOpMode, uint32_t u32ActiveCode, uint32_t u32DCTimes_us)
{
    int i = 0, DrvIdx = 0, AxisIdx = 0;
    int nret = 0;
    uint8_t u8SlaveId;

    uint8_t u8Version = 0;
    uint8_t u8State = 0;
    uint16_t u16RxPDOSize = 0, u16TxPDOSize = 0, u16SpiSize = 0;
    
    memset(RxPDOData, 0, sizeof(RxPDOData));
    memset(TxPDOData, 0, sizeof(TxPDOData));    

#ifndef DEBUG_DRIVER_INFO
    UserSetCrcType(3);

    _ec_delay(10);
    u16SpiSize = TEST_SPI_DATA_SIZE;

    u8Version = ECM_InitLibrary(&u16SpiSize);
    if (u8Version == 0) {
        MSG_ERR("ECM_InitLibrary : FAILED\r\n");
        return -1;
    }
    MSG_DBG("FW Ver(0x%X)\r\n", u8Version);
    //_ec_delay();

    nret = ECM_EcatInit(u32ActiveCode, u32DCTimes_us);
    if (nret <= 0) {
        MSG_ERR("ECM_EcatInit : Failed\r\n");
        ECM_SlaveInfoGet(0, ECM_SLV_INFO_ALstatuscode, (uint8_t *)&u16RxPDOSize);
        MSG_ERR("ALstatuscode 0x%x\n",u16RxPDOSize);
        return -1;
    }
    gMasterInfo.u8SlaveCnt = ECM_EcatSlvCntGet();	
    MSG_DBG("Slave count %d, %d\r\n", gMasterInfo.u8SlaveCnt, TEST_SLV_CNT);	
    //_ec_delay();  
    //0~127：從站站號
    //0xFF ：所有從站
    u8SlaveId = 0xFF;
    nret = ECM_EcatStateGet(u8SlaveId, &u8State);
    MSG_DBG("(%d) ECM_EcatStateGet return %d, State 0x%X\n",u8SlaveId,nret,u8State);
    if (nret <= 0) {
        MSG_ERR("ECM_EcatStateGet : Failed\r\n");
        return -1;      
    }
    if(u8State & EC_STATE_ERROR){
        MSG_DBG("Ack state:ECM State return err:%d\n", u8State);
        nret = ECM_EcatStateSet(u8SlaveId, (EC_STATE_ACK | EC_STATE_PRE_OP));
        MSG_DBG("ECM_EcatStateSet(%d, 0x%X) return %d\n",u8SlaveId,(EC_STATE_ACK | EC_STATE_PRE_OP), nret);
        nret = ECM_EcatStateGet(u8SlaveId, &u8State);
        MSG_DBG("(%d) ECM_EcatStateGet return %d, State 0x%X\n",u8SlaveId,nret,u8State);
    }
    gMasterInfo.u8SlaveCnt = ECM_EcatSlvCntGet();
#else	
    gMasterInfo.u8SlaveCnt = 14;	
#endif // #ifdef DEBUG_DRIVER_INFO	

    if (gMasterInfo.u8SlaveCnt < TEST_SLV_CNT) {
        MSG_ERR("ERROR : Slave count %d < %d\r\n", gMasterInfo.u8SlaveCnt, TEST_SLV_CNT);
        return -1;
    }
    MSG_DBG("Slave count %d, %d\r\n", gMasterInfo.u8SlaveCnt, TEST_SLV_CNT);
    nret = ec_slave_scan(u32CanOpenOpMode);
    if (nret != EC_ERR_NONE){
        MSG_ERR("ERROR : ec_slave_scan()\r\n");
        return -1;          
        }
	
#if 1
        nret = ECM_StateCheck(0xFF, EC_STATE_PRE_OP, 10000);// Set mode must be at PRE-OP state
        // Select all slaves command: 0xFF, there's only 128 slaves totally.
        if(nret == 0){
            MSG_ERR("ERROR : ECM_StateCheck()\r\n");
            return -1;
        }
		//
#if 1
		else{
			uint16_t u16ErrorCode = 0;
			uint16_t u16AlarmCode=0;
			uint8_t  u8ErrorRegister;
			EtherCatSlaveSdoRead(0, 0x603F, 0, 2, (uint8_t*)&u16ErrorCode);
			MSG_DBG("Common Error Code(0x603F) : %x\r\n", u16ErrorCode);
			EtherCatSlaveSdoRead(0, 0x1001, 0, 1, (uint8_t*)&u8ErrorRegister);
			MSG_DBG("Common Error Reg.(0x1001) : %x\r\n", u8ErrorRegister);			
			EtherCatSlaveSdoRead(0, 0x2001, 0, 2, (uint8_t*)&u16AlarmCode);
			MSG_DBG("Delta Alarm Code(0x2001) : %x\r\n", u16AlarmCode);
		}
#endif
		
#else    
    for(i=0;i<gMasterInfo.u8SlaveCount;i++){
        nret = ECM_EcatStateGet(i, &u8State);
        MSG_DBG("(%d) ECM_EcatStateGet return %d, State 0x%X\n",i,nret,u8State);
        if(u8State & EC_STATE_ERROR){
            nret = ECM_EcatStateSet(i, (EC_STATE_ACK | EC_STATE_PRE_OP));
            MSG_DBG("ECM_EcatStateSet(%d, 0x%X) return %d\n",i,(EC_STATE_ACK | EC_STATE_PRE_OP), nret);
            nret = ECM_EcatStateGet(i, &u8State);
            if (nret == 0) {
                MSG_ERR("ECM_EcatStateGet(%d) return %d\n",i,nret);
                return -1;
            }
            MSG_DBG("ECM_EcatStateGet(%d) get 0x%X\n",i, u8State);
            if (u8State & EC_STATE_ERROR){
                return -1;
            }
        }else if (u8State != EC_STATE_PRE_OP){
            nret = ECM_StateCheck(i, EC_STATE_PRE_OP, 10000000);
            if (nret == 0) {
                MSG_ERR("Slave%d set state to PRE-OP fail\n",i);
                return -1;
            }
        }
    }
#endif      
    MSG_DBG("=============\r\n");
    MSG_DBG("PRE-OP state\r\n");
    MSG_DBG("=============\r\n");
    //nret = ConfigDrive(1, EtherCatMasterGetDriverStartIdx(), EtherCatMasterGetDriverStartIdx(), 0, N_AXIS_IN_ONE_DRV, 0x1600, 0x1A00, TEST_MODEOP);     
    
    if (EtherCatMasterGetDriverCnt()){
        nret = ConfigDriverPDO(EtherCatMasterGetDriverStartIdx(), EtherCatMasterGetDriverEndIdx(), 1, &gMasterInfo);
        
        if (nret != EC_ERR_NONE) {
            MSG_ERR("ConfigDrive : PDO Failed\r\n");
            return (nret);
        }
    }
    ECM_SetTxFIFOCnt(TEST_TXFIFO_CNT);
    ECM_SetRxFIFOCnt(TEST_RXFIFO_CNT);
    // Check ECM queue size first
    nret = ECM_CheckMEMSpace(TEST_PDO_TO_FIFO_ONCE);
    if (nret <= 0) {
        MSG_ERR("ECM_CheckMEMSpace : Failed\r\n");
        return -1;
    }
    MSG_DBG("ECM_CheckMEMSpace : Pass\r\n");
    ECM_InitFIFO();
    ECM_EnableFIFO(0);
    u16RxPDOSize = ECM_FifoRxPdoSizeGet();
    u16TxPDOSize = ECM_FifoTxPdoSizeGet();
    if (u16RxPDOSize != RxPDODATASIZE()) {
        MSG_ERR("RxPDO size %d != %d\r\n", u16RxPDOSize, RxPDODATASIZE());
        return -1;
    }
    if (u16TxPDOSize != TxPDODATASIZE()) {
        MSG_ERR("TxPDO size %d != %d\r\n", u16TxPDOSize, TxPDODATASIZE());
        return -1;
    }
    MSG_DBG("RxPDO size %d, RxPDODATASIZE() size %d\r\n", u16RxPDOSize, RxPDODATASIZE());
    MSG_DBG("TxPDO size %d, TxPDODATASIZE() size %d\r\n", u16TxPDOSize, TxPDODATASIZE());
    
    if (EtherCatMasterGetDriverCnt()){
        nret = SetDriverCmdOpMode(EtherCatMasterGetDriverStartIdx(), EtherCatMasterGetDriverEndIdx(), TEST_MODEOP, N_AXIS_IN_ONE_DRV);
        if(nret <=0 ){
            MSG_DBG("SetDriverCmdOpMode fail=%d\n",nret); 
            return(-1);
        }
        MSG_DBG("SetDriverCmdOpMode ret=%d\n",nret); 
    }
    if (ECM_EcatWkcErrorMaxSet(20) == 1)
        MSG_DBG("ECM_EcatWkcErrorMaxSet ok\r\n");
    else
        MSG_DBG("ECM_EcatWkcErrorMaxSet failed\r\n");

#ifdef ECM402_ENABLE
    if (EtherCatMasterGetDriverCnt()){  
#if 0			
        for (DrvIdx = EtherCatMasterGetDriverStartIdx(); DrvIdx <=EtherCatMasterGetDriverEndIdx(); DrvIdx++) {
            for (AxisIdx = 0; AxisIdx < N_AXIS_IN_ONE_DRV; AxisIdx++) {
                nret = ECM_Drv402SM_AdvConfig((DrvIdx*N_AXIS_IN_ONE_DRV) + AxisIdx, DrvIdx, TEST_CTL_WORD_OFFSET+(AxisIdx * sizeof(AXIS_RXPDO_ST_DEF_T)), TEST_STA_WORD_OFFSET+(AxisIdx * sizeof(AXIS_TXPDO_ST_DEF_T)));
                if (nret == 0) {
                    MSG_ERR("ECM_Drv402SM_AdvConfig error : %d\r\n", (DrvIdx*N_AXIS_IN_ONE_DRV) + AxisIdx);
                    return -1;
                }
            }
        }
#endif
        MSG_DBG("Set 402 state to SERVO-OFF\n");
        for (DrvIdx = EtherCatMasterGetDriverStartIdx(); DrvIdx <= EtherCatMasterGetDriverEndIdx(); DrvIdx++) {
            for (AxisIdx = 0; AxisIdx < N_AXIS_IN_ONE_DRV; AxisIdx++) {
                nret = ECM_Drv402SM_StateSet((DrvIdx*N_AXIS_IN_ONE_DRV) + AxisIdx, SERVO_OFF_STATE);
                if (nret == 0) {
                    MSG_ERR("ECM_Drv402SM_StateSet error : %d\r\n", (DrvIdx*EtherCatMasterGetDriverCnt()) + AxisIdx);
                    return -1;
                }
            }
        }
    }
#endif

    nret = ECM_StateCheck(0xFF, EC_STATE_SAFE_OP, 1000);
    if (nret == 0) {
        return -1;
    }
    MSG_DBG("=============\r\n");
    MSG_DBG("SAFE-OP state\r\n");
    MSG_DBG("=============\r\n");
  
    MSG_DBG("Check DC stable : \n");
    while (1) {
        UserDelay(1000000);
        nret = ECM_CheckDCStable();
        if (nret == 1) {
            break;
        }
    }
    MSG_DBG("PASS\r\n");
    MSG_DBG("=============\r\n");
    MSG_DBG("TO OP state\r\n");
    MSG_DBG("=============\r\n");
    nret = ECM_StateCheck(0xFF, EC_STATE_OPERATIONAL, 1000);
    if (nret <= 0) {
        for(i=0;i<gMasterInfo.u8SlaveCnt;i++){
            ECM_SlaveInfoGet(i, ECM_SLV_INFO_ALstatuscode, (uint8_t *)&u16RxPDOSize);
            MSG_DBG("(%d) ALstatuscode 0x%x\n",i,u16RxPDOSize);
        }
        MSG_DBG("Enter key to continue\n");
        WAIT_KEY();
    }
    MSG_DBG("Check DC stable : \n");
    while (1) {
        UserDelay(1000000);
        nret = ECM_CheckDCStable();
        if (nret == 1) {
            break;
        }
    }
    MSG_DBG("PASS\r\n");
    
    MSG_DBG("Start AlignmentPosition\n");
    ECM_EnableFIFO(1);  

#if 1
    MSG_DBG("Wait Key\n");      
    if (EtherCatMasterGetDriverCnt()){
      
        nret = AlignmentPosition(gnServerMotorPos);
        if (nret <= 0) {
            return -1;
        }
        
        nret = WaitServoOn(gnServerMotorPos);      
        if (nret <= 0) {
            return -1;
        }   
    }
#else       
    nret = AlignmentPosition(gnServerMotorPos);
    if (nret <= 0) {
        return -1;
    }


#ifdef ECM402_ENABLE
    for (DrvIdx = EtherCatMasterGetDriverStartIdx(); DrvIdx <=EtherCatMasterGetDriverEndIdx(); DrvIdx++) {
        for (AxisIdx = 0; AxisIdx < N_AXIS_IN_ONE_DRV; AxisIdx++) {
            nret = ECM_Drv402SM_StateSet((DrvIdx*N_AXIS_IN_ONE_DRV) + AxisIdx, SERVO_ON_STATE);
            if (nret == 0) {
                MSG_ERR("ECM_Drv402SM_StateSet error : %d\r\n", (DrvIdx*TEST_DRV_CNT) + AxisIdx);
                return -1;
            }
        }
    }
    while (1) {
        i = 1;
        for (DrvIdx = 0; DrvIdx < EtherCatMasterGetDriverCnt(); DrvIdx++) {
            for (AxisIdx = 0; AxisIdx < N_AXIS_IN_ONE_DRV; AxisIdx++) {
                nret = PdoExchangeAndGet402State(DrvIdx, AxisIdx, &u8State);
                if (nret == 0) {
                    MSG_DBG("ECM_Drv402SM_StateGet error : %d\r\n", i);
                }
                if (u8State == SERVO_ON_STATE) {
                    MSG_DBG("%d %d servo on\n", DrvIdx, AxisIdx);
                }else{
                    i = 0;
                    MSG_DBG("%d %d u8State(0x%X)\n", DrvIdx, AxisIdx, u8State);
                }
                UserDelay(100000);
            }
        }
        if (i == 1)
            break;
    }
#endif      
    MSG_DBG("DONE\n");
#endif
    //
    //  PDO example : use FIFO do cyclic data exchange
    //MSG_DBG("Enter to start application, any key to continue\n");
    //WAIT_KEY();
    //_ec_delay();  
    MSG_DBG("Start application\n");
    if (u8Version <= 0x10){
        ECM_EnableFIFO(1);
        MSG_DBG("Enable FIFO first\n");
    }
    return (EC_ERR_NONE);
}


static int ec_master_init (EC_MASTER_T *pstECMMaster, char* pbyRxPDOBuffer, char* pbyTxPDOBuffer)
{
    int nret ;	
    uint16_t u16ALStatus=0, u16SpiSize;

    uint8_t u8Version;	
    
    pstECMMaster->u8CurrentState = EC_MASTER_UNKNOWN;
    
    // initial RxPDOBuffer & TxPDOBuffer
    memset(pbyRxPDOBuffer, 0, pstECMMaster->configs.u32RxPDOBufferSize);
    memset(pbyTxPDOBuffer, 0, pstECMMaster->configs.u32TxPDOBufferSize);    

    UserSetCrcType(3);
    
    _ec_delay(10);
    u16SpiSize = TEST_SPI_DATA_SIZE;

    u8Version = ECM_InitLibrary(&u16SpiSize);
    if (u8Version == 0) {
        MSG_ERR("ECM_InitLibrary : FAILED\r\n");
        return (EC_ERR_MASTER_INIT_LIB);
    }
    pstECMMaster->u8FirmwareVersion = u8Version;
    MSG_DBG("FW Ver(0x%X)\r\n", pstECMMaster->u8FirmwareVersion);


    // initial slaves to Initial State
    nret = ECM_EcatInit(pstECMMaster->configs.u32ActiveCode, pstECMMaster->configs.u32DCTimes_us);
    if (nret <= 0) {
        MSG_ERR("ECM_EcatInit : Failed\r\n");
        ECM_SlaveInfoGet(0, ECM_SLV_INFO_ALstatuscode, (uint8_t *)&u16ALStatus);
        MSG_ERR("ALstatuscode 0x%x\n",u16ALStatus);
        return (EC_ERR_SLAVE_INIT);
    }
    
    return (EC_ERR_NONE);
}



int EtherCatMasterOpen (uint32_t u32SPIClock, uint32_t u32CanOpenOpMode, uint32_t u32ActiveCode, uint32_t u32DCTimes_us, ETHERCAT_MASTER_PDO_CB callback)
{
    int nret ;    
   
    // initial Debug trace 
    TRACE_INIT();   	
#if 1
    gMasterInfo.pPDOCallback = callback;  
    nret = nret =  ec_master_init_old(u32SPIClock, u32CanOpenOpMode, u32ActiveCode, u32DCTimes_us);
#else   
    uint16_t u16RxPDOSize, u16TxPDOSize;
	
    gMasterInfo.pPDOCallback = callback;  
	gMasterInfo.configs.u32SPIClock = u32SPIClock;
	gMasterInfo.configs.u32CanOpenOpMode = u32CanOpenOpMode;
	gMasterInfo.configs.u32ActiveCode = u32ActiveCode;
	gMasterInfo.configs.u32DCTimes_us = u32DCTimes_us;	
	
	gMasterInfo.configs.u32RxPDOBufferSize = sizeof(RxPDOData);
	gMasterInfo.configs.u32TxPDOBufferSize = sizeof(TxPDOData);	
	
    u16RxPDOSize = sizeof(RxPDOData);
    u16TxPDOSize = sizeof(TxPDOData);  
    nret =  ec_master_init(&gMasterInfo, RxPDOData, u16RxPDOSize, TxPDOData, u16TxPDOSize, u32ActiveCode, u32DCTimes_us);
    if (nret != EC_ERR_NONE){
        return (EC_ERR_NONE);
    }
#endif    
    return (nret);
}

/**
 * @brief       啟動ISR之PDO交換
 *
 * @param       None
 *
 * @return      EC_ERR_NONE
 *
 * @details     The PA default IRQ, declared in startup_M480.s.
 */
int EtherCatMasterRunning (void)
{
    int nret = EC_ERR_NONE;
    IRQn_Type   IRQn;

    if (gFiFoPDOInfo.u8Initialed == 0){
        SysTick_open();
        UserDelay(1000);
        gFiFoPDOInfo.nStartFIFO = 1;  
        ECM_ClearFIFO(0);                       //  0 for TX and RX both   

#if (APP_USED_PYT_180_DB == 1)
        /* Configure PA.8 as Input mode and enable interrupt by rising edge trigger */
        GPIO_SetMode(PA, BIT8, GPIO_MODE_INPUT);
        GPIO_EnableInt(PA, 8, GPIO_INT_FALLING);
        IRQn = GPA_IRQn;
#else
        /* Configure PE.0 as Input mode and enable interrupt by rising edge trigger */
        GPIO_SetMode(PE, BIT0, GPIO_MODE_INPUT);
        GPIO_EnableInt(PE, 0, GPIO_INT_FALLING);
        IRQn = GPE_IRQn;
#endif  
        TRACE_MSG("G\n");
        gFiFoPDOInfo.u8Initialed = 1;
        EC_Master_MotionRunningEnable(1); 
        gFiFoPDOInfo.u8IRQNumber = IRQn;
    }
    if (gFiFoPDOInfo.u8EtherCATDataPackageInterrupt == 0){
        gFiFoPDOInfo.u8EtherCATDataPackageInterrupt = 1;
        gFiFoPDOInfo.u8BypassFirstEtherCatInt = 1;      
        EC_Master_InterruptEnable();    
        NVIC_EnableIRQ(gFiFoPDOInfo.u8IRQNumber);
    }
    
    return (nret);
}



/**
 * @brief       停止ISR之PDO交換
 *
 * @param       None
 *
 * @return      EC_ERR_NONE
 *
 * @details     Disable PA/PE Interrupt and waiting command finished of SPI.
 */
int EtherCatMasterStop (void)
{
    if (gFiFoPDOInfo.u8EtherCATDataPackageInterrupt == 1){
        if (gFiFoPDOInfo.u8IRQNumber != 0){
            NVIC_DisableIRQ(gFiFoPDOInfo.u8IRQNumber);
#if (APP_USED_PYT_180_DB == 1)        
            GPIO_CLR_INT_FLAG(PA, BIT8);
#else
            GPIO_CLR_INT_FLAG(PE, BIT0);
#endif // APP_USED_PYT_180_DB == 1  
        }
        while (gFiFoPDOInfo.nCmdState != EC_CMD_STATE_NONE){}
        EC_Master_InterruptDisable();           
        gFiFoPDOInfo.u8EtherCATDataPackageInterrupt = 0;
        
    }
    return (EC_ERR_NONE);
}



static void _doEtherCATMasterWaitReady(void)
{
    while (1){
        if (gFiFoPDOInfo.nCmdState == EC_CMD_STATE_NONE &&
            gFiFoPDOInfo.u8EtherCATDataPackageInterrupt == 0){
            return ;
        }
    }   
}


/**
 * @brief       讀取SDO of Slave
 *
 * @param       None
 *
 * @return      EC_ERR_NONE
 *
 * @details     Disable PA/PE Interrupt and waiting command finished of SPI.
 */

int EtherCatSlaveSdoRead(uint8_t Slave, \
        uint16_t Index, \
        uint8_t SubIndex, \
        uint16_t size, \
        uint8_t *Data)
{
    
    int32_t Timeout = 2000000000;
    int nret;

    _doEtherCATMasterWaitReady();
    nret = ECM_EcatSdoRead(Slave, Index, SubIndex, size, Timeout, Data);
    
    if (nret <= 0){
        return (EC_ERR_CMD_RD);
    }
    return (EC_ERR_NONE);
}


/**
 * @brief       寫入SDO of Slave
 *
 * @param       None
 *
 * @return      EC_ERR_NONE when write successful, otherwise return EC_ERR_CMD_WR.
 *
 * @details     Disable PA/PE Interrupt and waiting command finished of SPI.
 */
int EtherCatSlaveSdoWrite (uint8_t Slave, \
        uint16_t Index, \
        uint8_t SubIndex, \
        uint16_t size, \
        uint8_t *Data)
{
    int32_t Timeout = 2000000000;
    int nret;
    
    _doEtherCATMasterWaitReady();   
    nret = ECM_EcatSdoWrite(Slave, Index, SubIndex, size, Timeout, Data);
    
    if (nret <= 0){
        return (EC_ERR_CMD_WR);
    }
    return (EC_ERR_NONE);
}


/*
 * Desc
 *      Read data from Rx/Tx PDO .
 * Param
 *      pu8PDOBuffer: pointer to RxPDO or TxPDO.
 *      pstPDOEntry: pointer to Slave OD..
 *      nIdx: Objext Index.
 *      pu32Data: pointer to buffer of data.
 *      u8Offset: offset of data.
 * Return
 *      EC_ERR_NONE : No error
 *      EC_ERR_BOUNDARY: read data out of boundary.
 */
static int _rdPDOBuffer(uint8_t *pu8PDOBuffer, EC_SLAVE_PDO_OFFSET_T *pstPDOEntry, int nIdx, uint8_t *pu8Data, uint8_t u8Offset)
{
    uint8_t *pu8TXBuffer; 
    int nDataBytes, nDataOffset;
    
    // 檢查索引是否大於陣列大小
    if (nIdx > pstPDOEntry[0].u8Bytes){
        return (EC_ERR_BOUNDARY);
    }

    nDataBytes = pstPDOEntry[nIdx].u8Bytes;
    nDataOffset = pstPDOEntry[nIdx].u16Offset + u8Offset;
    pu8TXBuffer = pu8PDOBuffer+nDataOffset;
//#ifdef DEBUG_DRIVER_INFO
    gRxTxBufferOffset = nDataOffset;
//#endif				
    //printf("Device %d, offset=%d, bytes=%d\n", u8DeviceIdx, nDataOffset, nDataBytes);
    if (nDataBytes == 1){
        *pu8Data = *pu8TXBuffer;
    }
    else if (nDataBytes == 2){
        *pu8Data++ = *pu8TXBuffer++;
        *pu8Data = *pu8TXBuffer;    
    }
    else if (nDataBytes == 3){
        *pu8Data++ = *pu8TXBuffer++;
        *pu8Data++ = *pu8TXBuffer++;        
        *pu8Data = *pu8TXBuffer;        
    }   
    else{
        *pu8Data++ = *pu8TXBuffer++;
        *pu8Data++ = *pu8TXBuffer++;
        *pu8Data++ = *pu8TXBuffer++;            
        *pu8Data = *pu8TXBuffer;
    }
    return (EC_ERR_NONE);   
}



/*
 * Desc
 *      Wrtie data to RxPDO/TxPDO
 * Param
 *      pu8PDOBuffer: pointer to RxPDO or TxPDO. 
 *      pstPDOEntry: pointer to Slave OD..
 *      nIdx: Objext Index.
 *      u32Data: value of data.
 *      u8Offset: offset of data.
 * Return
 *      EC_ERR_NONE : No error
 *      EC_ERR_BOUNDARY: read data out of boundary.
 */
static int _wrPDOBuffer(uint8_t *pu8PDOBuffer, EC_SLAVE_PDO_OFFSET_T *pstPDOEntry, int nIdx, uint32_t u32Data, uint8_t u8Offset)
{
    uint8_t *pu8RXBuffer; 
    UN_CVT cvt;
    int nDataBytes, nDataOffset;
    
    // 檢查索引是否大於陣列大小 
    if (nIdx > pstPDOEntry[0].u8Bytes){
        return (EC_ERR_BOUNDARY);
    }
    
    nDataBytes = pstPDOEntry[nIdx].u8Bytes;
    nDataOffset = pstPDOEntry[nIdx].u16Offset + u8Offset;
    cvt.l = u32Data;
    pu8RXBuffer = pu8PDOBuffer+nDataOffset;
//#ifdef DEBUG_DRIVER_INFO
    gRxTxBufferOffset = nDataOffset;
//#endif		
    //printf("Device %d, offset=%d, bytes=%d\n", u8DeviceIdx, nDataOffset, nDataBytes);     
    if (nDataBytes == 1){
        *pu8RXBuffer = cvt.b[0];
    }
    else if (nDataBytes == 2){
        *pu8RXBuffer++ = cvt.b[0];
        *pu8RXBuffer   = cvt.b[1];      
    }
    else if (nDataBytes == 3){
        *pu8RXBuffer++ = cvt.b[0];      
        *pu8RXBuffer++ = cvt.b[1];
        *pu8RXBuffer   = cvt.b[2];      
    }   
    else{
        *pu8RXBuffer++ = cvt.b[0];
        *pu8RXBuffer++ = cvt.b[1];  
        *pu8RXBuffer++ = cvt.b[2];
        *pu8RXBuffer   = cvt.b[3];
    }
    return (EC_ERR_NONE);   
}



int EtherCatGetVidPid(uint8_t u8DeviceIdx, uint32_t *pu32Vid, uint32_t *pu32Pid)
{
    EC_SLAVE_VID_PID_T *pstSlaveVidPidTable;
    
    if (u8DeviceIdx > EtherCatGetDevicesCnt()){
        return (EC_ERR_BOUNDARY);
    }
    pstSlaveVidPidTable = &gMasterInfo.pstSlaveVidPidTable[u8DeviceIdx];
    *pu32Vid = pstSlaveVidPidTable->u32Vid; 
    *pu32Pid = pstSlaveVidPidTable->u32Pid; 
    
    return (EC_ERR_NONE);
}



int EtherCatGetDevicesCnt(void)
{
    return (gMasterInfo.u8SlaveCnt);
}


int EtherCatGetDOutCnt(void)
{
    if (!gMasterInfo.stSlaveOD.DOut){
        return (0);
    }
    return (gMasterInfo.stSlaveOD.DOut[0].u8Bytes);
}

int EtherCatGetDInCnt(void)
{
    if (!gMasterInfo.stSlaveOD.DIn){
        return (0);
    }
    return (gMasterInfo.stSlaveOD.DIn[0].u8Bytes);
}

int EtherCatGetAInCnt(void)
{
    if (!gMasterInfo.stSlaveOD.AIn){
        return (0);
    }
    return (gMasterInfo.stSlaveOD.AIn[0].u8Bytes);
}

int EtherCatGetAOutCnt(void)
{
    if (!gMasterInfo.stSlaveOD.AOut){
        return (0);
    }
    return (gMasterInfo.stSlaveOD.AOut[0].u8Bytes);
}


int EtherCatGetDInVal(uint8_t u8Idx, uint32_t *pu32Data)
{
    return _rdPDOBuffer(TxPDOData, gMasterInfo.stSlaveOD.DOut, u8Idx, (uint8_t*)pu32Data , 0);
}   


int EtherCatGetAInVal(uint8_t u8Idx, uint32_t *pu32Data)
{
    return _rdPDOBuffer(TxPDOData, gMasterInfo.stSlaveOD.AOut, u8Idx, (uint8_t*)pu32Data , 0);
}   


/*
 * Descriptor : read Server RxPDO data to data
 */
static int EC_rdServerRxPDO(uint8_t u8ServerIdx, int nIdx, uint32_t *pu32Data)
{
    uint8_t u8Offset;
    
    if (u8ServerIdx >= gMasterInfo.u8ServerCnt){
        return (EC_ERR_SERVO_INDEX);
    }   
    
    //u8Offset = (u8ServerIdx <= 1) ? 0 : gMasterInfo.pstServerAttr[nServerIdx-1].RxPDO.u8DataOffset;
    u8Offset = 0;
    nIdx += gMasterInfo.pstServerAttr[u8ServerIdx].RxPDO.u16ServerPDOffsetIdx;;
    return _rdPDOBuffer(RxPDOData, gMasterInfo.stSlaveOD.ServerRx, nIdx, (uint8_t*)pu32Data, u8Offset);
}  



/*
 * Descriptor : Write Server data to RxPDO
 */
static int EC_wrServerRxPDO(uint8_t u8ServerIdx, int nIdx, uint32_t u32Data)
{
    uint8_t u8Offset;
    
    if (u8ServerIdx >= gMasterInfo.u8ServerCnt){
        return (EC_ERR_SERVO_INDEX);
    }   
    
    u8Offset = 0;
    nIdx += gMasterInfo.pstServerAttr[u8ServerIdx].RxPDO.u16ServerPDOffsetIdx;
    return _wrPDOBuffer(RxPDOData, gMasterInfo.stSlaveOD.ServerRx, nIdx, u32Data, u8Offset);
} 


/*
 * Descriptor : read Server TxPDO data to variable
 */
static int EC_rdServerTxPDO(uint8_t u8ServerIdx, int nIdx, uint8_t *pu8Data)
{
    //uint8_t u8Offset;
    
    if (u8ServerIdx >= gMasterInfo.u8ServerCnt){
        return (EC_ERR_SERVO_INDEX);
    }
    
    nIdx += gMasterInfo.pstServerAttr[u8ServerIdx].TxPDO.u16ServerPDOffsetIdx;
    return _rdPDOBuffer(TxPDOData, gMasterInfo.stSlaveOD.ServerTx, nIdx, pu8Data, 0);
}   

/*
 * Descriptor : Write data to ServerTx TxPDO
 */
int EC_wrServerTxPDO(uint8_t u8ServerIdx, int nIdx, uint32_t u32Data)
{
    uint8_t u8Offset;
    
    if (u8ServerIdx >= gMasterInfo.u8ServerCnt){
        return (EC_ERR_SERVO_INDEX);
    }   
    
    //u8Offset = (u8ServerIdx <= 1) ? 0 : gMasterInfo.pstServerAttr[u8ServerIdx-1].TxPDO.u8DataOffset;
    u8Offset = 0;
    nIdx += gMasterInfo.pstServerAttr[u8ServerIdx].RxPDO.u16ServerPDOffsetIdx;
    return _wrPDOBuffer(TxPDOData, gMasterInfo.stSlaveOD.ServerRx, nIdx, u32Data, u8Offset);
}   


int EtherCatGetCtrlWord(uint8_t u8ServerIdx, uint16_t *pu16Data)
{
    int nIdx = gMasterInfo.stSlaveOD.RxCtrlWordReg[u8ServerIdx+1].u8Idx;
    return (EC_rdServerRxPDO(u8ServerIdx, nIdx, (uint32_t*)pu16Data));
}


int EtherCatGetTargetPos(uint8_t u8ServerIdx, uint32_t *pu32Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxTargetPosReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu32Data));
}


int EtherCatGetStatusWord(uint8_t u8ServerIdx, uint16_t *pu16Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxStatusWordReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu16Data));
}

int EtherCatGetActualPos(uint8_t u8ServerIdx, uint32_t *pu32Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxActualPosReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu32Data));
}

int EtherCatGetActualTorque(uint8_t u8ServerIdx, uint16_t *pu16Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxActualTorqueReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu16Data));
}

int EtherCatGetErrorCode(uint8_t u8ServerIdx, uint16_t *pu16Data)
{
    
    int nIdx = gMasterInfo.stSlaveOD.TxErrorCodeReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu16Data));
}

int EtherCatGetTouchProbeState(uint8_t u8ServerIdx, uint16_t *pu16Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxTouchProbeStateReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu16Data));
}

int EtherCatGetTouchProbe1Pos(uint8_t u8ServerIdx, uint32_t *pu32Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxTouchProbe1PositiveEdgeReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu32Data));
}

int EtherCatGetTouchProbe2Pos(uint8_t u8ServerIdx, uint32_t *pu32Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxTouchProbe2PositiveEdgeReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu32Data));
}

int EtherCatGetFollowingErrorActualValue(uint8_t u8ServerIdx, uint32_t *pu32Data)
{
    int nIdx = gMasterInfo.stSlaveOD.TxFollowingErrorActualValueReg[u8ServerIdx+1].u8Idx ;
    return (EC_rdServerTxPDO(u8ServerIdx, nIdx, (uint8_t*)pu32Data));
}

/*
 * Descriptor : Write Dout data to RxPDO
 */
int EtherCatSetDOutVal(uint8_t u8Idx, uint32_t u32Data)
{
    u8Idx++;
    return _wrPDOBuffer(RxPDOData,gMasterInfo.stSlaveOD.DOut, u8Idx, u32Data , 0);
}   



/*
 * Descriptor : Write Aout data to RxPDO
 */
int EtherCatSetAOutVal(uint8_t u8Idx, uint32_t u32Data)
{
    u8Idx++;
    return _wrPDOBuffer(RxPDOData,gMasterInfo.stSlaveOD.AOut, u8Idx, u32Data , 0);
}   



int EtherCatSetCtrlWord(uint8_t u8ServerIdx, uint16_t u16Data)
{
    return (EC_wrServerRxPDO(u8ServerIdx, gMasterInfo.stSlaveOD.RxCtrlWordReg[u8ServerIdx+1].u8Idx, u16Data));
}



int EtherCatSetTargetPos(uint8_t u8ServerIdx, uint32_t u32Data)
{
    return (EC_wrServerRxPDO(u8ServerIdx, gMasterInfo.stSlaveOD.RxTargetPosReg[u8ServerIdx+1].u8Idx, u32Data));
}


int EtherCatSetTouchProbeMode(uint8_t u8ServerIdx, uint16_t u16Data)
{
    return (EC_wrServerRxPDO(u8ServerIdx, gMasterInfo.stSlaveOD.RxTouchProbeModeReg[u8ServerIdx+1].u8Idx, u16Data));
}



int EtherCatSetStatusWord(uint8_t u8ServerIdx, uint32_t u32Data)
{
    return (EC_wrServerTxPDO(u8ServerIdx, gMasterInfo.stSlaveOD.TxStatusWordReg[u8ServerIdx+1].u8Idx, u32Data));
}



int EtherCatSetActualPos(uint8_t u8ServerIdx, uint32_t u32Data)
{
    return (EC_wrServerTxPDO(u8ServerIdx, gMasterInfo.stSlaveOD.TxActualPosReg[u8ServerIdx+1].u8Idx , u32Data));
}



int EtherCatSetErrorCode(int u8ServerIdx, uint32_t u32Data)
{
    return (EC_wrServerTxPDO(u8ServerIdx, gMasterInfo.stSlaveOD.TxErrorCodeReg[u8ServerIdx+1].u8Idx, u32Data));
}

