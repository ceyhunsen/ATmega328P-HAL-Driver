/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for direction settings in GPIO module.
 */

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
#include "gpio.h"
#include "unity.h"
#include <test_mock_up.h>
#include <avr/io.h>
#include <stdint.h>

/**
 * Tests setting GPIO direction to output, for port b while setting one port
 * at a time.
 */
void test_direction_output_b_single()
{
	enum io_result result;
	uint8_t i;

	for (i = 0; i < 8; i++) {
		result = gpio_set_direction(io_port_b, i,
		                            io_direction_output);

		TEST_ASSERT_EQUAL(result, io_success);
		TEST_ASSERT_EQUAL(1 << i, DDRB);

		reset_registers();
	}
}

/**
 * Tests setting GPIO direction to output, for port b while setting ports
 * sequentially.
 */
void test_direction_output_b_multi()
{
	enum io_result result;
	uint8_t i, register_value;

	register_value = 0;

	for (i = 0; i < 8; i++) {
		result = gpio_set_direction(io_port_b, i,
		                            io_direction_output);

		// Every iteration, pin i should be set to ouput.
		register_value |= 1 << i;

		TEST_ASSERT_EQUAL(io_success, result);
		TEST_ASSERT_EQUAL(register_value, DDRB);
	}
}

/**
 * Tests setting GPIO direction to output, for port c while setting one port
 * at a time.
 */
void test_direction_output_c_single()
{
	enum io_result result;
	uint8_t i;

	for (i = 0; i < 8; i++) {
		result = gpio_set_direction(io_port_c, i,
		                            io_direction_output);

		TEST_ASSERT_EQUAL(result, io_success);
		TEST_ASSERT_EQUAL(1 << i, DDRC);

		reset_registers();
	}
}

/**
 * Tests setting GPIO direction to output, for port c while setting ports
 * sequentially.
 */
void test_direction_output_c_multi()
{
	enum io_result result;
	uint8_t i, register_value;

	register_value = 0;

	for (i = 0; i < 8; i++) {
		result = gpio_set_direction(io_port_c, i,
		                            io_direction_output);

		// Every iteration, pin i should be set to ouput.
		register_value |= 1 << i;

		TEST_ASSERT_EQUAL(io_success, result);
		TEST_ASSERT_EQUAL(register_value, DDRC);
	}
}

/**
 * Tests setting GPIO direction to output, for port d while setting one port
 * at a time.
 */
void test_direction_output_d_single()
{
	enum io_result result;
	uint8_t i;

	for (i = 0; i < 8; i++) {
		result = gpio_set_direction(io_port_d, i,
		                            io_direction_output);

		TEST_ASSERT_EQUAL(result, io_success);
		TEST_ASSERT_EQUAL(1 << i, DDRD);

		reset_registers();
	}
}

/**
 * Tests setting GPIO direction to output, for port b while setting ports
 * sequentially.
 */
void test_direction_output_d_multi()
{
	enum io_result result;
	uint8_t i, register_value;

	register_value = 0;

	for (i = 0; i < 8; i++) {
		result = gpio_set_direction(io_port_d, i,
		                            io_direction_output);

		// Every iteration, pin i should be set to ouput.
		register_value |= 1 << i;

		TEST_ASSERT_EQUAL(io_success, result);
		TEST_ASSERT_EQUAL(register_value, DDRD);
	}
}
