/**
 * @file nhal_spi_mock.cpp
 * @brief C interface bridge for SPI mock
 */

#include "nhal_spi_mock.hpp"

extern "C" {
    // SPI Master interface implementations
    nhal_result_t nhal_spi_master_init(struct nhal_spi_context *ctx) {
        return NhalSpiMock::instance().nhal_spi_master_init(ctx);
    }

    nhal_result_t nhal_spi_master_deinit(struct nhal_spi_context *ctx) {
        return NhalSpiMock::instance().nhal_spi_master_deinit(ctx);
    }

    nhal_result_t nhal_spi_master_set_config(struct nhal_spi_context *ctx, struct nhal_spi_config *config) {
        return NhalSpiMock::instance().nhal_spi_master_set_config(ctx, config);
    }

    nhal_result_t nhal_spi_master_get_config(struct nhal_spi_context *ctx, struct nhal_spi_config *config) {
        return NhalSpiMock::instance().nhal_spi_master_get_config(ctx, config);
    }

    nhal_result_t nhal_spi_master_write(struct nhal_spi_context *ctx, const uint8_t *data, size_t len) {
        return NhalSpiMock::instance().nhal_spi_master_write(ctx, data, len);
    }

    nhal_result_t nhal_spi_master_read(struct nhal_spi_context *ctx, uint8_t *data, size_t len) {
        return NhalSpiMock::instance().nhal_spi_master_read(ctx, data, len);
    }

    nhal_result_t nhal_spi_master_write_read(struct nhal_spi_context *ctx, const uint8_t *tx_data, size_t tx_len, uint8_t *rx_data, size_t rx_len) {
        return NhalSpiMock::instance().nhal_spi_master_write_read(ctx, tx_data, tx_len, rx_data, rx_len);
    }
}
