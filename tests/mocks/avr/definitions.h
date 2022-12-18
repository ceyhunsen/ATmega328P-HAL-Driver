/**
 * @file definitions.h
 * @author Ceyhun Şen
 * @brief Mock up register definitions. This file must included just once.
 */

#ifndef __DEFINITIONS_H
#define __DEFINITIONS_H

#include <avr/io.h>

// System control and reset.
byte_register_t MCUSR = 0;
byte_register_t WDTCSR = 0;

/**
 * @brief Reset every register to initial value.
 */
void reset_registers()
{
	MCUSR = 0;
	WDTCSR = 0;
}

#endif // __DEFINITIONS_H
