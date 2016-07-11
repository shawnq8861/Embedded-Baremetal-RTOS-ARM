/************************************************************************************

Copyright (c) 2001-2007  University of Washington Extension.

Module Name:

    tasks.c

Module Description:

    The tasks that are executed by the test application.

    History

    2014/03/02: Shawn Quinn:
      Added message box and printask to unmangle output
    2014/03/08: Shawn Quinn:
      Added event flag group and producer/consumer tasks
      Added managed memory for message printing

************************************************************************************/

#include "includes.h"
#include "print.h"
#include "uarts.h"
#include "init.h"
#include "driver.h"
#include "drv_display.h"
#include "drv_input.h"

#define BUFSIZE 256

/************************************************************************************

   Allocate the stacks for each task.
   The maximum of tasks the application can have is defined by OS_MAX_TASKS in os_cfg.h

************************************************************************************/

static OS_STK   Task1Stk[APP_TASK_DEFAULT_STK_SIZE];
static OS_STK   Task2Stk[APP_TASK_DEFAULT_STK_SIZE];
//static OS_STK   Task3Stk[APP_TASK_DEFAULT_STK_SIZE];
static OS_STK   TaskPStk[APP_TASK_DEFAULT_STK_SIZE];
static OS_STK   Task4Stk[APP_TASK_DEFAULT_STK_SIZE];
static OS_STK   Task5Stk[APP_TASK_DEFAULT_STK_SIZE];
static OS_STK   Task6Stk[APP_TASK_DEFAULT_STK_SIZE];
static OS_STK   TaskDStk[APP_TASK_DEFAULT_STK_SIZE];
static OS_STK   TaskIStk[APP_TASK_DEFAULT_STK_SIZE];


// Task prototypes
void TaskOne(void* pdata);
void TaskTwo(void* pdata);
//void TaskThree(void* pdata);
void TaskPrint(void* pdata);
void TaskFour(void* pdata);
void TaskFive(void* pdata);
void TaskSix(void* pdata);
void TaskDisplay(void* pdata);
void TaskInput(void* pdata);

// Useful functions
//static void SetLED(BOOLEAN state);
void printWithBuf(char *buf, int size, char *format, ...);

OSDRV_DRIVER_ENTRY DriverTable[] =
{
		// Init Config, Context Initialized, RefCount
		//{ { Spi_Init, NULL, NULL, NULL, NULL }, { 0 }, NULL, FALSE, 0 },
		//{ { Mp3_Init, NULL, NULL, NULL, NULL }, { 0 }, NULL, FALSE, 0 }//,
		// add additional drivers here
		{ { Display_Init, NULL, NULL, NULL, NULL }, { 0 }, NULL, FALSE, 0 },
		{ { Input_Init, NULL, NULL, NULL, NULL }, { 0 }, NULL, FALSE, 0 }
};

#define DRIVER_COUNT (sizeof(DriverTable)/sizeof(OSDRV_DRIVER_ENTRY))

/************************************************************************************

   This task is the initial task running, started by main(). It starts
   the system tick timer and creates all the other tasks. Then it deletes itself.

************************************************************************************/
void StartupTask(void* pdata)
{
	//extern OS_MEM *msgMem;	// the memory partition
	INT8U err;
	char buf[BUFSIZE];
	printWithBuf(buf, BUFSIZE, "StartupTask: Begin\n");
	printWithBuf(buf, BUFSIZE, "StartupTask: Starting timer tick\n");

    // Start the system tick
    Tmr_TickInit();

    // initialize the driver sub-system
    err = OSDRV_SubsysInit(DriverTable, DRIVER_COUNT);

    if (err != OS_DRV_NO_ERR)
    {
    	//print_f("StartupTask: Failed to initialize driver subsystem: %d\n\r", err);
    	printWithBuf(buf, BUFSIZE, "StartupTask: Failed to initialize driver subsystem: %d\n\r", err);
    	// park here
    	while (TRUE)
    		;
    }

     // Create the the test tasks
    printWithBuf(buf, BUFSIZE, "StartupTask: Creating the tasks\n");

    // The maximum of tasks the application can have is defined by OS_MAX_TASKS in os_cfg.h
    OSTaskCreate(TaskOne, (void*)0, (void*)&Task1Stk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_TEST1_PRIO);
    OSTaskCreate(TaskTwo, (void*)0, (void*)&Task2Stk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_TEST2_PRIO);
    //OSTaskCreate(TaskThree, (void*)0, (void*)&Task3Stk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_TEST3_PRIO);
    OSTaskCreate(TaskPrint, (void*)0, (void*)&TaskPStk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_PRINT_PRIO);
    OSTaskCreate(TaskFour, (void*)0, (void*)&Task4Stk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_TEST4_PRIO);
    OSTaskCreate(TaskFive, (void*)0, (void*)&Task5Stk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_TEST5_PRIO);
    OSTaskCreate(TaskSix, (void*)0, (void*)&Task6Stk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_TEST6_PRIO);
    OSTaskCreate(TaskDisplay, (void*)0, (void*)&TaskDStk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_DISPLAY_PRIO);
    OSTaskCreate(TaskInput, (void*)0, (void*)&TaskIStk[APP_TASK_DEFAULT_STK_SIZE-1], APP_TASK_INPUT_PRIO);

    // Delete ourselves, letting the work be done in the new tasks.
    printWithBuf(buf, BUFSIZE, "StartupTask: deleting self\n");
	OSTaskDel(OS_PRIO_SELF);
}

/************************************************************************************

   TaskOne turns on the LED every 1000 ticks.

************************************************************************************/
void TaskOne(void* pdata)
{
	extern OS_EVENT *mb1, *mb2, *sem1, *sem2; 	// the OS events
	extern OS_MEM *msgMem;	// the memory partition
	INT8U err;
	INT8U dsplyMsg = IOCTL_DISPLAY_LED_ON;
	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskOne: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block

    while(1)
    {
    	OSSemPend( sem2, 0, &err );
     	OSTimeDly(1000);
     	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
    	sprintf (msgBuf, "TaskOne: Turn LED On\n");	// place message string in buffer
     	OSMboxPost(mb1, msgBuf);	// send the message string
        OSMboxPost(mb2, &dsplyMsg);	// send the message to display driver
        err = OSSemPost( sem1 );
    }
}

/************************************************************************************

   TaskTwo turns off the LED every 500 ticks.

************************************************************************************/
void TaskTwo(void* pdata)
{
	extern OS_EVENT *mb1, *mb2, *sem1, *sem2; 	// the OS events
	extern OS_MEM *msgMem;	// the memory partition
	INT8U err;
	INT8U dsplyMsg = IOCTL_DISPLAY_LED_OFF;
	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskTwo: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block
    OSTimeDly(400);  // Delay starting to interleave the tasks.

    while(1)
    {
    	OSTimeDly(1000);
    	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
    	sprintf (msgBuf, "TaskTwo: Turn LED Off\n");	// place message string in buffer
    	OSMboxPost(mb1, msgBuf);	// send the message string
    	OSMboxPost(mb2, &dsplyMsg);	// send the message to display driver
        //SetLED(FALSE);
        err = OSSemPost( sem2 );
        OSSemPend( sem1, 0, &err );
    }
}

/************************************************************************************

   TaskThree - Counts up

************************************************************************************/
void TaskThree(void* pdata)
{
	extern OS_EVENT *mb1; 	// the message mailbox for printing
	extern OS_MEM *msgMem;	// the memory partition
	INT8U err;
	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskThree: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block

	int count = 0;
    while(1)
    {
    	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
    	sprintf (msgBuf, "TaskThree: count = %d\n", count++);	// place message string in buffer
    	OSMboxPost(mb1, msgBuf);	// send the message string
    	int i;
    	for(i=0;i<100000;i++); // pretend work
    }
}

/************************************************************************************

   Print a formated string with the given buffer.
   Each task should use its own buffer to prevent data corruption.

************************************************************************************/
void printWithBuf(char *buf, int size, char *format, ...)
{
    va_list args;
    va_start(args, format);
    vsnprintf(buf, size, format, args);
	printString(buf);
    va_end(args);
}

/************************************************************************************

   Prints a formated string received as a mailbox message from other tasks.
   Each task gets a buffer from an OS memory partion to hold the message.
   This task puts the buffer back after printing the message.

************************************************************************************/
void TaskPrint(void* pdata)
{
	extern OS_EVENT *mb1; 	// the message mailbox for printing
	extern OS_MEM *msgMem;	// the memory partition
	INT8U err;
	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskPrint: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block

    for(;;)
    {
    	void *msg;      // will point to the received message
    	msg = (char *)OSMboxPend( mb1, 0, &err ) ;  // wait for a message
    	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
    	printWithBuf(msgBuf, BUFSIZE, msg);	// print the message
    	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block
    	OSMemPut(msgMem, (INT8U *)msg);		// return the message memory block
    }
}

/************************************************************************************

   TaskFour sets event flag one

************************************************************************************/
void TaskFour(void* pdata)
{
	extern OS_EVENT *mb1; 	// the message mailbox for printing
	extern OS_FLAG_GRP *SomeStatusFlags; 		// the flag group to post flag events to
	extern OS_MEM *msgMem;	// the memory partition
	OS_FLAGS tskFourFlags;	// to hold the current flag values
	INT8U err;
	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskFour: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block

	OSTimeDly(200);  // Delay starting to interleave the tasks.

    while(1)
    {
    	tskFourFlags = OSFlagPost(SomeStatusFlags, TEST_EVENT_FLAG_ONE, OS_FLAG_SET, &err);	// post event flag
    	if ((tskFourFlags & TEST_EVENT_FLAG_ONE) == TEST_EVENT_FLAG_ONE)
    	{
    		msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
    		sprintf (msgBuf, "TaskFour: Flag One Posted, flags = %d\n", tskFourFlags);	// place message string in buffer
    		OSMboxPost(mb1, msgBuf);	// send the message string
    	}
     	OSTimeDly(1000);
    }
}

/************************************************************************************

   TaskFive sets event flag two

************************************************************************************/
void TaskFive(void* pdata)
{
	extern OS_EVENT *mb1; 	// the message mailbox for printing
	extern OS_FLAG_GRP *SomeStatusFlags; 		// the flag group to post flag events to
	extern OS_MEM *msgMem;	// the memory partition
	OS_FLAGS tskFiveFlags;	// to hold the current flag values
	INT8U err;
	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskFive: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block


	OSTimeDly(500);  // Delay starting to interleave the tasks.

    while(1)
    {
    	tskFiveFlags = OSFlagPost(SomeStatusFlags, TEST_EVENT_FLAG_TWO, OS_FLAG_SET, &err);	// post event flag
    	if ((tskFiveFlags & TEST_EVENT_FLAG_TWO) == TEST_EVENT_FLAG_TWO)
    	{
    		msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
    		sprintf (msgBuf, "TaskFive: Flag Two Posted, flags = %d\n", tskFiveFlags);	// place message string in buffer
    		OSMboxPost(mb1, msgBuf);	// send the message string
    	}
     	OSTimeDly(1000);
    }
}

/************************************************************************************

   TaskSix consumes event flags one and two

************************************************************************************/
void TaskSix(void* pdata)
{
	extern OS_EVENT *mb1; 	// the message mailbox for printing
	extern OS_FLAG_GRP *SomeStatusFlags; 	// the flag group to post flag events to
	extern OS_MEM *msgMem;	// the memory partition
	OS_FLAGS status;
	INT8U err;
	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskSix: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block

	OSTimeDly(800);  // Delay starting to interleave the tasks.

   	for(;;)
    {
    	status = OSFlagPend(SomeStatusFlags, TEST_EVENT_FLAG_ONE + TEST_EVENT_FLAG_TWO,
									OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME,
									10, &err);	// post event flag
    	if (status == TEST_EVENT_FLAG_ONE + TEST_EVENT_FLAG_TWO)
    	{
    		msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
    		sprintf (msgBuf, "TaskSix: Flags Consumed, status = %d\n", status);	// place message string in buffer
    		OSMboxPost(mb1, msgBuf);	// send the message string
    	}
     	OSTimeDly(250);
    }
}

/************************************************************************************

   TaskDisplay toggles LED on and off

************************************************************************************/
void TaskDisplay(void* pdata){
	extern OS_EVENT *mb2; 	// the message mailbox for LED control
	INT8U err, msg;
	INT32U length;
	HANDLE hDisplay;

	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskDisplay: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block

	while( 1 )
	{
		hDisplay = Open(DISPLAY_DRV, OSDRV_WRITE | OSDRV_EXCLUSIVE);
		length = sizeof(HANDLE);
		msg = *(INT8U*)OSMboxPend( mb2, 0, &err ) ;  // wait for a message
		if ( msg == IOCTL_DISPLAY_LED_ON)
		{
			err = Ioctl(hDisplay, msg, NULL, &length);	// call driver to turn LED on
		}
		else if ( msg == IOCTL_DISPLAY_LED_OFF)
		{
			err = Ioctl(hDisplay, msg, NULL, &length);	// call driver to turn LED off
		}
		Close( hDisplay );
		OSTimeDly(100);
	}
}

/************************************************************************************

   TaskInput reads the state of the buttons

************************************************************************************/
void TaskInput(void* pdata){
	extern OS_EVENT *mb1; 	// the message mailbox for printing
	INT8U err, msg;
	INT8U cntrl = 0;
	INT32U length;
	HANDLE hInput;

	char *msgBuf;
	msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
	printWithBuf(msgBuf, BUFSIZE, "TaskInput: starting\n");
	OSMemPut(msgMem, (INT8U *)msgBuf);		// return the memory block

	for(;;)
	{
		hInput = Open(INPUT_DRV, OSDRV_WRITE | OSDRV_EXCLUSIVE);
		length = sizeof(HANDLE);
		msg = Ioctl(hInput, cntrl, NULL, &length);	// call driver to check button state
		if ( msg == PLAY_BUTTON_PRESSED)
		{
			msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
			sprintf (msgBuf, "Play button pressed\n");	// place message string in buffer
			OSMboxPost(mb1, msgBuf);	// send the message string
		}
		else if ( msg == STOP_BUTTON_PRESSED)
		{
			msgBuf = (char *)OSMemGet(msgMem, &err);	// retrieve a block of memory to hold message string
			sprintf (msgBuf, "Stop button pressed\n");	// place message string in buffer
			OSMboxPost(mb1, msgBuf);	// send the message string
		}
		Close( hInput );
		OSTimeDly(1000);
	}
}
