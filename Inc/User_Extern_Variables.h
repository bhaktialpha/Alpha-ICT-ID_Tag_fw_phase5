/*
 * User_Extern_Variables.h
 *
 *  Created on: Feb 25, 2021
 *      Author: Alpha037
 */

#ifndef USER_EXTERN_VARIABLES_H_
#define USER_EXTERN_VARIABLES_H_



#endif /* USER_EXTERN_VARIABLES_H_ */
/*******************************************************************************
 * File Includes
 ******************************************************************************/
/* NXP Library files */
#include "stdbool.h"
#include "stdint.h"
//#include "phApp_Init.h"
//#include "board.h"
//#include "fsl_tpm.h"
//#include "fsl_lpuart.h"
//#include "fsl_intmux.h"
//#include "fsl_wdog32.h"

/* User defined files */
#include "User_Defines.h"



/*******************************************************************************
 * Variables Definitions
 ******************************************************************************/
/* User_RFID.c */
extern volatile bool tpmIsrFlag;

/* User_Buzzer.c */
extern unsigned char PWM_Tone_Part;
extern unsigned char F_Unlock_Alarm;
extern unsigned char F_Lock_Alarm;
extern unsigned char F_Long_Beep_Alarm;
extern unsigned char F_Double_Beep_Alarm;
extern unsigned char F_Error_Alarm;
extern unsigned char F_Wait_For_Long_Beep_Buzzer;
extern unsigned char F_Wait_For_Unlock_Buzzer;
extern unsigned char F_Wait_For_Error_Buzzer;
extern unsigned char F_Wait_For_Lock_Buzzer;
extern volatile uint8_t updatedDutycycle;
/* User_Usart.c */
extern unsigned char F_Start_Receive_Data_USART2;
extern unsigned char F_HHD_Data_Captured_USART2;
extern unsigned char F_Omit_USART2_First_Received_Byte;
extern unsigned char Rx_Byte_USART2;
extern unsigned char F_Receive_Complete_USART2;
extern unsigned char Received_Index_End_Char;
extern unsigned char F_Start_USART2_Receive_Timeout;
/* User_PC_Communication.c */
extern unsigned char F_Write_to_HHD_UART;
extern unsigned char F_Start_Send_Frame;
extern unsigned char F_Comm_Timeout;
extern unsigned char F_Start_Comm_Timeout;
extern unsigned char F_HHD_Detect_Timeout;
extern unsigned char F_Start_HHD_Detect_Timeout;
extern unsigned char F_Start_HHD_Comm_Timeout;
extern unsigned char F_Start_Card_RW_Timeout;
extern unsigned char F_Card_RW_Timeout;
extern unsigned char F_Err_LED_Indication_Off;
extern unsigned char F_Err_LED_Indication_On;
extern unsigned char F_Start_Err_LED_Indication;
extern unsigned char F_Start_Card_RW_LED_Indication;
/* User_RFID.c */
extern unsigned char F_RFID_Tag_Removed;
extern unsigned char F_RFID_Tag_Write_Complete;
extern unsigned char RW_Tag_Block_Number;/* Start from Sector 3, block 0 */
extern unsigned char RW_Tag_Block_Number_Bak;
extern unsigned char RW_Tag_Sector_Number;
extern unsigned char RW_Tag_Buffer_Index;
extern unsigned char F_Card_Detected;
extern unsigned char F_RFID_Tag_Write_Fail;
extern unsigned char F_RFID_Tag_Read_Fail;
extern unsigned char F_Card_Read_Command_Received;
extern unsigned char F_Card_Write_Command_Received;
extern unsigned char F_RFID_Tag_Read_Complete;
extern unsigned char bUidSize;
extern unsigned char F_RFID_Lib_Init_Err;
/* User_Timer.c */
extern unsigned char F_Door_Handle_Pressed;
extern unsigned char F_First_Time_Handle_Pressed;
extern unsigned char F_First_Time_Handle_Release;
extern unsigned char Counter_10ms;

/* User_Usart.c */
//extern unsigned char Receive_Data_USART2[1];
//extern unsigned char Rx_Buffer_USART2[RX_BUF_SIZE];
//extern unsigned char Tx_Buffer_USART2[TX_BUF_SIZE];
///* User_PC_Communication.c */
//extern unsigned char Error_Code_Buffer[2];
//extern unsigned char Card_Data_Buffer[CARD_DATA_SIZE];
/* User_RFID.c */
extern uint8_t bDataBuffer[32];
extern unsigned char User_NFC_memory_read_bytes[246];
extern uint8_t Key[12];/* Set the key for the MIFARE (R) Classic cards. */
extern uint8_t Original_Key[12];

/* User_Buzzer.c */
extern unsigned int PWM_Time_Counter;
extern unsigned int Current_Volume_Val_Buzzer_Tune;
/* User_Usart.c */
extern unsigned int Rx_Index_USART2;
extern unsigned int Rx_Index_USART2_Bak;
extern unsigned int USART2_Receive_Timeout_Counter;
extern unsigned int txIndex;
extern unsigned int Received_Index_End_Char_1;
extern unsigned int Received_Payload_Bytes_USART2;
/* User_PC_Communication.c */
extern unsigned int PC_Comm_Stage;
extern unsigned int Comm_Timeout_Counter;
extern unsigned int HHD_Comm_Timeout_Counter;
extern unsigned int  HHD_Detect_Timeout_Counter;
extern unsigned int Send_Frame_Counter;
extern unsigned int HHD_Tx_Size;
extern unsigned int Card_RW_Timeout_Counter;
extern unsigned int Err_LED_Indication_Counter;
extern unsigned int Err_LED_Indication_Counter1;
extern unsigned int Card_RW_LED_Indication_Counter;
/* User_RFID.c */
extern volatile uint32_t DelaytickCounter;
extern unsigned int Main_Operation;
extern unsigned int NFC_Tag_Process_Stage;
extern unsigned int Tag_Status;
extern unsigned int wTagsDetected_Bak;
/* User_Timer.c */
extern uint32_t Input_Val;

///* User_RFID.c */
//extern phacDiscLoop_Sw_DataParams_t       * pDiscLoop;       /* Discovery loop component */
///* User_WDT.c */
//extern WDOG_Type *wdog32_base;
///* User_Timer.c */
//extern tpm_chnl_pwm_signal_param_t tpmParam;
///* User_Usart.c */
//extern lpuart_config_t config;
//extern lpuart_transfer_t xfer;
//extern lpuart_transfer_t sendXfer;
//extern lpuart_transfer_t receiveXfer;
///* User_RFID.c */
//extern phKeyStore_Sw_KeyEntry_t           sKeyEntries[NUMBER_OF_KEYENTRIES];                                  /* Sw KeyEntry structure */
//extern phKeyStore_Sw_KUCEntry_t           sKUCEntries[NUMBER_OF_KUCENTRIES];                                  /* Sw Key usage counter structure */
//extern phKeyStore_Sw_KeyVersionPair_t     sKeyVersionPairs[NUMBER_OF_KEYVERSIONPAIRS * NUMBER_OF_KEYENTRIES]; /* Sw KeyVersionPair structure */
//extern phacDiscLoop_Sw_DataParams_t       * pDiscLoop;       /* Discovery loop component */
