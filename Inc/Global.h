/*
 * Global.h
 *
 *  Created on: Oct 5, 2020
 *      Author: bhakti.deshpande
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#define D_DEBUG     0
#define D_DEBUG1     1
#define CHECK_RTC_TIME_FLAG    0
#define CHECK_DISPLAY_FLAG    0
#define Test_Run_Stop2_Mode   1
#define ENABLE_LED_BLINKING     1
#define LOW_BATTERY_CONFIRM_TIME 1000
#define HALF_BATTERY_CONFIRM_TIME 1000
#define FULL_BATTERY_CONFIRM_TIME 1000

#define	START_BYTE 			 	0xA0
#define END_BYTE 			 	0x0A

#define UART_1_TX_Buffer_Size  50
#define UART_1_RX_Buffer_Size  50

#define MAX_IMG_SIZE 16800

typedef struct
{

	unsigned int Data_Received_Flag:1;
	unsigned int Image_USB_Received_Flag:1;
	unsigned int Pair_data_Received_Flag:1;
	unsigned int Start_Response_time_flag:1;
	unsigned int Start_Command_Response_time:1;
	unsigned int F_Response_timeout_done:1;
	unsigned int Command_Response_timeout:1;
	unsigned int CRC_Verified_Flag:1;
	unsigned int Check_busy_pin_flag:1;
	unsigned int Busy_pin_error_flag:1;
	unsigned int Start_busyline_timer:1;
	unsigned int Start_to_reciv_data_flag:1;
	unsigned int Start_to_reciv_time_data_flag:1;
	unsigned int Response_OK_flag:1;
	unsigned char F_Run_Stop2_Mode:1;
	unsigned char Exit_Stop2_Mode_flag:1;
	unsigned char RTC_Alarm_A_wakeup_flag:1;
	unsigned char RTC_Alarm_B_wakeup_flag:1;
	unsigned char Initialize_ble_flag:1;
	unsigned char Ble_connected_flag:1;
	unsigned char F_Device_Data_Received:1;
	unsigned char Receive_Ble_frame_flag:1;
	unsigned char Receive_time_frame_flag:1;
	unsigned char Receive_time_frame_done_flag:1;
	unsigned char print_display:1;
	unsigned char No_responce_Shutdown_MCU_mosfet:1;
	unsigned char Start_Ble_Connect_timeout_flag:1;
	unsigned char Shutdown_MCU_mosfet:1;
	unsigned char Communication_error_flag:1;
	unsigned char Communication_started_flag:1;
	unsigned char Ckeck_communication_error:1;
	unsigned char Disconnect_ble_flag:1;
	unsigned char configure_ble_beacons:1;
	unsigned char Start_Ble_beacons:1;
	unsigned char check_command_response:1;
	unsigned char check_command_response1:1;
	unsigned char check_command_response2:1;
	unsigned char check_command_response3:1;
	unsigned char check_command_response4:1;
	unsigned char Start_vibrator_motor_flag:1;
	unsigned char Check_battery_voltage_flag:1;
	unsigned char Check_reapet_battery_voltage_flag:1;

	unsigned char F_Low_Battery_Voltage:1;
	unsigned char F_full_Battery_Voltage:1;
	unsigned char F_half_Battery_Voltage :1;

	unsigned char F_Monitor_Low_Battery_Voltage :1;
	unsigned char F_Monitor_half_Battery_Voltage:1;
	unsigned char F_Monitor_full_Battery_Voltage:1;
	unsigned char F_Low_Battery_Voltage_Confirmed :1;
	unsigned char	F_full_Battery_Voltage_Confirmed:1;
	unsigned char	F_half_Battery_Voltage_Confirmed :1;
	unsigned char	Battery_status_updated_flag :1;
	unsigned char	Display_not_connected_flag :1;
	unsigned char	Start_Led_blinking :1;
	unsigned char   Tag_Expire_external_interrupt_flag:1;
	unsigned char	Tag_printing_done_flag :1;
	unsigned char LPUART1_Receive_time_frame_flag:1;
	unsigned char UART1_Receive_time_frame_flag:1;
}FLG;
FLG flags;

unsigned char BLE_CONNECTED;


#define MAIN_BLE_COMMAND_STAGE  				0
#define MAIN_BLE_CONNECTION_STAGE     			1
#define MAIN_SAVE_RTC_INPUTS_STAGE     			2
#define MAIN_IMAGE_DATA_RECEPTION_STAGE         3
#define MAIN_SLEEP_MODE_WAKEUP_STAGE            4
#define MAIN_SLEEP_MODE_STAGE 					5



#endif /* GLOBAL_H_ */
