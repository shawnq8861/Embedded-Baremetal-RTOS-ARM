#ifndef _TIMER2_H
#define _TIMER2_H

void initTimer2(uint32_t cclk);
void startTimer2(void);
uint32_t getTimer2Count(void);
uint32_t getTimer2Freq(void);

#endif /* _TIMER2_H */
