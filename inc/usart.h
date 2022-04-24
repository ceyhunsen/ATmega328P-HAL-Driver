/**
 * @file usart.h
 * @author Ceyhun Şen
 * @brief USART header file for ATmega328P HAL driver.
 * */

#ifndef __ATMEGA328P_USART_H
#define __ATMEGA328P_USART_H

#include <avr/io.h>
#include <stdint.h>

/**
 * @enum usart_operating_mode
 * @brief Operating modes for USART.
 * */
typedef enum usart_operating_mode {
	asynchronous_normal_mode,
	asynchronous_double_speed_mode,
	synchronous_master_mode
} usart_operating_mode;

/**
 * @enum usart_parity
 * @brief Parity settings for USART.
 * */
typedef enum usart_parity {
	disabled,
	even_parity,
	odd_parity
} usart_parity;

/**
 * @enum usart_mode
 * @brief Modes for USART.
 * */
typedef enum usart_mode {
	transmit,
	receive,
	transmit_receive
} usart_mode;

/**
 * @struct usart_t
 * @brief USART definitions.
 * */
typedef struct usart_t {
	uint16_t baud_rate;
	uint8_t stop_bits;
	uint8_t data_bits;
	usart_parity parity;
	usart_operating_mode operating_mode;
	usart_mode mode;
} usart_t;

void usart_init(usart_t *usart);
void usart_transmit(usart_t *usart, uint8_t *data, uint16_t len);
void usart_receive(usart_t *usart, uint8_t *data, uint16_t len);

#endif // __ATMEGA328P_USART_H
