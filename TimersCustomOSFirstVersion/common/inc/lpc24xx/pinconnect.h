#ifndef __PINCONNECT_H
#define __PINCONNECT_H


/*******************************************************************************
 * Pin function select register values
 */

#define PINSEL_PRIMARY  0 /* Primary (default) function, typically GPIO port */
#define PINSEL_ALT_01   1 /* First  alternate function */
#define PINSEL_ALT_10   2 /*`Second alternate function */
#define PINSEL_ALT_11   3 /* Third  alternate function */

#define PINSEL_MASK(function, pos)  ((function & 0x00000003) << (pos * 2))
#define PINSEL_CLR_MASK(pos) (~(3 << (pos * 2)))


/*******************************************************************************
 * Pin mode select register bits - Pull-up, Pull-down, or no resistor
 */
#define PINMODE_PULL_UP   0 /* Pin has on-chip pull-up enabled (default) */
#define PINMODE_PULL_NONE 2 /* Pin has neither pull-up nor pull-down enabled */
#define PINMODE_PULL_DOWN 3 /* Pin has on-chip pull-down enabled */

#define PINMODE_MASK(mode, pos) ((mode & 0x00000003) << (pos * 2))


#define PINCON_BASE_ADDR  (0xE002C000)
#define PINSEL0     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x00)) /* RW */
#define PINSEL1     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x04)) /* RW */
#define PINSEL2     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x08)) /* RW */
#define PINSEL3     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x0C)) /* RW */
#define PINSEL4     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x10)) /* RW */
#define PINSEL5     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x14)) /* RW */
#define PINSEL6     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x18)) /* RW */
#define PINSEL7     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x1C)) /* RW */
#define PINSEL8     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x20)) /* RW */
#define PINSEL9     (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x24)) /* RW */
#define PINSEL10    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x28)) /* RW */
#define PINSEL10_MASK  0x00000008   /* mask reserved bits */
#define PINSEL11    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x2C)) /* RW */
#define PINSEL11_MASK  0x0000000F   /* mask reserved bits */

#define PINMODE0    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x40)) /* RW */
#define PINMODE1    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x44)) /* RW */
#define PINMODE2    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x48)) /* RW */
#define PINMODE3    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x4C)) /* RW */
#define PINMODE4    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x50)) /* RW */
#define PINMODE5    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x54)) /* RW */
#define PINMODE6    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x58)) /* RW */
#define PINMODE7    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x5C)) /* RW */
#define PINMODE8    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x60)) /* RW */
#define PINMODE9    (*(volatile uint32_t *)(PINCON_BASE_ADDR + 0x64)) /* RW */

typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_PINCON {
    uint32_t  SEL0;                 /* RW  Offset 0x00 */
    uint32_t  SEL1;                 /* RW  Offset 0x04 */
    uint32_t  SEL2;                 /* RW  Offset 0x08 */
    uint32_t  SEL3;                 /* RW  Offset 0x0C */
    uint32_t  SEL4;                 /* RW  Offset 0x10 */
    uint32_t  SEL5;                 /* RW  Offset 0x14 */
    uint32_t  SEL6;                 /* RW  Offset 0x18 */
    uint32_t  SEL7;                 /* RW  Offset 0x1C */
    uint32_t  SEL8;                 /* RW  Offset 0x20 */
    uint32_t  SEL9;                 /* RW  Offset 0x24 */
    uint32_t  SEL10;                /* RW  Offset 0x28 */
    uint32_t  SEL11;                /* RW  Offset 0x2C */
    uint32_t  __pad_30;
    uint32_t  __pad_34;
    uint32_t  __pad_38;
    uint32_t  __pad_3C;
    uint32_t  MODE0;                /* RW  Offset 0x40 */
    uint32_t  MODE1;                /* RW  Offset 0x44 */
    uint32_t  MODE2;                /* RW  Offset 0x48 */
    uint32_t  MODE3;                /* RW  Offset 0x4C */
    uint32_t  MODE4;                /* RW  Offset 0x50 */
    uint32_t  MODE5;                /* RW  Offset 0x54 */
    uint32_t  MODE6;                /* RW  Offset 0x58 */
    uint32_t  MODE7;                /* RW  Offset 0x5C */
    uint32_t  MODE8;                /* RW  Offset 0x60 */
    uint32_t  MODE9;                /* RW  Offset 0x64 */
}  LPC24XX_PINCON_t, *P_LPC24XX_PINCON_t;

#define P_PINCON_REGS ((LPC24XX_PINCON_t *)PINCON_BASE_ADDR)


#endif /* __PINCONNECT_H */
