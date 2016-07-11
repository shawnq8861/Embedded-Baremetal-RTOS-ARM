#ifndef __SCB_H
#define __SCB_H


#define LPC2478_SCB_BASE        (0xE01FC000)
/* TODO extra credit fix name space clash, rename struct members */

#if 0
#define MAMCR           (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x000))  /* RW */
#define MAMTIM          (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x004))  /* RW */

#define MEMMAP          (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x040))  /* RW */

#define PLLCON          (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x080))  /* RW */
#define PLLCFG          (*(volatile uint32_t *)(LPC2478_SCB_BASE + 0x084))  /* RW */
#define PLLSTAT         (*(volatile uint32_t *)(LPC2478_SCB_BASE + 0x088))  /* RO */
#define PLLFEED         (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x08C))  /* WO */

#define PCON            (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x0C0))  /* RW */
#define PCONP           (*(volatile uint32_t *)(LPC2478_SCB_BASE + 0x0C4))  /* RW */

#define CCLKCFG         (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x104))  /* RW */
#define USBCLKCFG       (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x108))  /* RW */
#define CLKSRCSEL       (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x10C))  /* RW */

#define EXTINT          (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x140))  /* RW */
#define INTWAKE         (*(volatile uint16_t *)(LPC2478_SCB_BASE + 0x144))  /* RW */
#define EXTMODE         (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x148))  /* RW */
#define EXTPOLAR        (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x14C))  /* RW */

#define RSID            (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x180))  /* RW */
#define CSPR            (*(volatile uint32_t *)(LPC2478_SCB_BASE + 0x184))  /* WO */
#define AHBCFG1         (*(volatile uint32_t *)(LPC2478_SCB_BASE + 0x188))  /* RW */
#define AHBCFG2         (*(volatile uint32_t *)(LPC2478_SCB_BASE + 0x18C))  /* RW */

#define SCS             (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x1A0))  /* RW */
#define IRCTRIM         (*(volatile uint16_t *)(LPC2478_SCB_BASE + 0x1A4))  /* RW */
#define PCLKSEL0        (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x1A8))  /* RW */
#define PCLKSEL1        (*(volatile uint8_t  *)(LPC2478_SCB_BASE + 0x1AC))  /* RW */

#else


typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_SCB {
                                /* Access Offset */
    uint8_t   MAMCR;            /* RW     0x000 */
    uint8_t   __pad_001;
    uint8_t   __pad_002;
    uint8_t   __pad_003;
    uint8_t   MAMTIM;           /* RW     0x004 */
    uint8_t   __pad_005;
    uint8_t   __pad_006;
    uint8_t   __pad_007;
    uint8_t   __pad_008;
    uint8_t   __pad_009;
    uint8_t   __pad_00A;
    uint8_t   __pad_00B;
    uint8_t   __pad_00C;
    uint8_t   __pad_00D;
    uint8_t   __pad_00E;
    uint8_t   __pad_00F;
    uint8_t   __pad_010;
    uint8_t   __pad_011;
    uint8_t   __pad_012;
    uint8_t   __pad_013;
    uint8_t   __pad_014;
    uint8_t   __pad_015;
    uint8_t   __pad_016;
    uint8_t   __pad_017;
    uint8_t   __pad_018;
    uint8_t   __pad_019;
    uint8_t   __pad_01A;
    uint8_t   __pad_01B;
    uint8_t   __pad_01C;
    uint8_t   __pad_01D;
    uint8_t   __pad_01E;
    uint8_t   __pad_01F;
    uint8_t   __pad_020;
    uint8_t   __pad_021;
    uint8_t   __pad_022;
    uint8_t   __pad_023;
    uint8_t   __pad_024;
    uint8_t   __pad_025;
    uint8_t   __pad_026;
    uint8_t   __pad_027;
    uint8_t   __pad_028;
    uint8_t   __pad_029;
    uint8_t   __pad_02A;
    uint8_t   __pad_02B;
    uint8_t   __pad_02C;
    uint8_t   __pad_02D;
    uint8_t   __pad_02E;
    uint8_t   __pad_02F;
    uint8_t   __pad_030;
    uint8_t   __pad_031;
    uint8_t   __pad_032;
    uint8_t   __pad_033;
    uint8_t   __pad_034;
    uint8_t   __pad_035;
    uint8_t   __pad_036;
    uint8_t   __pad_037;
    uint8_t   __pad_038;
    uint8_t   __pad_039;
    uint8_t   __pad_03A;
    uint8_t   __pad_03B;
    uint8_t   __pad_03C;
    uint8_t   __pad_03D;
    uint8_t   __pad_03E;
    uint8_t   __pad_03F;
    uint8_t   MEMMAP;           /* RW     0x040 */
    uint8_t   __pad_041;
    uint8_t   __pad_042;
    uint8_t   __pad_043;
    uint8_t   __pad_044;
    uint8_t   __pad_045;
    uint8_t   __pad_046;
    uint8_t   __pad_047;
    uint8_t   __pad_048;
    uint8_t   __pad_049;
    uint8_t   __pad_04A;
    uint8_t   __pad_04B;
    uint8_t   __pad_04C;
    uint8_t   __pad_04D;
    uint8_t   __pad_04E;
    uint8_t   __pad_04F;
    uint8_t   __pad_050;
    uint8_t   __pad_051;
    uint8_t   __pad_052;
    uint8_t   __pad_053;
    uint8_t   __pad_054;
    uint8_t   __pad_055;
    uint8_t   __pad_056;
    uint8_t   __pad_057;
    uint8_t   __pad_058;
    uint8_t   __pad_059;
    uint8_t   __pad_05A;
    uint8_t   __pad_05B;
    uint8_t   __pad_05C;
    uint8_t   __pad_05D;
    uint8_t   __pad_05E;
    uint8_t   __pad_05F;
    uint8_t   __pad_060;
    uint8_t   __pad_061;
    uint8_t   __pad_062;
    uint8_t   __pad_063;
    uint8_t   __pad_064;
    uint8_t   __pad_065;
    uint8_t   __pad_066;
    uint8_t   __pad_067;
    uint8_t   __pad_068;
    uint8_t   __pad_069;
    uint8_t   __pad_06A;
    uint8_t   __pad_06B;
    uint8_t   __pad_06C;
    uint8_t   __pad_06D;
    uint8_t   __pad_06E;
    uint8_t   __pad_06F;
    uint8_t   __pad_070;
    uint8_t   __pad_071;
    uint8_t   __pad_072;
    uint8_t   __pad_073;
    uint8_t   __pad_074;
    uint8_t   __pad_075;
    uint8_t   __pad_076;
    uint8_t   __pad_077;
    uint8_t   __pad_078;
    uint8_t   __pad_079;
    uint8_t   __pad_07A;
    uint8_t   __pad_07B;
    uint8_t   __pad_07C;
    uint8_t   __pad_07D;
    uint8_t   __pad_07E;
    uint8_t   __pad_07F;
    uint8_t   PLLCON;           /* RW     0x080 */
    uint8_t   __pad_081;
    uint8_t   __pad_082;
    uint8_t   __pad_083;
    uint32_t  PLLCFG;           /* RW     0x084 */
    uint32_t  PLLSTAT;          /* R      0x088 */
    uint8_t   PLLFEED;          /*  W     0x08C */
    uint8_t   __pad_08D;
    uint8_t   __pad_08E;
    uint8_t   __pad_08F;
    uint8_t   __pad_090;
    uint8_t   __pad_091;
    uint8_t   __pad_092;
    uint8_t   __pad_093;
    uint8_t   __pad_094;
    uint8_t   __pad_095;
    uint8_t   __pad_096;
    uint8_t   __pad_097;
    uint8_t   __pad_098;
    uint8_t   __pad_099;
    uint8_t   __pad_09A;
    uint8_t   __pad_09B;
    uint8_t   __pad_09C;
    uint8_t   __pad_09D;
    uint8_t   __pad_09E;
    uint8_t   __pad_09F;
    uint8_t   __pad_0A0;
    uint8_t   __pad_0A1;
    uint8_t   __pad_0A2;
    uint8_t   __pad_0A3;
    uint8_t   __pad_0A4;
    uint8_t   __pad_0A5;
    uint8_t   __pad_0A6;
    uint8_t   __pad_0A7;
    uint8_t   __pad_0A8;
    uint8_t   __pad_0A9;
    uint8_t   __pad_0AA;
    uint8_t   __pad_0AB;
    uint8_t   __pad_0AC;
    uint8_t   __pad_0AD;
    uint8_t   __pad_0AE;
    uint8_t   __pad_0AF;
    uint8_t   __pad_0B0;
    uint8_t   __pad_0B1;
    uint8_t   __pad_0B2;
    uint8_t   __pad_0B3;
    uint8_t   __pad_0B4;
    uint8_t   __pad_0B5;
    uint8_t   __pad_0B6;
    uint8_t   __pad_0B7;
    uint8_t   __pad_0B8;
    uint8_t   __pad_0B9;
    uint8_t   __pad_0BA;
    uint8_t   __pad_0BB;
    uint8_t   __pad_0BC;
    uint8_t   __pad_0BD;
    uint8_t   __pad_0BE;
    uint8_t   __pad_0BF;
    uint8_t   PCON;             /* RW     0x0C0 */
    uint8_t   __pad_0C1;
    uint8_t   __pad_0C2;
    uint8_t   __pad_0C3;
    uint32_t  PCONP;            /* RW     0x0C4 */
    uint8_t   __pad_0C8;
    uint8_t   __pad_0C9;
    uint8_t   __pad_0CA;
    uint8_t   __pad_0CB;
    uint8_t   __pad_0CC;
    uint8_t   __pad_0CD;
    uint8_t   __pad_0CE;
    uint8_t   __pad_0CF;
    uint8_t   __pad_0D0;
    uint8_t   __pad_0D1;
    uint8_t   __pad_0D2;
    uint8_t   __pad_0D3;
    uint8_t   __pad_0D4;
    uint8_t   __pad_0D5;
    uint8_t   __pad_0D6;
    uint8_t   __pad_0D7;
    uint8_t   __pad_0D8;
    uint8_t   __pad_0D9;
    uint8_t   __pad_0DA;
    uint8_t   __pad_0DB;
    uint8_t   __pad_0DC;
    uint8_t   __pad_0DD;
    uint8_t   __pad_0DE;
    uint8_t   __pad_0DF;
    uint8_t   __pad_0E0;
    uint8_t   __pad_0E1;
    uint8_t   __pad_0E2;
    uint8_t   __pad_0E3;
    uint8_t   __pad_0E4;
    uint8_t   __pad_0E5;
    uint8_t   __pad_0E6;
    uint8_t   __pad_0E7;
    uint8_t   __pad_0E8;
    uint8_t   __pad_0E9;
    uint8_t   __pad_0EA;
    uint8_t   __pad_0EB;
    uint8_t   __pad_0EC;
    uint8_t   __pad_0ED;
    uint8_t   __pad_0EE;
    uint8_t   __pad_0EF;
    uint8_t   __pad_0F0;
    uint8_t   __pad_0F1;
    uint8_t   __pad_0F2;
    uint8_t   __pad_0F3;
    uint8_t   __pad_0F4;
    uint8_t   __pad_0F5;
    uint8_t   __pad_0F6;
    uint8_t   __pad_0F7;
    uint8_t   __pad_0F8;
    uint8_t   __pad_0F9;
    uint8_t   __pad_0FA;
    uint8_t   __pad_0FB;
    uint8_t   __pad_0FC;
    uint8_t   __pad_0FD;
    uint8_t   __pad_0FE;
    uint8_t   __pad_0FF;
    uint8_t   __pad_100;
    uint8_t   __pad_101;
    uint8_t   __pad_102;
    uint8_t   __pad_103;
    uint8_t   CCLKCFG;          /* RW     0x104 */
    uint8_t   __pad_105;
    uint8_t   __pad_106;
    uint8_t   __pad_107;
    uint8_t   USBCLKCFG;        /* RW     0x108 */
    uint8_t   __pad_109;
    uint8_t   __pad_10A;
    uint8_t   __pad_10B;
    uint8_t   CLKSRCSEL;        /* RW     0x10C */
    uint8_t   __pad_10D;
    uint8_t   __pad_10E;
    uint8_t   __pad_10F;
    uint8_t   __pad_110;
    uint8_t   __pad_111;
    uint8_t   __pad_112;
    uint8_t   __pad_113;
    uint8_t   __pad_114;
    uint8_t   __pad_115;
    uint8_t   __pad_116;
    uint8_t   __pad_117;
    uint8_t   __pad_118;
    uint8_t   __pad_119;
    uint8_t   __pad_11A;
    uint8_t   __pad_11B;
    uint8_t   __pad_11C;
    uint8_t   __pad_11D;
    uint8_t   __pad_11E;
    uint8_t   __pad_11F;
    uint8_t   __pad_120;
    uint8_t   __pad_121;
    uint8_t   __pad_122;
    uint8_t   __pad_123;
    uint8_t   __pad_124;
    uint8_t   __pad_125;
    uint8_t   __pad_126;
    uint8_t   __pad_127;
    uint8_t   __pad_128;
    uint8_t   __pad_129;
    uint8_t   __pad_12A;
    uint8_t   __pad_12B;
    uint8_t   __pad_12C;
    uint8_t   __pad_12D;
    uint8_t   __pad_12E;
    uint8_t   __pad_12F;
    uint8_t   __pad_130;
    uint8_t   __pad_131;
    uint8_t   __pad_132;
    uint8_t   __pad_133;
    uint8_t   __pad_134;
    uint8_t   __pad_135;
    uint8_t   __pad_136;
    uint8_t   __pad_137;
    uint8_t   __pad_138;
    uint8_t   __pad_139;
    uint8_t   __pad_13A;
    uint8_t   __pad_13B;
    uint8_t   __pad_13C;
    uint8_t   __pad_13D;
    uint8_t   __pad_13E;
    uint8_t   __pad_13F;
    uint8_t   EXTINT;           /* RW     0x140 */
    uint8_t   __pad_141;
    uint8_t   __pad_142;
    uint8_t   __pad_143;
    uint16_t  INTWAKE;          /* RW     0x144 */
    uint8_t   __pad_146;
    uint8_t   __pad_147;
    uint8_t   EXTMODE;          /* RW     0x148 */
    uint8_t   __pad_149;
    uint8_t   __pad_14A;
    uint8_t   __pad_14B;
    uint8_t   EXTPOLAR;         /* RW     0x14C */
    uint8_t   __pad_14D;
    uint8_t   __pad_14E;
    uint8_t   __pad_14F;
    uint8_t   __pad_150;
    uint8_t   __pad_151;
    uint8_t   __pad_152;
    uint8_t   __pad_153;
    uint8_t   __pad_154;
    uint8_t   __pad_155;
    uint8_t   __pad_156;
    uint8_t   __pad_157;
    uint8_t   __pad_158;
    uint8_t   __pad_159;
    uint8_t   __pad_15A;
    uint8_t   __pad_15B;
    uint8_t   __pad_15C;
    uint8_t   __pad_15D;
    uint8_t   __pad_15E;
    uint8_t   __pad_15F;
    uint8_t   __pad_160;
    uint8_t   __pad_161;
    uint8_t   __pad_162;
    uint8_t   __pad_163;
    uint8_t   __pad_164;
    uint8_t   __pad_165;
    uint8_t   __pad_166;
    uint8_t   __pad_167;
    uint8_t   __pad_168;
    uint8_t   __pad_169;
    uint8_t   __pad_16A;
    uint8_t   __pad_16B;
    uint8_t   __pad_16C;
    uint8_t   __pad_16D;
    uint8_t   __pad_16E;
    uint8_t   __pad_16F;
    uint8_t   __pad_170;
    uint8_t   __pad_171;
    uint8_t   __pad_172;
    uint8_t   __pad_173;
    uint8_t   __pad_174;
    uint8_t   __pad_175;
    uint8_t   __pad_176;
    uint8_t   __pad_177;
    uint8_t   __pad_178;
    uint8_t   __pad_179;
    uint8_t   __pad_17A;
    uint8_t   __pad_17B;
    uint8_t   __pad_17C;
    uint8_t   __pad_17D;
    uint8_t   __pad_17E;
    uint8_t   __pad_17F;
    uint8_t   RSID;             /* RW     0x180 */
    uint8_t   __pad_181;
    uint8_t   __pad_182;
    uint8_t   __pad_183;
    uint32_t  CSPR;             /* WO     0x184 */
    uint32_t  AHBCFG1;          /* RW     0x188 */
    uint32_t  AHBCFG2;          /* RW     0x18C */
    uint8_t   __pad_190;
    uint8_t   __pad_191;
    uint8_t   __pad_192;
    uint8_t   __pad_193;
    uint8_t   __pad_194;
    uint8_t   __pad_195;
    uint8_t   __pad_196;
    uint8_t   __pad_197;
    uint8_t   __pad_198;
    uint8_t   __pad_199;
    uint8_t   __pad_19A;
    uint8_t   __pad_19B;
    uint8_t   __pad_19C;
    uint8_t   __pad_19D;
    uint8_t   __pad_19E;
    uint8_t   __pad_19F;
    uint32_t  SCS;              /* RW     0x1A0 */
    uint16_t  IRCTRIM;          /* RW     0x1A4 */
    uint8_t   __pad_1A6;
    uint8_t   __pad_1A7;
    uint32_t  PCLKSEL0;         /* RW     0x1A8 */
    uint32_t  PCLKSEL1;         /* RW     0x1AC */
} LPC24XX_SCB_t, *P_LPC24XX_SCB_t;

#define P_SCB_REGS ((LPC24XX_SCB_t *)LPC2478_SCB_BASE)

#endif /* */

/*
 * MEMMAP
 */
#define BOOTLOADERMODE     0x0
#define USERFLASHMODE      0x1
#define USERRAMMODE        0x2
#define EXTERNALMEMORYMODE 0x3

/* MAM */
#define MAMCR_OFF          0
#define MAMCR_PARTIAL      1
#define MAMCR_FULL         2
//#define MAMTIM_CYCLES      (((CCLK)+19999999)/20000000)
#define MAMTIM_AUTOCFG     0
#define MAMTIM_1_CLK       1
#define MAMTIM_2_CLK       2
#define MAMTIM_3_CLK       3
#define MAMTIM_4_CLK       4
#define MAMTIM_5_CLK       5
#define MAMTIM_6_CLK       6
#define MAMTIM_7_CLK       7
#define MAMTIM_MAX_CLK     7



#define CCLK_DIV_1         (1)
#define CCLK_DIV_2         (2)
#define CCLK_DIV_4         (4)
#define CCLK_DIV_6         (6)
#define CCLK_DIV_8         (8)
#define CCLK_DIV_10        (10)
#define CCLK_DIV_12        (12)
#define CCLK_DIV_14        (14)
#define CCLK_DIV_16        (16)
#define CCLK_DIV_18        (18)
#define CCLK_DIV_20        (20)
#define CCLK_DIV_22        (22)
#define CCLK_DIV_24        (24)
#define CCLK_DIV_26        (26)
#define CCLK_DIV_28        (28)
//#define CCLK               (FCCO/CCLK_DIV)
//#define CCLKCFG_VALUE      (CCLK_DIV-1)
//#define PBSD               1
//#define PCLK               (CCLK / PBSD)


#define FOSC_INT_RC        (4000000)

#define CLKSRC_INT_RC      (0x00)
#define CLKSRC_MAIN_OSC    (0x01)
#define CLKSRC_MIN_RTC     (0x02)
#define CLKSRCSEL_MASK     (0x03)

#define SCS_GPIOM          (1<<0)
#define SCS_EMC_RST_DIS    (1<<1)
#define SCS_MCIPWR         (1<<3)
#define SCS_OSCRANGE       (1<<4)
#define SCS_OSCEN          (1<<5)
#define SCS_OSCSTAT        (1<<6)

//#define FCCO               (FOSC*PLL_MUL*2/PLL_DIV)
#define PLLCON_PLLE        (1<<0)
#define PLLCON_PLLC        (1<<1)
#define PLLSTAT_PLLE       (1<<24)
#define PLLSTAT_PLLC       (1<<25)
#define PLLSTAT_PLOCK      (1<<26)
#define PLLSTAT_MSEL_MASK      (0x00007FFF)
#define PLLSTAT_NSEL_MASK      (0x00FF0000)

#define PDIV_1             0x1
#define PDIV_2             0x2
#define PDIV_4             0x0
#define PDIV_6             0x3
#define PDIV_8             0x3

#define CLR_PCLK(per) ((0x3) << (per))
#define SET_PCLK(per,div) ((div) << (per))
#define GET_PCLK_SEL(PCLKSELn,per)     ( ( (PCLKSELn) >> (per) ) & 0x00000003 )

#define PCLK_WDT           0
#define PCLK_TIMER0        2
#define PCLK_TIMER1        4
#define PCLK_UART0         6
#define PCLK_UART1         8
#define PCLK_PWM1          12
#define PCLK_I2C0          14
#define PCLK_SPI           16
#define PCLK_RTC           18
#define PCLK_SSP1          20
#define PCLK_DAC           22
#define PCLK_ADC           24
#define PCLK_CAN1          26
#define PCLK_CAN2          28
#define PCLK_ACF           30

#define PCLK_BAT_RAM       0
#define PCLK_GPIO          2
#define PCLK_PCB           4
#define PCLK_I2C1          6
#define PCLK_SSP0          10
#define PCLK_TIMER2        12
#define PCLK_TIMER3        14
#define PCLK_UART2         16
#define PCLK_UART3         18
#define PCLK_I2C2          20
#define PCLK_I2S           22
#define PCLK_MCI           24
#define PCLK_SYSCON        28

//#define PCONP_BIT0        // Reserved, write zero, read undefined
#define PCONP_PCTIM0        (1<<1)
#define PCONP_PCTIM1        (1<<2)
#define PCONP_PCUART0       (1<<3)
#define PCONP_PCUART1       (1<<4)
#define PCONP_PCPWM0        (1<<5)
#define PCONP_PCPWM1        (1<<6)
#define PCONP_PCI2C0        (1<<7)
#define PCONP_PCSPI         (1<<8)
#define PCONP_PCRTC         (1<<9)
#define PCONP_PCSSP1        (1<<10)
#define PCONP_PCEMC         (1<<11)
#define PCONP_PCAD          (1<<12)
#define PCONP_PCCAN1        (1<<13)
#define PCONP_PCCAN2        (1<<14)
//#define PCONP_BIT15       // Reserved, write zero, read undefined
//#define PCONP_BIT16       // Reserved, write zero, read undefined
//#define PCONP_BIT17       // Reserved, write zero, read undefined
//#define PCONP_BIT18       // Reserved, write zero, read undefined
#define PCONP_PCI2C1        (1<<19)
#define PCONP_PCLCD         (1<<20)
#define PCONP_PCSSP0        (1<<21)
#define PCONP_PCTIM2        (1<<22)
#define PCONP_PCTIM3        (1<<23)
#define PCONP_PCUART2       (1<<24)
#define PCONP_PCUART3       (1<<25)
#define PCONP_PCI2C2        (1<<26)
#define PCONP_PCI2S         (1<<27)
#define PCONP_PCSDC         (1<<28)
#define PCONP_PCGPDMA       (1<<29)
#define PCONP_PCENET        (1<<30)
#define PCONP_PCUSB         (1<<31)
#define PCONP_MASK          ( \
                              PCONP_PCTIM0  | \
                              PCONP_PCTIM1  | \
                              PCONP_PCUART0 | \
                              PCONP_PCUART1 | \
                              PCONP_PCPWM0  | \
                              PCONP_PCPWM1  | \
                              PCONP_PCI2C0  | \
                              PCONP_PCSPI   | \
                              PCONP_PCRTC   | \
                              PCONP_PCSSP1  | \
                              PCONP_PCEMC   | \
                              PCONP_PCAD    | \
                              PCONP_PCCAN1  | \
                              PCONP_PCCAN2  | \
                              PCONP_PCI2C1  | \
                              PCONP_PCLCD   | \
                              PCONP_PCSSP0  | \
                              PCONP_PCTIM2  | \
                              PCONP_PCTIM3  | \
                              PCONP_PCUART2 | \
                              PCONP_PCUART3 | \
                              PCONP_PCI2C2  | \
                              PCONP_PCI2S   | \
                              PCONP_PCSDC   | \
                              PCONP_PCGPDMA | \
                              PCONP_PCENET  | \
                              PCONP_PCUSB     \
                            )

#endif /* __SCB_H */
