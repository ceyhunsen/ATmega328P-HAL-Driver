/**
 * @file
 * @author Ceyhun Şen
 * 
 * Main header for ATMega328P HAL driver GPIO module.
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

#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#include <stdint.h>

/**
 * Module specific return results.
 */
enum gpio_result {
	gpio_success = 0,
	gpio_error,
};

/**
 * Port specifier of a GPIO pin.
 */
enum gpio_port {
	gpio_port_b = 0,
	gpio_port_c,
	gpio_port_d
};

/**
 * GPIO pin specifier.
 * 
 * @param port Target port.
 * @param pin Target pin of the port
 */
struct gpio_pin {
	enum gpio_port port;
	uint8_t pin;
};

/**
 * State of the current GPIO pin.
 */
enum gpio_pin_state {
	gpio_state_low  = 0,
	gpio_state_high = 1
};

/**
 * Direction settings for GPIO pins.
 */
enum gpio_pin_direction {
	gpio_direction_output,
	gpio_direction_input
};

/**
 * Configuration options for a GPIO pin.
 * 
 * @param direction Direction of the pin.
 * @param pull_up Is pull-up enabled? 0 on disabled, 1 (or other values) on
 * enabled.
 */
struct gpio_pin_configuration {
	enum gpio_pin_direction direction;
	uint8_t is_pull_up;
};

enum gpio_result gpio_configure(struct gpio_pin gpio,
                                struct gpio_pin_configuration configuration);
enum gpio_result gpio_write(struct gpio_pin gpio, enum gpio_pin_state state);
enum gpio_result gpio_toggle(struct gpio_pin gpio);
enum gpio_result gpio_read(struct gpio_pin gpio, enum gpio_pin_state *state);

#endif // __HAL_GPIO_H
