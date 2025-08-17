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

hal_pin_result_t hal_pin_init(struct hal_pin_context * pin_ctxt);
hal_pin_result_t hal_pin_deinit(struct hal_pin_context * pin_ctxt);
hal_pin_result_t hal_pin_set_config(struct hal_pin_context * pin_ctxt, struct hal_pin_config * config );
hal_pin_result_t hal_pin_get_config(struct hal_pin_context * pin_ctxt, struct hal_pin_config * config );
hal_pin_result_t hal_pin_set_state(struct hal_pin_context * pin_ctxt, hal_pin_state_t value);
hal_pin_result_t hal_pin_get_state(struct hal_pin_context * pin_ctxt, hal_pin_state_t *value);
hal_pin_result_t hal_pin_set_callback( struct hal_pin_context * pin_ctxt, hal_pin_callback_t callback );
hal_pin_result_t hal_pin_set_direction(struct hal_pin_context * pin_ctxt, hal_pin_dir_t direction, hal_pin_pull_mode_t pull_mode);

#endif
