/**
 * @file nhal_pin.h
 * @brief Header for the Hardware Abstraction Layer (HAL) Pin module.
 *
 * This module provides a SYNCHRONOUS interface for managing general-purpose I/O (GPIO) pins.
 * All configuration, read, and write operations are blocking and complete before returning.
 * It defines types and functions for configuring, reading, writing, and
 * setting up asynchronous callbacks for pin state changes.
 */
#ifndef NHAL_PIN_H
#define NHAL_PIN_H

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
 * @brief Set pin direction and pull mode
 * @param ctx Pointer to pin context structure
 * @param direction Pin direction (input/output)
 * @param pull_mode Pull resistor configuration
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_set_direction(struct nhal_pin_context * ctx, nhal_pin_dir_t direction, nhal_pin_pull_mode_t pull_mode);

/**
 * @brief Configure GPIO pin interrupt
 *
 * @param ctx Pointer to initialized pin context
 * @param trigger Interrupt trigger type
 * @param callback Interrupt callback function
 * @param user_data User-provided data pointer passed to callback
 * @return NHAL_OK on success, error code otherwise
 *
 * @retval NHAL_ERR_BUSY Hardware resource conflict (STM32: EXTI line already used)
 * @retval NHAL_ERR_UNSUPPORTED Trigger type not supported by hardware
 */
nhal_result_t nhal_pin_set_interrupt_config(
    struct nhal_pin_context *ctx,
    nhal_pin_int_trigger_t trigger,
    nhal_pin_callback_t callback,
    void *user_data
);

/**
 * @brief Enable GPIO pin interrupt
 *
 * Enables the interrupt for a previously configured pin.
 *
 * @param ctx Pointer to initialized pin context
 * @return NHAL_OK on success, error code otherwise
 *
 * @retval NHAL_ERR_NOT_CONFIGURED Interrupt not configured for this pin
 */
nhal_result_t nhal_pin_interrupt_enable(struct nhal_pin_context *ctx);

/**
 * @brief Disable GPIO pin interrupt
 *
 * Disables the interrupt for a configured pin without removing configuration.
 *
 * @param ctx Pointer to initialized pin context
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_pin_interrupt_disable(struct nhal_pin_context *ctx);

#ifdef __cplusplus
}
#endif

#endif
