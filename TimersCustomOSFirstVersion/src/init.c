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
 *  Olimex LPC-2478-STK
 *
 * HISTORY
 *
 * NOTES
 *
 */

#include <stdint.h>
#include "print.h"
#include "lpc-2478-stk.h"
#include "init.h"
#include "timer1.h"
#include "timer2.h"


/* local functions */
static void initPLL(scb2300_t * pSCBParams);
static void initPCLK(void);
static void initGPIO(void);
static void initMAM(uint32_t cclk, uint8_t mamcr, uint8_t mamtim_override);
static void initVIC(void);

/*
 * DESCRIPTION:
 *
 *  initializes all the hardware components.
 */
void initHardware(scb2300_t * pSCBParams)
{
    uint32_t cclk = pSCBParams->PLL_Fcco/pSCBParams->CCLK_Div;
    /*
     * initialize main hardware components
     */
    /* Must turn off MAM before increasing frequency */
    initMAM(cclk, MAMCR_OFF, MAMTIM_7_CLK);

    /* Disable SDRAM before changing frequency (all data in SDRAM will be lost */
//    disableSDRAM();

    initPLL(pSCBParams);
    initMAM(cclk, pSCBParams->MAMMode, pSCBParams->MAMTim);
    initVIC();
    initPCLK();
    initGPIO();
//    initSDRAM(cclk);

    /* initialize specific hardware components for UART0 */
//    initUART0(38400, UART_8N1, UART_FIFO_OFF, cclk);
    initUART0(38400, UART_8N1, UFCR_FIFO_ENABLE, cclk);

    /* initialize timer1 */
    initTimer1(cclk);

    /* MEMMAP Choices are:
    BOOTLOADERMODE      0x00
    USERFLASHMODE       0x01
    USERRAMMODE         0x02
    EXTERNALMEMORYMODE  0x03
    */
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
 *  Taken from the LPC2478 User Manual:
 *
 *   5.14 PLL setup sequence
 *
 *   The following sequence must be followed step by step in order to
 *   have the PLL initialized and running:
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
    uint32_t pllcfg;

    /* Validate the incoming parameters based on supported values for the Main OSC */
    if ( pSCBParams->PLL_M_Mul < 6 ||
         pSCBParams->PLL_M_Mul > 512 ||
         pSCBParams->PLL_N_Div < 1 ||
         pSCBParams->PLL_N_Div > 32 ||
         pSCBParams->PLL_Fcco < 275000000 ||
         pSCBParams->PLL_Fcco > 550000000 ||
         pSCBParams->CCLK_Div == 0
        )
    {
        /* ASSERT invalid value: M, N, Fcco, CCLK_Div */
        RETAILMSG(1, ("ASSERT invalid value: M, N, Fcco, CCLK_Div\n\r"));
        return;
    }

    /* Validate the M and N matches the provided Fcco */
    if ( pSCBParams->PLL_Fcco != ((2 * pSCBParams->PLL_M_Mul * FOSC_MAIN)/pSCBParams->PLL_N_Div) )
    {
        /* ASSERT, invalid M and N or Fcco combinations */
        RETAILMSG(1, ("ASSERT, invalid M and N or Fcco combinations\n\r"));
        return;
    }

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
    if( FOSC_MAIN > 20000000 )
    {
        P_SCB_REGS->SCS |= SCS_OSCRANGE;
    }
    else
    {
        P_SCB_REGS->SCS &= ~SCS_OSCRANGE;
    }
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
     * TODO extra credit: Add timeout for slow FREF */
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

static void initMAM(uint32_t cclk, uint8_t mamcr, uint8_t mamtim_override)
{
    /* disable MAM */
    P_SCB_REGS->MAMCR = MAMCR_OFF;

    /* Either set according to optimally calculated value or override parameter */
    if(mamtim_override == MAMTIM_AUTOCFG)
    {
        P_SCB_REGS->MAMTIM  = (((cclk)+19999999)/20000000); /* stable setting */
    }
    else if( (mamtim_override > MAMTIM_AUTOCFG) && (mamtim_override <= MAMTIM_MAX_CLK) )
    {
        P_SCB_REGS->MAMTIM  = mamtim_override;
    }
    else
    {
        /* ASSERT invalid value
         *  setting to reset value for now */
        P_SCB_REGS->MAMTIM  = MAMTIM_MAX_CLK;
    }

    P_SCB_REGS->MAMCR   = mamcr;
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


uint32_t getFcclk( void )
{
    uint32_t Fosc;
    uint32_t Fpllclk;
    uint32_t Fcclk;
    uint8_t  clksrcsel;
    uint32_t pllstat;
    uint16_t M_mul;
    uint8_t  N_div;
    uint8_t  plle;
    uint8_t  pllc;

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
        | SET_PCLK (PCLK_TIMER1,  PDIV_1)
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


static void initGPIO(void)
{
    /* PORT0 */
    P_PINCON_REGS->SEL0 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P0.0  */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P0.1  */
        | PINSEL_MASK( PINSEL_ALT_01 , 2 )  /* P0.2 TXD0 - UART0 */
        | PINSEL_MASK( PINSEL_ALT_01 , 3 )  /* P0.3 RXD0 - UART0 */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P0.4  */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P0.5  */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P0.6  */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P0.7  */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P0.8  */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P0.9  */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P0.10 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P0.11 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P0.12 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P0.13 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P0.14 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P0.15 */
    );
    P_PINCON_REGS->SEL1 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P0.16 */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P0.17 */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P0.18 */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P0.19 */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P0.20 */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P0.21 */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P0.22 */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P0.23 */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P0.24 */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P0.25 */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P0.26 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P0.27 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P0.28 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P0.29 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P0.30 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P0.31 */
    );

    /* PORT1 */
    P_PINCON_REGS->SEL2 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P1.0  */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P1.1  */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P1.2  */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P1.3  */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P1.4  */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P1.5  */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P1.6  */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P1.7  */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P1.8  */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P1.9  */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P1.10 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P1.11 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P1.12 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P1.13 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P1.14 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P1.15 */
    );
    P_PINCON_REGS->SEL3 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P1.16 */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P1.17 */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P1.18 */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P1.19 */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P1.20 */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P1.21 */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P1.22 */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P1.23 */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P1.24 */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P1.25 */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P1.26 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P1.27 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P1.28 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P1.29 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P1.30 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P1.31 */
    );

    /* PORT2 */
    P_PINCON_REGS->SEL4 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P2.0  */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P2.1  */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P2.2  */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P2.3  */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P2.4  */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P2.5  */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P2.6  */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P2.7  */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P2.8  */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P2.9  */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P2.10 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P2.11 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P2.12 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P2.13 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P2.14 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P2.15 */
    );
    P_PINCON_REGS->SEL5 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P2.16 */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P2.17 */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P2.18 */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P2.19 */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P2.20 */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P2.21 */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P2.22 */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P2.23 */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P2.24 */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P2.25 */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P2.26 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P2.27 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P2.28 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P2.29 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P2.30 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P2.31 */
    );

    /* PORT3 */
    P_PINCON_REGS->SEL6 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P3.0  */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P3.1  */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P3.2  */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P3.3  */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P3.4  */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P3.5  */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P3.6  */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P3.7  */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P3.8  */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P3.9  */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P3.10 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P3.11 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P3.12 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P3.13 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P3.14 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P3.15 */
    );
    P_PINCON_REGS->SEL7 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P3.16 */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P3.17 */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P3.18 */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P3.19 */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P3.20 */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P3.21 */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P3.22 */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P3.23 */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P3.24 */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P3.25 */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P3.26 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P3.27 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P3.28 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P3.29 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P3.30 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P3.31 */
    );

    /* PORT4 */
    P_PINCON_REGS->SEL8 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P4.0  */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P4.1  */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P4.2  */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P4.3  */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P4.4  */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P4.5  */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P4.6  */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P4.7  */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P4.8  */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P4.9  */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P4.10 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P4.11 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P4.12 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P4.13 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P4.14 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P4.15 */
    );
    P_PINCON_REGS->SEL9 =
    (
          PINSEL_MASK( PINSEL_PRIMARY, 0 )  /* P4.16 */
        | PINSEL_MASK( PINSEL_PRIMARY, 1 )  /* P4.17 */
        | PINSEL_MASK( PINSEL_PRIMARY, 2 )  /* P4.18 */
        | PINSEL_MASK( PINSEL_PRIMARY, 3 )  /* P4.19 */
        | PINSEL_MASK( PINSEL_PRIMARY, 4 )  /* P4.20 */
        | PINSEL_MASK( PINSEL_PRIMARY, 5 )  /* P4.21 */
        | PINSEL_MASK( PINSEL_PRIMARY, 6 )  /* P4.22 */
        | PINSEL_MASK( PINSEL_PRIMARY, 7 )  /* P4.23 */
        | PINSEL_MASK( PINSEL_PRIMARY, 8 )  /* P4.24 */
        | PINSEL_MASK( PINSEL_PRIMARY, 9 )  /* P4.25 */
        | PINSEL_MASK( PINSEL_PRIMARY,10 )  /* P4.26 */
        | PINSEL_MASK( PINSEL_PRIMARY,11 )  /* P4.27 */
        | PINSEL_MASK( PINSEL_PRIMARY,12 )  /* P4.28 */
        | PINSEL_MASK( PINSEL_PRIMARY,13 )  /* P4.29 */
        | PINSEL_MASK( PINSEL_PRIMARY,14 )  /* P4.30 */
        | PINSEL_MASK( PINSEL_PRIMARY,15 )  /* P4.31 */
    );

    P_PINCON_REGS->SEL10 = ~(BIT(3)) & PINSEL10_MASK;   /* disable ETM, mask reserved bit to 0 */

    /*
     * NOTE:
     *
     *  SCS controls whether the LPC2478 is set to use the legacy registers or the new
     *  fast GPIO control registers.
     *
     */

    P_SCB_REGS->SCS |= BIT(0);  /* Fast GPIO / new registers */

    /* Set Port1 Fast GPIO direction register outputs */
    P_FIO1_REGS->DIR |= ( SD_LED_BIT | USB_UP_LED1_BIT | USB_UP_LED2_BIT );

    /* Turn off MCIPWR SD LED (near bottom left corner of LCD) */
    P_FIO1_REGS->CLR = SD_LED_BIT;
    /* Turn off USB_D_LINK LED */
    P_FIO1_REGS->SET = USB_UP_LED1_BIT;
    /* Turn off USB_H_LINK LED */
    P_FIO1_REGS->SET = USB_UP_LED2_BIT;
}

/*
 * TODO extra credit: combine into one initUART function that takes a struct type
 * containing configurable UART parameters
 */

void initUART0(uint32_t baud, uint8_t mode, uint8_t fmode, uint32_t cclk)
{
    uint8_t pclk_div;
    uint8_t pclk_sel;
    uint32_t uart_divisor_latch;
    uint8_t udl_roundbit;

    /* Make sure the power is turned on for the UART */
    P_SCB_REGS->PCONP = ((P_SCB_REGS->PCONP & PCONP_MASK) | PCONP_PCUART0);

    /* find out UART0's pclk divider */
    pclk_sel = GET_PCLK_SEL( P_SCB_REGS->PCLKSEL0, PCLK_UART0 );
    pclk_div = ( pclk_sel == 0 ? 4 : \
                 pclk_sel == 1 ? 1 : \
                 pclk_sel == 2 ? 2 : \
                 pclk_sel == 3 ? 8 : \
                 0 ); /* this evaluation should never happen */
    if( pclk_div == 0 )
    {
        // Can't really do print out the UART if it is not initialized!
    	// RETAILMSG(1, ("ASSERT: Invalid PCLK_SEL in UART\n\r"));
        return;
    }

    /* Calculate divisor latch value based on cclk and UART0's pclk divider
     * uart_divisor_latch = cclk/(16 * pclk_div * baud)
     * We effectively multiply by 2 to determine if it is odd or even
     * If it is even, then there is no round bit
     * If it is odd, then there is a round up
     * Shift it back */
    uart_divisor_latch = cclk/(pclk_div * baud * 8);
    udl_roundbit = ( (uart_divisor_latch & 0x1) == 0 ? 0 : 1 );
    uart_divisor_latch /= 2;
    /* TODO extra credit: use fractional dividers */


    /* Complete current transmission but stop any further transmissions */
    P_UART0_REGS->TER = 0;

    P_UART0_REGS->LCR = ULCR_DLAB_ENABLE;
    P_UART0_REGS->DLL = (uint8_t) uart_divisor_latch + udl_roundbit;
    P_UART0_REGS->DLM = (uint8_t)(uart_divisor_latch >> 8);
    P_UART0_REGS->LCR = (mode & ~ULCR_DLAB_ENABLE);

    /* Set FIFO modes and clear TX and RX FIFOs */
    P_UART0_REGS->FCR = fmode | UFCR_TXFIFO_RESET | UFCR_RXFIFO_RESET;

    /* Select UART pins and pin modes in registers PINSELn and PINMODEn */
    P_PINCON_REGS->MODE0 &=
    (
          PINSEL_CLR_MASK(  2 )  /* P0.2 TXD0 */
        & PINSEL_CLR_MASK(  3 )  /* P0.3 RXD0  */
    );
    P_PINCON_REGS->MODE0 |=
    (
          PINSEL_MASK( PINMODE_PULL_NONE , 2 )  /* P0.2 TXD0    */
        | PINSEL_MASK( PINMODE_PULL_NONE , 3 )  /* P0.3 RXD0    */
    );

    /* Make sure UART interrupts are disabled */
    /***** TODO ADD CODE HERE *****/

    /* resume transmissions */
    P_UART0_REGS->TER = UTER_TXEN;
}



/* initVIC is used to
 * 1. initialize the VIC to a known state by writing all registers with their
 *    reset values
 * 2. configures system-wide
 * This is useful if only a soft-reset occurred that does not
 * perform a full reset of the hardware
 */
static void initVIC(void)
{
    uint32_t i;

    /* Clear any leftover pending software generated interrupts */
    P_VIC_REGS->SoftIntClear = 0xFFFFFFFF;

    /* Clear all interrupt enable bits, mask all interrupt sources */
    P_VIC_REGS->IntEnClear = 0xFFFFFFFF;

    /* Set all interrupt sources to map to IRQ */
    P_VIC_REGS->IntSelect = 0x00000000;

    /* Initialize all VectAddr0..31 registers to reset vector */
    for(i = 0; i < NUM_VIC_VECT_ADDR_REGS; i++)
    {
        P_VIC_REGS->VectAddr[i] = 0;
    }

    /* Initialize all VectPriority0..31 registers to reset value */
    for(i = 0; i < (NUM_VIC_VECT_PRIORITY_REGS - 16); i++)
    {
        P_VIC_REGS->VectPriority[i] = VIC_VECT_PRIORITY_LOWEST;
    }

    /* Reset the Software Priority Mask */
    P_VIC_REGS->SWPriorityMask = 0xFFFF;

    /* Reset the VIC priority logic state machine */
    P_VIC_REGS->Address = 0;

    /* Configure so VIC registers can be accessed in User mode */
    P_VIC_REGS->Protection = VIC_PROTECTION_USER_OR_PRIVILEGED_MODE;

    return;
}


/* installVector() is used to install ISRs into the VIC.
 * Uses:
 * 1. a feature of the system gets installed dynamically
 * or an application that uses interrupts is loaded at run-time.  This
 * is when you would need to call installVectors at run-time.
 * 2. It can also be called to statically install vectors - those that
 * are known at compile time.
 */
void installVector(
        uint32_t vectorNumber,
        pfunction_t interruptServiceRoutine,
        arminterrupt_t intSelect,
        uint32_t priority)
{
    /* Enable Interrupt Channel */
    P_VIC_REGS->IntEnable |= (1 << vectorNumber);

    /* Choose bits FIQ=1 or IRQ=0 */
    if( intSelect == IntSelectIRQ )
    {
        P_VIC_REGS->IntSelect &= ~(1 << vectorNumber);
    }
    else if( intSelect == IntSelectFIQ )
    {
        P_VIC_REGS->IntSelect |= (1 << vectorNumber);
    }

    /* Install address of ISR into VICVectAddr# slot */
    P_VIC_REGS->VectAddr[vectorNumber] = (pfunction_t) interruptServiceRoutine;

    /* Set Vector Priorities */
    P_VIC_REGS->VectPriority[vectorNumber] = priority;


    return;
}

/* This macro turns periods in CCLKs */
#define P2C(sdram_period_ns,emc_period_ps)      ((( (sdram_period_ns*1000) < emc_period_ps)? \
                                        0:(uint32_t)((sdram_period_ns*1000)/emc_period_ps))+1)

#define SDRAM_TRRD          15      // Row active to row active delay (min)
#define SDRAM_TRCD          20      //  RAS# to CAS# delay (min)
#define SDRAM_TRP           20      // Row Precharge time (min)
#define SDRAM_TRAS          45      // Row active time (max)
#define SDRAM_TRAS_MAX      100000  //  Row active time (max)
#define SDRAM_TRC           65      // Row cycle time (min)
#define SDRAM_TRFC          65      // tRC=tRFC (min)
#define SDRAM_TRDL_CLK      2       //  Last data in to row precharge (min)
#define SDRAM_TWR_CLK       2       // tRDL=tWR (min)
#define SDRAM_TDAL_CLK      2       // Last data in to Active delay (min)
#define SDRAM_TCDL_CLK      1       //  Last data in to new col address delay (min)
#define SDRAM_TBDL_CLK      1       //  Last data in to burst stop (min)
#define SDRAM_TCCD_CLK      1       //  Col address to col address delay (min)

#define SDRAM_REFRESH       7813
#define SDRAM_TAPR_CLK      1       // Last data out to active command time
#define SDRAM_TXSR          67      // tSREX=tSXR Self-refresh exit time
#define SDRAM_TMRD_CLK      3       // Load mode register to active command time

/* dummy function for the exception vectors
 * Can be used for initial debugging */
void handlerDummy(void)
{
    /* forever */
    while(1) continue;
}
