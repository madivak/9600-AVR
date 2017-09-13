/*
 * TEST-USART.c
 *
 * Created: 8/30/2017 12:14:36 PM
 * Author : madiv
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 1000000 // Clock Speed
//#define BAUD 4800
#define MYUBRR0 (((FOSC / (4800 * 16UL))) - 1)
#define MYUBRR1 (((FOSC / (9600 * 16UL))) - 1)

void USART_Init0( unsigned int ubrr);
void USART_Init1( unsigned int ubrr);
void USART_Transmit0( unsigned char data0 );
unsigned char USART_Receive0( void );
void USART_Transmit1( unsigned char data1 );
unsigned char USART_Receive1( void );
void USART_putstring(char* StringPtr);

char String[]="Begin";	 //String[] is in fact an array but when we put the text between the " " symbols the compiler threats it as a String and automatically puts the null termination character in the end of the text

int main( void )
{
	USART_Init0(MYUBRR0);
	USART_Init1(MYUBRR1);
	while (1)
	{
		unsigned char gps;
		
		gps=USART_Receive1();
		
//		USART_Transmit0(USART_Receive1());
		USART_Transmit0(gps);     //Infinite loop	
	}
	return 0;
}

void USART_Init0( unsigned int ubrr)
{
	unsigned int baud0 = ubrr;
	/*Set baud rate */
	UBRR0H = (unsigned char)(baud0>>8);
	UBRR0L = (unsigned char)baud0;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Init1( unsigned int ubrr)
{
	unsigned int baud1 = ubrr;
	/*Set baud rate */
	UBRR1H = (unsigned char)(baud1>>8);
	UBRR1L = (unsigned char)baud1;
	/* Enable receiver and transmitter */
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS1)|(3<<UCSZ10);
}

void USART_Transmit0( unsigned char data0 )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );	;
	/* Put data into buffer, sends the data */
	UDR0 = data0;
}

unsigned char USART_Receive0( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}

void USART_Transmit1( unsigned char data1 )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR1A & (1<<UDRE1)) );	;
	/* Put data into buffer, sends the data */
	UDR1 = data1;
}

unsigned char USART_Receive1( void )
{
	/* Wait for data to be received */
	while ( !(UCSR1A & (1<<RXC1)));
	/* Get and return received data from buffer */
	return UDR1;
}

void USART_putstring(char* StringPtr){
	
	while(*StringPtr != 0x00){
		USART_Transmit1(*StringPtr);
	StringPtr++;}
	
}
