.. _twi-info:

How To Add To Project
=====================

If instructions in :ref:`getting-started` applied, this part can be skipped.

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/inc/`` directory to target project's include path.
3. Add ``atmega328p_hal_driver/src/atmega328p_hal_twi.c`` to target project's build toolchain as a source file.
4. Include ``atmega328p_hal_twi.h`` header to desired source file(s).

Core Functionalities
====================

Add ``atmega328p_hal_twi.c`` as a source file to use core funtions. Include ``atmega328p_hal_twi.h`` to use core functions.

Initialization
""""""""""""""

TWI must be initialized before using. Initialization takes only one step:

1. Call ``hal_twi_init()`` function with bit rate parameter (See: API Reference/hal_twi_bit_rate).

.. code-block:: c
	:caption: Example code

	// Initialize TWI with standart mode (100 kbit/s).
	hal_twi_init(hal_twi_standart_mode);

Write Memory In Blocking Mode
"""""""""""""""""""""""""""""

Data can be written to specified register in specified slave. To write to memory, use ``hal_twi_write_memory()`` function. While calling this function, register size can be selected.

.. code-block:: c
	:caption: Example code

	uint8_t buffer = 0x55;

	// Write data to SLAVE_REGISTER in SLAVE_ADDRESS slave.
	hal_twi_write_memory(SLAVE_ADDRESS, SLAVE_REGISTER, hal_twi_register_size_1_byte, &buffer, sizeof(buffer));

Read Memory In Blocking Mode
""""""""""""""""""""""""""""

Data can be read from specified register in specified slave. To read from memory, use ``hal_twi_read_memory()`` function. While calling this function, register size can be selected.

.. code-block:: c
	:caption: Example code

	uint8_t buffer;

	// Read data from SLAVE_REGISTER in SLAVE_ADDRESS slave.
	hal_twi_read_memory(SLAVE_ADDRESS, SLAVE_REGISTER, hal_twi_register_size_1_byte, &buffer, sizeof(buffer));

	printf("Read data: %u\n", buffer);
