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
#define __TIMER2_C__

#include "lpc-2478-stk.h"
#include "init.h"
#include "uw.h"
#include "timer2.h"
#include "print.h"
#include "scb.h"

uint32_t timer2Freq;

/* Configure Timer2 */
void initTimer2(uint32_t cclk)
{
    uint8_t pclk_div;
    uint8_t pclk_sel;
    uint32_t fcclk;

    P_SCB_REGS->PCONP |= PCONP_PCTIM2;

    /* find out pclk divider */
    pclk_sel = GET_PCLK_SEL( P_SCB_REGS->PCLKSEL1 , PCLK_TIMER2 );
    pclk_div = ( pclk_sel == 0 ? 4 : \
                 pclk_sel == 1 ? 1 : \
                 pclk_sel == 2 ? 2 : \
                 pclk_sel == 3 ? 8 : \
                 0 ); /* this evaluation should never happen */
    if( pclk_div == 0 )
    {
        return;
    }

    /* Get the frequency of cclk */
    fcclk = getFcclk();

    timer2Freq = (fcclk/pclk_div);

    /* Program the Timer registers.*/


    P_TIMER2_REGS->TCR = 0x02;                  /* disable and reset counter */
    P_TIMER2_REGS->TCR = 0x00;					/* clear the reset bit */
    P_TIMER2_REGS->CTCR = 0x00;                 /* Timer Mode: every rising PCLK edge */
    P_TIMER2_REGS->PR = 0x00;           		/* no prescale */
    P_TIMER2_REGS->IR = 0x3F;                   /* reset any interrupt flags */
    P_TIMER2_REGS->MR0 = 0x00;          		/* no match, run continuously */
    P_TIMER2_REGS->MCR = 0x00;   				/* no interrupt, run continuously */
    P_TIMER2_REGS->CCR = 0x00;   				/* no capture */
    P_TIMER2_REGS->EMR = 0x00;   				/* no external match */

    return;
}

void startTimer2(void)
{
	/* enable timer2  */
    P_TIMER2_REGS->TCR = 0x01;    /* enable counter */
}

uint32_t getTimer2Count(void)
{
	return P_TIMER2_REGS->TC;
}

uint32_t getTimer2Freq(void)
{
	return timer2Freq;
}
