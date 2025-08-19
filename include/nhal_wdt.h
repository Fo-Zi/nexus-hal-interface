/**
 * @file nhal_wdt.h
 * @brief Hardware Abstraction Layer for Watchdog Timer management.
 *
 * This file defines the API for interacting with watchdog timers.
 * It provides functions for initialization, configuration,
 * feeding, and control operations.
 *
 * The watchdog timer provides system reliability by automatically
 * resetting the system if it is not periodically serviced within
 * the configured timeout period.
 */
#ifndef NHAL_WDT_H
#define NHAL_WDT_H

#include <stdint.h>
#include <stddef.h>

#include "nhal_common.h"
#include "nhal_wdt_types.h"

/**
 * @brief Initialize watchdog context
 * @param wdt_ctx Pointer to watchdog context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_wdt_init(struct nhal_wdt_context * wdt_ctx);

/**
 * @brief Deinitialize watchdog context
 * @param wdt_ctx Pointer to watchdog context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_wdt_deinit(struct nhal_wdt_context * wdt_ctx);

/**
 * @brief Set watchdog configuration
 * @param wdt_ctx Pointer to watchdog context structure
 * @param config Pointer to configuration structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_wdt_set_config(struct nhal_wdt_context * wdt_ctx, struct nhal_wdt_config * config);

/**
 * @brief Get current watchdog configuration
 * @param wdt_ctx Pointer to watchdog context structure
 * @param config Pointer to configuration structure to fill
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_wdt_get_config(struct nhal_wdt_context * wdt_ctx, struct nhal_wdt_config * config);

/**
 * @brief Start/Enable the watchdog timer
 * @param wdt_ctx Pointer to watchdog context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_wdt_enable(struct nhal_wdt_context * wdt_ctx);

/**
 * @brief Stop/Disable the watchdog timer (if supported)
 * @param wdt_ctx Pointer to watchdog context structure
 * @return NHAL_OK on success, NHAL_ERR_UNSUPPORTED if not supported
 */
nhal_result_t nhal_wdt_disable(struct nhal_wdt_context * wdt_ctx);

/**
 * @brief Feed/Reset the watchdog timer
 * @param wdt_ctx Pointer to watchdog context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_wdt_feed(struct nhal_wdt_context * wdt_ctx);

#endif /* NHAL_WDT_H */