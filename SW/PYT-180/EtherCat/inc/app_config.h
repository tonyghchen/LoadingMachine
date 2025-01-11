/******************************************************************************
 *  File    :   app_config.h
 *  Version :   1.00
 *  Date    :   2022/06/7
 *  Author  :   chan-fa
 *
 * @copyright (C) 
 *
 ******************************************************************************/
#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#define APP_SPI_CLOCK               36000000

#define APP_EC_DC_ACTIVE_CODE       0x300
#define APP_EC_DC_TIME              1000000     // 1000000us=1ms

#define APP_ENABLE_ECHERCAT_INT1    1
#define APP_USED_PYT_180_DB         1

#define APP_DRV_CNT					0



#define ARRAY_LENGTH(x)     ( sizeof(x) / sizeof(x[0]))

#include "compiler.h"
#include "trace_config.h"


#endif
