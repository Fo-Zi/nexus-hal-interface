/**
 * @file hal_uart_async.h
 * @brief Hardware Abstraction Layer (HAL) for asynchronous UART communication.
 *
 * This header defines the public interface for asynchronous UART operations using internal buffers.
 * It provides functions for enabling async mode, managing buffers, and performing
 * non-blocking read/write operations with callback completion.
 *
 * Async mode provides non-blocking data flow using internal TX/RX buffers managed by the HAL.
 * This mode requires HAL_UART_ASYNC_BUFFERED_SUPPORT to be defined at compile time.
 *
 * @note This header requires hal_uart_basic.h to be included first for base functionality
 */

#ifndef HAL_UART_ASYNC_H
#define HAL_UART_ASYNC_H

#include <stddef.h>
#include <stdint.h>

#include "hal_common.h"
#include "hal_uart_types.h"

// Only provide async API if support enabled in private implementation header
#if defined(HAL_UART_ASYNC_BUFFERED_SUPPORT)

hal_uart_result_t hal_uart_enable_async_mode(
    struct hal_uart_context * uart_ctxt,
    const struct hal_uart_async_buffered_config *buffered_cfg
);

hal_uart_result_t hal_uart_disable_async_mode(
    struct hal_uart_context * uart_ctxt
);

hal_uart_result_t hal_uart_set_buffered_config(
    struct hal_uart_context * uart_ctxt,
    const struct hal_uart_async_buffered_config *buffered_cfg
);

hal_uart_result_t hal_uart_write_async(
    struct hal_uart_context * uart_ctxt,
    const uint8_t *data, size_t len,
    hal_timeout_ms timeout
);

hal_uart_result_t hal_uart_read_async(
    struct hal_uart_context * uart_ctxt,
    uint8_t *data, size_t len, size_t *bytes_read,
    hal_timeout_ms timeout
);

hal_uart_result_t hal_uart_get_rx_available(
    struct hal_uart_context * uart_ctxt,
    size_t *bytes_available
);

hal_uart_result_t hal_uart_get_tx_free(
    struct hal_uart_context * uart_ctxt,
    size_t *bytes_free
);

hal_uart_result_t hal_uart_flush_tx(
    struct hal_uart_context * uart_ctxt,
    hal_timeout_ms timeout
);

hal_uart_result_t hal_uart_clear_rx(
    struct hal_uart_context * uart_ctxt
);

#endif /* HAL_UART_BUFFERED_SUPPORT */

#endif /* HAL_UART_BUFFERED_H */
