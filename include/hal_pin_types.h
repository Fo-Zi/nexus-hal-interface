/**
 * @file hal_pin_types.h
 * @brief This file defines the types and enumerations used for interacting with hardware pins in the HAL.
 *
 * This header provides definitions for pin identifiers, status codes, callback functions,
 * configuration structures, context structures, and pin states.
 */
#ifndef HAL_PIN_TYPES_H
#define HAL_PIN_TYPES_H

#include <stdint.h>

typedef enum {
    HAL_PIN_OK = 0,                     /**< Operation completed successfully. */
    HAL_PIN_ERR_INVALID_PIN,            /**< The specified pin is invalid. */
    HAL_PIN_ERR_INVALID_MODE,           /**< The specified pin mode is invalid. */
    HAL_PIN_ERR_NOT_INITIALIZED,        /**< Pin has not been initialized. */
    HAL_PIN_ERR_TIMEOUT,                /**< Operation timed out before completion. */
    HAL_PIN_ERR_INVALID_ARG,            /**< One or more arguments are invalid. */
    HAL_PIN_ERR_HW_FAILURE,             /**< Hardware failure occurred. */
    HAL_PIN_ERR_LOCKED,                 /**< Pin is currently locked by another process. */
    HAL_PIN_ERR_OTHER                   /**< An unspecified error occurred. */
} hal_pin_result_t;

typedef void (*hal_pin_callback_t)(void * ctxt);

struct hal_pin_config;
typedef struct hal_pin_config hal_pin_config_t;

struct hal_pin_context;
typedef struct hal_pin_context hal_pin_context_t;

typedef enum hal_pin_state_t{
    HAL_PIN_LOW = 0,
    HAL_PIN_HIGH
}hal_pin_state_t;

#endif
