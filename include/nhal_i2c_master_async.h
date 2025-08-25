/**
 * @file nhal_i2c_master_async.h
 * @brief Hardware Abstraction Layer (HAL) for asynchronous I2C Master communication.
 *
 * This header defines the public interface for asynchronous I2C Master operations using DMA.
 * It provides functions for enabling async mode and performing
 * non-blocking read/write operations with automatic DMA optimization.
 *
 * Async mode provides non-blocking data transfers with callback completion.
 * This mode requires NHAL_I2C_ASYNC_DMA_SUPPORT to be defined at compile time.
 *
 * @note This header requires nhal_i2c_master.h to be included first for base functionality
 */

#ifndef NHAL_I2C_MASTER_ASYNC_H
#define NHAL_I2C_MASTER_ASYNC_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"
#include "nhal_i2c_types.h"

#if defined(NHAL_I2C_ASYNC_SUPPORT)

nhal_result_t nhal_i2c_master_init_async(
    struct nhal_i2c_context * ctx,
    const struct nhal_async_config * async_cfg
);

nhal_result_t nhal_i2c_master_deinit_async(
    struct nhal_i2c_context * ctx
);

nhal_result_t nhal_i2c_master_set_async_callback(
    struct nhal_i2c_context *ctx,
    nhal_async_complete_cb_t callback
);

nhal_result_t nhal_i2c_master_disable_async_callback(
    struct nhal_i2c_context *ctx
);

nhal_async_status_t nhal_i2c_master_get_async_status(
    struct nhal_i2c_context *ctx
);

nhal_result_t nhal_i2c_master_write_async(
    struct nhal_i2c_context *ctx,
    uint8_t dev_address,
    const uint8_t *data,
    size_t len,
    nhal_timeout_ms timeout_ms
);

nhal_result_t nhal_i2c_master_read_async(
    struct nhal_i2c_context *ctx,
    uint8_t dev_address,
    uint8_t *data,
    size_t len,
    nhal_timeout_ms timeout_ms
);

nhal_result_t nhal_i2c_master_write_read_reg_async(
    struct nhal_i2c_context *ctx,
    uint8_t dev_address,
    const uint8_t *reg_address, size_t reg_len,
    uint8_t *data, size_t data_len,
    nhal_timeout_ms timeout_ms
);

#endif /* NHAL_I2C_ASYNC_SUPPORT */

#endif /* NHAL_I2C_MASTER_ASYNC_H */
