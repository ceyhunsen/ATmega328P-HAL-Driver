.. _io-info:

How To Add To Project
=====================

If instructions in :ref:`getting-started` applied, this part can be skipped.

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/inc/`` directory to target project's include path.
3. Add ``atmega328p_hal_driver/src/atmega328p_hal_io.c`` to target project's build toolchain as a source file.
4. Include ``atmega328p_hal_io.h`` header to desired source file(s).

Setting Pins As Output Or Input
===============================

Pins are configurable via ``hal_io_set_pin_mode()`` function. Pin port, pin and pin mode must be given as parameter to function.

.. doxygenfunction:: hal_io_set_pin_mode
	:project: ATmega328P HAL Driver

Code example:

.. code-block:: c

	// Set PB5 pin as output.
	hal_io_set_pin_mode(hal_io_port_b, 5, hal_io_output_mode);

Changing Pin State
==================

Pins can be drived high or low with ``hal_io_write_pin()`` function. Pin port, pin and state must be given as parameter to function.

.. doxygenfunction:: hal_io_write_pin
	:project: ATmega328P HAL Driver

Code example:

.. code-block:: c

	// Write high to PB5 pin.
	hal_io_write_pin(hal_io_port_b, 5, hal_io_high_state);

Toggling Pin State
==================

Pin state can be toggled with ``hal_io_toggle_pin()`` function. Pin port and pin must be given as parameter to function.

.. doxygenfunction:: hal_io_toggle_pin
	:project: ATmega328P HAL Driver

Code example:

.. code-block:: c

	// Toggle PB5 pin state.
	hal_io_toggle_pin(hal_io_port_b, 5);

Reading Pin State
=================

Pin state can be read with ``hal_io_read_pin()`` function. Pin port and pin must be given as parameter to function. 1 will be returned if pin state is high, 0 otherwise.

.. doxygenfunction:: hal_io_read_pin
	:project: ATmega328P HAL Driver

Code example:

.. code-block:: c

	// Read PB0 pin state.
	uint8_t pb0_state = hal_io_read_pin(hal_io_port_b, 0);
	if (pb0_state == 1) {
		printf("PB0 is in high state.\n");
	}
	else {
		printf("PB0 is in low state.\n");
	}
