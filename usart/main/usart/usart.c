#include "usart.h"

ISR(USART_UDRE_vect)
{
	//przerwanie generowane, gdy bufor nadawania jest już pusty

	UDR = *string++;
	
	if(*string == 0)
		UCSRB &= ~(1<<UDRIE); //wyłącz przerwania pustego bufora nadawania
}

void defineBaud() 
{
	#define BAUD 9600
	#include <util/setbaud.h>

	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	#if USE_2X
	UCSRA |= (1 << U2X);
	#else
	UCSRA &= ~(1 << U2X);
	#endif
}

/*
Data bits:
	5-bit:
	6-bit: (1 << UCSZ0)
	7-bit: (1 << UCSZ1)
	8-bit: (1 << UCSZ1) | (1 << UCSZ0)
	9-bit: (1 << UCSZ2) | (1 << UCSZ1) | (1 << UCSZ0)
	
Stop bits:
	1-bit: 
	2-bit: (1 << USBS)

Asynchronous:
Synchronous: (1 << UMSEL)
*/
void usartInit()
{
	defineBaud();

	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UCSRB = (1 << TXEN);
}

void send(char* ch)
{
	string = ch;
	UCSRB |= (1 << UDRIE); // wlacz przerwanie
}