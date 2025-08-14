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

/**
 * @brief Enumeration for UART operation status codes.
 * These codes indicate the success or failure of a UART operation.
 */
typedef enum {
    HAL_UART_OK = 0,                /**< Operation completed successfully. */
    HAL_UART_ERR_TIMEOUT,           /**< Operation timed out before completion. */
    HAL_UART_ERR_INVALID_ARG,       /**< One or more arguments are invalid. */
    HAL_UART_ERR_NOT_INITIALIZED,   /**< UART peripheral has not been initialized. */
    HAL_UART_ERR_TX_BUFFER_FULL,    /**< Transmit buffer is full. */
    HAL_UART_ERR_RX_BUFFER_OVERFLOW,/**< Receive buffer overflowed. */
    HAL_UART_ERR_OTHER              /**< An unspecified error occurred. */
} hal_uart_result_t;

/**
 * @brief Enumeration for UART parity settings.
 * Specifies the type of parity checking to be used for data transmission.
 */
typedef enum {
    HAL_UART_PARITY_NONE,   /**< No parity bit is used. */
    HAL_UART_PARITY_EVEN,   /**< Parity bit is set such that the total number of '1' bits is even. */
    HAL_UART_PARITY_ODD,    /**< Parity bit is set such that the total number of '1' bits is odd. */
    HAL_UART_PARITY_NUM_TOTAL
} hal_uart_parity_t;

/**
 * @brief Enumeration for UART stop bits settings.
 * Specifies the number of stop bits to be used for data transmission.
 */
typedef enum {
    HAL_UART_STOP_BITS_1,       /**< 1 stop bit is used. */
    HAL_UART_STOP_BITS_2,       /**< 2 stop bits are used. */
    HAL_UART_STOP_BITS_NUM_TOTAL
} hal_uart_stop_bits_t;

/**
 * @brief Enumeration for UART data bits settings.
 * Specifies the number of data bits to be used for data transmission.
 */
typedef enum {
    HAL_UART_DATA_BITS_7,       /**< 7 data bits are used. */
    HAL_UART_DATA_BITS_8,       /**< 8 data bits are used. */
    HAL_UART_DATA_BITS_NUM_TOTAL
} hal_uart_data_bits_t;

/**
 * @brief Structure for common UART configuration parameters.
 * Defines standard configuration settings applicable to most UART implementations.
 */
typedef struct {
    uint32_t baudrate;              /**< The baud rate for communication (bits per second). */
    hal_uart_parity_t parity;       /**< The parity setting (none, even, or odd). */
    hal_uart_stop_bits_t stop_bits; /**< The number of stop bits (e.g., 1 or 2). */
    hal_uart_data_bits_t data_bits; /**< The number of data bits (e.g., 7 or 8). */
} hal_uart_basic_config_t;

struct hal_uart_context;
typedef struct hal_uart_context hal_uart_context_t;


// Buffering configuration - for implementations with buffered ops only
#ifdef HAL_UART_BUFFERED
    typedef struct {
        uint8_t* tx_buffer;     /**< Pointer to the transmit buffer. */
        size_t tx_buffer_size;  /**< Size of the transmit buffer in bytes. */
        uint8_t* rx_buffer;     /**< Pointer to the receive buffer. */
        size_t rx_buffer_size;  /**< Size of the receive buffer in bytes. */
    } hal_uart_buffered_config_t;
#endif

// Async configuration - for implementations with async ops only
#ifdef HAL_UART_ASYNC
    typedef void (*uart_tx_complete_cb_t)(uart_handle_t* handle, void* context);
    typedef void (*uart_rx_complete_cb_t)(uart_handle_t* handle, void* context,
    typedef void (*uart_error_cb_t)(uart_handle_t* handle, void* context,
    typedef struct {
        uart_tx_complete_cb_t tx_complete_cb;    /**< Callback function to be called upon transmit completion. */
        uart_rx_complete_cb_t rx_complete_cb;    /**< Callback function to be called upon receive completion. */
        uart_error_cb_t error_cb;              /**< Callback function to be called upon an error. */
        void* callback_context;                 /**< User-defined context pointer to be passed to the callbacks. */
    } hal_uart_async_config_t;
#endif // HAL_UART_ASYNC

/**
 * @brief Structure for complete UART configuration.
 * Combines common configuration parameters with a pointer to implementation-specific settings.
 */
typedef struct {

    hal_uart_basic_config_t basic_config;    /**< Basic UART configuration parameters. */

    #ifdef HAL_UART_ASYNC
        hal_uart_async_config_t async_config;
    #endif

    #ifdef HAL_UART_BUFFERED
        hal_uart_buffered_config_t buffered_config;
    #endif

    void * impl_specific_config;            /**< Pointer to an opaque structure for implementation-specific configuration.
                                                     The specific type of this pointer will depend on the HAL implementation. */

} hal_uart_config_t;


#endif /* HAL_UART_TYPES_H */
