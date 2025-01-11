#ifndef _MODBUS_H_
#define _MODBUS_H_

#include <stdint.h>

#define FUNC_CODE_READ_HOLDING_REG  0x03
#define FUNC_CODE_WRITE_SINGLE_REG  0x06

unsigned short modbus_getCRC16(unsigned char *puchMsg, unsigned short usDataLen);
uint16_t modbus_FormatCmd(unsigned char *pbyOutBuffer, uint8_t u8DeviceAddr, uint8_t u8FuncCode, uint16_t u16StartRegAddr, uint16_t u16DataCount);

#endif // _MODBUS_H_
