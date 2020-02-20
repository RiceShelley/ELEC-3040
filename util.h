#ifndef UTIL_H
#define UTIL_H

#include "stm32l100xc.h"
#include "gpio.h"
#include "util.h"
#include "itr.h"

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

typedef enum {
	false,
	true
} bool;

void delay(void);

void setup(void);

int bcd_count(int* count, bool dir);

#endif
