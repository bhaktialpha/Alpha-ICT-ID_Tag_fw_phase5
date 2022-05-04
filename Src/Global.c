/*
 * Global.c
 *
 *  Created on: Sep 30, 2020
 *      Author: bhakti.deshpande
 */



#include "main.h"
#include "usart.h"
#include "gpio.h"




uint32_t Custom_delay;

void Init_ADC(void);
void DeInit_ADC(void);
unsigned char Send_Command_State;

