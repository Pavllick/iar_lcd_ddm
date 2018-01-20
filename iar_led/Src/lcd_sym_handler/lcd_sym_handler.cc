#include "lcd_sym_handler.h"
#include <cmath> // round(value*10)/10

LCD_HandleTypeDef LCDSymHandler::hlcd;

// NumberCenterSymbol set
void LCDSymHandler::set(NumberCenterSymbol sym, float number) {
  if(!(number > -999 || number < 9999 || number == OFF)) return;  // [-999; 9999] limit of lcd digits quantity
  
  bool is_off = number == OFF;
  uint16_t seg_offset = 6;;  // SEG offset 2 for each digit [2 | 2 | 2 | 2]
  uint16_t com_offset = 4;;
  uint16_t digit;
  
  // Clearing all digits
  uint16_t clear = 9999;
  digit = 0;
  uint16_t seg_clear = seg_offset;
  uint16_t com_clear = com_offset;
  while(clear > 0) {
    digit = clear % 10;
    clear /= 10;
    
    uint16_t segs_amount = sizeof(syms[digit])/sizeof(syms[digit][0]);
    
    // Clear MASK
    for(int i = 0; i < segs_amount; i++) {
      MASK[syms[digit][i][COM] + com_clear] &= ~(syms[8][i][SEG] << seg_clear);
      MASK[syms[DIGITS_DOT][0][COM] + com_offset] &= ~(syms[DIGITS_DOT][0][SEG] << seg_offset - (2 * i));
    }
    
    seg_clear -= 2;
  }
  
  set_floating_num(4, number, is_off);
}

// NumberTopLeftSymbol set
void LCDSymHandler::set(NumberTopLeftSymbol sym, float number) {
  if(!(number > -99 || number < 999 || number == OFF)) return;  // [-99; 999] limit of lcd digits quantity
  
  bool is_off = number == OFF;
  uint16_t seg_offset = 4;  // SEG offset 2 for each digit [2 | 2 | 2 | 2]
  uint16_t com_offset = 0;
  uint16_t digit;
  
  // Clearing all digits
  uint16_t clear = 999;
  digit = 0;
  uint16_t seg_clear = seg_offset;
  uint16_t com_clear = com_offset;
  while(clear > 0) {
    digit = clear % 10;
    clear /= 10;
    
    uint16_t segs_amount = sizeof(syms[digit])/sizeof(syms[digit][0]);
    
    // Clear MASK
    for(int i = 0; i < segs_amount; i++) {
      MASK[syms[digit][i][COM] + com_clear] &= ~(syms[8][i][SEG] << seg_clear);
      MASK[syms[DIGITS_DOT][0][COM] + com_offset] &= ~(syms[DIGITS_DOT][0][SEG] << seg_offset - (2 * i));
    }
    
    seg_clear -= 2;
  }
  
  set_floating_num(3, number, is_off);
}

void LCDSymHandler::set_floating_num(int8_t digits_segments, float number, bool is_off) {
  uint16_t seg_offset = 0;  // SEG offset 2 for each digit [2 | 2 | 2 | 2]
  uint16_t com_offset = 0;
  uint8_t lcd_max_digits = digits_segments;
  
  float up_01 = 0;
  float down_01 = 0;
  
  if(digits_segments == 3) {
    up_01 = 0.01;
    down_01 = -0.01;
    seg_offset = 4;
    com_offset = 0;
  } else if(digits_segments == 4) {
    up_01 = 0.001;
    down_01 = -0.001;
    seg_offset = 6;
    com_offset = 4;
  }
  
  if(number < up_01 && number > down_01)
    number = 0;
  
  bool is_negative = false;
  if(number <= down_01) {
    is_negative = true;
    number = abs(number);
  }
  
  if(is_negative) lcd_max_digits -= 1;
  
  // int16_t number_left  = 0;
  int16_t number_right = 0;
  uint8_t digits_amount = 0;
  uint8_t digits_amount_left  = 0;
  uint8_t digits_amount_right = 0;
  uint8_t non_zero_digits_amount_right = 0;
  uint8_t zero_digits_amount_right = 0;
  int16_t dot_addr = 0;
  int16_t precis = 0;
  
  if(number >= up_01) {
    precis = precision(number, lcd_max_digits);
    int int_num = int_number(number, lcd_max_digits, &precis);  // update precis var !!
    
    digits_amount_right = int(floor(log10(abs((float)precis))));
    
    // number_left  = int(floor((float)int_num / precis));
    number_right = (int16_t)(int_num % precis);

    //int_num = int(floor(number * precis));
    digits_amount = int(floor(log10(abs((float)int_num)) + 1));
    
    non_zero_digits_amount_right = int(floor(log10(abs((float)number_right)) + 1));
    
    if(digits_amount >= digits_amount_right)
      digits_amount_left = digits_amount - digits_amount_right;

    number = floor((float)number * precis);
    //if(digits_amount > lcd_max_digits && digits_amount_left < lcd_max_digits) number /= pow(10.0, (digits_amount - lcd_max_digits));
    
    if(digits_amount_left < lcd_max_digits && digits_amount_left > 0 && digits_amount_right > 0) {
      dot_addr = lcd_max_digits - digits_amount_left;
      if(!(dot_addr < digits_amount_right)) dot_addr = digits_amount_right;
      if(dot_addr <= 0) dot_addr = lcd_max_digits - digits_amount_left;
      
    } else if(digits_amount_left == 0 && digits_amount_right > 0) {
      dot_addr = digits_amount_right;
      if(dot_addr >= lcd_max_digits) dot_addr = lcd_max_digits - 1;
      
      zero_digits_amount_right = digits_amount_right - non_zero_digits_amount_right;
    }
  }
  
  // Seting new digits
  uint16_t digit = 0;
  int int_number = int(floor(number));
  uint16_t seg_offset_tmp = seg_offset;
  while(int_number >= 0 && int_number != OFF) {
    digit = int_number % 10;
    int_number /= 10;
    
    uint16_t segs_amount = sizeof(syms[digit])/sizeof(syms[digit][0]);
    
    // Refresh MASK
    for(int i = 0; i < segs_amount; i++) {
      if(!is_off)
        MASK[syms[digit][i][COM] + com_offset] |= syms[digit][i][SEG] << seg_offset_tmp;
    }
    
    seg_offset_tmp -= 2;
    if(int_number == 0) int_number = -1;
  }
  
  if(dot_addr > 0 && !is_off) {
    // Draw dot sign
    //seg_offset = 4;
    MASK[syms[DIGITS_DOT][0][COM] + com_offset] |= syms[DIGITS_DOT][0][SEG] << seg_offset - (2 * dot_addr);
    
    // Draw zero sign
    if(digits_amount_left == 0) {
      for(int i = 0; i < 4; i++)
        MASK[syms[0][i][COM] + com_offset] |= syms[0][i][SEG] << seg_offset - (2 * dot_addr);
      
      // Draw zero signs to the right of dot
      while(zero_digits_amount_right) {
        for(int i = 0; i < 4; i++) {
        if(!is_off)
          MASK[syms[0][i][COM] + com_offset] |= syms[0][i][SEG] << seg_offset - (2 * (dot_addr - zero_digits_amount_right));
        }
        
        zero_digits_amount_right -= 1;
      }
    }
  }
  
  if(is_negative && !is_off) {
    //seg_offset = 4;
    int8_t minus_shift;
    if(digits_amount_left == 0) minus_shift =  digits_amount_right + 1;
    else minus_shift = digits_amount;
    MASK[syms[DIGITS_MINUS][0][COM] + com_offset] |= syms[DIGITS_MINUS][0][SEG] << seg_offset - (2 * minus_shift);
  }
}

uint16_t LCDSymHandler::precision(float number, uint8_t lcd_max_digits) {
  uint16_t prec = int(pow(10.0, (lcd_max_digits - 1)));
  int int_num = int(floor(number * prec));
  while(int_num % 10 == 0 && prec > 1) {
    prec /= 10;
    int_num /= 10;
  }
  
  return prec;
}

int LCDSymHandler::int_number(float number, int8_t lcd_max_digits, int16_t *precis) {
  int int_num = int(floor(number * *precis));
  int8_t digits_amount = int(floor(log10(abs((float)int_num)) + 1));
  while(digits_amount > lcd_max_digits) {
    if(*precis > 1) *precis /= 10;
    int_num /= 10;
    digits_amount -= 1;
  }
  
  return int_num;
}

// Number19Symbol set
void LCDSymHandler::set(Number19Symbol sym, int16_t number) {
  if(!((number <= 19 && number >= 0) || number == OFF)) return;    // [0; 19] limits of lcd digits quantity
  
  bool is_off = number == OFF;
  uint16_t seg_offset = 12;
  uint16_t com_offset = 0;
  uint16_t digit_offset = 41;
  
  MASK[syms[DIGITS_19_ONE][0][COM]] &= ~(syms[DIGITS_19_ONE][0][SEG] << seg_offset);
  
  if(number > 9 && number != OFF) {
    MASK[syms[DIGITS_19_ONE][0][COM]] |= syms[DIGITS_19_ONE][0][SEG] << seg_offset;
    number = number % 10;
  } else if(number == OFF) {
    number = 0;
  }
  
  uint16_t segs_amount = sizeof(syms[number + digit_offset])/sizeof(syms[number + digit_offset][0]);
  // Refresh MASK
  for(int i = 0; i < segs_amount; i++) {
    MASK[syms[number + digit_offset][i][COM] + com_offset] &= ~(syms[8 + digit_offset][i][SEG] << seg_offset);
    if(!is_off)
      MASK[syms[number + digit_offset][i][COM] + com_offset] |= syms[number + digit_offset][i][SEG] << seg_offset;
  }
}

// Number8_8Symbol set
void LCDSymHandler::set(Number8_8Symbol sym, int16_t number_1, bool is_dash, int16_t number_2) {
  if(!((
        number_1 <= 9 && number_2 <= 9 && 
        number_1 >= 0 && number_2 >= 0) || 
        number_1 == OFF)) return;    // [0; 9] limits of lcd digits quantity
  
  MASK[syms[DIGITS_8_8_DASH][0][COM]] &= ~(syms[DIGITS_8_8_DASH][0][SEG]);
  if(is_dash)
    MASK[syms[DIGITS_8_8_DASH][0][COM]] |= syms[DIGITS_8_8_DASH][0][SEG];
  
  bool is_off;
  uint16_t number = number_1;
  uint16_t seg_offset;
  uint16_t com_offset = 0;
  uint16_t digit_offset = 41;
  
  if(number == OFF)
    number = 0;
  
  uint16_t segs_amount = sizeof(syms[number + digit_offset])/sizeof(syms[number + digit_offset][0]);
  
  // Set first digit
  number = number_1;
  seg_offset = 10;
  is_off = number == OFF;
  if(number == OFF)
    number = 0;
  // Refresh MASK
  for(int i = 0; i < segs_amount; i++) {
    MASK[syms[number + digit_offset][i][COM] + com_offset] &= ~(syms[8 + digit_offset][i][SEG] << seg_offset);
    if(!is_off)
      MASK[syms[number + digit_offset][i][COM] + com_offset] |= syms[number + digit_offset][i][SEG] << seg_offset;
  }
  
  // Set second digit
  number = number_2;
  seg_offset = 8;
  is_off = number == OFF;
  if(number == OFF)
    number = 0;
  // Refresh MASK
  for(int i = 0; i < segs_amount; i++) {
    MASK[syms[number + digit_offset][i][COM] + com_offset] &= ~(syms[8 + digit_offset][i][SEG] << seg_offset);
    if(!is_off)
      MASK[syms[number + digit_offset][i][COM] + com_offset] |= syms[number + digit_offset][i][SEG] << seg_offset;
  }
}

// SingleSymbol set
void LCDSymHandler::set(SingleSymbol sym, bool is_set) {
  MASK[syms[sym.v()][0][COM]] &= ~syms[sym.v()][0][SEG];
  if(is_set) MASK[syms[sym.v()][0][COM]] |= syms[sym.v()][0][SEG];
}

// ButterySymbol set
void LCDSymHandler::set(ButterySymbol (*sym)[BATTERY_LEN + 1], uint16_t level) {
  if(level > BATTERY_LEN && level != OFF) return;
  for(int i = 0; i < BATTERY_LEN + 1; i++)
    MASK[syms[(*sym)[i].v()][0][COM]] &= ~syms[(*sym)[i].v()][0][SEG];
    
  bool is_off = (level == OFF);
  if(is_off) level = BATTERY_LEN;
  
  for(int i = 0; i <= level; i++) {
    if(!is_off) MASK[syms[(*sym)[i].v()][0][COM]] |= syms[(*sym)[i].v()][0][SEG];
  }
}

// AntennaSymbol set
void LCDSymHandler::set(AntennaSymbol (*sym)[ANTENNA_LEN + 1], uint16_t level) {
  if(level > ANTENNA_LEN && level != OFF) return;
  for(int i = 0; i < ANTENNA_LEN + 1; i++)
    MASK[syms[(*sym)[i].v()][0][COM]] &= ~syms[(*sym)[i].v()][0][SEG];
    
  bool is_off = (level == OFF);
  if(is_off) level = ANTENNA_LEN;
  
  for(int i = 0; i <= level; i++) {
    if(!is_off) MASK[syms[(*sym)[i].v()][0][COM]] |= syms[(*sym)[i].v()][0][SEG];
  }
}

// ScaleSymbol set
void LCDSymHandler::set(ScaleSymbol (*sym)[SCALE_LEN + 1], uint16_t level) {
  if(level > SCALE_LEN && level != OFF) return;
  for(int i = 0; i < SCALE_LEN + 1; i++)
    MASK[syms[(*sym)[i].v()][0][COM]] &= ~syms[(*sym)[i].v()][0][SEG];
    
  bool is_off = (level == OFF);
  if(is_off) level = SCALE_LEN;
  
  for(int i = 0; i <= level; i++) {
    if(!is_off) MASK[syms[(*sym)[i].v()][0][COM]] |= syms[(*sym)[i].v()][0][SEG];
  }
}

void LCDSymHandler::init() {
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LCD_Init();
  
  HAL_LCD_Clear(&hlcd);
}

void LCDSymHandler::update() {
  bool is_mask_updated = false;
  for(int i = 0; i < 8; i++)
    if(MASK[i] != MASK_PREV[i]) is_mask_updated = true;
  
  if(is_mask_updated) {
    HAL_LCD_Clear(&hlcd);
    
    for(int i = 0; i < 8; i++) {
      HAL_LCD_Write(&hlcd,
                    2 * i,                                          // COM
                    MASK[i],              // MASK
                    MASK[i]);              // SEG
    
      MASK_PREV[i] = MASK[i];
    }
    
    HAL_LCD_UpdateDisplayRequest(&hlcd);
  }
}

const uint16_t LCDSymHandler::syms[SYMS_AMOUNT][4][2] = {
  // NumberCenter Symbols
  /* 0  */  {{0, 3}, {1, 2}, {2, 3}, {3, 2}}, // 0
  /* 1  */  {{0, 0}, {1, 2}, {2, 2}, {3, 0}}, // 1
  /* 2  */  {{0, 2}, {1, 3}, {2, 1}, {3, 2}}, // 2
  /* 3  */  {{0, 2}, {1, 3}, {2, 2}, {3, 2}}, // 3
  /* 4  */  {{0, 1}, {1, 3}, {2, 2}, {3, 0}}, // 4
  /* 5  */  {{0, 3}, {1, 1}, {2, 2}, {3, 2}}, // 5
  /* 6  */  {{0, 3}, {1, 1}, {2, 3}, {3, 2}}, // 6
  /* 7  */  {{0, 2}, {1, 2}, {2, 2}, {3, 0}}, // 7
  /* 8  */  {{0, 3}, {1, 3}, {2, 3}, {3, 2}}, // 8
  /* 9  */  {{0, 3}, {1, 3}, {2, 2}, {3, 2}}, // 9
    
    // Single element symbols
  /* 10 */  {{5, 0x2000}},                    // C
  /* 11 */  {{6, 0x2000}},                    // KPA
  /* 12 */  {{7, 0x2000}},                    // MPA
    
    // BATTERY
  /* 13 */  {{3, 0x40}},                      // BATTERY
  /* 14 */  {{2, 0x40}},                      // BATTERY level 1
  /* 15 */  {{1, 0x40}},                      // BATTERY level 2
  /* 16 */  {{0, 0x40}},                      // BATTERY level 3
  
    // ANTENNA
  /* 17 */  {{0, 0x80}},                      // ANTENNA
  /* 18 */  {{1, 0x80}},                      // ANTENNA level 1
  /* 19 */  {{2, 0x80}},                      // ANTENNA level 2
  /* 20 */  {{3, 0x80}},                      // ANTENNA level 3
  /* 21 */  {{4, 0x2000}},                    // ANTENNA level 4
  
    // SCALE
  /* 22 */  {{7, 0x100}},                     // SCALE
  /* 23 */  {{7, 0x1000}},                    // SCALE level 1
  /* 24 */  {{6, 0x1000}},                    // SCALE level 2
  /* 25 */  {{5, 0x1000}},                    // SCALE level 3
  /* 26 */  {{4, 0x1000}},                    // SCALE level 4
  /* 27 */  {{4, 0x800}},                     // SCALE level 5
  /* 28 */  {{5, 0x800}},                     // SCALE level 6
  /* 29 */  {{6, 0x800}},                     // SCALE level 7
  /* 30 */  {{7, 0x800}},                     // SCALE level 8
  /* 31 */  {{7, 0x400}},                     // SCALE level 9
  /* 32 */  {{6, 0x400}},                     // SCALE level 10
  /* 33 */  {{5, 0x400}},                     // SCALE level 11
  /* 34 */  {{4, 0x400}},                     // SCALE level 12
  /* 35 */  {{4, 0x200}},                     // SCALE level 13
  /* 36 */  {{5, 0x200}},                     // SCALE level 14
  /* 37 */  {{6, 0x200}},                     // SCALE level 15
  /* 38 */  {{7, 0x200}},                     // SCALE level 16
  /* 39 */  {{6, 0x100}},                     // SCALE level 17
  /* 40 */  {{5, 0x100}},                     // SCALE level 18
  
  // NumberTopLeft Symbols
  /* 41 */  {{0, 3}, {1, 1}, {2, 3}, {3, 1}}, // 0
  /* 42 */  {{0, 0}, {1, 1}, {2, 1}, {3, 0}}, // 1
  /* 43 */  {{0, 1}, {1, 3}, {2, 2}, {3, 1}}, // 2
  /* 44 */  {{0, 1}, {1, 3}, {2, 1}, {3, 1}}, // 3
  /* 45 */  {{0, 2}, {1, 3}, {2, 1}, {3, 0}}, // 4
  /* 46 */  {{0, 3}, {1, 2}, {2, 1}, {3, 1}}, // 5
  /* 47 */  {{0, 3}, {1, 2}, {2, 3}, {3, 1}}, // 6
  /* 48 */  {{0, 1}, {1, 1}, {2, 1}, {3, 0}}, // 7
  /* 49 */  {{0, 3}, {1, 3}, {2, 3}, {3, 1}}, // 8
  /* 50 */  {{0, 3}, {1, 3}, {2, 1}, {3, 1}}, // 9
  
  /* 51 */  {{3, 2}},                         // 1 for 18 segmet
  /* 52 */  {{3, 0x200}},                     // - for 8-8 segmet
  
  // Dots for numbers
  /* 53 */  {{3, 0x4}},                       // dot for NumberTopLeft 8.88
  
  // Minus for numbers
  /* 53 */  {{1, 0x1}},                       // minus for NumberTopLeft -88
};

/* LCD init function */
void LCDSymHandler::MX_LCD_Init() {
  hlcd.Instance = LCD;
  hlcd.Init.Prescaler = LCD_PRESCALER_1;
  hlcd.Init.Divider = LCD_DIVIDER_16;
  hlcd.Init.Duty = LCD_DUTY_1_8;
  hlcd.Init.Bias = LCD_BIAS_1_4;
  hlcd.Init.VoltageSource = LCD_VOLTAGESOURCE_INTERNAL;
  hlcd.Init.Contrast = LCD_CONTRASTLEVEL_7;
  hlcd.Init.DeadTime = LCD_DEADTIME_0;
  hlcd.Init.PulseOnDuration = LCD_PULSEONDURATION_1;
  hlcd.Init.HighDrive = LCD_HIGHDRIVE_1;
  hlcd.Init.BlinkMode = LCD_BLINKMODE_OFF;
  hlcd.Init.BlinkFrequency = LCD_BLINKFREQUENCY_DIV8;
  hlcd.Init.MuxSegment = LCD_MUXSEGMENT_DISABLE;
  if (HAL_LCD_Init(&hlcd) != HAL_OK)
  {
    _Error_Handler((char *)__FILE__, __LINE__);
  }

}

/** Pinout Configuration */
void LCDSymHandler::MX_GPIO_Init() {
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char* file, int line) {
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif
