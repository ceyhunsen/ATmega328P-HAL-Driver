# Master makefile for all tests. This makefile will call every test seperately.
# Change HOST_C_STD and MCU_C_LIB paths according to your system.
#
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

# Host system C standard library include directory.
HOST_C_STD = /usr/include/

# AVR-libc include directory.
MCU_C_LIB  = /usr/avr/include

# Host C compiler.
export CC = gcc

# Local build directory.
export BUILD_DIR = build

# Include directories.
export C_INCLUDES =      \
-I $(CURDIR)/../include  \
-I $(CURDIR)/Unity/src

# System include directories.
export C_SYS_INCLUDES =   \
-isystem $(HOST_C_STD)    \
-isystem $(CURDIR)/mocks  \
-isystem $(MCU_C_LIB)     \

# C definitions.
export C_DEFINES =     \
-D __AVR_ATmega328P__  \

# Source files.
export C_SOURCES =  \
unity.c             \
test_mock_up.c      \

# Compile .c files to object files.
export HOST_COMPILE_OBJ = $(CC) $(C_DEFINES) $(C_INCLUDES) $(C_SYS_INCLUDES) -c

# Link previously compiled object files and create the test executable.
export HOST_COMPILE = $(CC) $(BUILD_DIR)/*.o

# Use this paths for searching source and header files.
export VPATH =         \
$(CURDIR)/Unity/src/   \
$(CURDIR)/mocks/       \
$(CURDIR)/../src/      \
$(CURDIR)/../include/  \

# All unit test directories.
UNIT_TESTS = $(wildcard unit/*/.)

# Run all tests.
all: unit

unit: $(UNIT_TESTS)

$(UNIT_TESTS):
	$(MAKE) -C $@

.PHONY: clean $(UNIT_TESTS)
