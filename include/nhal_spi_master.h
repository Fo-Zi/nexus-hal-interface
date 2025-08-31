/**
 * @file nhal_spi_master.h
 * @brief Hardware Abstraction Layer for synchronous SPI Master mode communication.
 *
 * This file defines the API for interacting with an SPI bus in master mode.
 * It provides functions for initialization, configuration,
 * reading, writing, and combined operations using synchronous blocking transfers.
 *
 * Synchronous mode provides blocking operations with automatic transfer optimization.
 * The HAL automatically selects the best transfer method (CPU vs DMA) based on
 * transfer size and hardware capabilities - applications don't need to know.
 * All operations block until completion or timeout.
 *
 * @note For non-blocking asynchronous operations, see nhal_spi_master_async.h
 */
#ifndef NHAL_SPI_MASTER_H
#define NHAL_SPI_MASTER_H

#include <stdint.h>
#include <stddef.h>

#include "nhal_common.h"
#include "nhal_spi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize SPI master context
 * @param ctx Pointer to SPI context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_init(struct nhal_spi_context * ctx);

/**
 * @brief Deinitialize SPI master context
 * @param ctx Pointer to SPI context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_deinit(struct nhal_spi_context * ctx);

/**
 * @brief Set SPI master configuration
 * @param ctx Pointer to SPI context structure
 * @param config Pointer to configuration structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_set_config(struct nhal_spi_context * ctx, struct nhal_spi_config * config);

/**
 * @brief Get current SPI master configuration
 * @param ctx Pointer to SPI context structure
 * @param config Pointer to configuration structure to fill
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_get_config(struct nhal_spi_context * ctx, struct nhal_spi_config * config);

/**
 * @brief Write data to SPI device (blocking)
 * @param ctx Pointer to SPI context structure
 * @param data Pointer to data to transmit
 * @param len Number of bytes to transmit
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_write(
    struct nhal_spi_context * ctx,
    const uint8_t * data, size_t len
);

/**
 * @brief Read data from SPI device (blocking)
 * @param ctx Pointer to SPI context structure
 * @param data Pointer to buffer for received data
 * @param len Number of bytes to read
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_read(
    struct nhal_spi_context * ctx,
    uint8_t * data, size_t len
);

/**
 * @brief Simultaneous write and read on SPI device (blocking)
 * @param ctx Pointer to SPI context structure
 * @param tx_data Pointer to data to transmit
 * @param tx_len Number of bytes to transmit
 * @param rx_data Pointer to buffer for received data
 * @param rx_len Number of bytes to read
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_write_read(
    struct nhal_spi_context * ctx,
    const uint8_t * tx_data, size_t tx_len,
    uint8_t * rx_data, size_t rx_len
);

#ifdef __cplusplus
}
#endif

#endif