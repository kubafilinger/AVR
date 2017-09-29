#define F_CPU 8000000L
#define MAX_STRING_LENGTH 100

#include <avr/interrupt.h>
#include <avr/io.h>

volatile char* string;

void defineBaud();
void usartInit();
void send(char*);