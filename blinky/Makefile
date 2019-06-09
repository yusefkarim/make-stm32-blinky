# Author: Yusef Karim

##### Project setup #####
# Name of your current project
PROJ_NAME = $(shell basename $(CURDIR))
# Directory containing all CMSIS relevent source code
CMSIS_DIR = ../CMSIS
LINKER_SCRIPT = $(CMSIS_DIR)/STM32L476RG.ld

##### Toolchain #####
TRIPLE  = 	arm-none-eabi
CC 		=	${TRIPLE}-gcc
LD 		= 	${TRIPLE}-ld
AS 		= 	${TRIPLE}-as
GDB 	= 	${TRIPLE}-gdb
OBJCOPY =  	${TRIPLE}-objcopy

##### Compiler options #####
CFLAGS = -g -Wall -T$(LINKER_SCRIPT)
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 --specs=nosys.specs

##### Project specific libraries #####
SRC_FILES += $(wildcard src/*.c)
CFLAGS += -Iinc

##### CMSIS libraries and source code #####
SRC_FILES += $(CMSIS_DIR)/src/*
CFLAGS += -I$(CMSIS_DIR)/inc

all:  $(PROJ_NAME).bin

##### Flash code to board using OpenOCD #####
flash: $(PROJ_NAME).bin
	openocd -f board/stm32l4discovery.cfg -c "program $^ reset exit 0x08000000"

##### Erase all flash memory from board using OpenOCD #####
erase:
	openocd -f board/stm32l4discovery.cfg -c "init; reset halt; stm32l4x mass_erase 0; exit"

##### Print out disassembly of specified function using GDB #####
##### USAGE EXAMPLE: 	make disass FUNC=main 				#####
disass: $(PROJ_NAME).elf
	$(GDB) $^ -batch -ex 'disass /r $(FUNC)'

clean:
	rm -f $(PROJ_NAME).bin $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(PROJ_NAME).bin: $(PROJ_NAME).elf
	$(OBJCOPY) -O binary $^ $@

