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
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
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
enum usart_result usart_init(struct usart_t *usart)
{
	// Wait until any ongoing operation is complete.
	loop_until_bit_is_set(UCSR0A, UDRE0);

	// Get operating mode prescaler and set USART control and status register.
	uint8_t operating_mode_prescaler = 16;
	switch (usart->mode) {
		default:
		case usart_mode_asynchronous_normal:
			operating_mode_prescaler = 16;
			CLEAR_BIT(UCSR0C, UMSEL00);
			CLEAR_BIT(UCSR0C, UMSEL01);
			CLEAR_BIT(UCSR0A, U2X0);
			break;
		case usart_mode_asynchronous_double_speed:
			operating_mode_prescaler = 8;
			CLEAR_BIT(UCSR0C, UMSEL00);
			CLEAR_BIT(UCSR0C, UMSEL01);
			SET_BIT(UCSR0A, U2X0);
			break;
		case usart_mode_synchronous_master:
			operating_mode_prescaler = 2;
			CLEAR_BIT(UCSR0C, UMSEL00);
			SET_BIT(UCSR0C, UMSEL01);
			CLEAR_BIT(UCSR0A, U2X0);
			break;
	}

	// Set parity bit setting.
	switch (usart->parity) {
		default:
		case usart_parity_disabled:
			CLEAR_BIT(UCSR0C, UPM00);
			CLEAR_BIT(UCSR0C, UPM01);
			break;
		case usart_parity_even:
			CLEAR_BIT(UCSR0C, UPM00);
			SET_BIT(UCSR0C, UPM01);
			break;
		case usart_parity_odd:
			SET_BIT(UCSR0C, UPM00);
			SET_BIT(UCSR0C, UPM01);
			break;
	}

	// Set stop bit setting.
	if (usart->stop_bits == 1) {
		CLEAR_BIT(UCSR0C, USBS0);
	}
	else {
		SET_BIT(UCSR0C, USBS0);
	}

	// Set data bit setting.
	switch (usart->data_bits) {
		case 5:
			CLEAR_BIT(UCSR0C, UCSZ00);
			CLEAR_BIT(UCSR0C, UCSZ01);
			break;
		case 6:
			SET_BIT(UCSR0C, UCSZ00);
			CLEAR_BIT(UCSR0C, UCSZ01);
			break;
		case 7:
			CLEAR_BIT(UCSR0C, UCSZ00);
			SET_BIT(UCSR0C, UCSZ01);
			break;
		case 8:
			SET_BIT(UCSR0C, UCSZ00);
			SET_BIT(UCSR0C, UCSZ01);
			break;
		case 9:
			SET_BIT(UCSR0C, UCSZ00);
			SET_BIT(UCSR0C, UCSZ01);
			SET_BIT(UCSR0B, UCSZ02);
			break;
		default:
			SET_BIT(UCSR0C, UCSZ00);
			SET_BIT(UCSR0C, UCSZ01);
			break;
	}

	// Get and set baud rate.
	uint16_t baud_rate = F_CPU / operating_mode_prescaler / usart->baud_rate - 1;
	UBRR0H = (baud_rate & 0xFF00) >> 8;
	UBRR0L = baud_rate & 0xFF;

	// Set mode.
	switch (usart->direction) {
		case usart_direction_transmit:
			SET_BIT(UCSR0B, TXEN0);
			CLEAR_BIT(UCSR0B, RXEN0);
			break;
		case usart_direction_receive:
			CLEAR_BIT(UCSR0B, TXEN0);
			SET_BIT(UCSR0B, RXEN0);
			break;
		case usart_direction_transmit_and_receive:
			SET_BIT(UCSR0B, TXEN0);
			SET_BIT(UCSR0B, RXEN0);
			break;
		default:
			SET_BIT(UCSR0B, TXEN0);
			SET_BIT(UCSR0B, RXEN0);
			break;
	}

	return usart_success;
}

/**
 * @brief Transmit data over USART.
 * @param usart USART struct.
 * @param data Data buffer that will be written to USART buffer.
 * @param len Data buffer length.
 * */
enum usart_result usart_transmit(struct usart_t *usart, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Wait till' any ongoing transfer is complete.
		loop_until_bit_is_set(UCSR0A, UDRE0);

		// Write data to the USART data register.
		UDR0 = data[i];
	}

	return usart_success;
}

/**
 * @brief Receive data over USART.
 * @param usart USART struct.
 * @param data Data buffer that will hold read data from USART buffer.
 * @param len Data buffer length.
 * */
enum usart_result usart_receive(struct usart_t *usart, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		// Wait till' any ongoing transfer is complete.
		loop_until_bit_is_set(UCSR0A, UDRE0);

		// Wait till' data is received.
		loop_until_bit_is_set(UCSR0A, RXC0);

		// Read data from USART data register.
		data[i] = UDR0;
	}

	return usart_success;
}
