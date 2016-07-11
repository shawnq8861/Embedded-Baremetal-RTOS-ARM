#ifndef __VIC_H
#define __VIC_H


#define LPC2478_VIC_BASE    (0xFFFFF000)
#define VICIRQStatus        (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x000))  /* RO */
#define VICFIQStatus        (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x004))  /* RO */
#define VICRawIntr          (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x008))  /* RO */
#define VICIntSelect        (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x00C))  /* RW */
#define VICIntEnable        (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x010))  /* RW */
#define VICIntEnClear       (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x014))  /* WO */
#define VICSoftInt          (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x018))  /* RW */
#define VICSoftIntClear     (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x01C))  /* WO */
#define VICProtection       (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x020))  /* RW */
#define VICSWPriorityMask   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x024))  /* RW */
#define VICVectAddr0        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x100))  /* RW */
#define VICVectAddr1        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x104))  /* RW */
#define VICVectAddr2        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x108))  /* RW */
#define VICVectAddr3        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x10C))  /* RW */
#define VICVectAddr4        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x110))  /* RW */
#define VICVectAddr5        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x114))  /* RW */
#define VICVectAddr6        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x118))  /* RW */
#define VICVectAddr7        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x11C))  /* RW */
#define VICVectAddr8        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x120))  /* RW */
#define VICVectAddr9        (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x124))  /* RW */
#define VICVectAddr10       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x128))  /* RW */
#define VICVectAddr11       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x12C))  /* RW */
#define VICVectAddr12       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x130))  /* RW */
#define VICVectAddr13       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x134))  /* RW */
#define VICVectAddr14       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x138))  /* RW */
#define VICVectAddr15       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x13C))  /* RW */
#define VICVectAddr16       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x140))  /* RW */
#define VICVectAddr17       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x144))  /* RW */
#define VICVectAddr18       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x148))  /* RW */
#define VICVectAddr19       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x14C))  /* RW */
#define VICVectAddr20       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x150))  /* RW */
#define VICVectAddr21       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x154))  /* RW */
#define VICVectAddr22       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x158))  /* RW */
#define VICVectAddr23       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x15C))  /* RW */
#define VICVectAddr24       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x160))  /* RW */
#define VICVectAddr25       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x164))  /* RW */
#define VICVectAddr26       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x168))  /* RW */
#define VICVectAddr27       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x16C))  /* RW */
#define VICVectAddr28       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x170))  /* RW */
#define VICVectAddr29       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x174))  /* RW */
#define VICVectAddr30       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x178))  /* RW */
#define VICVectAddr31       (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0x17C))  /* RW */
#define VICVectPriority0    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x200))  /* RW */
#define VICVectPriority1    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x204))  /* RW */
#define VICVectPriority2    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x208))  /* RW */
#define VICVectPriority3    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x20C))  /* RW */
#define VICVectPriority4    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x210))  /* RW */
#define VICVectPriority5    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x214))  /* RW */
#define VICVectPriority6    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x218))  /* RW */
#define VICVectPriority7    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x21C))  /* RW */
#define VICVectPriority8    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x220))  /* RW */
#define VICVectPriority9    (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x224))  /* RW */
#define VICVectPriority10   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x228))  /* RW */
#define VICVectPriority11   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x22C))  /* RW */
#define VICVectPriority12   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x230))  /* RW */
#define VICVectPriority13   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x234))  /* RW */
#define VICVectPriority14   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x238))  /* RW */
#define VICVectPriority15   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x23C))  /* RW */
#define VICVectPriority16   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x240))  /* RW */
#define VICVectPriority17   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x244))  /* RW */
#define VICVectPriority18   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x248))  /* RW */
#define VICVectPriority19   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x24C))  /* RW */
#define VICVectPriority20   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x250))  /* RW */
#define VICVectPriority21   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x254))  /* RW */
#define VICVectPriority22   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x258))  /* RW */
#define VICVectPriority23   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x25C))  /* RW */
#define VICVectPriority24   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x260))  /* RW */
#define VICVectPriority25   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x264))  /* RW */
#define VICVectPriority26   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x268))  /* RW */
#define VICVectPriority27   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x26C))  /* RW */
#define VICVectPriority28   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x270))  /* RW */
#define VICVectPriority29   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x274))  /* RW */
#define VICVectPriority30   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x278))  /* RW */
#define VICVectPriority31   (*(volatile uint32_t *)(LPC2478_VIC_BASE + 0x27C))  /* RW */
#define VICAddress          (*(volatile pfunction_t *)(LPC2478_VIC_BASE + 0xF00))  /* RW */


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_VIC {
    uint32_t    IRQStatus;              /* RO  Offset 0x000 */
    uint32_t    FIQStatus;              /* RO  Offset 0x004 */
    uint32_t    RawIntr;                /* RO  Offset 0x008 */
    uint32_t    IntSelect;              /* RW  Offset 0x00C */
    uint32_t    IntEnable;              /* RW  Offset 0x010 */
    uint32_t    IntEnClear;             /* WO  Offset 0x014 */
    uint32_t    SoftInt;                /* RW  Offset 0x018 */
    uint32_t    SoftIntClear;           /* WO  Offset 0x01C */
    uint32_t    Protection;             /* RW  Offset 0x020 */
    uint32_t    SWPriorityMask;         /* RW  Offset 0x024 */
    uint32_t    __PriorityDaisy;        /* RW  Offset 0x028 Reserved */
    uint32_t    __Pad02C_0FF[53];
    union ATTR_PACKED {
      pfunction_t      VectAddr[32];       /* RW Offset 0x100, array_size 32*4=128=0x80  */
      struct ATTR_PACKED {
        pfunction_t    VectAddr0;              /* RW  Offset 0x100 */
        pfunction_t    VectAddr1;              /* RW  Offset 0x104 */
        pfunction_t    VectAddr2;              /* RW  Offset 0x108 */
        pfunction_t    VectAddr3;              /* RW  Offset 0x10C */
        pfunction_t    VectAddr4;              /* RW  Offset 0x110 */
        pfunction_t    VectAddr5;              /* RW  Offset 0x114 */
        pfunction_t    VectAddr6;              /* RW  Offset 0x118 */
        pfunction_t    VectAddr7;              /* RW  Offset 0x11C */
        pfunction_t    VectAddr8;              /* RW  Offset 0x120 */
        pfunction_t    VectAddr9;              /* RW  Offset 0x124 */
        pfunction_t    VectAddr10;             /* RW  Offset 0x128 */
        pfunction_t    VectAddr11;             /* RW  Offset 0x12C */
        pfunction_t    VectAddr12;             /* RW  Offset 0x130 */
        pfunction_t    VectAddr13;             /* RW  Offset 0x134 */
        pfunction_t    VectAddr14;             /* RW  Offset 0x138 */
        pfunction_t    VectAddr15;             /* RW  Offset 0x13C */
        pfunction_t    VectAddr16;             /* RW  Offset 0x140 */
        pfunction_t    VectAddr17;             /* RW  Offset 0x144 */
        pfunction_t    VectAddr18;             /* RW  Offset 0x148 */
        pfunction_t    VectAddr19;             /* RW  Offset 0x14C */
        pfunction_t    VectAddr20;             /* RW  Offset 0x150 */
        pfunction_t    VectAddr21;             /* RW  Offset 0x154 */
        pfunction_t    VectAddr22;             /* RW  Offset 0x158 */
        pfunction_t    VectAddr23;             /* RW  Offset 0x15C */
        pfunction_t    VectAddr24;             /* RW  Offset 0x160 */
        pfunction_t    VectAddr25;             /* RW  Offset 0x164 */
        pfunction_t    VectAddr26;             /* RW  Offset 0x168 */
        pfunction_t    VectAddr27;             /* RW  Offset 0x16C */
        pfunction_t    VectAddr28;             /* RW  Offset 0x170 */
        pfunction_t    VectAddr29;             /* RW  Offset 0x174 */
        pfunction_t    VectAddr30;             /* RW  Offset 0x178 */
        pfunction_t    VectAddr31;             /* RW  Offset 0x17C */
      };
    };
    uint32_t    __pad180_1FF[32];
    union ATTR_PACKED {
      uint32_t      VectPriority[32];       /* RW Offset 0x200, array_size 32*4=128=0x80  */
      struct ATTR_PACKED {
        uint32_t    VectPriority0;          /* RW  Offset 0x200 */
        uint32_t    VectPriority1;          /* RW  Offset 0x204 */
        uint32_t    VectPriority2;          /* RW  Offset 0x208 */
        uint32_t    VectPriority3;          /* RW  Offset 0x20C */
        uint32_t    VectPriority4;          /* RW  Offset 0x210 */
        uint32_t    VectPriority5;          /* RW  Offset 0x214 */
        uint32_t    VectPriority6;          /* RW  Offset 0x218 */
        uint32_t    VectPriority7;          /* RW  Offset 0x21C */
        uint32_t    VectPriority8;          /* RW  Offset 0x220 */
        uint32_t    VectPriority9;          /* RW  Offset 0x224 */
        uint32_t    VectPriority10;         /* RW  Offset 0x228 */
        uint32_t    VectPriority11;         /* RW  Offset 0x22C */
        uint32_t    VectPriority12;         /* RW  Offset 0x230 */
        uint32_t    VectPriority13;         /* RW  Offset 0x234 */
        uint32_t    VectPriority14;         /* RW  Offset 0x238 */
        uint32_t    VectPriority15;         /* RW  Offset 0x23C */
        uint32_t    VectPriority16;         /* RW  Offset 0x240 */
        uint32_t    VectPriority17;         /* RW  Offset 0x244 */
        uint32_t    VectPriority18;         /* RW  Offset 0x248 */
        uint32_t    VectPriority19;         /* RW  Offset 0x24C */
        uint32_t    VectPriority20;         /* RW  Offset 0x250 */
        uint32_t    VectPriority21;         /* RW  Offset 0x254 */
        uint32_t    VectPriority22;         /* RW  Offset 0x258 */
        uint32_t    VectPriority23;         /* RW  Offset 0x25C */
        uint32_t    VectPriority24;         /* RW  Offset 0x260 */
        uint32_t    VectPriority25;         /* RW  Offset 0x264 */
        uint32_t    VectPriority26;         /* RW  Offset 0x268 */
        uint32_t    VectPriority27;         /* RW  Offset 0x26C */
        uint32_t    VectPriority28;         /* RW  Offset 0x270 */
        uint32_t    VectPriority29;         /* RW  Offset 0x274 */
        uint32_t    VectPriority30;         /* RW  Offset 0x278 */
        uint32_t    VectPriority31;         /* RW  Offset 0x27C */
      };
    };
    uint32_t    __pad280_EFF[800];
    pfunction_t    Address;                /* RW  Offset 0xF00 Reserved */
    uint32_t    __padF04_FDF[55];
    uint32_t    _VICPERIPHID0;          /* RO  Offset 0xFE0 Reserved */
    uint32_t    _VICPERIPHID1;          /* RO  Offset 0xFE4 Reserved */
    uint32_t    _VICPERIPHID2;          /* RO  Offset 0xFE8 Reserved */
    uint32_t    _VICPERIPHID3;          /* RO  Offset 0xFEC Reserved */
    uint32_t    _VICPCELLID0;           /* RO  Offset 0xFF0 Reserved */
    uint32_t    _VICPCELLID1;           /* RO  Offset 0xFF4 Reserved */
    uint32_t    _VICPCELLID2;           /* RO  Offset 0xFF8 Reserved */
    uint32_t    _VICPCELLID3;           /* RO  Offset 0xFFC Reserved */

}  LPC24XX_VIC_t, *P_LPC24XX_VIC_t;

#define P_VIC_REGS ((LPC24XX_VIC_t *)LPC2478_VIC_BASE)


#define VIC_CH0_WDT         (0)
#define VIC_CH1_SOFTINT     (1)
#define VIC_CH2_ARMCORE0    (2)
#define VIC_CH3_ARMCORE1    (3)
#define VIC_CH4_TIMER0      (4)
#define VIC_CH5_TIMER1      (5)
#define VIC_CH6_UART0       (6)
#define VIC_CH7_UART1       (7)
#define VIC_CH8_PWM1        (8)
#define VIC_CH9_I2C0        (9)
#define VIC_CH10_SSP0       (10)
#define VIC_CH10_SPI        (10)
#define VIC_CH11_SSP1       (11)
#define VIC_CH12_PLL        (12)
#define VIC_CH13_RTC        (13)
#define VIC_CH14_EINT0      (14)
#define VIC_CH15_EINT1      (15)
#define VIC_CH16_EINT2      (16)
#define VIC_CH17_EINT3      (17)
#define VIC_CH18_AD0        (18)
#define VIC_CH19_I2C1       (19)
#define VIC_CH20_BOD        (20)
#define VIC_CH21_ETHERNET   (21)
#define VIC_CH22_USB        (22)
#define VIC_CH23_CAN1_2     (23)
#define VIC_CH24_SD_MMC     (24)
#define VIC_CH25_GPDMA      (25)
#define VIC_CH26_TIMER2     (26)
#define VIC_CH27_TIMER3     (27)
#define VIC_CH28_UART2      (28)
#define VIC_CH29_UART3      (29)
#define VIC_CH30_I2C2       (30)
#define VIC_CH31_I2S        (31)

typedef enum {IntSelectIRQ=0, IntSelectFIQ} arminterrupt_t;

#define NUM_VIC_VECT_ADDR_REGS      (32)
#define NUM_VIC_VECT_PRIORITY_REGS  (32)

#define VIC_VECT_PRIORITY_HIGHEST   0
#define VIC_VECT_PRIORITY_LOWEST    15

#define VICSWPRIORITYREGISTERMASK 0x0000FFFF

#define VIC_PROTECTION_PRIVILEGED_MODE (1<<0)
#define VIC_PROTECTION_USER_OR_PRIVILEGED_MODE (0<<0)

#endif /* __VIC_H */
