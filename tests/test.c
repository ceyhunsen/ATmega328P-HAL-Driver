/**
 * @file test.c
 * @author Ceyhun Şen
 * @brief Test file for ATmega328p HAL driver.
 * */

#include "atmega328p_hal.h"

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h>
#include <string.h>

int main(void)
{
	// Set PB5 as output.
	hal_io_set_pin_mode(io_port_b, 5, io_mode_output);

	// Enable usart.
	hal_usart_t usart = {
		.baud_rate = 115200,
		.stop_bits = 1,
		.parity = disabled,
		.data_bits = 8,
		.operating_mode = asynchronous_double_speed_mode,
		.mode = transmit_and_receive,
	};

	hal_usart_init(&usart);
	hal_usart_stdio_init();

	uint16_t packet_count = 0;

	while (1) {
		hal_io_toggle_pin(io_port_b, 5);

		printf("%u\n", packet_count);

		packet_count++;
		_delay_ms(100);
	}

	return 0;
}
