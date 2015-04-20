################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/efm32tg/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RealEmbeddedProject.axf

# Tool invocations
RealEmbeddedProject.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "RealEmbeddedProject.ld" -Xlinker --gc-sections -Xlinker -Map="RealEmbeddedProject.map" --specs=nano.specs -o RealEmbeddedProject.axf "./src/CommProtocol.o" "./src/InitDevice.o" "./src/em_cmu.o" "./src/em_emu.o" "./src/em_gpio.o" "./src/em_leuart.o" "./src/em_timer.o" "./src/em_usart.o" "./src/main.o" "./src/sl.o" "./src/test.o" "./src/usart.o" "./emlib/em_system.o" "./CMSIS/efm32tg/startup_efm32tg.o" "./CMSIS/efm32tg/system_efm32tg.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: RealEmbeddedProject.hex'
	arm-none-eabi-objcopy -O ihex "RealEmbeddedProject.axf" "RealEmbeddedProject.hex"
	@echo ' '

	@echo 'Building bin file: RealEmbeddedProject.bin'
	arm-none-eabi-objcopy -O binary "RealEmbeddedProject.axf" "RealEmbeddedProject.bin"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "RealEmbeddedProject.axf"
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) RealEmbeddedProject.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
