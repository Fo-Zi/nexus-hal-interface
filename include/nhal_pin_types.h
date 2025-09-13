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

/**
 * @brief Pin logic state enumeration
 */
typedef enum nhal_pin_state_t{
    NHAL_PIN_LOW = 0,
    NHAL_PIN_HIGH
}nhal_pin_state_t;

/**
 * @brief Pin direction enumeration
 */
typedef enum {
    NHAL_PIN_DIR_INPUT,
    NHAL_PIN_DIR_OUTPUT,
    NHAL_PIN_DIR_TOTAL_NUM,
} nhal_pin_dir_t;

/**
 * @brief Pin pull resistor mode enumeration
 */
typedef enum {
    NHAL_PIN_PMODE_NONE,
    NHAL_PIN_PMODE_PULL_UP,
    NHAL_PIN_PMODE_PULL_DOWN,
    NHAL_PIN_PMODE_TOTAL_NUM,
} nhal_pin_pull_mode_t;

typedef enum {
    NHAL_PIN_INT_TRIGGER_NONE,
    NHAL_PIN_INT_TRIGGER_RISING_EDGE,
    NHAL_PIN_INT_TRIGGER_FALLING_EDGE,
    NHAL_PIN_INT_TRIGGER_BOTH_EDGES,
    NHAL_PIN_INT_TRIGGER_HIGH_LEVEL,
    NHAL_PIN_INT_TRIGGER_LOW_LEVEL,
    NHAL_PIN_INT_TRIGGER_TOTAL_NUM,
} nhal_pin_int_trigger_t;

/* Forward declaration */
struct nhal_pin_context;

/**
 * @brief Pin interrupt callback function type
 * 
 * @param pin_ctx Pin context that triggered the interrupt
 * @param user_data User-provided data pointer
 * 
 * @note This executes in interrupt context - keep it fast and minimal
 */
typedef void (*nhal_pin_callback_t)(struct nhal_pin_context *pin_ctx, void *user_data);

/**
 * @brief Pin configuration structure
 */
struct nhal_pin_config{
    nhal_pin_dir_t direction;
    nhal_pin_pull_mode_t pull_mode;
    struct nhal_pin_impl_config * impl_config;
};

/**
 * @brief Pin context structure (implementation-defined)
 *
 * Contains platform-specific pin identification and runtime state.
 * Must include unique pin identification and any shared resources.
 *
 * @par Example content:
 * @code
 * struct nhal_pin_context {
 *     // Pin identification: GPIO number OR port+pin OR platform handle
 *     uint32_t pin_id;
 *     // Shared resources: mutex for thread safety, callback state, etc.
 *     mutex_t *lock;
 * };
 * @endcode
 */
struct nhal_pin_context;


#endif
