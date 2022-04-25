/**
 * @file io.h
 * @author Ceyhun Şen
 * @brief I/O header file for ATmega328P HAL driver.
 * */

/*
 * MIT License
 * 
 * Copyright (c) 2022 Ceyhun Şen
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

#ifndef __IO_H
#define __IO_H

#include <stdint.h>

/**
 * @enum io_pin_states
 * @brief Pin states for I/O.
 * */
typedef enum io_pin_states {
	io_state_high,
	io_state_low
} io_pin_states;

/**
 * @enum io_pin_modes
 * @brief Pin modes for I/O.
 * */
typedef enum io_pin_modes {
	io_mode_output,
	io_mode_input_pull_up_on,
	io_mode_input_pull_up_off
} io_pin_modes;

/**
 * @enum io_ports
 * @brief Ports for I/O.
 * */
typedef enum io_ports {
	io_port_b,
	io_port_c,
	io_port_d
} io_ports;

void io_set_pin_mode(io_ports port, uint8_t pin, io_pin_modes mode);
void io_write_pin(io_ports port, uint8_t pin, io_pin_states state);
void io_toggle_pin(io_ports port, uint8_t pin);
uint8_t io_read_pin(io_ports port, uint8_t pin);

#endif // __IO_H
