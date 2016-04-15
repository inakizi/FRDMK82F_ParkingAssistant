################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_clock.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_common.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_dmamux.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_edma.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_flexio.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_flexio_camera.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_gpio.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_i2c.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_lpuart.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_mpu.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_sim.c \
/Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_smc.c 

OBJS += \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_dmamux.o \
./drivers/fsl_edma.o \
./drivers/fsl_flexio.o \
./drivers/fsl_flexio_camera.o \
./drivers/fsl_gpio.o \
./drivers/fsl_i2c.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_mpu.o \
./drivers/fsl_sim.o \
./drivers/fsl_smc.o 

C_DEPS += \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_dmamux.d \
./drivers/fsl_edma.d \
./drivers/fsl_flexio.d \
./drivers/fsl_flexio_camera.d \
./drivers/fsl_gpio.d \
./drivers/fsl_i2c.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_mpu.d \
./drivers/fsl_sim.d \
./drivers/fsl_smc.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/fsl_clock.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_clock.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_common.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_common.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_dmamux.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_dmamux.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_edma.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_edma.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_flexio.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_flexio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_flexio_camera.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_flexio_camera.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_gpio.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_i2c.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_lpuart.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_lpuart.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_mpu.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_mpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_sim.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_sim.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/fsl_smc.o: /Users/inakizi/Documents/Projects/NXPContest/Firmware/SDK_2.0_FRDM-K82F/devices/MK82F25615/drivers/fsl_smc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -D_DEBUG=1 -DCPU_MK82FN256VDC15 -DUSB_STACK_BM -DFRDM_K82F -DFREEDOM -I../.. -I../../ov7670 -I../../../../../../../devices/MK82F25615/utilities -I../../../../../../../middleware/usb_1.0.0 -I../../../../../../../middleware/usb_1.0.0/osa -I../../../../../../../middleware/usb_1.0.0/include -I../../../../../../../middleware/usb_1.0.0/device -I../../../../../../../CMSIS/Include -I../../../../.. -I../../../../../../../devices/MK82F25615/drivers -I../../../../../../../devices/MK82F25615 -std=gnu99 -fno-common  -ffreestanding  -fno-builtin  -mapcs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


