.. _getting-started:

Getting Started
===============

ATmega328P HAL driver supports various hardware peripherals. Each module can be separately used.

Naming Conventions
""""""""""""""""""

* All the namings in snake case except for the constants.
* All file names includes ``atmega328p_hal`` prefix. E.g.: ``atmega328p_hal_usart.c``.
* All function, struct and enum names includes ``hal`` prefix. E.g.: ``hal_usart_transmit()`` or ``hal_usart_t``.

Extra Modules
"""""""""""""

Some modules includes support for extra functionalities. For example: USART have transmit and receive in blocking mode as core functions. And in extra module of USART: Transmit and receive in non-blocking mode, stdio support is present. If any module has an extras module, it's source file must be compiled too (no new header is needed, only core header file is enough).

How To Add To Project
"""""""""""""""""""""

1. Copy ``atmega328p_hal_driver`` directory to target project's driver directory.
2. Add ``atmega328p_hal_driver/inc/`` directory to target project's include path.
3. Add desired source file(s) in ``atmega328p_hal_driver/src/`` directory to target project's build toolchain as source file(s).
4. Include ``atmega328p_hal.h`` header or a specific header to desired source file(s).
