.. _system-info:

How To Add To Project
=====================

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/inc/`` directory to target project's include path.
3. Add ``atmega328p_hal_driver/src/atmega328p_hal_system.c`` to target project's build toolchain as a source file.
4. Include ``atmega328p_hal_system.h`` header to desired source file(s).

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
	if (reset_status & hal_watchdog_reset) {
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

.. list-table:: Timeout Modes
	:header-rows: 1

	* - Number of WDT Oscillator Cycles
	  - Typical Time-out at VCC = 5.0V
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

Enabling Watchdog
"""""""""""""""""

``hal_system_enable_watchdog()`` function can be used to enable watchdog. While calling this function, give timeout option and operating mode as parameters.

Example code:

.. code-block:: c

	// Enable watchdog with 2 s timeout and reset mode.
	hal_system_enable_watchdog(_256k_cycles, reset);

Resetting Watchdog Timer
""""""""""""""""""""""""

Watchdog timer can be reset with ``hal_system_reset_watchdog()`` function.

Example code:

.. code-block:: c

	// Call reset function to reset watchdog timer.
	hal_system_reset_watchdog();

Disabling Watchdog
""""""""""""""""""

Watchdog can be disabled with ``hal_system_disable_watchdog()`` function. After a power on reset, ATmega328P defaults to disabled watchdog.

.. code-block:: c

	// Call disable function to disable watchdog.
	hal_system_disable_watchdog();
