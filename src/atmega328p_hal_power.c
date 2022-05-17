/**
 * @file atmega328p_hal_power.c
 * @author Ceyhun Şen
 * @brief Power management and sleep modes HAL functions for ATmega328P HAL driver.
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

#include "atmega328p_hal_power.h"
#include "atmega328p_hal_internals.h"
#include <avr/io.h>
#include <avr/sleep.h>

/**
 * @brief Set sleep mode for ATmega328P.
 * @param mode Sleep mode.
 * @see hal_power_sleep_modes
 * */
void hal_power_set_sleep_mode(hal_power_sleep_modes mode)
{
	// Set sleep mode.
	switch (mode) {
		case hal_power_idle_mode:
			_CLEAR_BIT(SMCR, SM0);
			_CLEAR_BIT(SMCR, SM1);
			_CLEAR_BIT(SMCR, SM2);
			break;
		case hal_power_adc_noise_reduction_mode:
			_CLEAR_BIT(SMCR, SM0);
			_CLEAR_BIT(SMCR, SM1);
			_SET_BIT(SMCR, SM2);
			break;
		case hal_power_power_down_mode:
			_CLEAR_BIT(SMCR, SM0);
			_SET_BIT(SMCR, SM1);
			_CLEAR_BIT(SMCR, SM2);
			break;
		case hal_power_power_save_mode:
			_CLEAR_BIT(SMCR, SM0);
			_SET_BIT(SMCR, SM1);
			_SET_BIT(SMCR, SM2);
			break;
		case hal_power_standby_mode:
			_SET_BIT(SMCR, SM0);
			_SET_BIT(SMCR, SM1);
			_CLEAR_BIT(SMCR, SM2);
			break;
		case hal_power_external_standby_mode:
			_SET_BIT(SMCR, SM0);
			_SET_BIT(SMCR, SM1);
			_SET_BIT(SMCR, SM2);
			break;
	}

	// Set sleep enable bit and call sleep instruction.
	_SET_BIT(SMCR, SE);
	sleep_cpu();

	// Clear sleep flag after sleep.
	_CLEAR_BIT(SMCR, SE);
}

/**
 * @brief Set specified modules power on or off.
 * @param module_mod Module and it's power state.
 * @see hal_power_module_power_modes
 * */
void hal_power_set_module_power(hal_power_module_power_modes module_mod)
{
	switch (module_mod) {
		case hal_power_twi_off:
			_SET_BIT(PRR, PRTWI);
			break;
		case hal_power_twi_on:
			_CLEAR_BIT(PRR, PRTWI);
			break;
		case hal_power_timer_0_off:
			_SET_BIT(PRR, PRTIM0);
			break;
		case hal_power_timer_0_on:
			_CLEAR_BIT(PRR, PRTIM0);
			break;
		case hal_power_timer_1_off:
			_SET_BIT(PRR, PRTIM1);
			break;
		case hal_power_timer_1_on:
			_CLEAR_BIT(PRR, PRTIM1);
			break;
		case hal_power_timer_2_off:
			_SET_BIT(PRR, PRTIM2);
			break;
		case hal_power_timer_2_on:
			_CLEAR_BIT(PRR, PRTIM2);
			break;
		case hal_power_spi_off:
			_SET_BIT(PRR, PRSPI);
			break;
		case hal_power_spi_on:
			_CLEAR_BIT(PRR, PRSPI);
			break;
		case hal_power_usart0_off:
			_SET_BIT(PRR, PRUSART0);
			break;
		case hal_power_usart0_on:
			_CLEAR_BIT(PRR, PRUSART0);
			break;
		case hal_power_adc_off:
			_SET_BIT(PRR, PRADC);
			break;
		case hal_power_adc_on:
			_CLEAR_BIT(PRR, PRADC);
			break;
		default:
			PRR = 0;
			break;
	}
}
