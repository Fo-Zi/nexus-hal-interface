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

// Only provide async API if support enabled in private implementation header
#if defined(NHAL_UART_ASYNC_BUFFERED_SUPPORT)

nhal_result_t nhal_uart_enable_async_mode(
    struct nhal_uart_context * uart_ctxt,
    const struct nhal_uart_async_buffered_config *buffered_cfg
);

nhal_result_t nhal_uart_disable_async_mode(
    struct nhal_uart_context * uart_ctxt
);

nhal_result_t nhal_uart_set_buffered_config(
    struct nhal_uart_context * uart_ctxt,
    const struct nhal_uart_async_buffered_config *buffered_cfg
);

nhal_result_t nhal_uart_write_async(
    struct nhal_uart_context * uart_ctxt,
    const uint8_t *data, size_t len,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_uart_read_async(
    struct nhal_uart_context * uart_ctxt,
    uint8_t *data, size_t len, size_t *bytes_read,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_uart_get_rx_available(
    struct nhal_uart_context * uart_ctxt,
    size_t *bytes_available
);

nhal_result_t nhal_uart_get_tx_free(
    struct nhal_uart_context * uart_ctxt,
    size_t *bytes_free
);

nhal_result_t nhal_uart_flush_tx(
    struct nhal_uart_context * uart_ctxt,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_uart_clear_rx(
    struct nhal_uart_context * uart_ctxt
);

#endif /* NHAL_UART_BUFFERED_SUPPORT */

#endif /* NHAL_UART_BUFFERED_H */
