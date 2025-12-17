################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include startup/subdir.mk
-include source/subdir.mk
-include mmcau/subdir.mk
-include mbedtls/port/ksdk/subdir.mk
-include mbedtls/library/subdir.mk
-include lvgl/template/subdir.mk
-include lvgl/lvgl/src/widgets/subdir.mk
-include lvgl/lvgl/src/misc/subdir.mk
-include lvgl/lvgl/src/hal/subdir.mk
-include lvgl/lvgl/src/gpu/subdir.mk
-include lvgl/lvgl/src/font/subdir.mk
-include lvgl/lvgl/src/extra/widgets/win/subdir.mk
-include lvgl/lvgl/src/extra/widgets/tileview/subdir.mk
-include lvgl/lvgl/src/extra/widgets/tabview/subdir.mk
-include lvgl/lvgl/src/extra/widgets/spinner/subdir.mk
-include lvgl/lvgl/src/extra/widgets/spinbox/subdir.mk
-include lvgl/lvgl/src/extra/widgets/span/subdir.mk
-include lvgl/lvgl/src/extra/widgets/msgbox/subdir.mk
-include lvgl/lvgl/src/extra/widgets/meter/subdir.mk
-include lvgl/lvgl/src/extra/widgets/list/subdir.mk
-include lvgl/lvgl/src/extra/widgets/led/subdir.mk
-include lvgl/lvgl/src/extra/widgets/keyboard/subdir.mk
-include lvgl/lvgl/src/extra/widgets/imgbtn/subdir.mk
-include lvgl/lvgl/src/extra/widgets/colorwheel/subdir.mk
-include lvgl/lvgl/src/extra/widgets/chart/subdir.mk
-include lvgl/lvgl/src/extra/widgets/calendar/subdir.mk
-include lvgl/lvgl/src/extra/widgets/animimg/subdir.mk
-include lvgl/lvgl/src/extra/themes/mono/subdir.mk
-include lvgl/lvgl/src/extra/themes/default/subdir.mk
-include lvgl/lvgl/src/extra/themes/basic/subdir.mk
-include lvgl/lvgl/src/extra/layouts/grid/subdir.mk
-include lvgl/lvgl/src/extra/layouts/flex/subdir.mk
-include lvgl/lvgl/src/extra/subdir.mk
-include lvgl/lvgl/src/draw/subdir.mk
-include lvgl/lvgl/src/core/subdir.mk
-include drivers/subdir.mk
-include device/subdir.mk
-include component/uart/subdir.mk
-include component/serial_manager/subdir.mk
-include component/lists/subdir.mk
-include board/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := PI_3
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: PI_3.axf

# Tool invocations
PI_3.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\elisa\Documents\portable-oscilloscope-pi3\src\PI_3_mais_atualizado\mmcau\asm-cm4-cm7" -Xlinker -Map="PI_3.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker --sort-section=alignment -Xlinker --cref -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -T PI_3_Debug.ld -o "PI_3.axf" $(OBJS) $(USER_OBJS) $(LIBS) -l_mmcau
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) PI_3.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "PI_3.axf"; # arm-none-eabi-objcopy -v -O binary "PI_3.axf" "PI_3.bin" ; # checksum -p MK64FN1M0xxx12 -d "PI_3.bin";
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
