/*
 * threads.c
 *
 *  Created on: Apr 26, 2014
 *      Author: Shawn Quinn
 */

#include "threads.h"

volatile int tickCount = 0;

void timeDelay(int sec)
{
	int i, pause;
	for (i = 0; i < sec; ++i)
	{
		pause = tickCount + 100;
		while (tickCount < pause)
		{
			continue;
		}
	}
}

/* Idle thread definition */

uint32_t idleThreadEntry(void* p)
{
	if( P_FIO1_REGS->PIN & SD_LED_BIT )
	{
		// Turn off MCIPWR SD LED (near bottom left corner of LCD)
		P_FIO1_REGS->CLR = SD_LED_BIT;
    }
	else
	{
		// Turn on MCIPWR SD LED (near bottom left corner of LCD)
		P_FIO1_REGS->SET = SD_LED_BIT;
	}
	printString("Exiting idle thread...\r\n");
	timeDelay(5);
	return OK;
}

/* Thread 1 definition, "producer" */
uint32_t thread1Entry(void* p)
{
	globalDataStr* s = (globalDataStr* )p;
	(*s).t1++;
	if ((*s).guard == 0)
	{
		(*s).guard = 1;
		(*s).inc++;
		(*s).guard = 0;
	}
	printString("Exiting thread1...\r\n");
	timeDelay(1);
	return OK;
}

/* Thread 2 definition, "consumer" */
uint32_t thread2Entry(void* p)
{
	globalDataStr* s = (globalDataStr* )p;
	(*s).t2++;
	if ((*s).guard == 0)
	{
		(*s).guard = 1;
		(*s).inc--;
		(*s).guard = 0;
	}
	printString("Exiting thread2...\r\n");
	timeDelay(1);
	return OK;
}

/* Thread 3 definition, "monitor"*/
uint32_t thread3Entry(void* p)
{
	globalDataStr* s = (globalDataStr* )p;
	if ((*s).guard == 0)
	{
		(*s).guard = 1;
		if ((*s).inc > 0)
		{
			return ERROR;
		}
		(*s).guard = 0;
	}
	printString("Exiting thread3...\r\n");
	timeDelay(1);
	return OK;
}

void createThread(void* p, int id, char* chName, int prio, int st, uint32_t (*fnc)(void*))
{
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
}

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
