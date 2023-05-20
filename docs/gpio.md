# GPIO

## Setting Pins As Output Or Input

Pins are configurable via `gpio_set_direction()` function.

Code example:

```c
enum gpio_result result;

// Set PB5 pin as output.
result = gpio_set_direction(gpio_port_b, 5, gpio_direction_output);

// Set PC4 pin as input, pull up off.
result = gpio_set_direction(gpio_port_c, 4, gpio_direction_input_pull_up_off);

// Set PD4 pin as input, pull up on.
result = gpio_set_direction(gpio_port_d, 3, gpio_direction_input_pull_up_on);
```

## Changing Pin State

Pins can be driven high or low with `gpio_write()` function.

Code example:

```c
enum gpio_result result;

// Write high to PB5 pin.
result = gpio_write(gpio_port_b, 5, gpio_state_high);

// Write low to PB5 pin.
result = gpio_write(gpio_port_b, 5, gpio_state_low);
```

## Toggling Pin State

Pin state can be toggled with `gpio_toggle()` function.

Code example:

```c
enum gpio_result result;

// Toggle PB5 pin state.
result = gpio_toggle(gpio_port_b, 5);
```

## Reading Pin State

Pin state can be read with `gpio_read()` function.

Code example:

```c
enum gpio_result result;
enum gpio_state state;

// Read PB0 pin state.
result = gpio_read(gpio_port_b, 0, &state);

if (state == gpio_state_high) {
    printf("PB0 is in high state.\n");
}
else {
    printf("PB0 is in low state.\n");
}
```
