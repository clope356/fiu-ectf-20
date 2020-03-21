################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/main.c \
../src/platform.c \
../src/sha-256.c \
../src/util.c 

OBJS += \
./src/main.o \
./src/platform.o \
./src/sha-256.o \
./src/util.o 

C_DEPS += \
./src/main.d \
./src/platform.d \
./src/sha-256.d \
./src/util.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O3 -g3 -I"/home/vagrant/ectf10/2020-ectf-insecure-example/mb/drm_audio_fw_bsp/microblaze_0/include" -c -fmessage-length=0 -MT"$@" -I"/home/vagrant/ectf10/2020-ectf-insecure-example/mb/drm_audio_fw_bsp/microblaze_0/include" -mlittle-endian -mxl-barrel-shift -mcpu=v10.0 -mno-xl-soft-mul -mxl-multiply-high -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


