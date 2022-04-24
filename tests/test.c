/**
 * @file test.c
 * @author Ceyhun Şen
 * @brief Test file for ATmega328p HAL driver.
 * */

#include "atmega328p_hal.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Main function for Arduirone.
 * @returns 0 on success, 1 otherwise.
 * */
int main(void)
{
	// Enable usart.
	usart_t usart = {
		.baud_rate = 9600,
		.stop_bits = 1,
		.parity = disabled,
		.data_bits = 8,
		.operating_mode = asynchronous_normal_mode,
		.mode = transmit,
	};

	usart_init(&usart);

	uint16_t xx = 0;

	while (1) {
		char text[10];
		sprintf(text, "%u, %u\n", xx++, DDRB);
		usart_transmit(&usart, (uint8_t *)text, strlen(text));
	}

	return 0;
}
