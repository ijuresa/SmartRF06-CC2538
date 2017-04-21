################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/adc.obj: ../drivers/adc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/adc.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/cpu.obj: ../drivers/cpu.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/cpu.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/debug.obj: ../drivers/debug.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/debug.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/flash.obj: ../drivers/flash.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/flash.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/gpio.obj: ../drivers/gpio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/gpio.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/gptimer.obj: ../drivers/gptimer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/gptimer.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/i2c.obj: ../drivers/i2c.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/i2c.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/interrupt.obj: ../drivers/interrupt.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/interrupt.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/ioc.obj: ../drivers/ioc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/ioc.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/pka.obj: ../drivers/pka.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/pka.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/sleepmode.obj: ../drivers/sleepmode.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/sleepmode.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/ssi.obj: ../drivers/ssi.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/ssi.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/sys_ctrl.obj: ../drivers/sys_ctrl.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/sys_ctrl.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/systick.obj: ../drivers/systick.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/systick.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/uart.obj: ../drivers/uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/uart.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/udma.obj: ../drivers/udma.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/udma.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/watchdog.obj: ../drivers/watchdog.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="drivers/watchdog.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


