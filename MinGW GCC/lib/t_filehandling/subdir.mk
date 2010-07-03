################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/t_filehandling/filehandling.o 

CPP_SRCS += \
../lib/t_filehandling/filehandling.cpp 

OBJS += \
./lib/t_filehandling/filehandling.o 

CPP_DEPS += \
./lib/t_filehandling/filehandling.d 


# Each subdirectory must supply rules for building sources it contributes
lib/t_filehandling/%.o: ../lib/t_filehandling/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


