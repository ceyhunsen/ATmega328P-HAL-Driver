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
	//~ uint8_t reset_status = hal_system_get_reset_status();

	// Set PB5 as output, PB0 as input.
	hal_io_set_pin_mode(io_port_b, 5, io_mode_output);
	//~ hal_io_set_pin_mode(io_port_b, 0, io_mode_input_pull_up_off);

	// Read EEPROM data.
	//~ uint8_t eeprom_data[4] = {0, 127, 128, 0};
	//~ uint16_t eeprom_write_data = 0x01FF, eeprom_write_read_data = 0;
	//~ hal_eeprom_write(1, (uint8_t *)&eeprom_write_data, sizeof(eeprom_write_data));
	//~ hal_eeprom_read(0, eeprom_data, 4);
	//~ hal_eeprom_read(1, (uint8_t *)&eeprom_write_read_data, sizeof(eeprom_write_read_data));

	// Enable usart.
	hal_usart_t usart = {
		.baud_rate = 9600,
		.stop_bits = 1,
		.parity = disabled,
		.data_bits = 8,
		.operating_mode = asynchronous_normal_mode,
		.mode = transmit,
	};

	hal_usart_init(&usart);

	uint16_t packet_count = 0;
	char msg[30];

	//~ hal_system_enable_watchdog(_256k_cycles, interrupt_and_reset);

	while (1) {
		hal_io_toggle_pin(io_port_b, 5);
		//~ uint8_t read_value = hal_io_read_pin(io_port_b, 0);

		//~ if (packet_count >= 50) {
			//~ power_set_module_power(usart0_off);
			//~ power_set_sleep_mode(idle);
		//~ }
		//~ if (packet_count >= 60) {
			//~ hal_power_set_module_power(usart0_on);
		//~ }

		sprintf(msg, "%u\n", packet_count);
		hal_usart_transmit(&usart, (uint8_t *)msg, strlen(msg));

		//~ sprintf(msg, ":%u, %u, %u, %u, %u\n", eeprom_data[0], eeprom_data[1], eeprom_data[2], eeprom_data[3], eeprom_write_read_data);
		//~ hal_usart_transmit(&usart, (uint8_t *)msg, strlen(msg));

		_delay_ms(100);
		packet_count++;
	}

	return 0;
}
