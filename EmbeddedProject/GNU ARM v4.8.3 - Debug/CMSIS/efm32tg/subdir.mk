################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c 

S_UPPER_SRCS += \
/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/GCC/startup_efm32tg.S 

OBJS += \
./CMSIS/efm32tg/startup_efm32tg.o \
./CMSIS/efm32tg/system_efm32tg.o 

C_DEPS += \
./CMSIS/efm32tg/system_efm32tg.d 


# Each subdirectory must supply rules for building sources it contributes
CMSIS/efm32tg/startup_efm32tg.o: /Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/GCC/startup_efm32tg.S
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM Assembler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb -c -x assembler-with-cpp -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" '-DEFM32TG110F32=1' -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

CMSIS/efm32tg/system_efm32tg.o: /Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Source/system_efm32tg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/Applications/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"CMSIS/efm32tg/system_efm32tg.d" -MT"CMSIS/efm32tg/system_efm32tg.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


