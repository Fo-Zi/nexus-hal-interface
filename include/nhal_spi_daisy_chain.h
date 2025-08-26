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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize SPI daisy chain context
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_init(struct nhal_spi_daisy_context * daisy_ctx);
/**
 * @brief Deinitialize SPI daisy chain context
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_deinit(struct nhal_spi_daisy_context * daisy_ctx);
/**
 * @brief Set SPI daisy chain configuration
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @param config Pointer to daisy chain configuration structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_set_config(struct nhal_spi_daisy_context * daisy_ctx, struct nhal_spi_daisy_config * config);
/**
 * @brief Get current SPI daisy chain configuration
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @param config Pointer to daisy chain configuration structure to fill
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_get_config(struct nhal_spi_daisy_context * daisy_ctx, struct nhal_spi_daisy_config * config);

/**
 * @brief Write data to daisy chain with per-device data specification
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @param devices Array of device structures containing data for each device
 * @param num_devices Number of devices in the chain
 * @param timeout Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_write_chain(
    struct nhal_spi_daisy_context * daisy_ctx,
    const struct nhal_spi_daisy_device * devices, size_t num_devices,
    nhal_timeout_ms timeout
);

/**
 * @brief Read data from daisy chain with per-device data specification
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @param devices Array of device structures to receive data from each device
 * @param num_devices Number of devices in the chain
 * @param timeout Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_read_chain(
    struct nhal_spi_daisy_context * daisy_ctx,
    struct nhal_spi_daisy_device * devices, size_t num_devices,
    nhal_timeout_ms timeout
);

/**
 * @brief Write uniform data to all devices in daisy chain
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @param data Pointer to data to write to each device
 * @param data_per_device Number of bytes to write to each device
 * @param timeout Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_write_uniform(
    struct nhal_spi_daisy_context * daisy_ctx,
    const uint8_t * data, size_t data_per_device,
    nhal_timeout_ms timeout
);

/**
 * @brief Read uniform data from all devices in daisy chain
 * @param daisy_ctx Pointer to SPI daisy chain context structure
 * @param data Pointer to buffer for received data from all devices
 * @param data_per_device Number of bytes to read from each device
 * @param timeout Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_daisy_read_uniform(
    struct nhal_spi_daisy_context * daisy_ctx,
    uint8_t * data, size_t data_per_device,
    nhal_timeout_ms timeout
);

#ifdef __cplusplus
}
#endif

#endif