/**
 * @file nhal_uart_mock.hpp
 * @brief Google Mock implementation for UART HAL interface
 */

#ifndef NHAL_UART_MOCK_HPP
#define NHAL_UART_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_uart.h"

/**
 * @brief Mock class for UART HAL interface
 */
class NhalUartMock {
public:
    // UART operations
    MOCK_METHOD(nhal_result_t, nhal_uart_init, (struct nhal_uart_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_uart_deinit, (struct nhal_uart_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_uart_set_config, (struct nhal_uart_context *ctx, struct nhal_uart_config *cfg));
    MOCK_METHOD(nhal_result_t, nhal_uart_get_config, (struct nhal_uart_context *ctx, struct nhal_uart_config *cfg));
    MOCK_METHOD(nhal_result_t, nhal_uart_write, (struct nhal_uart_context *ctx, const uint8_t *data, size_t len));
    MOCK_METHOD(nhal_result_t, nhal_uart_read, (struct nhal_uart_context *ctx, uint8_t *data, size_t len));

    // Singleton instance for C interface
    static NhalUartMock& instance() {
        static NhalUartMock mock;
        return mock;
    }
};

#endif /* NHAL_UART_MOCK_HPP */