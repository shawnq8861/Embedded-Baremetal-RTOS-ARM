#ifndef _TIMER1_H
#define _TIMER1_H

#define DEBUG_TIMER1_ISR 1

// high speed
//#define TMR_FREQ (500)		// the timer frequency in interrupts/second

// low speed
#define TMR_FREQ (5)		// the timer frequency in interrupts/second

void initTimer1(uint32_t cclk);
void startTimer1(void);
extern void timer1IRQHandler(void);

#endif /* _TIMER1_H */
