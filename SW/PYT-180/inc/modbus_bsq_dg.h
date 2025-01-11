#ifndef _MODBUS_BSQ_DG_H_
#define _MODBUS_BSQ_DG_H_

#include "modbus.h"


/* 小數點(0-3), 
    00-0        個位數 (default)
    01-0.0      十位數
    02-0.00     百位數
    03-0.000    千位數    
*/
#define SINGLE_DIGIT_POINT          0x00        // default
#define TEN_DIGIT_POINT             0x01
#define HUNDRED_DIGIT_POINT         0x02
#define THOUSAND_DIGIT_POINT        0x03

#define CODE_6_DECIMAL_POINT_REG    0x01  

/* 
  單位 : 1：MPa；2：Kg；3：T; 4:g；5：N；6；KN
  default : 2:Kg
*/
#define UNIT_MPA                0x01
#define UNIT_KG                 0x02        // default
#define UNIT_T                  0x03
#define UNIT_G                  0x04
#define UNIT_N                  0x05
#define UNIT_KN                 0x06
 
#define CODE_6_UNIT_REG         0x02 

/* 偏移值 : 低於該值輸出為0，預設值為0；範圍0-50
*/
#define MASK_REG                0x03 


/* 取樣率 : 
   1:600pcs; 2:300pcs; 3:150pcs; 4:75pcs; 5:37.5pcs(預設值); 6:18.75pcs; 7:10pcs
*/
#define SAMPLE_RATE_600         0x01
#define SAMPLE_RATE_300         0x02
#define SAMPLE_RATE_150         0x03
#define SAMPLE_RATE_75          0x04
#define SAMPLE_RATE_37_5        0x05
#define SAMPLE_RATE_18_5        0x06
#define SAMPLE_RATE_10          0x07

#define CODE_6_MASK_REG         0x03 
  
/* Device Address : 1-255, default : 1
*/ 
#define CODE_6_DEVICE_ADDR_REG  0x06

/* Baud Rate : 
   0-6:0:1200；1：2400；2：4800；3：9600；4：19200;5：38400；6:115200
   default 3:9600
*/
#define BAUD_RATE_1200          0x00
#define BAUD_RATE_2400          0x01
#define BAUD_RATE_4800          0x02
#define BAUD_RATE_9600          0x03
#define BAUD_RATE_19200         0x04
#define BAUD_RATE_38400         0x05
#define BAUD_RATE_115200        0x06

#define CODE_6_BAUD_RATE_REG    0x07

/* BAUD Ratee 同位元校正設定 : 0-3:0:N-8-1(預設值); 1:N-8-2; 2:ODD-8-1; 3:EVEN-8-1;
*/
#define PARITY_N_8_1            0x00
#define PARITY_N_8_2            0x01
#define PARITY_ODD_8_1          0x02
#define PARITY_EVEN_8_1         0x03

#define CODE_6_PARITY_REG       0x08


/* 讀取量測值;
*/
#define CODE_3_READ_VALUE_REG   0x00

uint16_t modbus_bsq_dg_ChangeDecimalPoint(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8SelPoint);
uint16_t modbus_bsq_dg_ChangeUnit(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8Unit);
uint16_t modbus_bsq_dg_ChangeSlaveAddr(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8NewDeviceAddr);
uint16_t modbus_bsq_dg_ChangeBaud(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr, uint8_t u8BaudRate);

uint16_t modbus_bsq_dg_ReadMeasureValue(unsigned char *pbyCmdBuffer, uint8_t u8DeviceAddr);




#endif // _modbus_bsq_dg_H_

