/**
 * @file
 * @author Ceyhun Şen
 * @brief GPIO header file for ATmega328P HAL driver.
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

#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H

#include <stdint.h>

/**
 * @enum
 * @brief Pin states for GPIO module.
 * */
enum gpio_pin_states {
	gpio_state_low  = 0,
	gpio_state_high = 1
};

/**
 * @enum
 * @brief Pin modes for GPIO module.
 * */
enum gpio_pin_modes {
	gpio_mode_output = 0,
	gpio_mode_input_pull_up_off,
	gpio_mode_input_pull_up_on
};

/**
 * @enum
 * @brief Ports for GPIO module.
 * */
enum gpio_ports {
	gpio_port_b,
	gpio_port_c,
	gpio_port_d
};

void gpio_set_pin_mode(gpio_ports port, uint8_t pin, gpio_pin_modes mode);
void gpio_write_pin(gpio_ports port, uint8_t pin, gpio_pin_states state);
void gpio_toggle_pin(gpio_ports port, uint8_t pin);
uint8_t gpio_read_pin(gpio_ports port, uint8_t pin);

#endif // __HAL_GPIO_H
