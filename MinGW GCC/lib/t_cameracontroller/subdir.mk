################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/t_cameracontroller/cameracontroller.o 

CPP_SRCS += \
../lib/t_cameracontroller/cameracontroller.cpp 

OBJS += \
./lib/t_cameracontroller/cameracontroller.o 

CPP_DEPS += \
./lib/t_cameracontroller/cameracontroller.d 


# Each subdirectory must supply rules for building sources it contributes
lib/t_cameracontroller/%.o: ../lib/t_cameracontroller/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


