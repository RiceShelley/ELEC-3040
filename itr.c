#include "itr.h"

void enable_itr(void) {
	// interupt sorce port a
	SYSCFG->EXTICR[0] &= 0xFFF0;
	// trig on rising edges
	//EXTI->RTSR = 0x3;
	EXTI->FTSR = 0x3;
	// Interupt mask register
	EXTI->IMR = 0x3;
	// clear flags
	EXTI->PR = 0;
	
	// Enable NVIC interupt stuff
	//NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	
	//NVIC_ClearPendingIRQ(EXTI0_IRQn);
	NVIC_ClearPendingIRQ(EXTI1_IRQn);
	
	//NVIC_SetPriority(EXTI0_IRQn, 1);
	//NVIC_SetPriority(EXTI0_IRQn, 2);
	
	__enable_irq();
}

void clear_itr(IRQn_Type irq) {
	EXTI->PR &= 0xFF;
	NVIC_ClearPendingIRQ(irq);
}
