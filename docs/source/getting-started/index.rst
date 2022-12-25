.. _getting-started:

Getting Started
===============

ATmega328P HAL driver supports various hardware peripherals. Each module can be separately used.

Naming Conventions
""""""""""""""""""

* All of the namings are in ``snake_case``, except for the constants: they are in ``SCREAMING_SNAKE_CASE``.
* All file names includes ``atmega328p_hal`` prefix. E.g.: ``atmega328p_hal_usart.c``.
* All function, struct, enum and enum member names includes ``hal`` prefix. E.g.: ``hal_usart_transmit()`` or ``hal_usart_t``.

With that information, needed members of this driver can be found easily.

Extra Modules
"""""""""""""

Some modules includes support for extra functionalities. For example: USART module have transmit and receive in blocking mode as core functions, transmit and receive in non-blocking mode as extra functions. If any module has an extra module, it's source file must be compiled too (no new header is needed, only core header file is enough). Extra modules have suffix of ``extra`` in their names.

How To Add To Project
"""""""""""""""""""""

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/include/`` directory to target project's include path.
3. Add desired source file(s) in ``atmega328p_hal_driver/src/`` directory to target project's build toolchain as source file(s).
4. Include ``atmega328p_hal.h`` header or a specific header to desired source file(s).
