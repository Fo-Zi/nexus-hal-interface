/**
 * @file nhal_common_mock.hpp
 * @brief Google Mock implementation for common NHAL timing functions
 */

#ifndef NHAL_COMMON_MOCK_HPP
#define NHAL_COMMON_MOCK_HPP

#include <gmock/gmock.h>
#include "nhal_common.h"

/**
 * @brief Mock class for common NHAL timing functions
 * 
 * This mock allows you to control timing behavior in tests, enabling
 * simulation of sensor timeouts, delays, and timing-dependent scenarios.
 * 
 * Example usage for DHT11 timeout testing:
 * @code
 * TEST(DHT11Test, HandlesTimeout) {
 *     auto& mock = NhalCommonMock::instance();
 *     
 *     // Simulate sensor taking too long to respond
 *     EXPECT_CALL(mock, nhal_get_timestamp_microseconds())
 *         .WillOnce(Return(1000))      // Start time
 *         .WillOnce(Return(1000 + 2000000)); // 2 seconds later (timeout)
 *     
 *     // Test should detect timeout and return error
 *     EXPECT_EQ(NHAL_ERR_TIMEOUT, dht11_read_sensor(&sensor_ctx));
 * }
 * @endcode
 */
class NhalCommonMock {
public:
    // Timing functions
    MOCK_METHOD(void, nhal_delay_microseconds, (uint32_t microseconds));
    MOCK_METHOD(void, nhal_delay_milliseconds, (uint32_t milliseconds));
    MOCK_METHOD(uint64_t, nhal_get_timestamp_microseconds, ());
    MOCK_METHOD(uint32_t, nhal_get_timestamp_milliseconds, ());

    // Singleton instance for C interface
    static NhalCommonMock& instance() {
        static NhalCommonMock mock;
        return mock;
    }
};

#endif /* NHAL_COMMON_MOCK_HPP */