/**
 * @file
 * @author Ceyhun Şen
 * @brief Unit tests for power management and sleep modes module.
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

#include "hal_power.h"
#include "test_mock_up.h"
#include "unity.h"
#include <avr/io.h>

void test_power_idle_mode()
{
	enum power_sleep_modes mode;

	mode = power_idle_mode;

	power_set_sleep_mode(mode);

	// Test if register value is correct.
	TEST_ASSERT_EQUAL(0b000 << 1, SMCR & 0b1110);

	// Test if enum value is the same with register value.
	TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

	// Test if sleep enable bit is disabled.
	TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_adc_noise_reduction_mode()
{
	enum power_sleep_modes mode;

	mode = power_adc_noise_reduction_mode;

	power_set_sleep_mode(mode);

	// Test if register value is correct.
	TEST_ASSERT_EQUAL(0b001 << 1, SMCR & 0b1110);

	// Test if enum value is the same with register value.
	TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

	// Test if sleep enable bit is disabled.
	TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_power_down_mode()
{
	enum power_sleep_modes mode;

	mode = power_power_down_mode;

	power_set_sleep_mode(mode);

	// Test if register value is correct.
	TEST_ASSERT_EQUAL(0b010 << 1, SMCR & 0b1110);

	// Test if enum value is the same with register value.
	TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

	// Test if sleep enable bit is disabled.
	TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_power_save_mode()
{
	enum power_sleep_modes mode;

	mode = power_power_save_mode;

	power_set_sleep_mode(mode);

	// Test if register value is correct.
	TEST_ASSERT_EQUAL(0b011 << 1, SMCR & 0b1110);

	// Test if enum value is the same with register value.
	TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

	// Test if sleep enable bit is disabled.
	TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_standby_mode()
{
	enum power_sleep_modes mode;

	mode = power_standby_mode;

	power_set_sleep_mode(mode);

	// Test if register value is correct.
	TEST_ASSERT_EQUAL(0b110 << 1, SMCR & 0b1110);

	// Test if enum value is the same with register value.
	TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

	// Test if sleep enable bit is disabled.
	TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

void test_power_external_standby_mode()
{
	enum power_sleep_modes mode;

	mode = power_external_standby_mode;

	power_set_sleep_mode(mode);

	// Test if register value is correct.
	TEST_ASSERT_EQUAL(0b111 << 1, SMCR & 0b1110);

	// Test if enum value is the same with register value.
	TEST_ASSERT_EQUAL(mode << 1, SMCR & 0b1110);

	// Test if sleep enable bit is disabled.
	TEST_ASSERT_EQUAL(0, SMCR & 0b1);
}

int main()
{
	RUN_TEST(test_power_idle_mode);
	RUN_TEST(test_power_adc_noise_reduction_mode);
	RUN_TEST(test_power_power_down_mode);
	RUN_TEST(test_power_power_save_mode);
	RUN_TEST(test_power_standby_mode);
	RUN_TEST(test_power_external_standby_mode);

	return UnityEnd();
}

void setUp()
{
	reset_registers();
}

void tearDown()
{
	reset_registers();
}
