#define MAX_NUM_DISPLAY 8

#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t total_displays;
uint8_t position;
volatile uint8_t number[MAX_NUM_DISPLAY];
volatile uint8_t *digit_ddr;
volatile uint8_t *digit_port; // HIGH level control
volatile uint8_t *display_ddr;
volatile uint8_t *display_port; // LOW level control

void LEDInit(uint8_t, volatile uint8_t *, volatile uint8_t *, volatile uint8_t *, volatile uint8_t *);
void LEDSetValue(char *);
void LEDSetNumber(int);
void LEDSetPosition(uint8_t);
void clearDisplay();
uint8_t convertChar(char);
void setTimer0();

#include "led_driver.c"