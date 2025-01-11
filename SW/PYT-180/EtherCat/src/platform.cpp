/******************************************************************************
 *  File    :   platform.cpp
 *  Version :   0.2
 *  Date    :   2020/09/03
 *  Author  :   User
 *
 *  Hardware dependency function - C source file
 *
 *  Provide necessary function for EcmUsrDriver
 *
 * @copyright (C) 2020 NEXTW TECHNOLOGY CO., LTD.. All rights reserved.
 *
 ******************************************************************************/

#include "NuMicro.h"
#include "platform.h"

#include "EcmDriver.h"
#include "ec_cmd_isr.h"

#define PLL_CLOCK           192000000
extern uint32_t    gSPIPackageCount;

extern "C"
{
static volatile uint32_t g_u32rxtxDone=0;
uint32_t g_u32CrcType = ECM_CRC_TYPE_32;
uint8_t  g_u8PDMA_IRQ_Callback=0;

void PDMA_IRQHandler(void)
{
#if 0
    uint32_t status = PDMA_GET_INT_STATUS(PDMA);
    
    TRACE_ISR_ENTRY();
    /* Check the PDMA transfer done interrupt flag */
    if(status & PDMA_INTSTS_TDIF_Msk){
        if((PDMA_GET_TD_STS(PDMA) & ((1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH) )) == ((1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH))){
            g_u32rxtxDone = 3;
            /* Clear the PDMA transfer done flags */
            PDMA_CLR_TD_FLAG(PDMA,(1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH));
            if (g_u8PDMA_IRQ_Callback && g_u32rxtxDone == 3){
                QSPI_DISABLE_TX_RX_PDMA(QSPI0);             
                g_u8PDMA_IRQ_Callback = 0;
                //UserDelay(150);
                //EC_CmdResponsePop();
                SysTick_enable();
            }
        }
    }   
    /* Check the DMA transfer abort interrupt flag */
    if (status & PDMA_INTSTS_ABTIF_Msk){
        if (PDMA_GET_ABORT_STS(PDMA) & PDMA_ABTSTS_ABTIF2_Msk){
            g_u32rxtxDone |= 4;
            PDMA_CLR_ABORT_FLAG(PDMA,PDMA_ABTSTS_ABTIF2_Msk);
		}
    }
    TRACE_ISR_EXIT();
#else   
    uint32_t status = PDMA_GET_INT_STATUS(PDMA);
    
    TRACE_ISR_ENTRY();
    if (status != 2){
//        TRACE_MSG("I:%x\n", status);
    }
    /* Check the PDMA transfer done interrupt flag */
    /* Check the DMA transfer abort interrupt flag */
    if(status & PDMA_INTSTS_ABTIF_Msk){
        if(PDMA_GET_ABORT_STS(PDMA) & PDMA_ABTSTS_ABTIF2_Msk){
            PDMA_CLR_ABORT_FLAG(PDMA,PDMA_ABTSTS_ABTIF2_Msk);
            g_u32rxtxDone |= 4;                 
            //TRACE_MSG("I:4\n");
        }
    }
    if (status & PDMA_INTSTS_TDIF_Msk){
        if (PDMA_GET_TD_STS(PDMA) & (0x1ul << SPI_MASTER_TX_DMA_CH)){
            PDMA_CLR_TD_FLAG(PDMA,(0x1ul << SPI_MASTER_TX_DMA_CH));  
            g_u32rxtxDone |= 2;         
            if (g_u8PDMA_IRQ_Callback){
                //TRACE_MSG("T=2\n");
            }
        }       
        if (PDMA_GET_TD_STS(PDMA) & (0x1ul << SPI_MASTER_RX_DMA_CH)){  
            PDMA_CLR_TD_FLAG(PDMA,(0x1ul << SPI_MASTER_RX_DMA_CH));
            g_u32rxtxDone |= 1;             
            if (g_u8PDMA_IRQ_Callback){ 
                //TRACE_MSG("R=1\n");
            }
        }

        if (g_u8PDMA_IRQ_Callback && g_u32rxtxDone == 3){
            QSPI_DISABLE_TX_RX_PDMA(QSPI0);
            g_u8PDMA_IRQ_Callback = 0;
            //UserDelay(150);
            //EC_CmdResponsePop();
            SysTick_enable();
        }
    }
    TRACE_ISR_EXIT();
#endif  
}


void UserSys_Init(uint32_t u32SpiFreq)
{
    SYS_UnlockReg();
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
    //CLK_EnableModuleClock(UART0_MODULE);    
    CLK_EnableModuleClock(UART1_MODULE);
    //CLK_EnableModuleClock(UART2_MODULE);    
    CLK_EnableModuleClock(UART3_MODULE);   
    CLK_EnableModuleClock(QSPI0_MODULE);
    CLK_EnableModuleClock(PDMA_MODULE);
    CLK_EnableModuleClock(CRC_MODULE);
    CLK_EnableModuleClock(TMR2_MODULE);
    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    //SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    //SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    /* Set GPB multi-function pins for UART1 RXD(PB2) and TXD(PB3) */
	SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk);
    SYS->GPB_MFPL |=  (SYS_GPB_MFPL_PB2MFP_UART1_RXD | SYS_GPB_MFPL_PB3MFP_UART1_TXD);	    
    /* Set GPB multi-function pins for UART2 RXD(PB0) and TXD(PB1) */
    //SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB0MFP_Msk);
    //SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_UART2_RXD | SYS_GPB_MFPL_PB1MFP_UART2_TXD); 
    /* Set GPB multi-function pins for UART3 RXD(PD0) and TXD(PD1) */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD0MFP_UART3_RXD | SYS_GPD_MFPL_PD1MFP_UART3_TXD);    

    /* Configure QSPI0 related multi-function pins. GPA[3:0] : QSPI0_MOSI0, QSPI0_MISO0, QSPI0_CLK, QSPI0_SS. */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_QSPI0_MOSI0 | SYS_GPA_MFPL_PA1MFP_QSPI0_MISO0 | SYS_GPA_MFPL_PA2MFP_QSPI0_CLK | SYS_GPA_MFPL_PA3MFP_QSPI0_SS;
    /* Enable QSPI0 clock pin (PA2) schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;
    /* Enable QSPI0 I/O high slew rate */
    GPIO_SetSlewCtl(PA, 0x3F, GPIO_SLEWCTL_HIGH);
    // Update prescale to set proper resolution.
    TIMER_SET_PRESCALE_VALUE(TIMER2, 0);
    // Set compare value as large as possible, so don't need to worry about counter overrun too frequently.
    TIMER_SET_CMP_VALUE(TIMER2, 0xFFFFFF);
    // Configure Timer 0 free counting mode, capture TDR value on rising edge
    TIMER_EnableCapture(TIMER2, TIMER_CAPTURE_FREE_COUNTING_MODE, TIMER_CAPTURE_EVENT_RISING);
    // Start Timer 0
    TIMER_Start(TIMER2);
    //UART_Open(UART0, 115200);
    //UART_Open(UART2, 9600);    
        
    // reset PDMA/QSPI
    SYS->IPRST0 |= SYS_IPRST0_PDMARST_Msk;
    SYS->IPRST1 |= SYS_IPRST1_QSPI0RST_Msk;     
    UserDelay(100);
    SYS->IPRST0 &= ~SYS_IPRST0_PDMARST_Msk;
    SYS->IPRST1 &= ~SYS_IPRST1_QSPI0RST_Msk;        
        
    // SPI setup
    QSPI_Open(QSPI0, SPI_MASTER, SPI_MODE_0, 8, u32SpiFreq);
    QSPI_EnableAutoSS(QSPI0, SPI_SS, SPI_SS_ACTIVE_LOW);
    
    PDMA_Open(PDMA,(1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH));
    PDMA_EnableInt(PDMA, SPI_MASTER_RX_DMA_CH, PDMA_INT_TRANS_DONE);
    PDMA_EnableInt(PDMA, SPI_MASTER_TX_DMA_CH, PDMA_INT_TRANS_DONE);
    NVIC_EnableIRQ(PDMA_IRQn);
    NVIC_SetPriority(PDMA_IRQn, 0); // 0: Highest priority, 0xF : Lowest priority.
        
    //SysTick_open();
}
void UserSys_Close(void)
{
    PDMA_Close(PDMA);
    QSPI_Close(QSPI0);
}

static int _doSPITransfer(uint8_t *pTxBuf, uint8_t *pRxBuf, uint32_t u32PackSize)
{
    /* SPI master PDMA TX channel configuration: */
    PDMA_SetTransferCnt(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_WIDTH_8, u32PackSize);
    PDMA_SetTransferAddr(PDMA,SPI_MASTER_TX_DMA_CH, (uint32_t)pTxBuf, PDMA_SAR_INC, (uint32_t)&QSPI0->TX, PDMA_DAR_FIX);
    PDMA_SetTransferMode(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_QSPI0_TX, FALSE, 0);
    PDMA_SetBurstType(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_REQ_SINGLE, 0);
    
    /* SPI master PDMA RX channel configuration: */
    PDMA_SetTransferCnt(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_WIDTH_8, u32PackSize);
    PDMA_SetTransferAddr(PDMA,SPI_MASTER_RX_DMA_CH, (uint32_t)&QSPI0->RX, PDMA_SAR_FIX, (uint32_t)pRxBuf, PDMA_DAR_INC);
    PDMA_SetTransferMode(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_QSPI0_RX, FALSE, 0);
    PDMA_SetBurstType(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_REQ_SINGLE, 0);
    
    g_u32rxtxDone = 0;
	gSPIPackageCount++;	
    
    /* Enable SPI master DMA function */    
    QSPI_TRIGGER_TX_RX_PDMA(QSPI0);
    return (1);
}

int UserSpiDataExchange(uint8_t *pTxBuf, uint8_t *pRxBuf, uint32_t u32PackSize)
{
    _doSPITransfer(pTxBuf, pRxBuf, u32PackSize);
    while(g_u32rxtxDone != 3);
    
    /* Disable SPI master DMA function */   
    QSPI_DISABLE_TX_RX_PDMA(QSPI0);
    return 1;
}


int UserDelay(uint32_t MircoSec)
{
    TIMER_Delay(TIMER2, MircoSec);
    return 1;
}
// Optional function
uint32_t UserSetCrcType(uint32_t u32CrcType)
{
    g_u32CrcType = u32CrcType;
    return g_u32CrcType;
}
uint32_t UserCalCrc(uint8_t *pu8Addr, uint32_t u32Size)
{
    uint32_t u32Addr,u32Offset;
    u32Addr = (uint32_t)pu8Addr;
    if(g_u32CrcType == 3){
        CRC_Open(CRC_32, (CRC_WDATA_RVS | CRC_CHECKSUM_RVS | CRC_CHECKSUM_COM), 0xffffffff, CRC_CPU_WDATA_32);
        for(u32Offset=0; u32Offset<u32Size; u32Offset+=4){
            CRC_WRITE_DATA(inpw(u32Addr+u32Offset));
        }
        return CRC_GetChecksum();
    }else if(g_u32CrcType == 2){
        CRC_Open(CRC_CCITT, (CRC_WDATA_RVS | CRC_CHECKSUM_RVS | CRC_CHECKSUM_COM), 0xffffffff, CRC_CPU_WDATA_16);
        for(u32Offset=0; u32Offset<u32Size; u32Offset+=2){
            CRC_WRITE_DATA(inps(u32Addr+u32Offset));
        }
        return CRC_GetChecksum();
    }else if(g_u32CrcType == 1){
        CRC_Open(CRC_8, (CRC_WDATA_RVS | CRC_CHECKSUM_RVS | CRC_CHECKSUM_COM), 0xffffffff, CRC_CPU_WDATA_8);
        for(u32Offset=0; u32Offset<u32Size; u32Offset++){
            CRC_WRITE_DATA(inpb(u32Addr+u32Offset));
        }
        return CRC_GetChecksum();
    }else{
        return ECM_CRC_MAGIC_NUM;
    }
}

int UserSpiDataExchangeResponse(int nRet, void*parg1, void*parg2, void*parg3,   void*parg4, void*parg5)
{
    //TRACE_MSG("30");
    /* Disable SPI master DMA function */   
    //QSPI_DISABLE_TX_RX_PDMA(QSPI0);
    QSPI_DISABLE_TX_PDMA(QSPI0);
    QSPI_DISABLE_RX_PDMA(QSPI0);
    return 1;   
}


int UserSpiDataExchangeISR(uint8_t *pTxBuf, uint8_t *pRxBuf, uint32_t u32PackSize)
{
    //TRACE_MSG("10");
    g_u8PDMA_IRQ_Callback = 1;
    //EC_CmdResponsePush(UserSpiDataExchangeResponse, NULL, NULL,NULL,NULL,NULL); 
    _doSPITransfer(pTxBuf, pRxBuf, u32PackSize);  

    return 1;
}


void SysTick_open(void)
{
        // config SysTick = 200us
        uint32_t ticks = PLL_CLOCK/5000;
    
        SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
        SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
        SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;     
}


void SysTick_enable(void)
{
        SysTick->VAL   = 0; 
        SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}


void SysTick_disable(void)
{
        SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk; 
}
} // extern "C"

//  (C) COPYRIGHT 2020 NEXTW Technology Corp.
