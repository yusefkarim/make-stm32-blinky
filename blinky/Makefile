# Author: Yusef Karim

##### Project setup #####
# Name of your current project
PROJ_NAME = test
# Directory containing all CMSIS relevent source code
CMSIS_DIR = $(HOME)/STM32L4-Projects/CMSIS
# Current working directory of our project
CWD := $(shell pwd)

##### Compiler options #####
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -g -Wall -TSTM32L476RG.ld
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 --specs=nosys.specs
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16

##### Project specific libraries #####
SRC_FILES = main.c
SRC_FILES += $(wildcard src/*.c)
CFLAGS += -Iinc

##### CMSIS libraries and source code #####
CFLAGS += -I$(CMSIS_DIR)/inc
SRC_FILES += $(CMSIS_DIR)/src/*


all:  $(PROJ_NAME).bin

clean:
	rm -f $(PROJ_NAME).bin $(PROJ_NAME).elf

$(PROJ_NAME).elf: $(SRC_FILES)
	$(CC) $(CFLAGS) -o $@ $^

$(PROJ_NAME).bin: $(PROJ_NAME).elf
	$(OBJCOPY) -O binary $^ $@

