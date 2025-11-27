################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/freertos_kernel/croutine.c \
../FreeRTOS/freertos_kernel/event_groups.c \
../FreeRTOS/freertos_kernel/list.c \
../FreeRTOS/freertos_kernel/queue.c \
../FreeRTOS/freertos_kernel/stream_buffer.c \
../FreeRTOS/freertos_kernel/tasks.c \
../FreeRTOS/freertos_kernel/timers.c 

C_DEPS += \
./FreeRTOS/freertos_kernel/croutine.d \
./FreeRTOS/freertos_kernel/event_groups.d \
./FreeRTOS/freertos_kernel/list.d \
./FreeRTOS/freertos_kernel/queue.d \
./FreeRTOS/freertos_kernel/stream_buffer.d \
./FreeRTOS/freertos_kernel/tasks.d \
./FreeRTOS/freertos_kernel/timers.d 

OBJS += \
./FreeRTOS/freertos_kernel/croutine.o \
./FreeRTOS/freertos_kernel/event_groups.o \
./FreeRTOS/freertos_kernel/list.o \
./FreeRTOS/freertos_kernel/queue.o \
./FreeRTOS/freertos_kernel/stream_buffer.o \
./FreeRTOS/freertos_kernel/tasks.o \
./FreeRTOS/freertos_kernel/timers.o 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/freertos_kernel/%.o: ../FreeRTOS/freertos_kernel/%.c FreeRTOS/freertos_kernel/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MK64FN1M0VLL12 -DCPU_MK64FN1M0VLL12_cm4 -DSDK_OS_BAREMETAL -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DLV_CONF_INCLUDE_SIMPLE -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__NEWLIB__ -DMBEDTLS_CONFIG_FILE='"ksdk_mbedtls_config.h"' -DSDK_OS_FREE_RTOS -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\board" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\Inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\utilities" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\device" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\serial_manager" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\lists" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\CMSIS" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\uart" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl\lvgl\src" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\lvgl\template" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\drivers\freertos" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\source" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\port" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\infra" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\setup" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc\transports" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\erpc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\mmcau" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\host" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\osa" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\template\sdhc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\sdmmc\inc" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\component\osa" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\FreeRTOS\freertos_kernel\portable\GCC\ARM_CM4F" -I"C:\Users\Acer-PC\Documents\MCUXpressoIDE_25.6.136\workspace\PI_3\FreeRTOS\freertos_kernel\include" -O0 -fno-common -g3 -gdwarf-4 -Wall -c -ffunction-sections -fdata-sections -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__NEWLIB__ -fstack-usage -specs=nano.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-FreeRTOS-2f-freertos_kernel

clean-FreeRTOS-2f-freertos_kernel:
	-$(RM) ./FreeRTOS/freertos_kernel/croutine.d ./FreeRTOS/freertos_kernel/croutine.o ./FreeRTOS/freertos_kernel/event_groups.d ./FreeRTOS/freertos_kernel/event_groups.o ./FreeRTOS/freertos_kernel/list.d ./FreeRTOS/freertos_kernel/list.o ./FreeRTOS/freertos_kernel/queue.d ./FreeRTOS/freertos_kernel/queue.o ./FreeRTOS/freertos_kernel/stream_buffer.d ./FreeRTOS/freertos_kernel/stream_buffer.o ./FreeRTOS/freertos_kernel/tasks.d ./FreeRTOS/freertos_kernel/tasks.o ./FreeRTOS/freertos_kernel/timers.d ./FreeRTOS/freertos_kernel/timers.o

.PHONY: clean-FreeRTOS-2f-freertos_kernel

