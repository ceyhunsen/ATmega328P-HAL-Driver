/**
 * @file eeprom.c
 * @author Ceyhun Şen
 * @brief Unit tests for EEPROM.
 */

/*
 * MIT License
 * 
 * Copyright (c) 2023 Ceyhun Şen
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */

#include "atmega328p_hal_memories.h"
#include "eeprom.h"
#include "unity.h"
#include <test_mock_up.h>
#include <avr/io.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Test EEPROM programming modes.
 */
void test_eeprom_modes()
{
	hal_memories_eeprom_t settings;

	settings.programming_mode = hal_memories_eeprom_erase_and_write_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EEPM1));
	TEST_ASSERT(bit_is_clear(EECR, EEPM0));

	settings.programming_mode = hal_memories_eeprom_erase_only_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EEPM1));
	TEST_ASSERT(bit_is_set(EECR, EEPM0));

	settings.programming_mode = hal_memories_eeprom_write_only_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_set(EECR, EEPM1));
	TEST_ASSERT(bit_is_clear(EECR, EEPM0));

	settings.programming_mode = hal_memories_eeprom_erase_and_write_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EEPM1));
	TEST_ASSERT(bit_is_clear(EECR, EEPM0));
}

/**
 * @brief Test EEPROM interrupt modes.
 */
void test_eeprom_interrupt()
{
	hal_memories_eeprom_t settings;

	settings.interrupt_mode = hal_memories_eeprom_interrupt_disabled;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EERIE));

	settings.interrupt_mode = hal_memories_eeprom_interrupt_enabled;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_set(EECR, EERIE));

	settings.interrupt_mode = hal_memories_eeprom_interrupt_disabled;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EERIE));
}

/**
 * @brief Test EEPROM single byte read operation.
 */
void test_eeprom_read_single_byte()
{
	#define FIXED_VALUE 0xF0

	// Create a buffer with fixed element.
	uint8_t buffer = FIXED_VALUE;

	// Read single byte from start, middle and end.
	uint16_t read_addresses[3] = {0, HAL_EEPROM_SIZE / 2, HAL_EEPROM_SIZE - 1};
	for (uint16_t i = 0; i < 3; i++) {
		// Reset buffer.
		buffer = FIXED_VALUE;

		// Read single byte.
		uint16_t read_length = hal_memories_eeprom_read(read_addresses[i], &buffer, 1);

		// Check if read enable bit is set.
		TEST_ASSERT_EQUAL(_BV(EERE), EECR & _BV(EERE));

		// It should return 1 byte as it reads only one byte.
		TEST_ASSERT_EQUAL(1, read_length);

		// It should read 0 because EEPROM and registers are in reset state.
		TEST_ASSERT_EQUAL(0, buffer);
		TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, buffer);

		// Reset registers for other reads.
		reset_registers();
	}

	// Try to read out of range address.
	read_addresses[0] = HAL_EEPROM_SIZE + 10;
	buffer = FIXED_VALUE;

	// Read single byte.
	uint16_t read_length = hal_memories_eeprom_read(read_addresses[0], &buffer, 1);

	// Read enable bit shouldn't be set.
	TEST_ASSERT_NOT_EQUAL(_BV(EERE), EECR & _BV(EERE));

	// It should return 1 byte as it reads only one byte.
	TEST_ASSERT_EQUAL(0, read_length);

	// It shouldn't read anything.
	TEST_ASSERT_EQUAL(FIXED_VALUE, buffer);
	TEST_ASSERT_NOT_EQUAL(0, buffer);
}
