//#include <stdio.h>
#include <stdint.h>
#include "NuMicro.h"
#include "platform.h"
#include "trace_config.h"
#include "test.h" 



uint32_t Tick_10ms;
#define TIMEOUT_COUNTS_US	16
#define TIMEOUT_COUNTS_MS	16*1000
//------------------------------------------------------------------------
//  FPGA Register Definition
//------------------------------------------------------------------------
#define uint8							uint8_t
#define uint16						uint16_t
#define BYTE							unsigned char
#define WORD							unsigned short
#define DWORD							unsigned long
#define SBYTE							char
#define SWORD							short
#define SDWORD							long

#define FPGA_AXIS_DDA0								0x000	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER0		0x002	// 16-bit, R
#define FPGA_AXIS_DDA1								0x004	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER1		0x006	// 16-bit, R
#define FPGA_AXIS_DDA2								0x008	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER2		0x00a	// 16-bit, R
#define FPGA_AXIS_DDA3								0x00c	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER3		0x00e	// 16-bit, R
#define FPGA_AXIS_DDA4								0x010	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER4		0x012	// 16-bit, R
#define FPGA_AXIS_DDA5								0x014	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER5		0x016	// 16-bit, R
#define FPGA_AXIS_DDA6								0x018	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER6		0x01a	// 16-bit, R
#define FPGA_AXIS_DDA7								0x01c	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_COUNTER7		0x01e	// 16-bit, R

#define FPGA_MPG_HANDWHEEL_COUNTER		0x020	// 16-bit, R

#define FPGA_CONTROL1									0x030	// 8-bit, R/W
#define FPGA_CONTROL2									0x031	// 8-bit, R/W
#define FPGA_CONTROL3									0x032	// 8-bit, R/W
#define FPGA_CONTROL4									0x033	// 8-bit, R/W

#define FPGA_AXIS_FEEDBACK_CMP0				0x040	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_CMP1				0x042	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_CMP2				0x044	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_CMP3				0x046	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_CMP4				0x048	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_CMP5				0x04a	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_CMP6				0x04c	// 16-bit, R/W
#define FPGA_AXIS_FEEDBACK_CMP7				0x04e	// 16-bit, R/W

#define FPGA_ADC1											0x0e0	// 16-bit, R
#define FPGA_ADC2											0x0e2	// 16-bit, R
#define FPGA_ADC3											0x0e4	// 16-bit, R
#define FPGA_ADC4											0x0e6	// 16-bit, R
#define FPGA_DAC1											0x0e8	// 8-bit, R/W
#define FPGA_DAC2											0x0ea	// 8-bit, R/W
#define FPGA_DAC3											0x0ec	// 8-bit, R/W
#define FPGA_DAC4											0x0ee	// 8-bit, R/W

#define FPGA_ARM_NUM_OF_AXIS					0x0f1	// 8-bit, R
#define FPGA_DRIVE_CLEAR							0x0f2	// 8-bit, R/W
#define FPGA_DRIVE_SERVO_ON						0x0f3	// 8-bit, R/W
#define FPGA_DRIVE_ALM								0x0f4	// 8-bit, R
#define FPGA_DRIVE_NEAR								0x0f5	// 8-bit, R
#define FPGA_HOME_STATUS							0x0f7	// 8-bit, R

#define FPGA_STOP_AXIS_T1							0x0f8	// 8-bit, R/W
#define FPGA_STOP_AXIS_T2							0x0f9	// 8-bit, R/W
#define FPGA_STOP_AXIS_T3							0x0fa	// 8-bit, R/W
#define FPGA_STOP_AXIS_T4							0x0fb	// 8-bit, R/W
#define FPGA_ORG_EDGE_MODE						0x0fc	// 8-bit, R/W
#define FPGA_ORG_AUTO_STOP_ENABLE			0x0fd	// 8-bit, R/W

#define FPGA_ORG_STOP_AXIS_X					0x100	// 8-bit, R/W
#define FPGA_ORG_STOP_AXIS_Z					0x101	// 8-bit, R/W
#define FPGA_ORG_STOP_AXIS_A					0x102	// 8-bit, R/W
#define FPGA_ORG_STOP_AXIS_B					0x103	// 8-bit, R/W
#define FPGA_ORG_STOP_AXIS_C					0x104	// 8-bit, R/W
#define FPGA_ORG_STOP_AXIS_D					0x105	// 8-bit, R/W
#define FPGA_FEEDBACK_CLEAR_ENABLE		0x106	// 8-bit, R/W

#define FPGA_EXT_ORG_INT_FLAG					0x108	// 8-bit, R
#define FPGA_EXT_ORG_INT_CONTROL			0x10a	// 8-bit, R/W
#define FPGA_EXT_ORG_EDGE_MODE				0x10c	// 8-bit, R/W

#define FPGA_HOME_INT_FLAG						0x110	// 8-bit, R
#define FPGA_HOME_INT_CONTROL					0x114	// 8-bit, R/W

#define FPGA_GPIO_OUTL								0xc00	// 8-bit, R/W
#define FPGA_GPIO_OUTM								0xc02	// 8-bit, R/W
#define FPGA_GPIO_OUTH								0xc04	// 8-bit, R/W
#define FPGA_GPIO_OUTE								0xc06	// 8-bit, R/W

#define FPGA_GPIO_INL									0xc08	// 8-bit, R
#define FPGA_GPIO_INM									0xc0a	// 8-bit, R
#define FPGA_GPIO_INH									0xc0c	// 8-bit, R
#define FPGA_GPIO_INE									0xc0e	// 8-bit, R

#define FPGA_TOUCH_INT_FLAG						0xc10	// 8-bit, R
#define FPGA_TOUCH_INT_CONTROL				0xc12	// 8-bit, R/W
#define FPGA_TOUCH_EDGE_MODE					0xc14	// 8-bit, R/W

#define KEY_STATUS								0xc1c	// 8-bit, R
#define KEY_COMMAND 		0xc0c
#define KEY_ACK 			0x1
#define KEY_NORMAL			0xff

#define FPGA_MPG_HANDWHEEL_IN					0xc20	// 8-bit, R
#define FPGA_MPG_HANDWHEEL_SCAN				0xc22	// 8-bit, R
#define FPGA_MPG_HANDWHEEL_MUL				0xc24	// 8-bit, R

#define FPGA_REP_TIME_INTERVAL1				0xc30	// 16-bit, R/W
#define FPGA_REP_TIME_INTERVAL2				0xc32	// 16-bit, R/W

#define FPGA_WRITE_COUNTER0						0xf00	// 16-bit, R/W
#define FPGA_WRITE_COUNTER1						0xf02	// 16-bit, R/W
#define FPGA_WRITE_COUNTER2						0xf04	// 16-bit, R/W
#define FPGA_WRITE_COUNTER3						0xf06	// 16-bit, R/W
#define FPGA_WRITE_COUNTER4						0xf08	// 16-bit, R/W
#define FPGA_WRITE_COUNTER5						0xf0a	// 16-bit, R/W
#define FPGA_WRITE_COUNTER6						0xf0c	// 16-bit, R/W
#define FPGA_WRITE_COUNTER7						0xf0e	// 16-bit, R/W



//-----------------------------
// AXIS
//-----------------------------
#define Rd1_1(var)																									\
				  var =SRAM_READ8(RxCmdBuf1+rRxCmdBuf1);										\
					INC_idxCmdBuf(rRxCmdBuf1) ;

#define Rd2_1(var)																									\
				  Rd1_1(var)																							 		\
				  var +=(SRAM_READ8(RxCmdBuf1+rRxCmdBuf1)<< 8);							\
					INC_idxCmdBuf(rRxCmdBuf1) ;
					
					
#define Rd3_1(var)																									\
				  Rd2_1(var)																									\
				  var+=(SRAM_READ8(RxCmdBuf1+rRxCmdBuf1)<<16) ;							\
					INC_idxCmdBuf(rRxCmdBuf1);

#define Rd4_1(var)																									\
				  Rd3_1(var)																									\
				  var+=(SRAM_READ8(RxCmdBuf1+rRxCmdBuf1)<<24) ;							\
					INC_idxCmdBuf(rRxCmdBuf1);


void LoadCell_Handler();

//------------------------------------------------------------------------
//  ARM Configuration Registers
//------------------------------------------------------------------------
void Configure_EBI_16BIT_Pins(void)
{
    /* EBI AD0~5 pins on PC.0~5 */
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_EBI_AD0 | SYS_GPC_MFPL_PC1MFP_EBI_AD1 |
                     SYS_GPC_MFPL_PC2MFP_EBI_AD2 | SYS_GPC_MFPL_PC3MFP_EBI_AD3 |
                     SYS_GPC_MFPL_PC4MFP_EBI_AD4 | SYS_GPC_MFPL_PC5MFP_EBI_AD5;

    /* EBI AD6, AD7 pins on PD.8, PD.9 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD8MFP_EBI_AD6 | SYS_GPD_MFPH_PD9MFP_EBI_AD7;

    /* EBI AD8, AD9 pins on PE.14, PE.15 */
    SYS->GPE_MFPH |= SYS_GPE_MFPH_PE14MFP_EBI_AD8 | SYS_GPE_MFPH_PE15MFP_EBI_AD9;

    /* EBI AD10, AD11 pins on PE.1, PE.0 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE1MFP_EBI_AD10 | SYS_GPE_MFPL_PE0MFP_EBI_AD11;

    /* EBI AD12~15 pins on PH.8~11 */
    SYS->GPH_MFPH |= SYS_GPH_MFPH_PH8MFP_EBI_AD12 | SYS_GPH_MFPH_PH9MFP_EBI_AD13 |
                     SYS_GPH_MFPH_PH10MFP_EBI_AD14 | SYS_GPH_MFPH_PH11MFP_EBI_AD15;

    /* EBI ADR16, ADR17 pins on PF.9, PF.8 */
    SYS->GPF_MFPH |= SYS_GPF_MFPH_PF9MFP_EBI_ADR16 | SYS_GPF_MFPH_PF8MFP_EBI_ADR17;

    /* EBI ADR18, ADR19 pins on PF.7, PF.6 */
    SYS->GPF_MFPL |= SYS_GPF_MFPL_PF7MFP_EBI_ADR18 | SYS_GPF_MFPL_PF6MFP_EBI_ADR19;


    /* EBI RD and WR pins on PE.4 and PE.5 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE4MFP_EBI_nWR | SYS_GPE_MFPL_PE5MFP_EBI_nRD;

    /* EBI WRL and WRH pins on PG.7 and PG.8 */
    SYS->GPG_MFPL |= SYS_GPG_MFPL_PG7MFP_EBI_nWRL;
    SYS->GPG_MFPH |= SYS_GPG_MFPH_PG8MFP_EBI_nWRH;

    /* EBI CS0 pin on PD.12 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD12MFP_EBI_nCS0;

		/* EBI CS1 pin on PD.11 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD11MFP_EBI_nCS1; //1MBYTE擴充記憶體的CS
		
    /* EBI ALE pin on PE.2 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE2MFP_EBI_ALE;

    /* EBI MCLK pin on PE.3 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE3MFP_EBI_MCLK;
}

void SYS_Init(uint32_t u32SpiFreq)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;
	

    /* Enable IP clock */
    //CLK_EnableModuleClock(UART0_MODULE);
	CLK_EnableModuleClock(UART1_MODULE);
	CLK_EnableModuleClock(UART3_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_EnableModuleClock(TMR1_MODULE);


    /* Select IP clock source */
    //CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
	CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART1SEL_HXT, CLK_CLKDIV0_UART1(1));
    CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL3_UART3SEL_HXT, CLK_CLKDIV4_UART3(1));      
	CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);
	CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_HXT, 0);
		
		/* Select PCLK0 as the clock source of QSPI0 */
    CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PCLK0, MODULE_NoMsk);
    /* Select PCLK0 as the clock source of QSPI0 */
    //CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PCLK0, MODULE_NoMsk);
    /* Select HXT(12MHz) as the clock source of TMR0 */ 
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);
	CLK_EnableModuleClock(TMR2_MODULE);
		

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    //SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    //SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set GPB multi-function pins for UART1 RXD and TXD */
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB2MFP_UART1_RXD | SYS_GPB_MFPL_PB3MFP_UART1_TXD);
		
	/* Set GPB multi-function pins for UART2 RXD and TXD */
    //SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB0MFP_Msk);
    //SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_UART2_RXD | SYS_GPB_MFPL_PB1MFP_UART2_TXD);

    /* Set GPB multi-function pins for UART3 RXD(PD0) and TXD(PD1) */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD0MFP_UART3_RXD | SYS_GPD_MFPL_PD1MFP_UART3_TXD); 
    
    CLK_EnableModuleClock(QSPI0_MODULE);
    CLK_EnableModuleClock(PDMA_MODULE);
    CLK_EnableModuleClock(CRC_MODULE);
	/* Configure QSPI0 related multi-function pins. GPA[3:0] : QSPI0_MOSI0, QSPI0_MISO0, QSPI0_CLK, QSPI0_SS. */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_QSPI0_MOSI0 | SYS_GPA_MFPL_PA1MFP_QSPI0_MISO0 | SYS_GPA_MFPL_PA2MFP_QSPI0_CLK | SYS_GPA_MFPL_PA3MFP_QSPI0_SS;
    /* Enable QSPI0 clock pin (PA2) schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;
    /* Enable QSPI0 I/O high slew rate */
    GPIO_SetSlewCtl(PA, 0x3F, GPIO_SLEWCTL_HIGH);
	// SPI setup
    QSPI_Open(QSPI0, SPI_MASTER, SPI_MODE_0, 8, u32SpiFreq);
    QSPI_EnableAutoSS(QSPI0, SPI_SS, SPI_SS_ACTIVE_LOW);
    PDMA_Open(PDMA,(1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH));
    PDMA_EnableInt(PDMA, SPI_MASTER_RX_DMA_CH, PDMA_INT_TRANS_DONE);
    PDMA_EnableInt(PDMA, SPI_MASTER_TX_DMA_CH, PDMA_INT_TRANS_DONE);
    NVIC_EnableIRQ(PDMA_IRQn);
	NVIC_SetPriority(PDMA_IRQn, 0);	// 0: Highest priority, 0xF : Lowest priority.
	
    /* Lock protected registers */
    SYS_LockReg();		
}

void Config_Hardware(uint32_t spi_clock)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init(spi_clock);
	   
	  /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    CLK_EnableModuleClock(EBI_MODULE);

    /* Lock protected registers */
    SYS_LockReg();
	
	/* Init UART to 115200-8n1 for print message */
	 
    //UART_Open(UART0, 115200);
	UART_Open(UART1, 115200);  // raspberry
	UART_Open(UART3, 115200);
	//NVIC_EnableIRQ(UART0_IRQn);
	//UART_EnableInt(UART0, (UART_INTEN_RDAIEN_Msk));// | UART_INTEN_THREIEN_Msk | UART_INTEN_RXTOIEN_Msk));
	NVIC_EnableIRQ(UART1_IRQn);
	UART_EnableInt(UART1, (UART_INTEN_RDAIEN_Msk));// | UART_INTEN_THREIEN_Msk | UART_INTEN_RXTOIEN_Msk));
	NVIC_EnableIRQ(UART3_IRQn);
	UART_EnableInt(UART3, (UART_INTEN_RDAIEN_Msk));// | UART_INTEN_THREIEN_Msk | UART_INTEN_RXTOIEN_Msk));
		
	/* Configure multi-function pins for EBI 16-bit application */
  Configure_EBI_16BIT_Pins();

	/* Initialize EBI bank0 to access external FPGA */
  EBI_Open(EBI_BANK0, EBI_BUSWIDTH_8BIT, EBI_TIMING_SLOWEST, 0, EBI_CS_ACTIVE_LOW); //,EBI_TIMING_SLOWEST
		
	/* Initialize EBI bank1 to access external SRAM */
  EBI_Open(EBI_BANK1, EBI_BUSWIDTH_16BIT,EBI_TIMING_NORMAL , 0, EBI_CS_ACTIVE_LOW); //EBI_TIMING_VERYFAST,EBI_TIMING_FAST,EBI_TIMING_NORMAL,EBI_TIMING_NORMAL,EBI_TIMING_SLOWEST
	//Timer setup
	// 
	TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 5000); //200us interrupt 1次
	// Enable timer interrupt
  TIMER_EnableInt(TIMER0);
  NVIC_EnableIRQ(TMR0_IRQn);
	TIMER_Start(TIMER0);		
		
	// Set timer frequency to 1MS
	TIMER_Open(TIMER1, TIMER_PERIODIC_MODE, 1000); // 1ms interrupt 1次
  // Enable timer interrupt
  TIMER_EnableInt(TIMER1);
  NVIC_EnableIRQ(TMR1_IRQn);
	TIMER_Start(TIMER1);		
		
	TIMER_SET_PRESCALE_VALUE(TIMER2, 0);
    // Set compare value as large as possible, so don't need to worry about counter overrun too frequently.
    TIMER_SET_CMP_VALUE(TIMER2, 0xFFFFFF);
    // Configure Timer 0 free counting mode, capture TDR value on rising edge
    TIMER_EnableCapture(TIMER2, TIMER_CAPTURE_FREE_COUNTING_MODE, TIMER_CAPTURE_EVENT_RISING);
    // Start Timer 0
    TIMER_Start(TIMER2);
}	


//------------------------------------------------------------------------
//  IRQ Handlers
//------------------------------------------------------------------------
extern "C"
{
 
    
	void UART3_IRQHandler(void){
		UART_T* uart=UART3;//  Raspberry

		if (!(uart->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)){   // Check RX empty => failed 
			uint8_t t1 = (uint8_t)uart->DAT ; 
			gstUARTModbus.si_buf[gstUARTModbus.si_buf_put_idx] = t1;
            __UART_BUF_INCR(gstUARTModbus.si_buf_put_idx);			
			gstUARTModbus.si_buf_len++;
            
		}
		
		if(uart->INTSTS&UART_INTSTS_THREINT_Msk){
			//傳送暫存器是空的
            if (gstUARTModbus.so_buf_get_idx != gstUARTModbus.so_buf_put_idx) {
                uart->DAT = gstUARTModbus.so_buf[gstUARTModbus.so_buf_get_idx];
                __UART_BUF_INCR(gstUARTModbus.so_buf_get_idx);
			
			}
			else{
				UART_DisableInt(uart, UART_INTEN_THREIEN_Msk) ;
			}
		}
		else{
		}
		UART_ClearIntFlag(uart, UART_INTSTS_RLSINT_Msk);
	}
    
	static int cnt_uart=1 ;
	static int cnt_uart_re=1 ;
	static int len=0 ;
	static int buf_idx ;
  extern char gUARTCmdTxBuf[];  
    
	void UART1_IRQHandler(void){
		UART_T* uart=UART1;//  Raspberry
// 		RTT("uart->FIFOSTS=%x",uart->FIFOSTS) ;
		if(!(uart->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)){   // Check RX empty => failed 
				uint8_t t1=(uint8_t)uart->DAT ;
                
//  			  RTT("%d---->%x",cnt_uart_re,t1) ;
//  				cnt_uart_re++ ;
// 				SRAM_WRITE8(RxCmdBuf1+wRxCmdBuf1,t1 ) ; // Get Data from UART RX  			
// 				INC_idxCmdBuf(wRxCmdBuf1);
			  switch(CmdState){
					case CMD1:
						//儲存命令
					  CmdBufTbl[widx_CmdBufTbl].cmd=t1 ;
					  CmdState=CMD2 ;
				    break ;
					case CMD2:
					  if((CmdBufTbl[widx_CmdBufTbl].cmd+t1)== 0xff){
							if(CmdBufTbl[widx_CmdBufTbl].cmd==defUART_wReset_0xa2){
								flgResetCmd=true ;
								break ;
							}
							for(int i=0 ; i < UART_cmdtbl[i].cmd !=0 ; i++){
								if(CmdBufTbl[widx_CmdBufTbl].cmd== UART_cmdtbl[i].cmd){
									len=UART_cmdtbl[i].length ;
									buf_idx=0 ;
									RTT("CMD:%x len=%d",CmdBufTbl[widx_CmdBufTbl].cmd,len) ;
									if(len==0){
										CmdState=CMD1 ;
										widx_CmdBufTbl++ ;
										if(widx_CmdBufTbl >= MAX_CMDBUFTBL){
											widx_CmdBufTbl=0;
										}
									}
									else{
										CmdState=ST_DATA ;
									}
									break ;
								}
							}
							if(CmdState == CMD2){
								// illegal cmd
								RTT("illegal cmd in UART1_IRQHandler %x  %x",CmdBufTbl[widx_CmdBufTbl].cmd,t1) ;
								CmdState=CMD1;
							}
						}
						else{
							RTT("illegal cmd in UART1_IRQHandler %x",CmdBufTbl[widx_CmdBufTbl].cmd) ;
							CmdBufTbl[widx_CmdBufTbl].cmd=t1 ;
						}
						break ;
					case ST_DATA:
						len-- ;
					  CmdBufTbl[widx_CmdBufTbl].buf[buf_idx++]=t1 ;
					  if(len ==0){
							CmdState=CMD1 ;
							CmdBufTbl[widx_CmdBufTbl].ms=msTicks;
							RTT("widx_CmdBufTbl=%d",widx_CmdBufTbl) ;
							if(CmdBufTbl[widx_CmdBufTbl].cmd == defUART_HandWheelPower_0xDE){
								RTT("HandWheelPower=%d" ,t1) ;
								SetHandWheelPower(t1);
							}
						  else if(CmdBufTbl[widx_CmdBufTbl].cmd == defUART_HandWheelAxis_0xDF){
								RTT("HandWheelAxis=%d" ,t1) ;
#ifdef RTT_TRACE_LOC
								TraceLoc.axis=t1 ;
								TraceLoc.flg=false ;
#endif
							}
							else if(CmdBufTbl[widx_CmdBufTbl].cmd == defUART_wSPD_0x2c){
								RTT("SPD:%d",t1) ;
								SetSPD(t1) ;
							}
							else{
								widx_CmdBufTbl++ ;
								if(widx_CmdBufTbl >= MAX_CMDBUFTBL){
									widx_CmdBufTbl=0;
								}
							}	
						}
						break ;			
				}			
		}
		
		if(uart->INTSTS&UART_INTSTS_THREINT_Msk){
			//傳送暫存器是空的
			if(wTxCmdBuf1 !=rTxCmdBuf1){
				//buf有要傳送的資料
				uint8_t t1 = gUARTCmdTxBuf[rTxCmdBuf1] ;   			
				INC_idxCmdBuf(rTxCmdBuf1);
				uart->DAT=t1 ;
				cnt_uart++ ;
			}
			else{
				UART_DisableInt(uart,UART_INTEN_THREIEN_Msk) ;
			}
		}
		else{
// 				RTT("else uart->FIFOSTS=%x",uart->FIFOSTS) ;
		}
		UART_ClearIntFlag(uart, UART_INTSTS_RLSINT_Msk);
	}

	void TMR0_IRQHandler(void){ //200us interrupt
        TRACE_ISR_ENTRY();
		TimerTicks2.timer++ ;		
		
        TIMER_ClearIntFlag(TIMER0);
        TRACE_ISR_EXIT();
	}
    
    
	void TMR1_IRQHandler(void){	//1ms interrupt
        TRACE_ISR_ENTRY();	
        msTicks++ ;		
				TimerIsr();
        TIMER_ClearIntFlag(TIMER1);
        TRACE_ISR_EXIT();
	}
	
}
extern "C"
{
	void GPG_IRQHandler(void){
    /* To check if PG.15 interrupt occurred */
		//IRQ5------DDA
    TRACE_ISR_ENTRY();
		static int cnt =0 ;
		static int cnt1=0; 
    if(GPIO_GET_INT_FLAG(PG, BIT15))
    {
			  FPGA_WRITE16(0,2) ;
			  FPGA_WRITE16(8,2) ;
#ifdef TEST_BREAK_PULSE
			  FPGA_WRITE16(4,Touch.step) ;
			  Touch.ddacnt[Touch.idx_ddacnt++]=FPGA_READ16(6) ;
			  if(Touch.idx_ddacnt ==MAX_DDACNT){
					Touch.idx_ddacnt=0 ;
				}
				if((Touch.flag != 0)&& (Touch.cnt < 100)){
					  if(Touch.cnt==0){
							 // DUMP Touch之前的值
							for(int i=0 ; i < MAX_DDACNT ;i++){
								MSG_RTT("%x\n",Touch.ddacnt[Touch.idx_ddacnt++]) ;
								if(Touch.idx_ddacnt ==MAX_DDACNT){
										Touch.idx_ddacnt=0 ;
								}	
							}
							MSG_RTT("------------------------------------\n") ;
						}
					  Touch.cnt++;
				    MSG_RTT("%x\n",FPGA_READ16(6)) ;
  			    TRACE_MSG("%x\n",FPGA_READ16(6)) ;
				}
#endif			
			  cnt++;
			  if((cnt %(1000*60))==0){
					cnt1++;
					TRACE_MSG("%d min",cnt1) ;
				}
        GPIO_CLR_INT_FLAG(PG, BIT15);
        //printf("PG.15 INT occurred.\n");
    }
    else
    {
        /* Un-expected interrupt. Just clear all PG interrupts */
        PG->INTSRC = PG->INTSRC;
        //printf("Un-expected interrupts.\n");
    }
    TRACE_ISR_EXIT();
	}
}

extern "C"
{
	void GPF_IRQHandler(void){
    /* To check if PF.11 interrupt occurred */
    TRACE_ISR_ENTRY();
    if(GPIO_GET_INT_FLAG(PF, BIT11))
    {
		// uint8 status= rDosMem(pc_base+INL);
		// 		printf("2_%d\n",status);
		TouchIsr();
        GPIO_CLR_INT_FLAG(PF, BIT11);
    }
    else
    {
        /* Un-expected interrupt. Just clear all PG interrupts */
        PF->INTSRC = PF->INTSRC;
        //printf("Un-expected interrupts.\n");
    }
    TRACE_ISR_EXIT();
	}
}


//------------------------------------------------------------------------
//  Serial Communication



class SerialCom
{       
public:
	SerialCom()	//Constructor
	{
		;
	}
	
	uint32_t Tx(unsigned char TxBuf[], uint32_t u32WriteBytes)
	{
		return UART_Write(UART2, TxBuf, u32WriteBytes);
	}

int32_t UART_PosWrite(UART_T* uart, uint8_t pu8TxBuf[], int32_t u32WriteBytes)
{
    uint32_t  u32Count, u32delayno;
    uint32_t  u32Exit = 0ul;

    for(u32Count = 0ul; u32Count != u32WriteBytes; u32Count++)
    {
        u32delayno = 0ul;
        while(uart->FIFOSTS & UART_FIFOSTS_TXFULL_Msk)   /* Check Tx Full */
        {
            u32delayno++;
            if(u32delayno >= 0x40000000ul)
            {
                u32Exit = 1ul;
                break;
            }
            else
            {
            }
        }

        if(u32Exit == 1ul)
        {
            break;
        }
        else
        {
            uart->DAT = pu8TxBuf[u32Count];    /* Send UART Data from buffer */
        }
    }

    return u32Count;
}
	uint32_t Rx(unsigned char RxBuf[], uint32_t BytesToRead, uint32_t Timeout_count)	
	{
    uint32_t  u32Count, u32delayno;
    uint32_t  u32Exit = 0ul;

    for(u32Count = 0ul; u32Count < BytesToRead; u32Count++)
    {	
        u32delayno = 0ul;
				while(uart->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk)   /* Check RX empty => failed */
        {
						if(Timeout_count == 0)
							continue;
						
						u32delayno++;
						if(u32delayno >= Timeout_count)
            {
                u32Exit = 1ul;
                break;
            }
        }
        if(u32Exit == 1ul)
        {
            break;
        }
        else
        {
            RxBuf[u32Count] = (uint8_t)uart->DAT; /* Get Data from UART RX  */
        }
    }
    return u32Count;
	}
		uint32_t Rx(unsigned char RxBuf[])	
	{
		//uint32_t  u32Count, u32delayno;
		if(!(uart->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk))   /* Check RX empty => failed */

    {	
        RxBuf[WriteId] = (uint8_t)uart->DAT; /* Get Data from UART RX  */			
			WriteId++;
			if(WriteId > MAX_CMD_BUF) 
					WriteId=1;

    }
    return WriteId;
	}
	UART_T* uart;
};



