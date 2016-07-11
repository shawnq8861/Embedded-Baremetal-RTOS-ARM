/*++
Copyright (c) 2001-2007  University of Washington Extension.  

Module Name:

    tasks.h

Module Description:

    header file for tasks.c
    
Revision History:

--*/
#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

// Includes
#include "includes.h"
#include "print.h"

/***********************************************
    Define the APP configuration
***********************************************/

//default stack size for tasks in OS_STK units
#define APP_TASK_DEFAULT_STK_SIZE         512
#define APP_TASK_START_STK_SIZE           512

//task priorities
#define APP_TASK_START_PRIO                 4
#define APP_TASK_PRINT_PRIO					5
#define APP_TASK_TEST1_PRIO                 8
#define APP_TASK_TEST2_PRIO                 9
#define APP_TASK_TEST3_PRIO                 13
#define APP_TASK_TEST4_PRIO                 10
#define APP_TASK_TEST5_PRIO                 11
#define APP_TASK_TEST6_PRIO                 12
#define APP_TASK_DISPLAY_PRIO				6
#define APP_TASK_INPUT_PRIO					7

// OS Timer Task Priority
#define  OS_TASK_TMR_PRIO             (OS_LOWEST_PRIO - 2)

// Other defines

//size of the test queue
#define Q1_SIZE       10

#define  TRACE_LEVEL_OFF                       0
#define  TRACE_LEVEL_INFO                      1
#define  TRACE_LEVEL_DEBUG                     2


#define  APP_TRACE_LEVEL                TRACE_LEVEL_DEBUG
#define  APP_TRACE                        DEBUGMSG
#define  APP_TRACE_INFO(x)            ((APP_TRACE_LEVEL >= TRACE_LEVEL_INFO)  ? (void)(APP_TRACE(1, x)) : (void)0)
#define  APP_TRACE_DEBUG(x)           ((APP_TRACE_LEVEL >= TRACE_LEVEL_DEBUG) ? (void)(APP_TRACE(1, x)) : (void)0)
//get external refrence to the print buffer
PRINT_BUFFER();

#endif  //__APP_CFG_H__
