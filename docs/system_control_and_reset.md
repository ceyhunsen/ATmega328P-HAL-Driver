# System Control And Reset

## Getting System Reset Source

System reset might be happened several reasons:

* Power on reset
* External reset
* Watchdog reset
* Brownout reset

To get reset source, use `hal_system_get_reset_status()` function and store the returned value. After that reset status register will be cleaned. So, store the returned value.

Example code:

```c
// Get reset status.
uint8_t reset_status = hal_system_get_reset_status();

// Use defined constants in system header to get system reset source.
// Check API reference for other reset sources.
if (reset_status & HAL_SYSTEM_WATCHDOG_RESET) {
    printf("Reset caused by a watchdog reset!\n");
}
```

## Configuring Watchdog

### Operating Modes

Watchdog timer has 3 operating modes:

* Interrupt
* System reset
* Interrupt and system reset

If interrupt mode is selected, remember to add ISR for `WDT_vect` vector. See [nongnu.org/avr-libc/user-manual/group__avr__interrupts.html](https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html) for more information.

### Setting Watchdog Timer

Watchdog timer can be set enabled or disabled with `hal_system_set_watchdog()` function. While calling this function, give timeout option and operating mode as parameters.

### Resetting Watchdog Timer

Watchdog timer can be reset with `hal_system_reset_watchdog()` function.
