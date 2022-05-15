.. _usart-info:

How To Add To Project
=====================

If instructions in :ref:`getting-started` applied, this part can be skipped.

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/inc/`` directory to target project's include path.
3. Add ``atmega328p_hal_driver/src/atmega328p_hal_usart.c`` to target project's build toolchain as a source file.
4. For extras, add ``atmega328p_hal_driver/src/atmega328p_hal_usart_extra.c`` to target project's build toolchain as a source file.
5. Include ``atmega328p_hal_usart.h`` header to desired source file(s).

Initialization
==============

USART must be initialized before using. Initialization takes 2 steps:

1. ``hal_usart_t`` struct instance created with desired options.
2. ``hal_usart_init()`` function is called with ``hal_usart_t`` struct as a parameter. 

.. code-block:: c
	:caption: Example code

	// Create USART struct.
	hal_usart_t usart = {
		.baud_rate = 9600,
		.stop_bits = 1,
		.parity = disabled,
		.data_bits = 8,
		.operating_mode = asynchronous_normal_mode,
		.mode = transmit_and_receive,
	};

	// Initialize USART.
	hal_usart_init(&usart);

See :ref:`usart-api-reference` for ``hal_usart_t`` struct to available options.

Transmitting Data
=================

Data can be transmitted in blocking mode over USART via ``hal_usart_transmit()`` function.

.. code-block:: c
	:caption: Example code

	// Create a data buffer.
	uint8_t *data = (uint8_t *)"Hello, world!\n";

	// Transmit buffered data.
	hal_usart_transmit(&usart, data, strlen((char *)data));

Receiving Data
==============

Data can be received in blocking mode over USART via ``hal_usart_receive()`` function. This function will wait till' at least ``len`` (function parameter) byte of data is received over USART.

.. code-block:: c
	:caption: Example code

	char data[10];

	// Receive data.
	hal_usart_receive(&usart, (uint8_t *)data, sizeof(data));

	printf("Received data: %s\n", (char *)data);

Extra Functionalities
=====================

To use the extra functionalities, ``atmega328p_hal_usart_extra.c`` must be added to the source files. Extra functionalities are:

* Standart I/O support

Standart I/O Support
""""""""""""""""""""

Standart I/O is supported over USART. To initialize standart I/O, ``hal_usart_stdio_init()`` function must be called after initilization of USART.

.. warning::

	USART 9 data bit mode is not supported.

.. code-block:: c
	:caption: Example code

	// Create USART struct.
	hal_usart_t usart = {
		.baud_rate = 9600,
		.stop_bits = 1,
		.parity = disabled,
		.data_bits = 8,
		.operating_mode = asynchronous_normal_mode,
		.mode = transmit_and_receive,
	};

	// Initialize USART.
	hal_usart_init(&usart);

	// Initialize standart I/O
	hal_usart_stdio_init();

	// Use standart I/O.
	int incoming_data = 0;
	scanf("%d", &incoming_data);
	printf("Received data: %d\n", incoming_data);
