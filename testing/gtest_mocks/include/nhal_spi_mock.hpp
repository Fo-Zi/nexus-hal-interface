/**
 * @file nhal_spi_mock.hpp
 * @brief Google Mock implementation for SPI HAL interface
 */

#ifndef NHAL_SPI_MOCK_HPP
#define NHAL_SPI_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_spi_master.h"
#include "nhal_spi_master_async.h"
#include "nhal_spi_daisy_chain.h"

/**
 * @brief Mock class for SPI HAL interface
 */
class NhalSpiMock {
public:
    // Basic SPI master operations
    MOCK_METHOD(nhal_result_t, nhal_spi_master_init, (struct nhal_spi_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_deinit, (struct nhal_spi_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_set_config, (struct nhal_spi_context *ctx, struct nhal_spi_config *config));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_get_config, (struct nhal_spi_context *ctx, struct nhal_spi_config *config));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_write, (struct nhal_spi_context *ctx, const uint8_t *data, size_t len, nhal_timeout_ms timeout));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_read, (struct nhal_spi_context *ctx, uint8_t *data, size_t len, nhal_timeout_ms timeout));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_write_read, (struct nhal_spi_context *ctx, const uint8_t *tx_data, size_t tx_len, uint8_t *rx_data, size_t rx_len, nhal_timeout_ms timeout));

    // Async SPI master operations
    MOCK_METHOD(nhal_result_t, nhal_spi_master_init_async, (struct nhal_spi_context *ctx, const struct nhal_async_config *async_cfg));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_deinit_async, (struct nhal_spi_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_set_async_callback, (struct nhal_spi_context *ctx, nhal_async_complete_cb_t callback));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_disable_async_callback, (struct nhal_spi_context *ctx));
    MOCK_METHOD(nhal_async_status_t, nhal_spi_master_get_async_status, (struct nhal_spi_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_write_async, (struct nhal_spi_context *ctx, const uint8_t *data, size_t len, nhal_timeout_ms timeout_ms));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_read_async, (struct nhal_spi_context *ctx, uint8_t *data, size_t len, nhal_timeout_ms timeout_ms));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_write_read_async, (struct nhal_spi_context *ctx, const uint8_t *tx_data, size_t tx_len, uint8_t *rx_data, size_t rx_len, nhal_timeout_ms timeout_ms));

    // Daisy chain operations
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_init, (struct nhal_spi_daisy_context *daisy_ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_deinit, (struct nhal_spi_daisy_context *daisy_ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_set_config, (struct nhal_spi_daisy_context *daisy_ctx, struct nhal_spi_daisy_config *config));
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_get_config, (struct nhal_spi_daisy_context *daisy_ctx, struct nhal_spi_daisy_config *config));
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_write_chain, (struct nhal_spi_daisy_context *daisy_ctx, const struct nhal_spi_daisy_device *devices, size_t num_devices, nhal_timeout_ms timeout));
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_read_chain, (struct nhal_spi_daisy_context *daisy_ctx, struct nhal_spi_daisy_device *devices, size_t num_devices, nhal_timeout_ms timeout));
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_write_uniform, (struct nhal_spi_daisy_context *daisy_ctx, const uint8_t *data, size_t data_per_device, nhal_timeout_ms timeout));
    MOCK_METHOD(nhal_result_t, nhal_spi_daisy_read_uniform, (struct nhal_spi_daisy_context *daisy_ctx, uint8_t *data, size_t data_per_device, nhal_timeout_ms timeout));

    // Singleton instance for C interface
    static NhalSpiMock& instance() {
        static NhalSpiMock mock;
        return mock;
    }
};

#endif /* NHAL_SPI_MOCK_HPP */