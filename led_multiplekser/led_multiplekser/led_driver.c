#ifndef F_CPU
#define F_CPU 8000000L
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER0_OVF_vect)
{
	static volatile int src_nr = 0, licznik = 0;
	
	if(licznik++ == 10)
	{
		src_nr = (src_nr + 1) % total_displays;
		
		*display_port = ~(1 << src_nr);
		*digit_port = number[src_nr];
	
		licznik = 0;
	}
	
	asm volatile ("nop");
}

void LEDInit(uint8_t total, volatile uint8_t *digit_ddr_wsk, volatile uint8_t *digit_port_wsk, volatile uint8_t *display_ddr_wsk, volatile uint8_t *display_port_wsk)
{
	total_displays = total;
	digit_ddr = digit_ddr_wsk;
	digit_port = digit_port_wsk;
	display_ddr = display_ddr_wsk;
	display_port = display_port_wsk;
	
	*digit_ddr = 0xFF;
	*digit_port = 0;
	*display_ddr = 0;
	*display_port = 0xFF;
	
	int i;
	for(i = 0; i < total_displays; i++)
	{
		*display_ddr |= (1 << i); // set OUT
	}
	
	set_timer0();
}

void LEDSetValue(char *val)
{
	int i;
	
	for(i = 0; i < total_displays; i++)
	{
		number[i] = convertChar(val[i]);
		
		if(val[i] == '\0')
			break;
	}
}

void LEDSetNumber(int nr)
{
	char s[MAX_NUM_DISPLAY + 1]; // +1 end char
	sprintf(s, "%d\0", nr);
	LEDSetValue(s);
}

void clearDisplay()
{
	int i;
	
	for(i = 0; i < total_displays; i++)
		number[i] = 0;
}

uint8_t convertChar(char s)
{
	uint8_t result = 0;
	
	switch(s)
	{
		case '0':
			result = 0b00111111;
			break;
		
		case '1':
			result = 0b00000110;
			break;
		
		case '2':
			result = 0b01011011;
			break;
		
		case '3':
			result = 0b01001111;
			break;
		
		case '4':
			result = 0b01100110;
			break;
		
		case '5':
			result = 0b01101101;
			break;
		
		case '6':
			result = 0b01111101;
			break;
		
		case '7':
			result = 0b00000111;
			break;
		
		case '8':
			result = 0b01111111;
			break;
		
		case '9':
			result = 0b01101111;
			break;
			
		default: // null
			result = 0;
			break;
	}
	
	return result;
}

void set_timer0()
{
	TCCR0 = 1 << CS01;
	TIMSK |= 1 << TOIE0;
}