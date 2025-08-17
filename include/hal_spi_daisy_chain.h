/**
 * @file hal_spi_daisy_chain.h
 * @brief Hardware Abstraction Layer for SPI daisy chain communication.
 *
 * This file defines the API for interacting with SPI devices connected in a daisy chain
 * configuration. In daisy chain mode, devices are connected MOSI->Device1_MISO->Device2_MISO->...
 * with a shared clock and chip select, forming a single large shift register.
 */
#ifndef HAL_SPI_DAISY_CHAIN_H
#define HAL_SPI_DAISY_CHAIN_H

#include <stdint.h>
#include <stddef.h>

#include "hal_common.h"
#include "hal_spi_types.h"

hal_spi_result_t hal_spi_daisy_init(struct hal_spi_daisy_context * daisy_ctx);
hal_spi_result_t hal_spi_daisy_deinit(struct hal_spi_daisy_context * daisy_ctx);
hal_spi_result_t hal_spi_daisy_set_config(struct hal_spi_daisy_context * daisy_ctx, struct hal_spi_daisy_config * config);
hal_spi_result_t hal_spi_daisy_get_config(struct hal_spi_daisy_context * daisy_ctx, struct hal_spi_daisy_config * config);

hal_spi_result_t hal_spi_daisy_write_chain(
    struct hal_spi_daisy_context * daisy_ctx,
    const struct hal_spi_daisy_device * devices, size_t num_devices,
    hal_timeout_ms timeout
);

hal_spi_result_t hal_spi_daisy_read_chain(
    struct hal_spi_daisy_context * daisy_ctx,
    struct hal_spi_daisy_device * devices, size_t num_devices,
    hal_timeout_ms timeout
);

hal_spi_result_t hal_spi_daisy_write_uniform(
    struct hal_spi_daisy_context * daisy_ctx,
    const uint8_t * data, size_t data_per_device,
    hal_timeout_ms timeout
);

hal_spi_result_t hal_spi_daisy_read_uniform(
    struct hal_spi_daisy_context * daisy_ctx,
    uint8_t * data, size_t data_per_device,
    hal_timeout_ms timeout
);

#endif