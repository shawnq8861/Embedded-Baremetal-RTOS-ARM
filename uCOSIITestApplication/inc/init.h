#ifndef __INIT_H__
#define __INIT_H__

#include "includes.h"	// OS includes

typedef struct scb2300params {
	INT16U PLL_M_Mul; /* PLL Multiplier. Valid values 6 through 512*/
	INT8U  PLL_N_Div; /* PLL Divider. Valid values 1 through 32 */
	INT32U PLL_Fcco;  /* Frequency (Hz) of PLL output */
	INT8U  CCLK_Div;  /* CPU Clock divider, cclk */
	INT8U  MAMMode;   /* */
	INT8U  MAMTim;
} scb2300_t;

// Declare bilateral semaphores for ITC between task1 and task2
OS_EVENT *sem1, *sem2;

// Declare a mailbox ECB for interacting with the print task
OS_EVENT *mb1;

// Declare a mailbox ECB for interacting with the display task
OS_EVENT *mb2;

// Declare an event flag group for task4, task5, and task6
OS_FLAG_GRP *SomeStatusFlags;

// task4 and task5 status flags
#define TEST_EVENT_FLAG_ONE		0X01
#define TEST_EVENT_FLAG_TWO		0X02

// Declare pointer to message partition
OS_MEM *msgMem;

// parameters used to set the size of the memory partition
#define memBlocks	16
#define blockSize	128

INT8U msgPart[memBlocks][blockSize]; // allocate memory for the messaging partition

/* Off-chip System Specific Parameters */
#define FOSC_MAIN            (12000000)          
#define FOSC_RTC             (32768)

/* Exported Prototypes */
void handlerDummy(void);
INT32U getFcclk(void);
void pinConfigurator(void);

void initUART0(INT32U baud, INT8U mode, INT8U fmode, INT32U cclk);
void initHardware(void);
void App_Init(void);

void VIC_Init(void);
void Tmr_TickInit(void);

#endif /* __INIT_H__ */
