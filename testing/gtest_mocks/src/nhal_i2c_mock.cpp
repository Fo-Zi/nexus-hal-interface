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

    nhal_result_t nhal_i2c_master_write(struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, const uint8_t *data, size_t len) {
        return NhalI2cMock::instance().nhal_i2c_master_write(ctx, dev_address, data, len);
    }

    nhal_result_t nhal_i2c_master_read(struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, uint8_t *data, size_t len) {
        return NhalI2cMock::instance().nhal_i2c_master_read(ctx, dev_address, data, len);
    }

    nhal_result_t nhal_i2c_master_write_read_reg(struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, const uint8_t *reg_address, size_t reg_len, uint8_t *data, size_t data_len) {
        return NhalI2cMock::instance().nhal_i2c_master_write_read_reg(ctx, dev_address, reg_address, reg_len, data, data_len);
    }

    // I2C Transfer interface implementations
    nhal_result_t nhal_i2c_master_perform_transfer(struct nhal_i2c_context *ctx, nhal_i2c_address_t dev_address, nhal_i2c_transfer_op_t *ops, size_t num_ops) {
        return NhalI2cMock::instance().nhal_i2c_master_perform_transfer(ctx, dev_address, ops, num_ops);
    }
}
