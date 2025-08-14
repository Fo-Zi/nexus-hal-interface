/**
 * @file hal_i2c.h
 * @brief Hardware Abstraction Layer for I2C communication.
 *
 * This file defines the API for interacting with an I2C bus.
 * It provides functions for initialization, configuration,
 * reading, writing, and combined write-read operations.
 */
#ifndef HAL_I2C_H
#define HAL_I2C_H

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
