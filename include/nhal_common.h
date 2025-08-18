#ifndef NHAL_COMMON_H
#define NHAL_COMMON_H

#include <stdint.h>

typedef uint16_t nhal_timeout_ms;

typedef enum {
    NHAL_OK = 0,
    NHAL_ERR_TIMEOUT,
    NHAL_ERR_INVALID_ARG,
    NHAL_ERR_INVALID_CONFIG,
    NHAL_ERR_INVALID_STATE,
    NHAL_ERR_NOT_FOUND,
    NHAL_ERR_NOT_SUPPORTED,
    NHAL_ERR_NOT_INITIALIZED,
    NHAL_ERR_NOT_CONFIGURED,
    NHAL_ERR_RESOURCE_BUSY,
    NHAL_ERR_RESOURCE_UNAVAILABLE,
    NHAL_ERR_COMMUNICATION,
    NHAL_ERR_HW_FAILURE,
    NHAL_ERR_NO_MEMORY,
    NHAL_ERR_BUFFER_OVERFLOW,
    NHAL_ERR_OTHER
} nhal_result_t;

void nhal_delay_microseconds(uint32_t microseconds);
void nhal_delay_milliseconds(uint32_t milliseconds);

nhal_result_t nhal_map_esp_err(int esp_err_code);

#endif
