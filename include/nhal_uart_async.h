/**
 * @file nhal_uart_async.h
 * @brief Hardware Abstraction Layer (HAL) for asynchronous UART communication.
 *
 * This header defines the public interface for asynchronous UART operations using internal buffers.
 * It provides functions for enabling async mode, managing buffers, and performing
 * non-blocking read/write operations with callback completion.
 *
 * Async mode provides non-blocking data flow using internal TX/RX buffers managed by the HAL.
 * This mode requires NHAL_UART_ASYNC_SUPPORT to be defined at compile time.
 *
 * @note This header requires nhal_uart_basic.h to be included first for base functionality
 */

#ifndef NHAL_UART_ASYNC_H
#define NHAL_UART_ASYNC_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"
#include "nhal_uart_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NHAL_UART_ASYNC_SUPPORT)

/**
 * @brief Initialize UART context for async mode
 * @param ctx Pointer to UART context structure
 * @param async_cfg Pointer to async configuration
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_init_async(
    struct nhal_uart_context * ctx,
    const struct nhal_async_config * async_cfg
);

/**
 * @brief Deinitialize UART async mode
 * @param ctx Pointer to UART context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_deinit_async(
    struct nhal_uart_context * ctx
);

/**
 * @brief Set callback for async operation completion
 * @param ctx Pointer to UART context structure
 * @param callback Callback function to execute on completion
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_set_async_callback(
    struct nhal_uart_context *ctx,
    nhal_async_complete_cb_t callback
);

/**
 * @brief Disable async completion callback
 * @param ctx Pointer to UART context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_disable_async_callback(
    struct nhal_uart_context *ctx
);

/**
 * @brief Get current async operation status
 * @param ctx Pointer to UART context structure
 * @return Current async operation status
 */
nhal_async_status_t nhal_uart_get_async_status(
    struct nhal_uart_context *ctx
);

/**
 * @brief Write data asynchronously
 * @param ctx Pointer to UART context structure
 * @param data Pointer to data to transmit
 * @param len Number of bytes to transmit
 * @param timeout_ms Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_write_async(
    struct nhal_uart_context * ctx,
    const uint8_t *data, size_t len,
    nhal_timeout_ms timeout_ms
);

/**
 * @brief Read data asynchronously
 * @param ctx Pointer to UART context structure
 * @param data Pointer to buffer for received data
 * @param len Number of bytes to read
 * @param timeout_ms Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_uart_read_async(
    struct nhal_uart_context * ctx,
    uint8_t *data, size_t len,
    nhal_timeout_ms timeout_ms
);

#endif /* NHAL_UART_ASYNC_SUPPORT */

#ifdef __cplusplus
}
#endif

#endif /* NHAL_UART_ASYNC_H */
