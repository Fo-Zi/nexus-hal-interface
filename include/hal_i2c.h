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

#include "hal_i2c_types.h"

hal_i2c_result_t hal_i2c_init(hal_i2c_context_t * ctxt);
hal_i2c_result_t hal_i2c_deinit(hal_i2c_context_t *i2c_ctx);
hal_i2c_result_t hal_i2c_set_config(hal_i2c_context_t *i2c_ctx, hal_i2c_config_t *config);
hal_i2c_result_t hal_i2c_get_config(hal_i2c_context_t *i2c_ctx, hal_i2c_config_t *config);
hal_i2c_result_t hal_i2c_write(hal_i2c_context_t *i2c_ctx, uint8_t dev_address, const uint8_t *data, size_t len);
hal_i2c_result_t hal_i2c_read(hal_i2c_context_t *i2c_ctx, uint8_t dev_address, uint8_t *data, size_t len);

hal_i2c_result_t hal_i2c_write_read_reg(
    hal_i2c_context_t *i2c_ctx,
    uint8_t dev_address,
    const uint8_t *reg_address, size_t reg_len,
    uint8_t *data,
    size_t data_len
);

#endif
