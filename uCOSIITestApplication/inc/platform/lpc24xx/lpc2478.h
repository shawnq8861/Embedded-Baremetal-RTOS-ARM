/*
 * MODULE:
 *
 *  lpc2478.h
 *
 * DESCRIPTION:
 *
 *  LPC2478 on-chip specific standard definitions file
 *
 */

#ifndef __LPC2478_H
#define __LPC2478_H


#include "dac.h"
#include "emc.h"
#include "gpio.h"
#include "pinconnect.h"
#include "scb.h"
#include "timers.h"
#include "uarts.h"
#include "vic.h"


/* Memory Locations */
#define FLASH_BASE     0x00000000
#define FLASH_SIZE     0x0007E000   /* 516,096 bytes */
                                    /*   8,192 bytes boot block at end of flash */

#define SRAM_BASE      0x40000000
#define SRAM_SIZE      0x00010000   /* 65,536 bytes */

/* SDRAM is defined in the board level file lpc-2478-stk.h since it is off-chip and on the board */

#endif /* __LPC2478_H */
