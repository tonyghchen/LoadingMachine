/******************************************************************************
 *  File    :   main.cpp
 *  Version :   1.00
 *  Date    :   2024/12/14
 *  Author  :   chan-fa
 *  Descriptor : 初始化設定LoadCell, 單位:g, Baud Rate=115200
 *
 *
 * @copyright (C) 2024.
 *
 ******************************************************************************/
#include <stdint.h>
#include "NuMicro.h"
#include "modbus_bsq_dg.h"
#include "uart_transfer.h"


#define PLL_CLOCK       192000000

MODULE_UART_INFO_Typedef * pgUart; 

unsigned char gbyMosbusCmdBuffer[64];

extern "C" {
int kbhit(void);
}

void SYS_Init(void)
{

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);
    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);
    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);
    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);
    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2);
    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    //CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART1SEL_HXT, CLK_CLKDIV0_UART1(1));    
    //CLK_SetModuleClock(UART2_MODULE, CLK_CLKSEL3_UART2SEL_HXT, CLK_CLKDIV4_UART2(1));  
    CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL3_UART3SEL_HXT, CLK_CLKDIV4_UART3(1));  
    /* Select PCLK0 as the clock source of QSPI0 */
    CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PCLK0, MODULE_NoMsk);
    /* Select PCLK0 as the clock source of QSPI0 */
    //CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PCLK0, MODULE_NoMsk);
    /* Select HXT(12MHz) as the clock source of TMR0 */ 
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);
    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART3_MODULE);   

    CLK_EnableModuleClock(TMR2_MODULE);
    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART3 RXD(PD0) and TXD(PD1) */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD0MFP_UART3_RXD | SYS_GPD_MFPL_PD1MFP_UART3_TXD);    

    // Update prescale to set proper resolution.
    TIMER_SET_PRESCALE_VALUE(TIMER2, 0);
    // Set compare value as large as possible, so don't need to worry about counter overrun too frequently.
    TIMER_SET_CMP_VALUE(TIMER2, 0xFFFFFF);
    // Configure Timer 0 free counting mode, capture TDR value on rising edge
    TIMER_EnableCapture(TIMER2, TIMER_CAPTURE_FREE_COUNTING_MODE, TIMER_CAPTURE_EVENT_RISING);
    // Start Timer 0
    TIMER_Start(TIMER2);
      
}


void delay(uint32_t ms)
{
    volatile uint32_t i, j;
    
    for(i=0; i < ms; i++){
        for(j=0; j < 10000; j++){
        }
    }
}



void send_packet(char *pPacket, uint16_t u16DataSizes)
{
    uart_put_datas(pgUart, pPacket, u16DataSizes);
    delay(1000);
}



static void Config(uint8_t u8DeviceAddr, uint8_t u8NewDeviceAddr)
{
    unsigned char  u8BaudRate, u8Unit;
    unsigned short u16CmdSize ;
    

    // change Unit to g.
    u8Unit = UNIT_G;
    u16CmdSize = modbus_bsq_dg_ChangeUnit(gbyMosbusCmdBuffer, u8DeviceAddr, u8Unit);
    send_packet((char*)gbyMosbusCmdBuffer,  u16CmdSize);
    
    // Change Device Addr
    if (u8DeviceAddr != u8NewDeviceAddr){
        u16CmdSize = modbus_bsq_dg_ChangeSlaveAddr(gbyMosbusCmdBuffer, u8DeviceAddr, u8NewDeviceAddr);
        send_packet((char*)gbyMosbusCmdBuffer,  u16CmdSize);
    }
    
    // change Baud rate = 115200
    u8BaudRate = BAUD_RATE_115200;
    u16CmdSize = modbus_bsq_dg_ChangeBaud(gbyMosbusCmdBuffer, u8NewDeviceAddr, u8BaudRate);
    send_packet((char*)gbyMosbusCmdBuffer,  u16CmdSize);    
}


void readValue(uint8_t u8DeviceAddr)
{
        uint16_t u16CmdSize = modbus_bsq_dg_ReadMeasureValue(gbyMosbusCmdBuffer, u8DeviceAddr);
        send_packet((char*)gbyMosbusCmdBuffer, u16CmdSize);
}


int main (int argc,char ** argv)
{
    uint32_t    u32BaudRate;
    uint16_t    u16CmdSize ; 
    uint8_t     u8DeviceAddr, u8NewDeviceAddr;
   
    bool config = false ;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();
    
    // initial uart3

    u32BaudRate = 115200;
    pgUart = uart_init(3, u32BaudRate);
    
    u8DeviceAddr = 1;   
    u8NewDeviceAddr = 1;
    if (config){
        Config(u8DeviceAddr, u8NewDeviceAddr);
    }
    else{
        // read Measure value.
        readValue(u8DeviceAddr);
    }
    // user code.
    while(1){

    }
}
