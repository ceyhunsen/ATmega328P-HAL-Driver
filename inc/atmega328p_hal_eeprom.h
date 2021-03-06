/**
 * @file atmega328p_hal_eeprom.h
 * @author Ceyhun Şen
 * @brief EEPROM header file for ATmega328P HAL driver.
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

#ifndef __ATMEGA328P_HAL_EEPROM_H
#define __ATMEGA328P_HAL_EEPROM_H

#include <stdint.h>

/**
 * @enum hal_eeprom_modes
 * @brief EEPROM modes.
 * 
 * Atomic operation will take 3.4 ms and perform write and erase operation,
 * hal_eeprom_write_only_mode will take 1.8 ms and only perform write operation and
 * hal_eeprom_erase_only_mode will take 1.8 ms and only perform erase operation on writing to
 * EEPROM.
 * */
typedef enum hal_eeprom_modes {
	hal_eeprom_atomic_mode,
	hal_eeprom_write_only_mode,
	hal_eeprom_erase_only_mode
} hal_eeprom_modes;

void hal_eeprom_set_mode(hal_eeprom_modes mode);
uint16_t hal_eeprom_read(uint16_t start_address, uint8_t *data, uint16_t len);
uint16_t hal_eeprom_write(uint16_t start_address, uint8_t *data, uint16_t len);

#endif // __ATMEGA328P_HAL_EEPROM_H
