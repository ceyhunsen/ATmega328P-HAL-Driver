/**
 * @file
 * @author Ceyhun Şen
 *
 * @brief Timer module, main functionalities.
 * */

// SPDX-FileCopyrightText: 2026 Ceyhun Şen <ceyhuusen@gmail.com>
// SPDX-License-Identifier: MIT

#include "hal_timer0.h"
#include "hal_internals.h"
#include "hal_io.h"

#include <avr/io.h>

/**
 * @brief Get current timer0 counter value.
 * @returns 8 bit value of the timer0 counter.
 */
uint8_t hal_timer0_get_counter() {
    volatile uint8_t val = TCNT0;
    return val;
}

/**
 * @brief Set new value to timer0 counter.
 */
void hal_timer0_set_counter(uint8_t val) { TCNT0 = val; }

/**
 * @brief Set the top value of the timer0 counter. This value will be the top
 * for the timer0 if the correct #hal_timer0_operation_modes is set.
 */
void hal_timer0_set_top(uint8_t val) { OCR0A = val; }

/**
 * @brief Set timer0 operation mode
 * @param mode Operation mode to be set
 * @returns Error if mode is invalid
 */
enum hal_result_timer0
hal_timer0_set_operation_mode(enum hal_timer0_operation_modes mode) {
    volatile uint8_t tccr0a, tccr0b;

    tccr0a = TCCR0A;
    tccr0b = TCCR0B;

    switch (mode) {
    case hal_timer0_mode_normal:
        CLEAR_BIT(tccr0b, WGM02);
        CLEAR_BIT(tccr0a, WGM01);
        CLEAR_BIT(tccr0a, WGM00);
        break;

    case hal_timer0_mode_ctc:
        CLEAR_BIT(tccr0b, WGM02);
        SET_BIT(tccr0a, WGM01);
        CLEAR_BIT(tccr0a, WGM00);
        break;

    case hal_timer0_mode_fast_pwm:
        CLEAR_BIT(tccr0b, WGM02);
        SET_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
        break;
    case hal_timer0_mode_fast_pwm_to_top:
        SET_BIT(tccr0b, WGM02);
        SET_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
        break;

    case hal_timer0_mode_phase_correct_pwm:
        CLEAR_BIT(tccr0b, WGM02);
        CLEAR_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
        break;
    case hal_timer0_mode_phase_correct_pwm_to_top:
        SET_BIT(tccr0b, WGM02);
        CLEAR_BIT(tccr0a, WGM01);
        SET_BIT(tccr0a, WGM00);
        break;

    default:
        return hal_result_timer0_invalid_operation_mode;
    }

    TCCR0A = tccr0a;
    TCCR0B = tccr0b;

    return hal_result_timer0_ok;
}

/**
 * @brief Get operation mode of the timer0.
 *
 * Reads related registers to determine current operation mode of the timer0
 * module.
 *
 * @returns Operation mode.
 */
enum hal_timer0_operation_modes hal_timer0_get_operation_mode() {
    uint8_t tccr0a, tccr0b;
    enum hal_timer0_operation_modes op_mode;

    tccr0a = TCCR0A & (BIT(WGM00) | BIT(WGM01));
    tccr0b = TCCR0B & BIT(WGM02);

    // WGM bit for the TCCR0B is not 2 but 3. Therefore, needs to be shifted 1
    // to the left.
    op_mode = tccr0a | (tccr0b >> 1);

    return op_mode;
}

/**
 * @brief Set output compare pin behaviour.
 *
 * Behavior will change based on the compare output mode. Please refer to the
 * datasheet for more information.
 *
 * @warning This call will make corresponding pin's direction to output, using
 * \ref hal_io_configure.
 *
 * @param reg Output compare register to set.
 * @param mode Output compare mode to set.
 *
 * @return Error if given mode or register is invalid, ok if everything is
 * valid.
 *
 * \see hal_timer0_output_compare_mode
 */
enum hal_result_timer0
hal_timer0_set_output_compare_mode(enum hal_timer0_output_compare_register reg,
                                   enum hal_timer0_output_compare_mode mode) {
    volatile uint8_t reg_val;
    uint8_t bit1, bit0;

    struct hal_io_pin io = {.port = hal_io_port_d};
    struct hal_io_pin_configuration configuration = {
        .direction = hal_io_direction_output,
    };

    // Set bits.
    switch (reg) {
    case hal_timer0_output_compare_register_a:
        bit1 = COM0A1;
        bit0 = COM0A0;

        io.pin = 6;
        if (hal_io_configure(io, configuration) != hal_result_io_ok) {
            return hal_result_timer0_cant_set_output_compare_io_pin;
        };
        break;
    case hal_timer0_output_compare_register_b:
        bit1 = COM0B1;
        bit0 = COM0B0;

        io.pin = 5;
        if (hal_io_configure(io, configuration) != hal_result_io_ok) {
            return hal_result_timer0_cant_set_output_compare_io_pin;
        };
        break;

    default:
        return hal_result_timer0_invalid_output_compare_register;
    }

    // Change the register.
    reg_val = TCCR0A;
    switch (mode) {
    case hal_timer0_compare_output_mode_normal:
        CLEAR_BIT(reg_val, bit1);
        CLEAR_BIT(reg_val, bit0);
        break;
    case hal_timer0_compare_output_mode_toggle:
        CLEAR_BIT(reg_val, bit1);
        SET_BIT(reg_val, bit0);
        break;
    case hal_timer0_compare_output_mode_clear:
        SET_BIT(reg_val, bit1);
        CLEAR_BIT(reg_val, bit0);
        break;
    case hal_timer0_compare_output_mode_set:
        SET_BIT(reg_val, bit1);
        SET_BIT(reg_val, bit0);
        break;

    default:
        return hal_result_timer0_invalid_output_compare_mode;
    }

    TCCR0A = reg_val;

    return hal_result_timer0_ok;
}

/**
 * @brief Set force output compare mode.
 *
 * @param reg Output compare register to set.
 * @param mode 0 to disable, non-zero to force enable.
 *
 * @returns Error if current mode or register is invalid, ok if everything is
 * valid.
 */
enum hal_result_timer0 hal_timer0_set_force_output_compare_mode(
    enum hal_timer0_output_compare_register reg, uint8_t mode) {
    uint8_t bit;

    // Check current operation mode and return error if it is one of PWM modes.
    switch (hal_timer0_get_operation_mode()) {
    case hal_timer0_mode_normal:
    case hal_timer0_mode_ctc:
        break;

    default:
        return hal_result_timer0_invalid_operation_mode;
    }

    switch (reg) {
    case hal_timer0_output_compare_register_a:
        bit = FOC0A;
        break;
    case hal_timer0_output_compare_register_b:
        bit = FOC0B;
        break;

    default:
        return hal_result_timer0_invalid_output_compare_register;
    }

    if (mode) {
        SET_BIT(TCCR0B, bit);
    } else {
        CLEAR_BIT(TCCR0B, bit);
    }

    return hal_result_timer0_ok;
}

/**
 * @brief Set timer0's clock source
 *
 * ## PWM Frequency
 *
 * This prescaler can be used to set PWM frequency. Formula is the following:
 *
 * f_OCnxPWM = f_clk_I/O / (N * 256)
 *
 * For example, if f_clk_I/O is 16 MHz and \ref hal_timer0_prescaler_1 is used,
 * frequency will end up being 62.5 KHz (16 MHz / 256).
 */
enum hal_result_timer0
hal_timer0_set_clock_source(enum hal_timer0_clock_source source) {
    volatile uint8_t reg = TCCR0B;

    switch (source) {
    case hal_timer0_stop:
        CLEAR_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_1:
        CLEAR_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_8:
        CLEAR_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_64:
        CLEAR_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_256:
        SET_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_prescaler_1024:
        SET_BIT(reg, CS02);
        CLEAR_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;
    case hal_timer0_external_falling_edge:
        SET_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        CLEAR_BIT(reg, CS00);
        break;
    case hal_timer0_external_rising_edge:
        SET_BIT(reg, CS02);
        SET_BIT(reg, CS01);
        SET_BIT(reg, CS00);
        break;

    default:
        return hal_result_timer0_invalid_clock_source;
    }

    TCCR0B = reg;

    return hal_result_timer0_ok;
}

/**
 * @brief Sets specified interrupt enabled or disabled
 *
 * @param interrupt Interrupt to clear
 * @param mode Non-zero to enable, zero to disable
 *
 * @returns Error if interrupt is not valid, OK if it is valid
 */
enum hal_result_timer0
hal_timer0_set_interrupt(enum hal_timer0_interrupt interrupt, uint8_t mode) {
    uint8_t bit;

    switch (interrupt) {
    case hal_timer0_overflow:
        bit = TOV0;
        break;
    case hal_timer0_output_compare_a:
        bit = OCF0A;
        break;
    case hal_timer0_output_compare_b:
        bit = OCF0B;
        break;

    default:
        return hal_result_timer0_invalid_interrupt;
    }

    if (mode) {
        SET_BIT(TIMSK0, bit);
    } else {
        CLEAR_BIT(TIMSK0, bit);
    }

    return hal_result_timer0_ok;
}

/**
 * @brief Clears specified interrupt, manually
 *
 * @param interrupt Interrupt to clear
 *
 * @returns Error if interrupt is not valid, OK if it is valid
 */
enum hal_result_timer0
hal_timer0_clear_interrupt(enum hal_timer0_interrupt interrupt) {
    switch (interrupt) {
    case hal_timer0_overflow:
        SET_BIT(TIFR0, TOV0);
        break;
    case hal_timer0_output_compare_a:
        SET_BIT(TIFR0, OCF0A);
        break;
    case hal_timer0_output_compare_b:
        SET_BIT(TIFR0, OCF0B);
        break;

    default:
        return hal_result_timer0_invalid_interrupt;
    }

    return hal_result_timer0_ok;
}
