################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/One\ bumb.c 

OBJS += \
./src/One\ bumb.o 

C_DEPS += \
./src/One\ bumb.d 


# Each subdirectory must supply rules for building sources it contributes
src/One\ bumb.o: ../src/One\ bumb.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/One bumb.d" -MT"src/One\ bumb.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


