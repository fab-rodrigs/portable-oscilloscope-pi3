################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/misc/lv_anim.c \
../lvgl/src/misc/lv_anim_timeline.c \
../lvgl/src/misc/lv_area.c \
../lvgl/src/misc/lv_async.c \
../lvgl/src/misc/lv_bidi.c \
../lvgl/src/misc/lv_color.c \
../lvgl/src/misc/lv_fs.c \
../lvgl/src/misc/lv_gc.c \
../lvgl/src/misc/lv_ll.c \
../lvgl/src/misc/lv_log.c \
../lvgl/src/misc/lv_lru.c \
../lvgl/src/misc/lv_math.c \
../lvgl/src/misc/lv_mem.c \
../lvgl/src/misc/lv_printf.c \
../lvgl/src/misc/lv_style.c \
../lvgl/src/misc/lv_style_gen.c \
../lvgl/src/misc/lv_templ.c \
../lvgl/src/misc/lv_timer.c \
../lvgl/src/misc/lv_tlsf.c \
../lvgl/src/misc/lv_txt.c \
../lvgl/src/misc/lv_txt_ap.c \
../lvgl/src/misc/lv_utils.c 

C_DEPS += \
./lvgl/src/misc/lv_anim.d \
./lvgl/src/misc/lv_anim_timeline.d \
./lvgl/src/misc/lv_area.d \
./lvgl/src/misc/lv_async.d \
./lvgl/src/misc/lv_bidi.d \
./lvgl/src/misc/lv_color.d \
./lvgl/src/misc/lv_fs.d \
./lvgl/src/misc/lv_gc.d \
./lvgl/src/misc/lv_ll.d \
./lvgl/src/misc/lv_log.d \
./lvgl/src/misc/lv_lru.d \
./lvgl/src/misc/lv_math.d \
./lvgl/src/misc/lv_mem.d \
./lvgl/src/misc/lv_printf.d \
./lvgl/src/misc/lv_style.d \
./lvgl/src/misc/lv_style_gen.d \
./lvgl/src/misc/lv_templ.d \
./lvgl/src/misc/lv_timer.d \
./lvgl/src/misc/lv_tlsf.d \
./lvgl/src/misc/lv_txt.d \
./lvgl/src/misc/lv_txt_ap.d \
./lvgl/src/misc/lv_utils.d 

OBJS += \
./lvgl/src/misc/lv_anim.o \
./lvgl/src/misc/lv_anim_timeline.o \
./lvgl/src/misc/lv_area.o \
./lvgl/src/misc/lv_async.o \
./lvgl/src/misc/lv_bidi.o \
./lvgl/src/misc/lv_color.o \
./lvgl/src/misc/lv_fs.o \
./lvgl/src/misc/lv_gc.o \
./lvgl/src/misc/lv_ll.o \
./lvgl/src/misc/lv_log.o \
./lvgl/src/misc/lv_lru.o \
./lvgl/src/misc/lv_math.o \
./lvgl/src/misc/lv_mem.o \
./lvgl/src/misc/lv_printf.o \
./lvgl/src/misc/lv_style.o \
./lvgl/src/misc/lv_style_gen.o \
./lvgl/src/misc/lv_templ.o \
./lvgl/src/misc/lv_timer.o \
./lvgl/src/misc/lv_tlsf.o \
./lvgl/src/misc/lv_txt.o \
./lvgl/src/misc/lv_txt_ap.o \
./lvgl/src/misc/lv_utils.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/misc/%.o: ../lvgl/src/misc/%.c lvgl/src/misc/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_FREE_RTOS -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\Inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\freertos_kernel\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\port" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\freertos_plus_tcp\test\cbmc\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\freertos_plus_tcp\tools\tcp_utilities\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\tls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\pkcs11" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\crypto\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\mbedtls_utils" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\common_io\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\common_io\test" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\library" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\utils\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\port\ksdk" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\pkcs11\corePKCS11\source\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\mbedtls_config" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\secure_sockets\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\freertos\include\platform" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include\platform" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include\types" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\freertos\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include\private" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include\types" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\host" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\osa" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\template\sdhc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\osa" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2f-src-2f-misc

clean-lvgl-2f-src-2f-misc:
	-$(RM) ./lvgl/src/misc/lv_anim.d ./lvgl/src/misc/lv_anim.o ./lvgl/src/misc/lv_anim_timeline.d ./lvgl/src/misc/lv_anim_timeline.o ./lvgl/src/misc/lv_area.d ./lvgl/src/misc/lv_area.o ./lvgl/src/misc/lv_async.d ./lvgl/src/misc/lv_async.o ./lvgl/src/misc/lv_bidi.d ./lvgl/src/misc/lv_bidi.o ./lvgl/src/misc/lv_color.d ./lvgl/src/misc/lv_color.o ./lvgl/src/misc/lv_fs.d ./lvgl/src/misc/lv_fs.o ./lvgl/src/misc/lv_gc.d ./lvgl/src/misc/lv_gc.o ./lvgl/src/misc/lv_ll.d ./lvgl/src/misc/lv_ll.o ./lvgl/src/misc/lv_log.d ./lvgl/src/misc/lv_log.o ./lvgl/src/misc/lv_lru.d ./lvgl/src/misc/lv_lru.o ./lvgl/src/misc/lv_math.d ./lvgl/src/misc/lv_math.o ./lvgl/src/misc/lv_mem.d ./lvgl/src/misc/lv_mem.o ./lvgl/src/misc/lv_printf.d ./lvgl/src/misc/lv_printf.o ./lvgl/src/misc/lv_style.d ./lvgl/src/misc/lv_style.o ./lvgl/src/misc/lv_style_gen.d ./lvgl/src/misc/lv_style_gen.o ./lvgl/src/misc/lv_templ.d ./lvgl/src/misc/lv_templ.o ./lvgl/src/misc/lv_timer.d ./lvgl/src/misc/lv_timer.o ./lvgl/src/misc/lv_tlsf.d ./lvgl/src/misc/lv_tlsf.o ./lvgl/src/misc/lv_txt.d ./lvgl/src/misc/lv_txt.o ./lvgl/src/misc/lv_txt_ap.d ./lvgl/src/misc/lv_txt_ap.o ./lvgl/src/misc/lv_utils.d ./lvgl/src/misc/lv_utils.o

.PHONY: clean-lvgl-2f-src-2f-misc

