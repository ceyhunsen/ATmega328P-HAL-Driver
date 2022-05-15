/**
 * @file atmega328p_hal_usart_extra.c
 * @author Ceyhun Şen
 * @brief USART extra HAL functions for ATmega328P HAL driver.
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

/*******************************************************************************
 * Standart I/O support.
 ******************************************************************************/
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

/**
 * @brief Initialize stdio.
 * */
void hal_usart_stdio_init()
{
	static FILE hal_stdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);
	stdout = &hal_stdout;
}
/*******************************************************************************
 * End of standart I/O support.
 ******************************************************************************/
