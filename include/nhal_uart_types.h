/**
 * @file nhal_uart_types.h
 * @brief Defines common data types, enumerations, and structures for UART HAL operations.
 *
 * This header provides the necessary type definitions used across the Universal Asynchronous
 * Receiver-Transmitter (UART) Hardware Abstraction Layer (HAL). It includes definitions
 * for UART identifiers, operation status codes, parity settings, and structures for
 * common and complete UART configurations, as well as the UART context/handle.
 * These types aim to provide a consistent interface for various UART implementations.
 */

#ifndef NHAL_UART_TYPES_H
#define NHAL_UART_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"

typedef uint8_t nhal_uart_bus_id;


typedef enum {
    NHAL_UART_PARITY_NONE,   /**< No parity bit is used. */
    NHAL_UART_PARITY_EVEN,   /**< Parity bit is set such that the total number of '1' bits is even. */
    NHAL_UART_PARITY_ODD,    /**< Parity bit is set such that the total number of '1' bits is odd. */
} nhal_uart_parity_t;

typedef enum {
    NHAL_UART_STOP_BITS_1,       /**< 1 stop bit is used. */
    NHAL_UART_STOP_BITS_2,       /**< 2 stop bits are used. */
} nhal_uart_stop_bits_t;

typedef enum {
    NHAL_UART_DATA_BITS_7,       /**< 7 data bits are used. */
    NHAL_UART_DATA_BITS_8,       /**< 8 data bits are used. */
} nhal_uart_data_bits_t;

struct nhal_uart_config{
    uint32_t baudrate;              /**< The baud rate for communication (bits per second). */
    nhal_uart_parity_t parity;       /**< The parity setting (none, even, or odd). */
    nhal_uart_stop_bits_t stop_bits; /**< The number of stop bits (e.g., 1 or 2). */
    nhal_uart_data_bits_t data_bits; /**< The number of data bits (e.g., 7 or 8). */
    struct nhal_uart_impl_config * impl_config;
};

typedef enum {
    NHAL_UART_OP_MODE_SYNC_ONLY,        /**< Synchronous blocking operations only. */
    NHAL_UART_OP_MODE_SYNC_AND_ASYNC    /**< Both synchronous and asynchronous operations. */
} nhal_uart_operation_mode_t;

/**
 * @brief Base UART context - always present, minimal footprint
 */
struct nhal_uart_context{
    nhal_uart_bus_id uart_bus_id;
    nhal_uart_operation_mode_t current_mode;

    struct nhal_uart_impl_ctx * impl_ctx;

    // Conditional extensions - only included if support is compiled in
#if defined(NHAL_UART_ASYNC_BUFFERED_SUPPORT)
    struct nhal_uart_async_buffered_extension {
        nhal_uart_tx_complete_cb_t tx_complete_cb;
        nhal_uart_rx_complete_cb_t rx_complete_cb;
        nhal_uart_error_cb_t error_cb;
        void * callback_context;
        uint8_t * tx_buffer;
        size_t tx_buffer_size;
        uint8_t * rx_buffer;
        size_t rx_buffer_size;
        size_t tx_bytes_queued;
        size_t rx_bytes_available;
        bool is_async_initialized;
    } async_buffered;
#endif
};

typedef void (*nhal_uart_tx_complete_cb_t)(void * ctxt);
typedef void (*nhal_uart_rx_complete_cb_t)(void * ctxt, uint8_t * data, size_t length);
typedef void (*nhal_uart_error_cb_t)(void * ctxt, nhal_result_t error);

/**
 * @brief Configuration for asynchronous operations with buffering
 */
struct nhal_uart_async_buffered_config{
    struct nhal_uart_config basic_config;           /**< Basic UART configuration */
    nhal_uart_tx_complete_cb_t tx_complete_cb;
    nhal_uart_rx_complete_cb_t rx_complete_cb;
    nhal_uart_error_cb_t error_cb;
    void * callback_context;
    uint8_t * tx_buffer;
    size_t tx_buffer_size;
    uint8_t * rx_buffer;
    size_t rx_buffer_size;
};

#endif /* NHAL_UART_TYPES_H */
