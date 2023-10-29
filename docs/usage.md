# Usage

## Using ATmega328P HAL Driver In Other Projects

ATmega328P HAL driver is seperated in to independent modules for every
peripheral. Thus, unneeded modules can be omitted while compiling to save both
memory and flash space.

### With CMake

### Manually

1. Copy `atmega328p_hal_driver` directory to target project's drivers directory.
2. Add `atmega328p_hal_driver/include/` directory to target project's include
path.
3. Add desired source file(s) in `atmega328p_hal_driver/src/` to target
project's build toolchain as source file(s).
4. Include `hal.h` header or a specific header to desired source file(s).

## Example Programs That Use ATmega328P HAL Driver

Example usage for every module is in `examples` directory.

## Naming Conventions

* Module names follows ATmega328P data-sheet conventions. Altough, longer names
might be shortened.
* All of the namings are in `snake_case`, except for the constants: they are in
`SCREAMING_SNAKE_CASE`.
* All file names includes `hal_` prefix (e.g.: `hal_usart.c`).
* All functions, structs, enums and enum members includes it's module name
prefix (e.g.: `usart_transmit()` or `struct usart_t`).

## Modules

A module can have 3 different files and they have different suffixes:

1. Core module with blocking functions have no suffixes. E.g.: `hal_usart.c`.
2. Interrupt module with non-blocking functions have `_irq` suffix. E.g.:
`hal_usart_irq.c`.
3. Extra module with non-standard functions (like support for `printf()` over
USART) have `_extra` suffix. E.g.: `hal_usart_extra.c`.
