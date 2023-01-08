/**
 * @file atmega328p_hal_memories.h
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

#ifndef __ATMEGA328P_HAL_MEMORIES_H
#define __ATMEGA328P_HAL_MEMORIES_H

#include <stdint.h>

/**
 * @enum hal_memories_eeprom_modes
 * @brief EEPROM programming modes.
 * 
 * Erase and write mode will take 3.4 ms and perform write and erase operation
 * (atomic operation). Write only mode will take 1.8 ms and only perform write
 * operation. Finally, erase only mode will take 1.8 ms and only perform erase
 * operation on writing to EEPROM.
 * */
typedef enum hal_memories_eeprom_modes {
	hal_memories_eeprom_erase_and_write_mode = 0,
	hal_memories_eeprom_write_only_mode      = 1,
	hal_memories_eeprom_erase_only_mode      = 2
} hal_memories_eeprom_modes;

/**
 * @enum hal_memories_eeprom_interrupt_mode
 * @brief Interrupt mode for EEPROM access.
 */
typedef enum hal_memories_eeprom_interrupt_mode {
	hal_memories_eeprom_interrupt_disabled = 0,
	hal_memories_eeprom_interrupt_enabled  = 1
} hal_memories_eeprom_interrupt_mode;

/**
 * @brief All EEPROM settings.
 */
typedef struct hal_memories_eeprom_settings {
	hal_memories_eeprom_modes mode;
	hal_memories_eeprom_interrupt_mode interrupt_mode;
} hal_memories_eeprom_settings;

void hal_memories_eeprom_set(hal_memories_eeprom_settings settings);
uint16_t hal_memories_eeprom_read(uint16_t start_address, uint8_t *data, uint16_t len);
uint16_t hal_memories_eeprom_write(uint16_t start_address, uint8_t *data, uint16_t len);

#endif // __ATMEGA328P_HAL_MEMORIES_H
