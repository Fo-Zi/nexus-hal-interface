/**
 * @file nhal_pin.h
 * @brief Header for the Hardware Abstraction Layer (HAL) Pin module.
 *
 * This module provides an interface for managing general-purpose I/O (GPIO) pins.
 * It defines types and functions for configuring, reading, writing, and
 * setting up callbacks for pin state changes.
 */
#ifndef NHAL_PIN_H_
#define NHAL_PIN_H_

#include <stdint.h>
#include <stdbool.h>

#include "nhal_pin_types.h"

nhal_result_t nhal_pin_init(struct nhal_pin_context * pin_ctxt);
nhal_result_t nhal_pin_deinit(struct nhal_pin_context * pin_ctxt);
nhal_result_t nhal_pin_set_config(struct nhal_pin_context * pin_ctxt, struct nhal_pin_config * config );
nhal_result_t nhal_pin_get_config(struct nhal_pin_context * pin_ctxt, struct nhal_pin_config * config );
nhal_result_t nhal_pin_set_state(struct nhal_pin_context * pin_ctxt, nhal_pin_state_t value);
nhal_result_t nhal_pin_get_state(struct nhal_pin_context * pin_ctxt, nhal_pin_state_t *value);
nhal_result_t nhal_pin_set_callback( struct nhal_pin_context * pin_ctxt, nhal_pin_callback_t callback );
nhal_result_t nhal_pin_set_direction(struct nhal_pin_context * pin_ctxt, nhal_pin_dir_t direction, nhal_pin_pull_mode_t pull_mode);

#endif
