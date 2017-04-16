#define F_CPU 8000000L

#include <avr/io.h>
#include "led_driver/led_driver.h"
#include "clock_driver/clock_driver.h"
#include <util/delay.h>

int main(void)
{
    LEDInit(6, &DDRD, &PORTD, &DDRC, &PORTC);
	set_timer_rtc();
    sei();
    
    LEDSetNumber(32);
    LEDSetValue("7 312");
    clearDisplay();
    
    while(1)
    {
// 		if(CLOCKStatus && (1 << CHANGE_STATUS))
// 		{
			int *tab = getTime();
		
			LEDSetPosition(0);
			LEDSetNumber(tab[0]);
		
			LEDSetPosition(2);
			LEDSetNumber(tab[1]);
		
			LEDSetPosition(4);
			LEDSetNumber(tab[2]);
			
// 			CLOCKStatus &= ~(1 << CHANGE_STATUS);
// 		}
	}
}