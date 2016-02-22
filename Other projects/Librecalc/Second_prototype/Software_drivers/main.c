#define NO_BIT_DEFINES
#include <pic16f722a.h>
#include <math.h>

#define COLUMN  8
#define LINE    8

#define __CONFIG 0x2007
__code short __at (__CONFIG) cfg0 = _INTRC_OSC_NOCLKOUT & _WDT_OFF & _PWRTE_OFF & _MCLRE_OFF & _BOR_OFF;

unsigned char currentState[COLUMN][LINE];

void send(char c)
{
	TXREG = c;
	while(!PIR1bits.TXIF);
}

void main() 
{
    long count;

    // Init state array
    char i,j;
    for(i=0 ; i<COLUMN ; i++)
    {
        for(j=0 ; j<LINE ; j++)
        {
            currentState[i][j] = 1;
        }
    }

    //  Init uart
    SPBRG = 25; // 4800 bps @ 8Mz

    TRISC = 0x40;

    TXSTA = 0;           
    RCSTA = 0;
    RCSTAbits.CREN = 1;
    RCSTAbits.SREN = 1;
    TXSTAbits.BRGH = 0;
    PIR1bits.TXIF = 0;
    PIE1bits.RCIE = 0;
    PIR1bits.RCIF = 0;
    PIE1bits.TXIE = 0;
    TXSTAbits.TXEN = 1;
    RCSTAbits.SPEN = 1;

    // Ouput on port A
    ANSELA = 0;
    TRISA = 0;
    PORTA = 0;

    // Input on port B
    ANSELB = 0;
    TRISB = 0xFF;
    OPTION_REG = 0xEF && OPTION_REG;
    WPUB = 0xFF;

    while (1) 
    {
        PORTA = 254;

        for(i=0 ; i<COLUMN ; i++)
        {
            for(j=0 ; j<LINE ; j++)
            {
                unsigned char value = ((PORTB >> j) & 1) ^ 1;

                if(currentState[i][j] != value)
                {
                    currentState[i][j] = value;
                    send(j + ( i * LINE ) + (value * COLUMN * LINE));
                }
            }

	    if(i == 0)
	    {
		    PORTA = 253;
	    }
	    else if(i == 1)
	    {
		    PORTA = 251;
	    } 
	    else if(i == 2)
	    {
		    PORTA = 247;
	    } 
	    else if(i == 3)
	    {
		    PORTA = 239;
	    } 
	    else if(i == 4)
	    {
		    PORTA = 223;
	    } 
	    else if(i == 5)
	    {
		    PORTA = 191;
	    } 
	    else if(i == 6)
	    {
		    PORTA = 127;
	    } 
	    else if(i == 7)
	    {
		    // dernier passage dans la boucle donc rien a faire
	    }

	    for(count = 0 ; count < 100 ; count++){} //delay
        }
    }
}
