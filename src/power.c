/**
 * @file power.c
 * @author Ceyhun Şen
 * @brief Power management HAL functions for ATmega328P HAL driver.
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

#include "power.h"
#include "atmega328p_hal_internals.h"
#include <avr/io.h>

void power_set_mode(power_modes mode)
{
	
}

/**
 * @brief Set specified modules power on or off.
 * @param module_mod Module and it's power state.
 * @see power_module_power_modes
 * */
void power_set_module_power(power_module_power_modes module_mod)
{
	switch (module_mod) {
		case twi_off:
			PRR |= _BV(PRTWI);
			break;
		case twi_on:
			_CLEAR_BIT(PRR, PRTWI);
			break;
		case timer_0_off:
			PRR |= _BV(PRTIM0);
			break;
		case timer_0_on:
			_CLEAR_BIT(PRR, PRTIM0);
			break;
		case timer_1_off:
			PRR |= _BV(PRTIM1);
			break;
		case timer_1_on:
			_CLEAR_BIT(PRR, PRTIM1);
			break;
		case timer_2_off:
			PRR |= _BV(PRTIM2);
			break;
		case timer_2_on:
			_CLEAR_BIT(PRR, PRTIM2);
			break;
		case spi_off:
			PRR |= _BV(PRSPI);
			break;
		case spi_on:
			_CLEAR_BIT(PRR, PRSPI);
			break;
		case usart0_off:
			PRR |= _BV(PRUSART0);
			break;
		case usart0_on:
			_CLEAR_BIT(PRR, PRUSART0);
			break;
		case adc_off:
			PRR |= _BV(PRADC);
			break;
		case adc_on:
			_CLEAR_BIT(PRR, PRADC);
			break;
		default:
			PRR = 0;
			break;
	}
}
