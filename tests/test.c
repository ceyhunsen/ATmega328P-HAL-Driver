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
	hal_io_set_pin_mode(hal_io_port_b, 5, hal_io_output_mode);

	// Enable usart.
	hal_usart_t usart = {
		.baud_rate = 115200,
		.stop_bits = 1,
		.parity = hal_usart_parity_disabled,
		.data_bits = 8,
		.operating_mode = hal_usart_asynchronous_double_speed_mode,
		.mode = hal_usart_transmit_and_receive_mode,
	};

	hal_usart_init(&usart);
	hal_usart_stdio_init();

	uint16_t packet_count = 0;

	while (1) {
		hal_io_toggle_pin(hal_io_port_b, 5);

		printf("%u\n", packet_count);

		packet_count++;
		_delay_ms(100);
	}

	return 0;
}
