# Development Guide

## Naming Conventions

* Module names do not follow ATmega328P data-sheet conventions. Common names are
used.
* All of the namings are in `snake_case`, except for the constants: they are in
`SCREAMING_SNAKE_CASE`.
* All file names includes `hal_` prefix (e.g.: `hal_usart.c`).
* All function, struct, enum and enum member names includes it's module name's
prefix (e.g.: `usart_transmit()` or `struct usart_t`).

With these information, any functionality of this driver can be found easily.

## Modules

A module can have 3 different files and they have different suffixes:

1. Core module with blocking functions. Have no suffixes. E.g.: `hal_usart.c`.
2. Interrupt module with non-blocking functions. Have `_irq` suffix. E.g.:
`hal_usart_irq.c`.
3. Extra module with non-standard functions like support for `printf()` on
USART. Have `_extra` suffix. E.g.: `hal_usart_extra.c`.

Core module must be compiled too if just any of the last modules are going to be
used.

## Tests

This driver developed using test driven development techniques. Tests can be
found in `tests` directory.

There are 2 test types: Unit and integration. Unit tests runs on host machine
and just checks if memory accesses made by driver are correct. Integration tests
however, might be run on host machine or MCU itself.

This driver depends [Unity](https://github.com/ThrowTheSwitch/Unity) test
framework. This repository should be cloned to `tests/Unity` directory, if not
cloned while cloning this repository.

### Running Tests

#### All At Once

To run all of the tests, in `tests/` directory, run:

```bash
make
```

Beware that some tests needs extra hardware! Check test directory for README
files if that's the case.

#### One By One

All modules can be tested seperately.To run only one test, call `make` with it's
path (including `/.` suffix). For example, to run `gpio` module's unit
tests:

```bash
make unit/gpio/.
```

Unit and integration tests can be runned seperately too:

```bash
make unit         # Runs unit tests.
make integration  # Runs integration tests.
```

### Creating New Tests

#### Unit

Let's assume new test name is `new_test`.

1. Create `tests/unit/new_test` directory.
2. Copy [`template_unit_test_makefile`](template_unit_test_makefile) to
`tests/unit/new_test` directory and rename it to `Makefile`.
3. Append new source files to newly created `Makefile`.
