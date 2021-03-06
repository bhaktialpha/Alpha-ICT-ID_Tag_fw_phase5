/*
 * User_UART.h
 *
 *  Created on: 19-Sep-2018
 *      Author: Ajinkya
 */

#include "stdint.h"
#include "Global.h"

 uint8_t UART_1_Transmit_Buffer[50];

 uint8_t  LPUART1_Receive_Buffer[140];
 extern uint8_t usart_1_Rx_Data[2],lpuart_1_Rx_Data[2];


unsigned int Send_cmd_Error_Cnt,Counter_Response_Time;

void UART1_Transmit( uint8_t *strptr, unsigned int length);
void LP_UART1_Transmit( uint8_t *strptr, unsigned int length);

void Check_Device_Connection();
void Send_BLE_Commands(void);
void Disconnect_Ble(void);
void Send_BLE_Beacons_Commands(void);

extern uint8_t usart_1_Rx_Data[2];
extern uint8_t lpuart_1_Rx_Data[2];
//extern unsigned char Transmit_Buffer[50];
extern unsigned char LPUART1_CRC[2];
//extern unsigned char LPUART1_Image_Buffer[16803];
extern unsigned char LPUART1_Footer[2];
extern unsigned char LPUART1_Image_Data_Buffer[16803];
extern unsigned char LPUART1_Image_Buffer1[144];
extern unsigned char LPUART1_Time[6];

extern unsigned char UART1_CRC[2];
extern unsigned char UART1_Header[2];
extern unsigned char UART1_Footer[2];
extern unsigned char UART1_Time[6];
extern unsigned int Frame_count;

