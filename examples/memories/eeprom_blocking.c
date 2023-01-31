/**
 * @file eeprom_blocking.c
 * @author Ceyhun Şen
 * @brief Memories module, blocking EEPROM example code.
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
#include <stdint.h>

/**
 * @brief Address to write and read from.
 */
#define WRITE_READ_ADDRESS 0

int main()
{
	// Initialize EEPROM.
	hal_memories_eeprom_t eeprom = {
		.programming_mode = hal_memories_eeprom_erase_and_write_mode,
		.interrupt_mode = hal_memories_eeprom_interrupt_disabled
	};
	hal_memories_eeprom_set(eeprom);

	// Create a temporary write buffer.
	uint8_t write_buffer[] = {0x1F, 0x2E};

	// Write it to EEPROM.
	hal_memories_eeprom_write(WRITE_READ_ADDRESS, write_buffer, sizeof write_buffer);

	// Create a temporary read buffer.
	uint8_t read_buffer[] = {0, 0};

	// Read it from EEPROM.
	hal_memories_eeprom_read(WRITE_READ_ADDRESS, read_buffer, sizeof read_buffer);

	return 0;
}
