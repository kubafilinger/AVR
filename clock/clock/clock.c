#define F_CPU 8000000L

#include "led_driver/led_driver.h"
#include "clock_driver/clock_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
    DDRB = 0x00000001;
	PORTB = 0b00011110;
	
	LEDInit(6, &DDRD, &PORTD, &DDRC, &PORTC);
	CLOCKInit();
	sei();
	
	clearDisplay();
	CLOCKStart();
	
	while(1)
	{
		if(CLOCKStatus & (1 << CHANGE_STATUS))
		{
			int *tab = getTime();
		
			LEDSetPosition(0);
			LEDSetNumberWithZero(tab[0]);
		
		 	LEDSetPosition(2);
		 	LEDSetNumberWithZero(tab[1]);
		 		
			LEDSetPosition(4);
			LEDSetNumberWithZero(tab[2]);
		
 		 	CLOCKStatus &= ~(1 << CHANGE_STATUS);
 		}
	}
}