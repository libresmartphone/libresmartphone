/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Header file for MangaScreen.h.
 */

#ifndef _MANGA_SCREEN_H_
#define _MANGA_SCREEN_H_

	/* Includes: */
		#include <avr/io.h>
		#include <avr/wdt.h>
		#include <avr/power.h>
		#include <avr/interrupt.h>
		#include <string.h>

		#include "Descriptors.h"
		#include "LCD.h"
		#include "Digitizer.h"
		#include "EEPROM.h"

		#include <LUFA/Drivers/Board/LEDs.h>
		//#include <LUFA/Drivers/Board/Joystick.h>
		#include <LUFA/Drivers/Board/Buttons.h>
		#include <LUFA/Drivers/Misc/RingBuffer.h>
		#include <LUFA/Drivers/USB/USB.h>

		#define dev_err(format, arg...) printf(format , ## arg)
		#define dev_info(format, arg...) printf(format , ## arg)
		#define dev_dbg(format, arg...) printf(format , ## arg)
		#define dev_warn(format, arg...) printf(format , ## arg)



	/* Macros: */
		/** LED mask for the library LED driver, to indicate that the USB interface is not ready. */
		#define LEDMASK_USB_NOTREADY      LEDS_LED2

		/** LED mask for the library LED driver, to indicate that the USB interface is enumerating. */
		#define LEDMASK_USB_ENUMERATING  (LEDS_LED1)

		/** LED mask for the library LED driver, to indicate that the USB interface is ready. */
		#define LEDMASK_USB_READY        (LEDS_LED1)

		/** LED mask for the library LED driver, to indicate that an error has occurred in the USB interface. */
		#define LEDMASK_USB_ERROR        (LEDS_LED3)

	/* Pins: */
		#define PIN_NCS   	(1<<0) // PB0
		#define PIN_SCLK  	(1<<1) // PB1
		#define PIN_MOSI  	(1<<2) // PB2
		#define PIN_MISO  	(1<<3) // PB3
		#define PIN_ST 		(1<<4) // PB4
		#define PIN_PDO		(1<<5) // PB5
		#define PIN_S4		(1<<6) // PB6

		#define PIN_PD		(1<<7) // PC7
		
		#define PIN_SCL		(1<<0) // PD0
		#define PIN_SDA		(1<<1) // PD1
		#define PIN_S3		(1<<2) // PD2
		#define PIN_SCL_BB	(1<<3) // PD3
		#define PIN_SDA_BB	(1<<5) // PD5
		#define PIN_SCDT	(1<<6) // PD6
		#define PIN_BL    	(1<<7) // PD7
		#define PIN_RESET 	(1<<6) // PE6


	/* Function Prototypes: */
		void SetupHardware(void);
		void HandleSerial(void);
		void HandleDigitizer(void);
		void HandleEEPROM(void);
		int execute_command(void);

		int putchar_printf(char var, FILE *stream);

		void EVENT_USB_Device_Connect(void);
		void EVENT_USB_Device_Disconnect(void);
		void EVENT_USB_Device_ConfigurationChanged(void);
		void EVENT_USB_Device_ControlRequest(void);
		void EVENT_USB_Device_StartOfFrame(void);

		bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                         uint8_t* const ReportID,
		                                         const uint8_t ReportType,
		                                         void* ReportData,
		                                         uint16_t* const ReportSize);
		void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
		                                          const uint8_t ReportID,
		                                          const uint8_t ReportType,
		                                          const void* ReportData,
		                                          const uint16_t ReportSize);
#endif

