# ATmega328P HAL Drivers

Unofficial HAL drivers for ATmega328P microcontroller.

**This driver is still in development! Use it in your own risk.**

## Adding To Project

ATmega328P hal driver should be added as a submodule to your project:

```bash
cd project/drivers/directory
git submodule add https://github.com/ceyhunsen/ATmega328P-HAL-Driver.git
```

For contributing to project, clone it recursively for third party libraries:

```bash
git clone --recurse-submodules https://github.com/ceyhunsen/ATmega328P-HAL-Driver.git
```

## Documentation

Documentation is available at
[atmega328p-hal-driver.rtfd.io](http://atmega328p-hal-driver.rtfd.io/).
Alternatively, documentation can be generated locally with:

```bash
cd docs/
doxygen Doxyfile
```

Generated documents will be placed in `docs/build` directory.

## License

This project is licensed under [MIT license](LICENSE).
