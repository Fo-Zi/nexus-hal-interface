/**
 * @file nhal_uart_mock.cpp
 * @brief C interface bridge for UART mock
 */

#include "nhal_uart_mock.hpp"

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

    nhal_result_t nhal_uart_write(struct nhal_uart_context *ctx, const uint8_t *data, size_t len) {
        return NhalUartMock::instance().nhal_uart_write(ctx, data, len);
    }

    nhal_result_t nhal_uart_read(struct nhal_uart_context *ctx, uint8_t *data, size_t len) {
        return NhalUartMock::instance().nhal_uart_read(ctx, data, len);
    }
}
