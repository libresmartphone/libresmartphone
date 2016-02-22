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
 *  Main source file for the VirtualSerialMouse demo. This file contains the main tasks of
 *  the demo and is responsible for the initial application hardware configuration.
 */

#include "MangaScreen.h"

/** LUFA CDC Class driver interface configuration and state information. This structure is
 *  passed to all CDC Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_CDC_Device_t VirtualSerial_CDC_Interface =
	{
		.Config =
			{
				.ControlInterfaceNumber         = 0,
				.DataINEndpoint                 =
					{
						.Address                = CDC_TX_EPADDR,
						.Size                   = CDC_TXRX_EPSIZE,
						.Banks                  = 1,
					},
				.DataOUTEndpoint                =
					{
						.Address                = CDC_RX_EPADDR,
						.Size                   = CDC_TXRX_EPSIZE,
						.Banks                  = 1,
					},
				.NotificationEndpoint           =
					{
						.Address                = CDC_NOTIFICATION_EPADDR,
						.Size                   = CDC_NOTIFICATION_EPSIZE,
						.Banks                  = 1,
					},
			},
	};

/** Buffer to hold the previously generated Digitizer HID report, for comparison purposes inside the HID class driver. */
static uint8_t PrevDigitizerHIDReportBuffer[sizeof(USB_DigitizerReport_Data_t)];

/** Circular buffer to hold data from the host before it is sent to the LCD */
static RingBuffer_t FromHost_Buffer;

/** Underlying data buffer for \ref FromHost_Buffer, where the stored bytes are located. */
static uint8_t  FromHost_Buffer_Data[128];

USB_DigitizerReport_Data_t* DigitizerReport;

char cmd[100];
int cmd_cnt;
bool enable_reports = false;

/** LUFA HID Class driver interface configuration and state information. This structure is
 *  passed to all HID Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
USB_ClassInfo_HID_Device_t Digitizer_HID_Interface =
{
	.Config =
		{
			.InterfaceNumber                = 2,
			.ReportINEndpoint               =
				{
					.Address                = DIGITIZER_EPADDR,
					.Size                   = DIGITIZER_EPSIZE,
					.Banks                  = 1,
				},
			.PrevReportINBuffer             = PrevDigitizerHIDReportBuffer,
			.PrevReportINBufferSize         = sizeof(PrevDigitizerHIDReportBuffer),
		},
};

static FILE mystdout = FDEV_SETUP_STREAM(putchar_printf, NULL, _FDEV_SETUP_WRITE);

/** Main program entry point. This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void){

	// Bind to output som we can use printf
	stdout = &mystdout;

	SetupHardware();

	RingBuffer_InitBuffer(&FromHost_Buffer, FromHost_Buffer_Data, sizeof(FromHost_Buffer_Data));


	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;){
		HandleSerial();				
		CDC_Device_USBTask(&VirtualSerial_CDC_Interface);
		HID_Device_USBTask(&Digitizer_HID_Interface);
		USB_USBTask();
	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void){
	int ret;
	int i;

	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Backlight comes on early to suppress the full on blink. */
	BL_on(0);		
	_delay_ms(10); // Wait at least 4ms before enabling the output. Not sure why..

	/* Set up USB */	
	USB_Init();

	ret = EEPROM_Init();
	if(ret)
		dev_err("EEPROM error: %x\n", ret);

	ret = LCD_Init();
	if(ret)
		dev_err("LCD error: %x\n", ret);
	
	ret = Digitizer_Init();
	if(ret)
		dev_err("Digitizer error: %x\n", ret);
		

	DDRC  |= PIN_PD;  // Powerdown 
	PORTC |= PIN_PD;  // High for normal operation
	DDRB  |= PIN_PDO; // Powerdown outputs
	PORTB |= PIN_PDO; // High for normal operation
	
	/* Now we can turn on BL */
	for(i=0; i<255; i++){
		BL_on(i);		
		_delay_ms(10);
	}

	/* Init the LEDs now to show that the hardware init has gone ok */	
	LEDs_Init();
	

	printf(">");
}


/** Checks for changes in the position of the board joystick, sending strings to the host upon each change. */
void HandleSerial(void){
	int err;

	/* Only try to read in bytes from the CDC interface if the transmit buffer is not full */
	if (!(RingBuffer_IsFull(&FromHost_Buffer))){
		int16_t ReceivedByte = CDC_Device_ReceiveByte(&VirtualSerial_CDC_Interface);
		/* Read bytes from the USB OUT endpoint into the USART transmit buffer */
		if (!(ReceivedByte < 0)){
		  	RingBuffer_Insert(&FromHost_Buffer, ReceivedByte);
			CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ReceivedByte);
		}
	}

	while (RingBuffer_GetCount(&FromHost_Buffer) > 0){
		int16_t c = RingBuffer_Remove(&FromHost_Buffer);
		
		if(c == '\n' || c == '\r'){
			if(cmd_cnt > 0 && (cmd[cmd_cnt-1] == '\n' || cmd[cmd_cnt-1] == '\r'))
				cmd_cnt--;
			cmd[cmd_cnt] = 0;			
			err = execute_command();
			cmd_cnt = 0;			
		}
		else{
			cmd[cmd_cnt++] = c;			
		}
	}
}

/* Binding for printf */ 
int putchar_printf(char var, FILE *stream) {
    if (var == '\n') 
		CDC_Device_SendByte(&VirtualSerial_CDC_Interface, '\r');
	CDC_Device_SendByte(&VirtualSerial_CDC_Interface, var);
    return 0;
}

/** Execute a command received via virtual serial */
int execute_command(void){
	int val, ret;

	if(strcmp(cmd, "set display on") == 0){
		LCD_Init();
	}
	else if(strcmp(cmd, "set display off") == 0){
		LCD_UnInit();
	}
	else if(strncmp(cmd, "set backlight ", 14) == 0){
		val = atoi(cmd+14);
		if(val >= 0 && val <= 255)
			BL_on(val);
		else
			printf("Value out of range: %d. Valid range is 0 to 255\n", val);
	}
	else if(strcmp(cmd, "init") == 0){
		ret = Digitizer_Init();
		if(ret)
			dev_err("Digitizer error: %x\n", ret);
	}
	else{
		printf("Unknown comand\n");
		printf("List of commands:\n");
		printf("set backlight <0..255>\n");
		printf("set display <on/off>\n");
	}

	printf(">");

	return 0;
}

/** Event handler for the library USB Connection event. */
void EVENT_USB_Device_Connect(void){
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the library USB Disconnection event. */
void EVENT_USB_Device_Disconnect(void){
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the library USB Configuration Changed event. */
void EVENT_USB_Device_ConfigurationChanged(void){
	bool ConfigSuccess = true;

	ConfigSuccess &= HID_Device_ConfigureEndpoints(&Digitizer_HID_Interface);
	ConfigSuccess &= CDC_Device_ConfigureEndpoints(&VirtualSerial_CDC_Interface);

	USB_Device_EnableSOFEvents();

	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

/** Event handler for the library USB Control Request reception event. */
void EVENT_USB_Device_ControlRequest(void){
	CDC_Device_ProcessControlRequest(&VirtualSerial_CDC_Interface);
	HID_Device_ProcessControlRequest(&Digitizer_HID_Interface);
}

/** Event handler for the USB device Start Of Frame event. */
void EVENT_USB_Device_StartOfFrame(void){
	HID_Device_MillisecondElapsed(&Digitizer_HID_Interface);
}

/** HID class driver callback function for the creation of HID reports to the host.
 *
 *  \param[in]     HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in,out] ReportID    Report ID requested by the host if non-zero, otherwise callback should set to the generated report ID
 *  \param[in]     ReportType  Type of the report to create, either HID_REPORT_ITEM_In or HID_REPORT_ITEM_Feature
 *  \param[out]    ReportData  Pointer to a buffer where the created report should be stored
 *  \param[out]    ReportSize  Number of bytes written in the report (or zero if no report is to be sent)
 *
 *  \return Boolean true to force the sending of the report, false to let the library determine if it needs to be sent
 */
bool CALLBACK_HID_Device_CreateHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                         uint8_t* const ReportID,
                                         const uint8_t ReportType,
                                         void* ReportData,
                                         uint16_t* const ReportSize)
{

	USB_DigitizerReport_Data_t* DigitizerReport = (USB_DigitizerReport_Data_t*)ReportData;
	
	//if(enable_reports)
	if (Digitizer_get_report(DigitizerReport))
	    *ReportSize = 0;
    else
        *ReportSize = sizeof(USB_DigitizerReport_Data_t);
    
    //dev_dbg("HIDReport size: %d\n", *ReportSize);
    return true;
}

/** HID class driver callback function for the processing of HID reports from the host.
 *
 *  \param[in] HIDInterfaceInfo  Pointer to the HID class interface configuration structure being referenced
 *  \param[in] ReportID    Report ID of the received report from the host
 *  \param[in] ReportType  The type of report that the host has sent, either HID_REPORT_ITEM_Out or HID_REPORT_ITEM_Feature
 *  \param[in] ReportData  Pointer to a buffer where the received report has been stored
 *  \param[in] ReportSize  Size in bytes of the received HID report
 */
void CALLBACK_HID_Device_ProcessHIDReport(USB_ClassInfo_HID_Device_t* const HIDInterfaceInfo,
                                          const uint8_t ReportID,
                                          const uint8_t ReportType,
                                          const void* ReportData,
                                          const uint16_t ReportSize)
{
	// Unused (but mandatory for the HID class driver) in this demo, since there are no Host->Device reports
}

