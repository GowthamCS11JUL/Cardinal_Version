################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia151/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/Cardinal_Github/Cardinal" -I"D:/Cardinal_Github/MSPM0G_Library/Include" -I"D:/Cardinal_Github/Cardinal/Debug" -I"C:/ti/mspm0_sdk_2_00_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_00_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-612939601: ../main.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.19.0/sysconfig_cli.bat" --script "D:/Cardinal_Github/Cardinal/main.syscfg" -o "." -s "C:/ti/mspm0_sdk_2_00_00_03/.metadata/product.json" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-612939601 ../main.syscfg
device.opt: build-612939601
device.cmd.genlibs: build-612939601
ti_msp_dl_config.c: build-612939601
ti_msp_dl_config.h: build-612939601
Event.dot: build-612939601

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia151/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/Cardinal_Github/Cardinal" -I"D:/Cardinal_Github/MSPM0G_Library/Include" -I"D:/Cardinal_Github/Cardinal/Debug" -I"C:/ti/mspm0_sdk_2_00_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_00_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g110x_ticlang.o: C:/ti/mspm0_sdk_2_00_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g110x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccstheia151/ccs/tools/compiler/ti-cgt-armllvm_4.0.0.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"D:/Cardinal_Github/Cardinal" -I"D:/Cardinal_Github/MSPM0G_Library/Include" -I"D:/Cardinal_Github/Cardinal/Debug" -I"C:/ti/mspm0_sdk_2_00_00_03/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_00_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


