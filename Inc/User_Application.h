/**
  ******************************************************************************
  * File Name          : Application.h
  * Description        : Function prototypes and Macros for Application execution.
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/

#include "stm32l0xx_hal.h"

void Display_Application(void);
void  UART1_Display_Application(void );
void Ckeck_communication_error(void);
void Save_RTC_Value_Application(void);
extern int hex_to_dec(unsigned int hexadecimal_number);
