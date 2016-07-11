/*
 * MODULE
 *
 *   init.c
 *
 * DESCRIPTION
 *
 *  Hardware Initialization Routines
 *
 * PLATFORM
 *
 *  Olimex LPC-2378-STK
 *
 * HISTORY
 *
 *   2007/10/31: Mitch Ishihara:
 *     changed PINSEL10 setting to just write the value instead
 *       of read-modify-write.
 *   2007/10/01: Mitch Ishihara:
 *     split init routines from main.c
 *     changed MEMMAP to USERRAMMODE to run completely from RAM
 *   2007/09/12: Andrew N. Sloss:
 *     convert the main.c to use VOLATILExx(<address>) format
 *     added 1st draft comments
 *   2007/08/21: Andrew N. Sloss:
 *     inspired from James Lynch's example code demo2106_blink_flash.
 *
 * NOTES
 *
 */


#include <cpu.h>
#include "../inc/platform/lpc2478-stk.h"
#include "pins.h"
#include "uarts.h"
#include "init.h"

/* local functions */
static void initPLL(scb2300_t * pSCBParams);
static void initPCLK(void);
static void initGPIO(void);
static void initMAM(INT32U cclk, INT8U mamcr, INT8U mamtim_override);

/*
 * DESCRIPTION:
 *
 *  initializes all the hardware components.
 */
void initHardware(void)
{
    /* Initial SCB Parameters */
    scb2300_t SCBParams = {
        .PLL_M_Mul = 12,           /* PLL Multiplier. Valid values 6 through 512*/
        .PLL_N_Div = 1,            /* PLL Divider. Valid values 1 through 32 */
        .PLL_Fcco = 288000000,     /* Frequency (Hz) of PLL output */
        .CCLK_Div = 6,             /* CPU Clock divider, cclk */
        .MAMMode = MAMCR_PARTIAL,  /* MAM mode Partial is the preferred setting for Rev -,A parts */
        .MAMTim = MAMTIM_AUTOCFG   /* Let initMAM calculate the optimal MAM timing */
    };

    scb2300_t *pSCBParams = &SCBParams;

	INT32U cclk = pSCBParams->PLL_Fcco/pSCBParams->CCLK_Div;
	/*
     * intialize main hardware components
     */
	/* Must turn off MAM before increasing frequency */
    initMAM(cclk, MAMCR_OFF, MAMTIM_MAX_CLK);
    
    initPLL(pSCBParams);
    initMAM(cclk, pSCBParams->MAMMode, pSCBParams->MAMTim);
    initPCLK();
    initGPIO();
    VIC_Init();
    
    /* intialize specific hardware components for UART0 */
    initUART0(38400, UART_8N1, UART_FIFO_OFF, cclk);
    
    /* MEMMAP Choices are:
    BOOTLOADERMODE      0x00
    USERFLASHMODE       0x01
    USERRAMMODE         0x02
    EXTERNALMEMORYMODE  0x03
    */
    //DMI VOLATILE32(MEMMAP) = USERRAMMODE;
    P_SCB_REGS->MEMMAP = USERFLASHMODE;
}


/******************************************************************************
 *
 * DESCRIPTION
 *
 *  This init is specific to the 2300 family of devices.
 *  
 * NOTES
 *
 *  Taken from the LPC2378 User Manual:
 *
 *   5.14 PLL setup sequence
 *
 *   The following sequence must be followed step by step in order to
 *   have the PLL initialized an running:
 *
 *   1. Disconnect the PLL with one feed sequence if PLL is already
 *      connected.
 *   2. Disable the PLL with one feed sequence.
 *   3. Change the CPU Clock Divider setting to speed up operation without
 *      the PLL, if desired.
 *   4. Write to the Clock Source Selection Control register to change the
 *      clock source.
 *   5. Write to the PLLCFG and make it effective with one feed sequence.
 *      The PLLCFG can only be updated when the PLL is disabled.
 *   6. Enable the PLL with one feed sequence.
 *   7. Change the CPU Clock Divider setting for the operation with the
 *      PLL. It's critical to do this before connecting the PLL.
 *   8. Wait for the PLL to achieve lock by monitoring the PLOCK bit in the
 *      PLLSTAT register, or using the PLOCK interrupt, or wait for a fixed
 *      time when the input clock to PLL is slow (i.e. 32 kHz). The value of
 *      PLOCK may not be stable when the PLL reference frequency (FREF, the
 *      frequency of REFCLK, which is equal to the PLL input frequency divided
 *      by the pre-divider value) is less than 100 kHz or greater than 20
 *      MHz. In these cases, the PLL may be assumed to be stable after a
 *      start-up time has passed. This time is 500 us when FREF is
 *      greater than 400 kHz and 200 / FREF seconds when FREF is less than
 *      400kHz.
 *   9. Connect the PLL with one feed sequence.
 *
 *   It's very important not to merge any steps above. For example, don't
 *   update the PLLCFG and enable the PLL simultaneously with the same feed
 *   sequence.
 *
 *
 *  This implementation is fixed as follows:
 * 1. Uses the main oscillator
 * 2. PLL Fcco is fixed at compile time at 288 MHz using external defines
 * 3. It also sets the CCLK to a known stable 48 MHz
 */
static void initPLL(scb2300_t * pSCBParams)
{
	INT32U pllcfg;
	
	/* [1] Check if PLL connected, disconnect if yes. */
    if ((P_SCB_REGS->PLLSTAT) & PLLSTAT_PLLC)
    {
    	P_SCB_REGS->PLLCON = PLLCON_PLLE;
        /* Enable PLL, disconnected ( PLLC = 0)*/
    	P_SCB_REGS->PLLFEED = 0xAA;
    	P_SCB_REGS->PLLFEED = 0x55;
    }

    /* [2] Disable the PLL once it has been disconnected. */
    P_SCB_REGS->PLLCON  = 0;
    P_SCB_REGS->PLLFEED = 0xAA;
    P_SCB_REGS->PLLFEED = 0x55;

    /* [3] Change the CPU Clock Divider setting 
     * to speed up operation without the PLL, if desired. 
     * We're going to divide by 1 for maximum non-PLL clock speed.
     * NOTE: CCLKCFG adds one internally so we must subtract one */
    P_SCB_REGS->CCLKCFG = (CCLK_DIV_1 - 1);

    /* [4] Enable the main oscillator, select clock source  */
    P_SCB_REGS->SCS |= SCS_OSCEN;

    /* Wait until main OSC is usable */
    do {} while ((P_SCB_REGS->SCS & SCS_OSCSTAT) == 0);

    /* Select the main osc as the PLL clk source. */
    P_SCB_REGS->CLKSRCSEL = CLKSRC_MAIN_OSC;

    /*
     * NOTES:
     *
     * Set multiplier and divider values.
     *
     *  PLLCFG = ((N - 1) << 16) + (M - 1)
     *
     *  F_cco = (2 * M *F_in)/N
     *      M = 12, N = 1, F_in = 12.000 MHz -> F_cco = 288.000 MHz
     *
     */
    /* [5] Write to the PLLCFG and make it effective with feed sequence */
    pllcfg = (((pSCBParams->PLL_N_Div - 1) << 16) + ((pSCBParams->PLL_M_Mul - 1) << 0));
    P_SCB_REGS->PLLCFG = pllcfg;
    P_SCB_REGS->PLLFEED = 0xAA;
    P_SCB_REGS->PLLFEED = 0x55;
    
    /* [6] Enable the PLL and make it effective with feed sequence */
    P_SCB_REGS->PLLCON  = PLLCON_PLLE;
    P_SCB_REGS->PLLFEED = 0xAA;
    P_SCB_REGS->PLLFEED = 0x55;
        
    /* [7] Change the CPU Clock Divider setting for the operation with the PLL.
     *     It's critical to do this before connecting the PLL.
     * NOTE: CCLKCFG adds one internally so we must subtract one
     * Divide F_cco down to get the CCLK output. */
    P_SCB_REGS->CCLKCFG = (pSCBParams->CCLK_Div - 1);

    /* [8] Wait for the PLL to lock to set frequency 
     * TODO: Add timeout for slow FREF */
    do {} while(((P_SCB_REGS->PLLSTAT) & PLLSTAT_PLOCK) == 0);
    do {} while(((P_SCB_REGS->PLLSTAT) & 0x00FF7FFF) != pllcfg);
    
    /* [9] Enable and connect the PLL as the clock source */
    P_SCB_REGS->PLLCON = (PLLCON_PLLE | PLLCON_PLLC);
    P_SCB_REGS->PLLFEED = 0xAA;
    P_SCB_REGS->PLLFEED = 0x55;
    
    /* Check connect bit status and wait for connection. */
    do {} while(((P_SCB_REGS->PLLSTAT) & PLLSTAT_PLLC) == 0);

    return;
}

/*
 * DESCRIPTION
 *
 * enable the MAM accelerator and sets number of clocks used for
 * flash memory fetch.
 *
 * PARAMETERS
 * cclk : CPU Clock Frequency
 * mamcr: MAM mode MAMCR_OFF, MAMCR_PARTIAL, or MAMCR_FULL
 *
 * EXAMPLE
 *
 *   initMAM(12000000, MAMCR_PARTIAL);
 */

static void initMAM(INT32U cclk, INT8U mamcr, INT8U mamtim_override)
{
    /* disable MAM */
	P_SCB_REGS->MAMCR	= MAMCR_OFF;
	
	/* Either set according to override parameter or optimally calculate */
	if( (0 < mamtim_override) && (mamtim_override <= MAMTIM_MAX_CLK) )
	{
		P_SCB_REGS->MAMTIM	= mamtim_override;
	}
	else /* if( (mamtim_override == 0) || MAMTIM_MAX_CLK < mamtim_override  ) */
	{
		P_SCB_REGS->MAMTIM	= (((cclk)+19999999)/20000000); /* stable setting */
	}

	P_SCB_REGS->MAMCR	= mamcr;
}

/*
 * NAME
 *
 * initCCLK
 *
 * DESCRIPTION
 *
 * Set the cclk for CPU sub-system.
 *
 * PARAMETER
 *
 * none...
 *
 * EXAMPLE
 *
 *   initCCLK();
 *
 * NOTES
 *
 *  none...
 *
 */

void initCCLK( scb2300_t * pSCBParams )
{
    /* Divide F_cco down to get the cclk Divider. (Fcco / cclk = clock divider) 
     * NOTE: CCLKCFG adds one internally so we must subtract one */
	P_SCB_REGS->CCLKCFG = ((pSCBParams->PLL_Fcco/pSCBParams->CCLK_Div) - 1);

    return;
}


INT32U getFcclk( void )
{
    INT32U Fosc;
    INT32U Fpllclk;
    INT32U Fcclk;
    INT8U  clksrcsel;
    INT32U pllstat;
    INT16U M_mul;
    INT8U  N_div;
    INT8U  plle;
    INT8U  pllc;
    
	/* Determine Fosc from configured clock source */
    clksrcsel = P_SCB_REGS->CLKSRCSEL;
    if( (clksrcsel & CLKSRCSEL_MASK) == CLKSRC_INT_RC )
    {
    	Fosc = FOSC_INT_RC;
    }
    else if( (clksrcsel & CLKSRCSEL_MASK) == CLKSRC_MAIN_OSC )
    {
    	Fosc = FOSC_MAIN;
    }
    else if( (clksrcsel & CLKSRCSEL_MASK) == CLKSRC_MIN_RTC )
    {
    	Fosc = FOSC_RTC;
    }
    else /* Invalid clock source */
    {
    	return -1;
    }

    /* Determine Fpllclk based on PLL configuration */
    pllstat = P_SCB_REGS->PLLSTAT;
    M_mul = (pllstat & PLLSTAT_MSEL_MASK) + 1;
    N_div = ((pllstat & PLLSTAT_NSEL_MASK) >> 16) + 1;
    plle  = (pllstat & PLLSTAT_PLLE) >> 24;
    pllc  = (pllstat & PLLSTAT_PLLC) >> 25;
    
    if( plle && pllc )
    {
    	Fpllclk = (2 * M_mul * Fosc) / N_div; 
    }
    else
    {
    	Fpllclk = Fosc;
    }
    
    /* Find out cclk frequency based on CCLKCFG */
    Fcclk = Fpllclk/(P_SCB_REGS->CCLKCFG + 1);

    return Fcclk;
}

/*
 * NAME
 *
 * initPCLK
 *
 * DESCRIPTION
 *
 * Set the pclk for each peripheral. The default PDIV_4, but we do that
 * explicitly here to make it easier to change them later.
 *
 * PARAMETER
 *
 * none...
 *
 * EXAMPLE
 *
 *   initPCLK();
 *
 * NOTES
 *
 *  none...
 *
 */

static void initPCLK(void)
{
	P_SCB_REGS->PCLKSEL0 =
    (
          SET_PCLK (PCLK_WDT,     PDIV_4)
        | SET_PCLK (PCLK_TIMER0,  PDIV_1)
        | SET_PCLK (PCLK_TIMER1,  PDIV_4)
        | SET_PCLK (PCLK_UART0,   PDIV_1)
        | SET_PCLK (PCLK_UART1,   PDIV_1)
        | SET_PCLK (PCLK_PWM1,    PDIV_4)
        | SET_PCLK (PCLK_I2C0,    PDIV_4)
        | SET_PCLK (PCLK_SPI,     PDIV_4)
        | SET_PCLK (PCLK_RTC,     PDIV_4)
        | SET_PCLK (PCLK_SSP1,    PDIV_4)
        | SET_PCLK (PCLK_DAC,     PDIV_4)
        | SET_PCLK (PCLK_ADC,     PDIV_4)
        | SET_PCLK (PCLK_CAN1,    PDIV_4)
        | SET_PCLK (PCLK_CAN2,    PDIV_4)
        | SET_PCLK (PCLK_ACF,     PDIV_4)
    );

	P_SCB_REGS->PCLKSEL1 =
    (
          SET_PCLK (PCLK_BAT_RAM, PDIV_4)
        | SET_PCLK (PCLK_GPIO,    PDIV_4)
        | SET_PCLK (PCLK_PCB,     PDIV_4)
        | SET_PCLK (PCLK_I2C1,    PDIV_4)
        | SET_PCLK (PCLK_SSP0,    PDIV_4)
        | SET_PCLK (PCLK_TIMER2,  PDIV_4)
        | SET_PCLK (PCLK_TIMER3,  PDIV_4)
        | SET_PCLK (PCLK_UART2,   PDIV_1)
        | SET_PCLK (PCLK_UART3,   PDIV_1)
        | SET_PCLK (PCLK_I2C2,    PDIV_4)
        | SET_PCLK (PCLK_I2S,     PDIV_4)
        | SET_PCLK (PCLK_MCI,     PDIV_4)
        | SET_PCLK (PCLK_SYSCON,  PDIV_4)
    );
}

/*
 * NAME:
 *
 *  pinConfigurator
 *
 * DESCRIPTION:
 *
 *  setups all the pins of the LPC2378
 *
 * PARAMETERS:
 *
 *  none...
 *
 * RETURN:
 *
 *  none...
 *
 * EXAMPLE:
 *
 *   pinConfigurator();
 *
 * NOTES:
 *
 *  experimental
 *
 */

void pinConfigurator(void)
{
    INT32U n;
    INT32U i;
    INT32U pattern;

    n=0;

    while (mcuPins[n].pinSelect != 0)
    {
        pattern=0x00000000;

        for (i=0; i<16; i++)
        {
            pattern |= (mcuPins[n].pin[i].multiplex << (mcuPins[n].pin[i].position*2));
        }

        VOLATILE32(mcuPins[n].pinSelect) = pattern; /* set the complete world */
        n ++;
    }

    /*
     * NOTE:
     *
     * Complete by setting the ETM to be disabled on PINSEL10
     *
     */
    VOLATILE32(PINSEL10) = ~(BIT(3)) & PINSEL10_MASK;   /* disable ETM, mask reserved bit to 0 */
    
}

/*
 * NAME:
 *
 *  initGPIO
 *
 * DESCRIPTION:
 *
 *  sets up the GPIO pins
 *
 * PARAMETERS:
 *
 *  none...
 *
 * RETURN:
 *
 *  none...
 *
 * EXAMPLE:
 *
 *   initGPIO();
 *
 * NOTES:
 *
 *  none...
 *
 */

static void initGPIO(void)
{
    pinConfigurator();

    /*
     * Old method:
     *
     * VOLATILE32(U0_TX_PINSEL_REG) = (VOLATILE32(U0_TX_PINSEL_REG) & ~U0_TX_PINMASK ) | U0_TX_PINSEL;
     * VOLATILE32(U0_RX_PINSEL_REG) = (VOLATILE32(U0_RX_PINSEL_REG) & ~U0_RX_PINMASK ) | U0_RX_PINSEL;
     */

    /*
     * NOTE:
     *
     *  SCS controls whether the LPC2xxx is set to use the legacy registers or the new
     *  fast GPIO control registers.
     *
     */

    P_SCB_REGS->SCS |= BIT(0);  /* Fast GPIO / new registers */

    /* Set Port0 Fast GPIO direction register outputs */
//    VOLATILE32(FIO0DIR) |= ( SD_LED_BIT | USBC_LED_BIT | USB_LINK_LED_BIT ); // LPC2378STK
    FIO1DIR |= ( SD_LED_BIT | USB_UP_LED1_BIT | USB_LINK_LED_BIT ); // LPC2478STK

    /* Set Port1 Fast GPIO direction register outputs */
//    VOLATILE32(FIO1DIR) |= ( LCD_BL_BIT ); // LPC2378STK (no equivalent on LPC2478STK)

    /* Turn off MCIPWR SD LED (near bottom left corner of LCD) */
//    VOLATILE32(FIO0CLR)  = SD_LED_BIT; // LPC2378STK
    FIO1CLR  = SD_LED_BIT; // LPC2378STK

    /* Turn off USBC LED */
//    VOLATILE32(FIO0SET)  = USBC_LED_BIT; // LPC2378STK
    FIO1SET  = USB_UP_LED1_BIT; // LPC2378STK

    /* Turn off USB_LINK LED */
//    VOLATILE32(FIO0SET)  = USB_LINK_LED_BIT; // LPC2378STK
    FIO1SET  = USB_LINK_LED_BIT; // LPC2378STK
    
}

/*
 * NAME:
 *
 *  initUART0
 *
 * DESCRIPTION:
 *
 *  sets up UART0 to be 38.4 K Baud, 8 data bits, no parity, and no
 *  flow control
 *
 * PARAMETERS:
 *
 *  none...
 *
 * RETURN:
 *
 *  none...
 *
 * EXAMPLE:
 *
 *   initUART0();
 *
 * NOTES:
 *
 *  experimental
 *
 */

void initUART0(INT32U baud, INT8U mode, INT8U fmode, INT32U cclk)
{
    INT8U pclk_div;
    INT8U pclk_sel;
    INT32U uart_divisor_latch;
    INT8U udl_roundbit;
    
    /* find out UART0's pclk divider */
    pclk_sel = GET_PCLK_SEL( P_SCB_REGS->PCLKSEL0, PCLK_UART0 );
    pclk_div = ( pclk_sel == 0 ? 4 : \
    		     pclk_sel == 1 ? 1 : \
    		     pclk_sel == 2 ? 2 : \
    		     pclk_sel == 3 ? 8 : \
    		     0 ); /* this evaluation should never happen */
    if( pclk_div == 0 )
    {
    	return;
    }
    
    /* Calculate divsor latch value based on cclk and UART0's pclk divider 
     * We multiply by 2 to determine if it is odd or even
     * If it is even, then there is no round bit
     * If it is odd, then there is a round up 
     * Shift it back */
    uart_divisor_latch = ( 2 * ( (cclk/pclk_div) / ( (baud) * 16) ) );
    udl_roundbit = ( (uart_divisor_latch & 0x1) == 0 ? 0 : 1 );
    uart_divisor_latch /= 2;

    /* stop any transmissions */
    P_UART0_REGS->TER = 0;
    
    P_UART0_REGS->LCR = ULCR_DLAB_ENABLE;
    P_UART0_REGS->DLL = (uint8_t) uart_divisor_latch + udl_roundbit;
    P_UART0_REGS->DLM = (uint8_t)(uart_divisor_latch >> 8);
    P_UART0_REGS->LCR = (mode & ~ULCR_DLAB_ENABLE);

    /* Set FIFO modes and Reset */
    P_UART0_REGS->FCR = fmode | UFCR_TXFIFO_RESET | UFCR_RXFIFO_RESET;
    
    /* resume transmissions */
    P_UART0_REGS->TER = UTER_TXEN; 
}


/*
 * NAME:
 *
 *  handlerDummy
 *
 * DESCRIPTION:
 *
 *  dummy function for the exception vectors
 *
 * PARAMETERS:
 *
 *  none...
 *
 * RETURN:
 *
 *  never returns
 *
 * EXAMPLE:
 *
 *   n/a
 *
 * NOTES:
 *
 *  none..
 *
 */

void handlerDummy(void)
{
    /* forever */
    while(1) continue;
}

void App_Init(void)
{
	INT8U err;

	// Create bilateral semaphores for task1 and task2
	sem1 = OSSemCreate( 0 );
	sem2 = OSSemCreate( 0 );

	// Create mailbox message for printing task
	mb1 = OSMboxCreate ( (void*)0 );

	// Create mailbox message for display task
	mb2 = OSMboxCreate ( (void*)0 );

	// Create the event flag group
	SomeStatusFlags = OSFlagCreate(0x00, &err);

	// Create the memory partition for task printing
	msgMem = OSMemCreate(msgPart, memBlocks, blockSize, &err);
}
