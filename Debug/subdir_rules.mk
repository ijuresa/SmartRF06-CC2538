################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
blinky.obj: ../blinky.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="blinky.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cx2538_setup.obj: ../cx2538_setup.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="cx2538_setup.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cx2538_startup_ccs.obj: ../cx2538_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M3 --code_state=16 -me --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538" --include_path="C:/Users/Jura611/Documents/GitHub/SmartRF06-CC2538/include" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --define=DEBUG --define=CC2538_USE_ALTERNATE_INTERRUPT_MAP -g --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="cx2538_startup_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


