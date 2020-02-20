#include "util.h"

void delay(void) {
	int i, j, k;
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 20000; j++) {
			k += j;	
		}
	}
}

void setup(void) {
	// Enable clock for GPIO port C
	RCC->AHBENR |= 0x04;
	// Enable clock for GPIO port B
	RCC->AHBENR |= 0x02;
	// Enable clock for GPIO port A
	RCC->AHBENR |= 0x01;
	
	// Set gpio pins to default values
	GPIOA->MODER = PORTA_RST;
	GPIOC->MODER = PORTC_RST;
	GPIOB->MODER = PORTC_RST;

	// Enable port c outputs
	for (int i = 0; i <= 4; i++) {
		pinMode(GPIOC, i, OUTPUT_MODE);
	}
	
	enable_itr();
}

int bcd_count(int* count, bool dir) {
	*count += (dir) ? 1 : -1;
	if (*count > 9) {
		*count = 0;
	} else if (*count < 0) {
		*count = 9;
	}
	return *count;
}
