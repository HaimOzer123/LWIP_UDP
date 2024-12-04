################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTG/Src/Tests/ADC_test.c \
../RTG/Src/Tests/I2C_test.c \
../RTG/Src/Tests/SPI_test.c \
../RTG/Src/Tests/Timer_test.c \
../RTG/Src/Tests/UART_test.c 

OBJS += \
./RTG/Src/Tests/ADC_test.o \
./RTG/Src/Tests/I2C_test.o \
./RTG/Src/Tests/SPI_test.o \
./RTG/Src/Tests/Timer_test.o \
./RTG/Src/Tests/UART_test.o 

C_DEPS += \
./RTG/Src/Tests/ADC_test.d \
./RTG/Src/Tests/I2C_test.d \
./RTG/Src/Tests/SPI_test.d \
./RTG/Src/Tests/Timer_test.d \
./RTG/Src/Tests/UART_test.d 


# Each subdirectory must supply rules for building sources it contributes
RTG/Src/Tests/%.o RTG/Src/Tests/%.su RTG/Src/Tests/%.cyclo: ../RTG/Src/Tests/%.c RTG/Src/Tests/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -I"C:/Users/Haim/Desktop/RTED/ARM/prj/LWIP_UDP/RTG/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-RTG-2f-Src-2f-Tests

clean-RTG-2f-Src-2f-Tests:
	-$(RM) ./RTG/Src/Tests/ADC_test.cyclo ./RTG/Src/Tests/ADC_test.d ./RTG/Src/Tests/ADC_test.o ./RTG/Src/Tests/ADC_test.su ./RTG/Src/Tests/I2C_test.cyclo ./RTG/Src/Tests/I2C_test.d ./RTG/Src/Tests/I2C_test.o ./RTG/Src/Tests/I2C_test.su ./RTG/Src/Tests/SPI_test.cyclo ./RTG/Src/Tests/SPI_test.d ./RTG/Src/Tests/SPI_test.o ./RTG/Src/Tests/SPI_test.su ./RTG/Src/Tests/Timer_test.cyclo ./RTG/Src/Tests/Timer_test.d ./RTG/Src/Tests/Timer_test.o ./RTG/Src/Tests/Timer_test.su ./RTG/Src/Tests/UART_test.cyclo ./RTG/Src/Tests/UART_test.d ./RTG/Src/Tests/UART_test.o ./RTG/Src/Tests/UART_test.su

.PHONY: clean-RTG-2f-Src-2f-Tests

