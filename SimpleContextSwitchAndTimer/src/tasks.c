#include "lpc2478.h"
#include "print.h"

//
// hello_world with timer reset
//
void hello_world(void)
{
	WRITEREG32(T0IR, 0xFF);         // Reset timer
	printString("Hello world!\n");
}

//
// taskOne counts up from 0.
// Never exits.
//
void taskOne(void)
{
	int count = 0;
	while(1)
	{
		printString("task one: ");
		print_uint32(count++);
		printString("\n");
		int i;
		for(i=0;i<10000;i++);    // delay
	}
}

//
// taskTwo counts down from 0xFFFFFFFF
// Never exits.
//
void taskTwo(void)
{
	int count = 0xFFFFFFFF;
	while(1)
	{
		printString("task two: ");
		print_uint32(count--);
		printString("\n");
		int i;
		for(i=0;i<10000;i++);    // delay
	}
}
