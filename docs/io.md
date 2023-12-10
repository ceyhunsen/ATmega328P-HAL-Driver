# I/O Ports

## Capabilities

* Pin direction can be set to input or output
    * Pull-up or pull-down selection when pin is configured as input
* High or low signal output when pin is configured as output
    * Toggle pin output signal when pin is configured as output
* Pin level reading when pin is configured as input

## Function Return Type

Every I/O function will return `enum io_result` type. This value can be
checked if operation is successful or not.

## Configuring Pins

Configuring a I/O pin is done with `io_configure()` function. This function
will accept any kind of information about a pin.

### Switching Between Input and Output

`struct io_pin_configuration.direction` can be used to specify direction of an
I/O pin.

### Setting Pin As Pull-Up/Pull-Down In Input Mode

I/O pins with input direction, can be configured with pull-up enabled or
disabled. To do this, `struct io_pin_configuration.is_pull_up` can be used.

## Read/Write Operations On Pins

### Change Pin Output State

I/O pins can be driven high or low with `io_write()` function.

### Toggling Pin Output State

Pin state can be toggled with `io_toggle()` function.

### Reading Pin Input State

Pin state can be read with `io_read()` function. Read value should be stored
in given `enum io_pin_state` pointer.
