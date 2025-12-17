################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/draw/lv_draw_arc.c \
../lvgl/lvgl/src/draw/lv_draw_blend.c \
../lvgl/lvgl/src/draw/lv_draw_img.c \
../lvgl/lvgl/src/draw/lv_draw_label.c \
../lvgl/lvgl/src/draw/lv_draw_line.c \
../lvgl/lvgl/src/draw/lv_draw_mask.c \
../lvgl/lvgl/src/draw/lv_draw_rect.c \
../lvgl/lvgl/src/draw/lv_draw_triangle.c \
../lvgl/lvgl/src/draw/lv_img_buf.c \
../lvgl/lvgl/src/draw/lv_img_cache.c \
../lvgl/lvgl/src/draw/lv_img_decoder.c 

C_DEPS += \
./lvgl/lvgl/src/draw/lv_draw_arc.d \
./lvgl/lvgl/src/draw/lv_draw_blend.d \
./lvgl/lvgl/src/draw/lv_draw_img.d \
./lvgl/lvgl/src/draw/lv_draw_label.d \
./lvgl/lvgl/src/draw/lv_draw_line.d \
./lvgl/lvgl/src/draw/lv_draw_mask.d \
./lvgl/lvgl/src/draw/lv_draw_rect.d \
./lvgl/lvgl/src/draw/lv_draw_triangle.d \
./lvgl/lvgl/src/draw/lv_img_buf.d \
./lvgl/lvgl/src/draw/lv_img_cache.d \
./lvgl/lvgl/src/draw/lv_img_decoder.d 

OBJS += \
./lvgl/lvgl/src/draw/lv_draw_arc.o \
./lvgl/lvgl/src/draw/lv_draw_blend.o \
./lvgl/lvgl/src/draw/lv_draw_img.o \
./lvgl/lvgl/src/draw/lv_draw_label.o \
./lvgl/lvgl/src/draw/lv_draw_line.o \
./lvgl/lvgl/src/draw/lv_draw_mask.o \
./lvgl/lvgl/src/draw/lv_draw_rect.o \
./lvgl/lvgl/src/draw/lv_draw_triangle.o \
./lvgl/lvgl/src/draw/lv_img_buf.o \
./lvgl/lvgl/src/draw/lv_img_cache.o \
./lvgl/lvgl/src/draw/lv_img_decoder.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/draw/%.o: ../lvgl/lvgl/src/draw/%.c lvgl/lvgl/src/draw/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_BAREMETAL -DLV_CONF_INCLUDE_SIMPLE -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\board" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\utilities" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\drivers" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\device" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\serial_manager" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\lists" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\CMSIS" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\uart" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc\infra" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc\setup" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\include" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\library" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\port\ksdk" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mmcau" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\lvgl" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\lvgl\src" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\template" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\source" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\Inc" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-lvgl-2f-src-2f-draw

clean-lvgl-2f-lvgl-2f-src-2f-draw:
	-$(RM) ./lvgl/lvgl/src/draw/lv_draw_arc.d ./lvgl/lvgl/src/draw/lv_draw_arc.o ./lvgl/lvgl/src/draw/lv_draw_blend.d ./lvgl/lvgl/src/draw/lv_draw_blend.o ./lvgl/lvgl/src/draw/lv_draw_img.d ./lvgl/lvgl/src/draw/lv_draw_img.o ./lvgl/lvgl/src/draw/lv_draw_label.d ./lvgl/lvgl/src/draw/lv_draw_label.o ./lvgl/lvgl/src/draw/lv_draw_line.d ./lvgl/lvgl/src/draw/lv_draw_line.o ./lvgl/lvgl/src/draw/lv_draw_mask.d ./lvgl/lvgl/src/draw/lv_draw_mask.o ./lvgl/lvgl/src/draw/lv_draw_rect.d ./lvgl/lvgl/src/draw/lv_draw_rect.o ./lvgl/lvgl/src/draw/lv_draw_triangle.d ./lvgl/lvgl/src/draw/lv_draw_triangle.o ./lvgl/lvgl/src/draw/lv_img_buf.d ./lvgl/lvgl/src/draw/lv_img_buf.o ./lvgl/lvgl/src/draw/lv_img_cache.d ./lvgl/lvgl/src/draw/lv_img_cache.o ./lvgl/lvgl/src/draw/lv_img_decoder.d ./lvgl/lvgl/src/draw/lv_img_decoder.o

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-draw

