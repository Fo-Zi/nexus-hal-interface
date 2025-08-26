/**
 * @file nhal_wdt_mock.cpp
 * @brief C interface bridge for Watchdog Timer mock
 */

#include "nhal_wdt_mock.hpp"

extern "C" {
    nhal_result_t nhal_wdt_init(struct nhal_wdt_context *ctx) {
        return NhalWdtMock::instance().nhal_wdt_init(ctx);
    }

    nhal_result_t nhal_wdt_deinit(struct nhal_wdt_context *ctx) {
        return NhalWdtMock::instance().nhal_wdt_deinit(ctx);
    }

    nhal_result_t nhal_wdt_set_config(struct nhal_wdt_context *ctx, struct nhal_wdt_config *config) {
        return NhalWdtMock::instance().nhal_wdt_set_config(ctx, config);
    }

    nhal_result_t nhal_wdt_get_config(struct nhal_wdt_context *ctx, struct nhal_wdt_config *config) {
        return NhalWdtMock::instance().nhal_wdt_get_config(ctx, config);
    }

    nhal_result_t nhal_wdt_enable(struct nhal_wdt_context *ctx) {
        return NhalWdtMock::instance().nhal_wdt_enable(ctx);
    }

    nhal_result_t nhal_wdt_disable(struct nhal_wdt_context *ctx) {
        return NhalWdtMock::instance().nhal_wdt_disable(ctx);
    }

    nhal_result_t nhal_wdt_feed(struct nhal_wdt_context *ctx) {
        return NhalWdtMock::instance().nhal_wdt_feed(ctx);
    }
}