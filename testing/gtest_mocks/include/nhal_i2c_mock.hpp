/**
 * @file nhal_i2c_mock.hpp
 * @brief Google Mock implementation for I2C HAL interface
 */

#ifndef NHAL_I2C_MOCK_HPP
#define NHAL_I2C_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_i2c_master.h"
#include "nhal_i2c_transfer.h"

/**
 * @brief Mock class for I2C HAL interface
 */
class NhalI2cMock {
public:
    // I2C master operations
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_init, (struct nhal_i2c_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_deinit, (struct nhal_i2c_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_set_config, (struct nhal_i2c_context *ctx, struct nhal_i2c_config *config));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_get_config, (struct nhal_i2c_context *ctx, struct nhal_i2c_config *config));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_write, (struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, const uint8_t *data, size_t len));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_read, (struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, uint8_t *data, size_t len));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_write_read_reg, (struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, const uint8_t *reg_address, size_t reg_len, uint8_t *data, size_t data_len));

    // Transfer operations
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_perform_transfer, (struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, nhal_i2c_transfer_op_t *ops, size_t num_ops));

    // Singleton instance for C interface
    static NhalI2cMock& instance() {
        static NhalI2cMock mock;
        return mock;
    }
};

#endif /* NHAL_I2C_MOCK_HPP */
