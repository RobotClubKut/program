################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../PSPADtiny.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
PSPADtiny.o

OBJS_AS_ARGS +=  \
PSPADtiny.o

C_DEPS +=  \
PSPADtiny.d

C_DEPS_AS_ARGS +=  \
PSPADtiny.d

OUTPUT_FILE_PATH +=PSPADtiny.elf

OUTPUT_FILE_PATH_AS_ARGS +=PSPADtiny.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler



./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 20100110.0
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -Os -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -mmcu=attiny4313 -c -gdwarf-2 -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 20100110.0
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="PSPADtiny.map" -Wl,--start-group  -Wl,--end-group -Wl,--gc-sections -mmcu=attiny4313 
	@echo Finished building target: $@
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "PSPADtiny.elf" "PSPADtiny.hex"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "PSPADtiny.elf" "PSPADtiny.eep" || exit 0
	"C:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "PSPADtiny.elf" > "PSPADtiny.lss"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "PSPADtiny.elf" "PSPADtiny.srec"
	"C:\WinAVR-20100110\bin\avr-size.exe" "PSPADtiny.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "PSPADtiny.elf" "PSPADtiny.a" "PSPADtiny.hex" "PSPADtiny.lss" "PSPADtiny.eep" "PSPADtiny.map" "PSPADtiny.srec"
	