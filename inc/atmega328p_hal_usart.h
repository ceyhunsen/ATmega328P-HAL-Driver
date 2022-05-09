/**
 * @file atmega328p_hal_usart.h
 * @author Ceyhun Şen
 * @brief USART header file for ATmega328P HAL driver.
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

#ifndef __ATMEGA328P_HAL_USART_H
#define __ATMEGA328P_HAL_USART_H

#include <avr/io.h>
#include <stdint.h>

/**
 * @enum hal_usart_operating_mode
 * @brief Operating modes for USART.
 * */
typedef enum hal_usart_operating_mode {
	asynchronous_normal_mode,
	asynchronous_double_speed_mode,
	synchronous_master_mode
} hal_usart_operating_mode;

/**
 * @enum hal_usart_parity
 * @brief Parity settings for USART.
 * */
typedef enum hal_usart_parity {
	disabled,
	even_parity,
	odd_parity
} hal_usart_parity;

/**
 * @enum hal_usart_mode
 * @brief Modes for USART.
 * */
typedef enum hal_usart_mode {
	transmit,
	receive,
	transmit_receive
} hal_usart_mode;

/**
 * @struct hal_usart_t
 * @brief USART definitions.
 * */
typedef struct hal_usart_t {
	uint16_t baud_rate;
	uint8_t stop_bits;
	uint8_t data_bits;
	hal_usart_parity parity;
	hal_usart_operating_mode operating_mode;
	hal_usart_mode mode;
} hal_usart_t;

void hal_usart_init(hal_usart_t *usart);
void hal_usart_transmit(hal_usart_t *usart, uint8_t *data, uint16_t len);
void hal_usart_receive(hal_usart_t *usart, uint8_t *data, uint16_t len);

#endif // __ATMEGA328P_HAL_USART_H