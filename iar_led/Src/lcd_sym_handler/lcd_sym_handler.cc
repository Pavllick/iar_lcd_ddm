#include "lcd_sym_handler.h"

LCD_HandleTypeDef LCDSymHandler::hlcd;

// NumberSymbol set
void LCDSymHandler::set(NumberSymbol sym, int16_t number) {
  if(sym == DIGITS_1 && !(number <= 999 || number == OFF)) return;   // 999 limit of lcd digits quantity
  if(sym == DIGITS_2 && !(number <= 9999 || number == OFF)) return;  // 9999 limit of lcd digits quantity
  if(sym == DIGITS_3 && !((number <= 19 && number >= 0) || number == OFF)) return;    // [0; 19] limits of lcd digits quantity
  
  bool is_off = number == OFF;
  uint16_t digit_offset = 0;
  uint16_t seg_offset;  // SEG offset 2 for each digit [2 | 2 | 2 | 2]
  uint16_t com_offset;
  
  if(sym == DIGITS_1 || sym == DIGITS_2) {
    if(sym == DIGITS_1) {
      seg_offset = 4;
      com_offset = 0;
    } else if(sym == DIGITS_2) {
      seg_offset = 6;
      com_offset = 4;
    }
    
    // Clearing all digits
    uint16_t clear = 0;
    uint16_t clear_digit = 0;
    uint16_t seg_clear = seg_offset;
    uint16_t com_clear = com_offset;
    if(sym == DIGITS_1) clear = 999;
    else if(sym == DIGITS_2) clear = 9999;
    else if(sym == DIGITS_3) clear = 9;
    while(clear > 0) {
      clear_digit = clear % 10;
      clear /= 10;
      
      uint16_t segs_amount = sizeof(syms[clear_digit + digit_offset])/sizeof(syms[clear_digit + digit_offset][0]);
      
      // Clear MASK
      for(int i = 0; i < segs_amount; i++)
        MASK[syms[clear_digit + digit_offset][i][COM] + com_clear] &= ~(syms[8 + digit_offset][i][SEG] << seg_clear);
      
      seg_clear -= 2;
    }
    
    if(number == OFF) {
      number = 0;
    }
    
    // Seting new digits
    uint16_t digit;
    while(number >= 0) {
      digit = number % 10;
      number /= 10;
      
      uint16_t segs_amount = sizeof(syms[digit + digit_offset])/sizeof(syms[digit + digit_offset][0]);
      
      // Refresh MASK
      for(int i = 0; i < segs_amount; i++) {
        //MASK[syms[digit + digit_offset][i][COM] + com_offset] &= ~(syms[8 + digit_offset][i][SEG] << seg_offset);
        if(!is_off)
          MASK[syms[digit + digit_offset][i][COM] + com_offset] |= syms[digit + digit_offset][i][SEG] << seg_offset;
      }
      
      seg_offset -= 2;
      if(number == 0) number = -1;
    }
  }
  else {
    seg_offset = 12;
    com_offset = 0;
    digit_offset = 41;
    
    
    if(sym == DIGITS_3)
      MASK[syms[DIGITS_3_ONE][0][COM]] &= ~(syms[DIGITS_3_ONE][0][SEG] << seg_offset);
    
    if(sym == DIGITS_3 && number > 9 && number != OFF) {
      MASK[syms[DIGITS_3_ONE][0][COM]] |= syms[DIGITS_3_ONE][0][SEG] << seg_offset;
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
}

// SingleSymbol set
void LCDSymHandler::set(SingleSymbol sym, SetResetSym is_set) {
  MASK[syms[sym.v()][0][COM]] &= ~syms[sym.v()][0][SEG];
  if(is_set.v()) MASK[syms[sym.v()][0][COM]] |= syms[sym.v()][0][SEG];
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

void LCDSymHandler::set_seg(uint32_t com, uint32_t seg) {
  
  HAL_LCD_Write(&hlcd, com*2, 1 << seg, 1 << seg);
  //HAL_LCD_UpdateDisplayRequest(&hlcd);
}

void LCDSymHandler::init() {
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_LCD_Init();
  
  //for(int i = 0; i < 8; i++) MASK[i] = 0;
  //for(int i = 0; i < 8; i++) MASK_PREV[i] = 0;
  
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
  
  /* 51 */  {{3, 2}}                          // 1 for 18 segmet
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
