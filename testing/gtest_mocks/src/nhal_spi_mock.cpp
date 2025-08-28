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

    // SPI Master Async interface implementations
    nhal_result_t nhal_spi_master_init_async(struct nhal_spi_context *ctx, const struct nhal_async_config *async_cfg) {
        return NhalSpiMock::instance().nhal_spi_master_init_async(ctx, async_cfg);
    }

    nhal_result_t nhal_spi_master_deinit_async(struct nhal_spi_context *ctx) {
        return NhalSpiMock::instance().nhal_spi_master_deinit_async(ctx);
    }

    nhal_result_t nhal_spi_master_set_async_callback(struct nhal_spi_context *ctx, nhal_async_complete_cb_t callback) {
        return NhalSpiMock::instance().nhal_spi_master_set_async_callback(ctx, callback);
    }

    nhal_result_t nhal_spi_master_disable_async_callback(struct nhal_spi_context *ctx) {
        return NhalSpiMock::instance().nhal_spi_master_disable_async_callback(ctx);
    }

    nhal_async_status_t nhal_spi_master_get_async_status(struct nhal_spi_context *ctx) {
        return NhalSpiMock::instance().nhal_spi_master_get_async_status(ctx);
    }

    nhal_result_t nhal_spi_master_write_async(struct nhal_spi_context *ctx, const uint8_t *data, size_t len) {
        return NhalSpiMock::instance().nhal_spi_master_write_async(ctx, data, len);
    }

    nhal_result_t nhal_spi_master_read_async(struct nhal_spi_context *ctx, uint8_t *data, size_t len) {
        return NhalSpiMock::instance().nhal_spi_master_read_async(ctx, data, len);
    }

    nhal_result_t nhal_spi_master_write_read_async(struct nhal_spi_context *ctx, const uint8_t *tx_data, size_t tx_len, uint8_t *rx_data, size_t rx_len) {
        return NhalSpiMock::instance().nhal_spi_master_write_read_async(ctx, tx_data, tx_len, rx_data, rx_len);
    }

    // SPI Daisy Chain interface implementations
    nhal_result_t nhal_spi_daisy_init(struct nhal_spi_daisy_context *daisy_ctx) {
        return NhalSpiMock::instance().nhal_spi_daisy_init(daisy_ctx);
    }

    nhal_result_t nhal_spi_daisy_deinit(struct nhal_spi_daisy_context *daisy_ctx) {
        return NhalSpiMock::instance().nhal_spi_daisy_deinit(daisy_ctx);
    }

    nhal_result_t nhal_spi_daisy_set_config(struct nhal_spi_daisy_context *daisy_ctx, struct nhal_spi_daisy_config *config) {
        return NhalSpiMock::instance().nhal_spi_daisy_set_config(daisy_ctx, config);
    }

    nhal_result_t nhal_spi_daisy_get_config(struct nhal_spi_daisy_context *daisy_ctx, struct nhal_spi_daisy_config *config) {
        return NhalSpiMock::instance().nhal_spi_daisy_get_config(daisy_ctx, config);
    }

    nhal_result_t nhal_spi_daisy_write_chain(struct nhal_spi_daisy_context *daisy_ctx, const struct nhal_spi_daisy_device *devices, size_t num_devices) {
        return NhalSpiMock::instance().nhal_spi_daisy_write_chain(daisy_ctx, devices, num_devices);
    }

    nhal_result_t nhal_spi_daisy_read_chain(struct nhal_spi_daisy_context *daisy_ctx, struct nhal_spi_daisy_device *devices, size_t num_devices) {
        return NhalSpiMock::instance().nhal_spi_daisy_read_chain(daisy_ctx, devices, num_devices);
    }

    nhal_result_t nhal_spi_daisy_write_uniform(struct nhal_spi_daisy_context *daisy_ctx, const uint8_t *data, size_t data_per_device) {
        return NhalSpiMock::instance().nhal_spi_daisy_write_uniform(daisy_ctx, data, data_per_device);
    }

    nhal_result_t nhal_spi_daisy_read_uniform(struct nhal_spi_daisy_context *daisy_ctx, uint8_t *data, size_t data_per_device) {
        return NhalSpiMock::instance().nhal_spi_daisy_read_uniform(daisy_ctx, data, data_per_device);
    }
}