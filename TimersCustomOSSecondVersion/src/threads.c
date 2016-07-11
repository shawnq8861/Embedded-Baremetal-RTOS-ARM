/*
 * threads.c
 *
 * Module Description:
 *
 * Thread data structures and functions
 *
 *  Created on: April 26, 2014
 *      Author: Shawn Quinn
 */

#include "threads.h"
#include "osServices.h"

extern volatile uint32_t tickCount;
volatile uint32_t timer2EntryCt;
volatile uint32_t timer2ExitCt;

globalDataStr shared =
{
   	0,
   	0,
   	0,
   	0
};

uint32_t flashLED = 0;

//
// hello_world with timer reset
//
void hello_world(void)
{
	++tickCount;	// increment the system tick count
	// Clear interrupt condition in peripheral
	P_TIMER1_REGS->IR = 0xFF;   // reset any timer1 interrupt flags
	// Acknowledge the VIC
	P_VIC_REGS->Address = 0;    // write anything
	printString("Hello world!\r\n");
}

// Idle thread definition
void idleThreadEntry(void* p)
{
	//uint32_t rVal;
	uint32_t overHead = 0;
	printString("\r\n");
	for(;;)
	{
		++flashLED;
		// high speed
		//if ( flashLED > 500000)	// 500000 @ 500 ticks/sec
		// low speed
		if ( flashLED > 5)	// 5 @ 5 ticks/sec and 50 msec delay
		{
			flashLED = 0;
			if( P_FIO1_REGS->PIN & SD_LED_BIT )
			{
				P_FIO1_REGS->CLR = SD_LED_BIT;	// Turn off SD LED
			}
			else
			{
				P_FIO1_REGS->SET = SD_LED_BIT;	// Turn on SD LED
			}
		}
		overHead = timer2ExitCt - timer2EntryCt;

		// low speed
		RETAILMSG(1, ("Idle thd, Ent = %u, Ext = %u, Diff = %u\r\n",
				timer2EntryCt, timer2ExitCt, overHead));

/*
		asm("MRS %0, cpsr\n" : "=r" (rVal));	// get cpsr
		rVal &= 0x001F;							// mask out all but last byte
		printStringHex("Idle Thread Mode = ", rVal);	//print out
*/
/*
		printString("Idle Stack Top = ");
		print_uint32((uint32_t)idleTCB.stackTop);
		printString("\r\n");
		getStackPtr(&rVal);
		printString("Idle Stack Ptr = ");
		print_uint32(rVal);
		printString("\r\n");
		printString("Idle Stack Bottom = ");
		print_uint32((uint32_t)idleTCB.stackBottom);
		printString("\r\n");
*/
		msTimeDelay(25);	// low speed
	}
}

// Thread 1 definition, "producer"
void thread1Entry(void* p)
{
	//uint32_t rVal;
	globalDataStr* s = (globalDataStr* )p;
	for (;;)
	{
		(*s).t1++;
		if ((*s).guard == 0)
		{
			(*s).guard = 1;
			(*s).inc++;
			(*s).guard = 0;
		}
		// high speed
		//printString("T1\r\n");

		// low speed
		RETAILMSG(1, ("Thread 1, guard = %u, inc = %u, t1 = %u, t2 = %u\r\n",
								shared.guard, shared.inc, shared.t1, shared.t2));

/*
		asm("MRS %0, cpsr\n" : "=r" (rVal));	// get cpsr
		rVal &= 0x001F;							// mask out all but last byte
		printStringHex("Thread 1 Mode = ", rVal);	//print out
*/
/*
		printString("Thd 1 Stack Top = ");
		print_uint32((uint32_t)thread1TCB.stackTop);
		printString("\r\n");
		getStackPtr(&rVal);
		printString("Thd 1 Stack Ptr = ");
		print_uint32(rVal);
		printString("\r\n");
		printString("Thd 1 Stack Bottom = ");
		print_uint32((uint32_t)thread1TCB.stackBottom);
		printString("\r\n");
*/
		msTimeDelay(25);	// low speed
	}
}

// Thread 2 definition, "consumer"
void thread2Entry(void* p)
{
	//uint32_t rVal;
	globalDataStr* s = (globalDataStr* )p;
	for (;;)
	{
		(*s).t2++;
		if ((*s).guard == 0)
		{
			(*s).guard = 1;
			(*s).inc--;
			(*s).guard = 0;
		}
		// high speed
		//printString("T2\r\n");

		// low speed
		RETAILMSG(1, ("Thread 2, guard = %u, inc = %u, t1 = %u, t2 = %u\r\n",
								shared.guard, shared.inc, shared.t1, shared.t2));

/*
		asm("MRS %0, cpsr\n" : "=r" (rVal));	// get cpsr
		rVal &= 0x001F;							// mask out all but last byte
		printStringHex("Thread 2 Mode = ", rVal);	//print out
*/
/*
		printString("Thd 2 Stack Top = ");
		print_uint32((uint32_t)thread2TCB.stackTop);
		printString("\r\n");
		getStackPtr(&rVal);
		printString("Thd 2 Stack Ptr = ");
		print_uint32(rVal);
		printString("\r\n");
		printString("Thd 2 Stack Bottom = ");
		print_uint32((uint32_t)thread2TCB.stackBottom);
		printString("\r\n");
*/
		msTimeDelay(25);	// low speed
	}
}

// Thread 3 definition, "monitor"
void thread3Entry(void* p)
{
	//uint32_t rVal;
	globalDataStr* s = (globalDataStr* )p;
	for (;;)
	{
		if ((*s).guard == 0)
		{
			(*s).guard = 1;
			if ((*s).inc > 0)
			{
				// low speed
				printString("Error, inc > 0...\r\n");
			}
			(*s).guard = 0;
		}
		// high speed
		//printString("T3\r\n");

		// low speed
		RETAILMSG(1, ("Thread 3, guard = %u, inc = %u, t1 = %u, t2 = %u\r\n",
							shared.guard, shared.inc, shared.t1, shared.t2));

/*
		asm("MRS %0, cpsr\n" : "=r" (rVal));	// get cpsr
		rVal &= 0x001F;							// mask out all but last byte
		printStringHex("Thread 3 Mode = ", rVal);	//print out
*/
/*
		printString("Thd 3 Stack Top = ");
		print_uint32((uint32_t)thread3TCB.stackTop);
		printString("\r\n");
		getStackPtr(&rVal);
		printString("Thd 3 Stack Ptr = ");
		print_uint32(rVal);
		printString("\r\n");
		printString("Thd 3 Stack Bottom = ");
		print_uint32((uint32_t)thread3TCB.stackBottom);
		printString("\r\n");
*/
		msTimeDelay(25);	// low speed
	}
}

// Initialize thread data structure field
void createThread(void* p, uint32_t id, char* chName, uint32_t prio, uint32_t st, void (*fnc)(void*))
{
	extern uint32_t thdCount;
	threadStr* thd = (threadStr* )p;
	(*thd).uId = id;
	uint32_t i;
	for (i = 0; *chName != '\0'; ++chName)
	{
		(*thd).name[i] = *chName;
		++i;
	}
	(*thd).name[i] = '\0';
	(*thd).priority = prio;
	(*thd).state = st;
	(*thd).thdFunc = fnc;
	++thdCount;
}

// Print thread data structure field
void printThreadData(void* p)
{
	threadStr* thd = (threadStr* )p;
	RETAILMSG(1, ("UID = %u, name = %s, priority = %u",
			(*thd).uId, (*thd).name, (*thd).priority));
	switch((*thd).state)
	{
		case READY:
			printString(", state = Ready\r\n");
			break;
		case ACTIVE:
			printString(", state = Active\r\n");
			break;
		case BLOCKED:
			printString(", state = Blocked\r\n");
			break;
		default:
			break;
	}
}

// Initialize the stack before first use, return stack pointer for the TCB
// argument to be passed to thread is preloaded in R0
uint32_t initStack(uint32_t* stack, void* threadAddress, void* pData)
{
	// Calculate the top of the stack.
	uint32_t *stkptr = (uint32_t*)(stack + STACKSIZE - 1);

	*(stkptr)   = (uint32_t)threadAddress;   // PC
	*(--stkptr) = (uint32_t)0x0e0e0e0e;     // R14 - LR
	*(--stkptr) = (uint32_t)0x0c0c0c0c;     // R12
	*(--stkptr) = (uint32_t)0x0b0b0b0b;     // R11
	*(--stkptr) = (uint32_t)0x0a0a0a0a;     // R10
	*(--stkptr) = (uint32_t)0x09090909;     // R9
	*(--stkptr) = (uint32_t)0x08080808;     // R8
	*(--stkptr) = (uint32_t)0x07070707;     // R7
	*(--stkptr) = (uint32_t)0x06060606;     // R6
	*(--stkptr) = (uint32_t)0x05050505;     // R5
	*(--stkptr) = (uint32_t)0x04040404;     // R4
	*(--stkptr) = (uint32_t)0x03030303;     // R3
	*(--stkptr) = (uint32_t)0x02020202;     // R2
	*(--stkptr) = (uint32_t)0x01010101;     // R1
	*(--stkptr) = (uint32_t)pData;     // R0, holds pointer to shared variable
	*(--stkptr) = ARM_USER_MODE_ARM;    // CPSR, user mode

	return (uint32_t)(stkptr);
}

// Fill the thread structure for each thread
// Initialize the stack and assign the stack pointer for each thread
// Fill the TCB for each thread
void initThreads(void)
{
	// The Idle thread...
	createThread(&idleThdStr, 0, "idle thread", 10, READY, &idleThreadEntry);
	idleStkPtr = initStack(idleThreadStk, idleThdStr.thdFunc, (void*)&shared);
	idleTCB.threadDataPtr = &idleThdStr;
	idleTCB.threadStkPtr = &idleStkPtr;
	idleTCB.stackTop = &idleThreadStk[STACKSIZE - 1];
	idleTCB.stackBottom = &idleThreadStk[0];
	// Thread 1...
	createThread(&thrd1Str, 1, "thread 1", 10, READY, &thread1Entry);
	thread1StkPtr = initStack(thread1Stk, thrd1Str.thdFunc, (void*)&shared);
	thread1TCB.threadDataPtr = &thrd1Str;
	thread1TCB.threadStkPtr = &thread1StkPtr;
	thread1TCB.stackTop = &thread1Stk[STACKSIZE - 1];
	thread1TCB.stackBottom = &thread1Stk[0];
	// Thread 2...
	createThread(&thrd2Str, 2, "thread 2", 10, READY, &thread2Entry);
	thread2StkPtr = initStack(thread2Stk, thrd2Str.thdFunc, (void*)&shared);
	thread2TCB.threadDataPtr = &thrd2Str;
	thread2TCB.threadStkPtr = &thread2StkPtr;
	thread2TCB.stackTop = &thread2Stk[STACKSIZE - 1];
	thread2TCB.stackBottom = &thread2Stk[0];
	// Thread 3...
	createThread(&thrd3Str, 3, "thread 3", 10, READY, &thread3Entry);
	thread3StkPtr = initStack(thread3Stk, thrd3Str.thdFunc, (void*)&shared);
	thread3TCB.threadDataPtr = &thrd3Str;
	thread3TCB.threadStkPtr = &thread3StkPtr;
	thread3TCB.stackTop = &thread3Stk[STACKSIZE - 1];
	thread3TCB.stackBottom = &thread3Stk[0];
}
