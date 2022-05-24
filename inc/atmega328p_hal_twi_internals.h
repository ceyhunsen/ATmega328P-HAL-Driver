/**
 * @file atmega328p_hal_twi_internals.h
 * @author Ceyhun Şen
 * @brief Two wire interface internal header file for ATmega328P HAL driver.
 * */

/*
 * MIT License
 * 
 * Copyright (c) 2022 Ceyhun Şen
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */

#ifndef __ATMEGA328P_HAL_TWI_INTERNALS_H
#define __ATMEGA328P_HAL_TWI_INTERNALS_H

#include "atmega328p_hal_internals.h"

/**
 * @brief Start transmission bits.
 * */
#define START_TRANSMISSION (_PIN_TO_BIT(TWINT) | _PIN_TO_BIT(TWEN))

/**
 * @brief Start receiving data and send ack bit.
 * */
#define START_RECEIVING_ACK (START_TRANSMISSION | _PIN_TO_BIT(TWEA))

/**
 * @brief Start receiving data and send nack bit.
 * */
#define START_RECEIVING_NACK START_TRANSMISSION

/**
 * @brief START condition bits.
 * */
#define START_CONDITION (START_TRANSMISSION | _PIN_TO_BIT(TWSTA))

/**
 * @brief STOP condition bits.
 * */
#define STOP_CONDITION (START_TRANSMISSION | _PIN_TO_BIT(TWSTO))

/**
 * @brief Transform 7 bit slave address to 8 bit slave write address.
 * */
#define SLAVE_ADDRESS_WRITE(address) (((address) << 1) | TW_WRITE)

/**
 * @brief Transform 7 bit slave address to 8 bit slave read address.
 * */
#define SLAVE_ADDRESS_READ(address)  (((address) << 1) | TW_READ)

// Internal functions.
uint8_t hal_twi_send_start_condition();
void hal_twi_send_stop_condition();
uint8_t hal_twi_transmit_byte(uint8_t data);
uint8_t hal_twi_receive_byte(uint8_t *data, uint8_t is_end);
uint8_t hal_twi_transmit_slave_address(uint8_t slave_address);
uint8_t hal_twi_transmit_register(uint16_t reg, hal_twi_register_size reg_size);

#endif // __ATMEGA328P_HAL_TWI_INTERNALS_H
