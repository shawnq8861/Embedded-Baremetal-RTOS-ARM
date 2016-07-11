/************************************************************************************

Module Name:

    main.c

Module Description:

    Task scheduler and initialization and setup of two task context switching example

Revision History:

    23JAN2014 Shawn Quinn

************************************************************************************/

#include "lpc2478.h"
#include "init.h"
#include "print.h"

#define  ARM_MODE_ARM           0x00000000
#define  ARM_SVC_MODE_ARM      (0x00000013L + ARM_MODE_ARM)

// Default size of stacks.
#define STACKSIZE 256

// Allocate space for two stacks
int stackOne[STACKSIZE];
int stackTwo[STACKSIZE];

// Task context management
//
// To manage the context for the two tasks all we really need
// is to store the stack pointers. The actual context for the
// tasks are stored on their own stacks.
//
// taskID is a global variable that holds the ID of the current stack.
//
// currentSP is a global variable that holds the value of the
// stack pointer for the current stack.

int stackOneSP;       // Value of task 1's stack pointer
int stackTwoSP;       // Value of task 2's stack pointer

int currentSP;        // The value of the current task's stack pointer
int taskID;           // The ID of the current task

void taskOne(void);   // Task one counts up from 0
void taskTwo(void);   // Task two counts down from 0xFFFFFFFF

void initialize_timer_tick (void);   // Intializes timer for the interrupt tick
void switch_to_current(void);        // Switches to the current task

/*
	Intialize stack.

	The stack grows down in memory so we want to start by calculating
	the top of the stack.

	Then fill in the initial data starting at the top and working down.

	The important values are the task_address and the initial CPSR.

	LR doesn't matter since the task is a infinite loop and should not exit.
	If it doesn't exit, then it doesn't use the LR since it doesn't return.

*/
int initialize_stack(int* stack, void* task_address)
{
	// Calculate the top of the stack.
	int *stkptr = (int*)(stack + STACKSIZE - 1);

	*(stkptr)   = (int)task_address;   // PC
	*(--stkptr) = (int)0x0e0e0e0e;     // R14 - LR
	*(--stkptr) = (int)0x0c0c0c0c;     // R12
	*(--stkptr) = (int)0x0b0b0b0b;     // R11
	*(--stkptr) = (int)0x0a0a0a0a;     // R10
	*(--stkptr) = (int)0x09090909;     // R9
	*(--stkptr) = (int)0x08080808;     // R8
	*(--stkptr) = (int)0x07070707;     // R7
	*(--stkptr) = (int)0x06060606;     // R6
	*(--stkptr) = (int)0x05050505;     // R5
	*(--stkptr) = (int)0x04040404;     // R4
	*(--stkptr) = (int)0x03030303;     // R3
	*(--stkptr) = (int)0x02020202;     // R2
	*(--stkptr) = (int)0x01010101;     // R1
	*(--stkptr) = (int)0x00000000;     // R0
	*(--stkptr) = ARM_SVC_MODE_ARM;    // CPSR

	return (int)(stkptr);
}

/*
	Simple task scheduler that decides which task to run.

	Alternates back and forth between two tasks by changing the
	value of currentSP used by SwitchingIRQHandler in switch.s

	SwitchingIRQHandler does the real context switching work.
*/
void scheduler(int sp)
{
	WRITEREG32(T0IR, 0xFF);            // Reset timer
	printString("Switch\n");

	if (taskID == 1)
	{
		stackOneSP = sp;               // Store stack pointer for task 1
		taskID = 2;                    // Set the taskID to task 2
		currentSP = stackTwoSP;        // Set the current stack pointer to task 2's stack pointer
	}
	else
	{
		stackTwoSP = sp;               // Store stack pointer for task 2
		taskID = 1;                    // Set the taskID to task 1
		currentSP = stackOneSP;        // Set the current stack pointer to task 1's stack pointer
	}
}

///////////////////////////////////////////////////////////////////////////////////////////
//
//  main
//
//  Intializes two stacks one for each task. Set currentSP and taskID to the first task.
//  Starts the timer for the interrupt ticks which will cause the tasks to switch.
//  Runs the first task.
//
//  This function never runs passed the call to switch_to_current() so it never exits.
//
int main(void)
{
    initHardware();

    printString("University of Washington - Context_Switcher Test Application \n");
    printString("Shawn Quinn, CP105, Lab 2\n");

    // Setup initial stacks for tasks
    stackOneSP = initialize_stack(stackOne, (void*)taskOne);
    stackTwoSP = initialize_stack(stackTwo, (void*)taskTwo);

    // Set current to first task
    taskID = 1;
    currentSP = stackOneSP;

    initialize_timer_tick();

    // Run the current task
    switch_to_current();         // This call never returns to this function.

    // Never gets here.
    printString("Main completed.\n");
    while(1);
    return 0;
}


