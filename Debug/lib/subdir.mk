################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/Debounce.cpp \
../lib/StepMotor.cpp 

OBJS += \
./lib/Debounce.o \
./lib/StepMotor.o 

CPP_DEPS += \
./lib/Debounce.d \
./lib/StepMotor.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o lib/%.su lib/%.cyclo: ../lib/%.cpp lib/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -IC:/Users/Dom/STM32CubeIDE/workspace_1.13.0/ABC/lib -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lib

clean-lib:
	-$(RM) ./lib/Debounce.cyclo ./lib/Debounce.d ./lib/Debounce.o ./lib/Debounce.su ./lib/StepMotor.cyclo ./lib/StepMotor.d ./lib/StepMotor.o ./lib/StepMotor.su

.PHONY: clean-lib

