#ifndef NHAL_COMMON_H
#define NHAL_COMMON_H

#include <stdint.h>

typedef uint16_t nhal_timeout_ms;

typedef enum {
    NHAL_ASYNC_STATUS_IDLE,      /**< No async operation in progress */
    NHAL_ASYNC_STATUS_BUSY,      /**< Async operation in progress */
    NHAL_ASYNC_STATUS_COMPLETE,  /**< Operation completed successfully */
    NHAL_ASYNC_STATUS_ERROR      /**< Operation completed with error */
} nhal_async_status_t;

struct nhal_async_config {
    struct nhal_async_impl_config * impl_config;  /**< Platform-specific async config */
};

/**
 * @brief Unified HAL result type for all peripheral operations
 */
typedef enum {
    NHAL_OK = 0,                         /**< Operation completed successfully. */
    
    // Common argument/validation errors  
    NHAL_ERR_INVALID_ARG,                /**< Invalid arguments provided. */
    NHAL_ERR_INVALID_CONFIG,             /**< Invalid configuration. */
    NHAL_ERR_NOT_INITIALIZED,            /**< Peripheral not initialized. */
    NHAL_ERR_ALREADY_INITIALIZED,        /**< Already initialized. */
    NHAL_ERR_NOT_CONFIGURED,             /**< Peripheral not configured. */
    
    // State errors
    NHAL_ERR_NOT_STARTED,                /**< Operation not started. */
    NHAL_ERR_ALREADY_STARTED,            /**< Already started/running. */
    NHAL_ERR_BUSY,                       /**< Resource busy/locked/unavailable. */
    
    // Operation errors
    NHAL_ERR_TIMEOUT,                    /**< Operation timeout. */
    NHAL_ERR_HW_FAILURE,                 /**< Hardware failure. */
    NHAL_ERR_UNSUPPORTED,                /**< Feature not supported. */
    
    // Communication errors (generic)
    NHAL_ERR_NO_RESPONSE,                /**< No response from target (NACK, etc.). */
    NHAL_ERR_TRANSMISSION_ERROR,         /**< General transmission error. */
    
    // Buffer/resource errors
    NHAL_ERR_BUFFER_FULL,                /**< Buffer full. */
    NHAL_ERR_BUFFER_OVERFLOW,            /**< Buffer overflow. */
    NHAL_ERR_OUT_OF_MEMORY,              /**< Memory allocation failed. */
    
    // Catch-all
    NHAL_ERR_OTHER                       /**< Unspecified error. */
} nhal_result_t;

// Common async operation types
typedef void (*nhal_async_complete_cb_t)(void *context);

/**
 * @brief Blocking delay for specified number of microseconds
 *
 * This function performs a busy-wait delay, blocking the calling thread
 * for the specified duration. Should be used for precise timing requirements
 * where scheduler-based delays are insufficient.
 *
 * @param microseconds Number of microseconds to delay
 */
void nhal_delay_microseconds(uint32_t microseconds);

/**
 * @brief Blocking delay for specified number of milliseconds
 *
 * This function performs a busy-wait delay, blocking the calling thread
 * for the specified duration. Should be used for precise timing requirements
 * where scheduler-based delays are insufficient.
 *
 * @param milliseconds Number of milliseconds to delay
 */
void nhal_delay_milliseconds(uint32_t milliseconds);

/**
 * @brief Get monotonic timestamp in microseconds since boot
 *
 * This function returns a monotonic timestamp suitable for measuring
 * time intervals with microsecond precision. The timestamp resets on
 * system boot and may rollover after ~4294 seconds on 32-bit systems.
 * Unsigned arithmetic automatically handles rollover correctly for
 * interval calculations.
 *
 * @return Monotonic timestamp in microseconds
 */
uint64_t nhal_get_timestamp_microseconds(void);

/**
 * @brief Get monotonic timestamp in milliseconds since boot
 *
 * This function returns a monotonic timestamp suitable for measuring
 * time intervals with millisecond precision. The timestamp resets on
 * system boot and may rollover after ~49 days on 32-bit systems.
 * Unsigned arithmetic automatically handles rollover correctly for
 * interval calculations.
 *
 * @return Monotonic timestamp in milliseconds
 */
uint32_t nhal_get_timestamp_milliseconds(void);

#endif
