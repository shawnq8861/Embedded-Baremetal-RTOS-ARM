/*
 * osServices.h
 *
 * Module Description:
 *
 * OS service routines and utility functions
 *
 *  Created on: May 11, 2014
 *      Author: Shawn Quinn
 */

#ifndef OSSERVICES_H_
#define OSSERVICES_H_

void timeDelay(uint32_t sec);
void msTimeDelay(uint32_t msec);
void fillQueue(void);
void scheduler(uint32_t stkPtr);
void startOS(void);
void startFirstThread(void);
void idleThreadEntry(void* p);
void abortPrint(unsigned int type, unsigned int address);

#endif /* OSSERVICES_H_ */
