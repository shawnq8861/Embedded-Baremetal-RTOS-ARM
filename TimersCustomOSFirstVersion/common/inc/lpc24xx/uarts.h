#ifndef __UARTS_H
#define __UARTS_H

#define LPC2478_UART0_BASE      (0xE000C000)
#define U0RBR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x00)) /* RO */
#define U0THR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x00)) /* WO */
#define U0DLL   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x00)) /* RW */
#define U0DLM   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x04)) /* RW */
#define U0IER   (*(volatile uint32_t *)(LPC2478_UART0_BASE + 0x04)) /* RW */
#define U0IIR   (*(volatile uint32_t *)(LPC2478_UART0_BASE + 0x08)) /* RO */
#define U0FCR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x08)) /* WO */
#define U0LCR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x0C)) /* RW */
#define U0LSR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x14)) /* RO */
#define U0SCR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x1C)) /* RW */
#define U0ACR   (*(volatile uint32_t *)(LPC2478_UART0_BASE + 0x20)) /* RW */
#define U0ICR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x24)) /* RW */
#define U0FDR   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x28)) /* RW */
#define U0TER   (*(volatile uint8_t  *)(LPC2478_UART0_BASE + 0x30)) /* RW */

#define LPC2478_UART2_BASE      (0xE0078000)

typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_UART {
    union ATTR_PACKED {         /* Offset 0x00 */
        uint8_t RBR;            /* RO */
        uint8_t THR;            /* WO */
        uint8_t DLL;            /* RW if DLAB = 1 */
    };
    uint8_t   pad0[3];
    union ATTR_PACKED {         /* Offset 0x04 */
        struct ATTR_PACKED {
            uint8_t DLM;
            uint8_t pad1[3];
        };
        uint32_t IER;
    };
    union ATTR_PACKED {         /* Offset 0x08 */
        uint32_t IIR;
        struct ATTR_PACKED {
            uint8_t FCR;
            uint8_t pad2[3];
        };
    };
    uint8_t   LCR;              /* Offset 0x0C */
    uint8_t   pad3[3];
    uint8_t   pad4[4];
    uint8_t   LSR;              /* Offset 0x14 */
    uint8_t   pad5[3];
    uint8_t   MSR;              /* Offset 0x18 */
    uint8_t   pad6[3];
    uint8_t   SCR;              /* Offset 0x1C */
    uint8_t   pad7[3];
    uint32_t  ACR;              /* Offset 0x20 */
    uint8_t   ICR;              /* Offset 0x24 */
    uint8_t   pad8[3];
    uint8_t   FDR;              /* Offset 0x28 */
    uint8_t   pad9[3];
    uint32_t  pad10;            /* Offset 0x2C */
    uint8_t   TER;              /* Offset 0x30 */
    uint8_t   pad11[3];
}  LPC24XX_UART_t, *P_LPC24XX_UART_t;

#define P_UART0_REGS ((LPC24XX_UART_t *)LPC2478_UART0_BASE)
#define P_UART2_REGS ((LPC24XX_UART_t *)LPC2478_UART2_BASE)

#define U0_TX_PINSEL_REG   PINSEL0
#define U0_TX_PINSEL       (1UL<<4)
#define U0_TX_PINMASK      (3UL<<4)
#define U0_RX_PINSEL_REG   PINSEL0
#define U0_RX_PINSEL       (1UL<<6)
#define U0_RX_PINMASK      (3UL<<6)

#define ULCR_DLAB_ENABLE   (1<<7)

#define ULSR_PE            (1<<2)
#define ULSR_FE            (1<<3)
#define ULSR_BI            (1<<4)
#define ULSR_THRE          (1<<5)
#define ULSR_TEMT          (1<<6)
#define ULSR_RXFE          (1<<7)

#define UIER_THRE          (1<<1)
#define UTER_TXEN          (1<<7)
#define UART_8N1           (uint8_t)(3<<0)
#define UART_FIFO_OFF      (0x00)

#define UFCR_FIFO_ENABLE   (1<<0)
#define UFCR_RXFIFO_RESET  (1<<1)
#define UFCR_TXFIFO_RESET  (1<<2)
#define UFCR_RX_TRIGGER_1  (0<<6)
#define UFCR_RX_TRIGGER_4  (1<<6)
#define UFCR_RX_TRIGGER_8  (2<<6)
#define UFCR_RX_TRIGGER_14 (3<<6)

/* TODO extra credit move this to application files */
#define SERIALPRINT_UARTNUM 0

#if (SERIALPRINT_UARTNUM == 0)
#define PUTC(c)              while(!(P_UART0_REGS->LSR & ULSR_THRE)) continue; \
                           P_UART0_REGS->THR = (uint8_t) c
#elif (SERIALPRINT_UARTNUM == 2)
#define PUTC(c)              while(!(P_UART2_REGS->LSR & ULSR_THRE)) continue; \
                                 P_UART2_REGS->THR = (uint8_t) c
#else
#define PUTC(c)              (0)
#endif


#endif /* __UARTS_H */
