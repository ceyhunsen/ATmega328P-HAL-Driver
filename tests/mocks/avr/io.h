/**
 * @file io.h
 * @author Ceyhun Şen
 * @brief Mock up IO definitions.
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

#ifndef __IO_H
#define __IO_H

#include <stdint.h>

#define _BV(bit) (1 << (bit))

typedef uint8_t  byte_register_t;
typedef uint16_t word_register_t;
typedef uint32_t dword_register_t;

// System control and reset.
extern byte_register_t MCUSR;
extern byte_register_t WDTCSR;

enum __MCUSR {
	PORF = 0,
	EXTRF,
	BORF,
	WDRF
};

enum __WDTCSR {
	WDP0 = 0,
	WDP1,
	WDP2,
	WDE,
	WDCE,
	WDP3,
	WDIE,
	WDIF
};

#endif // __IO_H
