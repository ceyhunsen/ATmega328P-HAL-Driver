/**
 * @file watchdog.c
 * @author Ceyhun Şen
 * @brief Unit tests for watchdog timer.
 */

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

#include "atmega328p_hal_system.h"
#include "watchdog.h"
#include "unity.h"
#include <avr/io.h>

/**
 * @brief Unit test for cycle check when enabling watchdog timer.
 */
void test_wdt_enable_cycles()
{
	int j = 0;

	for (hal_system_watchdog_cycles i = 0; i <= hal_system_watchdog_1024k_cycles; i++, j++) {
		// Set cycle.
		hal_system_enable_watchdog(i, hal_system_watchdog_interrupt_mode);

		// Check if written correctly.
		TEST_ASSERT_EQUAL(WDTCSR & 0b1111, j);

		// Reset register.
		WDTCSR = 0;
	}
}
