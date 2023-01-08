/**
 * @file io.h
 * @author Ceyhun Şen
 * @brief Mock up IO definitions.
 */

/*
 * MIT License
 * 
 * Copyright (c) 2023 Ceyhun Şen
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

// Memories.
extern word_register_t EEAR;
extern word_register_t EEDR;
extern word_register_t EECR;
extern word_register_t GPIOR2;
extern word_register_t GPIOR1;
extern word_register_t GPIOR0;

// System control and reset.
extern byte_register_t MCUSR;
extern byte_register_t WDTCSR;

enum __EEAR {
	EEAR0 = 0,
	EEAR1,
	EEAR2,
	EEAR3,
	EEAR4,
	EEAR5,
	EEAR6,
	EEAR7,
	EEAR8,
};

enum __EECR {
	EERE = 0,
	EEPE,
	EEMPE,
	EERIE,
	EEPM0,
	EEPM1,
};

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

#define _BV(bit) (1 << (bit))
#define bit_is_set(sfr, bit) ((sfr) & _BV(bit))
#define bit_is_clear(sfr, bit) (!((sfr) & _BV(bit)))
#define loop_until_bit_is_set(sfr, bit) do { } while (bit_is_clear(sfr, bit))
#define loop_until_bit_is_clear(sfr, bit) do { } while (bit_is_set(sfr, bit))

#endif // __IO_H
