# Development Guide

This driver developed using test driven development techniques. Tests can be
found in `tests` directory.

## Naming Conventions

* Module names do not follow ATmega328P data-sheet conventions. Common names are
used.
* All of the namings are in `snake_case`, except for the constants: they are in
`SCREAMING_SNAKE_CASE`.
* All file names includes `hal_` prefix (e.g.: `hal_usart.c`).
* All function, struct, enum and enum member names includes it's module name's
prefix (e.g.: `usart_transmit()` or `struct usart_t`).

With these information, any functionality of this driver can be found easily.

### More On Modules

A module can have 3 different files and they have different suffixes:

1. Core module with blocking functions. Have no suffixes. E.g.: `hal_usart.c`.
2. Interrupt module with non-blocking functions. Have `_irq` suffix. E.g.:
`hal_usart_irq.c`.
3. Extra module with non-standard functions like support for `printf()` on
USART. Have `_extra` suffix. E.g.: `hal_usart_extra.c`.

Core module must be compiled too if just any of the last modules are going to be
used.
