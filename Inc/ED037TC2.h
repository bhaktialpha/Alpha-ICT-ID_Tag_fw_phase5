#ifndef __ED037TC2_H__
#define __ED037TC2_H__

#include "main.h"
#include "stm32l0xx_hal.h"
#include "Global.h"
#define Vibrator_Motor_H 				HAL_GPIO_WritePin(Vibrator_motor_GPIO_Port, Vibrator_motor_Pin, GPIO_PIN_SET);
#define Vibrator_Motor_L 				HAL_GPIO_WritePin(Vibrator_motor_GPIO_Port, Vibrator_motor_Pin, GPIO_PIN_RESET);


typedef uint16_t eink_coordinate;
/*************************************************************************************
 * Copyright (C) 2019 E Ink Holdings Inc. (Ryan Liu, Eric CH Huang) All Rights Reserved *
 *************************************************************************************/
/**********************************
Constant set
**********************************/
#define BUSYN  HAL_GPIO_ReadPin(ePD1_BUSY_GPIO_Port,ePD1_BUSY_Pin)//new
#define RSTN_L HAL_GPIO_WritePin(ePD1_RESET_GPIO_Port,ePD1_RESET_Pin,0)//new
#define RSTN_H HAL_GPIO_WritePin(ePD1_RESET_GPIO_Port,ePD1_RESET_Pin,1)

#define DC_L   HAL_GPIO_WritePin(ePD1_D_C_GPIO_Port,ePD1_D_C_Pin,0)//new
#define DC_H   HAL_GPIO_WritePin(ePD1_D_C_GPIO_Port,ePD1_D_C_Pin,1)


#define CSB_H  HAL_GPIO_WritePin(ePD1_CS_GPIO_Port,ePD1_CS_Pin,1)//new
#define CSB_L  HAL_GPIO_WritePin(ePD1_CS_GPIO_Port,ePD1_CS_Pin,0)

#define SDA_H  HAL_GPIO_WritePin(ePD1_MOSI_GPIO_Port,ePD1_MOSI_Pin,1)
#define SDA_L  HAL_GPIO_WritePin(ePD1_MOSI_GPIO_Port,ePD1_MOSI_Pin,0)

#define SCL_L  	HAL_GPIO_WritePin(ePD1_SCK_GPIO_Port,ePD1_SCK_Pin,0)
#define SCL_H  	HAL_GPIO_WritePin(ePD1_SCK_GPIO_Port,ePD1_SCK_Pin,1)


//#define SDA_IN  HAL_GPIO_ReadPin(ePD1_MOSI_GPIO_Port,ePD1_MOSI_Pin)//new

#define BLEControl_L  	HAL_GPIO_WritePin(Ble_control_GPIO_Port,Ble_control_Pin,0);
#define BLEControl_H  	HAL_GPIO_WritePin(Ble_control_GPIO_Port,Ble_control_Pin,1);

#define MCU_Mosfet_L  	HAL_GPIO_WritePin(MCU_Mosfet_GPIO_Port,MCU_Mosfet_Pin,0);
#define MCU_Mosfet_H  	HAL_GPIO_WritePin(MCU_Mosfet_GPIO_Port,MCU_Mosfet_Pin,1);

//#define MCU_Mosfet_L  	HAL_GPIO_WritePin(Button_Status_GPIO_Port,Button_Status_Pin,0);
//#define MCU_Mosfet_H  	HAL_GPIO_WritePin(Button_Status_GPIO_Port,Button_Status_Pin,1);


#define Ble_Mosfet_L  	HAL_GPIO_WritePin(Ble_Mosfet_GPIO_Port,Ble_Mosfet_Pin,0);
#define Ble_Mosfet_H  	HAL_GPIO_WritePin(Ble_Mosfet_GPIO_Port,Ble_Mosfet_Pin,1);

#define LED1_L  	HAL_GPIO_WritePin(Battery_Indication_LED_GPIO_Port,Battery_Indication_LED_Pin,0);
#define LED1_H  	HAL_GPIO_WritePin(Battery_Indication_LED_GPIO_Port,Battery_Indication_LED_Pin,1);

unsigned int byte_counter;// = MAX_IMG_SIZE;

#define DATA_MASK   0x0100
#define DCX_CMD     0x0000
#define DCX_DATA    0x0001


#define LUT_VCOM    0x0020
#define LUT_WW      0x0021
#define LUT_R       0x0022 // LUTR/LUTBW
#define LUT_W       0x0023 // LUTW/LUTWB
#define LUT_B       0x0024 // LUTB/LUTBB
#define LUTC_O      0x0025

#define Initial_23_16          0x00
#define Initial_15_0           0x0000 // 1K
#define Temperature0_23_16     0x00
#define Temperature0_15_0      0x0400 // 1K
#define Temperature1_23_16     0x00
#define Temperature1_15_0      0x0800
#define Temperature2_23_16     0x00
#define Temperature2_15_0      0x0C00
#define Temperature3_23_16     0x00
#define Temperature3_15_0      0x1000
#define Temperature4_23_16     0x00
#define Temperature4_15_0      0x1400
#define Temperature5_23_16     0x00
#define Temperature5_15_0      0x1800
#define Temperature6_23_16     0x00
#define Temperature6_15_0      0x1C00
#define Temperature7_23_16     0x00
#define Temperature7_15_0      0x2000
#define Temperature8_23_16     0x00
#define Temperature8_15_0      0x2400
#define Temperature9_23_16     0x00
#define Temperature9_15_0      0x2800
#define Temperature10_23_16    0x00
#define Temperature10_15_0     0x2C00

#endif 

#define PDTM1        0x14
#define PDTM2        0x15
#define PDRF         0x16

#define PFS         0x0003
#define CMD         0xF8
#define OSC         0x0030
#define OSC_V	    0x003C

#define PSR         0x00
#define PSR_V       0x6F

#define PWR_EPD     0x01
#define PWR_V1      0x03
#define PWR_V2      0x00//0x07
#define PWR_V3      0x3F//0x0D
#define PWR_V4      0x3F//0x0D
#define PWR_V5      0x0F//0x00

#define POF         0x02
#define PON         0x04

#define DTM1        0x10
#define DTM2        0x13

#define DSP         0x11
#define DRF         0x12

#define PLL_M       0x30
#define PLL_V       0x2A

#define TSC_EPD     0x40
#define TSE         0x41
#define TSE_V       0x00
#define CDI         0x50
#define CDI_V       0x37
#define TCON        0x60
#define TCON_V      0x04
#define TRES        0x61

#define SET_STG     0x26
#define SET_STG_V     0x0F

#define AMV     0x80
#define AMV_V     0x11
#define VV          0x82


#define TSGS        0x0062
#define TSGS_V1        0x00
#define TSGS_V2        0x00
#define TSGS_V3        0x00
#define TSGS_V4        0x00
//   2"
#define TRES_V1     0x01
#define TRES_V2     0x18
#define TRES_V3     0x01
#define TRES_V4     0xE0

#define VDCS        0x82
#define VDCS_V      0x0C // -0.8V

#define BTST      	0x06
#define BTST_V1   	0x57
#define BTST_V2   	0x63
#define BTST_V3   	0x31

// EPD2- Pins Macros
#define BUSY2N  HAL_GPIO_ReadPin(ePD2_BUSY_GPIO_Port,ePD2_BUSY_Pin)
#define RSTN2_L HAL_GPIO_WritePin(ePD2_RESET_GPIO_Port,ePD2_RESET_Pin,0)
#define RSTN2_H HAL_GPIO_WritePin(ePD2_RESET_GPIO_Port,ePD2_RESET_Pin,1)
#define DC2_L   HAL_GPIO_WritePin(ePD2_D_C_GPIO_Port,ePD2_D_C_Pin,0)
#define DC2_H   HAL_GPIO_WritePin(ePD2_D_C_GPIO_Port,ePD2_D_C_Pin,1)
#define CSB2_H  HAL_GPIO_WritePin(ePD2_CS_GPIO_Port,ePD2_CS_Pin,1)
#define CSB2_L  HAL_GPIO_WritePin(ePD2_CS_GPIO_Port,ePD2_CS_Pin,0)



// EPD2- Pins Macros

//EPD1 Functions
void check_busy_high(void);
void check_busy_low(void);
int EPD_Init(void);
void EPD_Display_KW(const unsigned char *img_kw, unsigned int size);
void EPD_Load_Display_Data(unsigned char const *Value);
void EPD_Display_White(void);
void EPD_Display_Black(void);
void EPD_Display_Black1(void);
int Eink_Partial_Display_Update(eink_coordinate x, eink_coordinate y, eink_coordinate w, eink_coordinate l,const unsigned char *img_kw );

//EPD1 Functions



//__ED037TC2_EXTERN__ unsigned int byte_counter;
