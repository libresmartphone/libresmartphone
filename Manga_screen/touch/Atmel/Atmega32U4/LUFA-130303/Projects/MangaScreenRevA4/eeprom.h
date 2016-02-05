
#ifndef _MANGA_SCREEN_EEPROM_H_
#define _MANGA_SCREEN_EEPROM_H_


#include "MangaScreen.h"
#include <stdlib.h>
#include <stdio.h>
#include <avr/eeprom.h>

int read_brightness(void);
void write_brightness(int brightness);

int read_debug_level(void);
void write_debug_level(int level);

void write_digitizer_config(int config);
int read_digitizer_config(void);
#endif
