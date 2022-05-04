/*
 * User_BLE.c
 *
 *  Created on: 22-Sep-2019
 *      Author: Bhakti
 */
#include "stm32l0xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "main.h"
#include "User_UART.h"
#include "User_CRC.h"
#include "User_Application.h"
#include "Global.c"
#include "ED037TC2.h"
#include "Buzzer.h"
//#include "Screens.h"
unsigned char UART_1_Transmit_Buffer[UART_1_TX_Buffer_Size];
extern FLG flags;
extern unsigned int Communication_timeout_counter;
extern unsigned int Frame_number ;
extern char MAC_buffer[6];
UART_HandleTypeDef huart1;
uint8_t LPUART_1_Transmit_Buffer[15];
unsigned long int i,j,k;
unsigned long int y,z;
//unsigned long int pixel_value = 16764,pixel_value_end=35;
//unsigned long int pixel_value_1 = 16782,pixel_value_end_1=35;
unsigned int Hours_count = 0;
unsigned int Min_count = 0;
unsigned char Test_byte;

//*****************************************************************************
/**
 * @fn void Save_RTC_Value_Application(void)
 * @brief This function
 * 1. check CRC of time frame, convert hr and mins into hex and save the data in RAM
 * 2. send ACK/NAC frame according to CRC validation
 * @author Bhakti Deshpande
 */
//***************************************************************************************************************************

void Save_RTC_Value_Application(void)
{
	CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART1_Time,3);
	if(flags.LPUART1_Receive_time_frame_flag == 1)
	{
		if((CRC_Value.CRC_Value_char[1]== LPUART1_Time[3]) && (CRC_Value.CRC_Value_char[0]== LPUART1_Time[4]))
		{
			Hours_count = hex_to_dec(LPUART1_Time[1]);
			Min_count = hex_to_dec(LPUART1_Time[2]);

			if(Min_count>55)
			{
				Hours_count=Hours_count+1;
				Min_count=0;
			}
			LPUART_1_Transmit_Buffer[0] = '*';
			LPUART_1_Transmit_Buffer[1] = 'A';
			LPUART_1_Transmit_Buffer[2] = 'C';
			LPUART_1_Transmit_Buffer[3] = 'K';
			CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART_1_Transmit_Buffer,4);
			LPUART_1_Transmit_Buffer[4] = CRC_Value.CRC_Value_char[1];
			LPUART_1_Transmit_Buffer[5] = CRC_Value.CRC_Value_char[0];
			LPUART_1_Transmit_Buffer[6] = '#';
			LP_UART1_Transmit(LPUART_1_Transmit_Buffer,7);							/* Received CRC matched with calculated CRC */
			flags.Receive_time_frame_done_flag = 1;
		}
		else
		{

			LPUART_1_Transmit_Buffer[0] = '*';
			LPUART_1_Transmit_Buffer[1] = 'N';
			LPUART_1_Transmit_Buffer[2] = 'A';
			LPUART_1_Transmit_Buffer[3] = 'K';
			CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART_1_Transmit_Buffer,4);
			LPUART_1_Transmit_Buffer[4] = CRC_Value.CRC_Value_char[1];
			LPUART_1_Transmit_Buffer[5] = CRC_Value.CRC_Value_char[0];
			LPUART_1_Transmit_Buffer[6] = '#';
			LP_UART1_Transmit(LPUART_1_Transmit_Buffer,7);							/* Received CRC doesn't  with calculated CRC */
			flags.Shutdown_MCU_mosfet = 1;
		}


	}
	else if(flags. UART1_Receive_time_frame_flag == 1)
	{
		//BLEControl_L;
		/* Calculate CRC of 16803 bytes in UART_1_Image Buffer */
		if((CRC_Value.CRC_Value_char[1]== LPUART1_Time[3]) && (CRC_Value.CRC_Value_char[0]== LPUART1_Time[4]))
		{
			Hours_count = hex_to_dec(LPUART1_Time[1]);
			Min_count = hex_to_dec(LPUART1_Time[2]);
			if(Min_count>55)
			{
				Hours_count=Hours_count+1;
				Min_count=0;
			}
			UART_1_Transmit_Buffer[0] = '*';
			UART_1_Transmit_Buffer[1] = 'A';
			UART_1_Transmit_Buffer[2] = 'C';
			UART_1_Transmit_Buffer[3] = 'K';
			CRC_Value.CRC_Value_int=Calculate_Block_CRC16(UART_1_Transmit_Buffer,4);
			UART_1_Transmit_Buffer[4] = CRC_Value.CRC_Value_char[1];
			UART_1_Transmit_Buffer[5] = CRC_Value.CRC_Value_char[0];
			UART_1_Transmit_Buffer[6] = '#';
			UART1_Transmit(UART_1_Transmit_Buffer,7);							/* Received CRC matched with calculated CRC */
			flags.Receive_time_frame_done_flag = 0;
		}
		else
		{

			UART_1_Transmit_Buffer[0] = '*';
			UART_1_Transmit_Buffer[1] = 'N';
			UART_1_Transmit_Buffer[2] = 'A';
			UART_1_Transmit_Buffer[3] = 'K';
			CRC_Value.CRC_Value_int=Calculate_Block_CRC16(UART_1_Transmit_Buffer,4);
			UART_1_Transmit_Buffer[4] = CRC_Value.CRC_Value_char[1];
			UART_1_Transmit_Buffer[5] = CRC_Value.CRC_Value_char[0];
			UART_1_Transmit_Buffer[6] = '#';
			UART1_Transmit(UART_1_Transmit_Buffer,7);							/* Received CRC doesn't  with calculated CRC */
			flags.Shutdown_MCU_mosfet = 1;
		}
	}
	/* Calculate CRC of 16803 bytes in UART_1_Image Buffer */

}
//*****************************************************************************
/**
 * @fn void Display_Application()
 * @brief This function handles display functionality according to received image, check CRC and send response frames
 * according to error type.
 * @author Bhakti Deshpande
 */
//***************************************************************************************************************************


void Display_Application(void)
{

	CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART1_Image_Buffer1,144);

	/* Calculate CRC of 16803 bytes in UART_1_Image Buffer */
	if((CRC_Value.CRC_Value_char[1]== LPUART1_CRC[0]) && (CRC_Value.CRC_Value_char[0]== LPUART1_CRC[1]))
	{
		flags.CRC_Verified_Flag = 1; 							/* Received CRC matched with calculated CRC */
	}
	else
	{
		flags.CRC_Verified_Flag = 0;  							/* Received CRC doesn't  with calculated CRC */
	}
	if(flags.CRC_Verified_Flag == 1)
	{

		memcpy((LPUART1_Image_Data_Buffer + Frame_count),LPUART1_Image_Buffer1+4,140);

		LPUART_1_Transmit_Buffer[0] = START_BYTE;
		LPUART_1_Transmit_Buffer[1] = START_BYTE;
		strcat(&LPUART_1_Transmit_Buffer,MAC_buffer);
		LPUART_1_Transmit_Buffer[8] = 'A';
		LPUART_1_Transmit_Buffer[9] = 'C';
		LPUART_1_Transmit_Buffer[10] = 'K';
		CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART_1_Transmit_Buffer,11);
		LPUART_1_Transmit_Buffer[11] = CRC_Value.CRC_Value_char[1];
		LPUART_1_Transmit_Buffer[12] = CRC_Value.CRC_Value_char[0];
		LPUART_1_Transmit_Buffer[13] = END_BYTE;
		LPUART_1_Transmit_Buffer[14] = END_BYTE;
		LP_UART1_Transmit(LPUART_1_Transmit_Buffer,15);	/* Send response frame with display error */
		memset(LPUART1_Image_Buffer1,0,144);
		memset(LPUART1_Footer,0,2);
		memset(LPUART1_CRC,0,2);
		memset(LPUART_1_Transmit_Buffer,0,15);

		if(flags.print_display == 1)
		{
			HAL_GPIO_WritePin(LCD_Mosfet_GPIO_Port,LCD_Mosfet_Pin,0);
			flags.Ckeck_communication_error = 0;
			if(EPD_Init()== SUCCESS)
			{
				EPD_Display_KW(LPUART1_Image_Data_Buffer,16800);
				//Eink_Partial_Display_Update(232,0,48,40,Screen_battery5);
			}
			if(flags.Busy_pin_error_flag == 1) 				    /* Check for display update error error E02*/
			{
				LPUART_1_Transmit_Buffer[0] = START_BYTE;
				LPUART_1_Transmit_Buffer[1] = START_BYTE;
				strcat(LPUART_1_Transmit_Buffer,MAC_buffer);
				LPUART_1_Transmit_Buffer[8] = 'E';
				LPUART_1_Transmit_Buffer[9] = '0';
				LPUART_1_Transmit_Buffer[10] = '2';
				CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART_1_Transmit_Buffer,11);
				LPUART_1_Transmit_Buffer[11] = CRC_Value.CRC_Value_char[1];
				LPUART_1_Transmit_Buffer[12] = CRC_Value.CRC_Value_char[0];
				LPUART_1_Transmit_Buffer[13] = END_BYTE;
				LPUART_1_Transmit_Buffer[14] = END_BYTE;
				LP_UART1_Transmit(LPUART_1_Transmit_Buffer,15);	/* Send response frame with display error */
				HAL_Delay(2000);
				memset(LPUART1_Image_Buffer1,0,144);
				memset(LPUART1_Footer,0,2);
				memset(LPUART1_CRC,0,2);
				memset(LPUART_1_Transmit_Buffer,0,15);
#if(D_DEBUG)
				uint8_t test_1[30]="E02 - Display Not connected\r\n";
				UART1_Transmit(test_1,27);
#endif

				flags.Busy_pin_error_flag = 0;				/* Reset display update error flag */
				//MCU_Mosfet2_H;

				flags.Shutdown_MCU_mosfet = 1;

			}
			else
			{
				Initiate_Buzzer_Beep1();					//beep 2
				Execute_Buzzer_Beep1();
				Vibrator_Motor_H;
				flags.Start_vibrator_motor_flag = 1;
				LPUART_1_Transmit_Buffer[0] = START_BYTE;
				LPUART_1_Transmit_Buffer[1] = START_BYTE;
				strcat(LPUART_1_Transmit_Buffer,MAC_buffer);
				LPUART_1_Transmit_Buffer[8] = 'S';
				LPUART_1_Transmit_Buffer[9] = 'U';
				LPUART_1_Transmit_Buffer[10] = 'C';
				CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART_1_Transmit_Buffer,11);
				LPUART_1_Transmit_Buffer[11] = CRC_Value.CRC_Value_char[1];
				LPUART_1_Transmit_Buffer[12] = CRC_Value.CRC_Value_char[0];
				LPUART_1_Transmit_Buffer[13] = END_BYTE;
				LPUART_1_Transmit_Buffer[14] = END_BYTE;
				LP_UART1_Transmit(LPUART_1_Transmit_Buffer,15);	/* Send response frame with success message */
				//				UART1_Transmit(LPUART_1_Transmit_Buffer,15);
				memset(LPUART1_Image_Buffer1,0,144);
				memset(LPUART1_Footer,0,2);
				memset(LPUART1_CRC,0,2);
				memset(LPUART_1_Transmit_Buffer,0,15);
#if(D_DEBUG)
				uint8_t test_1[30]="Display updated Successfully\r\n";
				UART1_Transmit(test_1,30);
#endif
				HAL_Delay(1000);
			}

			memset(LPUART_1_Transmit_Buffer,0,sizeof(LPUART_1_Transmit_Buffer));
			memset(LPUART1_Image_Buffer1,0,sizeof(LPUART1_Image_Buffer1));
			memset(LPUART1_Footer,0,2);
			flags.Communication_started_flag = 0;
			Communication_timeout_counter = 0;
			if(Hours_count == 0 && Min_count == 0)
			{
				flags.Shutdown_MCU_mosfet = 1;

			}
			else
			{
				//				Send_Command_State = 2;
				//				flags.configure_ble_beacons = 1;
				//				flags.Ble_connected_flag = 0;
				//				Ble_Mosfet_L;
				//				BLEControl_L;
				Send_Command_State = 2;
				flags.configure_ble_beacons = 1;
				flags.Ble_connected_flag = 0;
				flags.Communication_error_flag = 0;
				Ble_Mosfet_L;
				BLEControl_L;
				flags.Start_Ble_beacons = 1;
			}
			flags.print_display = 0;
		}

		flags.CRC_Verified_Flag = 0;

	}
	else if(flags.CRC_Verified_Flag == 0)
	{
//		Initiate_Buzzer_Beep2();					//tune - low, high, low, high - 2
//		Execute_Buzzer_Beep2();
//		Vibrator_Motor_H;
//		flags.Start_vibrator_motor_flag = 1;
		LPUART_1_Transmit_Buffer[0] = START_BYTE;
		LPUART_1_Transmit_Buffer[1] = START_BYTE;
		strcat(LPUART_1_Transmit_Buffer,MAC_buffer);
		LPUART_1_Transmit_Buffer[8] = 'E';
		LPUART_1_Transmit_Buffer[9] = '0';
		LPUART_1_Transmit_Buffer[10] = '1';
		CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART_1_Transmit_Buffer,11);
		LPUART_1_Transmit_Buffer[11] = CRC_Value.CRC_Value_char[1];
		LPUART_1_Transmit_Buffer[12] = CRC_Value.CRC_Value_char[0];
		LPUART_1_Transmit_Buffer[13] = END_BYTE;
		LPUART_1_Transmit_Buffer[14] = END_BYTE;
		LP_UART1_Transmit(LPUART_1_Transmit_Buffer,15);	/* Send response frame with display error */
#if(D_DEBUG)
		uint8_t test_1[30]="E01:CRC Miss match Error\r\n";
		UART1_Transmit(test_1,26);
#endif
		HAL_Delay(2000);
		memset(LPUART1_Image_Buffer1,0,144);
		memset(LPUART1_Footer,0,2);
		memset(LPUART1_CRC,0,2);
		memset(LPUART_1_Transmit_Buffer,0,sizeof(LPUART_1_Transmit_Buffer));
		memset(LPUART1_Image_Buffer1,0,sizeof(LPUART1_Image_Buffer1));
		memset(LPUART1_Footer,0,2);
		memset(LPUART_1_Transmit_Buffer,0,15);
		flags.Shutdown_MCU_mosfet = 1;
	}
}


//*****************************************************************************
/**
 * @fn void Ckeck_communication_error(void)
 * @brief This function
 * 1. check if next data frames are receiving without fail and also finds if communication stopped due to any reason
 * there is 10 sec timer between two consecutive frames, if next frame didn't received in 10 secs communication error occurs
 * and MCU mosfet will be made off to save battery
 * @author Bhakti Deshpande
 */
//***************************************************************************************************************************

void Ckeck_communication_error(void)
{

	if(flags.Communication_error_flag == 1 && (Frame_number != Frame_number+1))//Previouse_frame_number || Frame_number == 0 ) )
	{

#if(D_DEBUG)
		{
			uint8_t Error_string[27] = "E03 - Communication Error\r\n";
			HAL_UART_Transmit(&huart1,Error_string,27,255);
		}
#endif
		Vibrator_Motor_H;
		flags.Start_vibrator_motor_flag = 1;
		Initiate_Buzzer_Beep2();					//tune - low, high, low, high - 2
		Execute_Buzzer_Beep2();
		LPUART_1_Transmit_Buffer[0] = START_BYTE;
		LPUART_1_Transmit_Buffer[1] = START_BYTE;
		strcat(LPUART_1_Transmit_Buffer,MAC_buffer);
		LPUART_1_Transmit_Buffer[8] = 'E';
		LPUART_1_Transmit_Buffer[9] = '0';
		LPUART_1_Transmit_Buffer[10] = '3';
		CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART_1_Transmit_Buffer,11);
		LPUART_1_Transmit_Buffer[11] = CRC_Value.CRC_Value_char[1];
		LPUART_1_Transmit_Buffer[12] = CRC_Value.CRC_Value_char[0];
		LPUART_1_Transmit_Buffer[13] = END_BYTE;
		LPUART_1_Transmit_Buffer[14] = END_BYTE;
		LP_UART1_Transmit(LPUART_1_Transmit_Buffer,15);	/* Send response frame with display error */
		memset(LPUART1_Image_Buffer1,0,144);
		memset(LPUART1_Footer,0,2);
		memset(LPUART1_CRC,0,2);
		memset(LPUART_1_Transmit_Buffer,0,sizeof(LPUART_1_Transmit_Buffer));
		memset(LPUART1_Image_Buffer1,0,sizeof(LPUART1_Image_Buffer1));
		memset(LPUART1_Footer,0,2);
		memset(LPUART_1_Transmit_Buffer,0,15);
		flags.Ckeck_communication_error = 0;
		HAL_Delay(2000);
		//MCU_Mosfet2_H;
		flags.Shutdown_MCU_mosfet = 1;
	}

	//	Previouse_frame_number = Frame_number;
}



void UART1_Display_Application(void)
{

	CRC_Value.CRC_Value_int=Calculate_Block_CRC16(LPUART1_Image_Data_Buffer,16803);
	/* Calculate CRC of 16803 bytes in UART_1_Image Buffer */
	if((CRC_Value.CRC_Value_char[1]== UART1_CRC[0]) && (CRC_Value.CRC_Value_char[0]== UART1_CRC[1]))
	{
		flags.CRC_Verified_Flag = 1; 							/* Received CRC matched with calculated CRC */
	}
	else
	{
		flags.CRC_Verified_Flag = 0;  							/* Received CRC doesn't  with calculated CRC */
	}

	if(flags.CRC_Verified_Flag == 1)
	{
		HAL_GPIO_WritePin(LCD_Mosfet_GPIO_Port,LCD_Mosfet_Pin,0);
		flags.Ckeck_communication_error = 0;
		if(EPD_Init()== SUCCESS)
		{
			EPD_Display_KW(LPUART1_Image_Data_Buffer,16800);
			//Eink_Partial_Display_Update(232,0,48,40,Screen_battery5);
		}
		if(flags.Busy_pin_error_flag == 1) 				    /* Check for display update error error E02*/
		{
			UART_1_Transmit_Buffer[0] = START_BYTE;
			UART_1_Transmit_Buffer[1] = START_BYTE;
			UART_1_Transmit_Buffer[2] = 'E';
			UART_1_Transmit_Buffer[3] = '0';
			UART_1_Transmit_Buffer[4] = '2';
			CRC_Value.CRC_Value_int=Calculate_Block_CRC16(UART_1_Transmit_Buffer,5);
			UART_1_Transmit_Buffer[5] = CRC_Value.CRC_Value_char[1];
			UART_1_Transmit_Buffer[6] = CRC_Value.CRC_Value_char[0];
			UART_1_Transmit_Buffer[7] = END_BYTE;
			UART_1_Transmit_Buffer[8] = END_BYTE;
			UART1_Transmit(UART_1_Transmit_Buffer,9);	/* Send response frame with display error */
			flags.Busy_pin_error_flag = 0;				/* Reset display update error flag */
			flags.Shutdown_MCU_mosfet = 1;
		}
		else
		{

			flags.Image_USB_Received_Flag = 0;
			Initiate_Buzzer_Beep1();					//beep 2
			Execute_Buzzer_Beep1();
			Vibrator_Motor_H;

			flags.Start_vibrator_motor_flag = 1;
			UART_1_Transmit_Buffer[0] = START_BYTE;
			UART_1_Transmit_Buffer[1] = START_BYTE;
			UART_1_Transmit_Buffer[2] = 'A';
			UART_1_Transmit_Buffer[3] = 'C';
			UART_1_Transmit_Buffer[4] = 'K';
			CRC_Value.CRC_Value_int = Calculate_Block_CRC16(UART_1_Transmit_Buffer,5);
			UART_1_Transmit_Buffer[5] = CRC_Value.CRC_Value_char[1];
			UART_1_Transmit_Buffer[6] = CRC_Value.CRC_Value_char[0];
			UART_1_Transmit_Buffer[7] = END_BYTE;
			UART_1_Transmit_Buffer[8] = END_BYTE;
			UART1_Transmit(UART_1_Transmit_Buffer,9);	/* Send response frame with Acknowledgment */
			j=3;
			for(i=0;i<16800;i++)
			{
				LPUART1_Image_Data_Buffer[i] = 	LPUART1_Image_Data_Buffer[i+j];
			}

			memset(UART_1_Transmit_Buffer,0,sizeof(UART_1_Transmit_Buffer));
			memset(UART1_Footer,0,2);

			if(Hours_count == 0 && Min_count == 0)
			{
				flags.Shutdown_MCU_mosfet = 1;

			}
			else
			{

				Send_Command_State = 2;
				flags.configure_ble_beacons = 1;
				flags.Ble_connected_flag = 0;
				flags.Communication_error_flag = 0;
				flags.Start_Ble_beacons = 1;
				flags.Tag_printing_done_flag=1;

			}

		}
	}
	else
	{
		UART_1_Transmit_Buffer[0] = START_BYTE;
		UART_1_Transmit_Buffer[1] = START_BYTE;
		UART_1_Transmit_Buffer[2] = 'E';
		UART_1_Transmit_Buffer[3] = '0';
		UART_1_Transmit_Buffer[4] = '1';
		CRC_Value.CRC_Value_int=Calculate_Block_CRC16(UART_1_Transmit_Buffer,3);
		UART_1_Transmit_Buffer[5] = CRC_Value.CRC_Value_char[1];
		UART_1_Transmit_Buffer[6] = CRC_Value.CRC_Value_char[0];
		UART_1_Transmit_Buffer[7] = END_BYTE;
		UART_1_Transmit_Buffer[8] = END_BYTE;

		UART1_Transmit(UART_1_Transmit_Buffer,9);	/* Send response frame with CRC miss match error */
		memset(UART_1_Transmit_Buffer,0,sizeof(UART_1_Transmit_Buffer));
		memset(UART1_Footer,0,2);
		flags.Shutdown_MCU_mosfet = 1;
	}

}


