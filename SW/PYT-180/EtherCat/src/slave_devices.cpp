/******************************************************************************
 *  File    :   slave_info.cpp
 *  Version :   1.00
 *  Date    :   2022/03/23
 *  Author  :   XFORCE
 *
 *
*****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "NuMicro.h"
#include "EcmUsrDriver.h"
#include "platform.h"
#include "Utility.h"
#include "PdoDefine.h"
#include "app_config.h"
#include "slave_devices.h"
#include "device_table.cpp"

//#define DEBUG_DRIVER_INFO   1

#ifdef DEBUG_DRIVER_INFO
extern unsigned int gRxTxBufferOffset;

#define MOTOR_MAX_COUNT  20
typedef struct st_log_wrrd_pdo_t{
	unsigned rx[20];
	unsigned tx[20];
} ST_LOG_WRRD_PDO_T;

ST_LOG_WRRD_PDO_T gstLogWrRdPDO[MOTOR_MAX_COUNT];
#endif

typedef struct st_canopen_op_mode_regs 
{
    uint32_t    u32DeviceRegIdx;
    EC_SLAVE_PDO_REG_IDX_T  **pPDORegIdx;
} ST_CANOPEN_OP_MODE_REGS_T;




/*
 * Desc
 *      read Vid/Pid of slave
 * Param
 *      slaveIndex:
 *      pVid:
 *      pPid:
 * Return
 *      ECM_DEVICE_NONE : No error
 *      ECM_DEVICE_XXX: Error occur
 * */
static int ec_get_vid_pid(uint8_t slaveIndex, uint32_t *pVid, uint32_t *pPid)
{
        uint32_t u32Vid, u32Pid;
    int nret;
    
#ifdef DEBUG_DRIVER_INFO
#if 1
    if (slaveIndex <= 12){
		// for SanyoDenki RS2 EtherCAT 
        //*pVid = 0x01b9;
        //*pPid = 0x00000002;		
		
		// for 三洋
        *pVid = 0x1b9;
        *pPid = 0x2;
    }
    else{
        *pVid = 0x66f;		//國際
        *pPid = 0x60380008;     
    }

#else
    *pVid = 0x066f;
    *pPid = 0x60380004;
#endif  
#else
    nret = ECM_SlaveInfoGet(slaveIndex, 0x00, (uint8_t*)&u32Vid);
    if (nret != 1){
        return (EC_ERR_CMD_RD);             
    }       
    // 0x01 :get code of Product;   
    nret = ECM_SlaveInfoGet(slaveIndex, 0x01, (uint8_t*)&u32Pid);
    if (nret!= 1){
        return (EC_ERR_CMD_RD);         
    }   
        *pVid = u32Vid;
        *pPid = u32Pid;
#endif    
    return (EC_ERR_NONE);
}



/*
 * Desc
 *      Find First Server Index.
 *
 * Param
 *      u8SlaveIndex: 
 *      pIsFirstAttrACServer: First OD Entry for slave
 *      nFindFirstServer: Find First Server
 *      pstDeviceCnt :
 * Return
 *      pstDeviceCnt->u8ServerCnt : Server Count
 *      pstDeviceCnt->u8FirstServerIndex: First Server Index.
 * */
static void ac_server_count(uint8_t u8SlaveIndex,
                            int *pnIsFirstAttrACServer, 
                            int *pnFindFirstServer,
                            DEVICE_TYPE_COUNT_T*pstDeviceCnt)
{
    if (*pnIsFirstAttrACServer){
        pstDeviceCnt->u8ServerCnt +=1;
        *pnIsFirstAttrACServer =0;
        
        if (*pnFindFirstServer == 1){
            pstDeviceCnt->u8FirstServerIndex = u8SlaveIndex;
            *pnFindFirstServer = 0;
        }
    }   
}



/*
 * Desc
 *      Add Count of the In and Ount OD.
 *
 * Param
 *      isInOD: is In of OD.
 *      pstDeviceCnt :
 * Return
 *      pstDeviceCnt->u8AllIn : Count In of OD.
 *      pstDeviceCnt->u8AllOut: Count Out of OD.
 * */
static void add_od_in_out_cnt(int isInOD, DEVICE_TYPE_COUNT_T*pstDeviceCnt)
{
    if (isInOD == true){
        pstDeviceCnt->u8AllIn++;      
    }
    else{
        pstDeviceCnt->u8AllOut++;
    }
}



/*
 * Desc
 *      Is address of PDO assignment ?
 *
 * Param
 *      u16Addr: address of Index.
 * Return
 *      1 : Address is PDO assignment.
 *      0 : Address is'nt PDO assignment.
 * */
static int IsPDOAssignmentAddr(uint16_t u16Addr)
{
    return (u16Addr >= 0x1C10 && u16Addr <= 0x1C13) ? 1 : 0;
}


/*
 * Desc
 *      scan count of device type
 * Param
 *      nSlaveCnt: Slave counts
 *    pstDeviceCnt:
 * Return
 *      ECM_DEVICE_NONE : No error
 *      ECM_DEVICE_XXX: Error occur
 * */
static int ec_scan_slave_device_type(int nSlaveCnt, DEVICE_TYPE_COUNT_T*pstDeviceCnt, EC_SLAVE_VID_PID_T *pstSlaveVidPidTable)
{
    const ST_SLAVE_OBJECT_INFO_T *pstODInfo;
    uint32_t u32Vid, u32Pid;
    int      nSlaveIndex, i, ret; 
    int      nisFirstAttrACServer, nFindFirstServer=1;
    
    for (nSlaveIndex=0; nSlaveIndex < nSlaveCnt; nSlaveIndex++){
        
        ret = ec_get_vid_pid(nSlaveIndex, &u32Vid, &u32Pid);
        if (ret != EC_ERR_NONE){
            return (EC_ERR_CMD_RD);
        }
        
        MSG_DBG("Slave(%d) Info: Vid=0x%x, Pid=0x%x\n", nSlaveIndex, u32Vid, u32Pid); 
        
        // IsValidate slave ?
        for (i=0; i < ARRAY_LENGTH(slaves_device_table); i++){
            if (u32Vid == slaves_device_table[i].u32VID && u32Pid == slaves_device_table[i].u32PID){  
                pstSlaveVidPidTable[nSlaveIndex].u32Vid = u32Vid;
                pstSlaveVidPidTable[nSlaveIndex].u32Pid = u32Pid;               
                pstODInfo = slaves_device_table[i].pstObjectInfo;
                nisFirstAttrACServer = 1;
                
                while(!ISDEVICEEND(pstODInfo->u32Attr)){
                    if (ISCOUPLER(pstODInfo->u32Attr)){ 
                        pstDeviceCnt->u8Coupler++;
                    }
                    else if (ISDATAIN(pstODInfo->u32Attr)){
                        pstDeviceCnt->u8DIn++;
                        add_od_in_out_cnt(true, pstDeviceCnt);
                    }
                    else if (ISDATAOUT(pstODInfo->u32Attr)){
                        pstDeviceCnt->u8DOut++; 
                        add_od_in_out_cnt(false, pstDeviceCnt);    
                    }
                    else if (ISANALOGIN(pstODInfo->u32Attr)){
                        pstDeviceCnt->u8AIn++;  
                        add_od_in_out_cnt(true, pstDeviceCnt);
                    }
                    else if (ISANALOGOUT(pstODInfo->u32Attr)){
                        pstDeviceCnt->u8AOut++;    
                        add_od_in_out_cnt(false, pstDeviceCnt);    
                    }
                    else if (IsServerIn(pstODInfo->u32Attr)){
                        if (!IsPDOAssignmentAddr(HI_WORD(pstODInfo->u32Data))){
                            pstDeviceCnt->u8ServerIn++;
                            add_od_in_out_cnt(true, pstDeviceCnt);
                        }
                        ac_server_count(nSlaveIndex, &nisFirstAttrACServer, &nFindFirstServer, pstDeviceCnt);
                    }
                    else if (IsServerOut(pstODInfo->u32Attr)){
                        if (!IsPDOAssignmentAddr(HI_WORD(pstODInfo->u32Data))){                       
                            pstDeviceCnt->u8ServerOut++;
                            add_od_in_out_cnt(false, pstDeviceCnt);
                        }
                        ac_server_count(nSlaveIndex, &nisFirstAttrACServer, &nFindFirstServer, pstDeviceCnt);              
                    }
                    else {
                        return (EC_ERR_SLAVE_UNKNOWN);             
                    }   
                    pstODInfo++;
                }
                break;
            }
        }
    }
    return (EC_ERR_NONE);
}   


static void ec_slave_set_pdo_assign(const ST_SLAVE_OBJECT_INFO_T *pstODInfo,ST_PDO_ASSIGN_INFO_T*pstPDOAssign)
{
    uint8_t  u8DeviceType;
    uint8_t  u8ODCnt, u8DataSizes;
    
    pstPDOAssign->u16AssignAddr = HI_WORD(pstODInfo->u32Data);
    pstPDOAssign->u16MappingAddr = LOW_WORD(pstODInfo->u32Data);
    pstPDOAssign->pstODEntry = pstODInfo + 1;
    
    u8DeviceType = ECM_DEVICE_TYPE(pstODInfo->u32Attr);
    u8ODCnt = u8DataSizes = 0;
    while(1){
        pstODInfo++;        
        if (u8DeviceType == ECM_DEVICE_TYPE(pstODInfo->u32Attr)){
            u8ODCnt++;  
            u8DataSizes += ODDATABYTES(pstODInfo->u32Data);
        }
        else{
            break;
        }       
    }
    pstPDOAssign->u8ODEntryCnt = u8ODCnt;
    pstPDOAssign->u8DataSizes = u8DataSizes;        
}


/*
 * Desc
 *      computer total bytes of OD Array .
 *      設定Server的讀寫的資料位置偏移數
 * Param
 *      nServerCnt : Counts of Server.
 *      pstServerAttr: pointer to Server Attribute.
 * Return
 *      NONE: 
 * */
static void ec_slave_compute_server_offset(int nServerCnt, EC_SERVER_ATTR_T *pstServerAttr)
{
    int nServerIdx, i;
    uint16_t u16RxPDOffsetIdx, u16TxPDOffsetIdx;
    uint8_t  u8RxOffset, u8TxOffset;
        
    for (nServerIdx=1; nServerIdx <= nServerCnt; nServerIdx++){
        u8RxOffset = u8TxOffset = 0;
        u16RxPDOffsetIdx = u16TxPDOffsetIdx = 0;
        for(i=0; i < nServerIdx; i++){
            u8RxOffset += pstServerAttr[i].RxPDO.u8DataSizes;
            u8TxOffset += pstServerAttr[i].TxPDO.u8DataSizes;
            u16RxPDOffsetIdx += pstServerAttr[i].RxPDO.u8ODEntryCnt;
            u16TxPDOffsetIdx += pstServerAttr[i].TxPDO.u8ODEntryCnt;                
        }
				if (nServerIdx < nServerCnt){
					  pstServerAttr[nServerIdx].RxPDO.u8DataOffset = u8RxOffset;
					  pstServerAttr[nServerIdx].TxPDO.u8DataOffset = u8TxOffset; 

					  pstServerAttr[nServerIdx].RxPDO.u16ServerPDOffsetIdx = u16RxPDOffsetIdx;
					  pstServerAttr[nServerIdx].TxPDO.u16ServerPDOffsetIdx = u16TxPDOffsetIdx; 
				}
    }
}


/*
 * Desc
 *      computer total bytes of OD Array .
 *      設定陣列個數內的總共字元數
 * Param
 *      pstPDOffset: pointer to Slave OD.
 * Return
 *      NONE: 
 * */
static void ec_slave_compute_bytes_od_array(EC_SLAVE_PDO_OFFSET_T *pstPDOffset)
{
    int i, length = pstPDOffset[0].u8Bytes;
    uint16_t u16Bytes = 0;
    
    for(i=1; i <= length; i++){
        u16Bytes += pstPDOffset[i].u8Bytes;
    }
    pstPDOffset[0].u16Offset = u16Bytes;
}

/*
 * Desc
 *      set PDO offset and .
 * Param
 *      pstPDOffset: pointer to Slave OD.
 *      pu8Index: pointer to Index of Slave OD.
 *      pu16RxPDOffset :　pointer to Index of RX/PX PDO.
 *      u8PDOBits: Bits of OD entry
 * Return
 *      ECM_DEVICE_NONE : No error
 *      EC_ERR_BOUNDERY: write data out boundary.
 * */
static int ec_slave_set_od_pdo_attr (EC_SLAVE_PDO_OFFSET_T *pstPDOffset, uint8_t *pu8Index, uint8_t u8PDOBytes, uint16_t *pu16PDOffset, EC_SLAVE_PDO_OFFSET_T *pstRxTxPDOffset, uint8_t *pu8RxTxIndex)
{
  
    if (*pu8Index > pstPDOffset[0].u8Bytes){
        return (EC_ERR_BOUNDARY);
    }
    
    // setting bytes and offset of entry of Device Type
    // 設定各種輸入型態的資料長度與存取偏移(Offset)
    pstPDOffset[*pu8Index].u8Bytes = u8PDOBytes;
    pstPDOffset[*pu8Index].u16Offset = *pu16PDOffset;     
    *pu8Index += 1;
    
    // setting bytes and offset of entry of Rx/Tx
    // 設定Rx/Tx的資料長度與存取偏移(Offset)    
    pstRxTxPDOffset[*pu8RxTxIndex].u8Bytes = u8PDOBytes;
    pstRxTxPDOffset[*pu8RxTxIndex].u16Offset = *pu16PDOffset;     
    *pu8RxTxIndex +=1;
    
    *pu16PDOffset += u8PDOBytes;
    return (ECM_DEVICE_NONE);
}



/*
 * Desc
 *      set ODs Entry and Counts.
 * Param
 *      u8SlaveCnt : Count of Slave.
 *      pstSlaveVidPidTable : pointer to table of VID/PID
 *      pstSlaveOD: pointer to Slave OD.
 *      pstServerAttr: pointer to attr of Server.
 * Return
 *      EC_ERR_NONE : No error
 *      EC_ERR_MALLOC: alloc memory fail.
 * */
static int ec_slave_set_od(uint8_t u8SlaveCnt, EC_SLAVE_VID_PID_T *pstSlaveVidPidTable, EC_SLAVE_OD *pstSlaveOD, EC_SERVER_ATTR_T *pstServerAttr)
{
    const ST_SLAVE_OBJECT_INFO_T *pstODInfo;
    int      nSlaveIndex, i, ret = EC_ERR_NONE; 
    uint32_t u32Vid, u32Pid;
    uint16_t u16RxPDOffset, u16TxPDOffset;  
    uint8_t  u8DInIdx, u8DOutIdx, u8AInIdx, u8AOutIdx;
    uint8_t  u8ACServerInIdx, u8ACServerOutIdx, u8InIdx, u8OutIdx;

    uint8_t  u8ServerIdx =0;
    
    u8DInIdx = u8DOutIdx = u8AInIdx = u8AOutIdx = u8ACServerInIdx = u8ACServerOutIdx = u8InIdx = u8OutIdx = 1;
    u16RxPDOffset = u16TxPDOffset = 0;
    
    for (nSlaveIndex=0; nSlaveIndex < u8SlaveCnt; nSlaveIndex++){
        u32Vid = pstSlaveVidPidTable[nSlaveIndex].u32Vid;
        u32Pid = pstSlaveVidPidTable[nSlaveIndex].u32Pid;           
        // 
        for (i=0; i < ARRAY_LENGTH(slaves_device_table); i++){
            if (u32Vid == slaves_device_table[i].u32VID && u32Pid == slaves_device_table[i].u32PID){ 
            
                pstODInfo = slaves_device_table[i].pstObjectInfo;
                while(!ISDEVICEEND(pstODInfo->u32Attr)){
                    if (ISCOUPLER(pstODInfo->u32Attr)){    
                    }
                    else if (ISDATAIN(pstODInfo->u32Attr)){
                        ret = ec_slave_set_od_pdo_attr(pstSlaveOD->DIn, &u8DInIdx, ODDATABYTES(pstODInfo->u32Data), &u16TxPDOffset, pstSlaveOD->Tx, &u8InIdx);
                    }
                    else if (ISDATAOUT(pstODInfo->u32Attr)){
                        ret = ec_slave_set_od_pdo_attr(pstSlaveOD->DOut, &u8DOutIdx, ODDATABYTES(pstODInfo->u32Data), &u16RxPDOffset,pstSlaveOD->Rx, &u8OutIdx);    
                    }
                    else if (ISANALOGIN(pstODInfo->u32Attr)){
                        ret = ec_slave_set_od_pdo_attr(pstSlaveOD->AIn, &u8AInIdx, ODDATABYTES(pstODInfo->u32Data), &u16TxPDOffset, pstSlaveOD->Tx, &u8InIdx);
                    }
                    else if (ISANALOGOUT(pstODInfo->u32Attr)){
                        ret = ec_slave_set_od_pdo_attr(pstSlaveOD->AOut, &u8AOutIdx, ODDATABYTES(pstODInfo->u32Data), &u16RxPDOffset, pstSlaveOD->Rx, &u8OutIdx);   
                    }
                    else if (IsServerIn(pstODInfo->u32Attr)){
                        if (!IsPDOAssignmentAddr(HI_WORD(pstODInfo->u32Data))){
                            ret = ec_slave_set_od_pdo_attr(pstSlaveOD->ServerTx, &u8ACServerInIdx, ODDATABYTES(pstODInfo->u32Data), &u16TxPDOffset, pstSlaveOD->Tx, &u8InIdx);
                        }
                        else{
                            ec_slave_set_pdo_assign(pstODInfo, &pstServerAttr[u8ServerIdx].TxPDO);
                            u8ServerIdx++;
                        }
                    }
                    else if (IsServerOut(pstODInfo->u32Attr)){
                        if (!IsPDOAssignmentAddr(HI_WORD(pstODInfo->u32Data))){
                            ret = ec_slave_set_od_pdo_attr(pstSlaveOD->ServerRx, &u8ACServerOutIdx, ODDATABYTES(pstODInfo->u32Data), &u16RxPDOffset, pstSlaveOD->Rx, &u8OutIdx);
                        }
                        else{
                            ec_slave_set_pdo_assign(pstODInfo, &pstServerAttr[u8ServerIdx].RxPDO);
                        }                       
                    }
                    else {
                        return (EC_ERR_SLAVE_UNKNOWN);              
                    }   
                    if (ret != EC_ERR_NONE){
                        return (ret);
                    }
                    pstODInfo++;
                }
                break;                              
            }
        }
    }
    // set total bytes of OD Entry
    // 設定陣列個數內的總共字元數
    ec_slave_compute_bytes_od_array(pstSlaveOD->DIn);
    ec_slave_compute_bytes_od_array(pstSlaveOD->DOut);
    ec_slave_compute_bytes_od_array(pstSlaveOD->AIn);
    ec_slave_compute_bytes_od_array(pstSlaveOD->AOut);
    ec_slave_compute_bytes_od_array(pstSlaveOD->ServerTx);
    ec_slave_compute_bytes_od_array(pstSlaveOD->ServerRx);
    ec_slave_compute_bytes_od_array(pstSlaveOD->Rx);
    ec_slave_compute_bytes_od_array(pstSlaveOD->Tx); 

    ec_slave_compute_server_offset(u8ServerIdx, pstServerAttr);
    return (EC_ERR_NONE);
}



/*
 * Desc
 *      setting OD array.
 *      取得記憶體然後設定[0]內容為OD數量
 * Param
 *      pSlaveOD: pointer to Slave OD.
 *      u8CountOD: Count OD of Slave.
 * Return
 *      ECM_DEVICE_NONE : No error
 *      EC_ERR_MALLOC: alloc memory fail.
 * */
static int create_od(EC_SLAVE_PDO_OFFSET_T **pSlaveOD, uint8_t u8CountOD)
{
    uint16_t u16BufferSize = (u8CountOD+1) * sizeof(EC_SLAVE_PDO_OFFSET_T);
    void * pBuffer = vZeroMalloc(u16BufferSize);
    if (pBuffer == NULL){
        return (EC_ERR_MALLOC);
    }
    *pSlaveOD = (EC_SLAVE_PDO_OFFSET_T *)pBuffer;
    pSlaveOD[0]->u8Bytes = u8CountOD;
    
    return(EC_ERR_NONE);
}           



/*
 * Desc
 *      Create ODs Entry and Set Counts.
 * Param
 *      pstSlaveOD: pointer to Slave OD.
 *      pstDeviceCount: pointer to Count of Slave.
 * Return
 *      ECM_DEVICE_NONE : No error
 *      EC_ERR_MALLOC: alloc memory fail.
 * */
static int ec_slave_create_od(EC_SLAVE_OD   *pstSlaveOD, DEVICE_TYPE_COUNT_T *pstDeviceCount)
{
    if (create_od(&pstSlaveOD->DIn, pstDeviceCount->u8DIn) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }
    if (create_od(&pstSlaveOD->DOut, pstDeviceCount->u8DOut) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }
    if (create_od(&pstSlaveOD->AIn, pstDeviceCount->u8AIn) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }
    if (create_od(&pstSlaveOD->AOut, pstDeviceCount->u8AOut) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }
    if (create_od(&pstSlaveOD->ServerTx, pstDeviceCount->u8ServerIn) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }
    if (create_od(&pstSlaveOD->ServerRx, pstDeviceCount->u8ServerOut) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }   
    
    if (create_od(&pstSlaveOD->Tx, pstDeviceCount->u8AllIn) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }
    if (create_od(&pstSlaveOD->Rx, pstDeviceCount->u8AllOut) == EC_ERR_MALLOC){
        return EC_ERR_MALLOC;
    }   
    
    return(EC_ERR_NONE);
}


/*
 * Desc
 *      setup specifical registers for wr/rd functions.
 *      取得特殊位址的順序索引為了讀取與儲取特殊位址函數 
 *      
 * Param
 *      size: size of specifical register array. 
 *      pstOpModeReg: pointer to specifical register array. .
 *      pPDO: pointer to assign of Server. 
 *      u8Offset : offset of register.
 * Return
 *      none
 * */
static void ec_slave_setup_mode_regs(int size, ST_CANOPEN_OP_MODE_REGS_T *pstOpModeReg, ST_PDO_ASSIGN_INFO_T *pPDO, uint8_t u8Offset)
{
    EC_SLAVE_PDO_REG_IDX_T *pPDORegIdx;
    uint8_t u8RegIdx ;
    int i, j, nIdx;
    
    for(i=0; i < pPDO->u8ODEntryCnt; i++){
        u8RegIdx = SERVERREGIDX(pPDO->pstODEntry[i].u32Attr) ;
        if (u8RegIdx == ECM_RXPDO_TXPDO_REG_NONE){
            continue;
        }
        for(j=0; j < size; j++){
            if (u8RegIdx == SERVERREGIDX(pstOpModeReg[j].u32DeviceRegIdx)){
                pPDORegIdx = *pstOpModeReg[j].pPDORegIdx;
                nIdx = pPDORegIdx[0].u8Idx + 1;
                pPDORegIdx[nIdx].u8Idx = i + 1 + u8Offset;
                pPDORegIdx[0].u8Idx++;
                break;
            }
        }
    }
}



/*
 * Desc
 *      setup CSP registers for wr/rd functions.
 * Param
 *      nServerCnt: Count of Server. 
 *      pstSlaveOD: pointer to Slave OD.
 *      pstServerAttr: pointer to attr of Server. 
 * Return
 *      EC_ERR_NONE : No error
 *      EC_ERR_MALLOC: alloc memory fail.
 * */
static int ec_slave_set_csp_mode_regs(int nServerCnt, EC_SLAVE_OD *pstSlaveOD, EC_SERVER_ATTR_T *pstServerAttr)
{
    int i, allocSize;
    
    ST_CANOPEN_OP_MODE_REGS_T stOpModeReg[] = {
        {ECM_RXPOD_REG_CTLWORD,        		 		&pstSlaveOD->RxCtrlWordReg},
        {ECM_RXPDO_REG_TARGET_POS,      			&pstSlaveOD->RxTargetPosReg},
        {ECM_RXPDO_REG_TOUCH_PROBE_MODE,      		&pstSlaveOD->RxTouchProbeModeReg},		
        {ECM_TXPDO_REG_STATUSWORD,      			&pstSlaveOD->TxStatusWordReg},
        {ECM_TXPDO_REG_ACTUAL_POS,      			&pstSlaveOD->TxActualPosReg},
        {ECM_TXPDO_REG_ERROR_CODE,     				&pstSlaveOD->TxErrorCodeReg},
        {ECM_TXPDO_REG_TOUCH_PROBE_STATE,     		&pstSlaveOD->TxTouchProbeStateReg},  
        {ECM_TXPDO_REG_TOUCH_PROBE_1_POSITIVE_EDGE, &pstSlaveOD->TxTouchProbe1PositiveEdgeReg},		
        {ECM_TXPDO_REG_TOUCH_PROBE_2_POSITIVE_EDGE, &pstSlaveOD->TxTouchProbe2PositiveEdgeReg},
        {ECM_TXPDO_REG_FOLLOWING_ERROR_ACTUAL_VALUE,&pstSlaveOD->TxFollowingErrorActualValueReg},       
        {ECM_TXPDO_REG_ACTUAL_TORQUE, 				&pstSlaveOD->TxActualTorqueReg} ,  
        {ECM_TXPDO_REG_TARGET_POS, 		            &pstSlaveOD->TxTargetPosReg} , 
    };
    
    // alloc regs structure.
    allocSize = (nServerCnt+1)*sizeof(EC_SLAVE_PDO_REG_IDX_T);
    for(i=0; i < ARRAY_LENGTH(stOpModeReg); i++){
        *stOpModeReg[i].pPDORegIdx = (EC_SLAVE_PDO_REG_IDX_T*)vZeroMalloc(allocSize);
        if (!*stOpModeReg[i].pPDORegIdx){
            MSG_DBG("Error: malloc memory fail that regs of CSP mode\n");           
            return(EC_ERR_MALLOC); 
        }
    }
    
    //u8RxPDOOffset = u8TxPDOOffset = 0;
    for(i=0; i < nServerCnt; i++){
        ec_slave_setup_mode_regs(ARRAY_LENGTH(stOpModeReg), stOpModeReg, &pstServerAttr[i].RxPDO, 0);
        ec_slave_setup_mode_regs(ARRAY_LENGTH(stOpModeReg), stOpModeReg, &pstServerAttr[i].TxPDO, 0);
    }
    return(EC_ERR_NONE);    
}

/*
 * Desc
 *      setup specifical registers for wr/rd functions.
 *      取得特殊位址的順序索引為了讀取與儲取特殊位址函數  
 * Param
 *      nServerCnt: Count of Server. 
 *      pstSlaveOD: pointer to Slave OD.
 *      pstServerAttr: pointer to attr of Server. 
 * Return
 *      EC_ERR_NONE : No error
 *      EC_ERR_MALLOC: alloc memory fail.
 * */
static int ec_slave_set_mode_regs(uint32_t u32CanOpenOpMode, int nServerCnt, EC_SLAVE_OD *pstSlaveOD,  EC_SERVER_ATTR_T *pstServerAttr)
{
    int nret;
   
    if (u32CanOpenOpMode == EC_OP_CSP){
        nret = ec_slave_set_csp_mode_regs(nServerCnt, pstSlaveOD, pstServerAttr);
    }
    return(nret);   
}


#ifdef DEBUG_DRIVER_INFO    
static void testing(void);
#endif

/*
 * Desc
 *      set ODs Entry and Counts.
 * Param
 *      nSlaveCnt: Count of Slave.
 *      pstSlaveOD: pointer to Slave OD.
 * Return
 *      ECM_DEVICE_NONE : No error
 *      EC_ERR_XXX: error.
 * */    
int ec_slave_probe (int nSlaveCnt, uint32_t u32CanOpenOpMode, EC_MASTER_T *pstECMMaster)
{
    DEVICE_TYPE_COUNT_T stDeviceCount;
    int     ret;

    pstECMMaster->pstSlaveVidPidTable = (EC_SLAVE_VID_PID_T *)vZeroMalloc(sizeof(EC_SLAVE_VID_PID_T)*nSlaveCnt);
    if (pstECMMaster->pstSlaveVidPidTable == NULL){
        return (EC_ERR_SLAVE_UNKNOWN);      
    }
    memset(&stDeviceCount,0, sizeof(DEVICE_TYPE_COUNT_T));
    pstECMMaster->u8SlaveCnt = nSlaveCnt;

    ret = ec_scan_slave_device_type(nSlaveCnt, &stDeviceCount, pstECMMaster->pstSlaveVidPidTable);
    if (ret != EC_ERR_NONE){
        return (EC_ERR_SLAVE_UNKNOWN);
    }
    MSG_DBG("Slave Coupler:%d, DI:%d, DO:%d, AI:%d, AO:%d, AC Server:%d\n", 
            stDeviceCount.u8Coupler,
            stDeviceCount.u8DIn, stDeviceCount.u8DOut,
            stDeviceCount.u8AIn, stDeviceCount.u8AOut,
            stDeviceCount.u8ServerCnt);  
    
    // config Server Info.
    // 設定馬達相關資參數
    pstECMMaster->u8ServerCnt = stDeviceCount.u8ServerCnt;
    pstECMMaster->u8ServerStartIdx = stDeviceCount.u8FirstServerIndex;
    if (pstECMMaster->u8ServerCnt){
        pstECMMaster->u8ServerEndIdx = pstECMMaster->u8ServerStartIdx + (pstECMMaster->u8ServerCnt -1);
        
        pstECMMaster->pstServerAttr = (EC_SERVER_ATTR_T *)vZeroMalloc(sizeof(EC_SERVER_ATTR_T)*pstECMMaster->u8ServerCnt);
        if (pstECMMaster->pstServerAttr == NULL){
            MSG_DBG("Error: malloc memory fail that create EC_SERVER_ATTR_T\n");       
            return (EC_ERR_MALLOC);         
        }
    }  
    
    ret = ec_slave_create_od(&pstECMMaster->stSlaveOD,&stDeviceCount);
    if (ret != EC_ERR_NONE){
        MSG_DBG("Error: malloc memory fail that slave OD create.\n");       
        return (ret);
    }
    
    ret = ec_slave_set_od(nSlaveCnt, pstECMMaster->pstSlaveVidPidTable, &pstECMMaster->stSlaveOD, pstECMMaster->pstServerAttr);
    if (ret != EC_ERR_NONE){
        MSG_DBG("Error: malloc memory fail that slave OD setting.\n");       
        return (ret);
    }   

    ret = ec_slave_set_mode_regs(u32CanOpenOpMode, pstECMMaster->u8ServerCnt, &pstECMMaster->stSlaveOD, pstECMMaster->pstServerAttr);
    if (ret != EC_ERR_NONE){
        MSG_DBG("Error: malloc memory fail that slave setting registers.\n");       
        return (ret);
    }       

    if (RxPDODATASIZE() > TEST_SPI_DATA_SIZE){
        MSG_DBG("Error: TEST_SPI_DATA_SIZE:%d < RXPDOSize:%d.\n", TEST_SPI_DATA_SIZE, RxPDODATASIZE());       
        return (EC_ERR_SPI_SIZE_OVERFLOW);      
    }
    
    if (TxPDODATASIZE() > TEST_SPI_DATA_SIZE){
        MSG_DBG("Error: TEST_SPI_DATA_SIZE:%d < TXPDOSize:%d.\n", TEST_SPI_DATA_SIZE, TxPDODATASIZE());       
        return (EC_ERR_SPI_SIZE_OVERFLOW);      
    } 
#ifdef DEBUG_DRIVER_INFO    
    testing();
#endif  
    return (EC_ERR_NONE);
}


#ifdef DEBUG_DRIVER_INFO

typedef struct ECM_PACK _axis_rxpdo_st
{
    uint16_t    u16CtlWord;     // 0/9 /18/27/36/45/54/63
    uint8_t     u8Mode;         // 2/11/20/29/38/47/56/65
    int32_t     n32Target;      // 3/12/21/30/39/48/57/66                    
    int16_t     n16TouchProbe;  // 7/16/25/34/43/52/61/70
} _AXIS_RXPDO_T;

typedef struct ECM_PACK _axis_txpdo_st
{
    uint16_t    u16ErrorCode;               // 0/23/46/69/92 /115/138/161
    uint16_t    u16StaWord;                 // 2/25/48/71/94 /117/140/163         
    uint8_t     u8Mode;                     // 4/27/50/73/96 /119/142/165
    int32_t     n32Actual;                  // 5/28/51/74/97 /120/143/166         
    int16_t     u16TouchProbeStatus;        // 9/32/55/78/101/124/147/170
    int32_t     n32TouchProbePos1PosiVal;   //11/34/57/80/103/126/149/172
    int32_t     n32FollowingError;          //15/38/61/84/107/130/153/176
    uint32_t    u32DigitalInput;            //19/42/65/88/111/134/157/180    
}_AXIS_TXPDO_T;




struct app_info_st{
    uint32_t u32CtlWord[MOTOR_MAX_COUNT];
    uint32_t u32TestPos[MOTOR_MAX_COUNT];
	uint16_t u16TouchProbeMode[MOTOR_MAX_COUNT];

    
    uint16_t u16StatusWord[MOTOR_MAX_COUNT];
    uint16_t u16TouchProbeState[MOTOR_MAX_COUNT];
		uint16_t u16ActualTorque[MOTOR_MAX_COUNT];	
		uint16_t u16ErrorCode[MOTOR_MAX_COUNT];		
    uint32_t u32TouchProbe1PositiveEdge[MOTOR_MAX_COUNT];
    uint32_t u32TouchProbe2PositiveEdge[MOTOR_MAX_COUNT];		
    uint32_t u32FollowError[MOTOR_MAX_COUNT];		
	
};


static app_info_st gAppPDO;

static void log_offset(unsigned int DrvIdx, unsigned int isRx, unsigned int regIdx, unsigned int offset)
{
	if (isRx)
	    gstLogWrRdPDO[DrvIdx].rx[regIdx] = offset;
	else
	    gstLogWrRdPDO[DrvIdx].tx[regIdx] = offset;		
}


static void testing(void)
{
    _AXIS_RXPDO_T *pRXPDO = (_AXIS_RXPDO_T *)RxPDOData;
    _AXIS_TXPDO_T *pTXPDO = (_AXIS_TXPDO_T *)TxPDOData; 
    int i, DrvIdx, nServerCnt; 
    for(i=0; i < RxPDODATASIZE(); i++){
        RxPDOData[i] = i;
    }   
    for(i=0; i < TxPDODATASIZE(); i++){
        TxPDOData[i] = i;
    }
    
    //nServerCnt = EtherCatMasterGetDriverCnt();
    nServerCnt = 14; 
    for(DrvIdx=0; DrvIdx < nServerCnt; DrvIdx++){
        printf("\nset ctrl word\n");
        EtherCatSetCtrlWord(DrvIdx, 0xF);
		log_offset(DrvIdx, 1, 0, gRxTxBufferOffset);
            
           
        printf("\nSet Target Pos\n");   
        EtherCatSetTargetPos(DrvIdx,gAppPDO.u32TestPos[DrvIdx]);
		log_offset(DrvIdx, 1, 1, gRxTxBufferOffset);		

        printf("\nSet Touch Probe Mode\n");   
        EtherCatSetTouchProbeMode(DrvIdx,gAppPDO.u16TouchProbeMode[DrvIdx]);	
		log_offset(DrvIdx, 1, 2, gRxTxBufferOffset);		

			  printf("\nGet Status Word\n");  
        EtherCatGetStatusWord(DrvIdx, &gAppPDO.u16StatusWord[DrvIdx]);
 		log_offset(DrvIdx, 0, 0, gRxTxBufferOffset);     

        printf("\nGet Actual Pos\n");           
        EtherCatGetActualPos(DrvIdx, (uint32_t*)&gAppPDO.u32TestPos[DrvIdx]);
		log_offset(DrvIdx, 0, 1, gRxTxBufferOffset);
		
        printf("\nGet Actual Torque\n");  
        EtherCatGetActualTorque(DrvIdx, &gAppPDO.u16ActualTorque[DrvIdx]);		
		log_offset(DrvIdx, 0, 2, gRxTxBufferOffset);	

        printf("\nGet Error Code\n");  
        EtherCatGetErrorCode(DrvIdx, &gAppPDO.u16ErrorCode[DrvIdx]);		
		log_offset(DrvIdx, 0, 3, gRxTxBufferOffset);

        printf("\nGet Touch Probe State\n");  
        EtherCatGetTouchProbeState(DrvIdx, &gAppPDO.u16TouchProbeState[DrvIdx]);
		log_offset(DrvIdx, 0, 4, gRxTxBufferOffset);
		
        printf("\nGet Touch Probe 2  Edge Position\n");  
        EtherCatGetTouchProbe2Pos(DrvIdx, &gAppPDO.u32TouchProbe2PositiveEdge[DrvIdx]);
		log_offset(DrvIdx, 0, 5, gRxTxBufferOffset);		
		
        printf("\nGet Follow Error\n");  
        EtherCatGetFollowingErrorActualValue(DrvIdx, &gAppPDO.u32FollowError[DrvIdx]);
		log_offset(DrvIdx, 0, 6, gRxTxBufferOffset);		
		
        printf("\nGet Touch Probe 1  Edge Position\n"); 
        EtherCatGetTouchProbe1Pos(DrvIdx, &gAppPDO.u32TouchProbe1PositiveEdge[DrvIdx]);
		log_offset(DrvIdx, 0, 7, gRxTxBufferOffset);		
		
        //printf("\nGet Touch Probe 1 Positive Edge\n");  
        //EtherCatGetTouchProbe2Pos(DrvIdx, &gAppPDO.u32TouchProbe1PositiveEdge[DrvIdx]);		
    
        pRXPDO++;
        pTXPDO++;
    }

}
#endif


