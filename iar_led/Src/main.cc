/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "main.h"
#include "stm32l0xx_hal.h"

#include "delay.h"
#include "lcd_sym_handler.h"

void SystemClock_Config();
void init_buttons();

struct is_btn {
  static bool _1_pushed() {
    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_RESET) return true;
    else return false;
  }
  
  static bool _2_pushed() {
    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_RESET) return true;
    else return false;
  }
  
  static bool _3_pushed() {
    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_RESET) return true;
    else return false;
  }
};

int main() {
  SystemClock_Config();
  
  LCDSymHandler lcd;
  lcd.init();
  init_buttons();
  
  /* Sample
  float val_1 = -0.09;
  uint16_t val_2 = 0;
  bool direction = true;
  uint16_t temp = 0;
  */
  
  while(1) {
    /* Sample
    //lcd.set(DIGITS_CENTER, val_1);
    //lcd.set(DIGITS_TOP_LEFT, val_1);
    //lcd.set(DIGITS_19, val_2);
    //lcd.set(DIGITS_8_8, val_2, true, val_2);
    //lcd.set(SELSIUS, true);
    //lcd.set(&SCALE, val_2);
    
    if(is_btn::_1_pushed()) val_1 += 1;
    if(is_btn::_2_pushed()) val_1 -= 1;
    
    if(direction) val_1 += 0.01;
    else val_1 -= 0.01;
    
    if(val_1 > 1.1) direction = false;
    if(val_1 < -1.1) direction = true;
    
    if(temp != val_1 + val_2) {
      temp = val_1 + val_2;
      delay(100);
    }
    */
    
    lcd.update();
  }
}

void init_buttons() {
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

/** System Clock Configuration */
void SystemClock_Config() {

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler((char *)__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler((char *)__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler((char *)__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

extern "C" void assert_failed(char* file, unsigned long line) {
  while(1);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
