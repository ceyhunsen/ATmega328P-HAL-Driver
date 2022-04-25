/**
 * @file usart.h
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

#ifndef __ATMEGA328P_USART_H
#define __ATMEGA328P_USART_H

#include <avr/io.h>
#include <stdint.h>

/**
 * @enum usart_operating_mode
 * @brief Operating modes for USART.
 * */
typedef enum usart_operating_mode {
	asynchronous_normal_mode,
	asynchronous_double_speed_mode,
	synchronous_master_mode
} usart_operating_mode;

/**
 * @enum usart_parity
 * @brief Parity settings for USART.
 * */
typedef enum usart_parity {
	disabled,
	even_parity,
	odd_parity
} usart_parity;

/**
 * @enum usart_mode
 * @brief Modes for USART.
 * */
typedef enum usart_mode {
	transmit,
	receive,
	transmit_receive
} usart_mode;

/**
 * @struct usart_t
 * @brief USART definitions.
 * */
typedef struct usart_t {
	uint16_t baud_rate;
	uint8_t stop_bits;
	uint8_t data_bits;
	usart_parity parity;
	usart_operating_mode operating_mode;
	usart_mode mode;
} usart_t;

void usart_init(usart_t *usart);
void usart_transmit(usart_t *usart, uint8_t *data, uint16_t len);
void usart_receive(usart_t *usart, uint8_t *data, uint16_t len);

#endif // __ATMEGA328P_USART_H
