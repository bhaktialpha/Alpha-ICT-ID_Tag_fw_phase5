/*
 * User_Beacon.c
 *
 *  Created on: Jan 29, 2020
 *      Author: bhakti.deshpande
 */

#include "string.h"
#include "stdio.h"
#include "User_beacon.h"
#include "User_UART.h"
#include "ED037TC2.h"
#include "main.h"
#include "Global.h"
extern unsigned char check_ble_command_response;
uint8_t Response_string_1[13] = "Response OK\r\n";
uint8_t Response_string_2[19] = "Response NOT OK\r\n";
char MAC_buffer[6];
extern FLG flags;
extern unsigned int Ble_Connect_Counter_Response_Time;
unsigned char Send_Command_State = 2;
unsigned int temp_val;
//char BLE_Rename_Command[25] =  "S-,ALPHA_ID_TAG\r\n";
char content[12];
unsigned char Test_123[11];
char Test_1234[12];// = "SP,";
unsigned char Send_MAC_ADD[28];
char MAC_ADD[12];
extern int hex_to_dec(unsigned int hexadecimal_number);
extern int passkey_Sum(int n);
int jj=1,kk=0,passkey_1,passkey_2,passkey_3,passkey_4,passkey_5,passkey_6;
/**
 * @brief  Check device connection and disconnection response only
 * @param  None
 * @retval None
 */
void Check_Response_1( uint8_t* Rx_strng, int size)
{
	if((strstr(LPUART1_Receive_Buffer,Rx_strng)) != 0)
	{
		flags.Response_OK_flag = 1;
	}
	else
	{
		flags.Response_OK_flag = 0;
	}

}

/**
 * @brief  Check bluetooth command's response
 * @param  None
 * @retval None
 */
void Check_Get_Response(uint8_t* Rx_strng, unsigned int size)
{
#if(D_DEBUG)

	UART1_Transmit(LPUART1_Receive_Buffer, 10);
#endif

	if((strstr(LPUART1_Receive_Buffer,Rx_strng)) != 0)
	{
		flags.Response_OK_flag = 1;
#if(D_DEBUG)

		UART1_Transmit(Response_string_1,13);
#endif
	}
	else
	{
		flags.Response_OK_flag = 0;
#if(D_DEBUG)

		UART1_Transmit(Response_string_2,19);
#endif

	}

}




/**
 * @brief  send bluetooth initialization commands
 * @param  None
 * @retval None
 */
void Send_BLE_Commands(void)
{
	switch(Send_Command_State)
	{
	case 0:
		check_ble_command_response = 1;
		LP_UART1_Transmit(BM71_Command_0,5);
#if(D_DEBUG)

		UART1_Transmit(BM71_Command_0,5);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 1:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			//			Check_Get_Response(BLE_Response_4,6);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;
				if(Send_cmd_Error_Cnt > 5)
				{
					flags.No_responce_Shutdown_MCU_mosfet = 1;
					Send_Command_State = 0;
				}
#if(D_DEBUG)
				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
			if(Send_cmd_Error_Cnt > 5)
			{
#if(D_DEBUG)
				uint8_t test_string[56] = "No response from Bluetooth..Please check battery voltage\r\n" ;
				UART1_Transmit(test_string,56);
#endif
				Send_Command_State = 0;
				flags.No_responce_Shutdown_MCU_mosfet = 1;
			}
#if(D_DEBUG)

			UART1_Transmit(Response_string_2,19);
#endif
		}
		break;
	case 2:
		check_ble_command_response = 2;
		memset(LPUART1_Receive_Buffer,0,sizeof(LPUART1_Receive_Buffer));
		LP_UART1_Transmit(BM71_Command_1,3);
		HAL_Delay(100);
#if(D_DEBUG)

		UART1_Transmit(BM71_Command_1,3);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;

		break;
	case 3:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_0,5);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;
				if(Send_cmd_Error_Cnt > 2)
				{
					Send_cmd_Error_Cnt = 0;
					Send_Command_State = 0;
				}
#if(D_DEBUG)

				UART1_Transmit(Response_string_2,19);

#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;

			Send_cmd_Error_Cnt++;

			if(Send_cmd_Error_Cnt > 5)
			{
				Send_Command_State = 0;
				Send_cmd_Error_Cnt = 0;
			}
#if(D_DEBUG)

			UART1_Transmit(Response_string_2,19);

#endif
		}
		break;
	case 4:
			check_ble_command_response = 3;
			LP_UART1_Transmit(BM71_Command_6,5);
	#if(D_DEBUG)
			UART1_Transmit(BM71_Command_6,5);
	#endif

			flags.Start_Command_Response_time = 1;
			Counter_Response_Time = 0;
			Send_Command_State++;
			break;
		case 5:

			if(flags.Data_Received_Flag == 1)
			{
				flags.Data_Received_Flag = 0;
				flags.Start_Command_Response_time = 0;
				Counter_Response_Time = 0;
				Check_Get_Response(BLE_Response_1,9);
				if(flags.Response_OK_flag == 1)
				{
	#if(D_DEBUG)
					UART1_Transmit(Response_string_1,13);
	#endif
					Send_Command_State ++;
					Send_cmd_Error_Cnt = 0;
				}
				else
				{
					Send_Command_State--;
					Send_cmd_Error_Cnt++;

					if(Send_cmd_Error_Cnt > 2)
					{
						Send_Command_State = 0;
					}
	#if(D_DEBUG)

					UART1_Transmit(Response_string_2,19);

	#endif
				}
			}
			else if(flags.Command_Response_timeout == 1)
			{
				flags.Command_Response_timeout = 0;
				Counter_Response_Time = 0;
				Send_Command_State--;
				Send_cmd_Error_Cnt++;
	#if(D_DEBUG)

				UART1_Transmit(Response_string_2,19);
	#endif
				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
			}
			break;
	case 6:
		check_ble_command_response = 3;
		LP_UART1_Transmit(BM71_Command_2,6);
#if(D_DEBUG)
		UART1_Transmit(BM71_Command_2,6);
#endif
		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 7:

		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 2)
				{
					Send_cmd_Error_Cnt = 0;
					Send_Command_State = 0;
				}
#if(D_DEBUG)


				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG)

			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_cmd_Error_Cnt = 0;
				Send_Command_State = 0;
			}
		}
		break;
	case 8:
		check_ble_command_response = 5;
		LP_UART1_Transmit(BM71_Command_3,3);
		if(D_DEBUG)
		{
			UART1_Transmit(BM71_Command_3,3);
		}
	//	HAL_Delay(1000);
		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 9:

		if(flags.Data_Received_Flag == 1)
		{

			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_6,5);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_cmd_Error_Cnt = 0;
				Send_Command_State++;
				int k=0;
				for(k=0; k<12; k++)
				{
					content[k] = LPUART1_Receive_Buffer[4+k];
				}
				for(k=0; k<12; k++)
				{
					MAC_ADD[k] = LPUART1_Receive_Buffer[4+k];
				}
				strcpy(Test_1234,content);

				for(kk=0; kk<12; kk++)
				{
					if(Test_1234[jj] > 0x40)
					{
						Test_1234[jj]=Test_1234[jj]-0x7;
					}
					Test_123[kk+3] = Test_1234[jj];
					jj=jj+2;
				}

				if(content[0] <= 0x39) content[0] = content[0] - 0x30;
				else
				{
					content[0] = content[0] - 0x57;
					content[0] = content[0] & 0x0F;
				}

				if(content[1] <= 0x39) content[1] = content[1] - 0x30;
				else
				{
					content[1] = content[1] - 0x57;
					content[1] = content[1] & 0x0F;
				}

				if(content[2] <= 0x39) content[2] = content[2] - 0x30;
				else
				{
					content[2] = content[2] - 0x57;
					content[2] = content[2] & 0x0F;
				}

				if(content[3] <= 0x39) content[3] = content[3] - 0x30;
				else
				{
					content[3] = content[3] - 0x57;
					content[3] = content[3] & 0x0F;
				}

				if(content[4] <= 0x39)
				{
					content[4] = content[4] - 0x30;
					content[4] = content[4] & 0x0F;
				}
				else
				{
					content[4] = content[4] - 0x57;
					content[4] = content[4] & 0x0F;
				}

				if(content[5] <= 0x39) content[5] = content[5] - 0x30;
				else
				{
					content[5] = content[5] - 0x57;
					content[5] = content[5] & 0x0F;
				}

				if(content[6] <= 0x39) content[6] = content[6] - 0x30;
				else
				{
					content[6] = content[6] - 0x57;
					content[6] = content[6] & 0x0F;
				}

				if(content[7] <= 0x39) content[7] = content[7] - 0x30;
				else
				{
					content[7] = content[7] - 0x57;
					content[7] = content[7] & 0x0F;
				}

				if(content[8] <= 0x39) content[8] = content[8] - 0x30;
				else
				{
					content[8] = content[8] - 0x57;
					content[8] = content[8] & 0x0F;
				}

				if(content[9] <= 0x39) content[9] = content[9] - 0x30;
				else {
					content[9] = content[9] - 0x57;
					content[9] = content[9] & 0x0F;
				}

				if(content[10] <= 0x39) content[10] = content[10] - 0x30;
				else
				{
					content[10] = content[10] - 0x57;
					content[10] = content[10] & 0x0F;
				}

				if(content[11] <= 0x39) content[11] = content[11] - 0x30;
				else
				{
					content[11] = content[11] - 0x57;
					content[11] = content[11] & 0x0F;
				}

				Test_123[0] = 'S';
				Test_123[1] = 'P';
				Test_123[2] = ',';
				Test_123[9] = '\r';
				Test_123[10] = '\n';


				MAC_buffer[0] = (content[0] << 4)| content[1];

				MAC_buffer[1] = (content[2]<< 4)| content[3];

				MAC_buffer[2] = (content[4]<< 4)| content[5];

				MAC_buffer[3] = (content[6]<< 4)| content[7];

				MAC_buffer[4] = (content[8]<< 4)| content[9];

				MAC_buffer[5] = (content[10]<< 4)| content[11];


				passkey_1 = hex_to_dec(MAC_buffer[0]);
				passkey_2 = hex_to_dec(MAC_buffer[1]);
				passkey_3 = hex_to_dec(MAC_buffer[2]);
				passkey_4 = hex_to_dec(MAC_buffer[3]);
				passkey_5 = hex_to_dec(MAC_buffer[4]);
				passkey_6 = hex_to_dec(MAC_buffer[5]);
				//				Test_123[3] = passkey_Sum(MAC_buffer[0])+0x30;
				//						Test_123[4] = passkey_Sum(MAC_buffer[1])+0x30;
				//						Test_123[5] = passkey_Sum(MAC_buffer[2])+0x30;
				//						Test_123[6] = passkey_Sum(MAC_buffer[3])+0x30;
				//						Test_123[7] = passkey_Sum(MAC_buffer[4])+0x30;
				//						Test_123[8] = passkey_Sum(MAC_buffer[5])+0x30;

				Test_123[3] = passkey_Sum(MAC_buffer[0])+0x30;
				Test_123[4] = passkey_Sum(MAC_buffer[1])+0x30;
				Test_123[5] = passkey_Sum(MAC_buffer[2])+0x30;
				Test_123[6] = passkey_Sum(MAC_buffer[3])+0x30;
				Test_123[7] = passkey_Sum(MAC_buffer[4])+0x30;
				Test_123[8] = passkey_Sum(MAC_buffer[5])+0x30;

				if(Send_cmd_Error_Cnt > 5)
				{
					Send_Command_State = 0;
				}
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;
				if(Send_cmd_Error_Cnt > 2)
				{
					Send_cmd_Error_Cnt = 0;
					Send_Command_State = 0;
				}
				if(D_DEBUG)
				{
					UART1_Transmit(Response_string_2,19);
				}
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_Command_State = 0;
			}
			if(D_DEBUG)
			{
				UART1_Transmit(Response_string_2,19);
			}
		}
		break;

	case 10:
		check_ble_command_response = 3;
		LP_UART1_Transmit(BM71_Command_4,17);
#if(D_DEBUG)

		UART1_Transmit(BM71_Command_4,17);
#endif
		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 11:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State ++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG)
				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG)
			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 3)
			{
				Send_Command_State = 0;
			}
		}
		break;
	case 12:
		check_ble_command_response = 1;
		LP_UART1_Transmit(BM71_Command_0,5);
#if(D_DEBUG)
		UART1_Transmit(BM71_Command_0,5);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 13:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			//Check_Get_Response(BLE_Response[3],6);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State++;
				Send_cmd_Error_Cnt = 0;

			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

#if(D_DEBUG)

				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_Command_State = 0;
			}
#if(D_DEBUG)
			UART1_Transmit(Response_string_2,19);
#endif
		}
		break;

	case 14:
		check_ble_command_response = 2;
		LP_UART1_Transmit(BM71_Command_1,3);

#if(D_DEBUG)
		UART1_Transmit(BM71_Command_1,3);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 15:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_0,5);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State ++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;
				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG)

				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;

			if(Send_cmd_Error_Cnt > 3)
			{
				Send_Command_State = 0;
			}
#if(D_DEBUG)

			UART1_Transmit(Response_string_2,19);
#endif
		}
		break;
		/*case 14:
		LP_UART1_Transmit(Test_123,11);
#if(D_DEBUG)
		UART1_Transmit(Test_123,11);
#endif
		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;

	case 15:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG)
				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG)
			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_Command_State = 0;
			}
		}
		break;*/

//	case 14:
//		check_ble_command_response = 3;
//		LP_UART1_Transmit(BM71_Command_7,6);
//#if(D_DEBUG)
//		UART1_Transmit(BM71_Command_7,6);
//#endif
//		flags.Start_Command_Response_time = 1;
//		Counter_Response_Time = 0;
//		Send_Command_State++;
//		break;
//	case 15:
//		if(flags.Data_Received_Flag == 1)
//		{
//			flags.Data_Received_Flag = 0;
//			flags.Start_Command_Response_time = 0;
//			Counter_Response_Time = 0;
//			Check_Get_Response(BLE_Response_1,9);
//			if(flags.Response_OK_flag == 1)
//			{
//#if(D_DEBUG)
//				UART1_Transmit(Response_string_1,13);
//#endif
//				Send_Command_State++;
//				Send_cmd_Error_Cnt = 0;
//			}
//			else
//			{
//				Send_Command_State--;
//				Send_cmd_Error_Cnt++;
//
//				if(Send_cmd_Error_Cnt > 2)
//				{
//					Send_Command_State = 0;
//				}
//#if(D_DEBUG)
//				UART1_Transmit(Response_string_2,19);
//#endif
//			}
//		}
//		else if(flags.Command_Response_timeout == 1)
//		{
//			flags.Command_Response_timeout = 0;
//			Counter_Response_Time = 0;
//			Send_Command_State--;
//			Send_cmd_Error_Cnt++;
//#if(D_DEBUG)
//			UART1_Transmit(Response_string_2,19);
//#endif
//			if(Send_cmd_Error_Cnt > 2)
//			{
//				Send_Command_State = 0;
//			}
//		}
//		break;
	case 16:
		check_ble_command_response = 3;
		LP_UART1_Transmit(BM71_Command_5,5);
#if(D_DEBUG)
		UART1_Transmit(BM71_Command_5,5);
#endif
		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 17:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_cmd_Error_Cnt = 0;
				Ble_Connect_Counter_Response_Time = 0;
				flags.Start_Ble_Connect_timeout_flag = 1;
				BLEControl_H;
				Send_Command_State++;


#if(D_DEBUG)
				uint8_t Debug_string_waiting[25] = "Waiting for timeout....\r\n";
				UART1_Transmit(Debug_string_waiting,25);
#endif
				check_ble_command_response = 4;
				flags.Initialize_ble_flag = 0;
				flags.Start_Led_blinking = 1;

			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 5)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG)
				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG)
			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 5)
			{
				Send_Command_State = 0;
			}
		}
		break;
	}
}


/**
 * @brief  Check device connection and disconnection according to received response
 * @param  None
 * @retval None
 */

void Check_Device_Connection()
{
	Check_Response_1(BLE_Response_4,6);
	if(flags.Response_OK_flag == 1)
	{
		flags.Data_Received_Flag = 1;
		flags.F_Device_Data_Received = 0;
	}
	else
	{
		Check_Response_1(BLE_Response_2,12);
		if(flags.Response_OK_flag == 1)
		{
#if(D_DEBUG)
			uint8_t Device_disconnect_debug_string[28] = "Bluetooth disconnected\r\n";
			UART1_Transmit(Device_disconnect_debug_string,28);
#endif
			if(flags.Communication_started_flag == 1)
			{
				//				flags.No_responce_Shutdown_MCU_mosfet = 1;
				flags.Disconnect_ble_flag = 1;
			}
			Send_cmd_Error_Cnt = 0;
			flags.F_Device_Data_Received = 0;
			flags.Pair_data_Received_Flag = 0;
			//BLE_CONNECTED=0;
		}
		else
		{
			Check_Response_1(BLE_Response_3,6);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG)
				uint8_t Device_connect_debug_string[22] = "Bluetooth Paired \r\n";

				UART1_Transmit(Device_connect_debug_string,19);
				//	HAL_Delay(1000);
#endif
				Ble_Connect_Counter_Response_Time = 0;
				flags.Start_Ble_Connect_timeout_flag = 0;
				BLEControl_L;
				Send_cmd_Error_Cnt = 0;
				flags.Ble_connected_flag = 1;
				flags.Initialize_ble_flag = 0;
				flags.F_Device_Data_Received = 0;
				Ble_Connect_Counter_Response_Time = 0;
				flags.Pair_data_Received_Flag = 0;
				flags.F_Device_Data_Received = 0;
				//BLE_CONNECTED=1;
			}
			else
			{

				Check_Response_1(BLE_Response_5,8);
				if(flags.Response_OK_flag == 1)
				{
#if(D_DEBUG)
					uint8_t Device_connect_debug_string[22] = "Bluetooth Connected \r\n";

					UART1_Transmit(Device_connect_debug_string,22);
					//	HAL_Delay(1000);
#endif
					Ble_Connect_Counter_Response_Time = 0;
					flags.Start_Ble_Connect_timeout_flag = 0;
					BLEControl_L;
					Send_cmd_Error_Cnt = 0;
					flags.Ble_connected_flag = 1;
					flags.Initialize_ble_flag = 0;
					flags.F_Device_Data_Received = 0;
					flags.Start_Ble_Connect_timeout_flag = 0;
					Ble_Connect_Counter_Response_Time = 0;
					flags.Pair_data_Received_Flag = 0;
					flags.F_Device_Data_Received = 0;
					//BLE_CONNECTED=1;
				}
				else
				{
					Send_cmd_Error_Cnt = 0;
					//				flags.Ble_connected_flag = 1;
					flags.F_Device_Data_Received = 0;
					flags.Pair_data_Received_Flag = 0;
				}
			}
		}
	}
}

void Send_BLE_Beacons_Commands(void)
{
	switch(Send_Command_State)
	{
	case 0:
		check_ble_command_response = 1;
		LP_UART1_Transmit(BM71_Command_0,5);
#if(D_DEBUG1)
		UART1_Transmit(BM71_Command_0,5);
#endif
		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 1:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
		//	Check_Get_Response(BLE_Response_4,6);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;
				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}

			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
			if(Send_cmd_Error_Cnt > 5)
			{
				Send_Command_State = 0;
				flags.Shutdown_MCU_mosfet=1;
			}
#if(D_DEBUG1)

			UART1_Transmit(Response_string_2,19);

#endif
		}
		break;
	case 2:
		check_ble_command_response = 2;
//		LP_UART1_Transmit(BM71_Command_11,1);
//		HAL_Delay(100);
		LP_UART1_Transmit(BM71_Command_1,3);

#if(D_DEBUG1)
		UART1_Transmit(BM71_Command_1,3);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 3:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_0,5);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State++;
				Send_cmd_Error_Cnt = 0;

			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;
				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
					Send_cmd_Error_Cnt = 0;
				}
#if(D_DEBUG1)

				UART1_Transmit(Response_string_2,19);

#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;

			Send_cmd_Error_Cnt++;

			if(Send_cmd_Error_Cnt > 5)
			{
				Send_Command_State = 0;
				Send_cmd_Error_Cnt = 0;
			}
#if(D_DEBUG1)

			UART1_Transmit(Response_string_2,19);

#endif
		}
		break;
	case 4:
		check_ble_command_response = 3;
		LP_UART1_Transmit(BM71_Command_6,5);
#if(D_DEBUG1)
		UART1_Transmit(BM71_Command_6,5);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 5:

		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State ++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG1)

				UART1_Transmit(Response_string_2,19);

#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG1)

			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_Command_State = 0;
			}
		}
		break;


//	case 6:
//
//		LP_UART1_Transmit(BM71_Command_7,7);
//#if(D_DEBUG1)
//		UART1_Transmit(BM71_Command_7,7);
//#endif
//
//		flags.Start_Command_Response_time = 1;
//		Counter_Response_Time = 0;
//		Send_Command_State++;
//		break;
//	case 7:
//
//		if(flags.Data_Received_Flag == 1)
//		{
//			flags.Data_Received_Flag = 0;
//			flags.Start_Command_Response_time = 0;
//			Counter_Response_Time = 0;
//			Check_Get_Response(BLE_Response_1,9);
//			if(flags.Response_OK_flag == 1)
//			{
//#if(D_DEBUG1)
//				UART1_Transmit(Response_string_1,13);
//#endif
//				Send_Command_State ++;
//				Send_cmd_Error_Cnt = 0;
//			}
//			else
//			{
//				Send_Command_State--;
//				Send_cmd_Error_Cnt++;
//
//				if(Send_cmd_Error_Cnt > 2)
//				{
//					Send_Command_State = 0;
//				}
//#if(D_DEBUG1)
//
//				UART1_Transmit(Response_string_2,19);
//
//#endif
//			}
//		}
//		else if(flags.Command_Response_timeout == 1)
//		{
//			flags.Command_Response_timeout = 0;
//			Counter_Response_Time = 0;
//			Send_Command_State--;
//			Send_cmd_Error_Cnt++;
//#if(D_DEBUG1)
//
//			UART1_Transmit(Response_string_2,19);
//#endif
//			if(Send_cmd_Error_Cnt > 2)
//			{
//				Send_Command_State = 0;
//			}
//		}
//		break;

	case 6:

		LP_UART1_Transmit(BM71_Command_8,6);
#if(D_DEBUG1)
		UART1_Transmit(BM71_Command_8,6);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 7:

		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State ++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG1)

				UART1_Transmit(Response_string_2,19);

#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG1)

			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_Command_State = 0;
			}
		}
		break;

	case 8:

		LP_UART1_Transmit(BM71_Command_9,10);
#if(D_DEBUG1)
		UART1_Transmit(BM71_Command_9,10);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;

	case 9:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State ++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG1)

				UART1_Transmit(Response_string_2,19);

#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG1)

			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_Command_State = 0;
			}
		}
		break;
	case 10:
		LP_UART1_Transmit(BM71_Command_10,6);
#if(D_DEBUG1)
		UART1_Transmit(BM71_Command_10,6);
#endif

		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 11:

		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State ++;
				Send_cmd_Error_Cnt = 0;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 2)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG1)

				UART1_Transmit(Response_string_2,19);

#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG1)

			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 2)
			{
				Send_Command_State = 0;
			}
		}
		break;

	case 12:

		memset(Send_MAC_ADD,0,28);
		sprintf(Send_MAC_ADD,"NB,FF,CD000000%s",&MAC_ADD);
		Send_MAC_ADD[26]='\r';
		Send_MAC_ADD[27]='\n';

		LP_UART1_Transmit(Send_MAC_ADD, sizeof(Send_MAC_ADD));
		if(D_DEBUG1)
		{
			UART1_Transmit(Send_MAC_ADD,sizeof(Send_MAC_ADD));
		}
		//		LP_UART1_Transmit(BM71_Command_14, 56);
		//		if(D_DEBUG1)
		//		{
		//			UART1_Transmit(BM71_Command_14,56);
		//		}


		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;
	case 13:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_Command_State ++;

				Send_cmd_Error_Cnt = 0;

			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 5)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG1)
				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG1)
			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 5)
			{
				Send_Command_State = 0;
			}
		}
		break;

	case 14:

		LP_UART1_Transmit(BM71_Command_14,3);
#if(D_DEBUG1)
		UART1_Transmit(BM71_Command_14,3);
#endif
		flags.Start_Command_Response_time = 1;
		Counter_Response_Time = 0;
		Send_Command_State++;
		break;

	case 15:
		if(flags.Data_Received_Flag == 1)
		{
			flags.Data_Received_Flag = 0;
			flags.Start_Command_Response_time = 0;
			Counter_Response_Time = 0;
			Check_Get_Response(BLE_Response_1,9);
			if(flags.Response_OK_flag == 1)
			{
#if(D_DEBUG1)
				UART1_Transmit(Response_string_1,13);
#endif
				Send_cmd_Error_Cnt = 0;
				Ble_Connect_Counter_Response_Time = 0;
				//				flags.Start_Ble_Connect_timeout_flag = 1;
				BLEControl_H;

				Send_Command_State++;
			}
			else
			{
				Send_Command_State--;
				Send_cmd_Error_Cnt++;

				if(Send_cmd_Error_Cnt > 5)
				{
					Send_Command_State = 0;
				}
#if(D_DEBUG1)
				UART1_Transmit(Response_string_2,19);
#endif
			}
		}
		else if(flags.Command_Response_timeout == 1)
		{
			flags.Command_Response_timeout = 0;
			Counter_Response_Time = 0;
			Send_Command_State--;
			Send_cmd_Error_Cnt++;
#if(D_DEBUG1)
			UART1_Transmit(Response_string_2,19);
#endif
			if(Send_cmd_Error_Cnt > 5)
			{
				Send_Command_State = 0;
			}
		}
		break;

	case 16:
		//		BLEControl_L;
		//		HAL_Delay(1000);
		//		BLEControl_H;
		//
		//		UART1_Transmit(Dormant_mode_string,29);
		//		LP_UART1_Transmit(BM71_Command_12,5);
		//		UART1_Transmit(BM71_Command_12,5);
		//
		//		//		flags.Disconnect_ble_flag = 0;
		flags.configure_ble_beacons = 0;

		//	MX_RTC_Init();
		MX_RTC_Init();
		flags.F_Run_Stop2_Mode = 1;
		//		flags.Start_Ble_wakeup_timeout_flag = 1;
		Ble_Connect_Counter_Response_Time = 0;
		flags.Tag_printing_done_flag=1;
		HAL_GPIO_WritePin(LCD_Mosfet_GPIO_Port,LCD_Mosfet_Pin,1);
		break;
	}
}
