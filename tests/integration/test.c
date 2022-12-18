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

	hal_twi_init(hal_twi_fast_mode);

	uint16_t packet_count = 0;
	uint8_t buffer[3] = {2, 2, 2}, ret = 0;

	printf("ATmega328P started!\n");

	buffer[0] = 23;
	ret = hal_twi_write_memory(0b1101000, 119, hal_twi_register_size_1_byte, buffer, 1);

	while (1) {
		hal_io_toggle_pin(hal_io_port_b, 5);

		ret = hal_twi_read_memory(0b1101000, 117, hal_twi_register_size_1_byte, buffer, sizeof(buffer));

		printf("%u, %u: %u %u %u\n", packet_count, ret, buffer[0], buffer[1], buffer[2]);

		packet_count++;
		_delay_ms(100);
	}

	return 0;
}
