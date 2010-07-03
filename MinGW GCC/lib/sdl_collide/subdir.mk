################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../lib/sdl_collide/SDL_collide.o 

CPP_SRCS += \
../lib/sdl_collide/SDL_collide.cpp 

OBJS += \
./lib/sdl_collide/SDL_collide.o 

CPP_DEPS += \
./lib/sdl_collide/SDL_collide.d 


# Each subdirectory must supply rules for building sources it contributes
lib/sdl_collide/%.o: ../lib/sdl_collide/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	C:/Dev-Cpp/bin/mingw32-c++.exe -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


