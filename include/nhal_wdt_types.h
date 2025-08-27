/**
 * @file nhal_wdt_types.h
 * @brief Defines common types and structures for the Watchdog Timer Hardware Abstraction Layer (HAL).
 *
 * This header file provides opaque types, enumerations, and structures used across
 * the Watchdog Timer HAL API to facilitate watchdog timer management and monitoring.
 */
#ifndef NHAL_WDT_TYPES_H
#define NHAL_WDT_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "nhal_common.h"

typedef uint8_t nhal_wdt_id;


/**
 * @brief Callback function type for watchdog events
 * @param ctxt User context pointer
 */
typedef void (*nhal_wdt_callback_t)(void *context);

struct nhal_wdt_config {
    uint32_t timeout_ms;                        /**< Timeout period in milliseconds */
    struct nhal_wdt_impl_config * impl_config;  /**< Platform-specific configuration */
};

/**
 * @brief Base watchdog context - always present, minimal footprint
 */
struct nhal_wdt_context {
    nhal_wdt_id wdt_id;
    uint32_t timeout_ms;        /**< Cached timeout from last set_config call */
    bool is_started;
    
    struct nhal_wdt_impl_ctx * impl_ctx;
};

#endif /* NHAL_WDT_TYPES_H */