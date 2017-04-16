#define F_CPU 8000000L

#include <avr/io.h>
#include "led_driver.h"

#include <util/delay.h>

int main(void)
{
	LEDInit(6, &DDRD, &PORTD, &DDRC, &PORTC);
	sei();
	
	LEDSetNumber(32);
	LEDSetValue("7 312");
	clearDisplay();
	int b = 0;
	LEDSetPosition(5);
    while(1)
    {
		int static a = 0;

		if(a == 150)
			b = 1;
		else if(a == 0)
			b = 0;
			
		(b) ? LEDSetNumber(a--) : LEDSetNumber(a++);
		

		_delay_ms(100);
	}
}