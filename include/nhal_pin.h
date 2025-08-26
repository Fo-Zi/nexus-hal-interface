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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize pin context
 * @param ctx Pointer to pin context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_init(struct nhal_pin_context * ctx);
/**
 * @brief Deinitialize pin context
 * @param ctx Pointer to pin context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_deinit(struct nhal_pin_context * ctx);
/**
 * @brief Set pin configuration
 * @param ctx Pointer to pin context structure
 * @param config Pointer to pin configuration structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_set_config(struct nhal_pin_context * ctx, struct nhal_pin_config * config );
/**
 * @brief Get current pin configuration
 * @param ctx Pointer to pin context structure
 * @param config Pointer to pin configuration structure to fill
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_get_config(struct nhal_pin_context * ctx, struct nhal_pin_config * config );
/**
 * @brief Set pin state (high/low)
 * @param ctx Pointer to pin context structure
 * @param value Pin state to set
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_set_state(struct nhal_pin_context * ctx, nhal_pin_state_t value);
/**
 * @brief Get current pin state
 * @param ctx Pointer to pin context structure
 * @param value Pointer to store the current pin state
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_get_state(struct nhal_pin_context * ctx, nhal_pin_state_t *value);
/**
 * @brief Set interrupt callback for pin state changes
 * @param ctx Pointer to pin context structure
 * @param callback Callback function to execute on pin state change
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_set_callback( struct nhal_pin_context * ctx, nhal_pin_callback_t callback );
/**
 * @brief Set pin direction and pull mode
 * @param ctx Pointer to pin context structure
 * @param direction Pin direction (input/output)
 * @param pull_mode Pull resistor configuration
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_set_direction(struct nhal_pin_context * ctx, nhal_pin_dir_t direction, nhal_pin_pull_mode_t pull_mode);

#ifdef __cplusplus
}
#endif

#endif
