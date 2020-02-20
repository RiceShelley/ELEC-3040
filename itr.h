#ifndef ITR_H
#define ITR_H

#include "stm32l100xc.h"

void enable_itr(void);

void clear_itr(IRQn_Type irq);

#endif
