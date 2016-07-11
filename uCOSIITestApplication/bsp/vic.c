
#include <includes.h>

/*
*********************************************************************************************************
*
* Prototypes for dummy interrupt handlers
*
*********************************************************************************************************
*/
static  void  VIC_Dummy        (void);
static  void  VIC_DummyWDT     (void);
static  void  VIC_DummySW      (void);
static  void  VIC_DummyDEBUGRX (void);
static  void  VIC_DummyDEBUGTX (void);
static  void  VIC_DummyTIMER0  (void);
static  void  VIC_DummyTIMER1  (void);
static  void  VIC_DummyUART0   (void);
static  void  VIC_DummyUART1   (void);
static  void  VIC_DummyPWM01   (void);
static  void  VIC_DummyI2C0    (void);
static  void  VIC_DummySPI     (void);
static  void  VIC_DummySSP1    (void);
static  void  VIC_DummyPLL     (void);
static  void  VIC_DummyRTC     (void);
static  void  VIC_DummyEINT0   (void);
static  void  VIC_DummyEINT1   (void);
static  void  VIC_DummyEINT2   (void);
static  void  VIC_DummyEINT3   (void);
static  void  VIC_DummyAD0     (void);
static  void  VIC_DummyI2C1    (void);
static  void  VIC_DummyBOD     (void);
static  void  VIC_DummyETHERNET(void);
static  void  VIC_DummyUSB     (void);
static  void  VIC_DummyCAN01   (void);
static  void  VIC_DummyMMC     (void);
static  void  VIC_DummyGP_DMA  (void);
static  void  VIC_DummyTIMER2  (void);
static  void  VIC_DummyTIMER3  (void);
static  void  VIC_DummyUART2   (void);
static  void  VIC_DummyUART3   (void);
static  void  VIC_DummyI2C2    (void);
static  void  VIC_DummyI2S     (void);

CPU_INT32U  VIC_SpuriousInt;

/*
*********************************************************************************************************
*                                     VIC_Init()
*
* Description : Initialize the Vectored Interrupt Controller
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

void  VIC_Init (void)
{
    WRITEREG32(VICINTENCLEAR, 0xFFFFFFFF);                      /* Disable ALL interrupts                                   */
    WRITEREG32(VICADDRESS, 0);                                  /* Acknowlege any pending VIC interrupt                     */
    WRITEREG32(VICPROTECTION, 0);                               /* Allow VIC register access in User of Priviledged modes   */

    WRITEREG32(VICVECTADDR0, (CPU_INT32U)VIC_DummyWDT);         /* Set the vector address                                   */
    WRITEREG32(VICVECTADDR1, (CPU_INT32U)VIC_DummySW);
    WRITEREG32(VICVECTADDR2, (CPU_INT32U)VIC_DummyDEBUGRX);
    WRITEREG32(VICVECTADDR3, (CPU_INT32U)VIC_DummyDEBUGTX);
    WRITEREG32(VICVECTADDR4, (CPU_INT32U)VIC_DummyTIMER0);
    WRITEREG32(VICVECTADDR5, (CPU_INT32U)VIC_DummyTIMER1);
    WRITEREG32(VICVECTADDR6, (CPU_INT32U)VIC_DummyUART0);
    WRITEREG32(VICVECTADDR7, (CPU_INT32U)VIC_DummyUART1);
    WRITEREG32(VICVECTADDR8, (CPU_INT32U)VIC_DummyPWM01);
    WRITEREG32(VICVECTADDR9, (CPU_INT32U)VIC_DummyI2C0);
    WRITEREG32(VICVECTADDR10, (CPU_INT32U)VIC_DummySPI);
    WRITEREG32(VICVECTADDR11, (CPU_INT32U)VIC_DummySSP1);
    WRITEREG32(VICVECTADDR12, (CPU_INT32U)VIC_DummyPLL);
    WRITEREG32(VICVECTADDR13, (CPU_INT32U)VIC_DummyRTC);
    WRITEREG32(VICVECTADDR14, (CPU_INT32U)VIC_DummyEINT0);
    WRITEREG32(VICVECTADDR15, (CPU_INT32U)VIC_DummyEINT1);
    WRITEREG32(VICVECTADDR16, (CPU_INT32U)VIC_DummyEINT2);
    WRITEREG32(VICVECTADDR17, (CPU_INT32U)VIC_DummyEINT3);
    WRITEREG32(VICVECTADDR18, (CPU_INT32U)VIC_DummyAD0);
    WRITEREG32(VICVECTADDR19, (CPU_INT32U)VIC_DummyI2C1);
    WRITEREG32(VICVECTADDR20, (CPU_INT32U)VIC_DummyBOD);
    WRITEREG32(VICVECTADDR21, (CPU_INT32U)VIC_DummyETHERNET);
    WRITEREG32(VICVECTADDR22, (CPU_INT32U)VIC_DummyUSB);
    WRITEREG32(VICVECTADDR23, (CPU_INT32U)VIC_DummyCAN01);
    WRITEREG32(VICVECTADDR24, (CPU_INT32U)VIC_DummyMMC);
    WRITEREG32(VICVECTADDR25, (CPU_INT32U)VIC_DummyGP_DMA);
    WRITEREG32(VICVECTADDR26, (CPU_INT32U)VIC_DummyTIMER2);
    WRITEREG32(VICVECTADDR27, (CPU_INT32U)VIC_DummyTIMER3);
    WRITEREG32(VICVECTADDR28, (CPU_INT32U)VIC_DummyUART2);
    WRITEREG32(VICVECTADDR29, (CPU_INT32U)VIC_DummyUART3);
    WRITEREG32(VICVECTADDR30, (CPU_INT32U)VIC_DummyI2C2);
    WRITEREG32(VICVECTADDR31, (CPU_INT32U)VIC_DummyI2S);
}


/*
*********************************************************************************************************
*********************************************************************************************************
**                                       DUMMY INTERRUPT HANDLERS
*********************************************************************************************************
*********************************************************************************************************
*/

static  void  VIC_Dummy (void)
{
    while (DEF_TRUE) {
        ;
    }
}

static  void  VIC_DummyWDT (void)
{
    VIC_SpuriousInt = VIC_WDT;
    VIC_Dummy();
}

static  void  VIC_DummySW (void)
{
    VIC_SpuriousInt = VIC_SW;
    VIC_Dummy();
}

static  void  VIC_DummyDEBUGRX (void)
{
    VIC_SpuriousInt = VIC_DEBUGRX;
    VIC_Dummy();
}

static  void  VIC_DummyDEBUGTX (void)
{
    VIC_SpuriousInt = VIC_DEBUGTX;
    VIC_Dummy();
}

static  void  VIC_DummyTIMER0 (void)
{
    VIC_SpuriousInt = VIC_TIMER0;
    VIC_Dummy();
}

static  void  VIC_DummyTIMER1 (void)
{
    VIC_SpuriousInt = VIC_TIMER1;
    VIC_Dummy();
}

static  void  VIC_DummyUART0 (void)
{
    VIC_SpuriousInt = VIC_UART0;
    VIC_Dummy();
}

static  void  VIC_DummyUART1 (void)
{
    VIC_SpuriousInt = VIC_UART1;
    VIC_Dummy();
}

static  void  VIC_DummyPWM01 (void)
{
    VIC_SpuriousInt = VIC_PWM01;
    VIC_Dummy();
}

static  void  VIC_DummyI2C0 (void)
{
    VIC_SpuriousInt = VIC_I2C0;
    VIC_Dummy();
}

static  void  VIC_DummySPI (void)
{
    VIC_SpuriousInt = VIC_SPI;
    VIC_Dummy();
}

static  void  VIC_DummySSP1 (void)
{
    VIC_SpuriousInt = VIC_SSP1;
    VIC_Dummy();
}

static  void  VIC_DummyPLL (void)
{
    VIC_SpuriousInt = VIC_PLL;
    VIC_Dummy();
}

static  void  VIC_DummyRTC (void)
{
    VIC_SpuriousInt = VIC_RTC;
    VIC_Dummy();
}

static  void  VIC_DummyEINT0 (void)
{
    VIC_SpuriousInt = VIC_EINT0;
    VIC_Dummy();
}

static  void  VIC_DummyEINT1 (void)
{
    VIC_SpuriousInt = VIC_EINT1;
    VIC_Dummy();
}

static  void  VIC_DummyEINT2 (void)
{
    VIC_SpuriousInt = VIC_EINT2;
    VIC_Dummy();
}

static  void  VIC_DummyEINT3 (void)
{
    VIC_SpuriousInt = VIC_EINT3;
    VIC_Dummy();
}

static  void  VIC_DummyAD0 (void)
{
    VIC_SpuriousInt = VIC_AD0;
    VIC_Dummy();
}

static  void  VIC_DummyI2C1 (void)
{
    VIC_SpuriousInt = VIC_I2C1;
    VIC_Dummy();
}

static  void  VIC_DummyBOD (void)
{
    VIC_SpuriousInt = VIC_BOD;
    VIC_Dummy();
}

static  void  VIC_DummyETHERNET (void)
{
    VIC_SpuriousInt = VIC_ETHERNET;
    VIC_Dummy();
}

static  void  VIC_DummyUSB (void)
{
    VIC_SpuriousInt = VIC_USB;
    VIC_Dummy();
}

static  void  VIC_DummyCAN01 (void)
{
    VIC_SpuriousInt = VIC_CAN12;
    VIC_Dummy();
}

static  void  VIC_DummyMMC (void)
{
    VIC_SpuriousInt = VIC_MMC;
    VIC_Dummy();
}

static  void  VIC_DummyGP_DMA (void)
{
    VIC_SpuriousInt = VIC_GP_DMA;
    VIC_Dummy();
}

static  void  VIC_DummyTIMER2 (void)
{
    VIC_SpuriousInt = VIC_TIMER2;
    VIC_Dummy();
}

static  void  VIC_DummyTIMER3 (void)
{
    VIC_SpuriousInt = VIC_TIMER3;
    VIC_Dummy();
}

static  void  VIC_DummyUART2 (void)
{
    VIC_SpuriousInt = VIC_UART2;
    VIC_Dummy();
}

static  void  VIC_DummyUART3 (void)
{
    VIC_SpuriousInt = VIC_UART3;
    VIC_Dummy();
}

static  void  VIC_DummyI2C2 (void)
{
    VIC_SpuriousInt = VIC_I2C2;
    VIC_Dummy();
}

static  void  VIC_DummyI2S (void)
{
    VIC_SpuriousInt = VIC_I2S;
    VIC_Dummy();
}
