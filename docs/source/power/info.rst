.. _power-info:

How To Add To Project
=====================

If instructions in :ref:`getting-started` applied, this part can be skipped.

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/inc/`` directory to target project's include path.
3. Add ``atmega328p_hal_driver/src/atmega328p_hal_power.c`` to target project's build toolchain as a source file.
4. Include ``atmega328p_hal_power.h`` header to desired source file(s).

Sleep Modes
===========

ATmega328P supports 6 different sleep modes. This modes can be set via ``hal_power_set_sleep_mode()`` function. See ATmega328P data-sheet for individual sleep mode features.

ATmega328P can be waken up from a sleep with an interrupt.

Code example:

.. code-block:: c

	// Set idle sleep mode.
	hal_power_set_sleep_mode(idle);

Module Power Modes
==================

Every individual module can be turned off or on to reduce power usage. Use ``hal_power_set_module_power()`` function to set enable or disable modules.

Code example:

.. code-block:: c

	// Disable ADC.
	hal_power_set_module_power(adc_off);
