.. _system-info:

Getting System Reset Source
===========================

System reset might be happened several reasons:

* Power on reset
* External reset
* Watchdog reset
* Brownout reset

To get reset source, use ``hal_system_get_reset_status()`` function and store the returned value.

.. warning::

	After ``hal_system_get_reset_status()`` function called, reset status register will be cleaned. So, store the returned value.

After the function call, use returned value to get reset status.

Example code:

.. code-block:: c

	// Get reset status.
	uint8_t reset_status = hal_system_get_reset_status();

	// Use defined constants in system header to get system reset source.
	// Check API reference for other reset sources.
	if (reset_status & HAL_SYSTEM_WATCHDOG_RESET) {
		printf("Reset caused by a watchdog reset!\n");
	}

Configuring Watchdog
====================

Operating Modes
"""""""""""""""

Watchdog timer has 3 operating modes:

* Interrupt
* System reset
* Interrupt and system reset

.. doxygenenum:: hal_system_watchdog_modes
	:project: ATmega328P HAL Driver

.. warning::

	If interrupt mode is selected, remember to add ISR for ``WDT_vect`` vector. See https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html for more information.

Timeout Options
"""""""""""""""

Watchdog timer features 10 different timeout options:

.. list-table:: Typical Time-out For Each Cycle
	:header-rows: 1

	* - Number of WDT Oscillator Cycles
	  - Typical Time-out At VCC = 5.0V
	* - 2K (2048) cycles
	  - 16ms
	* - 4K (4096) cycles
	  - 32ms
	* - 8K (8192) cycles
	  - 64ms
	* - 16K (16384) cycles
	  - 0.125s
	* - 32K (32768) cycles
	  - 0.25s
	* - 64K (65536) cycles
	  - 0.5s
	* - 128K (131072) cycles
	  - 1.0s
	* - 256K (262144) cycles
	  - 2.0s
	* - 512K (524288) cycles
	  - 4.0s
	* - 1024K (1048576) cycles
	  - 8.0s

.. doxygenenum:: hal_system_watchdog_cycles
	:project: ATmega328P HAL Driver

Setting Watchdog Timer
""""""""""""""""""""""

Watchdog timer can be set enabled or disabled with ``hal_system_set_watchdog()`` function. While calling this function, give timeout option and operating mode as parameters.

Example code:

.. include:: ../../../examples/system/watchdog.c

Resetting Watchdog Timer
""""""""""""""""""""""""

Watchdog timer can be reset with ``hal_system_reset_watchdog()`` function.

Example code:

.. code-block:: c

	// Call reset function to reset watchdog timer.
	hal_system_reset_watchdog();
