#ifndef _CRITICAL_H
#define _CRITICAL_H

extern uint32_t InterruptsDisable(void);
extern void InterruptsEnable(uint32_t cpu_sr);

#define ARM_SR_FIQ_AND_IRQ_BITS 0x000000C0
#define ARM_SR_FIQ_BIT          0x00000040
#define ARM_SR_IRQ_BIT          0x00000080


#endif /* _CRITICAL_H */
