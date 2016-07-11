/*
 * osServices.c
 *
 * Module Description:
 *
 * OS service routines and utility functions
 *
 *  Created on: May 10, 2014
 *      Author: Shawn Quinn
 */

#include "threads.h"
#include "osServices.h"
#include "timer1.h"
#include "timer2.h"

volatile uint32_t tickCount = 0;
volatile uint32_t thdIndex;
uint32_t thdCount = 0;
uint32_t msecCount = 12000;
uint32_t timer2EntryCt;
extern globalDataStr shared;

void timeDelay(uint32_t sec)
{
	uint32_t i, pause;
	for (i = 0; i < sec; ++i)
	{
		pause = tickCount + 5;
		while (tickCount < pause)
		{
			continue;
		}
	}
}

void msTimeDelay(uint32_t msec)
{
	uint32_t delay, i;
	for ( i = 0; i < msec; ++i)
	{
		delay = msecCount + getTimer2Count();
		while(getTimer2Count() < delay)
		{
			continue;
		}
	}
}

void fillQueue(void)
{
	queueTable[0] = idleTCB;
    queueTable[1] = thread1TCB;
    queueTable[2] = thread2TCB;
    queueTable[3] = thread3TCB;

    return;
}

void scheduler(uint32_t stkPtr)
{
	++tickCount;	// increment the system tick count
	*(queueTable[thdIndex].threadStkPtr) = stkPtr;	// save previous thread stack pointer
	++thdIndex;		// point to the next thread to run
	if (thdIndex == thdCount)	// if end of queue, back to start
	{
		thdIndex = 0;
	}
	currStkPtr = *(queueTable[thdIndex].threadStkPtr);	// get next thread stack pointer

	// Clear interrupt condition in peripheral
	P_TIMER1_REGS->IR = 0xFF;   // reset any timer1 interrupt flags
	// Acknowledge the VIC
	P_VIC_REGS->Address = 0;    // write anything
}

void startOS(void)
{
	thdIndex = 0;			// set to first thread to run
	currStkPtr = *(queueTable[thdIndex].threadStkPtr);	// set current stk ptr
	startTimer1();			// start the tick timer
	startFirstThread();		// switch to user mode and start first thread
}

void abortPrint(unsigned int type, unsigned int address)
{
	if (type == 0) {
		printString("Data Abort at address: 0x");
	} else {
		printString("Prefetch Abort at address: 0x");
	}
	printHex(address);
	printString("\n\r");
}
