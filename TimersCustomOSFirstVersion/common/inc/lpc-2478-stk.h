/*
 * DESCRIPTION:
 *
 *  Olimex LPC-2478-STK board level specific definitions
 *
 */

#ifndef __LPC_2478_STK__
#define __LPC_2478_STK__

#include "uw.h"
#include "attributes.h"
#include "bitnum.h"
#include "lpc2478.h"

/* Off-chip System Specific Parameters */
#define FOSC_MAIN            (12000000)
#define FOSC_RTC             (32768)

/* Board-specific stuff goes here */
#define SD_LED_SET          FIO1SET
#define SD_LED_DIR          FIO1DIR
#define SD_LED_CLR          FIO1CLR
#define SD_LED_PIN          FIO1PIN
#define SD_LED_BIT          BIT(5)

#define USB_UP_LED1_BIT     BIT(18)
#define USB_UP_LED2_BIT     BIT(13)

#define BUT1_BIT            BIT(19)
#define BUT2_BIT            BIT(21)

/* Off-chip (LPC-2478) board level SDRAM, see lpc24xx\lpc2478.h for on-chip memory  */
#define SDRAM_BASE     0xA0000000   /* DYCS0 0xA0000000 - 0xAFFFFFFF */
#define SDRAM_SIZE     0x04000000   /* 64 MB */


#endif /* __LPC_2478_STK__ */
