/*++

Embsys 110A Spring 2014

Module Name:

    main.c

Module Description:

    This is the main program for Programming Assignment 2.

Created on:	May 4, 2014
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
#include "osServices.h"
//#include "printf.h"

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

uint32_t rVal;

int main( void )
{
	// Initial SCB Parameters
	const scb2300_t SCBParams =
	{ 12,  1, 288000000, 6, MAMCR_FULL, MAMTIM_4_CLK };	// MAMTIM=3, 48 MHz
    // M   N  Fcco   CCLKDIV MAMCR          MAMTIM         Optimal   CCLK

    // Initialize main hardware components
    initHardware((scb2300_t *)&SCBParams);

    RETAILMSG(1, ("\033[2J")); /* Clear entire screen */
    RETAILMSG(1, (
              "Programming Assignment #2: Built %s %s.\r\n\r\n",
              __DATE__, __TIME__));

    // Print out the current processor mode
    asm("MRS %0, cpsr\n" : "=r" (rVal));	// get cpsr
    rVal &= 0x001F;							// mask out all but last byte
    printStringHex("Main Mode = ", rVal);

    //init_printf(NULL, PUTC);

    //printf("Test value %d\r\n", 5);

    // Enable interrupts without changing cpsr settings
    InterruptsEnable(~ARM_SR_IRQ_BIT);

    // Initialize the application threads
    initThreads();

     // Install the initialized threads into the queue array
    fillQueue();

    // Start Timer2 which is used for system delays and time measurements
    startTimer2();

    uint32_t mainLoopCount = 0;

    printString("\nEntering superloop in main...\r\n");

    // Start os services:  initial thread, tick timer, scheduler and context switch
    startOS();

    for(;;)
    {
    	RETAILMSG(1, ("\nMain Loop Count = %u\r\n", mainLoopCount));

    	++mainLoopCount;

    	msTimeDelay(50);

    }// end for

    //
    // We never get here.
    //

    RETAILMSG(1, ("Programming Assignment #2: Exiting.\r\n\r\n"));

    return 0;
}
