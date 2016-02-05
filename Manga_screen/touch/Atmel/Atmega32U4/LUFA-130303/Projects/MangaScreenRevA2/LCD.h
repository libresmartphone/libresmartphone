/** Copyright 2013 Elias Bakken */

/* This file holds the methods for communicating with the 
LQ043.. LCD from SHARP */

#ifndef _MANGA_SCREEN_LCD_H_
#define _MANGA_SCREEN_LCD_H_

#include "MangaScreen.h"
#include <util/delay.h>
#include <avr/interrupt.h>

#define CMP_NOP 		0x00
#define CMD_SWRESET 	0x01
#define CMD_RDRED 		0x06
#define CMD_RDGREEN 	0x07
#define CMD_RDBLUE  	0x08
#define CMD_RDDPM   	0x0A
#define CMD_RDDMADCTL 	0x0B
#define CMD_RDDCOLMOD   0x0C

#define LCD_C     0
#define LCD_D     1

#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' - 10 + i)

// Function Definitions
int LCD_Init(void);
void LCD_UnInit(void);
void LcdExtended(void);
void LcdTest(void);
void LCD_CS_Low(void);
void LCD_CS_High(void);
void LcdWrite(char dnc, char data, char cs);
char LcdRead(char cs);
void BL_on(char duty);
void BL_off(void);
const char* to_hex(char x);

#endif

