/*
 * User_UART.c
 *
 *  Created on: Jan 2, 2020
 *      Author: bhakti.deshpande
 */


#include "stm32l0xx_it.h"
#include "string.h"
#include "stdio.h"
#include "main.h"
#include "User_UART.h"
/************************** Function Prototypes  ***********************************/

UART_HandleTypeDef huart1;
UART_HandleTypeDef hlpuart1;


void UART1_Transmit( uint8_t *strptr, unsigned int length)
{
	HAL_UART_Transmit(&huart1,strptr,length,255);
	HAL_UART_Receive_IT(&huart1,usart_1_Rx_Data,1);
}

void LP_UART1_Transmit( uint8_t *strptr, unsigned int length)
{
	HAL_UART_Transmit(&hlpuart1,strptr,length,255);
	HAL_UART_Receive_IT(&hlpuart1,usart_1_Rx_Data,1);
}

