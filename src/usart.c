/**
 * @file usart.c
 * @author Ceyhun Şen
 * @brief USART HAL functions for ATmega328p.
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

#include "usart.h"
#include "atmega328p_hal_internals.h"

/**
 * @brief Initialize USART.
 * @param usart USART struct.
 * */
void usart_init(usart_t *usart)
{
	// Get operating mode prescaler and set USART control and status register.
	uint8_t operating_mode_prescaler = 16;
	switch (usart->operating_mode) {
		case asynchronous_normal_mode:
			operating_mode_prescaler = 16;
			UCSR0C = 0b00 << 6;
			break;
		case asynchronous_double_speed_mode:
			operating_mode_prescaler = 8;
			UCSR0C = 0b00 << 6;
			break;
		case synchronous_master_mode:
			operating_mode_prescaler = 2;
			UCSR0C = 0b01 << 6;
			break;
		default:
			operating_mode_prescaler = 16;
			UCSR0C = 0b00 << 6;
			break;
	}

	// Set parity bit setting.
	switch (usart->parity) {
		case disabled:
			UCSR0C |= (0b00 << 4);
			break;
		case even_parity:
			UCSR0C |= 0b10 << 4;
			break;
		case odd_parity:
			UCSR0C |= 0b11 << 4;
			break;
		default:
			UCSR0C |= 0b00 << 4;
			break;
	}

	// Set stop bit setting.
	if (usart->stop_bits == 1) {
		UCSR0C |= 0b0 << 3;
	}
	else {
		UCSR0C |= 0b1 << 3;
	}

	// Set data bit setting.
	switch (usart->data_bits) {
		case 5:
			UCSR0C |= 0b00 << 1;
			break;
		case 6:
			UCSR0C |= 0b01 << 1;
			break;
		case 7:
			UCSR0C |= 0b10 << 1;
			break;
		case 8:
			UCSR0C |= 0b11 << 1;
			break;
		case 9:
			UCSR0C |= 0b11 << 1;
			UCSR0B |= _BV(2);
			break;
		default:
			UCSR0C |= 0b11 << 1;
			break;
	}

	// Get and set baud rate.
	uint16_t baud_rate = F_CPU / operating_mode_prescaler / usart->baud_rate - 1;
	UBRR0H = (baud_rate & 0xFF00) >> 8;
	UBRR0L = baud_rate & 0xFF;

	//! TO-DO: check ongoing operations.
	// Set mode.
	switch (usart->mode) {
		case transmit:
			UCSR0B |= _BV(3);
			_CLEAR_BIT(UCSR0B, 4);
			break;
		case receive:
			UCSR0B |= _BV(4);
			_CLEAR_BIT(UCSR0B, 3);
			break;
		case transmit_receive:
			UCSR0B |= _BV(3);
			UCSR0B |= _BV(4);
			break;
		default:
			UCSR0B |= _BV(3);
			UCSR0B |= _BV(4);
			break;
	}
}

/**
 * @brief Transmit data over USART.
 * */
void usart_transmit(usart_t *usart, uint8_t *data, uint16_t len)
{
	uint16_t i = 0;
	while (i < (uint32_t)len) {
		if (UCSR0A & (1 << 5)) {
			UDR0 = data[i++];
		}
	}
}

/**
 * @brief Receive data over USART.
 * */
void usart_receive(usart_t *usart, uint8_t *data, uint16_t len)
{
	
}
