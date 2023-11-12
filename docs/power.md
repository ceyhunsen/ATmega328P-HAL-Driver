# Power Management And Sleep Modes

## Capabilities

* Set various sleep modes
* Enable/disable individual peripherals

## Sleep Modes

There are a bunch of sleep modes, defined in `enum power_sleep_modes`. These
sleep modes can be selected with `power_set_sleep_mode()` function.

## Module Enable/Disable

Modules can be enabled or disabled indidually using `power_set_module_power()`
function. Possible candidates are listed in `enum power_modules`.
