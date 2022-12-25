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
 * @brief Set watchdog timer with given settings.
 * @param mode Watchdog timer trigger mode.
 * @param cycles Oscillator cycles before a watchdog trigger. Doesn't matter in disabled mode.
 * @see hal_system_watchdog_t
 * */
void hal_system_set_watchdog(hal_system_watchdog_t watchdog)
{
	// Because of register value must be written to register in one operation,
	// register value must be calculated beforehand.
	uint8_t watchdog_register_value = 0;

	// Save operating mode.
	switch (watchdog.mode) {
		default:
		case hal_system_watchdog_disabled:
			watchdog_register_value = 0;
			break;
		case hal_system_watchdog_interrupt_mode:
			_SET_BIT(watchdog_register_value, WDIE);
			break;
		case hal_system_watchdog_reset_mode:
			_SET_BIT(watchdog_register_value, WDE);
			break;
		case hal_system_watchdog_interrupt_and_reset_mode:
			_SET_BIT(watchdog_register_value, WDIE);
			_SET_BIT(watchdog_register_value, WDE);
			break;
	}

	// If watchdog timer is not disabled, save cycles.
	if (watchdog.mode != hal_system_watchdog_disabled) {
		watchdog_register_value |= (watchdog.cycles << WDP0);
	}

	// Disable interrupts and reset watchdog.
	cli();
	hal_system_reset_watchdog();

	// Clear watchdog status flag.
	_CLEAR_BIT(MCUSR, WDRF);

	// Set change enable.
	WDTCSR |= (1 << WDCE) | (1 << WDE);

	// Set register value.
	WDTCSR = watchdog_register_value;

	// Finally, enable interrupts.
	sei(); 
}

/**
 * @brief Reset watchdog timer counter.
 * */
inline void hal_system_reset_watchdog()
{
	wdt_reset();
}
