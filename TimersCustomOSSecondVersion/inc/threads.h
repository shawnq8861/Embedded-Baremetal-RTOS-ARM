/*
 * threads.h
 *
 * Module Description:
 *
 * Thread data structures and functions
 *
 *  Created on: April 27, 2014
 *      Author: Shawn Quinn
 */

#ifndef THREADS_H_
#define THREADS_H_

#include "lpc-2478-stk.h"
#include "print.h"

#define OK			0	// Thread status OK return value
#define ERROR		1	// Thread error condition return value
#define READY		0	// Blocked thread state
#define ACTIVE		1	// Active thread state
#define	BLOCKED		2	// Blocked thread state
#define QUEUECAP	4	// Queue table capacity
#define STACKSIZE 	512	// Default size of stacks.
#define ARM_MODE_ARM		0x00000000
#define ARM_SVC_MODE_ARM	(0x00000013L + ARM_MODE_ARM)
#define ARM_USER_MODE_ARM	(0x00000010L + ARM_MODE_ARM)

// Thread data structure definition
typedef struct
{
	uint32_t uId;
	char name[12];
	uint32_t priority;
	uint32_t state;
	void (*thdFunc)(void*);
}threadStr;

// Global data structure definition
typedef struct
{
	uint32_t guard;
	uint32_t inc;
	uint32_t t1;
	uint32_t t2;
}globalDataStr;

// Thread control block data structure definition
typedef struct
{
	threadStr* threadDataPtr;
	uint32_t* threadStkPtr;
	uint32_t* stackTop;
	uint32_t* stackBottom;
}threadControlBlock;

// Declare thread data and TCB's
threadStr idleThdStr;
threadStr thrd1Str;
threadStr thrd2Str;
threadStr thrd3Str;
threadControlBlock idleTCB;
threadControlBlock thread1TCB;
threadControlBlock thread2TCB;
threadControlBlock thread3TCB;

// Declare thread stack pointers
uint32_t currStkPtr;
uint32_t idleStkPtr;
uint32_t thread1StkPtr;
uint32_t thread2StkPtr;
uint32_t thread3StkPtr;

// Declare queue table for scheduler, thread data and TCB's
threadControlBlock queueTable[QUEUECAP];

// Allocate space for the thread stacks
uint32_t idleThreadStk[STACKSIZE];
uint32_t thread1Stk[STACKSIZE];
uint32_t thread2Stk[STACKSIZE];
uint32_t thread3Stk[STACKSIZE];

// Function declarations
void hello_world(void);
void idleThreadEntry(void* p);
void thread1Entry(void* p);
void thread2Entry(void* p);
void thread3Entry(void* p);
void createThread(void* p, uint32_t id, char* chName, uint32_t prio, uint32_t st, void (*fnc)(void*));
void printThreadData(void* p);
uint32_t initStack(uint32_t* stack, void* threadAddress, void* pData);
void initThreads(void);
extern void getStackPtr(uint32_t* stkPtr);

#endif /* THREADS_H_ */
