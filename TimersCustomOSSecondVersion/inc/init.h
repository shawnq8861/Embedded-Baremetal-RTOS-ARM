#ifndef INIT_H
#define INIT_H


typedef struct scb2300params {
    uint16_t PLL_M_Mul; /* PLL Multiplier. Valid values 6 through 512*/
    uint8_t  PLL_N_Div; /* PLL Divider. Valid values 1 through 32 */
    uint32_t PLL_Fcco;  /* Frequency (Hz) of PLL output */
    uint8_t  CCLK_Div;  /* CPU Clock divider, cclk */
    uint8_t  MAMMode;   /* */
    uint8_t  MAMTim;
} scb2300_t;



/* Exported Prototypes */
void handlerDummy(void);
void initHardware(scb2300_t * pSCBParams);
void initUART0(uint32_t baud, uint8_t mode, uint8_t fmode, uint32_t cclk);
void pinConfigurator(void);
uint32_t getFcclk(void);
void installVector(
        uint32_t vectorNumber,
        pfunction_t interruptServiceRoutine,
        arminterrupt_t intSelect,
        uint32_t priority);



#endif /* INIT_H */
