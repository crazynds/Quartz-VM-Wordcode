################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/opcodes/WordCoder/Wordcoder.cpp 

OBJS += \
./src/opcodes/WordCoder/Wordcoder.o 

CPP_DEPS += \
./src/opcodes/WordCoder/Wordcoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/opcodes/WordCoder/%.o: ../src/opcodes/WordCoder/%.cpp src/opcodes/WordCoder/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O1 -g3 -Wall -c -fmessage-length=0 -fpermissive -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


