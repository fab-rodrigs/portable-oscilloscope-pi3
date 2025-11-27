################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/lvgl/src/misc/lv_anim.c \
../lvgl/lvgl/src/misc/lv_area.c \
../lvgl/lvgl/src/misc/lv_async.c \
../lvgl/lvgl/src/misc/lv_bidi.c \
../lvgl/lvgl/src/misc/lv_color.c \
../lvgl/lvgl/src/misc/lv_fs.c \
../lvgl/lvgl/src/misc/lv_gc.c \
../lvgl/lvgl/src/misc/lv_ll.c \
../lvgl/lvgl/src/misc/lv_log.c \
../lvgl/lvgl/src/misc/lv_math.c \
../lvgl/lvgl/src/misc/lv_mem.c \
../lvgl/lvgl/src/misc/lv_printf.c \
../lvgl/lvgl/src/misc/lv_style.c \
../lvgl/lvgl/src/misc/lv_style_gen.c \
../lvgl/lvgl/src/misc/lv_templ.c \
../lvgl/lvgl/src/misc/lv_timer.c \
../lvgl/lvgl/src/misc/lv_tlsf.c \
../lvgl/lvgl/src/misc/lv_txt.c \
../lvgl/lvgl/src/misc/lv_txt_ap.c \
../lvgl/lvgl/src/misc/lv_utils.c 

C_DEPS += \
./lvgl/lvgl/src/misc/lv_anim.d \
./lvgl/lvgl/src/misc/lv_area.d \
./lvgl/lvgl/src/misc/lv_async.d \
./lvgl/lvgl/src/misc/lv_bidi.d \
./lvgl/lvgl/src/misc/lv_color.d \
./lvgl/lvgl/src/misc/lv_fs.d \
./lvgl/lvgl/src/misc/lv_gc.d \
./lvgl/lvgl/src/misc/lv_ll.d \
./lvgl/lvgl/src/misc/lv_log.d \
./lvgl/lvgl/src/misc/lv_math.d \
./lvgl/lvgl/src/misc/lv_mem.d \
./lvgl/lvgl/src/misc/lv_printf.d \
./lvgl/lvgl/src/misc/lv_style.d \
./lvgl/lvgl/src/misc/lv_style_gen.d \
./lvgl/lvgl/src/misc/lv_templ.d \
./lvgl/lvgl/src/misc/lv_timer.d \
./lvgl/lvgl/src/misc/lv_tlsf.d \
./lvgl/lvgl/src/misc/lv_txt.d \
./lvgl/lvgl/src/misc/lv_txt_ap.d \
./lvgl/lvgl/src/misc/lv_utils.d 

OBJS += \
./lvgl/lvgl/src/misc/lv_anim.o \
./lvgl/lvgl/src/misc/lv_area.o \
./lvgl/lvgl/src/misc/lv_async.o \
./lvgl/lvgl/src/misc/lv_bidi.o \
./lvgl/lvgl/src/misc/lv_color.o \
./lvgl/lvgl/src/misc/lv_fs.o \
./lvgl/lvgl/src/misc/lv_gc.o \
./lvgl/lvgl/src/misc/lv_ll.o \
./lvgl/lvgl/src/misc/lv_log.o \
./lvgl/lvgl/src/misc/lv_math.o \
./lvgl/lvgl/src/misc/lv_mem.o \
./lvgl/lvgl/src/misc/lv_printf.o \
./lvgl/lvgl/src/misc/lv_style.o \
./lvgl/lvgl/src/misc/lv_style_gen.o \
./lvgl/lvgl/src/misc/lv_templ.o \
./lvgl/lvgl/src/misc/lv_timer.o \
./lvgl/lvgl/src/misc/lv_tlsf.o \
./lvgl/lvgl/src/misc/lv_txt.o \
./lvgl/lvgl/src/misc/lv_txt_ap.o \
./lvgl/lvgl/src/misc/lv_utils.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/lvgl/src/misc/%.o: ../lvgl/lvgl/src/misc/%.c lvgl/lvgl/src/misc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_BAREMETAL -DLV_CONF_INCLUDE_SIMPLE -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\library" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls\port\ksdk" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\lvgl\src" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\lvgl\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\mbedtls" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3_mais_atualizado\Inc" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-lvgl-2f-src-2f-misc

clean-lvgl-2f-lvgl-2f-src-2f-misc:
	-$(RM) ./lvgl/lvgl/src/misc/lv_anim.d ./lvgl/lvgl/src/misc/lv_anim.o ./lvgl/lvgl/src/misc/lv_area.d ./lvgl/lvgl/src/misc/lv_area.o ./lvgl/lvgl/src/misc/lv_async.d ./lvgl/lvgl/src/misc/lv_async.o ./lvgl/lvgl/src/misc/lv_bidi.d ./lvgl/lvgl/src/misc/lv_bidi.o ./lvgl/lvgl/src/misc/lv_color.d ./lvgl/lvgl/src/misc/lv_color.o ./lvgl/lvgl/src/misc/lv_fs.d ./lvgl/lvgl/src/misc/lv_fs.o ./lvgl/lvgl/src/misc/lv_gc.d ./lvgl/lvgl/src/misc/lv_gc.o ./lvgl/lvgl/src/misc/lv_ll.d ./lvgl/lvgl/src/misc/lv_ll.o ./lvgl/lvgl/src/misc/lv_log.d ./lvgl/lvgl/src/misc/lv_log.o ./lvgl/lvgl/src/misc/lv_math.d ./lvgl/lvgl/src/misc/lv_math.o ./lvgl/lvgl/src/misc/lv_mem.d ./lvgl/lvgl/src/misc/lv_mem.o ./lvgl/lvgl/src/misc/lv_printf.d ./lvgl/lvgl/src/misc/lv_printf.o ./lvgl/lvgl/src/misc/lv_style.d ./lvgl/lvgl/src/misc/lv_style.o ./lvgl/lvgl/src/misc/lv_style_gen.d ./lvgl/lvgl/src/misc/lv_style_gen.o ./lvgl/lvgl/src/misc/lv_templ.d ./lvgl/lvgl/src/misc/lv_templ.o ./lvgl/lvgl/src/misc/lv_timer.d ./lvgl/lvgl/src/misc/lv_timer.o ./lvgl/lvgl/src/misc/lv_tlsf.d ./lvgl/lvgl/src/misc/lv_tlsf.o ./lvgl/lvgl/src/misc/lv_txt.d ./lvgl/lvgl/src/misc/lv_txt.o ./lvgl/lvgl/src/misc/lv_txt_ap.d ./lvgl/lvgl/src/misc/lv_txt_ap.o ./lvgl/lvgl/src/misc/lv_utils.d ./lvgl/lvgl/src/misc/lv_utils.o

.PHONY: clean-lvgl-2f-lvgl-2f-src-2f-misc

