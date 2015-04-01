################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_assert.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_cmu.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_emu.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_gpio.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_system.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_usart.c 

OBJS += \
./emlib/em_assert.o \
./emlib/em_cmu.o \
./emlib/em_emu.o \
./emlib/em_gpio.o \
./emlib/em_system.o \
./emlib/em_usart.o 

C_DEPS += \
./emlib/em_assert.d \
./emlib/em_cmu.d \
./emlib/em_emu.d \
./emlib/em_gpio.d \
./emlib/em_system.d \
./emlib/em_usart.d 


# Each subdirectory must supply rules for building sources it contributes
emlib/em_assert.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_assert.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_assert.d" -MT"emlib/em_assert.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_cmu.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_cmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_cmu.d" -MT"emlib/em_cmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_emu.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_emu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_emu.d" -MT"emlib/em_emu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_gpio.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_gpio.d" -MT"emlib/em_gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_system.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_system.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_system.d" -MT"emlib/em_system.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emlib/em_usart.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/src/em_usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"emlib/em_usart.d" -MT"emlib/em_usart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


