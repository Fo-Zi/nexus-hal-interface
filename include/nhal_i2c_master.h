/**
 * @file nhal_i2c_master.h
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
 * @note For non-blocking asynchronous operations, see nhal_i2c_master_async.h
 */
#ifndef NHAL_I2C_MASTER_H
#define NHAL_I2C_MASTER_H

#include <stdint.h>
#include <stddef.h>

#include "nhal_common.h"
#include "nhal_i2c_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize I2C master context
 * @param ctx Pointer to I2C context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_init(struct nhal_i2c_context * ctx);

/**
 * @brief Deinitialize I2C master context
 * @param ctx Pointer to I2C context structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_deinit(struct nhal_i2c_context *ctx);

/**
 * @brief Set I2C master configuration
 * @param ctx Pointer to I2C context structure
 * @param config Pointer to configuration structure
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_set_config(struct nhal_i2c_context *ctx, struct nhal_i2c_config *config);

/**
 * @brief Get current I2C master configuration
 * @param ctx Pointer to I2C context structure
 * @param config Pointer to configuration structure to fill
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_get_config(struct nhal_i2c_context *ctx, struct nhal_i2c_config *config);

/**
 * @brief Write data to I2C device (blocking)
 * @param ctx Pointer to I2C context structure
 * @param dev_address Target device address
 * @param data Pointer to data to transmit
 * @param len Number of bytes to transmit
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_write(
    struct nhal_i2c_context *ctx,
    nhal_i2c_address_t dev_address,
    const uint8_t *data, size_t len
);

/**
 * @brief Read data from I2C device (blocking)
 * @param ctx Pointer to I2C context structure
 * @param dev_address Target device address
 * @param data Pointer to buffer for received data
 * @param len Number of bytes to read
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_read(
    struct nhal_i2c_context *ctx,
    nhal_i2c_address_t dev_address,
    uint8_t *data, size_t len
);

/**
 * @brief Write to register then read from I2C device (blocking)
 * @param ctx Pointer to I2C context structure
 * @param dev_address Target device address
 * @param reg_address Pointer to register address bytes
 * @param reg_len Number of register address bytes
 * @param data Pointer to buffer for received data
 * @param data_len Number of bytes to read
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_write_read_reg(
    struct nhal_i2c_context *ctx,
    nhal_i2c_address_t dev_address,
    const uint8_t *reg_address, size_t reg_len,
    uint8_t *data, size_t data_len
);

#ifdef __cplusplus
}
#endif

#endif
