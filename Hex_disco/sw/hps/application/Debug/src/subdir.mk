################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/buttons.c \
../src/hexDisco.c 

OBJS += \
./src/buttons.o \
./src/hexDisco.o 

C_DEPS += \
./src/buttons.d \
./src/hexDisco.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 7.5.0 [arm-eabi]'
	arm-eabi-gcc -Dsoc_cv_av -I"/home/tijmen/Documents/Baremetal_Hex_Disco/sw/hps/application/inc" -I/home/tijmen/intelFPGA/20.1/embedded/ip/altera/hps/altera_hps/hwlib/include -I/home/tijmen/intelFPGA/20.1/embedded/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

