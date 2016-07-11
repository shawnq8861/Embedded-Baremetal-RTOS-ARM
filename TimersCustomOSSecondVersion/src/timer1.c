/*
 * timer1.c
 *
 *  Created on: May 4, 2014
 *      Author: Shawn Quinn
 */

#define __TIMER1_C__

#include "lpc-2478-stk.h"
#include "init.h"
#include "uw.h"
#include "timer1.h"
#include "print.h"

// configure timer1 to generate an interrupt on match
void initTimer1(uint32_t cclk)
{
    uint32_t match;
    uint8_t pclk_div;
    uint8_t pclk_sel;
    uint32_t fcclk;
    uint32_t frequency;

    // Call installVector to install ISR before enabling interrupt source
    installVector(VIC_CH5_TIMER1, &timer1IRQHandler, 0, VIC_VECT_PRIORITY_HIGHEST);

    // find out pclk divider
    pclk_sel = GET_PCLK_SEL( P_SCB_REGS->PCLKSEL0 , PCLK_TIMER1 );
    pclk_div = ( pclk_sel == 0 ? 4 : \
                 pclk_sel == 1 ? 1 : \
                 pclk_sel == 2 ? 2 : \
                 pclk_sel == 3 ? 8 : \
                 0 ); // this evaluation should never happen
    if( pclk_div == 0 )
    {
        return;
    }

    fcclk = getFcclk();				// get main clock frequency

    frequency = fcclk/pclk_div;		// calculate peripheral clock frequency

    match = frequency/TMR_FREQ;		// calculate the match value

    // Program the Timer registers

    P_TIMER1_REGS->TCR = 0x02;                  // disable and reset counter
    P_TIMER1_REGS->CTCR = 0x00;                 // Timer Mode: every rising PCLK edge
    P_TIMER1_REGS->PR = 0x00;           		// no prescale
    P_TIMER1_REGS->IR = 0x3F;                   // reset any interrupt flags
    P_TIMER1_REGS->MR0 = match;          		// match value
    P_TIMER1_REGS->MCR = MCR_MR0I | MCR_MR0R;   // interrupt on MR0 and reset on MR0, TC will reset

    return;
}

void startTimer1(void)
{
    P_TIMER1_REGS->TCR = 0x01;    // enable timer1, enable counter
}
