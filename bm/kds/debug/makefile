################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include utilities/subdir.mk
-include usb/device/source/khci/subdir.mk
-include usb/device/source/subdir.mk
-include startup/subdir.mk
-include sources/ov7670/subdir.mk
-include sources/subdir.mk
-include osa/subdir.mk
-include drivers/subdir.mk
-include board/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
dev_video_flexio_ov7670_lite_bm_frdmk82f.bin \


# All Target
all: dev_video_flexio_ov7670_lite_bm_frdmk82f.elf secondary-outputs

# Tool invocations
dev_video_flexio_ov7670_lite_bm_frdmk82f.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g -T ../MK82FN256xxx15_flash.ld -Xlinker --gc-sections -Wl,-Map,"dev_video_flexio_ov7670_lite_bm_frdmk82f.map" -Wall  --specs=nano.specs          -fno-common  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin  -mapcs  -Xlinker -static  -Xlinker -z  -Xlinker muldefs -o "dev_video_flexio_ov7670_lite_bm_frdmk82f.elf" -Xlinker --start-group $(OBJS) $(USER_OBJS) $(LIBS) -Xlinker --end-group
	@echo 'Finished building target: $@'
	@echo ' '

dev_video_flexio_ov7670_lite_bm_frdmk82f.bin: dev_video_flexio_ov7670_lite_bm_frdmk82f.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary "dev_video_flexio_ov7670_lite_bm_frdmk82f.elf"  "dev_video_flexio_ov7670_lite_bm_frdmk82f.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(S_UPPER_DEPS) dev_video_flexio_ov7670_lite_bm_frdmk82f.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
