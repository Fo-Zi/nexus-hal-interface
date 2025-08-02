/**
 * @file hal_i2c_transfer.h
 * @brief Defines the API for low-level I2C bus transfers in a Hardware Abstraction Layer (HAL).
 *
 * This header declares an API function for low-level I2C bus transfers, referencing
 * structures and enums defined in `hal_i2c_types.h` to facilitate complex I2C transactions,
 * including multi-message transfers with explicit control over START/STOP conditions and addressing.
 */
#ifndef HAL_I2C_TRANSFER_H_
#define HAL_I2C_TRANSFER_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "hal_i2c_types.h"

hal_i2c_result_t hal_i2c_perform_transfer(
    hal_i2c_context_t * ctx,
    hal_i2c_transfer_op_t *ops,
    size_t num_ops
);

#endif // HAL_I2C_TRANSFER_H_
