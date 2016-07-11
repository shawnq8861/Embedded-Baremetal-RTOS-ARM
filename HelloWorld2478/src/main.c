/*
 * MODULE
 *
 *   main.c
 *
 * DESCRIPTION
 *
 *  Sets up the Olimex LPC2478-STK board and continuously outputs a "Hello
 *  World" banner through the UART0 port.
 *
 *  Used to verify the at the Eclipse IDE, Cygwin, CDT, and GNUARM
 *  have been installed correctly.
 *
 * OS
 *
 *  n/a
 *
 * PLATFORM
 *
 *  Olimex LPC2478-STK
 *
****************************************************************************/
#define __MAIN_C__

//#include <stdio.h>
#include <stdint.h>
#include "lpc2478.h"
#include "init.h"
#include "print.h"

/*=========================================================================*/
/*  DEFINE: All Structures and Common Constants                            */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Prototypes                                                     */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Definition of all local Data                                   */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Definition of all local Procedures                             */
/*=========================================================================*/


/*=========================================================================*/
/*  DEFINE: All code exported                                              */
/*=========================================================================*/
/***************************************************************************/
/*  main                                                                   */
/***************************************************************************/
/*
 * NAME
 *
 *  main
 *
 * DESCRIPTION
 *
 *  prints out a standard banner on serial port
 *
 *   "University of Washington - UART Test Application"
 *
 * PARAMETERS
 *
 *  none...
 *
 * EXAMPLE
 *
 * from crt.s
 *
 *  B  main
 *
 * NOTES
 *
 *  This routine never terminates...
 *
 */
int main(void)
{
	uint32_t p;
	
    /* initialize */
    initHardware();
    
    printString("\033[2J"); /* Clear entire screen */
    printString("Olimex LPC-2478-STK... alive!!!\n");
    
    //sprintf(string, "sprintf works!\n");
    //printString(string);

    while (1)
    {
        /* Turn MCIPWR SD LED On */
        VOLATILE32(FIO1SET) |= 1<<5;
        
        printString("University of Washington - UART Test Application \n");
        for (p = 0; p < 0x100000; p++ );        // wait

        // IMPORTANT: String formatting drags in tons of other library code
        //  sprintf(string, "\n.%u", p);
        //  printString(string);
        
        /* Turn MCIPWR SD LED Off */
        VOLATILE32(FIO1CLR) |= 1<<5;
        for (p = 0; p < 0x100000; p++ );        // wait
    }
    /* never terminates, but put this here to make compiler happy ... */
    return(0);
}
/*** EOF ***/
