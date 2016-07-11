#ifndef __DAC_H
#define __DAC_H

#define DAC_BASE_ADDR   (0xE006C000)
#define DACR     (*(volatile uint32_t *)(DAC_BASE_ADDR + 0x00)) /* RW */

#define DACR_VALUE_MASK    0x0000FFC0
#define DACR_BIAS_MASK     0x00010000
#define DACR_MASK          (DACR_BIAS_MASK | DACR_VALUE_MASK)


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_DAC {
    uint32_t    R;
}  LPC24XX_DAC, *P_LPC24XX_DAC;

#define P_DAC_REGS  ((LPC24XX_DAC *)DAC_BASE_ADDR)


#endif /* __DAC_H */
