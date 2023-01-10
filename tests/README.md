# Tests

ATmega328P HAL driver utilizes test driven development. This includes unit and integration tests. Unit tests run on host computer and uses mock hardware definitions. Integration test on the other hand, runs on real hardware (might also uses extra hardwares like a sensor).

Both tests uses [Unity](https://github.com/ThrowTheSwitch/Unity) test framework. This repository **must be cloned recursively** in order to get the test framework. Or clone later to the `tests/Unity` directory.

## Running Tests

### All At Once

To run all of the tests, run:

```bash
make
```

in `tests/` (current directory) directory. Beware that some tests needs extra hardware!

If `make` commands ends with exit status `0`, tests are successful.

To run tests in parallel, use `-j` flag. Beware that integration test uses hardware and those tests must be run sequentially. So, run only unit tests in parallel:

```bash
make -j unit
```

### One By One

All modules can be tested seperately.To run only one test, call `make` with it's path (including `/.` suffix). For example, to run `memories` module's unit tests:

```bash
make unit/memories/.
```

Unit and integration tests can be seperately runned too:

```bash
make unit         # Runs unit tests.
make integration  # Runs integration tests.
```

## Creating New Tests

### Unit

Let's assume new test name is `new_test`.

1. Create `tests/unit/new_test` directory.
2. Copy [`template_unit_test_makefile`](template_unit_test_makefile) to `tests/unit/new_test` directory and rename it to `Makefile`.
3. Append new source files to newly created `Makefile`.
