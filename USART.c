/*
 * CFile1.c
 *
 * Created: 9/13/2017 8:26:57 AM
 *  Author: madiva
 */ 
#include <avr/io.h>
#include "USART.h"

void USART_Init( unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	//Enable receiver and transmitter 
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	//Normal speed mode
	UCSR0A = (1<<U2X0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_putstring(char* StringPtr)
	while(*StringPtr != 0x00)
	{
		USART_Transmit(*StringPtr);
	StringPtr++;
	}
}