/**
 * @file nhal_uart_async.h
 * @brief Hardware Abstraction Layer (HAL) for asynchronous UART communication.
 *
 * This header defines the public interface for asynchronous UART operations using internal buffers.
 * It provides functions for enabling async mode, managing buffers, and performing
 * non-blocking read/write operations with callback completion.
 *
 * Async mode provides non-blocking data flow using internal TX/RX buffers managed by the HAL.
 * This mode requires NHAL_UART_ASYNC_BUFFERED_SUPPORT to be defined at compile time.
 *
 * @note This header requires nhal_uart_basic.h to be included first for base functionality
 */

#ifndef NHAL_UART_ASYNC_H
#define NHAL_UART_ASYNC_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"
#include "nhal_uart_types.h"

#if defined(NHAL_UART_ASYNC_SUPPORT)

nhal_result_t nhal_uart_init_async(
    struct nhal_uart_context * ctx,
    const struct nhal_async_config * async_cfg
);

nhal_result_t nhal_uart_deinit_async(
    struct nhal_uart_context * ctx
);

nhal_result_t nhal_uart_set_async_callback(
    struct nhal_uart_context *ctx,
    nhal_async_complete_cb_t callback
);

nhal_result_t nhal_uart_disable_async_callback(
    struct nhal_uart_context *ctx
);

nhal_async_status_t nhal_uart_get_async_status(
    struct nhal_uart_context *ctx
);

nhal_result_t nhal_uart_write_async(
    struct nhal_uart_context * ctx,
    const uint8_t *data, size_t len,
    nhal_timeout_ms timeout_ms
);

nhal_result_t nhal_uart_read_async(
    struct nhal_uart_context * ctx,
    uint8_t *data, size_t len,
    nhal_timeout_ms timeout_ms
);

#endif /* NHAL_UART_ASYNC_SUPPORT */

#endif /* NHAL_UART_ASYNC_H */
