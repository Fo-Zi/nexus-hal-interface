/**
 * @file nhal_pin_mock.hpp
 * @brief Google Mock implementation for Pin HAL interface
 */

#ifndef NHAL_PIN_MOCK_HPP
#define NHAL_PIN_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_pin.h"

/**
 * @brief Mock class for Pin HAL interface
 */
class NhalPinMock {
public:
    // Pin operations
    MOCK_METHOD(nhal_result_t, nhal_pin_init, (struct nhal_pin_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_pin_deinit, (struct nhal_pin_context *ctx));
    MOCK_METHOD(nhal_result_t, nhal_pin_set_config, (struct nhal_pin_context *ctx, struct nhal_pin_config *config));
    MOCK_METHOD(nhal_result_t, nhal_pin_get_config, (struct nhal_pin_context *ctx, struct nhal_pin_config *config));
    MOCK_METHOD(nhal_result_t, nhal_pin_set_state, (struct nhal_pin_context *ctx, nhal_pin_state_t value));
    MOCK_METHOD(nhal_result_t, nhal_pin_get_state, (struct nhal_pin_context *ctx, nhal_pin_state_t *value));
    MOCK_METHOD(nhal_result_t, nhal_pin_set_callback, (struct nhal_pin_context *ctx, nhal_pin_callback_t callback));
    MOCK_METHOD(nhal_result_t, nhal_pin_set_direction, (struct nhal_pin_context *ctx, nhal_pin_dir_t direction, nhal_pin_pull_mode_t pull_mode));

    // Singleton instance for C interface
    static NhalPinMock& instance() {
        static NhalPinMock mock;
        return mock;
    }
};

#endif /* NHAL_PIN_MOCK_HPP */