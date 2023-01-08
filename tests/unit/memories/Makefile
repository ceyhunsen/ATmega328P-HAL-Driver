# Unit tests for memories module.
# Author: Ceyhun Şen

CC = gcc

TARGET = memories_test

BUILD_DIR = build

C_SOURCES = \
../../mocks/definitions.c \
../../../src/atmega328p_hal_memories.c \
../../Unity/src/unity.c \
memories.c \
eeprom.c \

C_INCLUDES = \
-I ../../../include/ \
-I ../../Unity/src/ \

C_SYS_INCLUDES = \
-isystem ../../mocks \

all:
	@mkdir -p $(BUILD_DIR)
	$(CC) $(C_SOURCES) $(C_INCLUDES) $(C_SYS_INCLUDES) -o $(BUILD_DIR)/$(TARGET).out
	$(BUILD_DIR)/$(TARGET).out
