/**
 * @file definitions.c
 * @author Ceyhun Şen
 * @brief Mock up register definitions.
 */

#include <definitions.h>
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
