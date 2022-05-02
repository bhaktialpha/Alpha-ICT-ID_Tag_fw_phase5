/*
 * User_Extern_Functions.h
 *
 *  Created on: Feb 25, 2021
 *      Author: Alpha037
 */

#ifndef USER_EXTERN_FUNCTIONS_H_
#define USER_EXTERN_FUNCTIONS_H_



#endif /* USER_EXTERN_FUNCTIONS_H_ */
/*******************************************************************************
 * File Includes
 ******************************************************************************/
/* NXP Library files */
#include "stdbool.h"
#include "stdint.h"
//#include "phApp_Init.h"
/* User defined files */



/*******************************************************************************
 * Function Prototype Definitions
 ******************************************************************************/
/* User_Buzzer.c */
extern void Initiate_Long_Beep_Alarm(void);
extern void Execute_Long_Beep_Alarm(void);
extern void Initiate_Double_Beep_Alarm(void);
extern void Execute_Double_Beep_Alarm(void);
extern void Start_PWM_Buzzer(void);
extern void Stop_PWM_Buzzer(void);
extern void Clear_Buzzer_Alarm_Flags(void);
extern void Update_Buzzer_PWM(uint32_t PWM_Frequency, uint8_t PWM_Duty_Cycle);
extern void Init_Buzzer_PWM(void);
extern void DeInit_Buzzer_PWM(void);
/* User_Usart.c */
extern void Init_HHD_UART(void);
extern void Write_to_HHD_UART(unsigned char *tx_buffer, uint16_t tx_data_size);
/* User_PC_Communication.c */
extern void Write_To_HHD_Init_Variables(unsigned int Buf_Size);
extern void Transmit_HHD_Data(void);
extern unsigned int Calculate_CRC(unsigned char* Buf, unsigned char Frame_Length);
extern unsigned char Validate_Received_Frame(unsigned char Cmp_Frame_Type, unsigned char Cmp_Cmd_Code_1, unsigned char Cmp_Cmd_Code_2, unsigned char F_Cmp_Sys_Pw);
extern unsigned char Check_Received_CRC(void);
extern unsigned char Check_Received_Frame_Type(unsigned char Rcv_Frame_type);
extern unsigned char Check_Received_Command_Code(unsigned char Rcv_Cmd_Code_1, unsigned char Rcv_Cmd_Code_2);
extern void Clear_Send_Frame_Flags(void);
extern void Start_Comm_Timeout(void);
extern void Clear_Comm_Timeout(void);
extern unsigned char Check_Comm_Timeout(void);
extern unsigned char Check_Received_Write_Card_Command_Data(void);
extern unsigned char Check_Received_Read_Card_Command_Data(void);
extern unsigned char Check_Received_DisConnect_Command_Data(void);
extern unsigned char Check_Received_Set_Lock_Time_Command_Data(void);
extern void Clear_Lock_Uart_Comm_Flags(void);
extern void Clear_USART2_Receive_Timeout(void);
extern unsigned char Check_PC_Frame_Command(unsigned char Cmp_Frame_Type, unsigned char Cmp_Cmd_Code_1, unsigned char Cmp_Cmd_Code_2, unsigned char F_Cmp_Sys_Pw);
extern char Execute_Received_Command(void);
extern void Process_PC_Command(void);
extern void Send_Error_Response(void);
extern void Fill_And_Send_OK_Response_Buffer(unsigned char Frame_Type, unsigned char Cmd_Code);
extern void Fill_And_Send_Card_Read_Response_Buffer(unsigned char Frame_Type, unsigned char Cmd_Code);
extern void Fill_And_Send_NOK_Response_Buffer(unsigned char Frame_Type, unsigned char Cmd_Code);
extern void Reset_RFID_Process_Flags(void);
extern void Init_Variables(void);
extern void Convert_To_Ascii_Of_Hex(unsigned int Val, unsigned char* Ret_Buf);
/* User_RFID.c */
extern void NfcrdlibEx4_MIFAREClassic(void *pParams);
extern unsigned char RFID_Init(void);
extern void Execute_RFID_Process(void);
/* User_Timer.c */
extern void Init_Timer(void);
extern void DelayTicks(uint32_t n);
/* User_WDT.c */
extern void Init_WDT(void);
/* User_PC_CRC.c */
extern uint16_t crc_xmodem( const unsigned char *input_str, size_t num_bytes );
