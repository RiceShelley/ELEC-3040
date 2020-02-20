#include "STM32L1xx.h" 

#include "gpio.h"
#include "itr.h"
#include "util.h"
#include "keypad.h"

bool keypad_pressed = 0;
uint8_t keypad_value = 0;
int timer = 0;

int main() {
	setup();
	initKeypad();
	
	int count = 0;
	uint8_t val = 0;
	
	while (true) {
		delay();
		timer++;
		// otherwise count and display
		val = bcd_count(&count, 1);
		
		// if keypad was pressed display value
		if (keypad_pressed) {
			val = keypad_value;
			// stop displaying keypad value after 5 seconds
			if (timer > 3) {
				keypad_pressed = false;
			}
		}
		GPIOC->ODR = val;
	}
}

/*
* Read from keypad
*/
void EXTI1_IRQHandler() {
	__disable_irq();
	
	keypad_value = readKeypad();
	keypad_pressed = true;
	timer = 0;
	GPIOC->ODR = keypad_value;
	
	clear_itr(EXTI1_IRQn);
	__enable_irq();
}
