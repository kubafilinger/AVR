#define MAX_NUM_DISPLAY 8

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t total_displays;
uint8_t position;
volatile uint8_t number[MAX_NUM_DISPLAY];
volatile uint8_t *digit_ddr;
volatile uint8_t *digit_port;
volatile uint8_t *display_ddr;
volatile uint8_t *display_port;

void LEDInit(uint8_t, volatile uint8_t *, volatile uint8_t *, volatile uint8_t *, volatile uint8_t *);

void LEDSetValue(char *);

void LEDSetNumber(int);

// 1 - 9 -> 01 - 09
void LEDSetNumberWithZero(int);

// set position first char on screen. 0 - first, 1 - second, etc.
void LEDSetPosition(uint8_t);

void clearDisplay();

uint8_t convertChar(char);

void setTimer0();

#include "led_driver.c"