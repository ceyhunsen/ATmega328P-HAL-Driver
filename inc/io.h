/**
 * @file io.h
 * @author Ceyhun Şen
 * @brief I/O header file for ATmega328P HAL driver.
 * */

#ifndef __IO_H
#define __IO_H

#include <stdint.h>

// Pin modes.
#define output             0
#define input              1
#define input_pull_up_on   1
#define input_pull_up_off  2

// I/O ports
#define PORTA 1
#define PORTB 2
#define PORTC 3
#define PORTD 4

void io_set_pin_mode(uint8_t port, uint8_t pin, uint8_t mode);
void io_write_pin(uint8_t port, uint8_t pin, uint8_t state);
uint8_t io_read_pin(uint8_t port, uint8_t pin);

#endif // __IO_H
