################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/AVLIF.cpp \
../src/AVLTree.cpp \
../src/Document.cpp \
../src/DocumentParser.cpp \
../src/HashIF.cpp \
../src/HashTab.cpp \
../src/IndexIF.cpp \
../src/QueryProcessor.cpp \
../src/StressTester.cpp \
../src/UserInterface.cpp \
../src/Word.cpp \
../src/main.cpp \
../src/tinyxml2.cpp 

OBJS += \
./src/AVLIF.o \
./src/AVLTree.o \
./src/Document.o \
./src/DocumentParser.o \
./src/HashIF.o \
./src/HashTab.o \
./src/IndexIF.o \
./src/QueryProcessor.o \
./src/StressTester.o \
./src/UserInterface.o \
./src/Word.o \
./src/main.o \
./src/tinyxml2.o 

CPP_DEPS += \
./src/AVLIF.d \
./src/AVLTree.d \
./src/Document.d \
./src/DocumentParser.d \
./src/HashIF.d \
./src/HashTab.d \
./src/IndexIF.d \
./src/QueryProcessor.d \
./src/StressTester.d \
./src/UserInterface.d \
./src/Word.d \
./src/main.d \
./src/tinyxml2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -lpthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


