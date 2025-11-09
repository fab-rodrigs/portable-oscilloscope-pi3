################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../mbedtls/port/ksdk/aes_alt.c \
../mbedtls/port/ksdk/des_alt.c \
../mbedtls/port/ksdk/ecp_alt.c \
../mbedtls/port/ksdk/ecp_alt_ksdk.c \
../mbedtls/port/ksdk/ecp_curves_alt.c \
../mbedtls/port/ksdk/ksdk_mbedtls.c 

C_DEPS += \
./mbedtls/port/ksdk/aes_alt.d \
./mbedtls/port/ksdk/des_alt.d \
./mbedtls/port/ksdk/ecp_alt.d \
./mbedtls/port/ksdk/ecp_alt_ksdk.d \
./mbedtls/port/ksdk/ecp_curves_alt.d \
./mbedtls/port/ksdk/ksdk_mbedtls.d 

OBJS += \
./mbedtls/port/ksdk/aes_alt.o \
./mbedtls/port/ksdk/des_alt.o \
./mbedtls/port/ksdk/ecp_alt.o \
./mbedtls/port/ksdk/ecp_alt_ksdk.o \
./mbedtls/port/ksdk/ecp_curves_alt.o \
./mbedtls/port/ksdk/ksdk_mbedtls.o 


# Each subdirectory must supply rules for building sources it contributes
mbedtls/port/ksdk/%.o: ../mbedtls/port/ksdk/%.c mbedtls/port/ksdk/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DLV_CONF_INCLUDE_SIMPLE -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_FREE_RTOS -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\Inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl\lvgl\src" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\port" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\library" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\port\ksdk" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\host" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\osa" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\template\sdhc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\osa" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\FreeRTOS\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\FreeRTOS\freertos_kernel\include" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-mbedtls-2f-port-2f-ksdk

clean-mbedtls-2f-port-2f-ksdk:
	-$(RM) ./mbedtls/port/ksdk/aes_alt.d ./mbedtls/port/ksdk/aes_alt.o ./mbedtls/port/ksdk/des_alt.d ./mbedtls/port/ksdk/des_alt.o ./mbedtls/port/ksdk/ecp_alt.d ./mbedtls/port/ksdk/ecp_alt.o ./mbedtls/port/ksdk/ecp_alt_ksdk.d ./mbedtls/port/ksdk/ecp_alt_ksdk.o ./mbedtls/port/ksdk/ecp_curves_alt.d ./mbedtls/port/ksdk/ecp_curves_alt.o ./mbedtls/port/ksdk/ksdk_mbedtls.d ./mbedtls/port/ksdk/ksdk_mbedtls.o

.PHONY: clean-mbedtls-2f-port-2f-ksdk

