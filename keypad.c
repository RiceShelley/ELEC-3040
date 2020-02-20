#include "keypad.h"

static int small_delay(void) {
	int k = 0;
	for (int i = 0; i < 100; i++) {
		k *= k;
	}
	return k;
}

static void waiting_state() {
	// set all col as outputs
	for (int i = 0; i < 4; i++) {
		pinMode(GPIOB, i, OUTPUT_MODE);
	}
	small_delay();
	// drive all col lines low
	for (int i = 0; i < 4; i++) {
		pinWrite(GPIOB, i, LOW);
	}
	
	// set all rows as inputs
	for (int i = 4; i < 8; i++) {
		pinMode(GPIOB, i, INPUT_MODE);
	}
	small_delay();
	// pull all rows high
	for (int i = 4; i < 8; i++) {
		pinPull(GPIOB, i, PULL_UP);
	}
}

void initKeypad(void) {
	waiting_state();
}

static int four_two_encoder(uint8_t val) {
	switch(val) {
		case 0x1:
			return 0;
		case 0x2:
			return 1;
		case 0x4:
			return 2;
		case 0x8:
			return 3;
		default:
			return 0;
	}
}

static uint8_t readRows(void) {
	return ((uint8_t) (~(GPIOB->IDR >> 4) & 0x000F));
}

static uint8_t decode_key[] = {
	1,
	2,
	3,
	10,
	4, 
	5, 
	6,
	11,
	7,
	8,
	9,
	12,
	14,
	0,
	15,
	13
};

uint8_t readKeypad(void) {
	// find the row that is down
	uint8_t row = readRows();
	
	for (int i = 0; i < 4; i++) {
		GPIOB->ODR = ~(1 << i);
		small_delay();
		uint8_t new_row = readRows();
		if (new_row == row) {
			waiting_state();
			return decode_key[four_two_encoder(row) * 4 + i];
		}
	}
	waiting_state();
	return 0;
}
