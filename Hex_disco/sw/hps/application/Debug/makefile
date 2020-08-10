################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := clean

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Baremetal_Hex_Disco.axf

# Tool invocations
Baremetal_Hex_Disco.axf: $(OBJS)  $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker 7.5.0 [arm-eabi]'
	arm-eabi-gcc  -o "Baremetal_Hex_Disco.axf" $(OBJS) $(LIBS) $(USER_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES) $(OBJS) $(C_DEPS) Baremetal_Hex_Disco.axf 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
