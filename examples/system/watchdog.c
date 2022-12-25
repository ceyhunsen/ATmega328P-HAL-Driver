#include "atmega328p_hal_system.h"

int main()
{
	// Create watchdog struct.
	hal_system_watchdog_t watchdog;

	// Enable watchdog timer with 2 second time out and reset mode.
	watchdog.cycles = hal_system_watchdog_256k_cycles;
	watchdog.mode = hal_system_watchdog_reset_mode;
	hal_system_set_watchdog(watchdog);

	// Disable watchdog timer.
	watchdog.mode = hal_system_watchdog_disabled;
	hal_system_set_watchdog(watchdog);

	return 0;
}
