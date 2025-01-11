/******************************************************************************
 *  File    :   trace_config.h
 *  Version :   1.00
 *  Date    :   2022/05/02
 *  Author  :   jfc
 *
 * @copyright (C) 2
 *
 ******************************************************************************/
#ifndef _TRACE_CONFIG_H_
#define _TRACE_CONFIG_H_


#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus


#if (TRACE_MODE == 2)				// for SystemView

#include "SEGGER_SYSVIEW_Conf.h"
#include "SEGGER_SYSVIEW.h"
#include "SEGGER_RTT.h"

#define TRACE_INIT()                { SEGGER_SYSVIEW_Conf();SEGGER_SYSVIEW_OnIdle(); }

#define TRACE_ISR_ENTRY()           SEGGER_SYSVIEW_RecordEnterISR()
#define TRACE_ISR_EXIT()            SEGGER_SYSVIEW_RecordExitISR()

#define TRACE_EXEC_FUNC(id)         SEGGER_SYSVIEW_RecordVoid((U32)id);         \
                                    p();                                            \
                                    SEGGER_SYSVIEW_RecordEndCall((U32)id);

#define TRACE_EXEC_TASK(t, par1)    SEGGER_SYSVIEW_OnTaskStartExec((U32)t);         \
                                    t(par1);                                            \
                                    SEGGER_SYSVIEW_OnTaskStopReady((U32)t, 0);

#define TRACE_TASK_START(id)        SEGGER_SYSVIEW_OnTaskStartExec((U32)id); 
#define TRACE_TASK_END(id)          SEGGER_SYSVIEW_OnTaskStopReady((U32)id,0); 
#define TRACE_MSG(fmt, args...)     SEGGER_SYSVIEW_PrintfHost(fmt, ##args);              

#define MSG_ERR(fmt, args...)       SEGGER_SYSVIEW_PrintfHost(fmt, ##args)
#define MSG_DBG(fmt, args...)       SEGGER_SYSVIEW_PrintfHost(fmt, ##args)
#define MSG_RTT(fmt, args...)       SEGGER_RTT_printf(0, fmt, ##args)

#define CHECK_KEY()                 (SEGGER_RTT_HasKey()==1)
#define WAIT_KEY()                  SEGGER_RTT_WaitKey()     

#define RTT(fmt,args...)    MSG_RTT(fmt,##args) ;TRACE_MSG(fmt,##args); 
#define vMalloc(x)					malloc(x)
               
#elif	(TRACE_MODE == 1)			// for printf/getchar()
#include "SEGGER_RTT.h"
    
#define TRACE_INIT()
#define TRACE_ISR_ENTRY() 
#define TRACE_ISR_EXIT()
#define TRACE_EXEC_TASK(t, p1)

#define TRACE_TASK_START(id)    
#define TRACE_TASK_END(id)      
#define TRACE_MSG(fmt, args...) 

#define MSG_ERR(fmt, args...)       SEGGER_RTT_printf(0, fmt, ##args)
#define MSG_DBG(fmt, args...)       SEGGER_RTT_printf(0, fmt, ##args)
#define MSG_RTT(fmt, args...)       SEGGER_RTT_printf(0, fmt, ##args)

#define CHECK_KEY()                 (SEGGER_RTT_HasKey()==1)
#define WAIT_KEY()                  SEGGER_RTT_WaitKey()    
#define RTT(fmt,args...)    MSG_RTT(fmt,##args) ;TRACE_MSG(fmt,##args); 

#define vMalloc(x)					mallocc(x)
#else								// none message
	
#define TRACE_INIT()
#define TRACE_ISR_ENTRY() 
#define TRACE_ISR_EXIT()
#define TRACE_EXEC_TASK(t, p1)

#define TRACE_TASK_START(id)    
#define TRACE_TASK_END(id)      
#define TRACE_MSG(fmt, args...) 

#define MSG_ERR(fmt, args...)  		printf(fmt, ##args)
#define MSG_DBG(fmt, args...)  		printf(fmt, ##args)
#define MSG_RTT(fmt, args...)   

#define CHECK_KEY()             	(0)
#define WAIT_KEY()              	getchar()
	
#define vMalloc(x)					malloc(x)      
#define RTT(fmt,args...)    
#endif /* SEGGER_TRACE_ENABLED */ 


#ifdef __cplusplus
}
#endif

#endif  // #ifndef _TRACE_CONFIG_H_
