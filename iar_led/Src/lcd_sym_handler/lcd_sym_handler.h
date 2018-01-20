#ifndef LCD_SYM_HENDLER_H_
#define LCD_SYM_HENDLER_H_

#include "stm32l0xx_hal.h"
#include "delay.h"

/******************************************************************************
  * This file privides LCD API. Initialization functions and symbols/numbers
  * handlers for STM32L053, 8 COMs and 14 SEGs.
  *
  *****************************************************************************
  *                 ##### How to use this library #####
  *****************************************************************************
  * @brief    Initialization functions
  * @description
  ==============================================================================
                    ##### Initialization function #####
  ==============================================================================
  * For init LCD it needs to define LCDSymHandler class variable
  * And to call function init(), that will set up all LCD pins configuration
  * automatically by using HAL driver, (#include "stm32l0xx_hal.h"), necessary
  * add to header
  * @example    LCDSymHandler lcd;      // Define class varible
  *             lcd.init();             // Initiate and configure LCD
  * 
  ******************************************************************************
  * @function     void update();
  * @brief        Updates LCD data
  * @description  Should calls after change symbol's value,
  *               may uses in main while cycle. Update LCD only if at least
  *               one symbol was chnged otherwise do nothing.
  * 
  ******************************************************************************
  * @brief    LCD elements setting functions
  * @description
  *
  ==============================================================================
                        ##### LCD handlers #####
  ==============================================================================
  * @brief      LCDSymHandler privides functions for set/reset LCD
  *             symbols and numbers. There are many overloadings
  *             for (set()) function that can be used for all LCD configurations
  *
  *****************************************************************************
  * @function   void set(sym, bool is_set);
  * @brief      Function for 1 symbol elements handle
  * @param      sym     - const symbol name, can be one of the followings:
  *             SELSIUS, KPA or MPA
  *             is_set  - on/off symbol
  *
  *****************************************************************************
  * @function   void set(ButterySymbol (*sym)[BATTERY_LEN + 1], uint16_t level);
  * @usage      void set(&BATTERY, uint16_t level);
  * @brief      Function for battery elements handle
  * @param      &BATTERY - const symbol name
  *             level    - number from range (0 to 3) or OFF constant
  * 
  *****************************************************************************
  * @function   void set(AntennaSymbol (*sym)[ANTENNA_LEN + 1], uint16_t level);
  * @usage      void set(&ANTENNA, uint16_t level);
  * @brief      Function for antenna elements handle
  * @param      &ANTENNA - const symbol name
  *             level    - number from range (0 to 4) or OFF constant
  * 
  *****************************************************************************
  * @function   void void set(ScaleSymbol (*sym)[SCALE_LEN   + 1], uint16_t level);
  * @usage      void set(&SCALE, uint16_t level);
  * @brief      Function for bottom scale elements handle
  * @param      &SCALE  - const symbol name
  *             level   - number from range (0 to 18) or OFF constant
  * 
  *****************************************************************************
  * @function   void set(NumberCenterSymbol sym, float number);
  * @usage      void set(DIGITS_CENTER, float number);
  * @brief      Function for center, 4 digits, number handle
  * @param      DIGITS_CENTER - const symbol name
  *             number        - floating number from range
  *                             (-999.0 to 9999.0) or OFF constant
  * 
  *****************************************************************************
  * @function   void set(NumberTopLeftSymbol sym, float number);
  * @usage      void set(DIGITS_TOP_LEFT, float number);
  * @brief      Function for top left, 3 digits, number handle
  * @param      DIGITS_TOP_LEFT - const symbol name
  *             number          - floating number from range
  *                               (-99.0 to 999.0) or OFF constant
  * 
  *****************************************************************************
  * @function   void set(Number19Symbol sym, int16_t number);
  * @usage      void set(DIGITS_19, int16_t number);
  * @brief      Function for top right, 2 digits, number handle
  * @param      DIGITS_19 - const symbol name
  *             number    - number from range (0 to 19) or OFF constant
  * 
  *****************************************************************************
  * @function   void set(Number8_8Symbol sym, int16_t number_1, bool is_dash, int16_t number_2);
  * @usage      void set(DIGITS_8_8, int16_t number);
  * @brief      Function for bottom right, two one digit numbers handle
  * @param      DIGITS_8_8 - const symbol name
  *             number_1   - number from range (0 to 9) or OFF constant
  *             is_dash    - on/off dash symbol between numbers
  *             number_2   - number from range (0 to 9) or OFF constant
  * 
  *****************************************************************************
  *****************************************************************************
  */

struct NumberCenterSymbol{
public:
  NumberCenterSymbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
  
private:
  uint16_t val;
};

struct NumberTopLeftSymbol{
public:
  NumberTopLeftSymbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
  
private:
  uint16_t val;
};

struct Number19Symbol{
public:
  Number19Symbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
  
private:
  uint16_t val;
};

struct Number8_8Symbol{
public:
  Number8_8Symbol(uint16_t v) { val = v ;}
  uint16_t v() { return val; }
  
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
static const uint16_t OFF = 10000;

static const NumberCenterSymbol  DIGITS_CENTER(    0 );
static const NumberTopLeftSymbol DIGITS_TOP_LEFT(  1 );
static const uint8_t             DIGITS_DOT =      53;
static const uint8_t             DIGITS_MINUS =    54;

static const Number19Symbol      DIGITS_19(        2 );
static const uint16_t            DIGITS_19_ONE =   51;

static const Number8_8Symbol     DIGITS_8_8(       3 );
static const uint16_t            DIGITS_8_8_DASH = 52;

static const SingleSymbol        SELSIUS(          10 );
static const SingleSymbol        KPA(              11 );
static const SingleSymbol        MPA(              12 );

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

  void set(NumberCenterSymbol sym, float number);
  void set(NumberTopLeftSymbol sym, float number);
  void set(Number19Symbol sym, int16_t number);
  void set(Number8_8Symbol sym, int16_t number_1, bool is_dash, int16_t number_2);
  
  void set(SingleSymbol sym, bool is_set);
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
  
  uint16_t precision(float number, uint8_t lcd_max_digits);
  int int_number(float number, int8_t lcd_max_digits, int16_t *precis);
  void set_floating_num(int8_t digits_segments, float number, bool is_off);
  
  static uint8_t const SYMS_AMOUNT = 55;
  static const uint16_t syms[SYMS_AMOUNT][4][2];
};

#endif  // LCD_SYM_HENDLER_H_