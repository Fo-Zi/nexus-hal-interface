#ifndef HAL_COMMON_H
#define HAL_COMMON_H

#include <stdint.h>

typedef uint16_t hal_timeout_ms;

/**
 * @brief Delay for specified number of microseconds
 *
 * @param microseconds Number of microseconds to delay
 */
void hal_delay_microseconds(uint32_t microseconds);

/**
 * @brief Delay for specified number of milliseconds
 *
 * @param milliseconds Number of milliseconds to delay
 */
void hal_delay_milliseconds(uint32_t milliseconds);

#endif
