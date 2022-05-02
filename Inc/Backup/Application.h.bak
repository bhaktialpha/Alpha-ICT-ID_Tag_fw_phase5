/**
  ******************************************************************************
  * File Name          : Application.h
  * Description        : Function prototypes and Macros for Application execution.
  ******************************************************************************
*/
/* Includes ------------------------------------------------------------------*/
#include <User_Defines.h>
#include "stm32l4xx_hal.h"
#include "i2c.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
//#include "Control.h"
//#include "SF125_Sensor.h"
#include "Cypress_Capsense_3116.h"
#include "User_ADC.h"
#include "Init.h"

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void Check_Capsense_Keys_Operation(void);
void Decide_Execution_Mode(void);
void Reset_Execution(void);
void Process_Execution_Mode(void);
void Check_Door_Operation(void);
void Low_Power_Mode_Execution(void);
void Disable_Peripheral_Clocks(void);
void Enable_Peripheral_Clocks(void);
void Enter_Stop2_Mode(void);
void Exit_Stop2_Mode(void);
void SystemClock_Config(void);
void Display_Key_Press_Messages(void);
void Disable_Current_Execution(void);
void Clear_Door_Unlock_Data(void);

void Check_Door_Status(void);
void Update_Current_Error_LED_Status(void);
void Exit_Wait_For_DoorLock(void);
void Exit_Registration_Mode(void);
void Erase_OTP(void);
//void Start_Buzzer(unsigned int _Period, unsigned int _OnTime);
void Start_Buzzer(unsigned int _Period);
void Start_Buzzer1(unsigned int _Period);
void Stop_Buzzer(void);
void Update_Buzzer(unsigned int _Period);
void Serve_Low_Battery_Indication(void);
void Delete_User_Password_Details(void);
void Delete_User_Passwords(void);
void Prepare_For_Mode_Entry(void);
void Prepare_For_Selected_Mode(void);
void Execute_Deletion_Mode(void);
void Delete_Update_User_Passwords(void);
void Delete_Update_User_Password_Details(void);
void Update_Password_Details(void);
void Delete_Finger_Prints(void);
void Delete_OTP(void);
void Exit_Deletion_Mode(void);
void Prepare_To_Enter_Stop2_Mode(void);
void Prepare_To_Enter_Run_Mode(void);
void Clear_Privacy_Mode_Flags(void);
void Exit_Door_Operation(void);
void Serve_Break_In_Error(void);
void Exit_Break_In_Error(void);
void Clear_Anti_Break_Input_Flags(void);
void Display_Power_On_Message(void);
extern void Execute_Master_Password_Register_Mode(void);
extern void Execute_OTP_Register_Mode(void);
extern void Decide_Deletion_Mode(void);


extern void Drive_Lock();
extern unsigned char F_Unlock_Door;
extern unsigned char F_Start_Door_Unlock_Time;
extern unsigned int Door_Unlock_Time_Counter;
extern unsigned char F_Start_Wait_for_Dummy_Counter;
extern unsigned int Wait_for_Dummy_Counter;

extern unsigned char F_Start_Dummy_Unlock_Counter;
extern unsigned int Dummy_Unlock_Time_Counter;
extern unsigned char F_Start_Latch_Operation_Time;
extern unsigned int Latch_Drive_Time_Counter;
extern unsigned char Lock_Stage;
extern unsigned char F_Key_Matched;
