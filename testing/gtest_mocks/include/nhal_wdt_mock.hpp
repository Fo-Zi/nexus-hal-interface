/**
 * @file nhal_wdt_mock.hpp
 * @brief Google Mock implementation for Watchdog Timer HAL interface
 */

#ifndef NHAL_WDT_MOCK_HPP
#define NHAL_WDT_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_wdt.h"

/**
 * @brief Mock class for Watchdog Timer HAL interface
 */
class NhalWdtMock {
public:
    // Watchdog timer operations
    MOCK_METHOD(nhal_result_t, nhal_wdt_init, (struct nhal_wdt_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_wdt_deinit, (struct nhal_wdt_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_wdt_set_config, (struct nhal_wdt_context *ctx, struct nhal_wdt_config *config));
    MOCK_METHOD(nhal_result_t, nhal_wdt_get_config, (struct nhal_wdt_context *ctx, struct nhal_wdt_config *config));
    MOCK_METHOD(nhal_result_t, nhal_wdt_enable, (struct nhal_wdt_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_wdt_disable, (struct nhal_wdt_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_wdt_feed, (struct nhal_wdt_context *ctx));

    // Singleton instance for C interface
    static NhalWdtMock& instance() {
        static NhalWdtMock mock;
        return mock;
    }
};

#endif /* NHAL_WDT_MOCK_HPP */