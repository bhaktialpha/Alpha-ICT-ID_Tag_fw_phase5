/*
 * User_ISRs.c
 *
 *  Created on: 03-May-2019
 *      Author:Bhakti
 */

#include <string.h>
#include <stdio.h>
#include "stm32l0xx_hal.h"
#include "User_UART.h"
#include "User_CRC.h"
#include "Global.c"
#include "Buzzer.h"
extern FLG flags;

UART_HandleTypeDef hlpuart1;
UART_HandleTypeDef huart1;
uint8_t usart_1_Rx_Data[2],lpuart_1_Rx_Data[2];

unsigned char LPUART1_CRC[2];
unsigned char LPUART1_Header[2];
unsigned char LPUART1_Footer[2];
unsigned char LPUART1_Time[6];

unsigned char UART1_CRC[2];
unsigned char UART1_Header[2];
unsigned char UART1_Footer[2];
//unsigned char UART1_Time[6];

unsigned char LPUART1_Image_Data_Buffer[16803];
unsigned char LPUART1_Image_Buffer1[144];
extern unsigned int Communication_timeout_counter;
unsigned char check_ble_command_response;
long int 	Tag_index = 0;
long int    rx_index = 0;
long int 	image_index = 0;
long int 	header_index = 0;
long int 	footer_index = 0;
long int 	crc_index = 0;
long int    usart_1_Rx_Index = 0;
long int    usart_1_pair_Index = 0;
long int    lpusart_1_Rx_Index = 0;
long int    test_Rx_Index = 0;
long int    Rx_Index = 0;
unsigned int Frame_number = 0,Previouse_frame_number = 0;
unsigned int Frame_count;

//*****************************************************************************
/**
 * @fn  void HAL_UART_RxCpltCallback(UART handle)
 * @brief Function prototypes for Receiving data on uart.
 * This function will receive specified no. of data bytes on uart 1.
 * @param *UART handle
 * @author Bhakti Deshpande
 */
//***************************************************************************************************************************

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(huart->Instance == LPUART1)
	{

		if(flags.Ble_connected_flag == 1)
		{
			uint8_t Temp_Rx_Char1;
			Temp_Rx_Char1 =  lpuart_1_Rx_Data[0];
			//			if(Temp_Rx_Char1 == START_BYTE)
			{
				LPUART1_Header[header_index] = Temp_Rx_Char1;
			}
			flags.Ckeck_communication_error = 1;
			flags.Communication_started_flag = 1; // IOS device connected.. receiving data
			if(flags.Start_to_reciv_data_flag == 1)
			{

				Communication_timeout_counter = 0;
				if (lpusart_1_Rx_Index <= 143)
				{
					LPUART1_Image_Buffer1[image_index] = Temp_Rx_Char1;   // save image data in separate buffer
					image_index++;
				}
				if( lpusart_1_Rx_Index >= 144 && lpusart_1_Rx_Index <= 145) 			 //save CRC in separate buffer
				{
					LPUART1_CRC[crc_index] = Temp_Rx_Char1;
					crc_index++;
				}
				if( lpusart_1_Rx_Index >= 146 )
				{
					LPUART1_Footer[footer_index] = Temp_Rx_Char1;		 //save footer in separate buffer
					footer_index++;
				}
			}

			if(LPUART1_Header[0] == START_BYTE && LPUART1_Header[1] == START_BYTE && flags.Start_to_reciv_data_flag == 0)// && flags.Receive_time_frame_done_flag == 1) // Check header at start of frame
			{

				lpusart_1_Rx_Index = 1;								// set receive data index to one
				image_index = 0;
				footer_index = 0;
				crc_index = 0;
				flags.Start_to_reciv_data_flag = 1; 		// Set store data frame flag
				LPUART1_Image_Buffer1[0] = START_BYTE;
				LPUART1_Image_Buffer1[1] = START_BYTE;
				image_index = image_index + 2;
				memset(LPUART1_Header,0,2);
			}
			lpusart_1_Rx_Index++;
			header_index++;
			if(header_index > 1)
			{
				header_index=0;
			}
			if(LPUART1_Footer[0] == END_BYTE && LPUART1_Footer[1] == END_BYTE)
			{
				lpusart_1_Rx_Index=0;                     		 //Clear receive data index
				image_index=0;							// Clear image index
				footer_index=0;							 //Clear footer index
				crc_index=0;							 //Clear CRC index
				flags.Start_to_reciv_data_flag = 0;
				Frame_number = LPUART1_Image_Buffer1[3];

				Frame_count = Frame_number*140;

				if(Frame_number == 119)
				{
					flags.print_display = 1;
				}

				flags.Receive_Ble_frame_flag = 1;			 //Set data frame received flag
			}

			if(Temp_Rx_Char1 == 0x2A)
			{
				//				LPUART1_Time[0] = Temp_Rx_Char1;
				memset(LPUART1_Time,0,6);
				test_Rx_Index = 0;
				flags.Start_to_reciv_time_data_flag = 1;
			}

			LPUART1_Time[test_Rx_Index] = Temp_Rx_Char1;
			test_Rx_Index++;
			if(test_Rx_Index==6)
			{
				test_Rx_Index=0;
			}
			if(Temp_Rx_Char1 == 0x23 && flags.Start_to_reciv_data_flag == 0 && flags.Start_to_reciv_time_data_flag == 1)
			{
				flags.Receive_time_frame_flag = 1;
				flags.Start_to_reciv_time_data_flag = 0;
				flags.LPUART1_Receive_time_frame_flag = 1;

			}

		}
		else //if (flags.check_command_response == 1)
		{
			uint8_t Temp_Rx_Char2;

			Temp_Rx_Char2 =  lpuart_1_Rx_Data[0];

			if(check_ble_command_response == 3 && Temp_Rx_Char2 == 'A')
			{
				Rx_Index = 0;
				flags.check_command_response2 = 1;
			}
			if(flags.check_command_response2 == 1)
			{
				LPUART1_Receive_Buffer[Rx_Index] = Temp_Rx_Char2;
				Rx_Index++;
				if(Temp_Rx_Char2 == ' ')
				{
					Rx_Index = 0;
					flags.Data_Received_Flag = 1;
					flags.check_command_response2 = 0;
				}
			}


			if(check_ble_command_response == 2 && Temp_Rx_Char2 == 'C')
			{
				Rx_Index = 0;
				flags.check_command_response = 1;
			}
			if(flags.check_command_response == 1)
			{
				LPUART1_Receive_Buffer[Rx_Index] = Temp_Rx_Char2;
				Rx_Index++;
				if(Temp_Rx_Char2 == ' ')
				{
					Rx_Index = 0;
					flags.Data_Received_Flag = 1;
					flags.check_command_response = 0;
				}
			}

			if(check_ble_command_response == 1 && Temp_Rx_Char2 == '%')
			{
				Rx_Index = 0;
				flags.check_command_response1 = 1;
			}
			if(flags.check_command_response1 == 1)
			{
				usart_1_Rx_Index = 0;
				LPUART1_Receive_Buffer[usart_1_Rx_Index] = Temp_Rx_Char2;
				Rx_Index++;
				if(Temp_Rx_Char2 == '%')
				{
					flags.Data_Received_Flag = 1;
					Rx_Index = 0;
					flags.check_command_response1 = 0;
				}

			}

			if(check_ble_command_response == 4)
			{
				LPUART1_Receive_Buffer[Rx_Index] = Temp_Rx_Char2;
				Rx_Index++;
				if(Temp_Rx_Char2 == '%' && Rx_Index>17 )
				{
					flags.Pair_data_Received_Flag = 1;
				}
			}

			if(check_ble_command_response == 5)
			{


				if(Temp_Rx_Char2 == 'B' && flags.check_command_response4 == 0)
				{
					Rx_Index = 0;
					//flags.check_command_response4 = 1;

				}

				LPUART1_Receive_Buffer[Rx_Index] = Temp_Rx_Char2;
				Rx_Index++;
				if(LPUART1_Receive_Buffer[0] == 'B' && LPUART1_Receive_Buffer[1] == 'T' && LPUART1_Receive_Buffer[2] == 'A')
				{
					flags.check_command_response4 = 1;
				}

				if(Temp_Rx_Char2 == '\r' && flags.check_command_response4 == 1)
				{
					flags.Data_Received_Flag = 1;
					Rx_Index = 0;
					check_ble_command_response = 0;
					flags.check_command_response4 = 0;
				}

			}
		}
		HAL_UART_Receive_IT(&hlpuart1, lpuart_1_Rx_Data, 1);
	}

	if(huart->Instance == USART1)
	{
		uint8_t Temp_Rx_Char2;
		Temp_Rx_Char2 =  usart_1_Rx_Data[0];
		UART1_Header[header_index] = Temp_Rx_Char2;
		if(flags.Ble_connected_flag == 0)
		{
			if(flags.Start_to_reciv_data_flag == 1)
			{
				if (rx_index <= 16802)
				{
					LPUART1_Image_Data_Buffer[image_index] = Temp_Rx_Char2;   /* save image data in separate buffer */
					image_index++;
				}
				if( rx_index >= 16803 && rx_index <= 16804) 			/* save CRC in separate buffer */
				{
					UART1_CRC[crc_index] = Temp_Rx_Char2;
					crc_index++;
				}
				if( rx_index >= 16805 )
				{
					UART1_Footer[footer_index] = Temp_Rx_Char2;		/* save footer in separate buffer */
					footer_index++;
				}
			}

			if(UART1_Header[0] == START_BYTE && UART1_Header[1] == START_BYTE && flags.Start_to_reciv_data_flag == 0)// && flags.Receive_time_frame_flag == 1) /* Check header at start of frame */
			{
				rx_index = 1;								/* set receive data index to one */
				image_index = 0;
				footer_index = 0;
				crc_index = 0;
				flags.Start_to_reciv_data_flag = 1; 		/* Set store data frame flag */
				LPUART1_Image_Data_Buffer[0] = START_BYTE;
				LPUART1_Image_Data_Buffer[1] = START_BYTE;
				image_index = image_index + 2;
				memset(UART1_Header,0,2);
			}

			rx_index++;
			header_index++;
			if(header_index > 1)
			{
				header_index=0;
			}
			if(UART1_Footer[0] == 0x0A && UART1_Footer[1] == 0x0A)
			{
				rx_index=0;                     		/* Clear receive data index */
				image_index=0;							/* Clear image index */
				footer_index=0;							/* Clear footer index */
				crc_index=0;							/* Clear CRC index */
				flags.Image_USB_Received_Flag = 1; 			/* Set data frame received flag */
				flags.Start_to_reciv_data_flag = 0;
			}
			if(Temp_Rx_Char2 == 0x2A)
			{
				//				LPUART1_Time[0] = Temp_Rx_Char1;
				memset(LPUART1_Time,0,6);
				test_Rx_Index = 0;
				flags.Start_to_reciv_time_data_flag = 1;
			}

			LPUART1_Time[test_Rx_Index] = Temp_Rx_Char2;
			test_Rx_Index++;
			if(test_Rx_Index==6)
			{
				test_Rx_Index=0;
			}
			if(Temp_Rx_Char2 == 0x23 && flags.Start_to_reciv_data_flag == 0 && flags.Start_to_reciv_time_data_flag == 1)
			{
				flags.Receive_time_frame_flag = 1;
				flags.UART1_Receive_time_frame_flag = 1;
				flags.Start_to_reciv_time_data_flag = 0;

			}
		}
		HAL_UART_Receive_IT(&huart1, usart_1_Rx_Data, 1);
	}

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//__weak
{
	/* Prevent unused argument(s) compilation warning */
	if(htim->Instance == TIM6)//---- 10mS.
	{
		/* BUZZER ALARMS */

		if(F_Buzzer_Beep1 == 1)
		{
			Execute_Buzzer_Beep1();
		}

		if(F_Buzzer_Beep2 == 1)
		{
			Execute_Buzzer_Beep2();
		}

		if(F_Buzzer_Beep3 == 1)
		{
			Execute_Buzzer_Beep3();
		}

		if(F_Buzzer_Beep4 == 1)
		{
			Execute_Buzzer_Beep4();
		}

		if(F_Buzzer_Tune1 == 1)
		{
			Execute_Buzzer_Tune1();
		}

		if(F_Buzzer_Tune2 == 1)
		{
			Execute_Buzzer_Tune2();
		}

		if(F_Buzzer_Tune3 == 1)
		{
			Execute_Buzzer_Tune3();
		}

		if(F_Buzzer_Tune4 == 1)
		{
			Execute_Buzzer_Tune4();
		}

		if(F_Buzzer_Tune5 == 1)
		{
			Execute_Buzzer_Tune5();
		}

		if(F_Buzzer_Tune6 == 1)
		{
			Execute_Buzzer_Tune6();
		}

		if(F_Buzzer_Tune7 == 1)
		{
			Execute_Buzzer_Tune7();
		}

		if(F_Buzzer_Tune8 == 1)
		{
			Execute_Buzzer_Tune8();
		}

		if(F_Buzzer_Tune9 == 1)
		{
			Execute_Buzzer_Tune9();
		}

		if(F_Buzzer_Melody1 == 1)
		{
			Execute_Buzzer_Melody1();
		}

		if(F_Buzzer_Melody2 == 1)		//add
		{
			Execute_Buzzer_Melody2();
		}



	}/* End of timer 10ms ISR */

}





