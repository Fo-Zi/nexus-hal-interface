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

nhal_result_t nhal_i2c_master_init(struct nhal_i2c_context * ctx);
nhal_result_t nhal_i2c_master_deinit(struct nhal_i2c_context *ctx);
nhal_result_t nhal_i2c_master_set_config(struct nhal_i2c_context *ctx, struct nhal_i2c_config *config);
nhal_result_t nhal_i2c_master_get_config(struct nhal_i2c_context *ctx, struct nhal_i2c_config *config);

nhal_result_t nhal_i2c_master_write(
    struct nhal_i2c_context *ctx,
    nhal_i2c_slave_addr dev_address,
    const uint8_t *data, size_t len,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_i2c_master_read(
    struct nhal_i2c_context *ctx,
    nhal_i2c_slave_addr dev_address,
    uint8_t *data, size_t len,
    nhal_timeout_ms timeout
);

nhal_result_t nhal_i2c_master_write_read_reg(
    struct nhal_i2c_context *ctx,
    nhal_i2c_slave_addr dev_address,
    const uint8_t *reg_address, size_t reg_len,
    uint8_t *data, size_t data_len,
    nhal_timeout_ms timeout
);

#ifdef __cplusplus
}
#endif

#endif
