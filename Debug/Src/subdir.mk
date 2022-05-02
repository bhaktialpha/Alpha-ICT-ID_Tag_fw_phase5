################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ED037TC2.c \
../Src/ED037TC2_partial_refresh.c \
../Src/Global.c \
../Src/Screens.c \
../Src/User_ADC.c \
../Src/User_Application.c \
../Src/User_Beacon.c \
../Src/User_Buzzer.c \
../Src/User_CRC.c \
../Src/User_ISRs.c \
../Src/User_UART.c \
../Src/adc.c \
../Src/dma.c \
../Src/gpio.c \
../Src/main.c \
../Src/rtc.c \
../Src/spi.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32l0xx.c \
../Src/tim.c \
../Src/usart.c 

OBJS += \
./Src/ED037TC2.o \
./Src/ED037TC2_partial_refresh.o \
./Src/Global.o \
./Src/Screens.o \
./Src/User_ADC.o \
./Src/User_Application.o \
./Src/User_Beacon.o \
./Src/User_Buzzer.o \
./Src/User_CRC.o \
./Src/User_ISRs.o \
./Src/User_UART.o \
./Src/adc.o \
./Src/dma.o \
./Src/gpio.o \
./Src/main.o \
./Src/rtc.o \
./Src/spi.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32l0xx.o \
./Src/tim.o \
./Src/usart.o 

C_DEPS += \
./Src/ED037TC2.d \
./Src/ED037TC2_partial_refresh.d \
./Src/Global.d \
./Src/Screens.d \
./Src/User_ADC.d \
./Src/User_Application.d \
./Src/User_Beacon.d \
./Src/User_Buzzer.d \
./Src/User_CRC.d \
./Src/User_ISRs.d \
./Src/User_UART.d \
./Src/adc.d \
./Src/dma.d \
./Src/gpio.d \
./Src/main.d \
./Src/rtc.d \
./Src/spi.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32l0xx.d \
./Src/tim.d \
./Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L073xx -c -I../Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -Og -ffunction-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/ED037TC2.d ./Src/ED037TC2.o ./Src/ED037TC2_partial_refresh.d ./Src/ED037TC2_partial_refresh.o ./Src/Global.d ./Src/Global.o ./Src/Screens.d ./Src/Screens.o ./Src/User_ADC.d ./Src/User_ADC.o ./Src/User_Application.d ./Src/User_Application.o ./Src/User_Beacon.d ./Src/User_Beacon.o ./Src/User_Buzzer.d ./Src/User_Buzzer.o ./Src/User_CRC.d ./Src/User_CRC.o ./Src/User_ISRs.d ./Src/User_ISRs.o ./Src/User_UART.d ./Src/User_UART.o ./Src/adc.d ./Src/adc.o ./Src/dma.d ./Src/dma.o ./Src/gpio.d ./Src/gpio.o ./Src/main.d ./Src/main.o ./Src/rtc.d ./Src/rtc.o ./Src/spi.d ./Src/spi.o ./Src/stm32l0xx_hal_msp.d ./Src/stm32l0xx_hal_msp.o ./Src/stm32l0xx_it.d ./Src/stm32l0xx_it.o ./Src/syscalls.d ./Src/syscalls.o ./Src/system_stm32l0xx.d ./Src/system_stm32l0xx.o ./Src/tim.d ./Src/tim.o ./Src/usart.d ./Src/usart.o

.PHONY: clean-Src

