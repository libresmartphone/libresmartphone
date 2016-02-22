

#include "EEPROM.h"

#define SCL	(1<<PD3)		//PORTD.0 PIN AS SCL PIN
#define SDA	(1<<PD5)		//PORTD.1 PIN AS SDA PIN

#define HPD _delay_us(10)
#define QPD	_delay_us(5)

#define COND_NONE    0
#define COND_START   1
#define COND_STOP	 2
#define COND_TIMEOUT 3
#define COND_ACK	 4

char edid[] = {0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x24, 0x27, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x19, 0x17, 0x1, 0x3, 0x81, 0xa, 0x6, 0x78, 0xe7, 0x0, 0x0, 0xa2, 0x57, 0x4b, 0x97, 0x24, 0x18, 0x4f, 0x53, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x0, 0x9b, 0x9, 0xe0, 0x20, 0x10, 0x20, 0xc, 0x30, 0x5, 0x6, 0x33, 0x0, 0x38, 0x5d, 0x0, 0x0, 0x0, 0x18, 0x0, 0x0, 0x0, 0xfc, 0x0, 0x4d, 0x61, 0x6e, 0x67, 0x61, 0x20, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6e, 0xa, 0x0, 0x0, 0x0, 0xfd, 0x0, 0x37, 0x41, 0x2a, 0x43, 0x3, 0x0, 0xa, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0, 0x0, 0x0, 0xfe, 0x0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0, 0x0, 0x0, 0x5d, 0xAA};

char buffer[100];
int b_cnt = 0;
char c_addr; // Chip address 
char d_addr = 0;
int read_addr;
int cond;

int EEPROM_Init(){
	I2C_Init();
	EnableI2CInterrupt();

	return 0;
}

/* Enable ionterrupt on falling edge */
void EnableI2CInterrupt(){
	EICRA |= (1<<ISC31) | (0<<ISC30); 	// INT3 interrupts on falling edge
	EIMSK |= (1<<INT3);				 	// INT3 enable
}

/* Disable interrupt in INT3 */
void DisableI2CInterrupt(){
	EIMSK &= ~(1<<INT3);				 // INT3 disbale
}

/* This routine is run when a 0->1 transition occurs on PB3 */
ISR(INT3_vect){
	char cond; 
	if((cond = (char) I2C_get_byte(&c_addr, 1)) != 0){ 	// Receive the address 0x50 + R/W bit
		return;
	}

	if((c_addr >> 1) != 0x50){ 							// This is not for us
		return; 
		
	}
	if(c_addr & 0x01){ 	 								// This is a read operation 
		while(1){
			cond = I2C_put_byte(edid[read_addr]);
			read_addr++;
			if(read_addr > 128)							// Cap that beach, yo. 
				read_addr = 128;
			if(cond == COND_ACK)
				continue;			
			if(cond == COND_NONE)
				return;
			printf("Err: %x\n", cond);
			return;				
		}
	}
	else{											// This is a write operation 
		if(I2C_get_byte(&d_addr, 1) == 0){			// Clock in the first address byte
			read_addr = 0; //(int) d_addr;				// Set the read/write pos
		}
	}
}

void I2C_Init(){
	DDRD &= ~SCL;  // PD3 input 
	DDRD &= ~SDA;  // PD5 input
	PORTD &= ~SDA; // Drive SDA low. 
}

// Wait for Start, stop or none-condition 
int wait_for_condition(int timeout){
	int before = (PIND & SDA);
	while((PIND & SCL) && timeout--){	
		if((PIND & SDA) != before){
			if((PIND & SDA) == 0)
				return COND_START;
			return COND_STOP;
		}
	}
	return (timeout ? COND_NONE : COND_TIMEOUT);
}

//Wait for edge to change
int sync(char level, int timeout){
	while((PIND & SCL) == level && timeout--); 
	if(timeout)
		return 0;
	return COND_TIMEOUT;
}

// Looks like the speed is 100KHz. 
int I2C_get_byte(char *data, int ack){
	int i;
	*data = 0;

	DDRD  &= ~SDA; 			// input

	for(i=7; i>=0; i--){
		sync(0, 30);						// Sync on rising
		HPD;								// Wait a half period		
		*data |= (((PIND & SDA)?1:0)<<i);	// Set the data
		cond = wait_for_condition(100);		// Wait for cond or dropping pin 
		if(cond != COND_NONE)
			return cond;
		HPD;
	}			

	if(ack)
		DDRD  |=  SDA; 		// Make SDA output
	sync(0, 100);			// Sync on rising
	sync(SCL, 100); 		// Sync on falling
	QPD;					// Wait
	DDRD  &= ~SDA; 			// Release the ACk
	return 0;
}


// Looks like the speed is 100KHz. 
int I2C_put_byte(char data){
	int i;
	int ack; 

	for(i=7; i>=0; i--){		
		if(data & (1<<i))
			DDRD &= ~SDA;				// Input
		else
			DDRD  |=  SDA; 				// output
		sync(0, 100); 					// Sync on rising SCK edge
		cond = wait_for_condition(27);	// Sync on falling edge
		if(cond != COND_NONE){
			DDRD  &= ~SDA; 				// input
			return cond;
		}
		QPD;
	}		
	DDRD  &= ~SDA; 						// input
	sync(0, 1000); 						// Sync on rising SCK edge	
	HPD;
	ack = ((PIND & SDA)?0:COND_ACK);			// If the pin is low, the master has ackglowledged
	sync(SCL, 1000); 					// Sync on falling SCK edge	
	QPD;								// Half period delay
	
	return ack;
}



