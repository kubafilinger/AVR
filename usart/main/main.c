#define F_CPU 8000000L

#include "usart/usart.c"
#include <avr/interrupt.h>
#include <avr/io.h>  
#include <stdio.h>
#include <util/delay.h>

int main(void)
{
	usartInit();

	sei();

	DDRC = 1;
	PORTC = 0b11111110;

	while(1)
	{
		//send("test\n\r");
		char* xd = {"Ala is %d years old\n\r"};
		sprintf(xd, xd, 21);
		
		send(xd);
		
		_delay_ms(1000);
	}
}