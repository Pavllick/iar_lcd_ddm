#ifndef LCD_SYM_HENDLER_H_
#define LCD_SYM_HENDLER_H_

#include "stm32l0xx_hal.h"
#include "delay.h"

typedef bool SetResetSym;
  const SetResetSym SET_SYM   = true;
  const SetResetSym RESET_SYM = false;

class LCDSymHandler {
  public:
    static LCD_HandleTypeDef hlcd;
    
    void init();
    void update();
    void set_seg(uint32_t com, uint32_t seg);
    void test_set();
    
    void set(uint16_t sym, uint16_t number);
    void set(uint16_t sym, SetResetSym is_set);
    
  private:
    const uint16_t COM = 0;
    const uint16_t SEG = 1;
    uint16_t MASK[8];
    
    static void MX_LCD_Init();
    static void MX_GPIO_Init();
    
    uint16_t syms[15][4][2] = {
      {{4, 3}, {5, 2}, {6, 3}, {7, 2}}, // 0
      {{4, 0}, {5, 2}, {6, 2}, {7, 0}}, // 1
      {{4, 2}, {5, 3}, {6, 1}, {7, 2}}, // 2
      {{4, 2}, {5, 3}, {6, 2}, {7, 2}}, // 3
      {{4, 1}, {5, 3}, {6, 2}, {7, 0}}, // 4
      {{4, 3}, {5, 1}, {6, 2}, {7, 2}}, // 5
      {{4, 3}, {5, 1}, {6, 3}, {7, 2}}, // 6
      {{4, 2}, {5, 2}, {6, 2}, {7, 0}}, // 7
      {{4, 3}, {5, 3}, {6, 3}, {7, 2}}, // 8
      {{4, 3}, {5, 3}, {6, 2}, {7, 2}}, // 9
      
      //Single element symbols
      {{0, 0x80}},                      // ANTENNA_SYM
      {{5, 0x2000}},                    // C
      {{6, 0x2000}},                    // KPA
      {{7, 0x2000}},                    // MPA
      {{7, 0x100}}                      // SCALE
    };
};

enum AvailableSymbols {
  DIGITS_1      = 0,
  DIGITS_2      = 1,
  ANTENNA_SYM   = 10,
  SELSIUS       = 11,
  KPA           = 12,
  MPA           = 13,
  SCALE         = 14,
};

#endif  // LCD_SYM_HENDLER_H_