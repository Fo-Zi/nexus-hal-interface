/**
 * @file nhal_pin_types.h
 * @brief This file defines the types and enumerations used for interacting with hardware pins in the HAL.
 *
 * This header provides definitions for pin identifiers, status codes, callback functions,
 * configuration structures, context structures, and pin states.
 */
#ifndef NHAL_PIN_TYPES_H
#define NHAL_PIN_TYPES_H

#include <stdint.h>

#include "nhal_common.h"

typedef enum nhal_pin_state_t{
    NHAL_PIN_LOW = 0,
    NHAL_PIN_HIGH
}nhal_pin_state_t;

typedef enum {
    NHAL_PIN_DIR_INPUT,
    NHAL_PIN_DIR_OUTPUT,
    NHAL_PIN_DIR_TOTAL_NUM,
} nhal_pin_dir_t;

typedef enum {
    NHAL_PIN_PMODE_NONE,
    NHAL_PIN_PMODE_PULL_UP,
    NHAL_PIN_PMODE_PULL_DOWN,
    NHAL_PIN_PMODE_PULL_UP_AND_DOWN,
    NHAL_PIN_PMODE_TOTAL_NUM,
} nhal_pin_pull_mode_t;

typedef void (*nhal_pin_callback_t)(void *context);

struct nhal_pin_config{
    nhal_pin_dir_t direction;
    nhal_pin_pull_mode_t pull_mode;
    struct nhal_pin_impl_config * impl_config;
};

/**
 * @brief Pin context structure
 * 
 * Note: Pin identification uses a different pattern than other peripherals.
 * While other peripherals use simple bus IDs (uint8_t), pins require more
 * complex identification schemes as different MCUs use various methods:
 * - Simple GPIO numbers (0-31)
 * - Port + pin combinations (PORTA.5, GPIOB.12)
 * - Complex hierarchical schemes
 * 
 * Therefore, pin_id is a pointer to an implementation-specific structure
 * rather than a simple integer bus ID.
 */
struct nhal_pin_context{
    struct nhal_pin_id * pin_id;
    struct nhal_pin_impl_ctx * impl_ctx;
};


#endif
