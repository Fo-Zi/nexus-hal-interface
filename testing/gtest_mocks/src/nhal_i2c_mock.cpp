/**
 * @file nhal_i2c_mock.cpp
 * @brief C interface bridge for I2C mock
 */

#include "nhal_i2c_mock.hpp"

extern "C" {
    // I2C Master interface implementations
    nhal_result_t nhal_i2c_master_init(struct nhal_i2c_context *ctx) {
        return NhalI2cMock::instance().nhal_i2c_master_init(ctx);
    }

    nhal_result_t nhal_i2c_master_deinit(struct nhal_i2c_context *ctx) {
        return NhalI2cMock::instance().nhal_i2c_master_deinit(ctx);
    }

    nhal_result_t nhal_i2c_master_set_config(struct nhal_i2c_context *ctx, struct nhal_i2c_config *config) {
        return NhalI2cMock::instance().nhal_i2c_master_set_config(ctx, config);
    }

    nhal_result_t nhal_i2c_master_get_config(struct nhal_i2c_context *ctx, struct nhal_i2c_config *config) {
        return NhalI2cMock::instance().nhal_i2c_master_get_config(ctx, config);
    }

    nhal_result_t nhal_i2c_master_write(struct nhal_i2c_context *ctx, nhal_i2c_address dev_address, const uint8_t *data, size_t len, nhal_timeout_ms timeout) {
        return NhalI2cMock::instance().nhal_i2c_master_write(ctx, dev_address, data, len, timeout);
    }

    nhal_result_t nhal_i2c_master_read(struct nhal_i2c_context *ctx, nhal_i2c_address dev_address, uint8_t *data, size_t len, nhal_timeout_ms timeout) {
        return NhalI2cMock::instance().nhal_i2c_master_read(ctx, dev_address, data, len, timeout);
    }

    nhal_result_t nhal_i2c_master_write_read_reg(struct nhal_i2c_context *ctx, nhal_i2c_address dev_address, const uint8_t *reg_address, size_t reg_len, uint8_t *data, size_t data_len, nhal_timeout_ms timeout) {
        return NhalI2cMock::instance().nhal_i2c_master_write_read_reg(ctx, dev_address, reg_address, reg_len, data, data_len, timeout);
    }

    // I2C Master Async interface implementations
    nhal_result_t nhal_i2c_master_init_async(struct nhal_i2c_context *ctx, const struct nhal_async_config *async_cfg) {
        return NhalI2cMock::instance().nhal_i2c_master_init_async(ctx, async_cfg);
    }

    nhal_result_t nhal_i2c_master_deinit_async(struct nhal_i2c_context *ctx) {
        return NhalI2cMock::instance().nhal_i2c_master_deinit_async(ctx);
    }

    nhal_result_t nhal_i2c_master_set_async_callback(struct nhal_i2c_context *ctx, nhal_async_complete_cb_t callback) {
        return NhalI2cMock::instance().nhal_i2c_master_set_async_callback(ctx, callback);
    }

    nhal_result_t nhal_i2c_master_disable_async_callback(struct nhal_i2c_context *ctx) {
        return NhalI2cMock::instance().nhal_i2c_master_disable_async_callback(ctx);
    }

    nhal_async_status_t nhal_i2c_master_get_async_status(struct nhal_i2c_context *ctx) {
        return NhalI2cMock::instance().nhal_i2c_master_get_async_status(ctx);
    }

    nhal_result_t nhal_i2c_master_write_async(struct nhal_i2c_context *ctx, nhal_i2c_address dev_address, const uint8_t *data, size_t len, nhal_timeout_ms timeout_ms) {
        return NhalI2cMock::instance().nhal_i2c_master_write_async(ctx, dev_address, data, len, timeout_ms);
    }

    nhal_result_t nhal_i2c_master_read_async(struct nhal_i2c_context *ctx, nhal_i2c_address dev_address, uint8_t *data, size_t len, nhal_timeout_ms timeout_ms) {
        return NhalI2cMock::instance().nhal_i2c_master_read_async(ctx, dev_address, data, len, timeout_ms);
    }

    nhal_result_t nhal_i2c_master_write_read_reg_async(struct nhal_i2c_context *ctx, nhal_i2c_address dev_address, const uint8_t *reg_address, size_t reg_len, uint8_t *data, size_t data_len, nhal_timeout_ms timeout_ms) {
        return NhalI2cMock::instance().nhal_i2c_master_write_read_reg_async(ctx, dev_address, reg_address, reg_len, data, data_len, timeout_ms);
    }

    // I2C Transfer interface implementations
    nhal_result_t nhal_i2c_master_perform_transfer(struct nhal_i2c_context *ctx, nhal_i2c_transfer_op_t *ops, size_t num_ops, nhal_timeout_ms timeout_ms) {
        return NhalI2cMock::instance().nhal_i2c_master_perform_transfer(ctx, ops, num_ops, timeout_ms);
    }
}