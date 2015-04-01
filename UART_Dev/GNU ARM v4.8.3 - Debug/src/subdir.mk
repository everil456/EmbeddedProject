################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/em_cmu.c \
../src/em_emu.c \
../src/em_gpio.c \
../src/em_leuart.c \
../src/em_timer.c \
../src/em_usart.c \
../src/main.c \
../src/usart.c 

OBJS += \
./src/em_cmu.o \
./src/em_emu.o \
./src/em_gpio.o \
./src/em_leuart.o \
./src/em_timer.o \
./src/em_usart.o \
./src/main.o \
./src/usart.o 

C_DEPS += \
./src/em_cmu.d \
./src/em_emu.d \
./src/em_gpio.d \
./src/em_leuart.d \
./src/em_timer.d \
./src/em_usart.d \
./src/main.d \
./src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
src/em_cmu.o: ../src/em_cmu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/em_cmu.d" -MT"src/em_cmu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/em_emu.o: ../src/em_emu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/em_emu.d" -MT"src/em_emu.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/em_gpio.o: ../src/em_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/em_gpio.d" -MT"src/em_gpio.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/em_leuart.o: ../src/em_leuart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/em_leuart.d" -MT"src/em_leuart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/em_timer.o: ../src/em_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/em_timer.d" -MT"src/em_timer.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/em_usart.o: ../src/em_usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/em_usart.d" -MT"src/em_usart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/main.d" -MT"src/main.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/usart.o: ../src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DEFM32TG110F32=1' '-DDEBUG=1' -I"/home/mark/SimplicityStudio/v3_workspace/UART_Dev/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/drivers" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"src/usart.d" -MT"src/usart.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


