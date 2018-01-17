#ifndef LCD_SYM_HENDLER_H_
#define LCD_SYM_HENDLER_H_

#include "stm32l0xx_hal.h"
#include "delay.h"

struct SetResetSym{
public:
  SetResetSym(bool v) { val = v ;}
  bool v() { return val; }
  
private:
  bool val;
};

struct NumberSymbol{
public:
  NumberSymbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
  
  friend bool operator==(const NumberSymbol& left, const NumberSymbol& right) {
    return left.val == right.val;
  }
  
  friend bool operator!=(const NumberSymbol& left, const NumberSymbol& right) {
    return !(left.val == right.val);
  }
  
private:
  uint16_t val;
};

struct SingleSymbol{
public:
  SingleSymbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
  
private:
  uint16_t val;
};

struct ButterySymbol{
public:
  ButterySymbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
private:
  uint16_t val;
};

struct AntennaSymbol{
public:
  AntennaSymbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
private:
  uint16_t val;
};

struct ScaleSymbol{
public:
  ScaleSymbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
private:
  uint16_t val;
};

// LCD Handle consts
static const uint16_t      OFF =        10000;

static const SetResetSym   SET_SYM(     true    );
static const SetResetSym   RESET_SYM(   false   );
                          
static const NumberSymbol  DIGITS_1(    0       );
static const NumberSymbol  DIGITS_2(    1       );
static const NumberSymbol  DIGITS_3(    2       );
static const uint16_t      DIGITS_3_ONE = 51;

static const SingleSymbol  SELSIUS(     10      );
static const SingleSymbol  KPA(         11      );
static const SingleSymbol  MPA(         12      );

// values of battery level [0...3] and OFF
static ButterySymbol       BATTERY[4] = { 13, 14, 15, 16 };
static const uint16_t      BATTERY_LEN = 3;

// values of antenna signal level [0...4] and OFF
static AntennaSymbol       ANTENNA[5] = { 17, 18, 19, 20, 21 };
static const uint16_t      ANTENNA_LEN = 4;

// values of scale level [0...18] and OFF
static ScaleSymbol         SCALE[19] = { 22, 23, 24, 25, 26, 27, 28,
                                         29, 30, 31, 32, 33, 34, 35,
                                         36, 37, 38, 39, 40 };
static const uint16_t      SCALE_LEN = 18;
  
class LCDSymHandler {
public:
  static LCD_HandleTypeDef hlcd;

  void init();
  void update();
  void set_seg(uint32_t com, uint32_t seg);
  void test_set();

  void set(NumberSymbol sym, int16_t number);
  void set(SingleSymbol sym, SetResetSym is_set);
  void set(ButterySymbol (*sym)[BATTERY_LEN + 1], uint16_t level);
  void set(AntennaSymbol (*sym)[ANTENNA_LEN + 1], uint16_t level);
  void set(ScaleSymbol   (*sym)[SCALE_LEN   + 1], uint16_t level);
  
private:
  const uint16_t COM = 0;
  const uint16_t SEG = 1;
  uint16_t MASK[8] = {};
  uint16_t MASK_PREV[8] = {};
  
  static void MX_LCD_Init();
  static void MX_GPIO_Init();
  
  static uint8_t const SYMS_AMOUNT = 52;
  static const uint16_t syms[SYMS_AMOUNT][4][2];
};

#endif  // LCD_SYM_HENDLER_H_