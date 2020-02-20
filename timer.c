#include "timer.h"
// Uses Timer 6 (TIM6->...)
// TIMx_ARR holds max value. Interrupt when TIMx_CNT reaches TIMx_ARR
// Uses STM32L100's default 2.097 MHz (0x200000 Hz)
// T = (PSC + 1)*(ARR +1)/CLK_freq
// Using ARR=0x20C3 and PSC=0x018 -- Should be exact 0.1s
// Timer 6 is IRQ 43


// NVIC_EnableIRQ(TIM6_IRQ7) // To set TIM6 interrupt as IRQ7
// TIM6 IRQHandler()
//TIM6->CR1 |= 0x01; //Enable timer's counting (Bit 0 = CEN)
//TIM6->SR &= ~0x01; //Clear timer's interrupt flag
// NVIC_ClearPendingIRQ(TIM6_IRQ43)
//TIM6->DIER |= 0x01; //Enable timer interrupt
//RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; //Enable clock for timer
//TIM6->PSC = 0x0018;
//TIM6->ARR = 0x20C3;
void timerSetup() //Using Timer 6, Every 0.1s interrupt
{
	TIM6->PSC = 0x0018;
	TIM6->ARR = 0x20C3;
	TIM6->DIER |= 0x01;
	TIM6->SR &= ~0x01; //Just in case
}

void timerStart()
{
	__enable_irq();
	NVIC_EnableIRQ(TIM6_IRQn);
	TIM6->CR1 |= 0x01;
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
}

void clear_timer_flags()
{
	TIM6->SR &= ~0x01;
	NVIC_ClearPendingIRQ(TIM6_IRQn);
}

void timerOff()
{
	TIM6->CR1 &= ~0x01;
	RCC->APB1ENR &= ~RCC_APB1ENR_TIM6EN;
	TIM6->CNT &= 0x0000;
}

void timerOn()
{
	TIM6->CR |= 0x01;
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
}