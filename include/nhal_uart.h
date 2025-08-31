/**
 * @file nhal_uart_basic.h
 * @brief Hardware Abstraction Layer (HAL) for synchronous UART communication.
 *
 * This header defines the public interface for synchronous (blocking) UART operations.
 * It provides functions for initializing, deinitializing, configuring, writing to, and
 * reading from UART instances in blocking mode.
 *
 * Synchronous mode provides blocking operations with automatic transfer optimization.
 * All operations block until completion or timeout.
 *
 * @note For asynchronous operations, see nhal_uart_async.h
 */

#ifndef NHAL_UART_H
#define NHAL_UART_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"
#include "nhal_uart_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize UART context in basic mode
 * @param ctx Pointer to UART context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_init(struct nhal_uart_context * ctx);

/**
 * @brief Deinitialize UART context
 * @param ctx Pointer to UART context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_deinit(struct nhal_uart_context * ctx);

/**
 * @brief Set UART configuration
 * @param ctx Pointer to UART context structure
 * @param cfg Pointer to configuration structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_set_config(struct nhal_uart_context * ctx, struct nhal_uart_config *cfg);

/**
 * @brief Get current UART configuration
 * @param ctx Pointer to UART context structure
 * @param cfg Pointer to configuration structure to fill
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_get_config(struct nhal_uart_context * ctx, struct nhal_uart_config *cfg);

/**
 * @brief Write data to UART (blocking)
 * @param ctx Pointer to UART context structure
 * @param data Pointer to data to transmit
 * @param len Number of bytes to transmit
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_write(struct nhal_uart_context * ctx, const uint8_t *data, size_t len);

/**
 * @brief Read data from UART (blocking)
 * @param ctx Pointer to UART context structure
 * @param data Pointer to buffer for received data
 * @param len Number of bytes to read
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_read(struct nhal_uart_context * ctx, uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* NHAL_UART_BASIC_H */
