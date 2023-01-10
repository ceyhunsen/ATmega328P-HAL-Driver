/**
 * @file atmega328p_hal_memories.c
 * @author Ceyhun Şen
 * @brief Memory operations.
 * */

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
#include "atmega328p_hal_internals.h"
#include <avr/io.h>

/**
 * @brief Set EEPROM settings.
 * 
 * @param settings EEPROM settings.
 * 
 * @see hal_memories_eeprom_settings
 * */
void hal_memories_eeprom_set(hal_memories_eeprom_settings settings)
{
	// Wait for ongoing write operations.
	loop_until_bit_is_clear(EECR, EEPE);

	// Set mode.
	switch (settings.mode) {
		default:
		case hal_memories_eeprom_erase_and_write_mode:
			_CLEAR_BIT(EECR, EEPM0);
			_CLEAR_BIT(EECR, EEPM1);
			break;
		case hal_memories_eeprom_erase_only_mode:
			_SET_BIT(EECR, EEPM0);
			_CLEAR_BIT(EECR, EEPM1);
			break;
		case hal_memories_eeprom_write_only_mode:
			_CLEAR_BIT(EECR, EEPM0);
			_SET_BIT(EECR, EEPM1);
			break;
	}
}

/**
 * @brief Read data from EEPROM.
 * @param start_address Start address of the read operation.
 * @param data Data buffer that will hold read data.
 * @param len Length of the data that will be read.
 * @returns Length of the readed data.
 * */
uint16_t hal_memories_eeprom_read(uint16_t start_address, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Check start_address overflow.
		if (start_address + i > (1 << 9) - 1) {
			return i;
		}

		// Wait for ongoing write operations.
		while (EECR & _BV(EEPE));

		// Set start_address.
		EEAR = start_address + i;

		// Start reading and set it to data[i].
		_SET_BIT(EECR, EERE);
		data[i] = EEDR;
	}

	return len;
}

/**
 * @brief Write data to EEPROM.
 * @param start_address Start address of the write operation.
 * @param data Data buffer that holds write data.
 * @param len Length of the data that will be written.
 * @returns Length of the written data.
 * */
uint16_t hal_memories_eeprom_write(uint16_t start_address, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Check start_address overflow.
		if (start_address + i > (1 << 10) - 1) {
			return i;
		}

		// Wait for ongoing write operations.
		while (EECR & _BV(EEPE));

		// Set start_address and data.
		EEAR = start_address + i;
		EEDR = data[i];

		// Enable writing.
		_SET_BIT(EECR, EEMPE);
		_SET_BIT(EECR, EEPE);
	}

	return len;
}
