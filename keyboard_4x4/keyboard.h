/************************************************************************/
/* SPECIFICATION:

ports 0-3 OUTPUTS and changing in loop
ports 4-7 INPUTS and listen HIGH state

INICIALIZATION:
1. setPorts() - required 8 identical pors
2.                                                                      */
/************************************************************************/

volatile uint8_t * KEYBOARD_DDR = 0;
volatile uint8_t * KEYBOARD_PORT = 0;
volatile uint8_t * KEYBOARD_PIN = 0;
volatile uint8_t checkPush = 0;
char keyboard[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

void setPorts(volatile uint8_t *, volatile uint8_t *, volatile uint8_t *);
char pushKey();

void setPorts(volatile uint8_t * ddr, volatile uint8_t * port, volatile uint8_t * pin) {
	
	KEYBOARD_DDR = ddr;
	KEYBOARD_PORT = port;
	KEYBOARD_PIN = pin;
	
	*KEYBOARD_DDR = 0b00001111;
	*KEYBOARD_PORT = 0b11111111;
}

char pushKey() {
	int i, j;
	
	for(i = 0; i < 4; i++)
	{
		*KEYBOARD_PORT &= ~(1 << i);

		for(j = 0; j < 4; j++)
		{
			if(!(*KEYBOARD_PIN & (1 << (j + 4))))
			{
				char key = keyboard[3 - j][3 - i];
				 	
				_delay_ms(20);
				while(!(*KEYBOARD_PIN & (1 << (j + 4))));
				
				return key;
			}
		}

		*KEYBOARD_PORT |= (1 << i);
	}
}