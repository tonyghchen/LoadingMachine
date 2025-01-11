

//***************** : Define to prevent recursive inclusion
#ifndef __MODULE_UART_TRANSFER_H__
#define __MODULE_UART_TRANSFER_H__



/***************************************************************************
Include Files
***************************************************************************/
#include    <stdarg.h>
#include    <string.h>
#include    <stdio.h>



//**************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this
// header have a C binding.
//
//**************************************************************************
#ifdef __cplusplus
 extern "C" {
#endif


/***************************************************************************
Constant Define
***************************************************************************/
// direct call functions of board.

typedef int  (DRVUART_RX_ISR_HOOK)(unsigned char ch);

#define SIO_RING_BUF_LEN   0x200

#define SO_BUF_LEN         (SIO_RING_BUF_LEN)
#define SI_BUF_LEN         (SIO_RING_BUF_LEN)


enum {
    EPBB_UART_OK=0,
    EPBB_UART_ERR_PORT,
    EPBB_UART_ERR_CONFIG,
    EPBB_UART_ERR_TX_BUF_FULL,
    EPBB_UART_ERR_RX_BUF_EMPTY
};

typedef struct uart_info_st
{
        void                 *user_data;	
        uint16_t              irq_no;
        uint8_t               com_idx;		

        uint16_t              so_buf_put_idx, so_buf_get_idx;
        uint16_t              si_buf_put_idx, si_buf_get_idx;
        uint8_t               si_buf[SI_BUF_LEN];
        uint8_t               so_buf[SO_BUF_LEN];
} MODULE_UART_INFO_Typedef;




/***************************************************************************
Function Prototypes
***************************************************************************/
MODULE_UART_INFO_Typedef * uart_init(uint8_t dev_no, uint32_t baud_rate);
int uart_query_char (MODULE_UART_INFO_Typedef *p_uart_port);
int uart_get_char (MODULE_UART_INFO_Typedef *p_uart_port, char *p_ch);
int uart_put_char (MODULE_UART_INFO_Typedef *p_uart_port, char ch);
int uart_put_datas  (MODULE_UART_INFO_Typedef *p_uart_port, char *pu8TxBuf, int nWriteBytes);

//**************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//**************************************************************************
#ifdef __cplusplus
}
#endif

#endif /* __MODULE_UART_TRANSFER_H__ */

