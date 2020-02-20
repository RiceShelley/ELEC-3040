#include "STM32L1xx.h" 

#include "gpio.h"
#include "itr.h"
#include "util.h"
#include "keypad.h"
#include "timer.h"

bool start = false;

int time_sec = 0;
int time_sub_sec = 0;

void update_display() {
	GPIOC->ODR = time_sec & (time_sub_sec << 4);
}

int main() {
	setup();
	initKeypad();
	timerSetup();
	
	while (true) {
		// Nothing to do but wait.
	}
}

/*
* Keypad ITR
*/
void EXTI1_IRQHandler() {
	__disable_irq();
	
	keypad_value = readKeypad();
	if (keypad_value == 0) {
		start = !start;
		if (start) {
			// Start stopwatch counting
			timerStart();
		} else {
			// Pause stopwatch counting
			timerOff();
		}
	} else if (keypad_value == 1) {
		// Reset to zero ONLY IF stop watch is NOT counting
		if (!start) {
			time_sec = 0;
			time_sub_sec = 0;
			update_display();
		}
	}
	
	clear_itr(EXTI1_IRQn);
	__enable_irq();
}

void TIM6_IRQHandler() {
	
	int last_time_sub_sec = time_sub_sec;
	bcd_count(&time_sub_sec, 1);
	
	/*
	* If the tenth of a second clock goes 
	* from 9 to 0 then increment single second clock
	*/
	if (last_time_sub_sec == 9 && time_sub_sec == 0) {
		bcd_count(&time_sec, 1);
	}
	
	// Display time
	update_display();
	clear_timer_flags();
}
