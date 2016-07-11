/*
 File: 			drv_input.h
 Description: 	LP2478-SDK input driver header file
 Author:		Shawn Quinn

 Created for UW CP105, Winter 2014, term project.

 This file contains the interface between the driver and the application.
 Version 1 performs the task of reading the state of the input buttons.

 VER	DATE	INI		DESCRIPTION
 ----	-------	---		-------------------------------------------------------
 0.01	22MAR14	MSQ		Initial version created.

 */

#ifndef __INPUTDRV_H__
#define __INPUTDRV_H__

//name of input device
#define INPUT_DRV   "\\dev\\INPUT"

// define the control codes and data for this driver
// Read the state of the input buttons
#define PLAY_BUTTON_PRESSED			1
#define STOP_BUTTON_PRESSED			2
#define NO_BUTTON_PRESSED			3

INT8U Input_Init(POSDRV_DISPATCH pDispatch, PVOID *ppContext,
				POSDRV_CONFIG pConfig);

#endif //__DISPLAYDRV_H__
