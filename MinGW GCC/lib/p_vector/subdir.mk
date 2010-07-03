################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/p_vector/point.o \
../lib/p_vector/vector.o 

CPP_SRCS += \
../lib/p_vector/point.cpp \
../lib/p_vector/vector.cpp 

OBJS += \
./lib/p_vector/point.o \
./lib/p_vector/vector.o 

CPP_DEPS += \
./lib/p_vector/point.d \
./lib/p_vector/vector.d 


# Each subdirectory must supply rules for building sources it contributes
lib/p_vector/%.o: ../lib/p_vector/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


