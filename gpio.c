#include "gpio.h"

void pinMode(GPIO_TypeDef* port, int pin, int dir) {
	port->MODER |= ENABLE_PIN(dir, pin);
}

void pinWrite(GPIO_TypeDef* port, int pin, int state) {
	if (state == 1) {
		port->ODR |= (1 << pin);
	} else {
		port->ODR &= ~(1 << pin);
	}
}

void pinPull(GPIO_TypeDef* port, int pin, int state) {
	port->PUPDR |= ENABLE_PIN(state, pin);
}
