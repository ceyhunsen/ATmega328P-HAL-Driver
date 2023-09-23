# Tests

This driver developed using test driven development techniques. Tests can be
found in `tests` directory.

There are 2 test types: Unit and integration. Unit tests runs on host machine
and just checks if memory accesses made by driver are correct. Integration tests
however, might be run on host machine or MCU itself.

This driver depends [Unity](https://github.com/ThrowTheSwitch/Unity) test
framework. This repository should be cloned to `tests/Unity` directory, if not
cloned while cloning this repository.

## Running Tests

### All At Once

To run all of the tests, in `tests/` directory, run:

```bash
make
```

Beware that some tests needs extra hardware! Check test directory for README
files if that's the case.

### One By One

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

## Creating New Tests

### Unit

Let's assume new test name is `new_test`.

1. Create `tests/unit/new_test` directory.
2. Copy `template_unit_test_makefile` to `tests/unit/new_test` directory and
rename it to `Makefile`.
3. Append new source files to newly created `Makefile`.

## Mock Interface

Unit tests and some of the integration tests are basically checks if right value
is written to the right register. To do this on host computer, a mock register
interface should be created. This interface will write this data to a buffer
memory, not real registers. With this, tests can be run on host computer without
the need of hardware.

Mock interface is in `tests/mocks` directory. This directory includes mock
interface and mock headers of the avr libc library.

Tests should use `tests/mocks` directory as include directory and compile
`tests/mocks/test_mock_up.c` file with the rest of the test.

Mock interface will convert raw memory access to buffer memory access. Code can
be written as it is written for hardware:

```c
// Declaration of a random data.
uint8_t data;
data = 87;

// Writing a random data to USART data register.
UDR0 = data;
```

Above code should be converted like this by the compiler for hardware:

```c
*(volatile uint8_t *)(0xC6) = data;
```

Mock interface should convert this to:

```c
__atmega328p_registers[0xC6] = data;
```

With mock interface conversion, it's value can be checked in host computer:

```c
TEST_ASSERT_EQUAL(data, UDR0);
// Line above is equal to:
TEST_ASSERT_EQUAL(data, __atmega328p_registers[0xC6]);
```
