/**
 * @file nhal_spi_mock.hpp
 * @brief Google Mock implementation for SPI HAL interface
 */

#ifndef NHAL_SPI_MOCK_HPP
#define NHAL_SPI_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_spi_master.h"

/**
 * @brief Mock class for SPI HAL interface
 */
class NhalSpiMock {
public:
    // SPI master operations
    MOCK_METHOD(nhal_result_t, nhal_spi_master_init, (struct nhal_spi_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_deinit, (struct nhal_spi_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_set_config, (struct nhal_spi_context *ctx, struct nhal_spi_config *config));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_get_config, (struct nhal_spi_context *ctx, struct nhal_spi_config *config));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_write, (struct nhal_spi_context *ctx, const uint8_t *data, size_t len));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_read, (struct nhal_spi_context *ctx, uint8_t *data, size_t len));
    MOCK_METHOD(nhal_result_t, nhal_spi_master_write_read, (struct nhal_spi_context *ctx, const uint8_t *tx_data, size_t tx_len, uint8_t *rx_data, size_t rx_len));

    // Singleton instance for C interface
    static NhalSpiMock& instance() {
        static NhalSpiMock mock;
        return mock;
    }
};

#endif /* NHAL_SPI_MOCK_HPP */