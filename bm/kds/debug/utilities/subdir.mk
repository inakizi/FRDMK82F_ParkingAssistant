################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/utilities/fsl_debug_console.c 

OBJS += \
./utilities/fsl_debug_console.o 

C_DEPS += \
./utilities/fsl_debug_console.d 


# Each subdirectory must supply rules for building sources it contributes
utilities/fsl_debug_console.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/utilities/fsl_debug_console.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


