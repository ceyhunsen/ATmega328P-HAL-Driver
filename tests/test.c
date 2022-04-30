/**
 * @file test.c
 * @author Ceyhun Şen
 * @brief Test file for ATmega328p HAL driver.
 * */

#include "atmega328p_hal.h"

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
	// Set PB5 as output, PB0 as input.
	io_set_pin_mode(io_port_b, 5, io_mode_output);
	io_set_pin_mode(io_port_b, 0, io_mode_input_pull_up_off);

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

	uint16_t packet_count = 0;
	char msg[20];

	while (1) {
		io_toggle_pin(io_port_b, 5);
		uint8_t read_value = io_read_pin(io_port_b, 0);

		sprintf(msg, "%u, %u, %u\n", packet_count++, read_value, PINB);
		usart_transmit(&usart, (uint8_t *)msg, strlen(msg));
		_delay_ms(100);
	}

	return 0;
}
