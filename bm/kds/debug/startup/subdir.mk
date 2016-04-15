################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/system_MK82F25615.c 

S_UPPER_SRCS += \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/gcc/startup_MK82F25615.S 

OBJS += \
./startup/startup_MK82F25615.o \
./startup/system_MK82F25615.o 

C_DEPS += \
./startup/system_MK82F25615.d 

S_UPPER_DEPS += \
./startup/startup_MK82F25615.d 


# Each subdirectory must supply rules for building sources it contributes
startup/startup_MK82F25615.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/gcc/startup_MK82F25615.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -x assembler-with-cpp -DDEBUG -D__STARTUP_CLEAR_BSS -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup/system_MK82F25615.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/system_MK82F25615.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


