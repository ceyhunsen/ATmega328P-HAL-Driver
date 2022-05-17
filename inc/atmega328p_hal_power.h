/**
 * @file atmega328p_hal_power.h
 * @author Ceyhun Şen
 * @brief Power management and sleeo modes header file for ATmega328P HAL driver.
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

#ifndef __ATMEGA328P_HAL_POWER_H
#define __ATMEGA328P_HAL_POWER_H

/**
 * @enum hal_power_sleep_modes
 * @brief Sleep modes for ATmega328P.
 * */
typedef enum hal_power_sleep_modes {
	hal_power_idle_mode,
	hal_power_adc_noise_reduction_mode,
	hal_power_power_down_mode,
	hal_power_power_save_mode,
	hal_power_standby_mode,
	hal_power_external_standby_mode
} hal_power_sleep_modes;

/**
 * @enum hal_power_module_power_modes
 * @brief Module power modes.
 * */
typedef enum hal_power_module_power_modes {
	hal_power_twi_off,
	hal_power_twi_on,
	hal_power_timer_0_off,
	hal_power_timer_0_on,
	hal_power_timer_1_off,
	hal_power_timer_1_on,
	hal_power_timer_2_off,
	hal_power_timer_2_on,
	hal_power_spi_off,
	hal_power_spi_on,
	hal_power_usart0_off,
	hal_power_usart0_on,
	hal_power_adc_off,
	hal_power_adc_on
} hal_power_module_power_modes;

void hal_power_set_sleep_mode(hal_power_sleep_modes mode);
void hal_power_set_module_power(hal_power_module_power_modes module_mod);

#endif // __ATMEGA328P_HAL_POWER_H
