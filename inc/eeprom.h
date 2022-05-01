/**
 * @file eeprom.h
 * @author Ceyhun Şen
 * @brief EEPROM header for ATmega328P.
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

#ifndef __EEPROM_H
#define __EEPROM_H

#include <stdint.h>

/**
 * @enum eeprom_modes
 * @brief EEPROM modes.
 * Atomic operation will take 3.4 ms and will perform write and erase operation,
 * write only will take 1.8 ms and will perform only write operation,
 * erase only will take 1.8 ms and will perform only erase operation
 * */
typedef enum eeprom_modes {
	atomic,
	write_only,
	erase_only
} eeprom_modes;

void eeprom_set_mode(eeprom_modes mode);
void eeprom_read(uint16_t address, uint8_t *data, uint16_t len);
void eeprom_write(uint16_t address, uint8_t *data, uint16_t len);

#endif // __EEPROM_H
