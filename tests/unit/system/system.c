/**
 * @file watchdog.c
 * @author Ceyhun Şen
 * @brief System tests.
 */

#include "watchdog.h"
#include "unity.h"
#include <avr/definitions.h>

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
	RUN_TEST(test_wdt_enable);

	return UnityEnd();
}
