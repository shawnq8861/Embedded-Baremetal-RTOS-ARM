/*++
Copyright (c) 2012-2013  University of Washington Extensions.  All rights reserved.

Module Name:

    timer.c

Module Description:

    This is the solution for Programming Assignment #5.
    It contains the support necessary to use timer 1 interrupts on the LPC2478.

Author:


Revision History:

--*/
#define __TIMER1_C__

#include "lpc-2478-stk.h"
#include "init.h"
#include "uw.h"
#include "timer1.h"
#include "print.h"

#define DEBUG_TIMER1_ISR 1

extern volatile int tickCount;

void
/***** Use GCC method to make this an ISR instead of a standard function *****/
__attribute__ ((interrupt("IRQ")))
timer1ISR(void)
{
    ++tickCount;

#if DEBUG_TIMER1_ISR
    /* read the IR flags */
    uint8_t IR = P_TIMER1_REGS->IR;

    /* check for bogus flags */
    IR &= ~0x01; /* all except for MR0 */
    if( IR )
    {
        while(1){continue;} /* infinite debugging loop */
    }
#endif

    /* Clear interrupt condition in peripheral */
    P_TIMER1_REGS->IR = 0xFF;   /* reset any timer1 interrupt flags */

    /* Acknowledge the VIC */
    P_VIC_REGS->Address = 0;    /* write anything */

    return;
}


/* Simple define used for match value */
#define PR_MATCH (2)
#define TMR_FREQ (100)

/* Configure Timer1 to generate an interrupt 100 times a second */
void initTimer1(uint32_t cclk)
{
    uint32_t prescale;
    uint8_t pclk_div;
    uint8_t pclk_sel;
    uint32_t fcclk;
    uint32_t frequency;

    /* Call installVector to install ISR before enabling interrupt source. */
    installVector(VIC_CH5_TIMER1, &timer1ISR, 0, VIC_VECT_PRIORITY_HIGHEST);

    /* find out pclk divider */
    pclk_sel = GET_PCLK_SEL( P_SCB_REGS->PCLKSEL0 , PCLK_TIMER1 );
    pclk_div = ( pclk_sel == 0 ? 4 : \
                 pclk_sel == 1 ? 1 : \
                 pclk_sel == 2 ? 2 : \
                 pclk_sel == 3 ? 8 : \
                 0 ); /* this evaluation should never happen */
    if( pclk_div == 0 )
    {
        return;
    }

    /* Determine prescale amount */
    /* Get the frequency of cclk */
    fcclk = getFcclk();

    /* Determine prescale amount for desired timer frequency */
    /* Get Timer1's Prescale Register */
    prescale = (fcclk / TMR_FREQ / PR_MATCH);
    if( prescale == 0 )
    {
        return;
    }

    frequency = (fcclk/pclk_div/prescale);
    RETAILMSG(1, ("Timer 1 Frequency: %lu (calculated)\n\r", frequency));

    /* Program the Timer registers.
     * make sure we are not running at half the speed due to the way the
     * counters increment and match */
    /* 1. Disable and reset counter */
    /* 2. Timer Mode: every rising PCLK edge */
    /* 3. Prescale down on the front end to save a little power (prescale - 1) */
    /* 4. Reset any interrupt flags */
    /* 5. When TC is match value (match - 1), the value programmed to this register must be greater than zero */
    /* 6. Interrupt on MR0, Reset on MR0 */
    P_TIMER1_REGS->TCR = 0x02;                  /* disable and reset counter */
    P_TIMER1_REGS->CTCR = 0x00;                 /* Timer Mode: every rising PCLK edge */
    P_TIMER1_REGS->PR = prescale - 1;           /* prescale down on the front end to save a little power */
    P_TIMER1_REGS->IR = 0x3F;                   /* reset any interrupt flags */
    P_TIMER1_REGS->MR0 = PR_MATCH - 1;          /* match on TC = 1 */
    P_TIMER1_REGS->MCR = MCR_MR0I | MCR_MR0R;   /* interrupt on MR0 and reset on MR0; TC will reset */

    return;
}


void startTimer1(void)
{
    /* enable timer1  */
    P_TIMER1_REGS->TCR = 0x01;    /* enable counter */
}
