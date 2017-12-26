#include "stm32l0xx.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "lld.h"
#include "delay.h"
#include "led_hendler.h"


int main(void) {
  if (SysTick_Config(SystemCoreClock/1000)) while(1);
  init_led_ports();
  
  while (1) {
    led_update();
    //printf("Test string %d \n", SystemCoreClock);
    //delay(50);
  }
}

extern "C" void assert_failed(char* file, unsigned long line) {
  while(1);
}
