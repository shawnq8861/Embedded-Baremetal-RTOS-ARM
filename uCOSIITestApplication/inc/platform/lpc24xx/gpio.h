#ifndef __GPIO_H
#define __GPIO_H

#include "../attributes.h"


/*
 * Steps taken to make this file.
 *
 * First we define the most portable method (but lacks type checking):
 * 1. #define a list of the registers and addresses
 *    use the name in the LPC User Manual
 *    add access note RW, RO, WO
 * 2. Add the bit width casts to each register definition
 * 3. Add Register Masks for reserved or unused bits
 * 4. Test each register definition by
 *    A) Printing out and verifying the addresses
 *    B) Writing code that exercises register accesses (read and write)
 *       and inspect the disassembly for proper instructions with
 *       all optimization levels (-O0, -O1, -O2, -Os, and -O3)
 *
 * Second we define the more structured and type checked approach:
 * 1. Identify similar structured address layouts of modules
 * 2. Define a new type based on a struct for the modules' register layout
 * 3. Test each register definition by
 *    A) Printing out and verifying the addresses
 *    B) Writing code that exercises register accesses (read and write)
 *       and inspect the disassembly for proper instructions with
 *       all optimization levels (-O0, -O1, -O2, -Os, and -O3)
 */

/*******************************************************************************
 * GPIO Registers (legacy APB accessible registers)
 */

#define GPIO_BASE_ADDR  (0xE0028000)
#define IO0PIN          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x00)) /* RW */
#define IO0SET          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x04)) /* RW */
#define IO0DIR          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x08)) /* RW */
#define IO0CLR          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x0C)) /* WO */

#define IO1PIN          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x10)) /* RW */
#define IO1SET          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x14)) /* RW */
#define IO1DIR          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x18)) /* RW */
#define IO1CLR          (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x1C)) /* WO */


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_GPIO {
    uint32_t  PIN;                  /* RW  IOx Base + 0x00 */
    uint32_t  SET;                  /* RW  IOx Base + 0x04 */
    uint32_t  DIR;                  /* RW  IOx Base + 0x08 */
    uint32_t  CLR;                  /* WO  IOx Base + 0x0C */
}  LPC24XX_GPIO_t, *P_LPC24XX_GPIO_t;

#define P_GPIO0_REGS ((LPC24XX_GPIO_t *)GPIO_BASE_ADDR)
#define P_GPIO1_REGS ((LPC24XX_GPIO_t *)GPIO_BASE_ADDR + 0x10)


/*******************************************************************************
 * GPIO Interrupt Registers
 */

/* Wierd note: these are the only registers with upper and lower case */
/* IOxIntClr registers are write 1 to clear*/

#define IOIntStatus     (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x80)) /* RO */
#define IOIntStatusMask (0x00000005) /* 0b0...0101 */

#define IO0IntStatR     (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x84)) /* RO */
#define IO0IntStatF     (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x88)) /* RO */
#define IO0IntClr       (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x8C)) /* WO */
#define IO0IntEnR       (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x90)) /* RW */
#define IO0IntEnF       (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0x94)) /* RW */

#define IO2IntStatR     (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0xA4)) /* RO */
#define IO2IntStatF     (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0xA8)) /* RO */
#define IO2IntClr       (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0xAC)) /* WO */
#define IO2IntEnR       (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0xB0)) /* RW */
#define IO2IntEnF       (*(volatile uint32_t *)(GPIO_BASE_ADDR + 0xB4)) /* RW */


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_GPIOINT {
    uint32_t  Status;               /* RO  GPIO_BASE_ADDR + 0x80 */
}  LPC24XX_GPIOINT_t, *P_LPC24XX_GPIOINT_t;

#define P_GPIO_INT_REGS ((LPC24XX_GPIOINT_t *)GPIO_BASE_ADDR + 0x80)


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_GPIOXINT {
    uint32_t  StatR;                /* RO  IOxInt Base + 0x04 */
    uint32_t  StatF;                /* RO  IOxInt Base + 0x08 */
    uint32_t  Clr;                  /* RO  IOxInt Base + 0x0C */
    uint32_t  EnR;                  /* RO  IOxInt Base + 0x10 */
    uint32_t  EnF;                  /* RO  IOxInt Base + 0x14 */
}  LPC24XX_GPIOXINT_t, *P_LPC24XX_GPIOXINT_t;

#define P_GPIO0_INT_REGS ((LPC24XX_GPIOXINT_t *)GPIO_BASE_ADDR + 0x84)
#define P_GPIO2_INT_REGS ((LPC24XX_GPIOXINT_t *)GPIO_BASE_ADDR + 0xA4)


/*******************************************************************************
 * Fast GPIO Registers (local bus accessible registers - enhanced GPIO features)
 */

/* FIOxMASK Registers: NOTE 0 enables bit, 1 disables bit access */
/* FIO Clear registers are write 1 to clear which is probably why they are WO */

#define FIO_BASE_ADDR  (0x3FFFC000)
#define FIO0DIR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x00))  /* RW */
#define FIO0DIR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x01))  /* RW */
#define FIO0DIR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x02))  /* RW */
#define FIO0DIR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x03))  /* RW */
#define FIO0DIRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x00))  /* RW */
#define FIO0DIRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x02))  /* RW */
#define FIO0DIR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x00))  /* RW */

#define FIO0MASK0       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x10))  /* RW */
#define FIO0MASK1       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x11))  /* RW */
#define FIO0MASK2       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x12))  /* RW */
#define FIO0MASK3       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x13))  /* RW */
#define FIO0MASKL       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x10))  /* RW */
#define FIO0MASKU       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x12))  /* RW */
#define FIO0MASK        (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x10))  /* RW */

#define FIO0PIN0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x14))  /* RW */
#define FIO0PIN1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x15))  /* RW */
#define FIO0PIN2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x16))  /* RW */
#define FIO0PIN3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x17))  /* RW */
#define FIO0PINL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x14))  /* RW */
#define FIO0PINU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x16))  /* RW */
#define FIO0PIN         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x14))  /* RW */

#define FIO0SET0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x18))  /* RW */
#define FIO0SET1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x19))  /* RW */
#define FIO0SET2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x1A))  /* RW */
#define FIO0SET3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x1B))  /* RW */
#define FIO0SETL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x18))  /* RW */
#define FIO0SETU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x1A))  /* RW */
#define FIO0SET         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x18))  /* RW */

#define FIO0CLR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x1C))  /* WO */
#define FIO0CLR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x1D))  /* WO */
#define FIO0CLR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x1E))  /* WO */
#define FIO0CLR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x1F))  /* WO */
#define FIO0CLRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x1C))  /* WO */
#define FIO0CLRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x1E))  /* WO */
#define FIO0CLR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x1C))  /* WO */

#define FIO1DIR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x20))  /* RW */
#define FIO1DIR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x21))  /* RW */
#define FIO1DIR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x22))  /* RW */
#define FIO1DIR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x23))  /* RW */
#define FIO1DIRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x20))  /* RW */
#define FIO1DIRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x22))  /* RW */
#define FIO1DIR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x20))  /* RW */
//#define FIO1DIR        0x3FFFC020

#define FIO1MASK0       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x30))  /* RW */
#define FIO1MASK1       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x31))  /* RW */
#define FIO1MASK2       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x32))  /* RW */
#define FIO1MASK3       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x33))  /* RW */
#define FIO1MASKL       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x30))  /* RW */
#define FIO1MASKU       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x32))  /* RW */
#define FIO1MASK        (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x30))  /* RW */

#define FIO1PIN0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x34))  /* RW */
#define FIO1PIN1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x35))  /* RW */
#define FIO1PIN2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x36))  /* RW */
#define FIO1PIN3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x37))  /* RW */
#define FIO1PINL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x34))  /* RW */
#define FIO1PINU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x36))  /* RW */
#define FIO1PIN         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x34))  /* RW */

#define FIO1SET0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x38))  /* RW */
#define FIO1SET1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x39))  /* RW */
#define FIO1SET2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x3A))  /* RW */
#define FIO1SET3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x3B))  /* RW */
#define FIO1SETL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x38))  /* RW */
#define FIO1SETU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x3A))  /* RW */
#define FIO1SET         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x38))  /* RW */

#define FIO1CLR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x3C))  /* WO */
#define FIO1CLR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x3D))  /* WO */
#define FIO1CLR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x3E))  /* WO */
#define FIO1CLR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x3F))  /* WO */
#define FIO1CLRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x3C))  /* WO */
#define FIO1CLRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x3E))  /* WO */
#define FIO1CLR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x3C))  /* WO */

#define FIO2DIR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x40))  /* RW */
#define FIO2DIR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x41))  /* RW */
#define FIO2DIR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x42))  /* RW */
#define FIO2DIR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x43))  /* RW */
#define FIO2DIRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x40))  /* RW */
#define FIO2DIRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x42))  /* RW */
#define FIO2DIR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x40))  /* RW */

#define FIO2MASK0       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x50))  /* RW */
#define FIO2MASK1       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x51))  /* RW */
#define FIO2MASK2       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x52))  /* RW */
#define FIO2MASK3       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x53))  /* RW */
#define FIO2MASKL       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x50))  /* RW */
#define FIO2MASKU       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x52))  /* RW */
#define FIO2MASK        (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x50))  /* RW */

#define FIO2PIN0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x54))  /* RW */
#define FIO2PIN1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x55))  /* RW */
#define FIO2PIN2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x56))  /* RW */
#define FIO2PIN3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x57))  /* RW */
#define FIO2PINL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x54))  /* RW */
#define FIO2PINU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x56))  /* RW */
#define FIO2PIN         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x54))  /* RW */

#define FIO2SET0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x58))  /* RW */
#define FIO2SET1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x59))  /* RW */
#define FIO2SET2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x5A))  /* RW */
#define FIO2SET3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x5B))  /* RW */
#define FIO2SETL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x58))  /* RW */
#define FIO2SETU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x5A))  /* RW */
#define FIO2SET         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x58))  /* RW */

#define FIO2CLR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x5C))  /* WO */
#define FIO2CLR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x5D))  /* WO */
#define FIO2CLR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x5E))  /* WO */
#define FIO2CLR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x5F))  /* WO */
#define FIO2CLRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x5C))  /* WO */
#define FIO2CLRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x5E))  /* WO */
#define FIO2CLR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x5C))  /* WO */

#define FIO3DIR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x60))  /* RW */
#define FIO3DIR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x61))  /* RW */
#define FIO3DIR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x62))  /* RW */
#define FIO3DIR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x63))  /* RW */
#define FIO3DIRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x60))  /* RW */
#define FIO3DIRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x62))  /* RW */
#define FIO3DIR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x60))  /* RW */

#define FIO3MASK0       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x70))  /* RW */
#define FIO3MASK1       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x71))  /* RW */
#define FIO3MASK2       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x72))  /* RW */
#define FIO3MASK3       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x73))  /* RW */
#define FIO3MASKL       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x70))  /* RW */
#define FIO3MASKU       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x72))  /* RW */
#define FIO3MASK        (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x70))  /* RW */

#define FIO3PIN0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x74))  /* RW */
#define FIO3PIN1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x75))  /* RW */
#define FIO3PIN2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x76))  /* RW */
#define FIO3PIN3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x77))  /* RW */
#define FIO3PINL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x74))  /* RW */
#define FIO3PINU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x76))  /* RW */
#define FIO3PIN         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x74))  /* RW */

#define FIO3SET0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x78))  /* RW */
#define FIO3SET1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x79))  /* RW */
#define FIO3SET2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x7A))  /* RW */
#define FIO3SET3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x7B))  /* RW */
#define FIO3SETL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x78))  /* RW */
#define FIO3SETU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x7A))  /* RW */
#define FIO3SET         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x78))  /* RW */

#define FIO3CLR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x7C))  /* WO */
#define FIO3CLR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x7D))  /* WO */
#define FIO3CLR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x7E))  /* WO */
#define FIO3CLR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x7F))  /* WO */
#define FIO3CLRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x7C))  /* WO */
#define FIO3CLRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x7E))  /* WO */
#define FIO3CLR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x7C))  /* WO */

#define FIO4DIR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x80))  /* RW */
#define FIO4DIR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x81))  /* RW */
#define FIO4DIR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x82))  /* RW */
#define FIO4DIR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x83))  /* RW */
#define FIO4DIRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x80))  /* RW */
#define FIO4DIRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x82))  /* RW */
#define FIO4DIR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x80))  /* RW */

#define FIO4MASK0       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x90))  /* RW */
#define FIO4MASK1       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x91))  /* RW */
#define FIO4MASK2       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x92))  /* RW */
#define FIO4MASK3       (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x93))  /* RW */
#define FIO4MASKL       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x90))  /* RW */
#define FIO4MASKU       (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x92))  /* RW */
#define FIO4MASK        (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x90))  /* RW */

#define FIO4PIN0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x94))  /* RW */
#define FIO4PIN1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x95))  /* RW */
#define FIO4PIN2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x96))  /* RW */
#define FIO4PIN3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x97))  /* RW */
#define FIO4PINL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x94))  /* RW */
#define FIO4PINU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x96))  /* RW */
#define FIO4PIN         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x94))  /* RW */

#define FIO4SET0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x98))  /* RW */
#define FIO4SET1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x99))  /* RW */
#define FIO4SET2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x9A))  /* RW */
#define FIO4SET3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x9B))  /* RW */
#define FIO4SETL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x98))  /* RW */
#define FIO4SETU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x9A))  /* RW */
#define FIO4SET         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x98))  /* RW */

#define FIO4CLR0        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x9C))  /* WO */
#define FIO4CLR1        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x9D))  /* WO */
#define FIO4CLR2        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x9E))  /* WO */
#define FIO4CLR3        (*(volatile uint8_t  *)(FIO_BASE_ADDR + 0x9F))  /* WO */
#define FIO4CLRL        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x9C))  /* WO */
#define FIO4CLRU        (*(volatile uint16_t *)(FIO_BASE_ADDR + 0x9E))  /* WO */
#define FIO4CLR         (*(volatile uint32_t *)(FIO_BASE_ADDR + 0x9C))  /* WO */


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_FIO {
    union ATTR_PACKED {
        uint32_t  DIR;              /* RW  FIOxBase + 0x00 */
        struct ATTR_PACKED {
            uint16_t    DIRL;       /* RW  FIOxBase + 0x00 */
            uint16_t    DIRU;       /* RW  FIOxBase + 0x02 */
        };
        struct ATTR_PACKED {
            uint8_t     DIR0;       /* RW  FIOxBase + 0x00 */
            uint8_t     DIR1;       /* RW  FIOxBase + 0x01 */
            uint8_t     DIR2;       /* RW  FIOxBase + 0x02 */
            uint8_t     DIR3;       /* RW  FIOxBase + 0x03 */
        };
    };
    uint8_t     __pad_04;
    uint8_t     __pad_05;
    uint8_t     __pad_06;
    uint8_t     __pad_07;
    uint8_t     __pad_08;
    uint8_t     __pad_09;
    uint8_t     __pad_0A;
    uint8_t     __pad_0B;
    uint8_t     __pad_0C;
    uint8_t     __pad_0D;
    uint8_t     __pad_0E;
    uint8_t     __pad_0F;
    union ATTR_PACKED {
        uint32_t  MASK;             /* RW  FIOxBase + 0x10 */
        struct ATTR_PACKED {
            uint16_t    MASKL;      /* RW  FIOxBase + 0x10 */
            uint16_t    MASKU;      /* RW  FIOxBase + 0x12 */
        };
        struct ATTR_PACKED {
            uint8_t     MASK0;      /* RW  FIOxBase + 0x10 */
            uint8_t     MASK1;      /* RW  FIOxBase + 0x11 */
            uint8_t     MASK2;      /* RW  FIOxBase + 0x12 */
            uint8_t     MASK3;      /* RW  FIOxBase + 0x13 */
        };
    };
    union ATTR_PACKED {
        uint32_t  PIN;              /* RW  FIOxBase + 0x14 */
        struct ATTR_PACKED {
            uint16_t    PINL;       /* RW  FIOxBase + 0x14 */
            uint16_t    PINU;       /* RW  FIOxBase + 0x16 */
        };
        struct ATTR_PACKED {
            uint8_t     PIN0;       /* RW  FIOxBase + 0x14 */
            uint8_t     PIN1;       /* RW  FIOxBase + 0x15 */
            uint8_t     PIN2;       /* RW  FIOxBase + 0x16 */
            uint8_t     PIN3;       /* RW  FIOxBase + 0x17 */
        };
    };
    union ATTR_PACKED {
        uint32_t  SET;              /* RW  FIOxBase + 0x18 */
        struct ATTR_PACKED {
            uint16_t    SETL;       /* RW  FIOxBase + 0x18 */
            uint16_t    SETU;       /* RW  FIOxBase + 0x1A */
        };
        struct ATTR_PACKED {
            uint8_t     SET0;       /* RW  FIOxBase + 0x18 */
            uint8_t     SET1;       /* RW  FIOxBase + 0x19 */
            uint8_t     SET2;       /* RW  FIOxBase + 0x1A */
            uint8_t     SET3;       /* RW  FIOxBase + 0x1B */
        };
    };
    union ATTR_PACKED {
        uint32_t  CLR;              /* WO  FIOxBase + 0x1C */
        struct ATTR_PACKED {
            uint16_t    CLRL;       /* WO  FIOxBase + 0x1C */
            uint16_t    CLRU;       /* WO  FIOxBase + 0x1E */
        };
        struct ATTR_PACKED {
            uint8_t     CLR0;       /* WO  FIOxBase + 0x1C */
            uint8_t     CLR1;       /* WO  FIOxBase + 0x1D */
            uint8_t     CLR2;       /* WO  FIOxBase + 0x1E */
            uint8_t     CLR3;       /* WO  FIOxBase + 0x1F */
        };
    };
}  LPC24XX_FIO_t, *P_LPC24XX_FIO_t;

#define P_FIO0_REGS     ((LPC24XX_FIO_t *)(FIO_BASE_ADDR + 0x00))
#define P_FIO1_REGS     ((LPC24XX_FIO_t *)(FIO_BASE_ADDR + 0x20))
#define P_FIO2_REGS     ((LPC24XX_FIO_t *)(FIO_BASE_ADDR + 0x40))
#define P_FIO3_REGS     ((LPC24XX_FIO_t *)(FIO_BASE_ADDR + 0x60))
#define P_FIO4_REGS     ((LPC24XX_FIO_t *)(FIO_BASE_ADDR + 0x80))


#endif /* __GPIO_H */
