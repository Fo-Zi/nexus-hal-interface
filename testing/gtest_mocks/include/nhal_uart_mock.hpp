/**
 * @file nhal_uart_mock.hpp
 * @brief Google Mock implementation for UART HAL interface
 */

#ifndef NHAL_UART_MOCK_HPP
#define NHAL_UART_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_uart_basic.h"
#include "nhal_uart_async.h"

/**
 * @brief Mock class for UART HAL interface
 */
class NhalUartMock {
public:
    // Basic UART operations
    MOCK_METHOD(nhal_result_t, nhal_uart_init, (struct nhal_uart_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_uart_deinit, (struct nhal_uart_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_uart_set_config, (struct nhal_uart_context *ctx, struct nhal_uart_config *cfg));
    MOCK_METHOD(nhal_result_t, nhal_uart_get_config, (struct nhal_uart_context *ctx, struct nhal_uart_config *cfg));
    MOCK_METHOD(nhal_result_t, nhal_uart_write, (struct nhal_uart_context *ctx, const uint8_t *data, size_t len));
    MOCK_METHOD(nhal_result_t, nhal_uart_read, (struct nhal_uart_context *ctx, uint8_t *data, size_t len));

    // Async UART operations
    MOCK_METHOD(nhal_result_t, nhal_uart_init_async, (struct nhal_uart_context *ctx, const struct nhal_async_config *async_cfg));
    MOCK_METHOD(nhal_result_t, nhal_uart_deinit_async, (struct nhal_uart_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_uart_set_async_callback, (struct nhal_uart_context *ctx, nhal_async_complete_cb_t callback));
    MOCK_METHOD(nhal_result_t, nhal_uart_disable_async_callback, (struct nhal_uart_context *ctx));
    MOCK_METHOD(nhal_async_status_t, nhal_uart_get_async_status, (struct nhal_uart_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_uart_write_async, (struct nhal_uart_context *ctx, const uint8_t *data, size_t len));
    MOCK_METHOD(nhal_result_t, nhal_uart_read_async, (struct nhal_uart_context *ctx, uint8_t *data, size_t len, size_t *bytes_read));

    // Singleton instance for C interface
    static NhalUartMock& instance() {
        static NhalUartMock mock;
        return mock;
    }
};

#endif /* NHAL_UART_MOCK_HPP */