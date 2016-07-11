/*
 File: 			drv_display.c
 Description: 	LP2478-SDK button driver implementation file
 Author:		Shawn Quinn

 Created for UW CP105, Winter 2014, term project.

 This file contains the interface between the driver and the application.
 Version 1 performs the task of reading the state of the input buttons.

 VER	DATE	INI		DESCRIPTION
 ----	-------	---		-------------------------------------------------------
 0.01	22MAR14	MSQ		Initial version created.

 */

#include "includes.h"  // OS includes
#include "driver.h"
#include "drv_input.h"
#include "init.h"


// we are supporting one input device
#define INPUT_DEVICE_COUNT 1

// define a data extension to hold data required by this driver
typedef struct
{
	INT8U OpenCount; // track opens handles to this device
} INPUT_EXT, *PINPUT_EXT;


// prototypes
INT8U Input_Open(INT8U DeviceIndex, PVOID pContext, INT8U Flags);
INT8U Input_Close(INT8U DeviceIndex, PVOID pContext);
INT8U Input_Write(INT8U DeviceIndex, PVOID pContext, PVOID pBuffer,
		INT32U* pCount);
INT8U Input_Ioctl(INT8U DeviceIndex, PVOID pContext, INT8U Control,
		PVOID pBuffer, INT32U* pCount);

//static void SetLED(BOOLEAN On);

/* 
 Input_Init - display driver initialization routine
 */
INT8U Input_Init(POSDRV_DISPATCH pDispatch, PVOID *ppContext,
		POSDRV_CONFIG pConfig)
{
	// allocate the data extension for use to save data for this driver
	*ppContext = DRV_MEMALLOC(sizeof(INPUT_EXT));
	if (*ppContext == NULL)
	{
		return OS_DRV_BUFFER_SIZE;
	}

	// zero the data extension
	memset(*ppContext, 0, sizeof(INPUT_EXT));

	// create a name for each device that we support
	OSDRV_AddName(pConfig, "INPUT");

	// set up the supported entry points for this driver
	pDispatch->pOpen = Input_Open; // required
	pDispatch->pClose = Input_Close; // required
	pDispatch->pRead = NULL; // optional, not currently supported in this driver
	pDispatch->pWrite = NULL; // optional; not supported until adding the LCD
	pDispatch->pIoctl = Input_Ioctl; // optional

	// set this driver to accept non-serialized requests on each handle
	// any synchronization needs to be handled by the driver or caller above us
	pConfig->Exclusive = FALSE;

	// return success
	return OS_DRV_NO_ERR;
}

/*
 Display_Open - open function for driver
 */
INT8U Input_Open(INT8U DeviceIndex, PVOID pContext, INT8U Flags)
{
	if (DeviceIndex >= INPUT_DEVICE_COUNT)
	{
		// someone passed us a bogus device
		DEBUGMSG(TRUE, ("INPUT_DRV attempt to open bad device index: 0x%X\n\r", DeviceIndex));
		return OS_DRV_NO_DEVICE;
	}

	// we only allow one handle to the device at a time in this driver
	if (((PINPUT_EXT) pContext)->OpenCount > 0)
	{
		DEBUGMSG(TRUE, ("INPUT_DRV attempt to open too many handles\n\r"));
		return OS_DRV_NO_DEVICE;
	}

	// count the open handles
	((PINPUT_EXT) pContext)->OpenCount++;

	// return success
	return OS_DRV_NO_ERR;
}

/*
 Input_Close - close function for driver
 */
INT8U Input_Close(INT8U DeviceIndex, PVOID pContext)
{
	if (DeviceIndex >= INPUT_DEVICE_COUNT)
	{
		// someone passed us a bogus device
		DEBUGMSG(TRUE, ("INPUT_DRV attempt to close bad device index: 0x%X\n\r", DeviceIndex));
		return OS_DRV_NO_DEVICE;
	}

	// keep count of the open handles
	((PINPUT_EXT) pContext)->OpenCount--;

	// return success
	return OS_DRV_NO_ERR;
}

/*
 Input_Ioctl - I/O control function for driver
 */
INT8U Input_Ioctl(INT8U DeviceIndex, PVOID pContext, INT8U Control,
		PVOID pBuffer, INT32U* pCount)
{
	INT32U btnPin;

	if (DeviceIndex >= INPUT_DEVICE_COUNT)
	{
		// someone passed us a bogus device
		DEBUGMSG(TRUE, ("INPUT_DRV attempt to send control code to bad device index: 0x%X\n\r", DeviceIndex));
		return OS_DRV_NO_DEVICE;
	}

	DEBUGMSG(TRUE, ("***** INPUT_DRV IOCTL: "));

	// determine which button is pressed
   	btnPin = FIO2PIN;

    if (!(btnPin & (1<<19)))
    {
    	//sprintf(stringbuffer, "\n\rBUT1 Pressed\n\r");
    	//printString(stringbuffer);
    	DEBUGMSG(TRUE, ("IOCTL_INPUT_BUT1_PRESSED\n\r"));
    	return PLAY_BUTTON_PRESSED;
    }
    else if (!(btnPin & (1<<21)))
    {
    	//sprintf(stringbuffer, "\n\rBUT2 Pressed\n\r");
    	//printString(stringbuffer);
    	DEBUGMSG(TRUE, ("IOCTL_INPUT_BUT2_PRESSED\n\r"));
    	return STOP_BUTTON_PRESSED;
    }
    else
    {
    	//sprintf(stringbuffer, "\n\rNo Button Pressed\n\r");
    	//printString(stringbuffer);
    	DEBUGMSG(TRUE, ("IOCTL_INPUT_NO_INPUT\n\r"));
    	return NO_BUTTON_PRESSED;
    }
}

/*
 Display_Read - read function for driver. Not currently implemented.
 */
INT8U Input_Read(INT8U DeviceIndex, PVOID pContext, PVOID pBuffer,
		INT32U* pCount)
{
	return OS_DRV_UNSUPPORTED;
}

/*
 Display_Write - write function for driver. Not currently implemented.
 */
INT8U Input_Write(INT8U DeviceIndex, PVOID pContext, PVOID pBuffer,
		INT32U* pCount)
{
	return OS_DRV_UNSUPPORTED;
}

/************************************************************************************
   Toggle the LED next to the display (labeled SD)
************************************************************************************/
//static void SetLED(BOOLEAN On)
//{
//    if (On) {
//        WRITEREG32(FIO0SET, SD_LED_BIT);
//      } else {
//        WRITEREG32(FIO0CLR, SD_LED_BIT);
//     }
//}
