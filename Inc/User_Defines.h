/**
  ******************************************************************************
  * File Name          : Common_Defines.h
  * Description        : Common Macros used by all the files.
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

//============================ EEPROM ===============================
#ifdef EEPROM_ENABLE

#define EEPROM_DEVICE_ADD						0xA0

#endif

/**
  ******************************************************************************
  * File Name          : Common_Defines.h
  * Description        : Common Macros used by all the files.
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
//#include "stm32l0xx_hal.h"

//============================ EEPROM ===============================
#ifdef EEPROM_ENABLE

#define EEPROM_DEVICE_ADD						0xA0

#endif

/* EEPROM data storage addresses */
#define STORE_IMAGE_ADD							0x0000 // 1-byte, No. of Finger prints registered.
#define DEFAULT_MASTER_PASSWORD_ADD				0x0010 // 16-bytes, Default Master Password address.
#define USER_MASTER_PASSWORD_ADD				0x0020 // 16-bytes, User Master Password address.
#define OTP_ADD									0x0030 // 16-bytes, OTP address.
#define PASSWORD_DETAILS_ADD					0x0040 // 5-bytes, Details of default, user master password and OTP.
#define USER_PASSWORD_DETAILS_ADD				0x0050 // 10-bytes, length details of user passwords.
#define VOLUME_DETAILS_ADD						0x0060 // 2-bytes, Volume details.
#define USER_PASSWORD_1_ADD						0x0100 // 16x10-bytes, User passwords.


#define DEFAULT_MASTER_PASSWORD_LENGTH			5 // No. of bytes in Default Master Password.

//#define USER_PASSWORD_DETAILS_ADD				0x01A0


#define ENROL_RECEIVE_ERROR_COUNT				10
#define RECEIVE_ERROR_COUNT						3
#define TRANSMIT_DELAY							20
#define CLEAR_BUFFER_CHAR						0x7E

#define DIVISION_COUNT							10//50	//

#ifdef ASLONG_MOTOR_ENABLE

#define MOTOR_ON_TIME_CLK						400//400//250 //= ASLONG //1000 = ETONM//mS
#define MOTOR_ON_TIME_CLK_NO_LOAD				MOTOR_ON_TIME_ANTICLK_1
#define MOTOR_ON_TIME_ANTICLK_1					310
#define MOTOR_ON_TIME_ANTICLK					(MOTOR_ON_TIME_ANTICLK_1 + MOTOR_ON_TIME_CLK)//500//= ASLONG//2100 = ETONM//mS
#define MOTOR_OFF_TIME							100//mS//1000//mS

#endif

#ifdef ETONM_MOTOR_ENABLE

#define MOTOR_ON_TIME_CLK						360//400//250 //= ASLONG //1000 = ETONM//mS
#define MOTOR_ON_TIME_CLK_NO_LOAD				MOTOR_ON_TIME_ANTICLK_1
#define MOTOR_ON_TIME_ANTICLK_1					270
#define MOTOR_ON_TIME_ANTICLK					(MOTOR_ON_TIME_ANTICLK_1 + MOTOR_ON_TIME_CLK)//500//= ASLONG//2100 = ETONM//mS
#define MOTOR_OFF_TIME							1000//mS

#endif

#define BUZZER_ON_COUNT				20//10// For 1 sec = 100mS*10
#define BUZZER_BEEP_ON_TIME			4//2// 2*100mS
#define BUZZER_BEEP_OFF_TIME		2//1// 1*100mS
#define BEEP_COUNT					6
#define ENROL_TIME_COUNT			4//4//10//*50mS// 300mS
#define KEY_DEBOUNCE_COUNT			3//*50mS
#define ENROL_KEY_LONG_PRESS_TIME	300//*10mS
#define SENSOR_WAKEUP_TIMEOUT		100//*50mS

#ifdef CAPSENSE_ENABLE

#define UNLOCK_ENTRY_TIMEOUT_COUNT			100//*50mS
//#define CAP_READ_KEY_TIME					2//4//1//*50mS
#define CAP_READ_KEY_TIME					1//4//1//*10mS
#define CAP_KEY_DEBOUNCE_COUNT				1//*50mS
#define UNLOCK_KEY_CODE_LENGTH				4//No. of characters in Door Unlock Code.
#define DOOR_UNLOCK_CODE					0x123A//0x1234	// Door Unlock Code.
#define ONE									0x01	//
#define TWO									0x02	//
#define THREE								0x03	//
#define FOUR								0x04	//
#define FIVE								0x05	//
#define SIX									0x06	//
#define SEVEN								0x07	//
#define EIGHT								0x08	//
#define NINE								0x09	//
#define STAR								'\0'//0x0A	//
#define ZERO								0x0B	//
#define HASH								0x0C	//

#define KEY_BEEP_TIME						4		//*50mS

#define REGISTER_ENTRY_TIMEOUT_COUNT		100 //*50mS

#define WAIT_FOR_SCAN_KEYS_COUNT			20// *50mS

#endif

#ifdef LED_DRIVER_ENABLE

#define LED_DATA_BIT_HIGH					1
#define TOTAL_LED_DATA_BITS					16
#define TOTAL_LED_DATA_BUF_BYTES			12
#define LED_UPDATE_DISPLAY_TIME				2//*50mS
#define LED_DISP_TIMEOUT					160//*50mS

#define LED_1								0x0002 //LED15.
#define LED_2								0x8000 //LED1.
#define LED_3								0x2000 //LED3.
#define LED_4								0x0004 //LED14.
#define LED_5								0x4000 //LED2.
#define LED_6								0x1000 //LED4.
#define LED_7								0x0008 //LED13.
#define LED_8								0x0100 //LED8.
#define LED_9								0x0800 //LED9.
#define LED_STAR							0x0010 //LED12.
#define LED_ZERO							0x0200 //LED7.
#define LED_HASH							0x0400 //LED6.
#define LED_ERR1							0x0020 //LED11.//Low Battery
#define LED_ERR2							0x0040 //LED10.
#define LED_ERR3							0x0080 //LED9.
#define LED_LOGO							0x0001 //LED16.
#define LED_OFF								0x0000

#define ALL_CAP_LED_ON						0xFF1E
#define ALL_CAP_LED_OFF						0x00E1
#define ALL_LED_OFF							0x0000

#define LED_1_POS							14 //LED15.
#define LED_2_POS							0 //LED1.
#define LED_3_POS							2 //LED3.
#define LED_4_POS							13 //LED14.
#define LED_5_POS							1 //LED2.
#define LED_6_POS							3 //LED4.
#define LED_7_POS							12 //LED13.
#define LED_8_POS							7 //LED8.
#define LED_9_POS							4 //LED9.
#define LED_STAR_POS						11 //LED12.
#define LED_ZERO_POS						6 //LED7.
#define LED_HASH_POS						5 //LED6.
#define LED_LOW_BATTERY_POS					10 //LED11.
#define LED_PRIVACY_MODE_POS				9 //LED10.
#define LED_ERROR_ALARM_POS					8 //LED9.
#define LED_LOGO_POS						15 //LED16.

#define USER_SET_BIT(p,q)	((p) |= (1 << (15 - q)))
#define USER_CLR_BIT(p,q)	((p) &= (~(1 << (15 - q))))
#define UPDATE_CURRENT_LED_STATUS(x,y,z) (z?USER_SET_BIT(x,y):USER_CLR_BIT(x,y))
#define LED_BLINK_TIME_COUNT				3// *50mS

#endif

#define EXTI_BUTTON_DEBOUNCE_COUNT			2 //*10mS
#define LOW									0

#ifdef IMAGEMATCH_MODULE_ENABLE

#define ONE_SEC_COUNT				2//4//*50mS//6//2//1//10
#define HEADER_MSB					0xEF
#define TIMEOUT_COUNT				6//8//60//*50mS
//#define STORE_IMAGE_ADD				0x10
#define ENROL_TIMEOUT_COUNT			200//*50mS
#define SEARCH_TIMEOUT_COUNT		100//*50mS

#endif

#define NULL_CHAR					0xFF//0x00

#ifdef IR_SENSOR_DOOR_OPERATION

//#define MAGNET_SWITCH_DELAY_COUNT				100// *50mS
#define MONITOR_DEADBOLT_ERROR_TIME				40// *50mS
#define WAIT_AFTER_MAGNETIC_SWITCH_INPUT_COUNT	40// *50mS
#define DEADBOLT_ERROR_INDICATION_TIME_COUNT	100// *50mS
#define WAIT_TIME_DEADBOLT_ERROR_COUNT			40// *50mS
#define IR_DEBOUNCE_COUNT						10// *10mS
#define MAGNETIC_SWITCH_DEBOUNCE_COUNT			10//*10mS

#endif

#define BUZZER_LONG_BEEP_COUNT					50// *10mS
#define DOOR_BUZZER_LONG_BEEP_COUNT				20// *10mS
#define DEADBOLT_ERROR_BUZZER_OFF_BEEP_COUNT	50// *10mS
#define DEADBOLT_ERROR_BUZZER_ON_BEEP_COUNT		100// *10mS
#define MAGNET_SWITCH_DELAY_COUNT				500

#define FP_MEMORY_FULL_BUZZER_ON_BEEP_COUNT1	20//*10ms
#define FP_MEMORY_FULL_BUZZER_OFF_BEEP_COUNT1	(10 + FP_MEMORY_FULL_BUZZER_ON_BEEP_COUNT1)
#define FP_MEMORY_FULL_BUZZER_ON_BEEP_COUNT2	(20 + FP_MEMORY_FULL_BUZZER_OFF_BEEP_COUNT1)
#define FP_MEMORY_FULL_BUZZER_OFF_BEEP_COUNT2	(80 + FP_MEMORY_FULL_BUZZER_ON_BEEP_COUNT2)

#define DELETE_ENTRY_TIMEOUT_COUNT				100// *50mS
#define KEY_PRESS_ONE_SEC_COUNT					20// *50mS
#define KEY_PRESS_ONE_MIN_COUNT					60// *(KEY_PRESS_ONE_SEC_COUNT * 50mS)

#define ALLOWED_NO_OF_DOOR_OPERATIONS			50// Door operations to be allowed after Low Battery voltage error.
#define PRANK_PREVENTION_ENTRY_COUNT			5
#define DOOR_SUSPENSION_TIME					1200//1min//*50mS
#define PRANK_PREVENTION_ALARM_TIME				200//*50mS

#define TIMER1_PRESCALAR_VAL					8// PWM frequency
#define KEYPAD_BLINK_TIME						2//*10mS
#define KEY_BUZZER_BEEP_TIME					15//*10mS
#define KEY_BUZZER_LONG_BEEP_COUNT				50// *10mS
#define DELETION_MODE_STAR_KEY_PRESS_TIME		60// *50mS
#define INNER_FASCIA_LED_BLINK_TIME				3//*50mS
#define PRIVACY_MODE_BUTTON_PRESS_TIME			300 //*10mS


#define TEST_BUZZER_PERIOD						366
#define TEST_BUZZER_PERIOD1						466


/* EEPROM data storage addresses */
#define STORE_IMAGE_ADD							0x0000 // 1-byte, No. of Finger prints registered.
#define DEFAULT_MASTER_PASSWORD_ADD				0x0010 // 16-bytes, Default Master Password address.
#define USER_MASTER_PASSWORD_ADD				0x0020 // 16-bytes, User Master Password address.
#define OTP_ADD									0x0030 // 16-bytes, OTP address.
#define PASSWORD_DETAILS_ADD					0x0040 // 5-bytes, Details of default, user master password and OTP.
#define USER_PASSWORD_DETAILS_ADD				0x0050 // 10-bytes, length details of user passwords.
#define VOLUME_DETAILS_ADD						0x0060 // 2-bytes, Volume details.
#define USER_PASSWORD_1_ADD						0x0100 // 16x10-bytes, User passwords.


#define DEFAULT_MASTER_PASSWORD_LENGTH			5 // No. of bytes in Default Master Password.

//#define USER_PASSWORD_DETAILS_ADD				0x01A0


#define ENROL_RECEIVE_ERROR_COUNT				10
#define RECEIVE_ERROR_COUNT						3
#define TRANSMIT_DELAY							20
#define CLEAR_BUFFER_CHAR						0x7E

#define DIVISION_COUNT							10//50	//

#ifdef ASLONG_MOTOR_ENABLE

#define MOTOR_ON_TIME_CLK						400//400//250 //= ASLONG //1000 = ETONM//mS
#define MOTOR_ON_TIME_CLK_NO_LOAD				MOTOR_ON_TIME_ANTICLK_1
#define MOTOR_ON_TIME_ANTICLK_1					310
#define MOTOR_ON_TIME_ANTICLK					(MOTOR_ON_TIME_ANTICLK_1 + MOTOR_ON_TIME_CLK)//500//= ASLONG//2100 = ETONM//mS
#define MOTOR_OFF_TIME							100//mS//1000//mS

#endif




typedef unsigned char	UCHAR;
typedef signed char     SCHAR;

typedef unsigned int    UINT;
typedef signed int      SINT;

typedef float			FLOAT;
typedef double			DOUBLE;
typedef signed int      INT;

#define D_CR						0x0D
#define D_LF						0x0A

#define 	UNLOCK_START			1
#define 	UNLOCK_STOP				2
#define 	DUMMY_UNLOCK_START		3
#define 	DUMMY_UNLOCK_STOP		4
#define 	LOCK_START				5
#define 	LOCK_STOP				6
#define 	DUMMY_LOCK_START		7
#define 	DUMMY_LOCK_STOP			8

#define D_EEPROM_1_DEVICE_ID							0xA0

#define D_MAX_ADC_CH 									1
#define D_NO_OF_SAMPLES 								20

//#define D_SPAN_COUNT									3600
//#define D_SPAN_VALUE									6.0
//#define D_ZERO_COUNT									2606//124
//#define D_ZERO_VALUE									4.5//0.1

#define D_MAX_LOG_COUNT						200

#define D_BLE				1
#define D_RFID				2
#define D_MECH_KEY			3
