/*
 File: 			drv_display.h
 Description: 	LP2378-SDK display driver header file
 Author:		Jeff Bosch

 Created for UW CP105, Winter 2012, term project.

 This file contains the interface between the driver and the application.
 Version 1 performs the trivial task of controlling the LED. Future versions
 can add other LEDs and the LCD, as time permits.

 VER	DATE	INI		DESCRIPTION
 ----	-------	---		-------------------------------------------------------
 0.01	18MAR12	JSB		Initial version created.

 */

#ifndef __DISPLAYDRV_H__
#define __DISPLAYDRV_H__

//name of display device
#define DISPLAY_DRV   "\\dev\\DISPLAY"

// define the control codes and data for this driver
// Control the LEDs
#define IOCTL_DISPLAY_LED_ON		1
#define IOCTL_DISPLAY_LED_OFF		2
#define IOCTL_DISPLAY_LED_BLINK		3

INT8U Display_Init(POSDRV_DISPATCH pDispatch, PVOID *ppContext,
				POSDRV_CONFIG pConfig);

#endif //__DISPLAYDRV_H__
