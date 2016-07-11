//#include <stdint.h>
//#include "lpc2378.h"
#include "print.h"

/*
 *
 * Example abort handler that prints the type of abort and 
 * the address where it happened.
 *
 */
void abortPrint(unsigned int type, unsigned int address)
{
	if (type == 0) {
		printString("Data Abort at address: 0x");
	} else {
		printString("Prefetch Abort at address: 0x");
	}
	printHex(address);
	printString("\n");
}
