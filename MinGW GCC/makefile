################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include lib/t_timer/subdir.mk
-include lib/t_sound/subdir.mk
-include lib/t_rect/subdir.mk
-include lib/t_playercontroller/subdir.mk
-include lib/t_physics/subdir.mk
-include lib/t_obj/subdir.mk
-include lib/t_mapobjtrans/subdir.mk
-include lib/t_map/subdir.mk
-include lib/t_keyboard/subdir.mk
-include lib/t_gameobjcontroller/subdir.mk
-include lib/t_filehandling/subdir.mk
-include lib/t_display/subdir.mk
-include lib/t_debug/subdir.mk
-include lib/t_cameracontroller/subdir.mk
-include lib/sdl_collide/subdir.mk
-include lib/p_vector/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ../bin/Spario

# Tool invocations
../bin/Spario: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MinGW C++ Linker'
	C:/Dev-Cpp/bin/mingw32-g++.exe -LC:/Dev-Cpp/lib -o"../bin/Spario" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C++_DEPS)$(OBJS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) ../bin/Spario
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
