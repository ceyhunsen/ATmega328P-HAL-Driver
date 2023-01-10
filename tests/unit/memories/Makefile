# Unit tests for memories module.
# Author: Ceyhun Şen

CC = gcc

TARGET = memories_test

BUILD_DIR = build

C_SOURCES = \
../../mocks/test_mock_up.c \
../../Unity/src/unity.c \
../../../src/atmega328p_hal_memories.c \
memories.c \
eeprom.c \

C_INCLUDES = \
-I ../../../include/ \
-I ../../Unity/src/ \

C_SYS_INCLUDES = \
-isystem /usr/include/ \
-isystem ../../mocks \
-isystem /usr/avr/include \

C_DEFINES = \
-D __AVR_ATmega328P__

all:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(C_SOURCES) $(C_DEFINES) $(C_INCLUDES) $(C_SYS_INCLUDES) -o $(BUILD_DIR)/$(TARGET).out
	$(BUILD_DIR)/$(TARGET).out
