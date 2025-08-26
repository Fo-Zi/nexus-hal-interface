/**
 * @file nhal_uart_mock.cpp
 * @brief C interface bridge for UART mock
 */

#include "nhal_uart_mock.hpp"

// UART Basic interface implementations
extern "C" {
    nhal_result_t nhal_uart_init(struct nhal_uart_context *ctx) {
        return NhalUartMock::instance().nhal_uart_init(ctx);
    }

    nhal_result_t nhal_uart_deinit(struct nhal_uart_context *ctx) {
        return NhalUartMock::instance().nhal_uart_deinit(ctx);
    }

    nhal_result_t nhal_uart_set_config(struct nhal_uart_context *ctx, struct nhal_uart_config *cfg) {
        return NhalUartMock::instance().nhal_uart_set_config(ctx, cfg);
    }

    nhal_result_t nhal_uart_get_config(struct nhal_uart_context *ctx, struct nhal_uart_config *cfg) {
        return NhalUartMock::instance().nhal_uart_get_config(ctx, cfg);
    }

    nhal_result_t nhal_uart_write(struct nhal_uart_context *ctx, const uint8_t *data, size_t len, nhal_timeout_ms timeout) {
        return NhalUartMock::instance().nhal_uart_write(ctx, data, len, timeout);
    }

    nhal_result_t nhal_uart_read(struct nhal_uart_context *ctx, uint8_t *data, size_t len, nhal_timeout_ms timeout) {
        return NhalUartMock::instance().nhal_uart_read(ctx, data, len, timeout);
    }

    // UART Async interface implementations
    nhal_result_t nhal_uart_init_async(struct nhal_uart_context *ctx, const struct nhal_async_config *async_cfg) {
        return NhalUartMock::instance().nhal_uart_init_async(ctx, async_cfg);
    }

    nhal_result_t nhal_uart_deinit_async(struct nhal_uart_context *ctx) {
        return NhalUartMock::instance().nhal_uart_deinit_async(ctx);
    }

    nhal_result_t nhal_uart_set_async_callback(struct nhal_uart_context *ctx, nhal_async_complete_cb_t callback) {
        return NhalUartMock::instance().nhal_uart_set_async_callback(ctx, callback);
    }

    nhal_result_t nhal_uart_disable_async_callback(struct nhal_uart_context *ctx) {
        return NhalUartMock::instance().nhal_uart_disable_async_callback(ctx);
    }

    nhal_async_status_t nhal_uart_get_async_status(struct nhal_uart_context *ctx) {
        return NhalUartMock::instance().nhal_uart_get_async_status(ctx);
    }

    nhal_result_t nhal_uart_write_async(struct nhal_uart_context *ctx, const uint8_t *data, size_t len, nhal_timeout_ms timeout_ms) {
        return NhalUartMock::instance().nhal_uart_write_async(ctx, data, len, timeout_ms);
    }

    nhal_result_t nhal_uart_read_async(struct nhal_uart_context *ctx, uint8_t *data, size_t len, nhal_timeout_ms timeout_ms) {
        return NhalUartMock::instance().nhal_uart_read_async(ctx, data, len, timeout_ms);
    }
}