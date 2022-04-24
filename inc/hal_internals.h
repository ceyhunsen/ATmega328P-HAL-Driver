/**
 * @file hal_internals.h
 * @author Ceyhun Şen
 * @brief Internal header file for ATmega328P HAL driver.
 * */

#ifndef __HAL_INTERNALS_H
#define __HAL_INTERNALS_H

#define F_CPU 16000000UL

#define _CLEAR_BIT(port, bit) (port &= ~(1 << bit))

#endif // __HAL_INTERNALS_H
