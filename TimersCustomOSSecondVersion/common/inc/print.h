#ifndef __PRINT_H__
#define __PRINT_H__

void printHex(uint32_t u32);
void print_uint32(uint32_t u);
void printString(char *ptr);
void printStringHex(char *ptr, uint32_t u32Hex);
void printChar(const int8_t letter);

extern char stringbuffer[];


//
// Macros for printing debug messages.
//
// TODO extra credit optional Add fflush(stdout)
#define _DBG_PRINTX_ARG(arg...) arg /* unroll the parens around the var args*/
#define PRINTBUFMAX 256
#define RETAILMSG(x,y) \
    ((x) ? (snprintf(stringbuffer, PRINTBUFMAX, _DBG_PRINTX_ARG y), printString(stringbuffer)) : (void)(0))
#define PRINT_DEFINEBUFFER() char stringbuffer[PRINTBUFMAX]
#define PRINT_BUFFER() extern char stringbuffer[]

#ifdef DEBUG
#define DEBUGMSG(x,y) \
    ((x) ? (snprintf(stringbuffer, PRINTBUFMAX, _DBG_PRINTX_ARG y), printString(stringbuffer)) : (void)(0))
#else // DEBUG
    #define DEBUGMSG(x,y) (void)(0)
#endif // DEBUG



#define PRINTREG(reg)  snprintf(stringbuffer, PRINTBUFMAX, \
        "\n\r &(%35s ) = 0x%lX  Read Value=%lX",#reg , (uint32_t)&(reg), (uint32_t)reg ); \
    printString(stringbuffer)



#endif /* __PRINT_H__ */
