#include "delay.h"

void delay(uint32_t delayMillis) {
  
    uint32_t delayTime = delayMillis * 1000;
    while(delayTime > 0) delayTime--;
}