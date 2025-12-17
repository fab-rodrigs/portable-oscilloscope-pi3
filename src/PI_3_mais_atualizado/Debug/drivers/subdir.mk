################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_common_arm.c \
../drivers/fsl_dmamux.c \
../drivers/fsl_dspi.c \
../drivers/fsl_dspi_edma.c \
../drivers/fsl_edma.c \
../drivers/fsl_gpio.c \
../drivers/fsl_i2c.c \
../drivers/fsl_i2c_edma.c \
../drivers/fsl_rnga.c \
../drivers/fsl_rtc.c \
../drivers/fsl_sai.c \
../drivers/fsl_sai_edma.c \
../drivers/fsl_sdhc.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c \
../drivers/fsl_uart_edma.c 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_common_arm.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_dspi.d \
./drivers/fsl_dspi_edma.d \
./drivers/fsl_edma.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_i2c_edma.d \
./drivers/fsl_rnga.d \
./drivers/fsl_rtc.d \
./drivers/fsl_sai.d \
./drivers/fsl_sai_edma.d \
./drivers/fsl_sdhc.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d \
./drivers/fsl_uart_edma.d 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_common_arm.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_dspi.o \
./drivers/fsl_dspi_edma.o \
./drivers/fsl_edma.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_i2c_edma.o \
./drivers/fsl_rnga.o \
./drivers/fsl_rtc.o \
./drivers/fsl_sai.o \
./drivers/fsl_sai_edma.o \
./drivers/fsl_sdhc.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o \
./drivers/fsl_uart_edma.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_BAREMETAL -DLV_CONF_INCLUDE_SIMPLE -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\board" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\utilities" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\drivers" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\device" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\serial_manager" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\lists" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\CMSIS" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\uart" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc\infra" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc\setup" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\include" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\library" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\port\ksdk" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mmcau" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\lvgl" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\lvgl\src" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\template" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\source" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\Inc" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-drivers

clean-drivers:
	-$(RM) ./drivers/fsl_adc16.d ./drivers/fsl_adc16.o ./drivers/fsl_clock.d ./drivers/fsl_clock.o ./drivers/fsl_common.d ./drivers/fsl_common.o ./drivers/fsl_common_arm.d ./drivers/fsl_common_arm.o ./drivers/fsl_dmamux.d ./drivers/fsl_dmamux.o ./drivers/fsl_dspi.d ./drivers/fsl_dspi.o ./drivers/fsl_dspi_edma.d ./drivers/fsl_dspi_edma.o ./drivers/fsl_edma.d ./drivers/fsl_edma.o ./drivers/fsl_gpio.d ./drivers/fsl_gpio.o ./drivers/fsl_i2c.d ./drivers/fsl_i2c.o ./drivers/fsl_i2c_edma.d ./drivers/fsl_i2c_edma.o ./drivers/fsl_rnga.d ./drivers/fsl_rnga.o ./drivers/fsl_rtc.d ./drivers/fsl_rtc.o ./drivers/fsl_sai.d ./drivers/fsl_sai.o ./drivers/fsl_sai_edma.d ./drivers/fsl_sai_edma.o ./drivers/fsl_sdhc.d ./drivers/fsl_sdhc.o ./drivers/fsl_smc.d ./drivers/fsl_smc.o ./drivers/fsl_uart.d ./drivers/fsl_uart.o ./drivers/fsl_uart_edma.d ./drivers/fsl_uart_edma.o

.PHONY: clean-drivers

