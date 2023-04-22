/**
 * @file
 * @author Ceyhun Şen
 * @brief GPIO functions for ATmega328P HAL driver.
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

#include "hal_gpio.h"
#include "hal_internals.h"
#include <avr/io.h>

static volatile uint8_t *get_ddr_pointer(gpio_ports port);
static volatile uint8_t *get_port_pointer(gpio_ports port);
static volatile uint8_t *get_pin_pointer(gpio_ports port);

/**
 * @brief Set pin mode of given port/pin.
 * @param port I/O port.
 * @param pin Pin of specified I/O port.
 * @param mode Pin mode to be set.
 * @see gpio_ports
 * @see gpio_pin_modes
 * */
void gpio_set_pin_mode(gpio_ports port, uint8_t pin, gpio_pin_modes mode)
{
	// Get port pointers.
	volatile uint8_t *ddr_pointer, *port_pointer;
	ddr_pointer = get_ddr_pointer(port);
	port_pointer = get_port_pointer(port);

	// Read register values.
	uint8_t ddr_value = *ddr_pointer;
	uint8_t port_value = *port_pointer;

	// Set mode.
	switch (mode) {
		case gpio_output_mode:
			// Tri-state intermediate step.
			if (!(ddr_value & _PIN_TO_BIT(pin)) && !(port_value & _PIN_TO_BIT(pin))) {
				_CLEAR_BIT(*port_pointer, pin);
			}
			// Input pull up intermediate step.
			if (!(ddr_value & _PIN_TO_BIT(pin)) && (port_value & _PIN_TO_BIT(pin))) {
				_CLEAR_BIT(*port_pointer, pin);
			}
			_SET_BIT(*ddr_pointer, pin);
			break;
		case gpio_input_pull_up_on_mode:
			// Output low intermediate step.
			if ((ddr_value & _PIN_TO_BIT(pin)) && !(port_value & _PIN_TO_BIT(pin))) {
				_SET_BIT(*port_pointer, pin);
			}
			_CLEAR_BIT(*ddr_pointer, pin);
			_SET_BIT(*port_pointer, pin);
			break;
		case gpio_input_pull_up_off_mode:
			// Output high intermediate step.
			if ((ddr_value & _PIN_TO_BIT(pin)) && (port_value & _PIN_TO_BIT(pin))) {
				_SET_BIT(*ddr_pointer, pin);
				_CLEAR_BIT(*port_pointer, pin);
			}
			_CLEAR_BIT(*ddr_pointer, pin);
			_CLEAR_BIT(*port_pointer, pin);
			break;
	}
}

/**
 * @brief Set pin mode of given port/pin.
 * @param port I/O port.
 * @param pin Pin of specified I/O port.
 * @param state Pin state to be set.
 * @see gpio_ports
 * @see gpio_pin_states
 * */
void gpio_write_pin(gpio_ports port, uint8_t pin, gpio_pin_states state)
{
	volatile uint8_t *port_pointer;
	port_pointer = get_port_pointer(port);

	switch (state) {
		case gpio_high_state:
			_SET_BIT(*port_pointer, pin);
			break;
		case gpio_low_state:
			_CLEAR_BIT(*port_pointer, pin);
			break;
	}
}

/**
 * @brief Toggle given pin.
 * @param port I/O port.
 * @param pin Pin of specified I/O port.
 * @see gpio_ports
 * */
void gpio_toggle_pin(gpio_ports port, uint8_t pin)
{
	volatile uint8_t *pin_pointer;
	pin_pointer = get_pin_pointer(port);

	_SET_BIT(*pin_pointer, pin);
}

/**
 * @brief Read value of a pin.
 * @param port I/O port.
 * @param pin Pin of specified I/O port.
 * @returns 1 if pin is high, 0 otherwise.
 * @see gpio_ports
 * */
uint8_t gpio_read_pin(gpio_ports port, uint8_t pin)
{
	volatile uint8_t *pin_pointer;
	pin_pointer = get_pin_pointer(port);

	uint8_t pin_value = *pin_pointer;

	return (pin_value & _PIN_TO_BIT(pin))? 1: 0;
}

/**
 * @brief Get DDRx pointer.
 * @param port I/O port.
 * @returns DDRx pointer
 * @see gpio_ports
 * */
static volatile uint8_t *get_ddr_pointer(gpio_ports port)
{
	volatile uint8_t *p;

	switch (port) {
		case gpio_port_b:
			p = &DDRB;
			break;
		case gpio_port_c:
			p = &DDRC;
			break;
		case gpio_port_d:
			p = &DDRD;
			break;
		default:
			p = &DDRB;
			break;
	}

	return p;
}

/**
 * @brief Get PORTx pointer.
 * @param port I/O port.
 * @returns PORTx pointer.
 * @see gpio_ports
 * */
static volatile uint8_t *get_port_pointer(gpio_ports port)
{
	volatile uint8_t *p;

	switch (port) {
		case gpio_port_b:
			p = &PORTB;
			break;
		case gpio_port_c:
			p = &PORTC;
			break;
		case gpio_port_d:
			p = &PORTD;
			break;
		default:
			p = &PORTB;
			break;
	}

	return p;
}

/**
 * @brief Get PINx pointer.
 * @param port I/O port.
 * @returns PINx pointer.
 * @see gpio_ports
 * */
static volatile uint8_t *get_pin_pointer(gpio_ports port)
{
	volatile uint8_t *p;

	switch (port) {
		case gpio_port_b:
			p = &PINB;
			break;
		case gpio_port_c:
			p = &PINC;
			break;
		case gpio_port_d:
			p = &PIND;
			break;
		default:
			p = &PINB;
			break;
	}

	return p;
}
