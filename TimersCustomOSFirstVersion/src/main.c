/*++

Embsys 110A Spring 2014

Module Name:

    main.c

Module Description:

    This is the main progam for Programming Assignment 1.

Created on:	April 27, 2014
Author:		Shawn Quinn

--*/
#define __MAIN_C__

#include "uw.h"
#include "lpc-2478-stk.h"
#include "init.h"
#include "print.h"
#include "timer1.h"
#include "timer2.h"
#include "critical.h"
#include "threads.h"



PRINT_DEFINEBUFFER();   /* required for lightweight sprintf */

//
// These defines allow you to enable and disable various debug messages.
//
#define DEBUG	0  		// 1 = enable debug prints,  0 = disable
#define BUT1	(1<<19)	// button one bit status bit location
#define BUT2	(1<<21)	// button two status bit location

/*++

Routine Description:

    Standard program main entry point.

Arguments:

    None.

Return Value:

    Returns 0, which indicates nothing.

--*/

uint32_t entryCount;
uint32_t exitCount __attribute__((section(".noinit")));

int main( void )
{
	entryCount = getTimer2Count();
    /* Initial SCB Parameters */
    const scb2300_t SCBParams =
   /* M   N  Fcco       CCLKDIV MAMCR          MAMTIM            Optimal   CCLK  */
   { 12,  1, 288000000, 6,      MAMCR_FULL,    MAMTIM_4_CLK   /* MAMTIM=3, 48 MHz */ };

    /* NOTES:
     * M:       PLL Multiplier
     * N:       PLL Divider
     * Fcco:    Frequency (Hz) of PLL output
     * CCLKDIV: CPU Clock divider, cclk
     * MAMCR:   MAM mode, Partial is the preferred setting for Rev -,A parts
     * MAMTIM:  Let initMAM calculate the optimal MAM timing
     */

#if DEBUG /* Use the for debugging to allow enough time for the JTAG to halt the processor */
    volatile uint32_t delaycounter;
    for (delaycounter = 0; delaycounter < 200000; delaycounter++){continue;}
#endif

    /* initialize */
    initHardware((scb2300_t *)&SCBParams);

    RETAILMSG(1, ("\033[2J")); /* Clear entire screen */
    RETAILMSG(1, (
              "Programming Assignment #1: Built %s %s.\r\n\r\n",
              __DATE__,
              __TIME__));

    /* If InterruptsEnable() is implemented robust such that it only uses the
     * I and F bits from the passed in parameter, zeroing out (to enable) the
     * I and/or F bits to enable those interrupts should be all that we need
     * to do.  The other bits are ignored and are 'don't care'. */
    InterruptsEnable(~ARM_SR_IRQ_BIT);

    /* Start Timer1 which is used to set a system delay */
    startTimer1();
    char strBuf[30];
    uint32_t err, timer2Freq;
    uint32_t timer2Cnt = 0;
    globalDataStr shared =
    {
    		0,
    		0,
    		0,
    		0
    };
    threadStr queueTable[QUEUECAP];
    threadStr idleThdStr;
    createThread(&idleThdStr, 0, "idle thread", 10, READY, &idleThreadEntry);
    queueTable[0] = idleThdStr;
    threadStr thrd1Str;
    createThread(&thrd1Str, 1, "thread 1", 9, READY, &thread1Entry);
    queueTable[1] = thrd1Str;
    threadStr thrd2Str;
    createThread(&thrd2Str, 2, "thread 2", 8, READY, &thread2Entry);
    queueTable[2] = thrd2Str;
    threadStr thrd3Str;
    createThread(&thrd3Str, 3, "thread 3", 7, READY, &thread3Entry);
    queueTable[3] = thrd3Str;
    printString("\nEntering superloop in main...\r\n");
    volatile uint32_t thdIndex = 0;

    for(;;)
    {
    	if (thdIndex == 0)
    	{
    		timer2Cnt = getTimer2Count();
    		RETAILMSG(1, ("\nCalling idle thread, timer2 count = %u\r\n", timer2Cnt));
    	}
    	else
    	{
    		timer2Cnt = getTimer2Count();
    		RETAILMSG(1, ("\nCalling thread %u, timer2 count = %u\r\n", thdIndex, timer2Cnt));
    	}
    	queueTable[thdIndex].state = ACTIVE;
    	printThreadData(&queueTable[thdIndex]);
    	err = queueTable[thdIndex].thdFunc(&shared);
    	queueTable[thdIndex].state = READY;
    	printThreadData(&queueTable[thdIndex]);
    	++thdIndex;
      	if (thdIndex == QUEUECAP)
      	{
      		thdIndex = 0;
      	}
        sprintf(strBuf,"guard = %u, inc = %u, t1 = %u, t2 = %u\r\n",
        		shared.guard, shared.inc, shared.t1, shared.t2);
        printString(strBuf);
        timer2Freq = getTimer2Freq();
        RETAILMSG(1, ("\nTimer2 frequency = %u\r\n", timer2Freq));
        RETAILMSG(1, ("\nEntry count = %u\r\n", entryCount));
        RETAILMSG(1, ("\nExit count = %u\r\n", exitCount));
        RETAILMSG(1, ("\nDelta T = %u\r\n", entryCount - exitCount));

        if (!(FIO2PIN & BUT1))
        {
           	printString("Button 1 pressed ....\n\r");
          	printString("Init timer 2 ....\n\r");
          	uint32_t cclk = ((scb2300_t *)&SCBParams)->PLL_Fcco/((scb2300_t *)&SCBParams)->CCLK_Div;
            initTimer2(cclk);
          	printString("Start timer 2 ....\n\r");
           	startTimer2();
        }
        if (!(FIO2PIN & BUT2))
        {
            printString("Button 2 pressed ....\n\r");
            exitCount = getTimer2Count();
            asm("mov pc, #0x00");
        }
    }// end for

    //
    // We never get here.
    //

    RETAILMSG(1, (
              "Programming Assignment #1: Exiting.\r\n\r\n"));

    return 0;
}
