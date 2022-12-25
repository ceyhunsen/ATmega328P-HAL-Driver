/**
 * @file hal_internals.h
 * @author Ceyhun Şen
 * @brief Internal header file for ATmega328P HAL driver.
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

#ifndef __ATMEGA328P_HAL_INTERNALS_H
#define __ATMEGA328P_HAL_INTERNALS_H

#include <avr/io.h>

/**
 * @addtogroup bit_manipulation
 * @brief Bit manipulation defines.
 * @{
 * */

/**
 * @brief Clear specified bit of var.
 * */
#define _CLEAR_BIT(var, bit) (var &= ~(1 << bit))

/**
 * @brief Set specified bit of var.
 * */
#define _SET_BIT(var, bit) (var |= _BV(bit))

/**
 * @brief Get pin value of a bit.
 * */
#define _PIN_TO_BIT(pin) (1 << (pin))

/**
 * @}
 * */

#endif // __ATMEGA328P_HAL_INTERNALS_H
