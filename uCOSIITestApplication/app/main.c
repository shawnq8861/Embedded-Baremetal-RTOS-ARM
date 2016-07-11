/************************************************************************************

Copyright (c) 2001-2011  University of Washington Extension.  All rights reserved.

Module Name:

    main.c

Module Description:

    Test application for UCOS-II port.
	Ported from the UCOS test app.

Revision History:

	2014/03/02: Shawn Quinn:
      Refactored OS event initialization into App_Init()

************************************************************************************/

//#include "includes.h"  // OS includes
#include "init.h"
#include "print.h"

// Prototype for startup task
void StartupTask(void* pdata);

// Allocate a stack for the startup task
static OS_STK StartupStk[APP_TASK_START_STK_SIZE];

// Allocate the print buffer
PRINT_DEFINEBUFFER();

/************************************************************************************

Routine Description:

    Standard program main entry point.

Arguments:

    None.

Return Value:

    Returns 0, which indicates nothing.

************************************************************************************/

int main(void)
{
    INT8U err;
    
    // Initialize hardware so we can use the serial port, etc.
    initHardware();

    RETAILMSG(1, ("uCOS Online (Project uCOS_Port_LPC2478, by Shawn Quinn)\n"));
    RETAILMSG(1, ("main: Build 201403009, Built %s %s.\n\n", __DATE__, __TIME__));

    // Initialize the OS
    DEBUGMSG(1, ("main: Running OSInit()...\n"));

    OSInit();

    App_Init();		// initialize semaphores, mailboxes, event flags, etc...

    // Create the startup task
    DEBUGMSG(1, ("main: Creating start up task.\n"));

    err = OSTaskCreate(StartupTask,
					   (void*)0,
					   (void*)&StartupStk[APP_TASK_START_STK_SIZE-1],
					   APP_TASK_START_PRIO);

    if (err != OS_NO_ERR) {
        DEBUGMSG(1, ("main: failed creating start up task: %d\n", err));
        while(TRUE);  //park on error
    }

    DEBUGMSG(1, ("Starting multi-tasking.\n"));

    // start the OS
    OSStart();

    // We never get here.
    RETAILMSG(1, ("main: error OSStart() returned: Exiting.\n\n"));

    return 0;
}

