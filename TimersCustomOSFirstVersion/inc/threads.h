/*
 * threads.h
 *
 *  Created on: Apr 27, 2014
 *      Author: Shawn Quinn
 */

#ifndef THREADS_H_
#define THREADS_H_

#include "lpc-2478-stk.h"
#include "print.h"

#define OK			0	// thread status OK return value
#define ERROR		1	// thread error condition return value
#define READY		0	// blocked thread state
#define ACTIVE		1	// active thread state
#define	BLOCKED		2	// blocked thread state
#define QUEUECAP	4	// queue table capacity

typedef struct
{
	uint32_t uId;
	char name[12];
	uint32_t priority;
	uint32_t state;
	uint32_t (*thdFunc)(void*);
}threadStr;

/* Global data structure definition */
typedef struct
{
	uint32_t guard;
	uint32_t inc;
	uint32_t t1;
	uint32_t t2;
}globalDataStr;

void timeDelay(int sec);
uint32_t idleThreadEntry(void* p);
uint32_t thread1Entry(void* p);
uint32_t thread2Entry(void* p);
uint32_t thread3Entry(void* p);
void createThread(void* p, int id, char* chName, int prio, int st, uint32_t (*fnc)(void*));
void printThreadData(void* p);

#endif /* THREADS_H_ */
