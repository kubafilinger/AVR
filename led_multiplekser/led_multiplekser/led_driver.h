#define MAX_NUM_DISPLAY 8 

uint8_t total_displays;
volatile uint8_t number[MAX_NUM_DISPLAY];
volatile uint8_t *digit_ddr;
volatile uint8_t *digit_port; // sterowanie HIGH
volatile uint8_t *display_ddr;
volatile uint8_t *display_port; // sterowanie LOW

void LEDInit(uint8_t, volatile uint8_t *, volatile uint8_t *, volatile uint8_t *, volatile uint8_t *);
void LEDSetValue(char *);
void LEDSetNumber(int);
void clearDisplay();
uint8_t convertChar(char);
void setTimer0();

#include "led_driver.c"