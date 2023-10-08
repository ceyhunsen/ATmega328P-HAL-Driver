/**
 * @file
 * @author Ceyhun Şen
 * 
 * Standard GPIO operations.
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

#include "hal_gpio.h"
#include "hal_internals.h"
#include <avr/io.h>

static volatile uint8_t *get_ddr_pointer(enum gpio_port port);
static volatile uint8_t *get_port_pointer(enum gpio_port port);
static volatile uint8_t *get_pin_pointer(enum gpio_port port);

/**
 * Configure a GPIO pin.
 * 
 * @param gpio GPIO pin to be configured.
 * @param configuration How to configure selected pin.
 */
enum gpio_result gpio_configure(struct gpio_pin gpio,
                                struct gpio_pin_configuration configuration)
{
	// Get port pointers.
	volatile uint8_t *ddr_pointer, *port_pointer;
	uint8_t ddr_value, port_value;

	ddr_pointer = get_ddr_pointer(gpio.port);
	port_pointer = get_port_pointer(gpio.port);

	// Read register values before doing a modification. Reading these
	// values beforehand will help in case of an interruption from another
	// context like interrupts.
	ddr_value = *ddr_pointer;
	port_value = *port_pointer;

	// Set direction.
	switch (configuration.direction) {
	case gpio_direction_output:
		// Tri-state intermediate step.
		if (!(ddr_value & BIT(gpio.pin)) &&
			!(port_value & BIT(gpio.pin))) {
			CLEAR_BIT(*port_pointer, gpio.pin);
		}
		// Input pull up intermediate step.
		if (!(ddr_value & BIT(gpio.pin)) &&
			(port_value & BIT(gpio.pin))) {
			CLEAR_BIT(*port_pointer, gpio.pin);
		}

		SET_BIT(*ddr_pointer, gpio.pin);

		break;
	default:
	case gpio_direction_input:
		if (configuration.is_pull_up) {
			// Output low intermediate step.
			if ((ddr_value & BIT(gpio.pin)) &&
			!(port_value & BIT(gpio.pin))) {
				SET_BIT(*port_pointer, gpio.pin);
			}

			CLEAR_BIT(*ddr_pointer, gpio.pin);
			SET_BIT(*port_pointer, gpio.pin);
		}
		else {
			// Output high intermediate step.
			if ((ddr_value & BIT(gpio.pin)) &&
				(port_value & BIT(gpio.pin))) {
				SET_BIT(*ddr_pointer, gpio.pin);
				CLEAR_BIT(*port_pointer, gpio.pin);
			}

			CLEAR_BIT(*ddr_pointer, gpio.pin);
			CLEAR_BIT(*port_pointer, gpio.pin);
		}
	}

	return gpio_success;
}

/**
 * Set pin state of given GPIO pin.
 * 
 * @param gpio Target GPIO pin.
 * @param state Pin state to be set.
 * */
enum gpio_result gpio_write(struct gpio_pin gpio, enum gpio_pin_state state)
{
	volatile uint8_t *port_pointer;
	port_pointer = get_port_pointer(gpio.port);

	switch (state) {
	case gpio_state_high:
		SET_BIT(*port_pointer, gpio.pin);
		break;
	default:
	case gpio_state_low:
		CLEAR_BIT(*port_pointer, gpio.pin);
		break;
	}

	return gpio_success;
}

/**
 * Toggle state of the given pin.
 * 
 * @param gpio Target GPIO pin.
 * */
enum gpio_result gpio_toggle(struct gpio_pin gpio)
{
	volatile uint8_t *pin_pointer;

	pin_pointer = get_pin_pointer(gpio.port);

	SET_BIT(*pin_pointer, gpio.pin);

	return gpio_success;
}

/**
 * Read value of a GPIO pin.
 * 
 * @param gpio Target GPIO pin.
 * @param state Pointer that will hold read result.
 * */
enum gpio_result gpio_read(struct gpio_pin gpio, enum gpio_pin_state *state)
{
	volatile uint8_t *pin_pointer;
	pin_pointer = get_pin_pointer(gpio.port);

	uint8_t pin_value = *pin_pointer;

	*state = (pin_value & BIT(gpio.pin))? gpio_state_high:
	                                      gpio_state_low;

	return gpio_success;
}

/**
 * @brief Get DDRx pointer.
 * 
 * @param port GPIO port.
 * @returns DDRx pointer
 * @see gpio_port
 * */
static volatile uint8_t *get_ddr_pointer(enum gpio_port port)
{
	volatile uint8_t *p;

	switch (port) {
		default:
		case gpio_port_b:
			p = &DDRB;
			break;
		case gpio_port_c:
			p = &DDRC;
			break;
		case gpio_port_d:
			p = &DDRD;
			break;
	}

	return p;
}

/**
 * @brief Get PORTx pointer.
 * 
 * @param port GPIO port.
 * @returns PORTx pointer.
 * @see gpio_port
 * */
static volatile uint8_t *get_port_pointer(enum gpio_port port)
{
	volatile uint8_t *p;

	switch (port) {
		default:
		case gpio_port_b:
			p = &PORTB;
			break;
		case gpio_port_c:
			p = &PORTC;
			break;
		case gpio_port_d:
			p = &PORTD;
			break;
	}

	return p;
}

/**
 * @brief Get PINx pointer.
 * 
 * @param port GPIO port.
 * @returns PINx pointer.
 * @see gpio_port
 * */
static volatile uint8_t *get_pin_pointer(enum gpio_port port)
{
	volatile uint8_t *p;

	switch (port) {
		default:
		case gpio_port_b:
			p = &PINB;
			break;
		case gpio_port_c:
			p = &PINC;
			break;
		case gpio_port_d:
			p = &PIND;
			break;
	}

	return p;
}
