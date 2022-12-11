/**
 * @file atmega328p_hal_twi.h
 * @author Ceyhun Şen
 * @brief Two wire interface header file for ATmega328P HAL driver.
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

#ifndef __ATMEGA328P_HAL_TWI_H
#define __ATMEGA328P_HAL_TWI_H

#include <stdint.h>

// Register size options.
typedef enum hal_twi_register_size {
	hal_twi_register_size_1_byte = 1,
	hal_twi_register_size_2_byte = 2
} hal_twi_register_size;

/**
 * @enum
 * @brief Bit rate modes for TWI.
 *
 * Standart mode: 100 kbit/s
 * Fast mode: 400 kbit/s
 * */
typedef enum hal_twi_bit_rate {
	hal_twi_standart_mode,
	hal_twi_fast_mode
} hal_twi_bit_rate;

void hal_twi_init(hal_twi_bit_rate bit_rate);
uint8_t hal_twi_write_memory(uint8_t slave_address, uint16_t reg, hal_twi_register_size reg_size, uint8_t *buffer, uint16_t len);
uint8_t hal_twi_read_memory(uint8_t slave_address, uint16_t reg, hal_twi_register_size reg_size, uint8_t *buffer, uint16_t len);

#endif // __ATMEGA328P_HAL_TWI_H
