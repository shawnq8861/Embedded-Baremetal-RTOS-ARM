#ifndef __TIMERS_H
#define __TIMERS_H


#define LPC2478_TIMER0_BASE     (0xE0004000)
#define T0IR    (*(volatile uint8_t  *)(LPC2478_TIMER0_BASE + 0x00))    /* RW */
#define T0TCR   (*(volatile uint8_t  *)(LPC2478_TIMER0_BASE + 0x04))    /* RW */
#define T0TC    (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x08))    /* RW */
#define T0PR    (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x0C))    /* RW */
#define T0PC    (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x10))    /* RW */
#define T0MCR   (*(volatile uint16_t *)(LPC2478_TIMER0_BASE + 0x14))    /* RW */
#define T0MR0   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x18))    /* RW */
#define T0MR1   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x1C))    /* RW */
#define T0MR2   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x20))    /* RW */
#define T0MR3   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x24))    /* RW */
#define T0CCR   (*(volatile uint16_t *)(LPC2478_TIMER0_BASE + 0x28))    /* RW */
#define T0CR0   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x2C))    /* RO */
#define T0CR1   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x30))    /* RO */
#define T0CR2   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x34))    /* RO */
#define T0CR3   (*(volatile uint32_t *)(LPC2478_TIMER0_BASE + 0x38))    /* RO */
#define T0EMR   (*(volatile uint16_t *)(LPC2478_TIMER0_BASE + 0x3C))    /* RW */
#define T0CTCR  (*(volatile uint8_t  *)(LPC2478_TIMER0_BASE + 0x70))    /* RW */

#define LPC2478_TIMER1_BASE     (0xE0008000)
#define T1IR    (*(volatile uint8_t  *)(LPC2478_TIMER1_BASE + 0x00))    /* RW */
#define T1TCR   (*(volatile uint8_t  *)(LPC2478_TIMER1_BASE + 0x04))    /* RW */
#define T1TC    (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x08))    /* RW */
#define T1PR    (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x0C))    /* RW */
#define T1PC    (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x10))    /* RW */
#define T1MCR   (*(volatile uint16_t *)(LPC2478_TIMER1_BASE + 0x14))    /* RW */
#define T1MR0   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x18))    /* RW */
#define T1MR1   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x1C))    /* RW */
#define T1MR2   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x20))    /* RW */
#define T1MR3   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x24))    /* RW */
#define T1CCR   (*(volatile uint16_t *)(LPC2478_TIMER1_BASE + 0x28))    /* RW */
#define T1CR0   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x2C))    /* RO */
#define T1CR1   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x30))    /* RO */
#define T1CR2   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x34))    /* RO */
#define T1CR3   (*(volatile uint32_t *)(LPC2478_TIMER1_BASE + 0x38))    /* RO */
#define T1EMR   (*(volatile uint16_t *)(LPC2478_TIMER1_BASE + 0x3C))    /* RW */
#define T1CTCR  (*(volatile uint8_t  *)(LPC2478_TIMER1_BASE + 0x70))    /* RW */

#define LPC2478_TIMER2_BASE     (0xE0070000)
#define T2IR    (*(volatile uint8_t  *)(LPC2478_TIMER2_BASE + 0x00))    /* RW */
#define T2TCR   (*(volatile uint8_t  *)(LPC2478_TIMER2_BASE + 0x04))    /* RW */
#define T2TC    (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x08))    /* RW */
#define T2PR    (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x0C))    /* RW */
#define T2PC    (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x10))    /* RW */
#define T2MCR   (*(volatile uint16_t *)(LPC2478_TIMER2_BASE + 0x14))    /* RW */
#define T2MR0   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x18))    /* RW */
#define T2MR1   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x1C))    /* RW */
#define T2MR2   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x20))    /* RW */
#define T2MR3   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x24))    /* RW */
#define T2CCR   (*(volatile uint16_t *)(LPC2478_TIMER2_BASE + 0x28))    /* RW */
#define T2CR0   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x2C))    /* RO */
#define T2CR1   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x30))    /* RO */
#define T2CR2   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x34))    /* RO */
#define T2CR3   (*(volatile uint32_t *)(LPC2478_TIMER2_BASE + 0x38))    /* RO */
#define T2EMR   (*(volatile uint16_t *)(LPC2478_TIMER2_BASE + 0x3C))    /* RW */
#define T2CTCR  (*(volatile uint8_t  *)(LPC2478_TIMER2_BASE + 0x70))    /* RW */

#define LPC2478_TIMER3_BASE     (0xE0074000)
#define T3IR    (*(volatile uint8_t  *)(LPC2478_TIMER3_BASE + 0x00))    /* RW */
#define T3TCR   (*(volatile uint8_t  *)(LPC2478_TIMER3_BASE + 0x04))    /* RW */
#define T3TC    (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x08))    /* RW */
#define T3PR    (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x0C))    /* RW */
#define T3PC    (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x10))    /* RW */
#define T3MCR   (*(volatile uint16_t *)(LPC2478_TIMER3_BASE + 0x14))    /* RW */
#define T3MR0   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x18))    /* RW */
#define T3MR1   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x1C))    /* RW */
#define T3MR2   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x20))    /* RW */
#define T3MR3   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x24))    /* RW */
#define T3CCR   (*(volatile uint16_t *)(LPC2478_TIMER3_BASE + 0x28))    /* RW */
#define T3CR0   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x2C))    /* RO */
#define T3CR1   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x30))    /* RO */
#define T3CR2   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x34))    /* RO */
#define T3CR3   (*(volatile uint32_t *)(LPC2478_TIMER3_BASE + 0x38))    /* RO */
#define T3EMR   (*(volatile uint16_t *)(LPC2478_TIMER3_BASE + 0x3C))    /* RW */
#define T3CTCR  (*(volatile uint8_t  *)(LPC2478_TIMER3_BASE + 0x70))    /* RW */


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_TIMER {
                                /* Access Offset */
    uint8_t   IR;               /* RW     0x00 */
    uint8_t   pad0[3];
    uint8_t   TCR;              /* RW     0x04 */
    uint8_t   pad1[3];
    uint32_t  TC;               /* RW     0x08 */
    uint32_t  PR;               /* RW     0x0C */
    uint32_t  PC;               /* RW     0x10 */
    uint16_t  MCR;              /* RW     0x14 */
    uint8_t   pad2[2];
    uint32_t  MR0;              /* RW     0x18 */
    uint32_t  MR1;              /* RW     0x1C */
    uint32_t  MR2;              /* RW     0x20 */
    uint32_t  MR3;              /* RW     0x24 */
    uint16_t  CCR;              /* RW     0x28 */
    uint8_t   pad3[2];
    uint32_t  CR0;              /* RO     0x2C */
    uint32_t  CR1;              /* R0     0x30 */
    uint32_t  CR2;              /* R0     0x34 */
    uint32_t  CR3;              /* R0     0x38 */
    uint16_t  EMR;              /* RW     0x3C */
    uint8_t   pad4[2];
    uint8_t   pad5[48];
    uint8_t   CTCR;             /* RW     0x70 */
    uint8_t   pad6[3];
} LPC24XX_TIMER_t, *P_LPC24XX_TIMER_t;

#define P_TIMER0_REGS ((LPC24XX_TIMER_t *)LPC2478_TIMER0_BASE)
#define P_TIMER1_REGS ((LPC24XX_TIMER_t *)LPC2478_TIMER1_BASE)
#define P_TIMER2_REGS ((LPC24XX_TIMER_t *)LPC2478_TIMER2_BASE)
#define P_TIMER3_REGS ((LPC24XX_TIMER_t *)LPC2478_TIMER3_BASE)


#define MCR_MR0I    (1<<0)
#define MCR_MR0R    (1<<1)
#define MCR_MR0S    (1<<2)
#define MCR_MR1I    (1<<3)
#define MCR_MR1R    (1<<4)
#define MCR_MR1S    (1<<5)
#define MCR_MR2I    (1<<6)
#define MCR_MR2R    (1<<7)
#define MCR_MR2S    (1<<8)
#define MCR_MR3I    (1<<9)
#define MCR_MR3R    (1<<10)
#define MCR_MR3S    (1<<11)

#endif /* __TIMERS_H */
