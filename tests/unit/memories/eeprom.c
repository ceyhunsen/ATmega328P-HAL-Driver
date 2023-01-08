/**
 * @file eeprom.c
 * @author Ceyhun Şen
 * @brief Unit tests for eeprom.
 */

/*
 * MIT License
 * 
 * Copyright (c) 2022 Ceyhun Şen
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
#include <avr/io.h>
#include <stdint.h>

/**
 * @brief Test EEPROM programming modes.
 */
void test_eeprom_modes()
{
	hal_memories_eeprom_settings settings;

	settings.mode = hal_memories_eeprom_erase_and_write_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EEPM1));
	TEST_ASSERT(bit_is_clear(EECR, EEPM0));

	settings.mode = hal_memories_eeprom_erase_only_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EEPM1));
	TEST_ASSERT(bit_is_set(EECR, EEPM0));

	settings.mode = hal_memories_eeprom_write_only_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_set(EECR, EEPM1));
	TEST_ASSERT(bit_is_clear(EECR, EEPM0));

	settings.mode = hal_memories_eeprom_erase_and_write_mode;
	hal_memories_eeprom_set(settings);
	TEST_ASSERT(bit_is_clear(EECR, EEPM1));
	TEST_ASSERT(bit_is_clear(EECR, EEPM0));
}

/**
 * @brief Test EEPROM interrupt modes.
 */
void test_eeprom_interrupt()
{

}
