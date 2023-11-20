# I/O Ports

## Capabilities

* Pin direction can be set to input or output
    * Pull-up or pull-down selection when pin is configured as input
* High or low signal output when pin is configured as output
    * Toggle pin output signal when pin is configured as output
* Pin level reading when pin is configured as input

## Function Return Values

Every I/O function will return `enum io_result` type. This value can be
checked if operation is successful or not.

## Configuring Pins

Configuring a I/O pin is done with `io_configure()` function. This function
will accept any kind of information about a pin.

### Setting Pin Direction

`struct io_pin_configuration.direction` can be used to specify direction of an
I/O pin.

Code example:

```c
enum io_result result;
struct io_pin_configuration conf;
struct io_pin io;

// Set PB5 pin as output.
io.port = io_port_b;
io.pin = 5;
conf.direction = io_direction_output;
result = io_configure(io, conf);

// Set PC4 pin as input.
io.port = io_port_c;
io.pin = 4;
conf.direction = io_direction_input;
result = io_configure(io, conf);
```

### Setting Pull-Up Value

I/O pins with input direction, can be configured with pull-up enabled or
disabled. To do this, `struct io_pin_configuration.is_pull_up` can be used.

Code example:

```c
enum io_result result;
struct io_pin_configuration conf;
struct io_pin io;

// Set PB5 pin as input and pull-up enabled.
io.port = io_port_b;
io.pin = 5;
conf.direction = io_direction_input;
conf.is_pull_up = 1;
result = io_configure(io, conf);

// Set PC4 pin as input and pull-up disabled.
io.port = io_port_c;
io.pin = 4;
conf.direction = io_direction_input;
conf.is_pull_up = 0;
result = io_configure(io, conf);
```

## Read/Write Operations On Pins

### Write New State To A Pin

I/O pins can be driven high or low with `io_write()` function.

Code example:

```c
enum io_result result;
struct io_pin io;

// Write high to PB5 pin.
io.port = io_port_b;
io.pin = 5;
result = io_write(io, io_state_high);

// Write low to PB5 pin.
io.port = io_port_b;
io.pin = 5;
result = io_write(io, io_state_low);
```

## Toggling Pin State

Pin state can be toggled with `io_toggle()` function.

Code example:

```c
enum io_result result;
struct io_pin io;

// Toggle PB5 pin state.
io.port = io_port_b;
io.pin = 5;
result = io_toggle(io);
```

## Reading Pin State

Pin state can be read with `io_read()` function.

Code example:

```c
enum io_result result;
enum io_pin_state state;
struct io_pin io;

// Read PB0 pin state.
io.port = io_port_b;
io.pin = 0;
result = io_read(io, &state);

if (state == io_state_high) {
    printf("PB0 is in high state.\n");
}
else {
    printf("PB0 is in low state.\n");
}
```
