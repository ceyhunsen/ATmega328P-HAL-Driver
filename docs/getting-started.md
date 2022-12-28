# Getting Started

ATmega328P hal driver is seperated in to independent modules for every peripheral. In this way, unneeded modules can be omitted to save both memory and flash space.

This driver depends on [avr-libc](https://www.nongnu.org/avr-libc/) and uses [avr-gcc](https://gcc.gnu.org/wiki/avr-gcc) as the compiler.

## How To Add To Project

1. Copy `atmega328p_hal_driver` directory to target project's driver directory.
2. Add `atmega328p_hal_driver/include/` directory to target project's include path.
3. Add desired source file(s) in `atmega328p_hal_driver/src/` directory to target project's build toolchain as source file(s).
4. Include `atmega328p_hal.h` header or a specific header to desired source file(s).

## Example Usage

Example usage for every module is in `examples` directory.

## Naming Conventions

* All module names taken from ATmega328P data-sheet.
* All of the namings are in `snake_case`, except for the constants: they are in `SCREAMING_SNAKE_CASE`.
* All file names includes `atmega328p_hal_` prefix. E.g.: `atmega328p_hal_usart.c`.
* All function, struct, enum and enum member names includes `hal` prefix. E.g.: `hal_usart_transmit()` or `hal_usart_t`.

With that information, needed members of this driver can be found easily.

## Extra Modules

Some modules includes support for extra functionalities. For example: USART module have transmit and receive in blocking mode as core functions, transmit and receive in non-blocking mode as extra functions. If any module has an extra module, it's source file must be compiled too (no new header is needed, only core header file is enough). Extra modules have suffix of `extra` in their names.
