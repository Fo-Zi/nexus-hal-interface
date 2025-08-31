/**
 * @file nhal_common_mock.cpp
 * @brief Mock implementations of common NHAL functions (timing, delays)
 */

extern "C" {
    #include "nhal_common.h"
}

// Mock implementations of timing functions
extern "C" {
    void nhal_delay_milliseconds(uint32_t ms) {
        // Mock implementation - do nothing for tests
        (void)ms;
    }

    void nhal_delay_microseconds(uint32_t us) {
        // Mock implementation - do nothing for tests  
        (void)us;
    }

    uint64_t nhal_get_timestamp_microseconds(void) {
        // Mock implementation - return incrementing time
        // Start from a reasonable time to avoid issues with uninitialized timestamps
        static uint64_t mock_time = 10000; 
        return mock_time += 50; // Increment by 50us each call - reasonable for timing measurements
    }

    uint32_t nhal_get_timestamp_milliseconds(void) {
        // Mock implementation - return incrementing time that matches microsecond time
        static uint32_t mock_time = 10; 
        return mock_time += 1; // Increment by 1ms each call - allows proper timing logic
    }
}