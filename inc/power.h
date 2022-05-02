/**
 * @file power.h
 * @author Ceyhun Şen
 * @brief Power management header file for ATmega328P HAL driver.
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

#ifndef __POWER_H
#define __POWER_H

/**
 * @enum power_modes
 * @brief Power modes.
 * */
typedef enum power_modes {
	idle,
	adc_noise_reduction,
	power_down,
	power_save,
	standby,
	external_standby
} power_modes;

/**
 * @enum power_module_power_modes
 * @brief Module power modes.
 * */
typedef enum power_module_power_modes {
	twi_off,
	twi_on,
	timer_0_off,
	timer_0_on,
	timer_1_off,
	timer_1_on,
	timer_2_off,
	timer_2_on,
	spi_off,
	spi_on,
	usart0_off,
	usart0_on,
	adc_off,
	adc_on
} power_module_power_modes;

void power_set_mode(power_modes mode);
void power_set_module_power(power_module_power_modes module_mod);

#endif // __POWER_H
