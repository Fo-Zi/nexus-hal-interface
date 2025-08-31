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

/**
 * @brief UART parity bit configuration
 */
typedef enum {
    NHAL_UART_PARITY_NONE,   /**< No parity bit is used. */
    NHAL_UART_PARITY_EVEN,   /**< Parity bit is set such that the total number of '1' bits is even. */
    NHAL_UART_PARITY_ODD,    /**< Parity bit is set such that the total number of '1' bits is odd. */
} nhal_uart_parity_t;

/**
 * @brief UART stop bits configuration
 */
typedef enum {
    NHAL_UART_STOP_BITS_1,       /**< 1 stop bit is used. */
    NHAL_UART_STOP_BITS_2,       /**< 2 stop bits are used. */
} nhal_uart_stop_bits_t;

/**
 * @brief UART data bits configuration
 */
typedef enum {
    NHAL_UART_DATA_BITS_7,       /**< 7 data bits are used. */
    NHAL_UART_DATA_BITS_8,       /**< 8 data bits are used. */
} nhal_uart_data_bits_t;

/**
 * @brief UART configuration structure
 */
struct nhal_uart_config{
    uint32_t baudrate;              /**< The baud rate for communication (bits per second). */
    nhal_uart_parity_t parity;       /**< The parity setting (none, even, or odd). */
    nhal_uart_stop_bits_t stop_bits; /**< The number of stop bits (e.g., 1 or 2). */
    nhal_uart_data_bits_t data_bits; /**< The number of data bits (e.g., 7 or 8). */
    struct nhal_uart_impl_config * impl_config;
};

/**
 * @brief UART context structure (implementation-defined)
 *
 * Contains platform-specific UART identification and runtime state.
 * Must include unique bus identification and any shared resources.
 *
 * @par Example content:
 * @code
 * struct nhal_uart_context {
 *     // Bus identification: UART index OR peripheral name OR base address
 *     uint8_t uart_id;
 *     // Shared resources: mutex for bus access, DMA handles, etc.
 *     mutex_t *bus_lock;
 * };
 * @endcode
 */
struct nhal_uart_context;

#endif /* NHAL_UART_TYPES_H */
