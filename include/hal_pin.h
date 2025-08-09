/**
 * @file hal_pin.h
 * @brief Header for the Hardware Abstraction Layer (HAL) Pin module.
 *
 * This module provides an interface for managing general-purpose I/O (GPIO) pins.
 * It defines types and functions for configuring, reading, writing, and
 * setting up callbacks for pin state changes.
 */
#ifndef HAL_PIN_H_
#define HAL_PIN_H_

#include <stdint.h>
#include <stdbool.h>

#include "hal_pin_types.h"

hal_pin_result_t hal_pin_init(hal_pin_context_t * pin_ctxt);
hal_pin_result_t hal_pin_deinit(hal_pin_context_t * pin_ctxt);
hal_pin_result_t hal_pin_set_config(hal_pin_context_t * pin_ctxt, hal_pin_config_t * config );
hal_pin_result_t hal_pin_get_config(hal_pin_context_t * pin_ctxt, hal_pin_config_t * config );
hal_pin_result_t hal_pin_set_state(hal_pin_context_t * pin_ctxt, hal_pin_state_t value);
hal_pin_result_t hal_pin_get_state(hal_pin_context_t * pin_ctxt, hal_pin_state_t *value);
hal_pin_result_t hal_pin_set_callback( hal_pin_context_t * pin_ctxt, hal_pin_callback_t callback );

#endif
