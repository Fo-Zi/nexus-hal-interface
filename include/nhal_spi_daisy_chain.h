/**
 * @file nhal_spi_daisy_chain.h
 * @brief Hardware Abstraction Layer for SPI daisy chain communication.
 *
 * This file defines the API for interacting with SPI devices connected in a daisy chain
 * configuration. In daisy chain mode, devices are connected MOSI->Device1_MISO->Device2_MISO->...
 * with a shared clock and chip select, forming a single large shift register.
 */
#ifndef NHAL_SPI_DAISY_CHAIN_H
#define NHAL_SPI_DAISY_CHAIN_H

#include <stdint.h>
#include <stddef.h>

#include "nhal_common.h"
#include "nhal_spi_types.h"

nhal_result_t nhal_spi_daisy_init(struct nhal_spi_daisy_context * daisy_ctx);
nhal_result_t nhal_spi_daisy_deinit(struct nhal_spi_daisy_context * daisy_ctx);
nhal_result_t nhal_spi_daisy_set_config(struct nhal_spi_daisy_context * daisy_ctx, struct nhal_spi_daisy_config * config);
nhal_result_t nhal_spi_daisy_get_config(struct nhal_spi_daisy_context * daisy_ctx, struct nhal_spi_daisy_config * config);

nhal_result_t nhal_spi_daisy_write_chain(
    struct nhal_spi_daisy_context * daisy_ctx,
    const struct nhal_spi_daisy_device * devices, size_t num_devices,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_spi_daisy_read_chain(
    struct nhal_spi_daisy_context * daisy_ctx,
    struct nhal_spi_daisy_device * devices, size_t num_devices,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_spi_daisy_write_uniform(
    struct nhal_spi_daisy_context * daisy_ctx,
    const uint8_t * data, size_t data_per_device,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_spi_daisy_read_uniform(
    struct nhal_spi_daisy_context * daisy_ctx,
    uint8_t * data, size_t data_per_device,
    nhal_timeout_ms timeout
);

#endif