# Memories

ATmega328P HAL driver supports EEPROM operations.

## Basic Operations

Basic operation is in blocking mode and will block other code until it's finished. Steps:

1. Create a `hal_memories_eeprom_t` struct and change it's members to desired values.
2. Call `hal_memories_eeprom_set()` function to set EEPROM modes.
3. Call `hal_memories_eeprom_read()` and `hal_memories_eeprom_write()` functions to read and write to EEPROM.

See `examples/memories/eeprom_basic.c` for reference code.
