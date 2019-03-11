#include "led_driver.h"

ISR(TIMER1_OVF_vect)
{
	static volatile int src_nr = 0;

	src_nr = (src_nr + 1) % total_displays;

	turnOffAllDisplays();

	*digit_port = number[src_nr];

	if(led_type == KATODA)
	*display_port |= (1 << src_nr);
	else if(led_type == ANODA)
	*display_port &= ~(1 << src_nr);

	TCNT1 = 60000;
}

void LEDInit(uint8_t total_displays_f, uint8_t led_type_f, volatile uint8_t *digit_ddr_wsk, volatile uint8_t *digit_port_wsk, volatile uint8_t *display_ddr_wsk, volatile uint8_t *display_port_wsk)
{
	total_displays = total_displays_f % (8 + 1);
	led_type = led_type_f % 2;
	digit_ddr = digit_ddr_wsk;
	digit_port = digit_port_wsk;
	display_ddr = display_ddr_wsk;
	display_port = display_port_wsk;

	*digit_ddr = 0xFF; // wszystkie sa out dla cyfry, niezaleznie od typu wyswietlacza

	int i;

	for(i = 0; i < total_displays; i++)
	{
		*display_ddr |= (1 << i);
	}

	clearDisplay();
	set_timer1();
}

void LEDSetValue(char *val)
{
	int i;

	for(i = 0; i < total_displays; i++)
	{
		if(val[i] == '\0')
		break;

		number[(i + position) % total_displays] = (led_type & KATODA) ? ~convertChar(val[i]) : convertChar(val[i]);
	}
}

void LEDSetPosition(uint8_t pos)
{
	position = pos % MAX_NUM_DISPLAY;
}

void LEDSetNumber(int nr)
{
	char s[MAX_NUM_DISPLAY + 1]; // +1 end char
	sprintf(s, "%d\0", nr);
	LEDSetValue(s);
}

void LEDSetNumberWithZero(int nr)
{
	char s[MAX_NUM_DISPLAY + 1]; // +1 end char

	if(nr < 10)
	sprintf(s, "0%d\0", nr);
	else
	sprintf(s, "%d\0", nr);

	LEDSetValue(s);
}

void clearDisplay()
{
	int i;

	for(i = 0; i < total_displays; i++)
	{
		if(led_type == KATODA) {
			number[i] = 0xFF;
		}
		else if(led_type == ANODA) {
			number[i] = 0;
		}
	}

	position = 0;
}

void turnOffAllDisplays()
{
	int i;

	for(i = 0; i < total_displays; i++)
	{
		if(led_type == KATODA) {
			*display_port &= ~(1 << i);
		}
		else if(led_type == ANODA) {
			*display_port |= (1 << i);
		}
	}
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

		case 'A':
		result = 0b01110111;
		break;

		case 'B':
		result = 0b01111111;
		break;

		case 'b':
		result = 0b01111100;
		break;

		case 'C':
		result = 0b111001;
		break;

		case 'c':
		result = 0b1011000;
		break;

		case 'd':
		result = 0b1011110;
		break;

		case 'E':
		result = 0b1111001;
		break;

		case 'F':
		result = 0b1110001;
		break;

		case 'G':
		result = 0b111101;
		break;

		case 'H':
		result = 0b1110110;
		break;

		case 'h':
		result = 0b1110100;
		break;

		case 'I':
		result = 0b110;
		break;

		case 'i':
		result = 0b100;
		break;

		case 'J':
		result = 0b1111;
		break;

		case 'j':
		result = 0b1110;
		break;

		case 'L':
		result = 0b111000;
		break;

		case 'O':
		result = 0b111111;
		break;

		case 'o':
		result = 0b1011100;
		break;

		case 'P':
		result = 0b1110011;
		break;

		case 'S':
		result = 0b1101101;
		break;

		case 'T':
		result = 0b110001;
		break;

		case 't':
		result = 0b1111000;
		break;

		case 'U':
		result = 0b111110;
		break;

		case 'u':
		result = 0b11100;
		break;

		case 'Y':
		result = 0b1100110;
		break;

		case 'Z':
		result = 0b1011011;
		break;

		case '.':
		result = 0b10000000;
		break;

		case '-':
		result = 0b1000000;
		break;

		case '_':
		result = 0b1000;
		break;

		case '=':
		result = 0b1001000;
		break;

		default:
		result = 0;
		break;
	}

	return result;
}

void set_timer1()
{
	TCCR1B |= 1 << CS10;
	TIMSK |= 1 << TOIE1;
	TCNT1 = 60000;
}

void LEDDot(uint8_t dot)
{
	uint8_t result;

	result = (led_type & KATODA) ? ~number[position] : number[position];

	if(dot == DEL_DOT)
	{
		result &= ~convertChar('.');
	}
	else
	{
		result |= convertChar('.');
	}

	number[position] = (led_type & KATODA) ? ~result : result;
}