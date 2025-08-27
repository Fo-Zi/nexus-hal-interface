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

/**
 * @brief Base UART context - always present, minimal footprint
 */
struct nhal_uart_context{
    nhal_uart_bus_id uart_bus_id;

    struct nhal_uart_impl_ctx * impl_ctx;

    // Async extensions handled separately in async context
};

typedef void (*nhal_uart_tx_complete_cb_t)(void *context);
typedef void (*nhal_uart_rx_complete_cb_t)(void *context);
typedef void (*nhal_uart_error_cb_t)(void *context);


#endif /* NHAL_UART_TYPES_H */
