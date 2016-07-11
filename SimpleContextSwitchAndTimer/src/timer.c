
#include "lpc2478.h"
#include "bsp.h"
#include "print.h"

#define TICKS_PER_SEC 5

void switchContext(void);
void Tmr_TickISR_Handler (void);


void initialize_timer_tick(void)
{
    int  pclk_freq;
    int  rld_cnts;
                                                                             /* VIC timer #0 Initialization                     */
    WRITEREG32(VICINTSELECT, READREG32(VICINTSELECT) & ~(1 << VIC_TIMER0));  /* Configure the timer interrupt as an IRQ source  */

    WRITEREG32(VICVECTADDR4, (INT32U)Tmr_TickISR_Handler);                   /* Set the vector address                          */
    WRITEREG32(VICINTENABLE,  (1 << VIC_TIMER0));                            /* Enable the timer interrupt source               */

    pclk_freq     =   BSP_CPU_PclkFreq(PCLKINDX_TIMER0);        /* Get the peripheral clock frequency                       */
    rld_cnts      =   pclk_freq / TICKS_PER_SEC;                /* Calculate the # of counts necessary for the OS ticker    */

    WRITEREG32(T0TCR, (1 << 1));                                /* Disable and reset counter 0 and the prescale counter 0   */
    WRITEREG32(T0TCR, 0);                                       /* Clear the reset bit                                      */
    WRITEREG32(T0PC,  0);                                       /* Prescaler is set to no division                          */

    WRITEREG32(T0MR0, rld_cnts);
    WRITEREG32(T0MCR, 3);                                       /* Interrupt on MR0 (reset TC), stop TC                     */

    WRITEREG32(T0CCR, 0);                                       /* Capture is disabled.                                     */
    WRITEREG32(T0EMR, 0);                                       /* No external match output.                                */
    WRITEREG32(T0TCR, 1);                                       /* Enable timer 0                                           */
}

void Tmr_TickISR_Handler(void)
{
    WRITEREG32(T0IR, 0xFF);                                     /* Clear timer #0 interrupt                                 */
    /* Could call an C function to handle the IRQ from here. */
}

