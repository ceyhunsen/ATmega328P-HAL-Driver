# GPIO

## Capabilities

* Pin direction can be set to input or output
    * Pull-up or pull-down selection when pin is configured as input
* High or low signal output when pin is configured as output
    * Toggle pin output signal when pin is configured as output
* Pin level reading when pin is configured as input

## Function Return Values

Every GPIO function will return `enum gpio_result` type. This value can be
checked if operation is successful or not.

## Configuring Pins

Configuring a GPIO pin is done with `gpio_configure()` function. This function
will accept any kind of information about a pin.

### Setting Pin Direction

`struct gpio_pin_configuration.direction` can be used to specify direction of a
GPIO pin.

Code example:

```c
enum gpio_result result;
struct gpio_pin_configuration conf;
struct gpio_pin gpio;

// Set PB5 pin as output.
gpio.port = gpio_port_b;
gpio.pin = 5;
conf.direction = gpio_direction_output;
result = gpio_configure(gpio, conf);

// Set PC4 pin as input.
gpio.port = gpio_port_c;
gpio.pin = 4;
conf.direction = gpio_direction_input;
result = gpio_configure(gpio, conf);
```

### Setting Pull-Up Value

GPIO pins with input direction, can be configured with pull-up enabled or
disabled. To do this, `struct gpio_pin_configuration.is_pull_up` can be used.

Code example:

```c
enum gpio_result result;
struct gpio_pin_configuration conf;
struct gpio_pin gpio;

// Set PB5 pin as input and pull-up enabled.
gpio.port = gpio_port_b;
gpio.pin = 5;
conf.direction = gpio_direction_input;
conf.is_pull_up = 1;
result = gpio_configure(gpio, conf);

// Set PC4 pin as input and pull-up disabled.
gpio.port = gpio_port_c;
gpio.pin = 4;
conf.direction = gpio_direction_input;
conf.is_pull_up = 0;
result = gpio_configure(gpio, conf);
```

## Read/Write Operations On Pins

### Write New State To A Pin

GPIO pins can be driven high or low with `gpio_write()` function.

Code example:

```c
enum gpio_result result;
struct gpio_pin gpio;

// Write high to PB5 pin.
gpio.port = gpio_port_b;
gpio.pin = 5;
result = gpio_write(gpio, gpio_state_high);

// Write low to PB5 pin.
gpio.port = gpio_port_b;
gpio.pin = 5;
result = gpio_write(gpio, gpio_state_low);
```

## Toggling Pin State

Pin state can be toggled with `gpio_toggle()` function.

Code example:

```c
enum gpio_result result;
struct gpio_pin gpio;

// Toggle PB5 pin state.
gpio.port = gpio_port_b;
gpio.pin = 5;
result = gpio_toggle(gpio);
```

## Reading Pin State

Pin state can be read with `gpio_read()` function.

Code example:

```c
enum gpio_result result;
enum gpio_pin_state state;
struct gpio_pin gpio;

// Read PB0 pin state.
gpio.port = gpio_port_b;
gpio.pin = 0;
result = gpio_read(gpio, &state);

if (state == gpio_state_high) {
    printf("PB0 is in high state.\n");
}
else {
    printf("PB0 is in low state.\n");
}
```
