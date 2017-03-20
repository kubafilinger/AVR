#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include "keyboard.h"

int main(void)
{
	DDRB = 0x00000001;
	PORTB = 0x11111110;
	
	setPorts(&DDRD, &PORTD, &PIND);

    while(1)
    {
		char key = pushKey();
		
		if(key == '7')
			PORTB ^= (1 << 0);
	}
}