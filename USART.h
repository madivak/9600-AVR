/*
 * IncFile1.h
 *
 * Created: 9/13/2017 8:26:37 AM
 *  Author: madiv
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

void USART_Init( unsigned int ubrr);
void USART_Transmit( unsigned char data );
/*unsigned char USART_Receive( void );*/

void USART_Init1( unsigned int ubrr);
/*void USART_Transmit1( unsigned char data );*/
unsigned char USART_Receive1( void );

#endif /* INCFILE1_H_ */