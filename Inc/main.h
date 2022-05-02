/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOC
#define Ble_control_Pin GPIO_PIN_0
#define Ble_control_GPIO_Port GPIOA
#define LCD_Mosfet_Pin GPIO_PIN_1
#define LCD_Mosfet_GPIO_Port GPIOA
#define Battery_Status_Pin GPIO_PIN_4
#define Battery_Status_GPIO_Port GPIOA
#define Ble_Mosfet_Pin GPIO_PIN_7
#define Ble_Mosfet_GPIO_Port GPIOA
#define Buzzer_Output_Pin GPIO_PIN_0
#define Buzzer_Output_GPIO_Port GPIOB
#define Buzzer_EN_Pin GPIO_PIN_1
#define Buzzer_EN_GPIO_Port GPIOB
#define ePD1_RESET_Pin GPIO_PIN_2
#define ePD1_RESET_GPIO_Port GPIOB
#define RFID_IRQ_Pin GPIO_PIN_10
#define RFID_IRQ_GPIO_Port GPIOB
#define RFID_IRQ_EXTI_IRQn EXTI4_15_IRQn
#define ePD1_D_C_Pin GPIO_PIN_11
#define ePD1_D_C_GPIO_Port GPIOB
#define Button_Status_Pin GPIO_PIN_12
#define Button_Status_GPIO_Port GPIOB
#define Button_Status_EXTI_IRQn EXTI4_15_IRQn
#define MCU_Mosfet_Pin GPIO_PIN_13
#define MCU_Mosfet_GPIO_Port GPIOB
#define Vibrator_motor_Pin GPIO_PIN_14
#define Vibrator_motor_GPIO_Port GPIOB
#define RFID_S_S_Pin GPIO_PIN_15
#define RFID_S_S_GPIO_Port GPIOB
#define ePD1_BUSY_Pin GPIO_PIN_8
#define ePD1_BUSY_GPIO_Port GPIOA
#define RFID_Mosfet_Control_Pin GPIO_PIN_11
#define RFID_Mosfet_Control_GPIO_Port GPIOA
#define ePD1_CS_Pin GPIO_PIN_15
#define ePD1_CS_GPIO_Port GPIOA
#define ePD1_SCK_Pin GPIO_PIN_3
#define ePD1_SCK_GPIO_Port GPIOB
#define ePD1_MOSI_Pin GPIO_PIN_5
#define ePD1_MOSI_GPIO_Port GPIOB
#define Battery_Indication_LED_Pin GPIO_PIN_8
#define Battery_Indication_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
//21
//11
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
