/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief
 *           Transmit and receive data from PC terminal through RS232 interface.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"
#include "uart_transfer.h"

#define COM_NUM          4

#define UART_RING_BUFSIZE               SO_BUF_LEN
/* Buf mask */
#define __BUF_MASK                      (UART_RING_BUFSIZE-1)
/* Check buf is full or not */
#define __BUF_IS_FULL(head, tail)       ((tail&__BUF_MASK)==((head+1)&__BUF_MASK))
/* Check buf will be full in next receiving or not */
#define __BUF_WILL_FULL(head, tail)     ((tail&__BUF_MASK)==((head+2)&__BUF_MASK))
/* Check buf is empty */
#define __BUF_IS_EMPTY(head, tail)      ((head&__BUF_MASK)==(tail&__BUF_MASK))
/* Reset buf */
#define __BUF_RESET(bufidx)             (bufidx=0)
#define __BUF_INCR(bufidx)              (bufidx=(bufidx+1)&__BUF_MASK)
#define __BUF_INCR_TEST(bufidx)         ((bufidx+1)&__BUF_MASK)

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
MODULE_UART_INFO_Typedef  uart_info[COM_NUM] =
{
      { UART0, UART0_IRQn, 0 },
      { UART1, UART1_IRQn, 1 },
      { UART2, UART2_IRQn, 2 },
      { UART3, UART3_IRQn, 3 }
};

/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
static void uartx_isr_comm (uint8_t dev_no);




/*---------------------------------------------------------------------------------------------------------*/
/* UART Callback function                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
static void uartx_isr_comm (uint8_t dev_no)
{
    MODULE_UART_INFO_Typedef * p_uart_port = &uart_info[dev_no];    
    UART_T *uart_base = (UART_T *)p_uart_port->user_data;   
    uint32_t u32IntSts = uart_base->INTSTS;
    uint8_t u8InChar = 0xFF;    
    uint16_t test_idx;
    

    if((u32IntSts & UART_INTSTS_RDAINT_Msk) || (u32IntSts & UART_INTSTS_RXTOINT_Msk))
    {
        /* Get all the input characters */
        while(UART_GET_RX_EMPTY(uart_base) == 0)
        {
            /* Get the character from UART Buffer */
            u8InChar = UART_READ(uart_base);

            /* Check if buffer full */
            test_idx = __BUF_INCR_TEST(p_uart_port->si_buf_put_idx);
            if (test_idx == p_uart_port->si_buf_get_idx) { //Overrun : 20130613
                u8InChar = 0;
            }
            else {
                p_uart_port->si_buf[p_uart_port->si_buf_put_idx] = u8InChar;
                p_uart_port->si_buf_put_idx = test_idx;
            }
        }
    }

    if (u32IntSts & UART_INTSTS_THREINT_Msk)
    {
        //TDR Empty
        if (p_uart_port->so_buf_put_idx != p_uart_port->so_buf_get_idx) {
            UART_WRITE(uart_base, p_uart_port->so_buf[p_uart_port->so_buf_get_idx]);
            __BUF_INCR(p_uart_port->so_buf_get_idx);
        }
        else{
            //Disable TXE IRQ
                  UART_DisableInt(uart_base, UART_INTEN_THREIEN_Msk);
        }
        //USART_ClearFlag(uart_base, USART_FLAG_TXE);       
    }

    if(UART0->FIFOSTS & (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk | UART_FIFOSTS_RXOVIF_Msk))
    {
        UART0->FIFOSTS = (UART_FIFOSTS_BIF_Msk | UART_FIFOSTS_FEF_Msk | UART_FIFOSTS_PEF_Msk | UART_FIFOSTS_RXOVIF_Msk);
    }
}


/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART0_IRQHandler(void)
{
    uartx_isr_comm(0);
}

void UART1_IRQHandler(void)
{
    uartx_isr_comm(1);
}


void UART2_IRQHandler(void)
{
    uartx_isr_comm(2);
}


void UART3_IRQHandler(void)
{
    uartx_isr_comm(3);
}


int uart_put_char (MODULE_UART_INFO_Typedef *p_uart_port, char ch)
{
        UART_T *uart_base = (UART_T *)p_uart_port->user_data;

        if (!p_uart_port){
            return (EPBB_UART_ERR_PORT);
        }


        if (__BUF_IS_FULL(p_uart_port->so_buf_put_idx, p_uart_port->so_buf_get_idx)){
            return (EPBB_UART_ERR_TX_BUF_FULL);
        }

        p_uart_port->so_buf[p_uart_port->so_buf_put_idx] = ch;
        __BUF_INCR(p_uart_port->so_buf_put_idx);

        // Trigger TXE interrupt
        //if (UART_GET_TX_EMPTY(uart_base, USART_IT_TXE) == RESET){
        if (!(uart_base->INTEN & UART_INTEN_THREIEN_Msk)){
            UART_EnableInt(uart_base, UART_INTEN_THREIEN_Msk);
        }

        return (EPBB_UART_OK);
}



int 
uart_put_datas (MODULE_UART_INFO_Typedef *p_uart_port, char *pu8TxBuf, int nWriteBytes)
{
        int    nCount;

        for (nCount = 0ul; nCount != nWriteBytes; nCount++){
            
            if (uart_put_char(p_uart_port, pu8TxBuf[nCount]) == EPBB_UART_ERR_TX_BUF_FULL){
                break;
            }
                
        }
        return (nCount);
}


/***************************************************************************
* Purpose   ....: Get character from UART.
* Input     ....:
*    @param ....: uart_port : uart structure
* Output    ....:
*    @param ....: p_ch : receiver character
* @Return   ....: return EPBB_UART_OK when send successful
*               : return EPBB_UAER_ERR_XX.
* Note      ....: None
***************************************************************************/
int
uart_get_char (MODULE_UART_INFO_Typedef *p_uart_port, char *p_ch)
{
        if (!p_uart_port){
            return (EPBB_UART_ERR_PORT);
        }

        if (!__BUF_IS_EMPTY(p_uart_port->si_buf_get_idx, p_uart_port->si_buf_put_idx)){
            *p_ch = p_uart_port->si_buf[p_uart_port->si_buf_get_idx];
            __BUF_INCR(p_uart_port->si_buf_get_idx);
            return (EPBB_UART_OK);
        }
        return (EPBB_UART_ERR_RX_BUF_EMPTY);
}



/***************************************************************************
* Purpose   ....: Query any character at UART.
* Input     ....:
*    @param ....: uart_port : pointer to the uart structure.
* Output    ....:
*    @param ....: None
* @Return   ....: return EPBB_UART_OK when send successful
*               : return EPBB_UAER_ERR_XX.
* Note      ....: None
***************************************************************************/
int
uart_query_char (MODULE_UART_INFO_Typedef *p_uart_port)
{
        if (!p_uart_port){
            return (EPBB_UART_ERR_PORT);
        }

        if (!__BUF_IS_EMPTY(p_uart_port->si_buf_get_idx, p_uart_port->si_buf_put_idx)){
            return (EPBB_UART_OK);
        }
        return (EPBB_UART_ERR_RX_BUF_EMPTY);
}



MODULE_UART_INFO_Typedef * uart_init(uint8_t dev_no, uint32_t baud_rate)
{
        MODULE_UART_INFO_Typedef *p_uart_port;
        UART_T *uart_base; 
    
        if (dev_no >= COM_NUM){
            return (NULL);
        }
		
        p_uart_port = &uart_info[dev_no];  
        uart_base = (UART_T *)p_uart_port->user_data;       
        
        /* Configure UARTx and set UARTx baud rate */
        UART_Open(uart_base, baud_rate);
        
        
        UART_SetTimeoutCnt(uart_base, 0x10); // Set Rx Time-out counter

        // Set RX FIFO Interrupt Trigger Level
        uart_base->FIFO &= ~ UART_FIFO_RFITL_Msk;
        uart_base->FIFO |= UART_FIFO_RFITL_4BYTES;

        /* Enable UART RDA/Time-out interrupt */
        NVIC_EnableIRQ((IRQn_Type)p_uart_port->irq_no);
        UART_EnableInt(uart_base, (UART_INTEN_RDAIEN_Msk  | UART_INTEN_RXTOIEN_Msk));
        
        return (p_uart_port);
}
