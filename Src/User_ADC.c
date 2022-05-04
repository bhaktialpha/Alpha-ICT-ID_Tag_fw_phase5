#include "User_Defines.h"
#include "main.h"
#include "User_ADC.h"
#include "User_Application.h"
#include "Screens.h"
#include "ED037TC2.h"
#include "Buzzer.h"
#include "rtc.h"
#include "usart.h"
#include "User_UART.h"
#define BATTERY_VOLTAGE_LOW_LEVEL1			3.4
#define BATTERY_VOLTAGE_LOW_LEVEL2			3.50//10%
//#define BATTERY_FULL_CHARGE					4.10//
#define BATTERY_HALF_CHARGE			3.70//50%
#define BATTERY_FULL_CHARGE			3.80//50%
//#define LOW_BATTERY_CONFIRM_TIME            100      //1 sec (10 ms timer * 100)


uint32_t ADC_Count[D_MAX_ADC_CH];

unsigned char Sample_Number;
double Battery_Voltage;
double ADC_Average[D_MAX_ADC_CH];

unsigned int Monitor_Low_Battery_Voltage_Counter = 0,Monitor_high_Battery_Voltage_Counter = 0,Monitor_half_Battery_Voltage_Counter = 0,F_Unlock_Door=0;
//unsigned int Monitor_Low_Battery_Recover_Voltage_Counter = 0;

unsigned int ADC_Sample[D_MAX_ADC_CH][D_NO_OF_SAMPLES];

double  Converted_ADC_Value[D_MAX_ADC_CH];
double ADCTotalSum;

void Get_ADC_Value_Converted(unsigned char adc_ch, double *Val_Dest);
unsigned int Get_ADC_Average_Single(unsigned char adc_ch);
/***************************************************************************************************
 * Function Name	: void Get_ADC_Average_Single()
 * Parameter		: adc_ch  - ADC Channel Number unsigned char
 * return			: avg_value   - calculated average unsigned int
 * Description 		: This Function is written to calculate average of single ADC Channel.
 *
 ***************************************************************************************************/
unsigned int Get_ADC_Average_Single(unsigned char adc_ch)
{
	unsigned char loop_cnt;
	unsigned int avg_value;

	for(loop_cnt = 0 ; loop_cnt < D_NO_OF_SAMPLES ; loop_cnt++)
	{
		ADCTotalSum += ADC_Sample[adc_ch][loop_cnt];
	}
	avg_value = ADCTotalSum / D_NO_OF_SAMPLES;
	ADCTotalSum = 0;

	return avg_value;
}


/***************************************************************************************************
 * Function Name	: void Get_ADC_Value()
 * Parameter		: adc_ch  - ADC Channel Number unsigned char
 * return			: value   - calculated value float
 * Description 		: This Function is written to calculate the actual value of parameter connected to ADC Channel
 * 					  eg.: Temperature (deg. C) , Current (Ampere) , Voltage(Volts)
 ***************************************************************************************************/
void Get_ADC_Value_Converted(unsigned char adc_ch, double *Val_Dest)
{

	double value;

	value = ADC_Average[adc_ch] * 3.3;
	value = value / 4096.00;
	value = value * 2.00;
	*Val_Dest = value;
}

/**
 * @brief ADC sensing is done here.
 *  If latch motor is in Drive mode ADC sensing is not done. Because surge in Battery Voltage may give indication of Low battery
 *  So to prevent this, ADC sensing is not done during motor operation
 * @param None
 * @retval None
 */

int ADC_Sensing_Operation(void)
{
	ADC_Average[0] = Get_ADC_Average_Single(0);

	Get_ADC_Value_Converted(0,&Battery_Voltage);

	if(Battery_Voltage < BATTERY_VOLTAGE_LOW_LEVEL1)
	{

		if(flags.F_Monitor_Low_Battery_Voltage == 0)
		{
			flags.F_Monitor_Low_Battery_Voltage = 1;
			Monitor_Low_Battery_Voltage_Counter = 0;
		}


		if(flags.F_Low_Battery_Voltage_Confirmed == 1)
		{

			Initiate_Buzzer_Beep3();					//tune - low, high, low, high - 2
			Execute_Buzzer_Beep3();
			Vibrator_Motor_H;
			flags.Start_vibrator_motor_flag = 1;
#if(D_DEBUG1)
			uint8_t test_1[36]="Low Battery, please charge battery\r\n";
			UART1_Transmit(test_1,36);

#endif
			HAL_Delay(3000);
			flags.F_Low_Battery_Voltage_Confirmed = 0;
			//HAL_UART_DeInit(&hlpuart1);
			MX_GPIO_DeInit();
			Ble_Mosfet_H;
			MCU_Mosfet_H;
		}
	}

	else if(Battery_Voltage < BATTERY_HALF_CHARGE)
	{
		if(flags.F_Monitor_Low_Battery_Voltage == 0)
		{
			flags.F_Monitor_Low_Battery_Voltage = 1;
			Monitor_Low_Battery_Voltage_Counter = 0;
		}

		if(flags.F_Low_Battery_Voltage_Confirmed == 1)
		{
			flags.F_Low_Battery_Voltage_Confirmed = 0;
			//if(flags.F_Low_Battery_Voltage == 0)
			{
				flags.F_Low_Battery_Voltage = 1;              //Low Battery Detected

				/* Start Motor to lock*/

				HAL_GPIO_WritePin(Buzzer_EN_GPIO_Port, Buzzer_EN_Pin, GPIO_PIN_SET);/* Enable Buzzer */
				Initiate_Buzzer_Beep2();					//beep 2
				Execute_Buzzer_Beep2();
				Vibrator_Motor_H;
				flags.Start_vibrator_motor_flag = 1;
				//	HAL_GPIO_WritePin(LCD_Mosfet_GPIO_Port,LCD_Mosfet_Pin,0);
#if(D_DEBUG1)
				uint8_t test_1[40]="Low Battery 10%, please charge battery\r\n";
				UART1_Transmit(test_1,40);
				HAL_Delay(1000);
#endif
				flags.Battery_status_updated_flag = 1;


			}
		}

	}

	else if(Battery_Voltage >= BATTERY_HALF_CHARGE && Battery_Voltage <= BATTERY_FULL_CHARGE)
	{
		if(flags.F_Monitor_half_Battery_Voltage == 0)
		{
			flags.F_Monitor_half_Battery_Voltage = 1;
			Monitor_half_Battery_Voltage_Counter = 0;
		}

		if(flags.F_half_Battery_Voltage_Confirmed == 1)
		{
			flags.F_half_Battery_Voltage_Confirmed = 0;
			HAL_GPIO_WritePin(LCD_Mosfet_GPIO_Port,LCD_Mosfet_Pin,0);
			flags.Battery_status_updated_flag = 1;
#if(D_DEBUG)
			uint8_t test_1[13]="50% Battery\r\n";
			UART1_Transmit(test_1,13);
			HAL_Delay(1000);
#endif

		}

	}

	else if(Battery_Voltage > BATTERY_FULL_CHARGE)
	{
		if(flags.F_Monitor_full_Battery_Voltage == 0)
		{
			flags.F_Monitor_full_Battery_Voltage = 1;
			Monitor_full_Battery_Voltage_Counter = 0;
		}

		if(flags.F_full_Battery_Voltage_Confirmed == 1)
		{
			flags.F_full_Battery_Voltage_Confirmed = 0;

#if(D_DEBUG)
			uint8_t test_1[13]="Full Battery\r\n";
			UART1_Transmit(test_1,14);
			HAL_Delay(1000);
#endif
			flags.Battery_status_updated_flag = 1;


		}
	}
	else
	{
		Monitor_Low_Battery_Voltage_Counter = 0;
	}

	if(flags.Battery_status_updated_flag == 1)
	{
		if(flags.Check_reapet_battery_voltage_flag == 1)
		{
			DeInit_ADC();
			HAL_RTC_MspDeInit(&hrtc);
			HAL_RTC_MspInit(&hrtc);
			MX_RTC_Init_1();
			flags.F_Run_Stop2_Mode =1;
			flags.Check_reapet_battery_voltage_flag = 0;
		}
		else if(flags.Check_reapet_battery_voltage_flag == 0)
		{

			DeInit_ADC();
			Ble_Mosfet_L;	 /* BM71 Mosfet control pin */
			MX_LPUART1_UART_Init();
			HAL_UART_Receive_IT(&hlpuart1,lpuart_1_Rx_Data,1); 		/* LPUART1 Interrupt call */
			flags.Battery_status_updated_flag = 0;
			flags.Check_battery_voltage_flag = 0;
			flags.Initialize_ble_flag = 1;
			return SUCCESS;
		}
	}

}

