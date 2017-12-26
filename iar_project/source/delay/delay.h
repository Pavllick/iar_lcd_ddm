#ifndef DEALY_H
#define DEALY_H

#include "stm32l053xx.h"

//inline void assert(uint8_t condition);
void delay(uint32_t delayMillis);
extern "C" void SysTick_Handler(void);


#endif