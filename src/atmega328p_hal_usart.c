/**
 * @file atmega328p_hal_usart.c
 * @author Ceyhun Şen
 * @brief USART HAL functions for ATmega328P HAL driver.
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

#include "atmega328p_hal_usart.h"
#include "atmega328p_hal_internals.h"

#ifndef F_CPU
# warning "CPU frequency (F_CPU) is not defined! Defaulting to 16 MHz..."
# define F_CPU 16000000UL
#endif // F_CPU

/*******************************************************************************
 * Standart I/O Support.
 ******************************************************************************/
#ifndef HAL_NO_STDIO

#include <stdio.h>

/**
 * @brief Transmit a char on USART.
 * @param c Char to transmit.
 * @param stream I/O stream (only here cause it's necessary).
 * @retval 0
 * */
static int usart_putchar(char c, FILE *stream)
{
	if (c == '\n')
		usart_putchar('\r', stream);
	loop_until_bit_is_set(UCSR0A, UDRE0);
	UDR0 = c;
	return 0;
}

static FILE hal_stdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

/**
 * @brief Initialize stdout.
 * */
static void hal_usart_stdio_init()
{
	stdout = &hal_stdout;
}

#endif // HAL_NO_STDIO
/*******************************************************************************
 * End of standart I/O Support.
 ******************************************************************************/

/**
 * @brief Initialize USART.
 * @param usart USART struct.
 * */
void hal_usart_init(hal_usart_t *usart)
{
	// Wait until any ongoing operation is complete.
	loop_until_bit_is_set(UCSR0A, UDRE0);

	// Get operating mode prescaler and set USART control and status register.
	uint8_t operating_mode_prescaler = 16;
	switch (usart->operating_mode) {
		case asynchronous_normal_mode:
			operating_mode_prescaler = 16;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_CLEAR_BIT(UCSR0C, UMSEL01);
			break;
		case asynchronous_double_speed_mode:
			operating_mode_prescaler = 8;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_CLEAR_BIT(UCSR0C, UMSEL01);
			break;
		case synchronous_master_mode:
			operating_mode_prescaler = 2;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_SET_BIT(UCSR0C, UMSEL01);
			break;
		default:
			operating_mode_prescaler = 16;
			_CLEAR_BIT(UCSR0C, UMSEL00);
			_CLEAR_BIT(UCSR0C, UMSEL01);
			break;
	}

	// Set parity bit setting.
	switch (usart->parity) {
		case disabled:
			_CLEAR_BIT(UCSR0C, UPM00);
			_CLEAR_BIT(UCSR0C, UPM01);
			break;
		case even_parity:
			_CLEAR_BIT(UCSR0C, UPM00);
			_SET_BIT(UCSR0C, UPM01);
			break;
		case odd_parity:
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
		case transmit:
			_SET_BIT(UCSR0B, TXEN0);
			_CLEAR_BIT(UCSR0B, RXEN0);
			break;
		case receive:
			_CLEAR_BIT(UCSR0B, TXEN0);
			_SET_BIT(UCSR0B, RXEN0);
			break;
		case transmit_and_receive:
			_SET_BIT(UCSR0B, TXEN0);
			_SET_BIT(UCSR0B, RXEN0);
			break;
		default:
			_SET_BIT(UCSR0B, TXEN0);
			_SET_BIT(UCSR0B, RXEN0);
			break;
	}

	// Standart I/O support.
	#ifndef HAL_NO_STDIO
	hal_usart_stdio_init();
	#endif // HAL_NO_STDIO
}

/**
 * @brief Transmit data over USART.
 * @param usart USART struct.
 * @param data Data buffer that will be written to USART buffer.
 * @param len Data buffer length.
 * */
void hal_usart_transmit(hal_usart_t *usart, uint8_t *data, uint16_t len)
{
	for (uint16_t i = 0; i < len; i++) {
		loop_until_bit_is_set(UCSR0A, UDRE0);
		UDR0 = data[i];
	}
}

/**
 * @brief Receive data over USART.
 * */
void hal_usart_receive(hal_usart_t *usart, uint8_t *data, uint16_t len)
{
	
}
