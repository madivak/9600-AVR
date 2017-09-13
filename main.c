/*
 * GSM.c
 *
 * Created: 9/13/2017 8:26:18 AM
 * Author : madiva
 */ 
#define F_CPU 16000000UL

#define FOSC 2000000 // Clock Speed
#define BAUD 9600
#define MYUBRR (((FOSC / (9600 * 16UL))) - 1)

#include <avr/io.h>
#include "USART.h"

int main( void )
{
	USART_Init(MYUBRR);
	while(1)
	{
		unsigned char gps;
		
		gps=USART_Receive();
		USART_Transmit(gps);
	}
}

