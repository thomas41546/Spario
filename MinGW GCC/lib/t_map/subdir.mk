################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/t_map/map.o 

CPP_SRCS += \
../lib/t_map/map.cpp 

OBJS += \
./lib/t_map/map.o 

CPP_DEPS += \
./lib/t_map/map.d 


# Each subdirectory must supply rules for building sources it contributes
lib/t_map/%.o: ../lib/t_map/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


