################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/blink.c 

OBJS += \
./src/blink.o 

C_DEPS += \
./src/blink.d 


# Each subdirectory must supply rules for building sources it contributes
src/blink.o: ../src/blink.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/blink.d" -MT"src/blink.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


