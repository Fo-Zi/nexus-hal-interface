/**
 * @file hal_uart_types.h
 * @brief Defines common data types, enumerations, and structures for UART HAL operations.
 *
 * This header provides the necessary type definitions used across the Universal Asynchronous
 * Receiver-Transmitter (UART) Hardware Abstraction Layer (HAL). It includes definitions
 * for UART identifiers, operation status codes, parity settings, and structures for
 * common and complete UART configurations, as well as the UART context/handle.
 * These types aim to provide a consistent interface for various UART implementations.
 */

#ifndef HAL_UART_TYPES_H
#define HAL_UART_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include "hal_common.h"

typedef uint8_t hal_uart_bus_id;

typedef enum {
    HAL_UART_OK = 0,                /**< Operation completed successfully. */
    HAL_UART_ERR_TIMEOUT,           /**< Operation timed out before completion. */
    HAL_UART_ERR_INVALID_ARG,       /**< One or more arguments are invalid. */
    HAL_UART_ERR_NOT_INITIALIZED,   /**< UART peripheral has not been initialized. */
    HAL_UART_ERR_TX_BUFFER_FULL,    /**< Transmit buffer is full. */
    HAL_UART_ERR_RX_BUFFER_OVERFLOW,/**< Receive buffer overflowed. */
    HAL_UART_ERR_HW_FAILURE,        /**< Hardware failure occurred. */
    HAL_UART_ERR_OTHER              /**< An unspecified error occurred. */
} hal_uart_result_t;

typedef enum {
    HAL_UART_PARITY_NONE,   /**< No parity bit is used. */
    HAL_UART_PARITY_EVEN,   /**< Parity bit is set such that the total number of '1' bits is even. */
    HAL_UART_PARITY_ODD,    /**< Parity bit is set such that the total number of '1' bits is odd. */
} hal_uart_parity_t;

typedef enum {
    HAL_UART_STOP_BITS_1,       /**< 1 stop bit is used. */
    HAL_UART_STOP_BITS_2,       /**< 2 stop bits are used. */
} hal_uart_stop_bits_t;

typedef enum {
    HAL_UART_DATA_BITS_7,       /**< 7 data bits are used. */
    HAL_UART_DATA_BITS_8,       /**< 8 data bits are used. */
} hal_uart_data_bits_t;

struct hal_uart_config{
    hal_uart_bus_id uart_bus_id;
    uint32_t baudrate;              /**< The baud rate for communication (bits per second). */
    hal_uart_parity_t parity;       /**< The parity setting (none, even, or odd). */
    hal_uart_stop_bits_t stop_bits; /**< The number of stop bits (e.g., 1 or 2). */
    hal_uart_data_bits_t data_bits; /**< The number of data bits (e.g., 7 or 8). */
    struct hal_uart_impl_config * impl_config;
};

typedef enum {
    HAL_UART_OP_MODE_SYNC_ONLY,        /**< Synchronous blocking operations only. */
    HAL_UART_OP_MODE_SYNC_AND_ASYNC    /**< Both synchronous and asynchronous operations. */
} hal_uart_operation_mode_t;

/**
 * @brief Base UART context - always present, minimal footprint
 */
struct hal_uart_context{
    hal_uart_bus_id uart_bus_id;
    hal_uart_operation_mode_t current_mode;

    struct hal_uart_impl_ctx * impl_ctx;

    // Conditional extensions - only included if support is compiled in
#if defined(HAL_UART_ASYNC_BUFFERED_SUPPORT)
    struct hal_uart_async_buffered_extension {
        hal_uart_tx_complete_cb_t tx_complete_cb;
        hal_uart_rx_complete_cb_t rx_complete_cb;
        hal_uart_error_cb_t error_cb;
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

typedef void (*hal_uart_tx_complete_cb_t)(void * ctxt);
typedef void (*hal_uart_rx_complete_cb_t)(void * ctxt, uint8_t * data, size_t length);
typedef void (*hal_uart_error_cb_t)(void * ctxt, hal_uart_result_t error);

/**
 * @brief Configuration for asynchronous operations with buffering
 */
struct hal_uart_async_buffered_config{
    struct hal_uart_config basic_config;           /**< Basic UART configuration */
    hal_uart_tx_complete_cb_t tx_complete_cb;
    hal_uart_rx_complete_cb_t rx_complete_cb;
    hal_uart_error_cb_t error_cb;
    void * callback_context;
    uint8_t * tx_buffer;
    size_t tx_buffer_size;
    uint8_t * rx_buffer;
    size_t rx_buffer_size;
};

#endif /* HAL_UART_TYPES_H */
