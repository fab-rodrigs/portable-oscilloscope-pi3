################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl-8.3.10/tests/src/test_cases/_test_template.c \
../lvgl-8.3.10/tests/src/test_cases/test_arc.c \
../lvgl-8.3.10/tests/src/test_cases/test_bar.c \
../lvgl-8.3.10/tests/src/test_cases/test_checkbox.c \
../lvgl-8.3.10/tests/src/test_cases/test_config.c \
../lvgl-8.3.10/tests/src/test_cases/test_demo_stress.c \
../lvgl-8.3.10/tests/src/test_cases/test_demo_widgets.c \
../lvgl-8.3.10/tests/src/test_cases/test_dropdown.c \
../lvgl-8.3.10/tests/src/test_cases/test_event.c \
../lvgl-8.3.10/tests/src/test_cases/test_font_loader.c \
../lvgl-8.3.10/tests/src/test_cases/test_fs.c \
../lvgl-8.3.10/tests/src/test_cases/test_line.c \
../lvgl-8.3.10/tests/src/test_cases/test_mem.c \
../lvgl-8.3.10/tests/src/test_cases/test_obj_tree.c \
../lvgl-8.3.10/tests/src/test_cases/test_slider.c \
../lvgl-8.3.10/tests/src/test_cases/test_snapshot.c \
../lvgl-8.3.10/tests/src/test_cases/test_style.c \
../lvgl-8.3.10/tests/src/test_cases/test_switch.c \
../lvgl-8.3.10/tests/src/test_cases/test_table.c \
../lvgl-8.3.10/tests/src/test_cases/test_textarea.c \
../lvgl-8.3.10/tests/src/test_cases/test_txt.c 

C_DEPS += \
./lvgl-8.3.10/tests/src/test_cases/_test_template.d \
./lvgl-8.3.10/tests/src/test_cases/test_arc.d \
./lvgl-8.3.10/tests/src/test_cases/test_bar.d \
./lvgl-8.3.10/tests/src/test_cases/test_checkbox.d \
./lvgl-8.3.10/tests/src/test_cases/test_config.d \
./lvgl-8.3.10/tests/src/test_cases/test_demo_stress.d \
./lvgl-8.3.10/tests/src/test_cases/test_demo_widgets.d \
./lvgl-8.3.10/tests/src/test_cases/test_dropdown.d \
./lvgl-8.3.10/tests/src/test_cases/test_event.d \
./lvgl-8.3.10/tests/src/test_cases/test_font_loader.d \
./lvgl-8.3.10/tests/src/test_cases/test_fs.d \
./lvgl-8.3.10/tests/src/test_cases/test_line.d \
./lvgl-8.3.10/tests/src/test_cases/test_mem.d \
./lvgl-8.3.10/tests/src/test_cases/test_obj_tree.d \
./lvgl-8.3.10/tests/src/test_cases/test_slider.d \
./lvgl-8.3.10/tests/src/test_cases/test_snapshot.d \
./lvgl-8.3.10/tests/src/test_cases/test_style.d \
./lvgl-8.3.10/tests/src/test_cases/test_switch.d \
./lvgl-8.3.10/tests/src/test_cases/test_table.d \
./lvgl-8.3.10/tests/src/test_cases/test_textarea.d \
./lvgl-8.3.10/tests/src/test_cases/test_txt.d 

OBJS += \
./lvgl-8.3.10/tests/src/test_cases/_test_template.o \
./lvgl-8.3.10/tests/src/test_cases/test_arc.o \
./lvgl-8.3.10/tests/src/test_cases/test_bar.o \
./lvgl-8.3.10/tests/src/test_cases/test_checkbox.o \
./lvgl-8.3.10/tests/src/test_cases/test_config.o \
./lvgl-8.3.10/tests/src/test_cases/test_demo_stress.o \
./lvgl-8.3.10/tests/src/test_cases/test_demo_widgets.o \
./lvgl-8.3.10/tests/src/test_cases/test_dropdown.o \
./lvgl-8.3.10/tests/src/test_cases/test_event.o \
./lvgl-8.3.10/tests/src/test_cases/test_font_loader.o \
./lvgl-8.3.10/tests/src/test_cases/test_fs.o \
./lvgl-8.3.10/tests/src/test_cases/test_line.o \
./lvgl-8.3.10/tests/src/test_cases/test_mem.o \
./lvgl-8.3.10/tests/src/test_cases/test_obj_tree.o \
./lvgl-8.3.10/tests/src/test_cases/test_slider.o \
./lvgl-8.3.10/tests/src/test_cases/test_snapshot.o \
./lvgl-8.3.10/tests/src/test_cases/test_style.o \
./lvgl-8.3.10/tests/src/test_cases/test_switch.o \
./lvgl-8.3.10/tests/src/test_cases/test_table.o \
./lvgl-8.3.10/tests/src/test_cases/test_textarea.o \
./lvgl-8.3.10/tests/src/test_cases/test_txt.o 


# Each subdirectory must supply rules for building sources it contributes
lvgl-8.3.10/tests/src/test_cases/%.o: ../lvgl-8.3.10/tests/src/test_cases/%.c lvgl-8.3.10/tests/src/test_cases/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DLV_CONF_INCLUDE_SIMPLE -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_FREE_RTOS -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\Inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\freertos_kernel\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\port" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\freertos_plus_tcp\test\cbmc\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\freertos_plus_tcp\tools\tcp_utilities\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\tls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\pkcs11" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\crypto\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\mbedtls_utils" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\common_io\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\common_io\test" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\library" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\freertos_plus\standard\utils\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mbedtls\port\ksdk" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\pkcs11\corePKCS11\source\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\3rdparty\mbedtls_config" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\secure_sockets\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\freertos\include\platform" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include\platform" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include\types" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\freertos\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\abstractions\platform\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include\private" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\libraries\c_sdk\standard\common\include\types" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\host" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\osa" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\template\sdhc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\osa" -O2 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-lvgl-2d-8-2e-3-2e-10-2f-tests-2f-src-2f-test_cases

clean-lvgl-2d-8-2e-3-2e-10-2f-tests-2f-src-2f-test_cases:
	-$(RM) ./lvgl-8.3.10/tests/src/test_cases/_test_template.d ./lvgl-8.3.10/tests/src/test_cases/_test_template.o ./lvgl-8.3.10/tests/src/test_cases/test_arc.d ./lvgl-8.3.10/tests/src/test_cases/test_arc.o ./lvgl-8.3.10/tests/src/test_cases/test_bar.d ./lvgl-8.3.10/tests/src/test_cases/test_bar.o ./lvgl-8.3.10/tests/src/test_cases/test_checkbox.d ./lvgl-8.3.10/tests/src/test_cases/test_checkbox.o ./lvgl-8.3.10/tests/src/test_cases/test_config.d ./lvgl-8.3.10/tests/src/test_cases/test_config.o ./lvgl-8.3.10/tests/src/test_cases/test_demo_stress.d ./lvgl-8.3.10/tests/src/test_cases/test_demo_stress.o ./lvgl-8.3.10/tests/src/test_cases/test_demo_widgets.d ./lvgl-8.3.10/tests/src/test_cases/test_demo_widgets.o ./lvgl-8.3.10/tests/src/test_cases/test_dropdown.d ./lvgl-8.3.10/tests/src/test_cases/test_dropdown.o ./lvgl-8.3.10/tests/src/test_cases/test_event.d ./lvgl-8.3.10/tests/src/test_cases/test_event.o ./lvgl-8.3.10/tests/src/test_cases/test_font_loader.d ./lvgl-8.3.10/tests/src/test_cases/test_font_loader.o ./lvgl-8.3.10/tests/src/test_cases/test_fs.d ./lvgl-8.3.10/tests/src/test_cases/test_fs.o ./lvgl-8.3.10/tests/src/test_cases/test_line.d ./lvgl-8.3.10/tests/src/test_cases/test_line.o ./lvgl-8.3.10/tests/src/test_cases/test_mem.d ./lvgl-8.3.10/tests/src/test_cases/test_mem.o ./lvgl-8.3.10/tests/src/test_cases/test_obj_tree.d ./lvgl-8.3.10/tests/src/test_cases/test_obj_tree.o ./lvgl-8.3.10/tests/src/test_cases/test_slider.d ./lvgl-8.3.10/tests/src/test_cases/test_slider.o ./lvgl-8.3.10/tests/src/test_cases/test_snapshot.d ./lvgl-8.3.10/tests/src/test_cases/test_snapshot.o ./lvgl-8.3.10/tests/src/test_cases/test_style.d ./lvgl-8.3.10/tests/src/test_cases/test_style.o ./lvgl-8.3.10/tests/src/test_cases/test_switch.d ./lvgl-8.3.10/tests/src/test_cases/test_switch.o ./lvgl-8.3.10/tests/src/test_cases/test_table.d ./lvgl-8.3.10/tests/src/test_cases/test_table.o ./lvgl-8.3.10/tests/src/test_cases/test_textarea.d ./lvgl-8.3.10/tests/src/test_cases/test_textarea.o ./lvgl-8.3.10/tests/src/test_cases/test_txt.d ./lvgl-8.3.10/tests/src/test_cases/test_txt.o

.PHONY: clean-lvgl-2d-8-2e-3-2e-10-2f-tests-2f-src-2f-test_cases

