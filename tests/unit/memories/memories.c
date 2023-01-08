/**
 * @file memories.c
 * @author Ceyhun Şen
 * @brief Unit tests for system module
 */

#include "eeprom.h"
#include "unity.h"
#include <definitions.h>

void setUp()
{
	reset_registers();
}

void tearDown()
{
	reset_registers();
}

int main()
{
	RUN_TEST(test_eeprom_modes);
	RUN_TEST(test_eeprom_interrupt);

	return UnityEnd();
}
