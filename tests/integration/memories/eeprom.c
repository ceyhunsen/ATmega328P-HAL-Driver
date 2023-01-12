/**
 * @file eeprom.c
 * @author Ceyhun Şen
 * @brief Integration tests for EEPROM.
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

#include "eeprom.h"
#include "unity.h"
#include "atmega328p_hal_memories.h"
#include <stdint.h>

/**
 * @brief Some random fixed number for testing.
 */
#define FIXED_VALUE 0xF0

/**
 * @brief Test writing and reading single byte to EEPROM.
 */
void test_eeprom_single_byte()
{
	// Initialize EEPROM first.
	hal_memories_eeprom_t eeprom = {
		.programming_mode = hal_memories_eeprom_erase_and_write_mode,
		.interrupt_mode = hal_memories_eeprom_interrupt_disabled
	};
	hal_memories_eeprom_set(eeprom);

	uint8_t buffer = 0;

	// Write some value to 3 EEPROM addresses: start, middle and end.
	uint16_t addresses[3] = {0, HAL_EEPROM_SIZE / 2, HAL_EEPROM_SIZE - 1};
	for (uint8_t i = 0; i < 3; i++) {
		buffer = FIXED_VALUE;

		uint16_t size = hal_memories_eeprom_write(addresses[i], &buffer, 1);
		TEST_ASSERT_EQUAL(1, size);

		buffer = 0, size = 0;

		size = hal_memories_eeprom_read(addresses[i], &buffer, 1);
		TEST_ASSERT_EQUAL(1, size);

		TEST_ASSERT_EQUAL(FIXED_VALUE, buffer);
	}
}

/**
 * @brief Test writing and reading single byte to EEPROM but out of range.
 */
void test_eeprom_single_byte_out_of_range()
{
	// Initialize EEPROM first.
	hal_memories_eeprom_t eeprom = {
		.programming_mode = hal_memories_eeprom_erase_and_write_mode,
		.interrupt_mode = hal_memories_eeprom_interrupt_disabled
	};
	hal_memories_eeprom_set(eeprom);

	uint8_t buffer = FIXED_VALUE;

	// It shouldn't write anything to EEPROM.
	uint16_t size = hal_memories_eeprom_write(HAL_EEPROM_SIZE + 10, &buffer, 1);
	TEST_ASSERT_EQUAL(0, size);

	buffer = 0;

	// It shouldn't read anything from EEPROM.
	size = hal_memories_eeprom_read(HAL_EEPROM_SIZE + 10, &buffer, 1);
	TEST_ASSERT_EQUAL(0, size);

	// Buffer should stay same.
	TEST_ASSERT_EQUAL(0, buffer);
}

/**
 * @brief Test writing and reading multiple bytes to EEPROM.
 */
void test_eeprom_multiple_bytes()
{
	// Initialize EEPROM first.
	hal_memories_eeprom_t eeprom = {
		.programming_mode = hal_memories_eeprom_erase_and_write_mode,
		.interrupt_mode = hal_memories_eeprom_interrupt_disabled
	};
	hal_memories_eeprom_set(eeprom);

	uint8_t buffer[3] = {FIXED_VALUE, FIXED_VALUE - 1, FIXED_VALUE - 2};

	// Write some value to 3 EEPROM addresses: start, middle and end.
	uint16_t addresses[3] = {0, HAL_EEPROM_SIZE / 2, HAL_EEPROM_SIZE - 4};
	for (uint8_t i = 0; i < 3; i++) {
		for (uint8_t i = 0; i < 3; i++)
			buffer[i] = FIXED_VALUE - i;

		uint16_t size = hal_memories_eeprom_write(addresses[i], buffer, 3);
		TEST_ASSERT_EQUAL(3, size);

		for (uint8_t i = 0; i < 3; i++)
			buffer[i] = 0;
		size = 0;

		size = hal_memories_eeprom_read(addresses[i], buffer, 3);
		TEST_ASSERT_EQUAL(3, size);

		for (uint8_t i = 0; i < 3; i++)
			TEST_ASSERT_EQUAL(FIXED_VALUE - i, buffer[i]);
	}
}

/**
 * @brief Test writing and reading multiple bytes to EEPROM but out of range.
 */
void test_eeprom_multiple_bytes_out_of_range()
{
	// Initialize EEPROM first.
	hal_memories_eeprom_t eeprom = {
		.programming_mode = hal_memories_eeprom_erase_and_write_mode,
		.interrupt_mode = hal_memories_eeprom_interrupt_disabled
	};
	hal_memories_eeprom_set(eeprom);

	uint8_t buffer[3] = {FIXED_VALUE, FIXED_VALUE - 1, FIXED_VALUE - 2};

	// Write some value to 3 EEPROM addresses: start, middle and end.
	for (uint8_t i = 0; i < 3; i++)
		buffer[i] = FIXED_VALUE - i;

	uint16_t size = hal_memories_eeprom_write(HAL_EEPROM_SIZE + 10, buffer, 3);
	TEST_ASSERT_EQUAL(0, size);

	for (uint8_t i = 0; i < 3; i++)
		buffer[i] = 0;
	size = 0;

	size = hal_memories_eeprom_read(HAL_EEPROM_SIZE + 10, buffer, 3);
	TEST_ASSERT_EQUAL(0, size);

	for (uint8_t i = 0; i < 3; i++)
		TEST_ASSERT_EQUAL(0, buffer[i]);
}
