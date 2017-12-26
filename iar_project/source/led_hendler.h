#ifndef LED_HENDLER_H
#define LED_HENDLER_H

#include "lld.h"

enum PINS{
  pCOM_0,
  pCOM_1,
  pCOM_2,
  pCOM_3,
  pCOM_4,
  pCOM_5,
  pCOM_6,
  pCOM_7,
  
  pPIN_0,
  pPIN_1,
  pPIN_2,
  pPIN_3,
  pPIN_4,
  pPIN_5,
  pPIN_6,
  pPIN_7,
  pPIN_8,
  pPIN_9,
  pPIN_10,
  pPIN_11,
  pPIN_12,
  pPIN_13,
};

static PINS pins_com[] = {pCOM_0, pCOM_1, pCOM_2, pCOM_3, pCOM_4, pCOM_5, pCOM_6, pCOM_7};
static PINS pins_pin[] = {pPIN_0, pPIN_1, pPIN_2, pPIN_3, pPIN_4, pPIN_5, pPIN_6, pPIN_7,
                          pPIN_8, pPIN_9, pPIN_10, pPIN_11, pPIN_12, pPIN_13,};

#define COM_0 GPIOA,  8
#define COM_1 GPIOA,  9
#define COM_2 GPIOA,  10
#define COM_3 GPIOB,  9
#define COM_4 GPIOC,  10
#define COM_5 GPIOC,  11
#define COM_6 GPIOC,  12
#define COM_7 GPIOD,  2

#define PIN_0 GPIOA,  1
#define PIN_1 GPIOA,  2
#define PIN_2 GPIOA,  3
#define PIN_3 GPIOA,  6
#define PIN_4 GPIOA,  7
#define PIN_5 GPIOB,  0
#define PIN_6 GPIOB,  1
#define PIN_7 GPIOB,  3
#define PIN_8 GPIOB,  4
#define PIN_9 GPIOB,  5
#define PIN_10 GPIOB, 10
#define PIN_11 GPIOB, 11
#define PIN_12 GPIOB, 12
#define PIN_13 GPIOB, 13

// Prototypes
void init_led_ports();
void led_update();

void set_pin(PINS com);
void reset_pin(PINS com);
void toggle_pin(PINS com);

#endif