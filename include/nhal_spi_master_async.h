/**
 * @file nhal_spi_master_async.h
 * @brief Hardware Abstraction Layer (HAL) for asynchronous SPI Master communication.
 *
 * This header defines the public interface for asynchronous SPI Master operations using DMA.
 * It provides functions for enabling async mode and performing
 * non-blocking read/write operations with automatic DMA optimization.
 *
 * Async mode provides non-blocking data transfers with callback completion.
 * This mode requires NHAL_SPI_ASYNC_SUPPORT to be defined at compile time.
 *
 * @note This header requires nhal_spi_master.h to be included first for base functionality
 */

#ifndef NHAL_SPI_MASTER_ASYNC_H
#define NHAL_SPI_MASTER_ASYNC_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"
#include "nhal_spi_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(NHAL_SPI_ASYNC_SUPPORT)

/**
 * @brief Initialize SPI context for async mode
 * @param ctx Pointer to SPI context structure
 * @param async_cfg Pointer to async configuration
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_init_async(
    struct nhal_spi_context * ctx,
    const struct nhal_async_config * async_cfg
);

/**
 * @brief Deinitialize SPI async mode
 * @param ctx Pointer to SPI context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_deinit_async(
    struct nhal_spi_context * ctx
);

/**
 * @brief Set callback for async operation completion
 * @param ctx Pointer to SPI context structure
 * @param callback Callback function to execute on completion
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_set_async_callback(
    struct nhal_spi_context *ctx,
    nhal_async_complete_cb_t callback
);

/**
 * @brief Disable async completion callback
 * @param ctx Pointer to SPI context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_disable_async_callback(
    struct nhal_spi_context *ctx
);

/**
 * @brief Get current async operation status
 * @param ctx Pointer to SPI context structure
 * @return Current async operation status
 */
nhal_async_status_t nhal_spi_master_get_async_status(
    struct nhal_spi_context *ctx
);

/**
 * @brief Write data asynchronously
 * @param ctx Pointer to SPI context structure
 * @param data Pointer to data to transmit
 * @param len Number of bytes to transmit
 * @param timeout_ms Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_write_async(
    struct nhal_spi_context * ctx,
    const uint8_t * data, size_t len,
);

/**
 * @brief Read data asynchronously
 * @param ctx Pointer to SPI context structure
 * @param data Pointer to buffer for received data
 * @param len Number of bytes to read
 * @param timeout_ms Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_read_async(
    struct nhal_spi_context * ctx,
    uint8_t * data, size_t len,
);

/**
 * @brief Write and read data simultaneously (full-duplex) asynchronously
 * @param ctx Pointer to SPI context structure
 * @param tx_data Pointer to data to transmit
 * @param tx_len Number of bytes to transmit
 * @param rx_data Pointer to buffer for received data
 * @param rx_len Number of bytes to read
 * @param timeout_ms Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_spi_master_write_read_async(
    struct nhal_spi_context * ctx,
    const uint8_t * tx_data, size_t tx_len,
    uint8_t * rx_data, size_t rx_len,
);

#endif /* NHAL_SPI_ASYNC_SUPPORT */

#ifdef __cplusplus
}
#endif

#endif /* NHAL_SPI_MASTER_ASYNC_H */
