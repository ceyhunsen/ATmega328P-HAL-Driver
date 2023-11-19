# System Control And Reset

## Capabilities

* Configure watchdog:
	* Set mode.
	* Set cycles.
* Reset watchdog.
* Get MCU reset status.

## Configure Watchdog

Watchdog can be configured using `system_set_watchdog()` function. This function
will accept watchdog mode and cycle count as arguments in a struct, called
`struct system_watchdog_t`.

## Reset Watchdog

## Get MCU Reset Status

ATmega328P can enter reset state with different causes. This causes are listed
in `enum system_reset_status`. Also, cause can be retrieved using
`uint8_t system_get_reset_status()` function. These 2 can be combined to examine
reset cause.
