# Author: Ceyhun Şen
# Makefile for ATmega328p HAL driver tests.

################################################################################
# Variables
################################################################################

TARGET = atmega328phaltest

# Device specific stuff.
MCU = atmega328p
PROGRAMMER = arduino
BAUD = 115200
PORT = /dev/ttyUSB0

# Compiler stuff.
CC = avr-gcc
COMPILE = $(CC) $(CFLAGS)

# Optimization flag.
OPTIMIZATION = debug

# Flags.
ifeq ($(OPTIMIZATION), size)
	OPT_FLAG = -Os
else ifeq ($(OPTIMIZATION), speed)
	OPT_FLAG = -O2
else ifeq ($(OPTIMIZATION), debug)
	OPT_FLAG = -Og
else ifeq ($(OPTIMIZATION), nothing)
	OPT_FLAG = -O0
else
	OPT_FLAG = -O0
endif
CFLAGS = -Wall $(OPT_FLAG) -mmcu=$(MCU) $(C_INCLUDES) -D F_CPU=16000000UL

# Include directories.
C_INCLUDES = \
-I../include

# Source files.
C_SOURCES = \
test.c \
../src/atmega328p_hal_power.c \
../src/atmega328p_hal_system.c \
../src/atmega328p_hal_eeprom.c \
../src/atmega328p_hal_io.c \
../src/atmega328p_hal_usart.c \
../src/atmega328p_hal_usart_extra.c \
../src/atmega328p_hal_twi.c \

# Binary files.
BUILD_DIR = build
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

################################################################################
# Rules
################################################################################

all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex

# Compile object files to .elf file.
$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(COMPILE) $(OBJECTS) -o $@

# Compile .elf file to .hex file.
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf Makefile
	avr-objcopy -j .text -j .data -O ihex $< $@
	avr-size --mcu=$(MCU) $@

# Compile source files to object file.
$(BUILD_DIR)/%.o: %.c Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Upload .hex file to MCU.
upload:
	avrdude -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(BUILD_DIR)/$(TARGET).hex:i

# Clean all binaries.
clean:
	rm -rf $(BUILD_DIR)

# Clear objects and build again.
again: clean all

# PHONY rules.
.PHONY: all upload upload again
