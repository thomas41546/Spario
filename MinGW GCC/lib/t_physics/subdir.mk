################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../lib/t_physics/physics.cpp 

OBJS += \
./lib/t_physics/physics.o 

CPP_DEPS += \
./lib/t_physics/physics.d 


# Each subdirectory must supply rules for building sources it contributes
lib/t_physics/%.o: ../lib/t_physics/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


