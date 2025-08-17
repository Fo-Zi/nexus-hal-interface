/**
 * @file hal_i2c_master.h
 * @brief Hardware Abstraction Layer for synchronous I2C Master mode communication.
 *
 * This file defines the API for interacting with an I2C bus in master mode.
 * It provides functions for initialization, configuration,
 * reading, writing, and combined operations using synchronous blocking transfers.
 *
 * Synchronous mode provides blocking operations with automatic transfer optimization.
 * The HAL automatically selects the best transfer method (CPU vs DMA) based on
 * transfer size and hardware capabilities - applications don't need to know.
 * All operations block until completion or timeout.
 *
 * @note For non-blocking asynchronous operations, see hal_i2c_master_async.h
 */
#ifndef HAL_I2C_MASTER_H
#define HAL_I2C_MASTER_H

#include <stdint.h>
#include <stddef.h>

#include "hal_common.h"
#include "hal_i2c_types.h"

hal_i2c_result_t hal_i2c_master_init(struct hal_i2c_context * ctxt);
hal_i2c_result_t hal_i2c_master_deinit(struct hal_i2c_context *i2c_ctx);
hal_i2c_result_t hal_i2c_master_set_config(struct hal_i2c_context *i2c_ctx, struct hal_i2c_config *config);
hal_i2c_result_t hal_i2c_master_get_config(struct hal_i2c_context *i2c_ctx, struct hal_i2c_config *config);

hal_i2c_result_t hal_i2c_master_write(
    struct hal_i2c_context *i2c_ctx,
    uint8_t dev_address,
    const uint8_t *data, size_t len,
    hal_timeout_ms timeout
);

hal_i2c_result_t hal_i2c_master_read(
    struct hal_i2c_context *i2c_ctx,
    uint8_t dev_address,
    uint8_t *data, size_t len,
    hal_timeout_ms timeout
);

hal_i2c_result_t hal_i2c_master_write_read_reg(
    struct hal_i2c_context *i2c_ctx,
    uint8_t dev_address,
    const uint8_t *reg_address, size_t reg_len,
    uint8_t *data, size_t data_len,
    hal_timeout_ms timeout
);

#endif
