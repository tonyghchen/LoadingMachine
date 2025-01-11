/******************************************************************************
 *	File	:	compiler.h
 *	Version :	1.00
 *	Date	:	2021/09/18
 *	Author	:	XFORCE
 *
 * @copyright (C) 2
 *
 ******************************************************************************/
#ifndef _COMPILER_H_
#define _COMPILER_H_


#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

#include <stdint.h>

#define ECM_PACK_BEGIN
#define ECM_PACK  __attribute__((__packed__))
#define ECM_PACK_END


typedef union   CVT {
        uint32_t  l ;
        uint16_t  w[2] ;
        uint8_t   b[4] ;
} UN_CVT;

#define HI_WORD(x)	(x>>16)
#define LOW_WORD(x)	(x&0xffff)

#ifdef __cplusplus
}
#endif

#endif	// #ifndef _COMPILER_H_
