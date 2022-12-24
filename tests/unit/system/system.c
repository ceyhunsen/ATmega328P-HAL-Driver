/**
 * @file system.c
 * @author Ceyhun Şen
 * @brief Unit tests for system module
 */

#include "watchdog.h"
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
	RUN_TEST(test_wdt_enable_cycles);

	return UnityEnd();
}
