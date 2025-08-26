/**
 * @file nhal_i2c_mock.hpp
 * @brief Google Mock implementation for I2C HAL interface
 */

#ifndef NHAL_I2C_MOCK_HPP
#define NHAL_I2C_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_i2c_master.h"
#include "nhal_i2c_master_async.h"
#include "nhal_i2c_transfer.h"

/**
 * @brief Mock class for I2C HAL interface
 */
class NhalI2cMock {
public:
    // Basic I2C master operations
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_init, (struct nhal_i2c_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_deinit, (struct nhal_i2c_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_set_config, (struct nhal_i2c_context *ctx, struct nhal_i2c_config *config));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_get_config, (struct nhal_i2c_context *ctx, struct nhal_i2c_config *config));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_write, (struct nhal_i2c_context *ctx, nhal_i2c_slave_addr dev_address, const uint8_t *data, size_t len, nhal_timeout_ms timeout));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_read, (struct nhal_i2c_context *ctx, nhal_i2c_slave_addr dev_address, uint8_t *data, size_t len, nhal_timeout_ms timeout));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_write_read_reg, (struct nhal_i2c_context *ctx, nhal_i2c_slave_addr dev_address, const uint8_t *reg_address, size_t reg_len, uint8_t *data, size_t data_len, nhal_timeout_ms timeout));

    // Async I2C master operations
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_init_async, (struct nhal_i2c_context *ctx, const struct nhal_async_config *async_cfg));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_deinit_async, (struct nhal_i2c_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_set_async_callback, (struct nhal_i2c_context *ctx, nhal_async_complete_cb_t callback));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_disable_async_callback, (struct nhal_i2c_context *ctx));
    MOCK_METHOD(nhal_async_status_t, nhal_i2c_master_get_async_status, (struct nhal_i2c_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_write_async, (struct nhal_i2c_context *ctx, nhal_i2c_slave_addr dev_address, const uint8_t *data, size_t len, nhal_timeout_ms timeout_ms));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_read_async, (struct nhal_i2c_context *ctx, nhal_i2c_slave_addr dev_address, uint8_t *data, size_t len, nhal_timeout_ms timeout_ms));
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_write_read_reg_async, (struct nhal_i2c_context *ctx, nhal_i2c_slave_addr dev_address, const uint8_t *reg_address, size_t reg_len, uint8_t *data, size_t data_len, nhal_timeout_ms timeout_ms));

    // Transfer operations
    MOCK_METHOD(nhal_result_t, nhal_i2c_master_perform_transfer, (struct nhal_i2c_context *ctx, nhal_i2c_transfer_op_t *ops, size_t num_ops, nhal_timeout_ms timeout_ms));

    // Singleton instance for C interface
    static NhalI2cMock& instance() {
        static NhalI2cMock mock;
        return mock;
    }
};

#endif /* NHAL_I2C_MOCK_HPP */