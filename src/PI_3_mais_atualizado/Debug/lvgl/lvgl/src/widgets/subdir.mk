################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/widgets/lv_arc.c \
../lvgl/lvgl/src/widgets/lv_bar.c \
../lvgl/lvgl/src/widgets/lv_btn.c \
../lvgl/lvgl/src/widgets/lv_btnmatrix.c \
../lvgl/lvgl/src/widgets/lv_canvas.c \
../lvgl/lvgl/src/widgets/lv_checkbox.c \
../lvgl/lvgl/src/widgets/lv_dropdown.c \
../lvgl/lvgl/src/widgets/lv_img.c \
../lvgl/lvgl/src/widgets/lv_label.c \
../lvgl/lvgl/src/widgets/lv_line.c \
../lvgl/lvgl/src/widgets/lv_objx_templ.c \
../lvgl/lvgl/src/widgets/lv_roller.c \
../lvgl/lvgl/src/widgets/lv_slider.c \
../lvgl/lvgl/src/widgets/lv_switch.c \
../lvgl/lvgl/src/widgets/lv_table.c \
../lvgl/lvgl/src/widgets/lv_textarea.c 

C_DEPS += \
./lvgl/lvgl/src/widgets/lv_arc.d \
./lvgl/lvgl/src/widgets/lv_bar.d \
./lvgl/lvgl/src/widgets/lv_btn.d \
./lvgl/lvgl/src/widgets/lv_btnmatrix.d \
./lvgl/lvgl/src/widgets/lv_canvas.d \
./lvgl/lvgl/src/widgets/lv_checkbox.d \
./lvgl/lvgl/src/widgets/lv_dropdown.d \
./lvgl/lvgl/src/widgets/lv_img.d \
./lvgl/lvgl/src/widgets/lv_label.d \
./lvgl/lvgl/src/widgets/lv_line.d \
./lvgl/lvgl/src/widgets/lv_objx_templ.d \
./lvgl/lvgl/src/widgets/lv_roller.d \
./lvgl/lvgl/src/widgets/lv_slider.d \
./lvgl/lvgl/src/widgets/lv_switch.d \
./lvgl/lvgl/src/widgets/lv_table.d \
./lvgl/lvgl/src/widgets/lv_textarea.d 

OBJS += \
./lvgl/lvgl/src/widgets/lv_arc.o \
./lvgl/lvgl/src/widgets/lv_bar.o \
./lvgl/lvgl/src/widgets/lv_btn.o \
./lvgl/lvgl/src/widgets/lv_btnmatrix.o \
./lvgl/lvgl/src/widgets/lv_canvas.o \
./lvgl/lvgl/src/widgets/lv_checkbox.o \
./lvgl/lvgl/src/widgets/lv_dropdown.o \
./lvgl/lvgl/src/widgets/lv_img.o \
./lvgl/lvgl/src/widgets/lv_label.o \
./lvgl/lvgl/src/widgets/lv_line.o \
./lvgl/lvgl/src/widgets/lv_objx_templ.o \
./lvgl/lvgl/src/widgets/lv_roller.o \
./lvgl/lvgl/src/widgets/lv_slider.o \
./lvgl/lvgl/src/widgets/lv_switch.o \
./lvgl/lvgl/src/widgets/lv_table.o \
./lvgl/lvgl/src/widgets/lv_textarea.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/widgets/%.o: ../lvgl/lvgl/src/widgets/%.c lvgl/lvgl/src/widgets/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_BAREMETAL -DLV_CONF_INCLUDE_SIMPLE -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\board" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\utilities" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\drivers" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\device" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\serial_manager" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\lists" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\CMSIS" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\component\uart" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc\infra" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc\setup" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\erpc" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\include" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\library" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls\port\ksdk" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mmcau" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\lvgl" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\lvgl\src" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\lvgl\template" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\source" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mbedtls" -I"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\Inc" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-lvgl-2f-src-2f-widgets

clean-lvgl-2f-lvgl-2f-src-2f-widgets:
	-$(RM) ./lvgl/lvgl/src/widgets/lv_arc.d ./lvgl/lvgl/src/widgets/lv_arc.o ./lvgl/lvgl/src/widgets/lv_bar.d ./lvgl/lvgl/src/widgets/lv_bar.o ./lvgl/lvgl/src/widgets/lv_btn.d ./lvgl/lvgl/src/widgets/lv_btn.o ./lvgl/lvgl/src/widgets/lv_btnmatrix.d ./lvgl/lvgl/src/widgets/lv_btnmatrix.o ./lvgl/lvgl/src/widgets/lv_canvas.d ./lvgl/lvgl/src/widgets/lv_canvas.o ./lvgl/lvgl/src/widgets/lv_checkbox.d ./lvgl/lvgl/src/widgets/lv_checkbox.o ./lvgl/lvgl/src/widgets/lv_dropdown.d ./lvgl/lvgl/src/widgets/lv_dropdown.o ./lvgl/lvgl/src/widgets/lv_img.d ./lvgl/lvgl/src/widgets/lv_img.o ./lvgl/lvgl/src/widgets/lv_label.d ./lvgl/lvgl/src/widgets/lv_label.o ./lvgl/lvgl/src/widgets/lv_line.d ./lvgl/lvgl/src/widgets/lv_line.o ./lvgl/lvgl/src/widgets/lv_objx_templ.d ./lvgl/lvgl/src/widgets/lv_objx_templ.o ./lvgl/lvgl/src/widgets/lv_roller.d ./lvgl/lvgl/src/widgets/lv_roller.o ./lvgl/lvgl/src/widgets/lv_slider.d ./lvgl/lvgl/src/widgets/lv_slider.o ./lvgl/lvgl/src/widgets/lv_switch.d ./lvgl/lvgl/src/widgets/lv_switch.o ./lvgl/lvgl/src/widgets/lv_table.d ./lvgl/lvgl/src/widgets/lv_table.o ./lvgl/lvgl/src/widgets/lv_textarea.d ./lvgl/lvgl/src/widgets/lv_textarea.o

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-widgets

