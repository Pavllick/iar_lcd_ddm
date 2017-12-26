#include "led_hendler.h"

void led_update() {
  for(int i = 0; i <= 13; i++) {
    toggle_pin(pins_com[i]);
  }
  
  for(int i = 0; i <= 13; i++) {
    set_pin(pins_pin[i]);
  }
}

void init_led_ports() {
  rccEnableGPIOA();
  rccEnableGPIOB();
  rccEnableGPIOC();
  rccEnableGPIOD();
  
  gpioPinMode(COM_0,  gpioMode_output);
  gpioPinMode(COM_1,  gpioMode_output);
  gpioPinMode(COM_2,  gpioMode_output);
  gpioPinMode(COM_3,  gpioMode_output);
  gpioPinMode(COM_4,  gpioMode_output);
  gpioPinMode(COM_5,  gpioMode_output);
  gpioPinMode(COM_6,  gpioMode_output);
  gpioPinMode(COM_7,  gpioMode_output);
  
  gpioPinMode(PIN_0,  gpioMode_output);
  gpioPinMode(PIN_1,  gpioMode_output);
  gpioPinMode(PIN_2,  gpioMode_output);
  gpioPinMode(PIN_3,  gpioMode_output);
  gpioPinMode(PIN_4,  gpioMode_output);
  gpioPinMode(PIN_5,  gpioMode_output);
  gpioPinMode(PIN_6,  gpioMode_output);
  gpioPinMode(PIN_7,  gpioMode_output);
  gpioPinMode(PIN_8,  gpioMode_output);
  gpioPinMode(PIN_9,  gpioMode_output);
  gpioPinMode(PIN_10, gpioMode_output);
  gpioPinMode(PIN_11, gpioMode_output);
  gpioPinMode(PIN_12, gpioMode_output);
  gpioPinMode(PIN_13, gpioMode_output);
}

void set_pin(PINS p) {
  switch(p) {  
    case pCOM_0:
      gpioSetPin(COM_0);
      break;
    case pCOM_1:
      gpioSetPin(COM_1);
      break;
    case pCOM_2:
      gpioSetPin(COM_2);
      break;
    case pCOM_3:
      gpioSetPin(COM_3);
      break;
    case pCOM_4:
      gpioSetPin(COM_4);
      break;
    case pCOM_5:
      gpioSetPin(COM_5);
      break;
    case pCOM_6:
      gpioSetPin(COM_6);
      break;
    case pCOM_7:
      gpioSetPin(COM_7);
      break;
      
    case pPIN_0:
      gpioSetPin(PIN_0);
      break;
    case pPIN_1:
      gpioSetPin(PIN_1);
      break;
    case pPIN_2:
      gpioSetPin(PIN_2);
      break;
    case pPIN_3:
      gpioSetPin(PIN_3);
      break;
    case pPIN_4:
      gpioSetPin(PIN_4);
      break;
    case pPIN_5:
      gpioSetPin(PIN_5);
      break;
    case pPIN_6:
      gpioSetPin(PIN_6);
      break;
    case pPIN_7:
      gpioSetPin(PIN_7);
      break;
    case pPIN_8:
      gpioSetPin(PIN_8);
      break;
    case pPIN_9:
      gpioSetPin(PIN_9);
      break;
    case pPIN_10:
      gpioSetPin(PIN_10);
      break;
    case pPIN_11:
      gpioSetPin(PIN_11);
      break;
    case pPIN_12:
      gpioSetPin(PIN_12);
      break;
    case pPIN_13:
      gpioSetPin(PIN_13);
      break;
  }  
}

void reset_pin(PINS p) {
  switch(p) {  
    case pCOM_0:
      gpioResetPin(COM_0);
      break;
    case pCOM_1:
      gpioResetPin(COM_1);
      break;
    case pCOM_2:
      gpioResetPin(COM_2);
      break;
    case pCOM_3:
      gpioResetPin(COM_3);
      break;
    case pCOM_4:
      gpioResetPin(COM_4);
      break;
    case pCOM_5:
      gpioResetPin(COM_5);
      break;
    case pCOM_6:
      gpioResetPin(COM_6);
      break;
    case pCOM_7:
      gpioResetPin(COM_7);
      break;
      
    case pPIN_0:
      gpioResetPin(PIN_0);
      break;
    case pPIN_1:
      gpioResetPin(PIN_1);
      break;
    case pPIN_2:
      gpioResetPin(PIN_2);
      break;
    case pPIN_3:
      gpioResetPin(PIN_3);
      break;
    case pPIN_4:
      gpioResetPin(PIN_4);
      break;
    case pPIN_5:
      gpioResetPin(PIN_5);
      break;
    case pPIN_6:
      gpioResetPin(PIN_6);
      break;
    case pPIN_7:
      gpioResetPin(PIN_7);
      break;
    case pPIN_8:
      gpioResetPin(PIN_8);
      break;
    case pPIN_9:
      gpioResetPin(PIN_9);
      break;
    case pPIN_10:
      gpioResetPin(PIN_10);
      break;
    case pPIN_11:
      gpioResetPin(PIN_11);
      break;
    case pPIN_12:
      gpioResetPin(PIN_12);
      break;
    case pPIN_13:
      gpioResetPin(PIN_13);
      break;
  }  
}

void toggle_pin(PINS p) {
  switch(p) {  
    case pCOM_0:
      gpioTogglePin(COM_0);
      break;
    case pCOM_1:
      gpioTogglePin(COM_1);
      break;
    case pCOM_2:
      gpioTogglePin(COM_2);
      break;
    case pCOM_3:
      gpioTogglePin(COM_3);
      break;
    case pCOM_4:
      gpioTogglePin(COM_4);
      break;
    case pCOM_5:
      gpioTogglePin(COM_5);
      break;
    case pCOM_6:
      gpioTogglePin(COM_6);
      break;
    case pCOM_7:
      gpioTogglePin(COM_7);
      break;
      
    case pPIN_0:
      gpioTogglePin(PIN_0);
      break;
    case pPIN_1:
      gpioTogglePin(PIN_1);
      break;
    case pPIN_2:
      gpioTogglePin(PIN_2);
      break;
    case pPIN_3:
      gpioTogglePin(PIN_3);
      break;
    case pPIN_4:
      gpioTogglePin(PIN_4);
      break;
    case pPIN_5:
      gpioTogglePin(PIN_5);
      break;
    case pPIN_6:
      gpioTogglePin(PIN_6);
      break;
    case pPIN_7:
      gpioTogglePin(PIN_7);
      break;
    case pPIN_8:
      gpioTogglePin(PIN_8);
      break;
    case pPIN_9:
      gpioTogglePin(PIN_9);
      break;
    case pPIN_10:
      gpioTogglePin(PIN_10);
      break;
    case pPIN_11:
      gpioTogglePin(PIN_11);
      break;
    case pPIN_12:
      gpioTogglePin(PIN_12);
      break;
    case pPIN_13:
      gpioTogglePin(PIN_13);
      break;
  }  
}