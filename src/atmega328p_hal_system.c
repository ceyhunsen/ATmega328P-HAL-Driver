/**
 * @file atmega328p_hal_system.c
 * @author Ceyhun Şen
 * @brief System control and reset HAL functions for ATmega328P HAL driver.
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

#include "atmega328p_hal_system.h"
#include "atmega328p_hal_internals.h"
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

/**
 * @brief Get reset status register value and reset status register.
 * @returns Reset status register value.
 * */
uint8_t hal_system_get_reset_status()
{
	uint8_t tmp = MCUSR;
	MCUSR = 0;
	return tmp;
}

/**
 * @brief Enable watchdog with given settings.
 * @param cycles Oscillator cycles before a watchdog trigger.
 * @param mode Watchdog trigger mode.
 * @see hal_system_watchdog_cycles
 * */
void hal_system_enable_watchdog(hal_system_watchdog_cycles cycles, hal_system_watchdog_modes mode)
{
	// Get watchdog register value with cycle and mode information.
	uint8_t watchdog_register_value = (cycles << WDP0);
	switch (mode) {
		case interrupt:
			_CLEAR_BIT(MCUSR, WDRF);
			watchdog_register_value |= (1 << WDIE);
			break;
		case reset:
			watchdog_register_value |= (1 << WDE);
			break;
		case interrupt_and_reset:
			watchdog_register_value |= (1 << WDIE);
			watchdog_register_value |= (1 << WDE);
			break;
		default:
			_CLEAR_BIT(MCUSR, WDRF);
			watchdog_register_value |= (1 << WDIE);
			break;
	}

	// Disable interrupts and reset watchdog.
	cli();
	hal_system_reset_watchdog();

	// Set change enable.
	WDTCSR |= (1 << WDCE) | (1 << WDE);

	// Set register value.
	WDTCSR = watchdog_register_value;

	// Finally, enable interrupts.
	sei(); 
}

/**
 * @brief Disable watchdog timer.
 * */
void hal_system_disable_watchdog()
{
	// Disable interrupts and reset watchdog.
	cli();
	hal_system_reset_watchdog();

	// Clear watchdog status flag.
	_CLEAR_BIT(MCUSR, WDRF);

	// Set change enable.
	WDTCSR |= (1 << WDCE) | (1 << WDE);

	// Turn off watchdog timer.
	WDTCSR = 0;

	// Finally, enable interrupts.
	sei(); 
}

/**
 * @brief Reset watchdog timer.
 * */
void hal_system_reset_watchdog()
{
	wdt_reset();
}
