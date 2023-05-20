# Getting Started

Welcome to the ATmega328P HAL driver documentation. This driver provides easy
to use interface for device peripherals.

ATmega328P hal driver is seperated in to independent modules for every
peripheral. In this way, unneeded modules can be omitted to save both memory and
flash space.

This driver depends on [avr-libc](https://www.nongnu.org/avr-libc/) and uses
[avr-gcc](https://gcc.gnu.org/wiki/avr-gcc) as the compiler.

## How To Add To Project

1. Copy `atmega328p_hal_driver` directory to target project's drivers directory.
2. Add `atmega328p_hal_driver/include/` directory to target project's include
path.
3. Add desired source file(s) in `atmega328p_hal_driver/src/` to target
project's build toolchain as source file(s).
4. Include `hal.h` header or a specific header to desired source
file(s).

## Example Usage

Example usage for every module is in `examples` directory.

## Naming Conventions

* Module names do not follow ATmega328P data-sheet conventions. Common names are
used.
* All of the namings are in `snake_case`, except for the constants: they are in
`SCREAMING_SNAKE_CASE`.
* All file names includes `hal_` prefix (e.g.: `hal_usart.c`).
* All function, struct, enum and enum member names includes it's module name's
prefix (e.g.: `usart_transmit()` or `struct usart_t`).

With these information, needed members of this driver can be found easily.

### More On Modules

A module can have 3 different files and they have different suffixes:

1. Core module with blocking functions. Have no suffixes. E.g.: `hal_usart.c`.
2. Interrupt module with non-blocking functions. Have `_irq` suffix. E.g.:
`hal_usart_irq.c`.
3. Extra module with non-standard functions. Have `_extra` suffix. E.g.:
`hal_usart_extra.c`.

## License

This project is licensed under MIT license.
