#ifndef _TIMER1_H
#define _TIMER1_H

void initTimer1(uint32_t cclk);
void startTimer1(void);
void timer1ISR(void);


#endif /* _TIMER1_H */
