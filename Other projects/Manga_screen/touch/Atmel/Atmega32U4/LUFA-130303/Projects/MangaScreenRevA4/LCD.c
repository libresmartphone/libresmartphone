

#include "LCD.h"

int LCD_Init(void){

	DDRB |=  PIN_NCS; 	// PB0
	DDRB |=  PIN_SCLK;  // PB1
	DDRB |=  PIN_MOSI;  // PB2
	DDRB &= ~PIN_MISO;  // PB3
	DDRB |=  PIN_ST; 	// PB4
	DDRC |=  PIN_PD;	// PC7
	DDRD |=  PIN_SCDT;	// PD6	
	DDRE |=  PIN_RESET;	// PE6
	DDRD |=  PIN_BL;   	// PD7
	
	PORTE |= PIN_RESET; 	//Reset high				
	_delay_ms(100); 			// Wait for power to become stable.
	PORTE &= ~PIN_RESET; 	// Reset low
	_delay_ms(1); 			// Page 13 in manual for LCD
	PORTE |= PIN_RESET;		// Reset high
	_delay_ms(6); 			// Page 13 in manual for LCD

	LcdWrite(LCD_C, 0x11, 1); // Sleep out command
	_delay_ms(110);
	LcdWrite(LCD_C, 0x29, 1); // Display on command

	LCD_CS_Low();
	LcdWrite(LCD_C, 0x3A, 0); // Interface pixel format
	LcdWrite(LCD_D, 0x70, 0); // 24 bit
	LCD_CS_High();

	LCD_CS_Low();
	LcdWrite(LCD_C, 0x36, 0); // Memory Access Control
	LcdWrite(LCD_D, 0x00, 0); // 24 bit
	LCD_CS_High();

	return 0;		
}

void LCD_UnInit(void){
	LcdWrite(LCD_C, 0x28, 1); // Sleep out command
	_delay_ms(110);
	LcdWrite(LCD_C, 0x10, 1); // Display on command
}

/* Chip select low */ 
void LCD_CS_Low(void){
	PORTB &= ~PIN_NCS; 
}

/* Chiop select High */
void LCD_CS_High(void){
	PORTB |= PIN_NCS; 
}


void LcdExtended(void){
	LCD_CS_Low();
	LcdWrite(LCD_C, 0xB9, 0); // Set extended commands
	LcdWrite(LCD_D, 0xFF, 0);
	LcdWrite(LCD_D, 0x83, 0);
	LcdWrite(LCD_D, 0x63, 0);
	LCD_CS_High();
}

void LcdTest(void){
	/*char data;

	send("RDID2:");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, 0xDB, 0); // Read the version ID, should be 0x81
	data = LcdRead(1);
	hex(data);
	send("\n");

	send("Display power mode: ");
	P1OUT &= ~PIN_NCS; // Select Chip Enable low
	LcdWrite(LCD_C, 0x0A, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");
	if(data & (1<<7))
		send("\tBooster OK\n");
	else
		send("\tBooster Error\n");
	if(data & (1<<4))
		send("\tSleep out mode\n");
	else
		send("\tSleep in mode\n");
	if(data & (1<<3))
		send("\tDisplay mode normal\n");
	else
		send("\tDisplay mode not normal\n");
	if(data & (1<<2))
		send("\tDisplay is on\n");
	else
		send("\tDisplay is off\n");

	send("Display pixel format: ");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, 0x0C, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");
	if(data == 0x70)
		send("\t24 bit pixel format\n");
	else if(data == 0x50)
		send("\t16 bit pixel format\n");
	else if(data == 0x60)
		send("\t18 bit pixel format\n");
	else
		send("\tUnknown pixel format\n");

	send("Display image mode: ");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, 0x0D, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");

	send("Display signal mode: ");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, 0x0E, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");

	send("Display self diagnostic: ");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, 0x0F, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");
	if(data & (1<<7))
		send("\tOTP match\n");
	else
		send("\tOTP mismatch\n");
	if(data & (1<<6))
		send("\tBooster level and timings OK\n");
	else
		send("\tBooster shit error\n");

	send("RDRED: ");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, CMD_RDRED, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");
	send("RDBLUE: ");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, CMD_RDBLUE, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");
	send("RDGREEN: ");
	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, CMD_RDGREEN, 0);
	data = LcdRead(1);
	hex(data);
	send("\n");

	P1OUT &= ~PIN_NCS; 
	LcdWrite(LCD_C, 0xB3, 0); // Set RGB interface related register (B3h)
	LcdWrite(LCD_D, 0x01, 0); // EPL + VSPL + HSPL + DPL
	P1OUT |= PIN_NCS; 
	*/
}


// Write data to the display
void LcdWrite(char dnc, char data, char cs){
	int i;

	if(cs)
		LCD_CS_Low(); // Select Chip Enable low

	// Output the control bit DNC
	if(dnc)
		PORTB |= PIN_MOSI;
	else
		PORTB &= ~PIN_MOSI;
	PORTB &= ~PIN_SCLK; // Clock pin low
	PORTB |= PIN_SCLK; // Clock pin high

	// Output the data byte
	for(i=0; i<8; i++){
		if(data & (0x01<<(7-i)))
			PORTB |= PIN_MOSI;
		else
			PORTB &= ~PIN_MOSI;
		PORTB &= ~PIN_SCLK; // Clock pin low
		PORTB |= PIN_SCLK; // Clock pin high
	}

	if(cs)
		LCD_CS_High(); // Select Chip Enable High

}

char LcdRead(char cs){
	int i;
	char data = 0;

	// Get the data byte
	for(i=0; i<8; i++){
		PORTB &= ~PIN_SCLK; // Clock pin low
		PORTB |= PIN_SCLK; // Clock pin high
		if(PINB & PIN_MISO){
			data += (0x01<<(7-i));
		}
	}
	if(cs)
		PORTB |= PIN_NCS; // Select Chip Enable High

	return data;
}

/* Setup PWM on pin PD7, see page 162 in the Datasheet */
void BL_on(char duty){

	TCCR4B = (0<<PWM4X)  | (0<<PSR4) | (0<<DTPS41) | (0<<DTPS40) | (1<<CS43) | (0<<CS42) | (0<<CS41) | (1<<CS40); 
	TCCR4C = (1<<COM4D1) | (0<<COM4D0) | (0<<FOC4D) | (1<<PWM4D); 
	TCCR4D = (0<<WGM41)  | (0<<WGM40); // Count up -mode, Fast PWM if PWM4D == 1
	TCCR4E = (0<<TLOCK4) | (0<<ENHC4) | (0<<OC4OE5) | (0<<OC4OE4) | (0<<OC4OE3) | (0<<OC4OE2) | (0<<OC4OE1) | (0<<OC4OE0); 

	OCR4C = 0xFF;		// Top value of counter 
   	OCR4D = (0xFF-duty); 		//set 75% duty cycle 
}

/* Translate a byte to a hex string */
const char* to_hex(char x){
	static char h[] = "0x00"; 
	h[2] = TO_HEX(((x & 0xF0) >> 4));
	h[3] = TO_HEX(((x & 0x0F) >> 0));

	return h;
}

