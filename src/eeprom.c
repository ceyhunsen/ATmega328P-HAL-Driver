/**
 * @file eeprom.c
 * @author Ceyhun Şen
 * @brief EEPROM HAL functions for ATmega328P.
 * */

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

#include "eeprom.h"
#include "atmega328p_hal_internals.h"
#include <avr/io.h>

/**
 * @brief Set EEPROM mode.
 * @param mode EEPROM mode to be set.
 * @see eeprom_modes
 * */
void eeprom_set_mode(eeprom_modes mode)
{
	// Wait for ongoing write operations.
	while (EECR & _PIN_TO_BIT(EEPE));

	// Set mode.
	switch (mode) {
		case atomic:
			EECR |= 0b00 << EEPM0;
			break;
		case erase_only:
			EECR |= 0b01 << EEPM0;
			break;
		case write_only:
			EECR |= 0b10 << EEPM0;
			break;
		default:
			EECR |= 0b00 << EEPM0;
			break;
	}
}

/**
 * @brief Read data from EEPROM.
 * @param address Start address of the read operation.
 * @param data Data buffer that will hold read data.
 * @param len Length of the data that will be read.
 * */
void eeprom_read(uint16_t address, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Check address overflow.
		if (address + i > (1 << 9) - 1) {
			return;
		}

		// Wait for ongoing write operations.
		while (EECR & _PIN_TO_BIT(EEPE));

		// Set address.
		EEAR = address + i;

		// Start reading and set it to data[i].
		EECR |= _BV(EERE);
		data[i] = EEDR;
	}
}

/**
 * @brief Write data to EEPROM.
 * @param address Start address of the write operation.
 * @param data Data buffer that holds write data.
 * @param len Length of the data that will be written.
 * */
void eeprom_write(uint16_t address, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Check address overflow.
		if (address + i > (1 << 9) - 1) {
			return;
		}

		// Wait for ongoing write operations.
		while (EECR & _PIN_TO_BIT(EEPE));

		// Set address and data.
		EEAR = address + i;
		EEDR = data[i];

		// Enable writing.
		EECR |= _BV(EEMPE);
		EECR |= _BV(EEPE);
	}
}
