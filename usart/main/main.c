#define F_CPU 8000000L

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "usart.h"

int main(void)
{
	usartInit();

	sei();

	char txt[200];
	float f = 1202.9377;
	uint32_t i = 12345678;
	char* s = "This is char";

	//sprintf(txt, "float = %f, unsigned long = %lu, text = %s\r\n", f, i, s);
	sprintf(txt, "test usart");

	while(1)
	{
		send(txt);

		_delay_ms(1000);
	}
}