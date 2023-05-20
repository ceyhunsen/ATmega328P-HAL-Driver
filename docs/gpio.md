# GPIO

TODO: This page needs rework

## Setting Pins As Output Or Input

Pins are configurable via `hal_io_set_pin_mode()` function. Pin port, pin and pin mode must be given as parameter to function.

Code example:

```c
// Set PB5 pin as output.
hal_io_set_pin_mode(hal_io_port_b, 5, hal_io_output_mode);
```

## Changing Pin State

Pins can be drived high or low with `hal_io_write_pin()` function. Pin port, pin and state must be given as parameter to function.

Code example:

```c
// Write high to PB5 pin.
hal_io_write_pin(hal_io_port_b, 5, hal_io_high_state);
```

## Toggling Pin State

Pin state can be toggled with `hal_io_toggle_pin()` function. Pin port and pin must be given as parameter to function.

Code example:

```c
// Toggle PB5 pin state.
hal_io_toggle_pin(hal_io_port_b, 5);
```

## Reading Pin State

Pin state can be read with `hal_io_read_pin()` function. Pin port and pin must be given as parameter to function. 1 will be returned if pin state is high, 0 otherwise.

Code example:

```c
// Read PB0 pin state.
uint8_t pb0_state = hal_io_read_pin(hal_io_port_b, 0);
if (pb0_state == 1) {
    printf("PB0 is in high state.\n");
}
else {
    printf("PB0 is in low state.\n");
}
```
