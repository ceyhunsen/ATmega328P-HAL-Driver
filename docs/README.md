# Getting Started

Welcome to the ATmega328P hardware abstraction layer driver documentation. This
driver provides easy to use interface for device peripherals while staying fast
and small as possible.

This driver depends on [avr-libc](https://www.nongnu.org/avr-libc/) and uses
[avr-gcc](https://gcc.gnu.org/wiki/avr-gcc) as the compiler.

This work is **not affiliated** with AVR in any way.

## Using It In Your Project

ATmega328P hal driver is seperated in to independent modules for every
peripheral. With this, unneeded modules can be omitted to save both memory and
flash space.

To add this driver to your project:

1. Copy `atmega328p_hal_driver` directory to target project's drivers directory.
2. Add `atmega328p_hal_driver/include/` directory to target project's include
path.
3. Add desired source file(s) in `atmega328p_hal_driver/src/` to target
project's build toolchain as source file(s).
4. Include `hal.h` header or a specific header to desired source
file(s).

## Example Usages

Example usage for every module is in `examples` directory.

## License

This project is licensed under [MIT license](../../../LICENSE).
