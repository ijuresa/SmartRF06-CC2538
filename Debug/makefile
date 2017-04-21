################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./blinky.obj" \
"./cx2538_setup.obj" \
"./cx2538_startup_ccs.obj" \
"./drivers/adc.obj" \
"./drivers/cpu.obj" \
"./drivers/debug.obj" \
"./drivers/flash.obj" \
"./drivers/gpio.obj" \
"./drivers/gptimer.obj" \
"./drivers/i2c.obj" \
"./drivers/interrupt.obj" \
"./drivers/ioc.obj" \
"./drivers/pka.obj" \
"./drivers/sleepmode.obj" \
"./drivers/ssi.obj" \
"./drivers/sys_ctrl.obj" \
"./drivers/systick.obj" \
"./drivers/uart.obj" \
"./drivers/udma.obj" \
"./drivers/watchdog.obj" \
"../cx2538xf53_ccs.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include drivers/subdir_vars.mk
-include subdir_rules.mk
-include drivers/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
RF06-CC2538.out \

EXE_OUTPUTS__QUOTED += \
"RF06-CC2538.out" \

BIN_OUTPUTS += \
RF06-CC2538.hex \

BIN_OUTPUTS__QUOTED += \
"RF06-CC2538.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "RF06-CC2538.out"

# Tool invocations
RF06-CC2538.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual -z -m"RF06-CC2538.map" --heap_size=0 --stack_size=256 -i"C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" -i"C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/drivers" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" -i"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/lib" --priority --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="RF06-CC2538_linkInfo.xml" --rom_model -o "RF06-CC2538.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

RF06-CC2538.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armhex" --memwidth=8 --romwidth=8 --intel -o "RF06-CC2538.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "blinky.obj" "cx2538_setup.obj" "cx2538_startup_ccs.obj" "drivers\adc.obj" "drivers\cpu.obj" "drivers\debug.obj" "drivers\flash.obj" "drivers\gpio.obj" "drivers\gptimer.obj" "drivers\i2c.obj" "drivers\interrupt.obj" "drivers\ioc.obj" "drivers\pka.obj" "drivers\sleepmode.obj" "drivers\ssi.obj" "drivers\sys_ctrl.obj" "drivers\systick.obj" "drivers\uart.obj" "drivers\udma.obj" "drivers\watchdog.obj" 
	-$(RM) "blinky.d" "cx2538_setup.d" "cx2538_startup_ccs.d" "drivers\adc.d" "drivers\cpu.d" "drivers\debug.d" "drivers\flash.d" "drivers\gpio.d" "drivers\gptimer.d" "drivers\i2c.d" "drivers\interrupt.d" "drivers\ioc.d" "drivers\pka.d" "drivers\sleepmode.d" "drivers\ssi.d" "drivers\sys_ctrl.d" "drivers\systick.d" "drivers\uart.d" "drivers\udma.d" "drivers\watchdog.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

