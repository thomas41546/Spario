################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/t_playercontroller/playercontroller.o 

CPP_SRCS += \
../lib/t_playercontroller/playercontroller.cpp 

OBJS += \
./lib/t_playercontroller/playercontroller.o 

CPP_DEPS += \
./lib/t_playercontroller/playercontroller.d 


# Each subdirectory must supply rules for building sources it contributes
lib/t_playercontroller/%.o: ../lib/t_playercontroller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


