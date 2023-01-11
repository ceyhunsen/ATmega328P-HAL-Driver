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
 * @brief Some random number for testing.
 */
#define FIXED_VALUE 0xF0

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
	uint8_t buffer = FIXED_VALUE;

	// Read single byte from start, middle and end.
	uint16_t read_addresses[3] = {0, HAL_EEPROM_SIZE / 2, HAL_EEPROM_SIZE - 1};
	for (uint16_t i = 0; i < 3; i++) {
		buffer = FIXED_VALUE;

		uint16_t read_length = hal_memories_eeprom_read(read_addresses[i], &buffer, 1);

		// Read enable bit should be set during read operation.
		TEST_ASSERT_EQUAL(_BV(EERE), EECR & _BV(EERE));

		// It should return 1 byte as it reads only one byte.
		TEST_ASSERT_EQUAL(1, read_length);

		// It should read 0 because EEPROM and registers are in reset state.
		TEST_ASSERT_EQUAL(0, buffer);
		TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, buffer);

		reset_registers();
	}

	// Try to read out of range address.
	read_addresses[0] = HAL_EEPROM_SIZE + 10;
	buffer = FIXED_VALUE;

	// Read single byte.
	uint16_t read_length = hal_memories_eeprom_read(read_addresses[0], &buffer, 1);

	// // Read enable bit shouldn't be set during read operation.
	TEST_ASSERT_NOT_EQUAL(_BV(EERE), EECR & _BV(EERE));

	// It should return 1 byte as it reads only one byte.
	TEST_ASSERT_EQUAL(0, read_length);

	// It shouldn't read anything.
	TEST_ASSERT_EQUAL(FIXED_VALUE, buffer);
	TEST_ASSERT_NOT_EQUAL(0, buffer);
}

/**
 * @brief Test EEPROM multiple bytes read operation.
 */
void test_eeprom_read_multiple_bytes()
{
	#define FIXED_VALUE 0xF0
	uint8_t buffer[3] = {FIXED_VALUE, FIXED_VALUE, FIXED_VALUE};

	// Read multiple bytes from start, middle and end.
	uint16_t read_addresses[3] = {0, HAL_EEPROM_SIZE / 2, HAL_EEPROM_SIZE - 4};
	for (uint16_t i = 0; i < 3; i++) {
		memset(buffer, FIXED_VALUE, sizeof buffer);

		uint16_t read_length = hal_memories_eeprom_read(read_addresses[i], buffer, 3);

		// Read enable bit should be set during read operation.
		TEST_ASSERT_EQUAL(_BV(EERE), EECR & _BV(EERE));

		TEST_ASSERT_EQUAL(3, read_length);

		// It should read 0 because EEPROM and registers are in reset state.
		for (uint8_t i = 0; i < 3; i++) {
			TEST_ASSERT_EQUAL(0, buffer[i]);
			TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, buffer[i]);
		}

		reset_registers();
	}

	// Try to read out of range address.
	read_addresses[0] = HAL_EEPROM_SIZE + 10;
	memset(buffer, FIXED_VALUE, sizeof buffer);

	uint16_t read_length = hal_memories_eeprom_read(read_addresses[0], buffer, 3);

	// Read enable bit shouldn't be set during read operation.
	TEST_ASSERT_NOT_EQUAL(_BV(EERE), EECR & _BV(EERE));

	TEST_ASSERT_EQUAL(0, read_length);

	// It shouldn't read anything.
	for (uint8_t i = 0; i < 3; i++) {
		TEST_ASSERT_NOT_EQUAL(0, buffer[i]);
		TEST_ASSERT_EQUAL(FIXED_VALUE, buffer[i]);
	}

	// Reset registers for other reads.
	reset_registers();

	// Try to read both in and out of range addresses.
	read_addresses[0] = HAL_EEPROM_SIZE - 2;
	memset(buffer, FIXED_VALUE, sizeof buffer);

	read_length = hal_memories_eeprom_read(read_addresses[0], buffer, 3);

	// Read enable bit should be set.
	TEST_ASSERT_EQUAL(_BV(EERE), EECR & _BV(EERE));

	// It should read 2 bytes.
	TEST_ASSERT_EQUAL(2, read_length);

	TEST_ASSERT_EQUAL(0, buffer[0]);
	TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, buffer[0]);

	TEST_ASSERT_EQUAL(0, buffer[1]);
	TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, buffer[1]);

	TEST_ASSERT_EQUAL(FIXED_VALUE, buffer[2]);
	TEST_ASSERT_NOT_EQUAL(0, buffer[2]);
}

/**
 * @brief Test EEPROM single byte write operation.
 */
void test_eeprom_write_single_byte()
{
	uint8_t buffer = FIXED_VALUE;

	// Write single byte to start, middle and end.
	uint16_t write_addresses[3] = {0, HAL_EEPROM_SIZE / 2, HAL_EEPROM_SIZE - 1};
	for (uint16_t i = 0; i < 3; i++) {
		// Before the write operation, EEPROM data register should be in reset
		// state (0 in this case).
		TEST_ASSERT_EQUAL(0, EEDR);
		TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, EEDR);

		uint16_t read_length = hal_memories_eeprom_write(write_addresses[i], &buffer, 1);

		// It should return 1 byte as it writes only one byte.
		TEST_ASSERT_EQUAL(1, read_length);

		// EEPROM data register should be `FIXED_VALUE`.
		TEST_ASSERT_EQUAL(FIXED_VALUE, EEDR);

		// Reset registers for other reads.
		reset_registers();
	}

	// Write single byte to out of range address.
	write_addresses[0] = HAL_EEPROM_SIZE + 10;

	// Before the write operation, EEPROM data register should be in reset
	// state (0 in this case).
	TEST_ASSERT_EQUAL(0, EEDR);
	TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, EEDR);

	uint16_t read_length = hal_memories_eeprom_write(write_addresses[0], &buffer, 1);

	TEST_ASSERT_EQUAL(0, read_length);

	// EEPROM data register should be reset value (0 in this case).
	TEST_ASSERT_EQUAL(0, EEDR);
}

/**
 * @brief Test EEPROM multiple bytes write operation.
 */
void test_eeprom_write_multiple_bytes()
{
	// Currently, write operation needs some hardware or thread to clear some
	// bits. So, this test is ignored at the moment.
	TEST_IGNORE();

	uint8_t buffer[3] = {FIXED_VALUE, FIXED_VALUE - 1, FIXED_VALUE - 2};

	// Write multiple bytes to start, middle and end.
	uint16_t write_addresses[3] = {0, HAL_EEPROM_SIZE / 2, HAL_EEPROM_SIZE - 4};
	for (uint16_t i = 0; i < 3; i++) {
		// Before the write operation, EEPROM data register should be in reset
		// state (0 in this case).
		TEST_ASSERT_EQUAL(0, EEDR);
		TEST_ASSERT_NOT_EQUAL(FIXED_VALUE, EEDR);

		uint16_t read_length = hal_memories_eeprom_write(write_addresses[i], buffer, 3);

		TEST_ASSERT_EQUAL(3, read_length);

		// EEPROM data register should be last member of buffer.
		TEST_ASSERT_EQUAL(buffer[2], EEDR);

		// Reset registers for other reads.
		reset_registers();
	}
}
