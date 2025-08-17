/**
 * @file hal_spi_master.h
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
 * @note For non-blocking asynchronous operations, see hal_spi_master_async.h
 */
#ifndef HAL_SPI_MASTER_H
#define HAL_SPI_MASTER_H

#include <stdint.h>
#include <stddef.h>

#include "hal_common.h"
#include "hal_spi_types.h"

hal_spi_result_t hal_spi_master_init(struct hal_spi_context * spi_ctx);
hal_spi_result_t hal_spi_master_deinit(struct hal_spi_context * spi_ctx);
hal_spi_result_t hal_spi_master_set_config(struct hal_spi_context * spi_ctx, struct hal_spi_config * config);
hal_spi_result_t hal_spi_master_get_config(struct hal_spi_context * spi_ctx, struct hal_spi_config * config);

hal_spi_result_t hal_spi_master_write(
    struct hal_spi_context * spi_ctx,
    const uint8_t * data, size_t len,
    hal_timeout_ms timeout
);

hal_spi_result_t hal_spi_master_read(
    struct hal_spi_context * spi_ctx,
    uint8_t * data, size_t len,
    hal_timeout_ms timeout
);

hal_spi_result_t hal_spi_master_write_read(
    struct hal_spi_context * spi_ctx,
    const uint8_t * tx_data, size_t tx_len,
    uint8_t * rx_data, size_t rx_len,
    hal_timeout_ms timeout
);

#endif