#ifndef HAL_COMMON_H
#define HAL_COMMON_H

#include <stdint.h>

#define BIT_SHIFT_LEFT(N) (1 << N)
#define BIT_SHIFT_RIGHT(N) (1 >> N)

typedef uint16_t hal_timeout_ms;

#endif
