#include "lcd_sym_handler.h"

LCD_HandleTypeDef LCDSymHandler::hlcd;

void LCDSymHandler::set(uint16_t sym, uint16_t number) {
  if(sym != DIGITS_1 || sym != DIGITS_2) return;
  if(number > 9999) return;
  
  uint16_t offset = 6;   // COM offset 2 for each digit [2 | 2 | 2 | 2]
  uint16_t digit;
  while(number > 0) {
    digit = number % 10;
    number /= 10;
    
    uint16_t segs_amount = sizeof(syms[digit])/sizeof(syms[digit][0]);
    
    // Refresh MASK
    for(int i = 0; i < segs_amount; i++) {
      MASK[syms[8][i][COM]]     &= ~(syms[8][i][SEG] << offset);
      MASK[syms[digit][i][COM]] |= syms[digit][i][SEG] << offset;
    }
    
    // Set Symbol or Digit
    for(int i = 0; i < segs_amount; i++) {
      HAL_LCD_Write(&hlcd,
                    2 * syms[digit][i][COM],              // COM
                    MASK[syms[8][i][COM]],                // MASK
                    syms[digit][i][SEG] << offset);       // SEG
    }
    
    offset -= 2;
  }
}

void LCDSymHandler::set(uint16_t sym, SetResetSym is_set) {
  if(sym == DIGITS_1 || sym == DIGITS_2) return;
  //if()
  
  // Refresh MASK
  MASK[syms[sym][0][COM]] &= ~syms[sym][0][SEG];
  if(is_set) MASK[syms[sym][0][COM]] |= syms[sym][0][SEG];
  
  // Set Symbol
    HAL_LCD_Write(&hlcd,
                  2 * syms[sym][0][COM],                // COM
                  MASK[syms[sym][0][COM]],              // MASK
                  syms[sym][0][SEG]);                   // SEG
}

void LCDSymHandler::test_set() {
  HAL_LCD_Write(&hlcd, 4*2, 0xFFFF, 1 << 1);
  
  //HAL_LCD_Write(&hlcd, 5*2, 1 << 1, MASK);
  //HAL_LCD_Write(&hlcd, 6*2, MASK, 1 << 1);
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
  
  HAL_LCD_Clear(&hlcd);
}

void LCDSymHandler::update() {
  HAL_LCD_UpdateDisplayRequest(&hlcd);
}

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
