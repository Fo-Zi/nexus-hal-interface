/**
 * @file nhal_i2c_transfer.h
 * @brief Defines the API for low-level I2C bus transfers in a Hardware Abstraction Layer (HAL).
 *
 * This header declares an API function for low-level I2C bus transfers, referencing
 * structures and enums defined in `nhal_i2c_types.h` to facilitate complex I2C transactions,
 * including multi-message transfers with explicit control over START/STOP conditions and addressing.
 */
#ifndef NHAL_I2C_TRANSFER_H_
#define NHAL_I2C_TRANSFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "nhal_common.h"
#include "nhal_i2c_types.h"

/**
 * @brief Perform complex I2C transfer with multiple operations
 * @param ctx Pointer to I2C context structure
 * @param ops Array of transfer operations to perform
 * @param num_ops Number of operations in the array
 * @param timeout_ms Timeout in milliseconds
 * @return NHAL_OK on success, error code otherwise
 */
nhal_result_t nhal_i2c_master_perform_transfer(
    struct nhal_i2c_context * ctx,
    nhal_i2c_transfer_op_t *ops,
    size_t num_ops,
    nhal_timeout_ms timeout_ms
);

#endif // NHAL_I2C_TRANSFER_H_
