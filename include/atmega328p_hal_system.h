/**
 * @file atmega328p_hal_system.h
 * @author Ceyhun Şen
 * @brief System control and reset module.
 * 
 * This module includes support for:
 * * Reset status
 * * Watchdog timer
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
 * @brief Watchdog oscillator cycles before a trigger.
 * */
typedef enum hal_system_watchdog_cycles {
	hal_system_watchdog_2k_cycles    = 0, ///< 16 ms at 5.0 V.
	hal_system_watchdog_4k_cycles    = 1, ///< 32 ms at 5.0 V.
	hal_system_watchdog_8k_cycles    = 2, ///< 64 ms at 5.0 V.
	hal_system_watchdog_16k_cycles   = 3, ///< 0.125 s at 5.0 V.
	hal_system_watchdog_32k_cycles   = 4, ///< 0.25 s at 5.0 V.
	hal_system_watchdog_64k_cycles   = 5, ///< 0.5 s at 5.0 V.
	hal_system_watchdog_128k_cycles  = 6, ///< 1 s at 5.0 V.
	hal_system_watchdog_256k_cycles  = 7, ///< 2 s at 5.0 V.
	hal_system_watchdog_512k_cycles  = 8, ///< 4 s at 5.0 V.
	hal_system_watchdog_1024k_cycles = 9  ///< 8 s at 5.0 V.
} hal_system_watchdog_cycles;

/**
 * @enum hal_system_watchdog_modes
 * @brief Trigger modes after watchdog timer expires.
 * */
typedef enum hal_system_watchdog_modes {
	hal_system_watchdog_interrupt_mode = 0,       ///< Trigger interrupt after watchdog timer expires.
	hal_system_watchdog_reset_mode,               ///< Reset MCU after watchdog timer expires.
	hal_system_watchdog_interrupt_and_reset_mode  ///< Trigger interrupt and reset MCU after watchdog timer expires.
} hal_system_watchdog_modes;

uint8_t hal_system_get_reset_status();
void hal_system_enable_watchdog(hal_system_watchdog_cycles cycles, hal_system_watchdog_modes mode);
void hal_system_disable_watchdog();
void hal_system_reset_watchdog();

#endif // __ATMEGA328P_HAL_SYSTEM_H
