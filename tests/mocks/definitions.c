/**
 * @file definitions.c
 * @author Ceyhun Şen
 * @brief Mock up register definitions.
 */

#include <definitions.h>
#include <avr/io.h>

// Memories.
word_register_t EEAR = 0;
word_register_t EEDR = 0;
word_register_t EECR = 0;
word_register_t GPIOR2 = 0;
word_register_t GPIOR1 = 0;
word_register_t GPIOR0 = 0;

// System control and reset.
byte_register_t MCUSR = 0;
byte_register_t WDTCSR = 0;

/**
 * @brief Reset every register to initial value.
 */
void reset_registers()
{
	EEAR = 0;
	EEDR = 0;
	EECR = 0;
	GPIOR2 = 0;
	GPIOR1 = 0;
	GPIOR0 = 0;

	MCUSR = 0;
	WDTCSR = 0;
}
