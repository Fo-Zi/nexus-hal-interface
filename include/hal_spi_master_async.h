/**
 * @file hal_spi_master_async.h
 * @brief Hardware Abstraction Layer (HAL) for asynchronous SPI Master communication.
 *
 * This header defines the public interface for asynchronous SPI Master operations using DMA.
 * It provides functions for enabling async mode and performing
 * non-blocking read/write operations with automatic DMA optimization.
 *
 * Async mode provides non-blocking data transfers with callback completion.
 * This mode requires HAL_SPI_ASYNC_DMA_SUPPORT to be defined at compile time.
 *
 * @note This header requires hal_spi_master.h to be included first for base functionality
 */

#ifndef HAL_SPI_MASTER_ASYNC_H
#define HAL_SPI_MASTER_ASYNC_H

#include <stddef.h>
#include <stdint.h>

#include "hal_common.h"
#include "hal_spi_types.h"

// Callback types for asynchronous operations
typedef void (*hal_spi_async_complete_cb_t)(void * ctx, hal_spi_result_t result);

// Only provide async API if support enabled in private implementation header
#if defined(HAL_SPI_ASYNC_DMA_SUPPORT)

hal_spi_result_t hal_spi_enable_async_mode(
    struct hal_spi_context * spi_ctx,
    const struct hal_spi_async_dma_config *async_cfg
);

hal_spi_result_t hal_spi_disable_async_mode(
    struct hal_spi_context * spi_ctx
);

hal_spi_result_t hal_spi_write_async(
    struct hal_spi_context * spi_ctx,
    const uint8_t * data, size_t len,
    hal_timeout_ms timeout,
    hal_spi_async_complete_cb_t callback,
    void * callback_ctx
);

hal_spi_result_t hal_spi_read_async(
    struct hal_spi_context * spi_ctx,
    uint8_t * data, size_t len,
    hal_timeout_ms timeout,
    hal_spi_async_complete_cb_t callback,
    void * callback_ctx
);

hal_spi_result_t hal_spi_write_read_async(
    struct hal_spi_context * spi_ctx,
    const uint8_t * tx_data, size_t tx_len,
    uint8_t * rx_data, size_t rx_len,
    hal_timeout_ms timeout,
    hal_spi_async_complete_cb_t callback,
    void * callback_ctx
);

#endif /* HAL_SPI_ASYNC_DMA_SUPPORT */

#endif /* HAL_SPI_MASTER_ASYNC_H */