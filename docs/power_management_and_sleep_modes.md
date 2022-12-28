# Power Management And Sleep Modes

## Sleep Modes

ATmega328P supports 6 different sleep modes. This modes can be set via `hal_power_set_sleep_mode()` function. See ATmega328P data-sheet for individual sleep mode features.

ATmega328P can be waken up from a sleep with an interrupt.

Code example:

```c
// Set idle sleep mode.
hal_power_set_sleep_mode(hal_power_idle_mode);
```

## Module Power Modes

Every individual module can be turned off or on to reduce power usage. Use `hal_power_set_module_power()` function to set enable or disable modules.

Code example:

```c
// Disable ADC.
hal_power_set_module_power(hal_power_adc_off);
```
