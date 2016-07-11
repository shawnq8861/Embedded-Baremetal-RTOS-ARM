/*
 File: 			drv_display.c
 Description: 	LP2378-SDK display driver implementation file
 Author:		Jeff Bosch

 Created for UW CP105, Winter 2012, term project.

 This file contains the interface between the driver and the application.
 Version 1 performs the trivial task of controlling the LED. Future versions
 can add other LEDs and the LCD, as time permits.

 VER	DATE	INI		DESCRIPTION
 ----	-------	---		-------------------------------------------------------
 0.01	18MAR12	JSB		Initial version created.

 */

#include "includes.h"  // OS includes
#include "driver.h"
#include "drv_display.h"
#include "init.h"


// we are supporting one display device
#define DISPLAY_DEVICE_COUNT 1

// define a data extension to hold data required by this driver
typedef struct
{
	INT8U OpenCount; // track opens handles to this device
} DISPLAY_EXT, *PDISPLAY_EXT;


// prototypes
INT8U Display_Open(INT8U DeviceIndex, PVOID pContext, INT8U Flags);
INT8U Display_Close(INT8U DeviceIndex, PVOID pContext);
INT8U Display_Write(INT8U DeviceIndex, PVOID pContext, PVOID pBuffer,
		INT32U* pCount);
INT8U Display_Ioctl(INT8U DeviceIndex, PVOID pContext, INT8U Control,
		PVOID pBuffer, INT32U* pCount);
static void SetLED(BOOLEAN On);

/* 
 Display_Init - display driver initialization routine
 */
INT8U Display_Init(POSDRV_DISPATCH pDispatch, PVOID *ppContext,
		POSDRV_CONFIG pConfig)
{
	// allocate the data extension for use to save data for this driver
	*ppContext = DRV_MEMALLOC(sizeof(DISPLAY_EXT));
	if (*ppContext == NULL)
	{
		return OS_DRV_BUFFER_SIZE;
	}

	// zero the data extension
	memset(*ppContext, 0, sizeof(DISPLAY_EXT));

	// create a name for each device that we support
	OSDRV_AddName(pConfig, "DISPLAY");

	// set up the supported entry points for this driver
	pDispatch->pOpen = Display_Open; // required
	pDispatch->pClose = Display_Close; // required
	pDispatch->pRead = NULL; // optional, not currently supported in this driver
	pDispatch->pWrite = NULL; // optional; not supported until adding the LCD
	pDispatch->pIoctl = Display_Ioctl; // optional

	// set this driver to accept non-serialized requests on each handle
	// any synchronization needs to be handled by the driver or caller above us
	pConfig->Exclusive = FALSE;

	// return success
	return OS_DRV_NO_ERR;
}

/*
 Display_Open - open function for driver
 */
INT8U Display_Open(INT8U DeviceIndex, PVOID pContext, INT8U Flags)
{
	if (DeviceIndex >= DISPLAY_DEVICE_COUNT)
	{
		// someone passed us a bogus device
		DEBUGMSG(TRUE, ("DISPLAY_DRV attempt to open bad device index: 0x%X\n\r", DeviceIndex));
		return OS_DRV_NO_DEVICE;
	}

	// we only allow one handle to the device at a time in this driver
	if (((PDISPLAY_EXT) pContext)->OpenCount > 0)
	{
		DEBUGMSG(TRUE, ("DISPLAY_DRV attempt to open too many handles\n\r"));
		return OS_DRV_NO_DEVICE;
	}

	// count the open handles
	((PDISPLAY_EXT) pContext)->OpenCount++;

	// return success
	return OS_DRV_NO_ERR;
}

/*
 Display_Close - close function for driver
 */
INT8U Display_Close(INT8U DeviceIndex, PVOID pContext)
{
	if (DeviceIndex >= DISPLAY_DEVICE_COUNT)
	{
		// someone passed us a bogus device
		DEBUGMSG(TRUE, ("DISPLAY_DRV attempt to close bad device index: 0x%X\n\r", DeviceIndex));
		return OS_DRV_NO_DEVICE;
	}

	// keep count of the open handles
	((PDISPLAY_EXT) pContext)->OpenCount--;

	// return success
	return OS_DRV_NO_ERR;
}

/*
 Display_Ioctl - I/O control function for driver
 */
INT8U Display_Ioctl(INT8U DeviceIndex, PVOID pContext, INT8U Control,
		PVOID pBuffer, INT32U* pCount)
{
	if (DeviceIndex >= DISPLAY_DEVICE_COUNT)
	{
		// someone passed us a bogus device
		DEBUGMSG(TRUE, ("DISPLAY_DRV attempt to send control code to bad device index: 0x%X\n\r", DeviceIndex));
		return OS_DRV_NO_DEVICE;
	}

	DEBUGMSG(TRUE, ("***** DISPLAY_DRV IOCTL: "));

	// determine which Control code is being used
	switch (Control)
	{
	case IOCTL_DISPLAY_LED_OFF: // Turn off the LED
		SetLED(0);
		DEBUGMSG(TRUE, ("IOCTL_DISPLAY_LED_OFF\n\r"));
		break;
	case IOCTL_DISPLAY_LED_ON:
		SetLED(1);
		DEBUGMSG(TRUE, ("IOCTL_DISPLAY_LED_ON\n\r"));
		break;
	default:
		// we don't know this control code
		return OS_DRV_UNSUPPORTED;
		DEBUGMSG(TRUE, ("OS_DRV_UNSUPPORTED\n\r"));
	}
	return OS_DRV_NO_ERR;
}

/*
 Display_Read - read function for driver. Not currently implemented.
 */
INT8U Display_Read(INT8U DeviceIndex, PVOID pContext, PVOID pBuffer,
		INT32U* pCount)
{
	return OS_DRV_UNSUPPORTED;
}

/*
 Display_Write - write function for driver. Not currently implemented.
 */
INT8U Display_Write(INT8U DeviceIndex, PVOID pContext, PVOID pBuffer,
		INT32U* pCount)
{
	return OS_DRV_UNSUPPORTED;
}

/************************************************************************************
   Toggle the LED next to the display (labeled SD)
************************************************************************************/

static void SetLED(BOOLEAN On)
{
	// Toggle SD LED as a system "heart beat"
	if (On)
	{
		FIO1SET = SD_LED_BIT;	// turn on
    }
	else
	{
		FIO1CLR = SD_LED_BIT;	// turn off
    }
}
