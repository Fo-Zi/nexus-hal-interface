/**
 * @file nhal_common_mock.cpp
 * @brief Mock implementations of common NHAL functions (timing, delays)
 */

#include "nhal_common_mock.hpp"

// C interface implementations that delegate to the mock
extern "C" {
    void nhal_delay_microseconds(uint32_t microseconds) {
        NhalCommonMock::instance().nhal_delay_microseconds(microseconds);
    }

    void nhal_delay_milliseconds(uint32_t milliseconds) {
        NhalCommonMock::instance().nhal_delay_milliseconds(milliseconds);
    }

    uint64_t nhal_get_timestamp_microseconds(void) {
        return NhalCommonMock::instance().nhal_get_timestamp_microseconds();
    }

    uint32_t nhal_get_timestamp_milliseconds(void) {
        return NhalCommonMock::instance().nhal_get_timestamp_milliseconds();
    }
}