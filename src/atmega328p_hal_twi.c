/**
 * @file atmega328p_hal_twi.c
 * @author Ceyhun Şen
 * @brief Two wire interface HAL functions for ATmega328P HAL driver.
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

#include "atmega328p_hal_twi.h"
#include "atmega328p_hal_twi_internals.h"
#include "atmega328p_hal_internals.h"
#include <avr/io.h>
#include <util/twi.h>
#include <stdint.h>

/*******************************************************************************
 * Internal Functions
 ******************************************************************************/

/**
 * @brief Send start condition.
 * @returns Status value.
 * */
uint8_t hal_twi_send_start_condition()
{
	// Send START condition.
	TWCR = START_CONDITION;

	// Wait for START condition to be transmitted.
	loop_until_bit_is_set(TWCR, TWINT);

	// Return status.
	return TW_STATUS;
}

/**
 * @brief Send stop condition.
 * @returns Status value.
 * */
void hal_twi_send_stop_condition()
{
	// Send stop condition.
	TWCR = STOP_CONDITION;
}

/**
 * @brief Transmit a byte.
 * @param data Data byte that will be transmitted.
 * @returns Status value.
 * */
uint8_t hal_twi_transmit_byte(uint8_t data)
{
	// Write data and start transmission.
	TWDR = data;
	TWCR = START_TRANSMISSION;

	// Wait for data to be transmitted.
	loop_until_bit_is_set(TWCR, TWINT);

	// Return status.
	return TW_STATUS;
}

/**
 * @brief Receive a byte.
 * @param data Received data pointer.
 * @param is_more Is there any more data that will be read later?
 * @returns Status value.
 * */
uint8_t hal_twi_receive_byte(uint8_t *data, uint8_t is_more)
{
	// Start receiving.
	if (is_more > 0) {
		TWCR = START_RECEIVING_ACK;
	}
	else {
		TWCR = START_RECEIVING_NACK;
	}

	// Wait for data to be received.
	loop_until_bit_is_set(TWCR, TWINT);

	// Save data.
	*data = TWDR;

	// Return status.
	return TW_STATUS;
}

/**
 * @brief Send slave address.
 * @param slave_address Slave address to be transmitted. This address should be
 * set write or read before calling this function.
 * @returns Status value.
 * */
uint8_t hal_twi_transmit_slave_address(uint8_t slave_address)
{
	// Send slave address and return status.
	return hal_twi_transmit_byte(slave_address);
}

uint8_t hal_twi_transmit_register(uint16_t reg, hal_twi_register_size reg_size)
{
	uint8_t status = 0;

	switch (reg_size) {
		case hal_twi_register_size_2_byte:
			status = hal_twi_transmit_byte((uint8_t)(reg >> 8));
			if (status != TW_MT_DATA_ACK)
				return status;
		case hal_twi_register_size_1_byte:
		default:
			status = hal_twi_transmit_byte(reg);
	}

	return status;
}

/*******************************************************************************
 * Core Functions
 ******************************************************************************/

/**
 * @brief Initialize TWI. CPU frequency is defaulted to 16 MHz.
 * @param bit_rate Bit rate option.
 * */
void hal_twi_init(hal_twi_bit_rate bit_rate)
{
	// Clear prescaler bits.
	_CLEAR_BIT(TWSR, TWPS1);
	_CLEAR_BIT(TWSR, TWPS0);

	// Set bit rate.
	switch (bit_rate) {
		default:
		case hal_twi_standart_mode:
			TWBR = 72;
			break;
		case hal_twi_fast_mode:
			TWBR = 12;
			break;
	}
}

/**
 * @brief Write data to specific memory over TWI.
 * @param slave_address Targeted slave address.
 * @param reg Register for memory write.
 * @param reg_size Register size in bytes.
 * @param buffer Data buffer to be transmitted.
 * @param len Data buffer length. If this value is 0, stop condition won't be
 * send to the bus so that repeated start condtion can be send.
 * @returns 0 if success, status otherwise.
 * @see hal_twi_register_size
 * */
uint8_t hal_twi_write_memory(uint8_t slave_address, uint16_t reg, hal_twi_register_size reg_size, uint8_t *buffer, uint16_t len)
{
	uint8_t status = 0;

	// Send START condition.
	status = hal_twi_send_start_condition();
	if (status != TW_START) {
		hal_twi_send_stop_condition();
		return status;
	}

	// Set slave write address.
	status = hal_twi_transmit_slave_address(SLAVE_ADDRESS_WRITE(slave_address));
	if (status != TW_MT_SLA_ACK) {
		hal_twi_send_stop_condition();
		return status;
	}

	// Set register address.
	status = hal_twi_transmit_register(reg, reg_size);
	if (status != TW_MT_DATA_ACK) {
		hal_twi_send_stop_condition();
		return status;
	}

	// Transmit data.
	for (uint16_t i = 0; i < len; i++) {
		status = hal_twi_transmit_byte(buffer[i]);
		if (status != TW_MT_DATA_ACK)
			return status;
	}

	// Send stop condition if any data is sent. If not any data is sent, prepare
	// for repeated start condition.
	if (len != 0)
		hal_twi_send_stop_condition();

	return 0;
}

/**
 * @brief Read data from specific memory over TWI.
 * @param slave_address Targeted slave address.
 * @param reg Register for memory read.
 * @param reg_size Register size in bytes.
 * @param buffer Data buffer that will hold read data.
 * @param len Data buffer length.
 * @returns 0 if success, status otherwise.
 * @see hal_twi_register_size
 * */
uint8_t hal_twi_read_memory(uint8_t slave_address, uint16_t reg, hal_twi_register_size reg_size, uint8_t *buffer, uint16_t len)
{
	uint8_t status = 0;

	// Send register address.
	status = hal_twi_write_memory(slave_address, reg, reg_size, buffer, 0);
	if (status != 0) {
		hal_twi_send_stop_condition();
		return status;
	}

	// Send repeated start condition.
	status = hal_twi_send_start_condition();
	if (status != TW_REP_START) {
		hal_twi_send_stop_condition();
		return status;
	}

	// Send slave read address.
	status = hal_twi_transmit_slave_address(SLAVE_ADDRESS_READ(slave_address));
	if (status != TW_MR_SLA_ACK) {
		hal_twi_send_stop_condition();
		return status;
	}

	// Receive data.
	for (uint16_t i = 0; i < len; i++) {
		status = hal_twi_receive_byte(&buffer[i], len - i - 1);
		if (status != TW_MR_DATA_ACK && i < len - 1) {
			hal_twi_send_stop_condition();
			return status;
		}
		else if (status != TW_MR_DATA_NACK && i == len - 1) {
			hal_twi_send_stop_condition();
			return status;
		}
	}

	// Send stop condition end return success.
	hal_twi_send_stop_condition();
	return 0;
}
