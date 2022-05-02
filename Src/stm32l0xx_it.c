/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32l0xx_it.c
 * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l0xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "User_Application.h"
#include "User_UART.h"
#include "User_Defines.h"
#include "Global.h"
#include "User_ADC.h"
#include "ED037TC2.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
unsigned int Counter_Response_Time = 0;
unsigned int Ble_Connect_Counter_Response_Time = 0,Second_count=1;
unsigned int Communication_timeout_counter = 0,Start_vibrator_motor_counter;
FLG flags;
UART_HandleTypeDef huart1;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc;
extern ADC_HandleTypeDef hadc;
extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart1;
extern RTC_HandleTypeDef hrtc;
extern SPI_HandleTypeDef hspi1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim6;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M0+ Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable Interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */


	unsigned char Chnl_cnt1;
    /*ADC Averaging*/
	for(Chnl_cnt1 = 0 ; Chnl_cnt1 < D_MAX_ADC_CH ; Chnl_cnt1++)
	{
		ADC_Sample[Chnl_cnt1][Sample_Number] = ADC_Count[Chnl_cnt1];
	}
	Sample_Number++;

	if(Sample_Number > D_NO_OF_SAMPLES)
	{
		Sample_Number = 0;
	}

	if(flags.Start_Response_time_flag == 1)
	{
		Counter_Response_Time++;
		if(Counter_Response_Time > 7000)
		{
			Counter_Response_Time = 0;
			flags.Start_Response_time_flag = 0;
			flags.F_Response_timeout_done = 1;
			//flags.Check_busy_pin_flag = 1;
			flags.Busy_pin_error_flag = 1;
		}

	}
	if(flags.Start_Command_Response_time == 1)
	{
		Counter_Response_Time++;
		if(Counter_Response_Time > 1000)
		{
			Counter_Response_Time = 0;
			flags.Start_Command_Response_time = 0;
			flags.Command_Response_timeout = 1;
		}
	}

	if( flags.Communication_started_flag == 0 && flags.Ble_connected_flag == 1 )
	{
		Counter_Response_Time++;
		if(Counter_Response_Time > 5000)
		{
			Counter_Response_Time = 0;
			flags.Start_Command_Response_time = 0;
			flags.Command_Response_timeout = 1;
		}
	}

	if(flags.Start_Ble_Connect_timeout_flag == 1 )
	{
		Ble_Connect_Counter_Response_Time++;
		if(Ble_Connect_Counter_Response_Time == Second_count*1000)
		{
			Second_count++;
		}
		if(Ble_Connect_Counter_Response_Time > 120000)
		{
			Ble_Connect_Counter_Response_Time = 0;
			flags.Start_Ble_Connect_timeout_flag = 0;
			flags.Shutdown_MCU_mosfet = 1;
		}
	}
	if(flags.Communication_started_flag == 1)
	{
		Communication_timeout_counter++;
		if(Communication_timeout_counter > 15000)
		{
			Communication_timeout_counter = 0;
			flags.Communication_started_flag = 0;
			flags.Communication_error_flag = 1;
		}

	}
	if(flags.F_Monitor_Low_Battery_Voltage == 1)/* Monitor low battery voltage for defined time to give low battery indication */
		{
			Monitor_Low_Battery_Voltage_Counter++;
			if(Monitor_Low_Battery_Voltage_Counter >= LOW_BATTERY_CONFIRM_TIME)
			{
				Monitor_Low_Battery_Voltage_Counter = 0;
				flags.F_Low_Battery_Voltage_Confirmed = 1;
				flags.F_Monitor_Low_Battery_Voltage = 0;
			}
		}

	if(flags.F_Monitor_full_Battery_Voltage == 1)/* Monitor low battery voltage for defined time to give low battery indication */
		{
			Monitor_full_Battery_Voltage_Counter++;
			if(Monitor_full_Battery_Voltage_Counter >= FULL_BATTERY_CONFIRM_TIME)
			{
				Monitor_full_Battery_Voltage_Counter = 0;
				flags.F_full_Battery_Voltage_Confirmed = 1;
				flags.F_Monitor_full_Battery_Voltage = 0;
			}
		}

	if(flags.F_Monitor_half_Battery_Voltage == 1)/* Monitor low battery voltage for defined time to give low battery indication */
		{
			Monitor_half_Battery_Voltage_Counter++;
			if(Monitor_half_Battery_Voltage_Counter >= HALF_BATTERY_CONFIRM_TIME)
			{
				Monitor_half_Battery_Voltage_Counter = 0;
				flags.F_half_Battery_Voltage_Confirmed = 1;
				flags.F_Monitor_half_Battery_Voltage = 0;
			}
		}



	if(flags.Start_vibrator_motor_flag == 1)
	{
		Start_vibrator_motor_counter++;
		if(Start_vibrator_motor_counter >= 500)
		{
			Start_vibrator_motor_counter = 0;
			flags.Start_vibrator_motor_flag = 0;
			Vibrator_Motor_L;
//			if(flags.Excecute_alart==1)
//			{
//				flags.Excecute_alart=0;
//				MCU_Mosfet_H;
//				//MCU_Mosfet2_H;
//				Ble_Mosfet_H;
//
//			}
		}
	}





  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles RTC global interrupt through EXTI lines 17, 19 and 20 and LSE CSS interrupt through EXTI line 19.
  */
void RTC_IRQHandler(void)
{
  /* USER CODE BEGIN RTC_IRQn 0 */

  /* USER CODE END RTC_IRQn 0 */
  HAL_RTC_AlarmIRQHandler(&hrtc);
  HAL_RTCEx_WakeUpTimerIRQHandler(&hrtc);
  /* USER CODE BEGIN RTC_IRQn 1 */

  /* USER CODE END RTC_IRQn 1 */
}

/**
  * @brief This function handles EXTI line 4 to 15 interrupts.
  */
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI4_15_IRQn 0 */
	 if(__HAL_GPIO_EXTI_GET_FLAG(Button_Status_Pin)){
		flags.Tag_Expire_external_interrupt_flag = 1;
		//HAL_GPIO_TogglePin(Battery_Indication_LED_Pin, Battery_Indication_LED_GPIO_Port);// toggle LD2 LED
		 }

  /* USER CODE END EXTI4_15_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(RFID_IRQ_Pin);
  HAL_GPIO_EXTI_IRQHandler(Button_Status_Pin);
  /* USER CODE BEGIN EXTI4_15_IRQn 1 */

  /* USER CODE END EXTI4_15_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel 1 interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc);
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles ADC, COMP1 and COMP2 interrupts (COMP interrupts through EXTI lines 21 and 22).
  */
void ADC1_COMP_IRQHandler(void)
{
  /* USER CODE BEGIN ADC1_COMP_IRQn 0 */

  /* USER CODE END ADC1_COMP_IRQn 0 */
  HAL_ADC_IRQHandler(&hadc);
  /* USER CODE BEGIN ADC1_COMP_IRQn 1 */

  /* USER CODE END ADC1_COMP_IRQn 1 */
}

/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
  /* USER CODE BEGIN TIM3_IRQn 0 */

  /* USER CODE END TIM3_IRQn 0 */
  HAL_TIM_IRQHandler(&htim3);
  /* USER CODE BEGIN TIM3_IRQn 1 */

  /* USER CODE END TIM3_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt and DAC1/DAC2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */

  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles SPI1 global interrupt.
  */
void SPI1_IRQHandler(void)
{
  /* USER CODE BEGIN SPI1_IRQn 0 */

  /* USER CODE END SPI1_IRQn 0 */
  HAL_SPI_IRQHandler(&hspi1);
  /* USER CODE BEGIN SPI1_IRQn 1 */

  /* USER CODE END SPI1_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles RNG and LPUART1 Interrupts / LPUART1 wake-up interrupt through EXTI line 28.
  */
void RNG_LPUART1_IRQHandler(void)
{
  /* USER CODE BEGIN RNG_LPUART1_IRQn 0 */

  /* USER CODE END RNG_LPUART1_IRQn 0 */
  HAL_UART_IRQHandler(&hlpuart1);
  /* USER CODE BEGIN RNG_LPUART1_IRQn 1 */

  /* USER CODE END RNG_LPUART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
