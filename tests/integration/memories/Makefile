# Integration test sub-Makefile for ATmega328P HAL driver.
# Author: Ceyhun Şen

# Copyright (c) 2023 Ceyhun Şen
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

TARGET = test

# Append source files.
MCU_C_SOURCES = \
memories.c      \

# Create object files.
OBJS = $(MCU_C_SOURCES:%.c=$(BUILD_DIR)/%.o)

# Check source files first. Then run test.
all: $(OBJS) $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex upload

# Create object files.
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(MCU_COMPILE_OBJ) $< -o $@

# Link everything to an elf file.
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(MCU_COMPILE) -o $@

# Convert elf file to hex file.
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(MCU_OBJ_COPY) -j .text -j .data -O ihex $< $@
	$(MCU_SIZE) --mcu=$(MCU) $@

# Upload .hex file to MCU.
upload:
	avrdude -v -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(BAUD) -U flash:w:$(BUILD_DIR)/$(TARGET).hex:i
