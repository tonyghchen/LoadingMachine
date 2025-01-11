/**************************************************************************//**
 * @file     modbus_bsq_dg.cpp
 * @version  V1.00
 * @brief    BSQ-DG-V2型單路稱重感測器
 *
 *
 * @copyright (C) 2024 
 *****************************************************************************/
 
#include "modbus_bsq_dg.h"


uint16_t modbus_bsq_dg_ChangeDecimalPoint(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8SelPoint)
{
    uint16_t u16CmdSize ;
    u16CmdSize =  modbus_FormatCmd(pbyCmdBuffer,  
                                   u8DeviceAddr, 
                                   FUNC_CODE_WRITE_SINGLE_REG, 
                                   CODE_6_DECIMAL_POINT_REG, 
                                   u8SelPoint);
    return (u16CmdSize);
} 



uint16_t modbus_bsq_dg_ChangeUnit(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8Unit)
{
    uint16_t u16CmdSize ;
    u16CmdSize =  modbus_FormatCmd(pbyCmdBuffer,  
                                   u8DeviceAddr, 
                                   FUNC_CODE_WRITE_SINGLE_REG, 
                                   CODE_6_UNIT_REG, 
                                   u8Unit);
    return (u16CmdSize);
} 



uint16_t modbus_bsq_dg_ChangeSlaveAddr(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8NewDeviceAddr)
{
    uint16_t u16CmdSize ;
    u16CmdSize =  modbus_FormatCmd(pbyCmdBuffer,  
                                   u8DeviceAddr, 
                                   FUNC_CODE_WRITE_SINGLE_REG, 
                                   CODE_6_DEVICE_ADDR_REG, 
                                   u8NewDeviceAddr);
    return (u16CmdSize);
} 


 
uint16_t modbus_bsq_dg_ChangeBaud(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8BaudRate)
{
    uint16_t u16CmdSize ;
    u16CmdSize =  modbus_FormatCmd(pbyCmdBuffer,  
                                   u8DeviceAddr, 
                                   FUNC_CODE_WRITE_SINGLE_REG, 
                                   CODE_6_BAUD_RATE_REG, 
                                   u8BaudRate);
    return (u16CmdSize);
}



uint16_t modbus_bsq_dg_ReadMeasureValue(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr)
{
    uint16_t u16CmdSize ;
    u16CmdSize =  modbus_FormatCmd(pbyCmdBuffer,  
                                   u8DeviceAddr, 
                                   FUNC_CODE_READ_HOLDING_REG, 
                                   CODE_3_READ_VALUE_REG, 
                                   1);
    return (u16CmdSize);                                   
}
