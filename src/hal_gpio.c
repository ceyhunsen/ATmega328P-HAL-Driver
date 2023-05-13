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
 * @brief Set pin direction of given gpio pin.
 * 
 * @param port Gpio port.
 * @param pin Pin number of specified gpio port.
 * @param direction Direction to be set.
 * */
enum gpio_result gpio_set_direction(enum gpio_port port, uint8_t pin,
                                    enum gpio_direction direction)
{
	// Get port pointers.
	volatile uint8_t *ddr_pointer, *port_pointer;
	uint8_t ddr_value, port_value;

	ddr_pointer = get_ddr_pointer(port);
	port_pointer = get_port_pointer(port);

	// Read register values.
	ddr_value = *ddr_pointer;
	port_value = *port_pointer;

	// Set direction.
	switch (direction) {
		case gpio_direction_output:
			// Tri-state intermediate step.
			if (!(ddr_value & BIT(pin)) &&
			    !(port_value & BIT(pin))) {
				CLEAR_BIT(*port_pointer, pin);
			}
			// Input pull up intermediate step.
			if (!(ddr_value & BIT(pin)) &&
			    (port_value & BIT(pin))) {
				CLEAR_BIT(*port_pointer, pin);
			}

			SET_BIT(*ddr_pointer, pin);

			break;
		case gpio_direction_input_pull_up_on:
			// Output low intermediate step.
			if ((ddr_value & BIT(pin)) &&
			    !(port_value & BIT(pin))) {
				SET_BIT(*port_pointer, pin);
			}

			CLEAR_BIT(*ddr_pointer, pin);
			SET_BIT(*port_pointer, pin);

			break;
		case gpio_direction_input_pull_up_off:
			// Output high intermediate step.
			if ((ddr_value & BIT(pin)) &&
			    (port_value & BIT(pin))) {
				SET_BIT(*ddr_pointer, pin);
				CLEAR_BIT(*port_pointer, pin);
			}

			CLEAR_BIT(*ddr_pointer, pin);
			CLEAR_BIT(*port_pointer, pin);

			break;
	}

	return gpio_success;
}

/**
 * @brief Set pin mode of given port/pin.
 * 
 * @param port GPIO port.
 * @param pin Pin of specified GPIO port.
 * @param state Pin state to be set.
 * */
enum gpio_result gpio_write(enum gpio_port port, uint8_t pin,
                            enum gpio_state state)
{
	volatile uint8_t *port_pointer;
	port_pointer = get_port_pointer(port);

	switch (state) {
		case gpio_state_high:
			SET_BIT(*port_pointer, pin);
			break;
		case gpio_state_low:
			CLEAR_BIT(*port_pointer, pin);
			break;
	}

	return gpio_success;
}

/**
 * @brief Toggle given pin.
 * 
 * @param port GPIO port.
 * @param pin Pin of specified GPIO port.
 * */
enum gpio_result gpio_toggle(enum gpio_port port, uint8_t pin)
{
	volatile uint8_t *pin_pointer;

	pin_pointer = get_pin_pointer(port);

	SET_BIT(*pin_pointer, pin);

	return gpio_success;
}

/**
 * @brief Read value of a pin.
 * 
 * @param port GPIO port.
 * @param pin Pin of specified GPIO port.
 * @returns 1 if pin is high, 0 otherwise.
 * */
enum gpio_result gpio_read(enum gpio_port port, uint8_t pin,
                           enum gpio_state *state)
{
	volatile uint8_t *pin_pointer;
	pin_pointer = get_pin_pointer(port);

	uint8_t pin_value = *pin_pointer;

	*state = (pin_value & BIT(pin))? gpio_state_high:
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
