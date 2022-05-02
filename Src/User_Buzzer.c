/**
  ******************************************************************************
  * File Name          : Buzzer.c
  * Description        : Program modules for buzzer interface.
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "Buzzer.h"
#include "string.h"

extern void MX_TIM1_Init(void);

/* Private variables ---------------------------------------------------------*/
unsigned char PWM_Tone_Part = 0;
unsigned char F_Buzzer_Tune4 = 0;
unsigned char F_Buzzer_Tune9 = 0;
unsigned char F_Buzzer_Beep1 = 0;
unsigned char F_Buzzer_Tune1 = 0;
unsigned char F_Buzzer_Tune2 = 0;
unsigned char F_Buzzer_Melody1 = 0;
unsigned char F_Buzzer_Beep2 = 0;
unsigned char F_Buzzer_Melody2 = 0;
unsigned char F_Buzzer_Tune3 = 0;
unsigned char F_Buzzer_Tune5 = 0;
unsigned char F_Buzzer_Tune6 = 0;
unsigned char F_Buzzer_Tune7 = 0;
unsigned char F_Buzzer_Tune8 = 0;
unsigned char F_Buzzer_Beep3 = 0;
unsigned char F_Buzzer_Beep4 = 0;


 unsigned char F_Temporary_Mute = 0;
 unsigned char PWM_Buzzer_Counter = 0;
 unsigned char F_Start_Buzzer_Beep = 0;
 unsigned char Buzzer_Beep_Counter = 0;
 unsigned char F_Start_PWM_Buzzer_For_Key = 0;
 unsigned char F_Start_Buzzer_Beep_For_Key = 0;
 unsigned char F_Start_PWM_Buzzer_Long_Beep_For_Key = 0;
//extern unsigned char F_PowerOn_LED_Pattern;
 unsigned char F_Wait_For_Unlock_Buzzer = 0;

unsigned int PWM_Time_Counter = 0;

unsigned int Current_Volume_Val_Key_Beep = 120;
unsigned int Current_Volume_Val_Buzzer_Tune = 120;

extern TIM_HandleTypeDef htim3;

/* Private function prototypes -----------------------------------------------*/
void Initiate_Buzzer_Tune4(void);
void Execute_Buzzer_Tune4(void);
void Initiate_Buzzer_Tune9(void);
void Execute_Buzzer_Tune9(void);
void Initiate_Buzzer_Beep1(void);
void Execute_Buzzer_Beep1(void);
void Initiate_Buzzer_Tune1(void);
void Execute_Buzzer_Tune1(void);
void Initiate_Buzzer_Tune2(void);
void Execute_Buzzer_Tune2(void);
void Initiate_Buzzer_Melody1(void);
void Execute_Buzzer_Melody1(void);
void Exit_Buzzer_Melody1(void);
void Initiate_Buzzer_Beep2(void);
void Execute_Buzzer_Beep2(void);
void Initiate_Buzzer_Melody2(void);
void Execute_Buzzer_Melody2(void);
void Exit_Buzzer_Melody2(void);
void Initiate_Buzzer_Tune3(void);
void Execute_Buzzer_Tune3(void);
void Initiate_Buzzer_Tune5(void);
void Execute_Buzzer_Tune5(void);
void Initiate_Buzzer_Tune6(void);
void Execute_Buzzer_Tune6(void);
void Initiate_Buzzer_Tune7(void);
void Execute_Buzzer_Tune7(void);
void Initiate_Buzzer_Tune8(void);
void Execute_Buzzer_Tune8(void);
//void Initiate_FP_Index_Display_Alarm(void);
//void Execute_FP_Index_Display_Alarm(void);
//void Initiate_Lock_Deadbolt_Alarm(void);
//void Execute_Lock_Deadbolt_Alarm(void);
void Initiate_Buzzer_Beep3(void);
void Execute_Buzzer_Beep3(void);
void Initiate_Buzzer_Beep4(void);
void Execute_Buzzer_Beep4(void);
//void Initiate_Unlock_Key_Beep_Alarm(void);
//void Execute_Unlock_Key_Beep_Alarm(void);
void Start_PWM_Buzzer(void);
//void Stop_PWM_Buzzer(void);
void Configure_PWM_uS(unsigned int Period_Val,unsigned int Vol_Val);
void Clear_Buzzer_Alarm_Flags(void);

/* Private user code ---------------------------------------------------------*/
/**
  * @brief  Disable buzzer and stop PWM.
  * @param  None
  * @retval None
  */
void Start_PWM_Buzzer(void)
{
	HAL_GPIO_WritePin(Buzzer_Enable_GPIO_Port, Buzzer_Enable_Pin, GPIO_PIN_SET);/* Enable Buzzer */
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
}

/**
  * @brief  Enable buzzer and start PWM.
  * @param  None
  * @retval None
  */
//void Stop_PWM_Buzzer(void)
//{
//	HAL_GPIO_WritePin(Buzzer_Enable_GPIO_Port, Buzzer_Enable_Pin, GPIO_PIN_RESET);/* Disable Buzzer */
//	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
//}
void Stop_Buzzer(void)
{
//    htim3.Init.Prescaler = TIMER2_PRESCALAR_VAL;
	htim3.Init.Prescaler = 0;
    htim3.Init.Period = 0;//_Period;
    HAL_TIM_Base_Init(&htim3);
    HAL_GPIO_WritePin(Buzzer_Enable_GPIO_Port, Buzzer_Enable_Pin, GPIO_PIN_RESET);/* Disable Buzzer */
    HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
}

/**
  * @brief  Initiate flags for starting Buzzer_Tune4.
  * @param  None
  * @retval None
  */
void Configure_PWM_uS(unsigned int Period_Val,unsigned int Vol_Val)
{
	htim3.Init.Prescaler = 16;//TIMER2_PRESCALAR_VAL;
	htim3.Init.Period = Period_Val;
	HAL_TIM_Base_Init(&htim3);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, Vol_Val);
}

/**
  * @brief  Start Buzzer_Tune4.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune4(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(360, Current_Volume_Val_Buzzer_Tune);// 168);/* Input period and duty cycle respectively */
		if(PWM_Time_Counter == 0 && Current_Volume_Val_Buzzer_Tune > 0)
		{
			Start_PWM_Buzzer();
		}
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 10)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(336, Current_Volume_Val_Buzzer_Tune);// 156);/* Input period and duty cycle respectively */
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 11)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360, Current_Volume_Val_Buzzer_Tune);// 168);/* Input period and duty cycle respectively */
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 10)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(336, Current_Volume_Val_Buzzer_Tune);// 156);/* Input period and duty cycle respectively */
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 11)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune4 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}
//void Execute_Buzzer_Tune4(void)
//{
//	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
//	{
//		Configure_PWM_uS(306, Current_Volume_Val_Buzzer_Tune);// 168);/* Input period and duty cycle respectively */
//		if(PWM_Time_Counter == 0 && Current_Volume_Val_Buzzer_Tune > 0)
//		{
//			Start_PWM_Buzzer();
//		}
//	}
//	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 10)
//	{
//		PWM_Time_Counter = 0;
//		Configure_PWM_uS(282, Current_Volume_Val_Buzzer_Tune);// 156);/* Input period and duty cycle respectively */
//		PWM_Tone_Part++;
//	}
//	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 11)
//	{
//		PWM_Time_Counter = 0;
//		Configure_PWM_uS(306, Current_Volume_Val_Buzzer_Tune);// 168);/* Input period and duty cycle respectively */
//		PWM_Tone_Part++;
//	}
//	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 10)
//	{
//		PWM_Time_Counter = 0;
//		Configure_PWM_uS(282, Current_Volume_Val_Buzzer_Tune);// 156);/* Input period and duty cycle respectively */
//		PWM_Tone_Part++;
//	}
//	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 11)
//	{
//		PWM_Time_Counter = 0;
//		PWM_Tone_Part = 0;
//		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
//		F_Buzzer_Tune4 = 0;
//		Stop_Buzzer();
//	}
//	PWM_Time_Counter++;
//}
/**
  * @brief  Initiate flags for starting Buzzer_Tune4.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune4(void)
{
	PWM_Buzzer_Counter = 0;
	F_Start_Buzzer_Beep = 0;
	Buzzer_Beep_Counter = 0;
	F_Start_PWM_Buzzer_For_Key = 0;
	F_Start_Buzzer_Beep_For_Key = 0;
	F_Start_PWM_Buzzer_Long_Beep_For_Key = 0;
	PWM_Buzzer_Counter = 0;

	F_Buzzer_Tune4 = 1;
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
}

/**
  * @brief  Initiate flags for starting Buzzer_Tune9.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune9(void)
{
//	if(!(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR28)))		/* Check RTC backup register to decide whether wakeup event occurred or power on reset */
//	{
//		HAL_Delay(10);
//		/* Initialize timer for pwm generation for buzzer */
//		MX_TIM1_Init();
		F_Buzzer_Tune9 = 1;
		PWM_Tone_Part = 0;
		PWM_Time_Counter = 0;
//		Initiate_Power_On_LED_Pattern();
//		HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR28, 1);
//		HAL_Delay(10);
//	}
}

/**
  * @brief  Start Buzzer_Tune9.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune9(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(400, 250);/* Input period and duty cycle respectively */
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360, 250);/* Input period and duty cycle respectively */
		PWM_Tone_Part++;

	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(320, 250);/* Input period and duty cycle respectively */
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(280, 250);/* Input period and duty cycle respectively */
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune9 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for Buzzer_Beep1.
  * @param  NoneF_Lock_Alarm
  * @retval None
  */
void Initiate_Buzzer_Beep1(void)
{
	/* Initialize timer for pwm generation for buzzer */
	MX_TIM3_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Beep1 = 1;
}

/**
  * @brief  Start Buzzer_Beep1.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Beep1(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(360, Current_Volume_Val_Key_Beep);// 120);/* Input period and duty cycle respectively */
		if(PWM_Time_Counter == 0 && Current_Volume_Val_Key_Beep > 0)
		{
			Start_PWM_Buzzer();
		}
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 25)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Beep1 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Tune1.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune1(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Tune1 = 1;
}

/**
  * @brief  Start Buzzer_Tune1.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune1(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(410, Current_Volume_Val_Buzzer_Tune);//200);
		if(PWM_Time_Counter == 0 && Current_Volume_Val_Buzzer_Tune > 0)
		{
			if(F_Temporary_Mute == 0)
			{
				Start_PWM_Buzzer();
			}
		}
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 5)//62)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(370, Current_Volume_Val_Buzzer_Tune);//200);
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 5)//106)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(410, Current_Volume_Val_Buzzer_Tune);//200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 5)//62)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(370, Current_Volume_Val_Buzzer_Tune);//200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 5)//106)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(410, Current_Volume_Val_Buzzer_Tune);//200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 4 && PWM_Time_Counter >= 5)//62)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(370, Current_Volume_Val_Buzzer_Tune);//200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 5 && PWM_Time_Counter >= 5)//62)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(410, Current_Volume_Val_Buzzer_Tune);//200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 6 && PWM_Time_Counter >= 5)//62)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(370, Current_Volume_Val_Buzzer_Tune);//200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 7 && PWM_Time_Counter >= 5)//62)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(410, Current_Volume_Val_Buzzer_Tune);//200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 8 && PWM_Time_Counter >= 5)//106)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune1 = 0;
		F_Wait_For_Unlock_Buzzer = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Tune2.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune2(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Tune2 = 1;
}

/**
  * @brief  Start Buzzer_Tune2.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune2(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(360, Current_Volume_Val_Buzzer_Tune);//150);
		if(PWM_Time_Counter == 0 && Current_Volume_Val_Buzzer_Tune > 0)
		{
			if(F_Temporary_Mute == 0)
			{
				Start_PWM_Buzzer();
			}
		}
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 14)//62)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(370, Current_Volume_Val_Buzzer_Tune);//150);
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 13)//106)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(460, Current_Volume_Val_Buzzer_Tune);//150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 17)//62)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune2 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Melody1.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Melody1(void)
{
	/* Initialize timer for pwm generation for buzzer */
	MX_TIM3_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Melody1 = 1;
}

/**
  * @brief  Exit Buzzer_Melody1.
  * @param  None
  * @retval None
  */
void Exit_Buzzer_Melody1(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Melody1 = 0;
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
}

/**
  * @brief  Start Buzzer_Melody1.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Melody1(void)
{
	unsigned char F_Repeat_Tune = 0;

	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(355,150);
 		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if((PWM_Tone_Part == 0)&& (PWM_Time_Counter > 9))
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(371,150);
 		PWM_Tone_Part++;
 	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 10)//106) //88)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(409,150);
 		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 9)//62) //112)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(452,150);
 		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 9)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(471,150);
 		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 4 && PWM_Time_Counter >= 12)//62) //72)//
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
	}
	else if(PWM_Tone_Part == 5 && PWM_Time_Counter >= 2)//62) //116)//
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		F_Repeat_Tune = 1;
 	}
//	PWM_Time_Counter++;
	if(F_Repeat_Tune == 1)
	{
		F_Repeat_Tune = 0;
		PWM_Time_Counter = 0;
		Stop_Buzzer();
	}
	else
	{
		PWM_Time_Counter++;
	}

}

/**
  * @brief  Initiate flags for Buzzer_Beep2.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Beep2(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Beep2 = 1;
}

/**
  * @brief  Start Buzzer_Beep2.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Beep2(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(360,120);
		if(PWM_Time_Counter == 0)
			Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 25)
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 5)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,120);
		Start_PWM_Buzzer();
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 25)
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		F_Buzzer_Beep2 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Melody2.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Melody2(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Melody2 = 1;
}

/**
  * @brief  Exit Buzzer_Melody2.
  * @param  None
  * @retval None
  */
void Exit_Buzzer_Melody2(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Melody2 = 0;
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
}

/**
  * @brief  Start Buzzer_Melody2.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Melody2(void)
{
	unsigned char F_Repeat_Tune = 0;

	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(439,300);
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if((PWM_Tone_Part == 0)&& (PWM_Time_Counter > 2))
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(415,300);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 2)//106) //88)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(404,120);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 4)//62) //112)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 4)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(355,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 4 && PWM_Time_Counter >= 2)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(366,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 5 && PWM_Time_Counter >= 2)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(331,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 6 && PWM_Time_Counter >= 2)//62) //72)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(317,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 7 && PWM_Time_Counter >= 2)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(304,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 8 && PWM_Time_Counter >= 2)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(304,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 9 && PWM_Time_Counter >= 2)//62) //72)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(317,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 10 && PWM_Time_Counter >= 2)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(331,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 11 && PWM_Time_Counter >= 2)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(366,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 12 && PWM_Time_Counter >= 2)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(355,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 13 && PWM_Time_Counter >= 2)//62) //112)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 14 && PWM_Time_Counter >= 4)//106) //88)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(404,120);
		PWM_Tone_Part++;
	}
	else if((PWM_Tone_Part == 15) && (PWM_Time_Counter >= 4))
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(415,300);
		PWM_Tone_Part++;
	}
	if(PWM_Tone_Part == 16 && PWM_Time_Counter >= 2)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(439,300);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 17 && PWM_Time_Counter >= 2)//62) //116)//
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part=0;
		F_Repeat_Tune = 1;
 	}
	if(F_Repeat_Tune == 1)
	{
		PWM_Time_Counter = 0;
		F_Repeat_Tune = 0;
		Stop_Buzzer();
	}
	else
	{
		PWM_Time_Counter++;
	}
}

/**
  * @brief  Initiate flags for starting Buzzer_Tune3.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune3(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Tune3 = 1;
}

/**
  * @brief  Start Buzzer_Tune3.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune3(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(583,300);
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if((PWM_Tone_Part == 0)&& (PWM_Time_Counter > 6))
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(566,300);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 6)//106) //88)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(326,120);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 6)//62) //112)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(331,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 6)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(355,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 4 && PWM_Time_Counter >= 6)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 5 && PWM_Time_Counter >= 6)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(376,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 6 && PWM_Time_Counter >= 12)//62) //72)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 7 && PWM_Time_Counter >= 6)//106) //100)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(355,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 8 && PWM_Time_Counter >= 6)//62) //112)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(331,150);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 9 && PWM_Time_Counter >= 6)//106) //88)//
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(326,120); //(608,300);
		PWM_Tone_Part++;
	}
	else if((PWM_Tone_Part == 10)&& (PWM_Time_Counter > 6))
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(566,300);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 11 && PWM_Time_Counter > 6)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(583,300);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 12 && PWM_Time_Counter >= 7)//62) //116)//
	{

		PWM_Time_Counter = 0;
		PWM_Tone_Part=0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune3 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Tune5.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune5(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	F_Temporary_Mute = 0;							/* Disable temporary mute function */
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Tune5 = 1;
}

/**
  * @brief  Start Buzzer_Tune5.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune5(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(260,160);
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 7)	//72
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(330,200);
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 12)	//116
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(260,160);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 7)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(330,200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 4 && PWM_Time_Counter >= 7)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(260,160);
		PWM_Tone_Part++;
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 5 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(330,200);
	}
	else if(PWM_Tone_Part == 6 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(260,160);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 7 && PWM_Time_Counter >= 7)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(330,200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 8 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);

	}
	else if(PWM_Tone_Part == 9 && PWM_Time_Counter >= 7)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(260,160);
		PWM_Tone_Part++;
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 10 && PWM_Time_Counter >= 7)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(330,200);
	}
	else if(PWM_Tone_Part == 11 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(260,160);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 12 && PWM_Time_Counter >= 7)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(330,200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 13 && PWM_Time_Counter >= 12)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune5 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting alarm for Buzzer_Tune6.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune6(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Tune6 = 1;
}

/**
  * @brief  Start alarm for Buzzer_Tune6.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune6(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(480,300);
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 15)//62//152)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(320,220);
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 17)//106//168)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune6 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting alarm for Buzzer_Tune7.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune7(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Tune7 = 1;
}

/**
  * @brief  Start alarm for Buzzer_Tune7.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune7(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(520,300);
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 12)//62//124)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(300,200);
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 16)//106//164)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 14)//62)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(300,200);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 15)//106//148)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune7 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Tune8.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Tune8(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Tune8 = 1;
}

/**
  * @brief  Start Buzzer_Tune8.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Tune8(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(380,140);
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 20)//62//196)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
		Configure_PWM_uS(420,160);
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 19)//106)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(460,250);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 20)//62)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(500,350);
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 19)//106)
	{
		PWM_Time_Counter = 0;
		PWM_Tone_Part = 0;
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		F_Buzzer_Tune8 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Beep3.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Beep3(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	F_Temporary_Mute = 0;							/* Disable temporary mute function */
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Beep3 = 1;
}

/**
  * @brief  Start Buzzer_Beep3.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Beep3(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(360,120);
		if(PWM_Time_Counter == 0)
			Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 25)//1
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 5)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,120);
		Start_PWM_Buzzer();
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 25)//2
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 5)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,120);
		Start_PWM_Buzzer();
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 4 && PWM_Time_Counter >= 25)//3
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		F_Buzzer_Beep3 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Initiate flags for starting Buzzer_Beep4.
  * @param  None
  * @retval None
  */
void Initiate_Buzzer_Beep4(void)
{
	/* Initialize timer for pwm generation for buzzer */
//	MX_TIM1_Init();
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
	F_Buzzer_Beep4 = 1;
}

/**
  * @brief  Start Buzzer_Beep4.
  * @param  None
  * @retval None
  */
void Execute_Buzzer_Beep4(void)
{
	if(PWM_Tone_Part == 0 && PWM_Time_Counter == 0)
	{
		Configure_PWM_uS(360,120);
		if(PWM_Time_Counter == 0)
		Start_PWM_Buzzer();
	}
	else if(PWM_Tone_Part == 0 && PWM_Time_Counter >= 25)
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 1 && PWM_Time_Counter >= 5)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,120);
		Start_PWM_Buzzer();
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 2 && PWM_Time_Counter >= 25)
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 3 && PWM_Time_Counter >= 5)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,120);
		Start_PWM_Buzzer();
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 4 && PWM_Time_Counter >= 25)
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 5 && PWM_Time_Counter >= 5)
	{
		PWM_Time_Counter = 0;
		Configure_PWM_uS(360,120);
		Start_PWM_Buzzer();
		PWM_Tone_Part++;
	}
	else if(PWM_Tone_Part == 6 && PWM_Time_Counter >= 25)
	{
		HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_3);
		PWM_Time_Counter = 0;
		F_Buzzer_Beep4 = 0;
		Stop_Buzzer();
	}
	PWM_Time_Counter++;
}

/**
  * @brief  Clear other buzzer alarm flags during antitheft error.
  * @param  None
  * @retval None
  */
void Clear_Buzzer_Alarm_Flags(void)
{
	F_Buzzer_Tune4 = 0;
	F_Buzzer_Tune9 = 0;
	F_Buzzer_Beep1 = 0;
	F_Buzzer_Tune1 = 0;
	F_Buzzer_Tune2 = 0;
	F_Buzzer_Beep2 = 0;
	F_Buzzer_Melody2 = 0;
	F_Buzzer_Tune3 = 0;
	F_Buzzer_Tune5 = 0;
	F_Buzzer_Tune6 = 0;
	F_Buzzer_Tune7 = 0;
	F_Buzzer_Tune8 = 0;
	F_Buzzer_Melody1 = 0;
	F_Buzzer_Beep3 = 0;
	F_Buzzer_Beep4 = 0;
	PWM_Tone_Part = 0;
	PWM_Time_Counter = 0;
}
