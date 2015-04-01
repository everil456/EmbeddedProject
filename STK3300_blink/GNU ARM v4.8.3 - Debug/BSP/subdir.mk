################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_bcc.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_stk.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_stk_leds.c \
/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_trace.c 

OBJS += \
./BSP/bsp_bcc.o \
./BSP/bsp_stk.o \
./BSP/bsp_stk_leds.o \
./BSP/bsp_trace.o 

C_DEPS += \
./BSP/bsp_bcc.d \
./BSP/bsp_stk.d \
./BSP/bsp_stk_leds.d \
./BSP/bsp_trace.d 


# Each subdirectory must supply rules for building sources it contributes
BSP/bsp_bcc.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_bcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"BSP/bsp_bcc.d" -MT"BSP/bsp_bcc.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/bsp_stk.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_stk.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"BSP/bsp_stk.d" -MT"BSP/bsp_stk.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/bsp_stk_leds.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_stk_leds.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"BSP/bsp_stk_leds.d" -MT"BSP/bsp_stk_leds.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

BSP/bsp_trace.o: /home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp/bsp_trace.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m3 -mthumb '-DDEBUG_EFM=1' '-DEFM32TG840F32=1' -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/examples/blink" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/emlib/inc" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/EFM32TG_STK3300/config" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/Device/SiliconLabs/EFM32TG/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/CMSIS/Include" -I"/home/mark/Downloads/SimplicityStudio_v3/developer/sdks/efm32/v2/kits/common/bsp" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -std=c99 -MMD -MP -MF"BSP/bsp_trace.d" -MT"BSP/bsp_trace.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


