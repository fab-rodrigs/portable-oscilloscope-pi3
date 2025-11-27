################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/core/lv_disp.c \
../lvgl/lvgl/src/core/lv_event.c \
../lvgl/lvgl/src/core/lv_group.c \
../lvgl/lvgl/src/core/lv_indev.c \
../lvgl/lvgl/src/core/lv_indev_scroll.c \
../lvgl/lvgl/src/core/lv_obj.c \
../lvgl/lvgl/src/core/lv_obj_class.c \
../lvgl/lvgl/src/core/lv_obj_draw.c \
../lvgl/lvgl/src/core/lv_obj_pos.c \
../lvgl/lvgl/src/core/lv_obj_scroll.c \
../lvgl/lvgl/src/core/lv_obj_style.c \
../lvgl/lvgl/src/core/lv_obj_style_gen.c \
../lvgl/lvgl/src/core/lv_obj_tree.c \
../lvgl/lvgl/src/core/lv_refr.c \
../lvgl/lvgl/src/core/lv_theme.c 

C_DEPS += \
./lvgl/lvgl/src/core/lv_disp.d \
./lvgl/lvgl/src/core/lv_event.d \
./lvgl/lvgl/src/core/lv_group.d \
./lvgl/lvgl/src/core/lv_indev.d \
./lvgl/lvgl/src/core/lv_indev_scroll.d \
./lvgl/lvgl/src/core/lv_obj.d \
./lvgl/lvgl/src/core/lv_obj_class.d \
./lvgl/lvgl/src/core/lv_obj_draw.d \
./lvgl/lvgl/src/core/lv_obj_pos.d \
./lvgl/lvgl/src/core/lv_obj_scroll.d \
./lvgl/lvgl/src/core/lv_obj_style.d \
./lvgl/lvgl/src/core/lv_obj_style_gen.d \
./lvgl/lvgl/src/core/lv_obj_tree.d \
./lvgl/lvgl/src/core/lv_refr.d \
./lvgl/lvgl/src/core/lv_theme.d 

OBJS += \
./lvgl/lvgl/src/core/lv_disp.o \
./lvgl/lvgl/src/core/lv_event.o \
./lvgl/lvgl/src/core/lv_group.o \
./lvgl/lvgl/src/core/lv_indev.o \
./lvgl/lvgl/src/core/lv_indev_scroll.o \
./lvgl/lvgl/src/core/lv_obj.o \
./lvgl/lvgl/src/core/lv_obj_class.o \
./lvgl/lvgl/src/core/lv_obj_draw.o \
./lvgl/lvgl/src/core/lv_obj_pos.o \
./lvgl/lvgl/src/core/lv_obj_scroll.o \
./lvgl/lvgl/src/core/lv_obj_style.o \
./lvgl/lvgl/src/core/lv_obj_style_gen.o \
./lvgl/lvgl/src/core/lv_obj_tree.o \
./lvgl/lvgl/src/core/lv_refr.o \
./lvgl/lvgl/src/core/lv_theme.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/core/%.o: ../lvgl/lvgl/src/core/%.c lvgl/lvgl/src/core/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_BAREMETAL -DLV_CONF_INCLUDE_SIMPLE -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\library" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\port\ksdk" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\lvgl\src" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\Inc" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-lvgl-2f-src-2f-core

clean-lvgl-2f-lvgl-2f-src-2f-core:
	-$(RM) ./lvgl/lvgl/src/core/lv_disp.d ./lvgl/lvgl/src/core/lv_disp.o ./lvgl/lvgl/src/core/lv_event.d ./lvgl/lvgl/src/core/lv_event.o ./lvgl/lvgl/src/core/lv_group.d ./lvgl/lvgl/src/core/lv_group.o ./lvgl/lvgl/src/core/lv_indev.d ./lvgl/lvgl/src/core/lv_indev.o ./lvgl/lvgl/src/core/lv_indev_scroll.d ./lvgl/lvgl/src/core/lv_indev_scroll.o ./lvgl/lvgl/src/core/lv_obj.d ./lvgl/lvgl/src/core/lv_obj.o ./lvgl/lvgl/src/core/lv_obj_class.d ./lvgl/lvgl/src/core/lv_obj_class.o ./lvgl/lvgl/src/core/lv_obj_draw.d ./lvgl/lvgl/src/core/lv_obj_draw.o ./lvgl/lvgl/src/core/lv_obj_pos.d ./lvgl/lvgl/src/core/lv_obj_pos.o ./lvgl/lvgl/src/core/lv_obj_scroll.d ./lvgl/lvgl/src/core/lv_obj_scroll.o ./lvgl/lvgl/src/core/lv_obj_style.d ./lvgl/lvgl/src/core/lv_obj_style.o ./lvgl/lvgl/src/core/lv_obj_style_gen.d ./lvgl/lvgl/src/core/lv_obj_style_gen.o ./lvgl/lvgl/src/core/lv_obj_tree.d ./lvgl/lvgl/src/core/lv_obj_tree.o ./lvgl/lvgl/src/core/lv_refr.d ./lvgl/lvgl/src/core/lv_refr.o ./lvgl/lvgl/src/core/lv_theme.d ./lvgl/lvgl/src/core/lv_theme.o

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-core

