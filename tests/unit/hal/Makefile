# Unit test sub-Makefile for ATmega328P HAL driver.
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

TARGET = test.out

# Append source files.
HOST_C_SOURCES += \
unity.c           \
hal.c             \

# Create object files.
OBJS = $(HOST_C_SOURCES:%.c=$(BUILD_DIR)/%.o)

# Check source files first. Then run test.
all: $(OBJS) $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)

# Create object files.
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(HOST_COMPILE_OBJ) $< -o $@

# Link everything.
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(HOST_COMPILE) -o $(BUILD_DIR)/$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
