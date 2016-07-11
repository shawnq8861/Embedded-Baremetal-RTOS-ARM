/*
 * macros.h
 *
 * Most of these were pulled from lpc2378.h because they are used in the project code base.
 * Probably would have been easier to just rename the original header!!!
 *
 *  Created on: Jan 31, 2014
 *      Author: jsbosch
 */

#ifndef MACROS_H_
#define MACROS_H_

/*
 * STANDARD DEFINITIONS
 */

#define BIT(a)  (1<<a)

#define U32 unsigned long
#define U16 unsigned short
#define U8  unsigned char

#define S32 long
#define S16 short
#define S8 char

#define VOLATILE32(addr) (*(volatile U32 *)(addr))
#define VOLATILE16(addr) (*(volatile U16 *)(addr))
#define VOLATILE8(addr)  (*(volatile U8 *)(addr))

/*
 *  read/write registers when pReg is a hex value for address (not cast as a pointer)
 */
#define READREG32(pReg) (*(volatile U32 *)(pReg))
#define READREG16(pReg) (*(volatile U16 *)(pReg))
#define READREG8(pReg) (*(volatile U8 *)(pReg))
#define WRITEREG32(pReg, data) ((*(volatile U32 *)(pReg)) = data)
#define WRITEREG16(pReg, data) ((*(volatile U16 *)(pReg)) = data)
#define WRITEREG8(pReg, data) ((*(volatile U8 *)(pReg))  = data)

#define SCB_READREG32(pReg) (P_SCB_REGS->pReg)
#define SCB_READREG16(pReg) (P_SCB_REGS->pReg)
#define SCB_READREG8(pReg)  (P_SCB_REGS->pReg)
#define SCB_WRITEREG32(pReg, data) (((P_SCB_REGS->pReg)) = data)
#define SCB_WRITEREG16(pReg, data) (((P_SCB_REGS->pReg)) = data)
#define SCB_WRITEREG8(pReg, data)  (((P_SCB_REGS->pReg))  = data)

#define AD0CR          0xE0034000
#define AD0GDR         0xE0034004
#define ADINTEN        0xE003400C
#define ADDR0          0xE0034010
#define ADDR1          0xE0034014
#define ADDR2          0xE0034018
#define ADDR3          0xE003401C
#define ADDR4          0xE0034020
#define ADDR5          0xE0034024
#define ADDR6          0xE0034028
#define ADDR7          0xE003402C

#define SET_PCLK(per,div) ((div) << (per))
//??add indx
#define  PCLKINDX_WDT                         0
#define  PCLKINDX_TIMER0                      1
#define  PCLKINDX_TIMER1                      2
#define  PCLKINDX_UART0                       3
#define  PCLKINDX_UART1                       4
#define  PCLKINDX_PWM0                        5
#define  PCLKINDX_PWM1                        6
#define  PCLKINDX_I2C0                        7
#define  PCLKINDX_SPI                         8
#define  PCLKINDX_RTC                         9
#define  PCLKINDX_SSP1                       10
#define  PCLKINDX_DAC                        11
#define  PCLKINDX_ADC                        12
#define  PCLKINDX_CAN1                       13
#define  PCLKINDX_CAN2                       14
#define  PCLKINDX_ACF                        15
#define  PCLKINDX_BAT_RAM                    16
#define  PCLKINDX_GPIO                       17
#define  PCLKINDX_PCB                        18
#define  PCLKINDX_I2C1                       19
#define  PCLKINDX_SSP0                       21
#define  PCLKINDX_TIMER2                     22
#define  PCLKINDX_TIMER3                     23
#define  PCLKINDX_UART2                      24
#define  PCLKINDX_UART3                      25
#define  PCLKINDX_I2C2                       26
#define  PCLKINDX_MCI                        27
#define  PCLKINDX_SYSCON                     29

#define PWM1IR         0xE0018000
#define PWM1TCR        0xE0018004
#define PWM1TC         0xE0018008
#define PWM1PR         0xE001800C
#define PWM1PC         0xE0018010
#define PWM1MCR        0xE0018014
#define PWM1MR0        0xE0018018
#define PWM1MR1        0xE001801C
#define PWM1MR2        0xE0018020
#define PWM1MR3        0xE0018024
#define PWM1CCR        0xE0018028
#define PWM1CR0        0xE001802C
#define PWM1CR1        0xE0018030
#define PWM1CR2        0xE0018034
#define PWM1CR3        0xE0018038
#define PWM1EMR        0xE001803C
#define PWM1MR4        0xE0018040
#define PWM1MR5        0xE0018044
#define PWM1MR6        0xE0018048
#define PWM1PCR        0xE001804C
#define PWM1LER        0xE0018050
#define PWM1CTCR       0xE0018070

//#define IO0DIR         0xE0028008
//#define IO0CLR         0xE002800C
//#define IO1PIN         0xE0028010
//#define IO1SET         0xE0028014
//#define IO1DIR         0xE0028018
//#define IO1CLR         0xE002801C


/*
 * Vectored Interrupt Controller
 */
/* VIC Interrupt registers */
typedef struct _VICINT_BITS{
    int WDT       : 1;
    int           : 1;
    int ARMCORE0  : 1;
    int ARMCORE1  : 1;
    int TIMER0    : 1;
    int TIMER1    : 1;
    int UART0     : 1;
    int UART1     : 1;
    int PWM1      : 1;
    int I2C0      : 1;
    int SPI       : 1;
    int SSP1      : 1;
    int PLL       : 1;
    int RTC       : 1;
    int EINT0     : 1;
    int EINT1     : 1;
    int EINT2     : 1;
    int EINT3     : 1;
    int AD0       : 1;
    int I2C1      : 1;
    int BOD       : 1;
    int ETHERNET  : 1;
    int USB       : 1;
    int CAN12     : 1;
    int SDMMC     : 1;
    int GPDMA     : 1;
    int TIMER2    : 1;
    int TIMER3    : 1;
    int UART2     : 1;
    int UART3     : 1;
    int I2C2      : 1;
    int I2S       : 1;
} VICINT_BITS, *PVICINT_BITS;

#define VICIRQSTATUS        0xFFFFF000
#define VICFIQSTAUS         0xFFFFF004
#define VICRAWINTR          0xFFFFF008
#define VICINTSELECT        0xFFFFF00C
#define VICINTENABLE        0xFFFFF010
#define VICINTENCLEAR       0xFFFFF014
#define VICSOFTINT          0xFFFFF018
#define VICSOFTINTCLEAR     0xFFFFF01C
#define VICPROTECTION       0xFFFFF020
#define VICSWPRIORITYMASK   0xFFFFF024
#define VICVECTADDR0        0xFFFFF100
#define VICVECTADDR1        0xFFFFF104
#define VICVECTADDR2        0xFFFFF108
#define VICVECTADDR3        0xFFFFF10C
#define VICVECTADDR4        0xFFFFF110
#define VICVECTADDR5        0xFFFFF114
#define VICVECTADDR6        0xFFFFF118
#define VICVECTADDR7        0xFFFFF11C
#define VICVECTADDR8        0xFFFFF120
#define VICVECTADDR9        0xFFFFF124
#define VICVECTADDR10       0xFFFFF128
#define VICVECTADDR11       0xFFFFF12C
#define VICVECTADDR12       0xFFFFF130
#define VICVECTADDR13       0xFFFFF134
#define VICVECTADDR14       0xFFFFF138
#define VICVECTADDR15       0xFFFFF13C
#define VICVECTADDR16       0xFFFFF140
#define VICVECTADDR17       0xFFFFF144
#define VICVECTADDR18       0xFFFFF148
#define VICVECTADDR19       0xFFFFF14C
#define VICVECTADDR20       0xFFFFF150
#define VICVECTADDR21       0xFFFFF154
#define VICVECTADDR22       0xFFFFF158
#define VICVECTADDR23       0xFFFFF15C
#define VICVECTADDR24       0xFFFFF160
#define VICVECTADDR25       0xFFFFF164
#define VICVECTADDR26       0xFFFFF168
#define VICVECTADDR27       0xFFFFF16C
#define VICVECTADDR28       0xFFFFF170
#define VICVECTADDR29       0xFFFFF174
#define VICVECTADDR30       0xFFFFF178
#define VICVECTADDR31       0xFFFFF17C
#define VICVECTPRIORITY0    0xFFFFF200
#define VICVECTPRIORITY1    0xFFFFF204
#define VICVECTPRIORITY2    0xFFFFF208
#define VICVECTPRIORITY3    0xFFFFF20C
#define VICVECTPRIORITY4    0xFFFFF210
#define VICVECTPRIORITY5    0xFFFFF214
#define VICVECTPRIORITY6    0xFFFFF218
#define VICVECTPRIORITY7    0xFFFFF21C
#define VICVECTPRIORITY8    0xFFFFF220
#define VICVECTPRIORITY9    0xFFFFF224
#define VICVECTPRIORITY10   0xFFFFF228
#define VICVECTPRIORITY11   0xFFFFF22C
#define VICVECTPRIORITY12   0xFFFFF230
#define VICVECTPRIORITY13   0xFFFFF234
#define VICVECTPRIORITY14   0xFFFFF238
#define VICVECTPRIORITY15   0xFFFFF23C
#define VICVECTPRIORITY16   0xFFFFF240
#define VICVECTPRIORITY17   0xFFFFF244
#define VICVECTPRIORITY18   0xFFFFF248
#define VICVECTPRIORITY19   0xFFFFF24C
#define VICVECTPRIORITY20   0xFFFFF250
#define VICVECTPRIORITY21   0xFFFFF254
#define VICVECTPRIORITY22   0xFFFFF258
#define VICVECTPRIORITY23   0xFFFFF25C
#define VICVECTPRIORITY24   0xFFFFF260
#define VICVECTPRIORITY25   0xFFFFF264
#define VICVECTPRIORITY26   0xFFFFF268
#define VICVECTPRIORITY27   0xFFFFF26C
#define VICVECTPRIORITY28   0xFFFFF270
#define VICVECTPRIORITY29   0xFFFFF274
#define VICVECTPRIORITY30   0xFFFFF278
#define VICVECTPRIORITY31   0xFFFFF27C
#define VICADDRESS          0xFFFFFF00
/*
 *  VIC Interrupt channels
 */
#define VIC_WDT          0  /* Watchdog                           */
#define VIC_SW           1  /* Software interrupts                */
#define VIC_DEBUGRX      2  /* Embedded ICE, DbgCommRx            */
#define VIC_DEBUGTX      3  /* Embedded ICE, DbgCommTx            */
#define VIC_TIMER0       4  /* Timer 0 (Match 0-3 Capture 0-3)    */
#define VIC_TIMER1       5  /* Timer 1 (Match 0-3 Capture 0-3)    */
#define VIC_UART0        6  /* UART 0  (RLS, THRE, RDA, CTI)      */
#define VIC_UART1        7  /* UART 1  (RLS, THRE, RDA, CTI, MSI) */
#define VIC_PWM01        8  /* PWM 01  (Match 0-6 Capture 0-3)    */
#define VIC_I2C0         9  /* I2C 0   (SI)                       */
#define VIC_SPI         10  /* SPI 0, SSP 0                       */
#define VIC_SSP1        11  /* SSP 1                              */
#define VIC_PLL         12  /* PLL lock (PLOCK)                   */
#define VIC_RTC         13  /* RTC      (RTCCIF, RTCALF)          */
#define VIC_EINT0       14  /* External interrupt 0 (EINT0)       */
#define VIC_EINT1       15  /* External interrupt 1 (EINT1)       */
#define VIC_EINT2       16  /* External interrupt 2 (EINT2)       */
#define VIC_EINT3       17  /* External interrupt 3 (EINT3)       */
#define VIC_AD0         18  /* A/D converter 0                    */
#define VIC_I2C1        19  /* I2C 1                              */
#define VIC_BOD         20  /* Brown out detect                   */
#define VIC_ETHERNET    21  /* Ethernet                           */
#define VIC_USB         22  /* USB Low and High priority          */
#define VIC_CAN12       23  /* CAN1,2 Tx, Rx                      */
#define VIC_MMC         24  /* SD/MMC                             */
#define VIC_GP_DMA      25  /* DMA channel 0, DMA channel 1       */
#define VIC_TIMER2      26  /* Timer 2 (Match 0-3 Capture 0-3)    */
#define VIC_TIMER3      27  /* Timer 3 (Match 0-3 Capture 0-3)    */
#define VIC_UART2       28  /* UART 2  (RLS, THRE, RDA, CTI)      */
#define VIC_UART3       29  /* UART 3  (RLS, THRE, RDA, CTI, MSI) */
#define VIC_I2C2        30  /* I2C 0   (SI)                       */
#define VIC_I2S         31  /* I2S Rx, Tx                         */

#endif /* MACROS_H_ */
