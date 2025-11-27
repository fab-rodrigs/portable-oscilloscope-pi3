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
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_BAREMETAL -DLV_CONF_INCLUDE_SIMPLE -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\library" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\port\ksdk" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\lvgl\src" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\Inc" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-mbedtls-2f-port-2f-ksdk

clean-mbedtls-2f-port-2f-ksdk:
	-$(RM) ./mbedtls/port/ksdk/aes_alt.d ./mbedtls/port/ksdk/aes_alt.o ./mbedtls/port/ksdk/des_alt.d ./mbedtls/port/ksdk/des_alt.o ./mbedtls/port/ksdk/ecp_alt.d ./mbedtls/port/ksdk/ecp_alt.o ./mbedtls/port/ksdk/ecp_alt_ksdk.d ./mbedtls/port/ksdk/ecp_alt_ksdk.o ./mbedtls/port/ksdk/ecp_curves_alt.d ./mbedtls/port/ksdk/ecp_curves_alt.o ./mbedtls/port/ksdk/ksdk_mbedtls.d ./mbedtls/port/ksdk/ksdk_mbedtls.o

.PHONY: clean-mbedtls-2f-port-2f-ksdk

