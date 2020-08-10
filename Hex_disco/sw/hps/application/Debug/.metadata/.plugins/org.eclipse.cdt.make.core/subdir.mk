################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../.metadata/.plugins/org.eclipse.cdt.make.core/specs.c 

OBJS += \
./.metadata/.plugins/org.eclipse.cdt.make.core/specs.o 

C_DEPS += \
./.metadata/.plugins/org.eclipse.cdt.make.core/specs.d 


# Each subdirectory must supply rules for building sources it contributes
.metadata/.plugins/org.eclipse.cdt.make.core/%.o: ../.metadata/.plugins/org.eclipse.cdt.make.core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler 7.5.0 [arm-eabi]'
	arm-eabi-gcc -Dsoc_cv_av -I"/home/tijmen/Documents/Baremetal_Hex_Disco/sw/hps/application/inc" -I/home/tijmen/intelFPGA/20.1/embedded/ip/altera/hps/altera_hps/hwlib/include -I/home/tijmen/intelFPGA/20.1/embedded/ip/altera/hps/altera_hps/hwlib/include/soc_cv_av -O0 -g -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


