
/** This file handles EDID requests from the 
Host coming via the HDMI cable. This should be handled 
as an interrupt oon the SCL line which is PD3 */

#ifndef _MANGA_SCREEN_EEPROM_H_
#define _MANGA_SCREEN_EEPROM_H_

#include <avr/interrupt.h>
#include "MangaScreen.h"

int EEPROM_Init(void);
void EnableI2CInterrupt(void);
void DisableI2CInterrupt(void);

int sync(char level, int timeout);
void I2C_Init(void);
int I2C_get_byte(char* data, int ack);
int I2C_put_byte(char data);
#endif


