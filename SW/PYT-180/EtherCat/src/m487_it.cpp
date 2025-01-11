// -------------------------------------------------------------------------
//  File        : m487_it.cpp
//              :
//  Library     :
//              :
//  Developer   : 
//              :
//  Purpose     : chip 487 interrupt handler.
//              :
//  Limitation  :
//              :
//  Note        :
//              :
// -------------------------------------------------------------------------

#include <stdint.h>
#include "pdodefine.h"
#include "trace_config.h"
#include "ec_master.h"

extern "C"{
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

#if 0

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
#endif

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
	TRACE_ISR_ENTRY();	
	PendSV_Handler_Hook();
	TRACE_ISR_EXIT();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	TRACE_ISR_ENTRY();
	SysTick_Handler_Hook();
	TRACE_ISR_EXIT();
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
void GPA_IRQHandler(void)
{
	TRACE_ISR_ENTRY();
	GPA_IRQHandler_Hook();
	TRACE_ISR_EXIT();	
}
#endif


/**
 * @brief       GPIO PE IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The PE default IRQ, declared in startup_M480.s.
 */
#if (APP_USED_PYT_180_DB == 0) 
void GPE_IRQHandler(void)
{
	TRACE_ISR_ENTRY();
	GPE_IRQHandler_Hook();
	TRACE_ISR_EXIT();	
}
#endif

} // extern "C"
