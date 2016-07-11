#ifndef __INIT_H__
#define __INIT_H__

typedef struct scb2300params {
	INT16U PLL_M_Mul; /* PLL Multiplier. Valid values 6 through 512*/
	INT8U  PLL_N_Div; /* PLL Divider. Valid values 1 through 32 */
	INT32U PLL_Fcco;  /* Frequency (Hz) of PLL output */
	INT8U  CCLK_Div;  /* CPU Clock divider, cclk */
	INT8U  MAMMode;   /* */
	INT8U  MAMTim;
} scb2300_t;


/* Off-chip System Specific Parameters */
#define FOSC_MAIN            (12000000)
#define FOSC_RTC             (32768)


/* Exported Prototypes */
void handlerDummy(void);
void initUART0(INT32U baud, INT8U mode, INT8U fmode, INT32U cclk);
//void initUART0(uint16_t baud, uint8_t mode, uint8_t fmode);
void initHardware(void);
void pinConfigurator(void);
INT32U getFcclk(void);



#endif /* __INIT_H__ */
