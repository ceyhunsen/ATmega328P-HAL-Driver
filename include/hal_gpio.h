/**
 * @file
 * @author Ceyhun Şen
 * @brief Enumeration and function declarations for GPIO module.
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
 * Return results for GPIO module.
 */
enum gpio_result {
	gpio_success = 0,
	gpio_error,
};

/**
 * Pin states for GPIO module.
 * */
enum gpio_state {
	gpio_state_low  = 0,
	gpio_state_high = 1
};

/**
 * Direction options for GPIO.
 * */
enum gpio_direction {
	gpio_direction_output = 0,
	gpio_direction_input_pull_up_off,
	gpio_direction_input_pull_up_on
};

/**
 * Ports for GPIO.
 * */
enum gpio_port {
	gpio_port_b,
	gpio_port_c,
	gpio_port_d
};

enum gpio_result gpio_set_direction(enum gpio_port port, uint8_t pin,
                                    enum gpio_direction mode);
enum gpio_result gpio_write(enum gpio_port port, uint8_t pin,
                            enum gpio_state state);
enum gpio_result gpio_toggle_pin(enum gpio_port port, uint8_t pin);
enum gpio_result gpio_read_pin(enum gpio_port port, uint8_t pin,
                               enum gpio_state *state);

#endif // __HAL_GPIO_H
