################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BARE_APP/001LED_TOGGLE.c 

OBJS += \
./BARE_APP/001LED_TOGGLE.o 

C_DEPS += \
./BARE_APP/001LED_TOGGLE.d 


# Each subdirectory must supply rules for building sources it contributes
BARE_APP/%.o BARE_APP/%.su: ../BARE_APP/%.c BARE_APP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BARE_APP

clean-BARE_APP:
	-$(RM) ./BARE_APP/001LED_TOGGLE.d ./BARE_APP/001LED_TOGGLE.o ./BARE_APP/001LED_TOGGLE.su

.PHONY: clean-BARE_APP

