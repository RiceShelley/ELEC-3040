#ifndef GPIO_H
#define GPIO_H

#include "stm32l100xc.h"

#define PORTA_RST 0xA8000000
#define PORTC_RST 0x00000000

#define OUTPUT_MODE 0x01
#define INPUT_MODE 0x00

#define HIGH 1
#define LOW 0

#define PULL_DOWN 0x10
#define PULL_UP 0x01

#define ENABLE_PIN(mode, pin_num) (mode << (pin_num * 2))

void pinMode(GPIO_TypeDef* port, int pin, int dir);

void pinWrite(GPIO_TypeDef* port, int pin, int state);

void pinPull(GPIO_TypeDef* port, int pin, int state);

#endif
