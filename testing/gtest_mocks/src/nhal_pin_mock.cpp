/**
 * @file nhal_pin_mock.cpp
 * @brief C interface bridge for Pin mock
 */

#include "nhal_pin_mock.hpp"

extern "C" {
    nhal_result_t nhal_pin_init(struct nhal_pin_context *ctx) {
        return NhalPinMock::instance().nhal_pin_init(ctx);
    }

    nhal_result_t nhal_pin_deinit(struct nhal_pin_context *ctx) {
        return NhalPinMock::instance().nhal_pin_deinit(ctx);
    }

    nhal_result_t nhal_pin_set_config(struct nhal_pin_context *ctx, struct nhal_pin_config *config) {
        return NhalPinMock::instance().nhal_pin_set_config(ctx, config);
    }

    nhal_result_t nhal_pin_get_config(struct nhal_pin_context *ctx, struct nhal_pin_config *config) {
        return NhalPinMock::instance().nhal_pin_get_config(ctx, config);
    }

    nhal_result_t nhal_pin_set_state(struct nhal_pin_context *ctx, nhal_pin_state_t value) {
        return NhalPinMock::instance().nhal_pin_set_state(ctx, value);
    }

    nhal_result_t nhal_pin_get_state(struct nhal_pin_context *ctx, nhal_pin_state_t *value) {
        return NhalPinMock::instance().nhal_pin_get_state(ctx, value);
    }

    nhal_result_t nhal_pin_set_callback(struct nhal_pin_context *ctx, nhal_pin_callback_t callback) {
        return NhalPinMock::instance().nhal_pin_set_callback(ctx, callback);
    }

    nhal_result_t nhal_pin_set_direction(struct nhal_pin_context *ctx, nhal_pin_dir_t direction, nhal_pin_pull_mode_t pull_mode) {
        return NhalPinMock::instance().nhal_pin_set_direction(ctx, direction, pull_mode);
    }
}