/**
 * @file nhal_spi_master_async.h
 * @brief Hardware Abstraction Layer (HAL) for asynchronous SPI Master communication.
 *
 * This header defines the public interface for asynchronous SPI Master operations using DMA.
 * It provides functions for enabling async mode and performing
 * non-blocking read/write operations with automatic DMA optimization.
 *
 * Async mode provides non-blocking data transfers with callback completion.
 * This mode requires NHAL_SPI_ASYNC_DMA_SUPPORT to be defined at compile time.
 *
 * @note This header requires nhal_spi_master.h to be included first for base functionality
 */

#ifndef NHAL_SPI_MASTER_ASYNC_H
#define NHAL_SPI_MASTER_ASYNC_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"
#include "nhal_spi_types.h"

#if defined(NHAL_SPI_ASYNC_SUPPORT)

nhal_result_t nhal_spi_master_init_async(
    struct nhal_spi_context * ctx,
    const struct nhal_async_config * async_cfg
);

nhal_result_t nhal_spi_master_deinit_async(
    struct nhal_spi_context * ctx
);

nhal_result_t nhal_spi_master_set_async_callback(
    struct nhal_spi_context *ctx,
    nhal_async_complete_cb_t callback
);

nhal_result_t nhal_spi_master_disable_async_callback(
    struct nhal_spi_context *ctx
);

nhal_async_status_t nhal_spi_master_get_async_status(
    struct nhal_spi_context *ctx
);

nhal_result_t nhal_spi_write_async(
    struct nhal_spi_context * ctx,
    const uint8_t * data, size_t len,
    nhal_timeout_ms timeout_ms
);

nhal_result_t nhal_spi_read_async(
    struct nhal_spi_context * ctx,
    uint8_t * data, size_t len,
    nhal_timeout_ms timeout_ms
);

nhal_result_t nhal_spi_write_read_async(
    struct nhal_spi_context * ctx,
    const uint8_t * tx_data, size_t tx_len,
    uint8_t * rx_data, size_t rx_len,
    nhal_timeout_ms timeout_ms
);

#endif /* NHAL_SPI_ASYNC_SUPPORT */

#endif /* NHAL_SPI_MASTER_ASYNC_H */
