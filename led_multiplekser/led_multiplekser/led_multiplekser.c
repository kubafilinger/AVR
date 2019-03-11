#define F_CPU 8000000L

#include "led_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	LEDInit(6, KATODA, &DDRD, &PORTD, &DDRC, &PORTC);

	sei();

	LEDSetNumber(32);
	clearDisplay();
	LEDSetValue("7 312");
	LEDSetPosition(2);

	LEDDot(PUT_DOT);
	_delay_ms(2000);

	LEDDot(DEL_DOT);
	_delay_ms(2000);

	char chars[30] = "ABbCcEFGHhIiJjLOoPSTtUuYZ=-_.";

	while(1)
    {
		int static a = 0;

		clearDisplay();
		LEDSetValue("ABbCcd");
		_delay_ms(5000);

		clearDisplay();
		LEDSetValue("EFGHhI");
		_delay_ms(5000);

		clearDisplay();
		LEDSetValue("iJjLOo");
		_delay_ms(5000);

		clearDisplay();
		LEDSetValue("PSTtUu");
		_delay_ms(5000);

		clearDisplay();
		LEDSetValue("YZ_-.=");
		_delay_ms(5000);
	}
}