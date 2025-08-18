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

// Callback types for asynchronous operations
typedef void (*nhal_spi_async_complete_cb_t)(void * ctx, nhal_result_t result);

// Only provide async API if support enabled in private implementation header
#if defined(NHAL_SPI_ASYNC_DMA_SUPPORT)

nhal_result_t nhal_spi_enable_async_mode(
    struct nhal_spi_context * spi_ctx,
    const struct nhal_spi_async_dma_config *async_cfg
);

nhal_result_t nhal_spi_disable_async_mode(
    struct nhal_spi_context * spi_ctx
);

nhal_result_t nhal_spi_write_async(
    struct nhal_spi_context * spi_ctx,
    const uint8_t * data, size_t len,
    nhal_timeout_ms timeout,
    nhal_spi_async_complete_cb_t callback,
    void * callback_ctx
);

nhal_result_t nhal_spi_read_async(
    struct nhal_spi_context * spi_ctx,
    uint8_t * data, size_t len,
    nhal_timeout_ms timeout,
    nhal_spi_async_complete_cb_t callback,
    void * callback_ctx
);

nhal_result_t nhal_spi_write_read_async(
    struct nhal_spi_context * spi_ctx,
    const uint8_t * tx_data, size_t tx_len,
    uint8_t * rx_data, size_t rx_len,
    nhal_timeout_ms timeout,
    nhal_spi_async_complete_cb_t callback,
    void * callback_ctx
);

#endif /* NHAL_SPI_ASYNC_DMA_SUPPORT */

#endif /* NHAL_SPI_MASTER_ASYNC_H */