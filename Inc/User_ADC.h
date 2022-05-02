#include "User_Defines.h"
extern uint32_t ADC_Count[D_MAX_ADC_CH];

extern unsigned char Sample_Number;

extern double ADC_Average[D_MAX_ADC_CH];
extern unsigned int ADC_Sample[D_MAX_ADC_CH][D_NO_OF_SAMPLES];

extern double  Converted_ADC_Value[D_MAX_ADC_CH];
extern double ADCTotalSum;

extern double Battery_Voltage;
unsigned int Monitor_Low_Battery_Voltage_Counter,Monitor_full_Battery_Voltage_Counter,Monitor_half_Battery_Voltage_Counter;
//extern unsigned int Monitor_Low_Battery_Recover_Voltage_Counter;



//extern unsigned char F_Low_Battery_Voltage;


extern void Get_ADC_Value_Converted(unsigned char adc_ch, double *Val_Dest);
extern unsigned int Get_ADC_Average_Single(unsigned char adc_ch);
extern int ADC_Sensing_Operation(void);

void DeInit_ADC(void);
void Init_ADC(void);
