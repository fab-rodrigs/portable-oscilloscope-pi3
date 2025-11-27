################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/core/lv_disp.c \
../lvgl/src/core/lv_event.c \
../lvgl/src/core/lv_group.c \
../lvgl/src/core/lv_indev.c \
../lvgl/src/core/lv_indev_scroll.c \
../lvgl/src/core/lv_obj.c \
../lvgl/src/core/lv_obj_class.c \
../lvgl/src/core/lv_obj_draw.c \
../lvgl/src/core/lv_obj_pos.c \
../lvgl/src/core/lv_obj_scroll.c \
../lvgl/src/core/lv_obj_style.c \
../lvgl/src/core/lv_obj_style_gen.c \
../lvgl/src/core/lv_obj_tree.c \
../lvgl/src/core/lv_refr.c \
../lvgl/src/core/lv_theme.c 

C_DEPS += \
./lvgl/src/core/lv_disp.d \
./lvgl/src/core/lv_event.d \
./lvgl/src/core/lv_group.d \
./lvgl/src/core/lv_indev.d \
./lvgl/src/core/lv_indev_scroll.d \
./lvgl/src/core/lv_obj.d \
./lvgl/src/core/lv_obj_class.d \
./lvgl/src/core/lv_obj_draw.d \
./lvgl/src/core/lv_obj_pos.d \
./lvgl/src/core/lv_obj_scroll.d \
./lvgl/src/core/lv_obj_style.d \
./lvgl/src/core/lv_obj_style_gen.d \
./lvgl/src/core/lv_obj_tree.d \
./lvgl/src/core/lv_refr.d \
./lvgl/src/core/lv_theme.d 

OBJS += \
./lvgl/src/core/lv_disp.o \
./lvgl/src/core/lv_event.o \
./lvgl/src/core/lv_group.o \
./lvgl/src/core/lv_indev.o \
./lvgl/src/core/lv_indev_scroll.o \
./lvgl/src/core/lv_obj.o \
./lvgl/src/core/lv_obj_class.o \
./lvgl/src/core/lv_obj_draw.o \
./lvgl/src/core/lv_obj_pos.o \
./lvgl/src/core/lv_obj_scroll.o \
./lvgl/src/core/lv_obj_style.o \
./lvgl/src/core/lv_obj_style_gen.o \
./lvgl/src/core/lv_obj_tree.o \
./lvgl/src/core/lv_refr.o \
./lvgl/src/core/lv_theme.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/core/%.o: ../lvgl/src/core/%.c lvgl/src/core/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_FREE_RTOS -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\Inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\freertos_kernel\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\port" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\freertos_plus_tcp\test\cbmc\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\freertos_plus_tcp\tools\tcp_utilities\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\tls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\pkcs11" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\crypto\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\mbedtls_utils" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\common_io\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\common_io\test" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\library" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\utils\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\port\ksdk" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\pkcs11\corePKCS11\source\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\mbedtls_config" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\secure_sockets\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\freertos\include\platform" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include\platform" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include\types" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\freertos\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include\private" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include\types" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\host" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\osa" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\template\sdhc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\osa" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-src-2f-core

clean-lvgl-2f-src-2f-core:
	-$(RM) ./lvgl/src/core/lv_disp.d ./lvgl/src/core/lv_disp.o ./lvgl/src/core/lv_event.d ./lvgl/src/core/lv_event.o ./lvgl/src/core/lv_group.d ./lvgl/src/core/lv_group.o ./lvgl/src/core/lv_indev.d ./lvgl/src/core/lv_indev.o ./lvgl/src/core/lv_indev_scroll.d ./lvgl/src/core/lv_indev_scroll.o ./lvgl/src/core/lv_obj.d ./lvgl/src/core/lv_obj.o ./lvgl/src/core/lv_obj_class.d ./lvgl/src/core/lv_obj_class.o ./lvgl/src/core/lv_obj_draw.d ./lvgl/src/core/lv_obj_draw.o ./lvgl/src/core/lv_obj_pos.d ./lvgl/src/core/lv_obj_pos.o ./lvgl/src/core/lv_obj_scroll.d ./lvgl/src/core/lv_obj_scroll.o ./lvgl/src/core/lv_obj_style.d ./lvgl/src/core/lv_obj_style.o ./lvgl/src/core/lv_obj_style_gen.d ./lvgl/src/core/lv_obj_style_gen.o ./lvgl/src/core/lv_obj_tree.d ./lvgl/src/core/lv_obj_tree.o ./lvgl/src/core/lv_refr.d ./lvgl/src/core/lv_refr.o ./lvgl/src/core/lv_theme.d ./lvgl/src/core/lv_theme.o

.PHONY: clean-lvgl-2f-src-2f-core

