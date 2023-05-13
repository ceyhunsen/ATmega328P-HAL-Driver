/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for toggle operations in GPIO module.
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

void test_toggle_b_single()
{
	enum gpio_result result;
	uint8_t i;

	for (i = 0; i < 8; i++) {
		result = gpio_toggle(gpio_port_b, i);

		TEST_ASSERT_EQUAL(result, gpio_success);
		TEST_ASSERT_EQUAL(1 << i, PINB);

		reset_registers();
	}
}

void test_toggle_b_multi()
{
	enum gpio_result result;
	uint8_t i, register_value;

	register_value = 0;

	for (i = 0; i < 8; i++) {
		result = gpio_toggle(gpio_port_b, i);

		// Every iteration, pin i should be set to ouput.
		register_value |= 1 << i;

		TEST_ASSERT_EQUAL(gpio_success, result);
		TEST_ASSERT_EQUAL(register_value, PINB);
	}
}

void test_toggle_c_single()
{
	enum gpio_result result;
	uint8_t i;

	for (i = 0; i < 8; i++) {
		result = gpio_toggle(gpio_port_c, i);

		TEST_ASSERT_EQUAL(result, gpio_success);
		TEST_ASSERT_EQUAL(1 << i, PINC);

		reset_registers();
	}
}

void test_toggle_c_multi()
{
	enum gpio_result result;
	uint8_t i, register_value;

	register_value = 0;

	for (i = 0; i < 8; i++) {
		result = gpio_toggle(gpio_port_c, i);

		// Every iteration, pin i should be set to ouput.
		register_value |= 1 << i;

		TEST_ASSERT_EQUAL(gpio_success, result);
		TEST_ASSERT_EQUAL(register_value, PINC);
	}
}

void test_toggle_d_single()
{
	enum gpio_result result;
	uint8_t i;

	for (i = 0; i < 8; i++) {
		result = gpio_toggle(gpio_port_d, i);

		TEST_ASSERT_EQUAL(result, gpio_success);
		TEST_ASSERT_EQUAL(1 << i, PIND);

		reset_registers();
	}
}

void test_toggle_d_multi()
{
	enum gpio_result result;
	uint8_t i, register_value;

	register_value = 0;

	for (i = 0; i < 8; i++) {
		result = gpio_toggle(gpio_port_d, i);

		// Every iteration, pin i should be set to ouput.
		register_value |= 1 << i;

		TEST_ASSERT_EQUAL(gpio_success, result);
		TEST_ASSERT_EQUAL(register_value, PIND);
	}
}
