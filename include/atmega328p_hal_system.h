/**
 * @file atmega328p_hal_system.h
 * @author Ceyhun Şen
 * @brief System control and reset header file for ATmega328P HAL driver.
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

#ifndef __ATMEGA328P_HAL_SYSTEM_H
#define __ATMEGA328P_HAL_SYSTEM_H

#include <stdint.h>

#define HAL_SYSTEM_WATCHDOG_RESET 3
#define HAL_SYSTEM_BROWNOUT_RESET 2
#define HAL_SYSTEM_EXTERNAL_RESET 1
#define HAL_SYSTEM_POWER_ON_RESET 0

/**
 * @enum hal_system_watchdog_cycles
 * @brief Watchdog wait cycles options before a trigger.
 * */
typedef enum hal_system_watchdog_cycles {
	hal_system_watchdog_2k_cycles = 0,
	hal_system_watchdog_4k_cycles = 1,
	hal_system_watchdog_8k_cycles = 2,
	hal_system_watchdog_16k_cycles = 3,
	hal_system_watchdog_32k_cycles = 4,
	hal_system_watchdog_64k_cycles = 5,
	hal_system_watchdog_128k_cycles = 6,
	hal_system_watchdog_256k_cycles = 7,
	hal_system_watchdog_512k_cycles = 8,
	hal_system_watchdog_1024k_cycles = 9
} hal_system_watchdog_cycles;

/**
 * @enum hal_system_watchdog_modes
 * @brief Wathcdog trigger modes.
 * */
typedef enum hal_system_watchdog_modes {
	hal_system_watchdog_interrupt_mode = 0,
	hal_system_watchdog_reset_mode,
	hal_system_watchdog_interrupt_and_reset_mode
} hal_system_watchdog_modes;

uint8_t hal_system_get_reset_status();
void hal_system_enable_watchdog(hal_system_watchdog_cycles cycles, hal_system_watchdog_modes mode);
void hal_system_disable_watchdog();
void hal_system_reset_watchdog();

#endif // __ATMEGA328P_HAL_SYSTEM_H
