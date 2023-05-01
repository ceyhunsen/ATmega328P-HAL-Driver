/**
 * @file
 * @author Ceyhun Şen
 * @brief USART HAL functions for ATmega328P HAL driver.
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

#include "hal_usart.h"
#include "hal_internals.h"
#include <avr/io.h>

#ifndef F_CPU
# warning "CPU frequency (F_CPU) is not defined! Defaulting to 16 MHz..."
# define F_CPU 16000000UL
#endif // F_CPU

/**
 * @brief Initialize USART.
 * @param usart USART struct.
 * */
void usart_init(usart_t *usart)
{
	// Wait until any ongoing operation is complete.
	loop_until_bit_is_set(UCSR0A, UDRE0);

	// Get operating mode prescaler and set USART control and status register.
	uint8_t operating_mode_prescaler = 16;
	switch (usart->operating_mode) {
		case usart_asynchronous_normal_mode:
			operating_mode_prescaler = 16;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_CLEAR_BIT(UCSR0C, UMSEL01);
			_CLEAR_BIT(UCSR0A, U2X0);
			break;
		case usart_asynchronous_double_speed_mode:
			operating_mode_prescaler = 8;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_CLEAR_BIT(UCSR0C, UMSEL01);
			_SET_BIT(UCSR0A, U2X0);
			break;
		case usart_synchronous_master_mode:
			operating_mode_prescaler = 2;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_SET_BIT(UCSR0C, UMSEL01);
			_CLEAR_BIT(UCSR0A, U2X0);
			break;
		default:
			operating_mode_prescaler = 16;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_CLEAR_BIT(UCSR0C, UMSEL01);
			_CLEAR_BIT(UCSR0A, U2X0);
			break;
	}

	// Set parity bit setting.
	switch (usart->parity) {
		case usart_parity_disabled:
			_CLEAR_BIT(UCSR0C, UPM00);
			_CLEAR_BIT(UCSR0C, UPM01);
			break;
		case usart_even_parity:
			_CLEAR_BIT(UCSR0C, UPM00);
			_SET_BIT(UCSR0C, UPM01);
			break;
		case usart_odd_parity:
			_SET_BIT(UCSR0C, UPM00);
			_SET_BIT(UCSR0C, UPM01);
			break;
		default:
			_CLEAR_BIT(UCSR0C, UPM00);
			_CLEAR_BIT(UCSR0C, UPM01);
			break;
	}

	// Set stop bit setting.
	if (usart->stop_bits == 1) {
		_CLEAR_BIT(UCSR0C, USBS0);
	}
	else {
		_SET_BIT(UCSR0C, USBS0);
	}

	// Set data bit setting.
	switch (usart->data_bits) {
		case 5:
			_CLEAR_BIT(UCSR0C, UCSZ00);
			_CLEAR_BIT(UCSR0C, UCSZ01);
			break;
		case 6:
			_SET_BIT(UCSR0C, UCSZ00);
			_CLEAR_BIT(UCSR0C, UCSZ01);
			break;
		case 7:
			_CLEAR_BIT(UCSR0C, UCSZ00);
			_SET_BIT(UCSR0C, UCSZ01);
			break;
		case 8:
			_SET_BIT(UCSR0C, UCSZ00);
			_SET_BIT(UCSR0C, UCSZ01);
			break;
		case 9:
			_SET_BIT(UCSR0C, UCSZ00);
			_SET_BIT(UCSR0C, UCSZ01);
			_SET_BIT(UCSR0B, UCSZ02);
			break;
		default:
			_SET_BIT(UCSR0C, UCSZ00);
			_SET_BIT(UCSR0C, UCSZ01);
			break;
	}

	// Get and set baud rate.
	uint16_t baud_rate = F_CPU / operating_mode_prescaler / usart->baud_rate - 1;
	UBRR0H = (baud_rate & 0xFF00) >> 8;
	UBRR0L = baud_rate & 0xFF;

	// Set mode.
	switch (usart->mode) {
		case usart_transmit_mode:
			_SET_BIT(UCSR0B, TXEN0);
			_CLEAR_BIT(UCSR0B, RXEN0);
			break;
		case usart_receive_mode:
			_CLEAR_BIT(UCSR0B, TXEN0);
			_SET_BIT(UCSR0B, RXEN0);
			break;
		case usart_transmit_and_receive_mode:
			_SET_BIT(UCSR0B, TXEN0);
			_SET_BIT(UCSR0B, RXEN0);
			break;
		default:
			_SET_BIT(UCSR0B, TXEN0);
			_SET_BIT(UCSR0B, RXEN0);
			break;
	}
}

/**
 * @brief Transmit data over USART.
 * @param usart USART struct.
 * @param data Data buffer that will be written to USART buffer.
 * @param len Data buffer length.
 * */
void usart_transmit(usart_t *usart, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Wait till' any ongoing transfer is complete.
		loop_until_bit_is_set(UCSR0A, UDRE0);

		// Write data to the USART data register.
		UDR0 = data[i];
	}
}

/**
 * @brief Receive data over USART.
 * @param usart USART struct.
 * @param data Data buffer that will hold read data from USART buffer.
 * @param len Data buffer length.
 * */
void usart_receive(usart_t *usart, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Wait till' any ongoing transfer is complete.
		loop_until_bit_is_set(UCSR0A, UDRE0);

		// Wait till' data is received.
		loop_until_bit_is_set(UCSR0A, RXC0);

		// Read data from USART data register.
		data[i] = UDR0;
	}
}
