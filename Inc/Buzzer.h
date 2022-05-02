/**
  ******************************************************************************
  * File Name          : Buzzer.h
  * Description        : Function prototypes and Macros for Buzzer interface.
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
//#include "i2c.h"
//#include "tim.h"
//#include "usart.h"
//#include "gpio.h"
//#include "Control.h"
//#include "Cypress_Capsense_3116.h"
//#include "Common_Defines.h"

/* Define ------------------------------------------------------------*/
#define Buzzer_Enable_GPIO_Port GPIOE		//GPIOC
#define Buzzer_Enable_Pin GPIO_PIN_0		//GPIO_PIN_6

/* Variables ---------------------------------------------------------*/
extern unsigned char F_Buzzer_Tune9;
extern unsigned char F_Buzzer_Beep1;
extern unsigned char F_Buzzer_Tune1;
extern unsigned char F_Buzzer_Tune2;
extern unsigned char F_Buzzer_Melody1;
extern unsigned char F_Buzzer_Beep2;
extern unsigned char F_Buzzer_Tune3;
extern unsigned char F_Buzzer_Melody2;
extern unsigned char F_Buzzer_Tune5;
extern unsigned char F_Buzzer_Tune6;
extern unsigned char F_Buzzer_Tune7;
extern unsigned char F_Buzzer_Tune8;
extern unsigned char F_Buzzer_Tune4;
extern unsigned char F_Buzzer_Beep3;
extern unsigned char F_Buzzer_Beep4;


/* Functions ---------------------------------------------------------*/
extern void Initiate_Buzzer_Tune4(void);
extern void Execute_Buzzer_Tune4(void);
extern void Initiate_Buzzer_Tune9(void);
extern void Execute_Buzzer_Tune9(void);
extern void Initiate_Buzzer_Beep1(void);
extern void Execute_Buzzer_Beep1(void);
extern void Initiate_Buzzer_Tune1(void);
extern void Execute_Buzzer_Tune1(void);
extern void Initiate_Buzzer_Tune2(void);
extern void Execute_Buzzer_Tune2(void);
extern void Initiate_Buzzer_Melody1(void);
extern void Execute_Buzzer_Melody1(void);
extern void Exit_Buzzer_Melody1(void);
extern void Initiate_Buzzer_Beep2(void);
extern void Execute_Buzzer_Beep2(void);
extern void Initiate_Buzzer_Melody2(void);
extern void Execute_Buzzer_Melody2(void);
extern void Exit_Buzzer_Melody2(void);
extern void Initiate_Buzzer_Tune3(void);
extern void Execute_Buzzer_Tune3(void);
extern void Initiate_Buzzer_Tune5(void);
extern void Execute_Buzzer_Tune5(void);
extern void Initiate_Buzzer_Tune6(void);
extern void Execute_Buzzer_Tune6(void);
extern void Initiate_Buzzer_Tune7(void);
extern void Execute_Buzzer_Tune7(void);
extern void Initiate_Buzzer_Tune8(void);
extern void Execute_Buzzer_Tune8(void);
extern void Initiate_Buzzer_Beep3(void);
extern void Execute_Buzzer_Beep3(void);
extern void Initiate_Buzzer_Beep4(void);
extern void Execute_Buzzer_Beep4(void);
extern void Start_PWM_Buzzer(void);
extern void Stop_PWM_Buzzer(void);
extern void Configure_PWM_uS(unsigned int, unsigned int);
extern void Clear_Buzzer_Alarm_Flags(void);


