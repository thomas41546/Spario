################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/t_obj/obj.o 

CPP_SRCS += \
../lib/t_obj/obj.cpp 

OBJS += \
./lib/t_obj/obj.o 

CPP_DEPS += \
./lib/t_obj/obj.d 


# Each subdirectory must supply rules for building sources it contributes
lib/t_obj/%.o: ../lib/t_obj/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


