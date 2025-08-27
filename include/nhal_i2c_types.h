/**
 * @file nhal_i2c_types.h
 * @brief Defines common types and structures for the I2C Hardware Abstraction Layer (HAL).
 *
 * This header file provides opaque types, enumerations, and structures used across
 * the I2C HAL API to facilitate communication over I2C buses.
 */
#ifndef NHAL_I2C_TYPES_H
#define NHAL_I2C_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"

typedef uint8_t nhal_i2c_bus_id;
typedef uint16_t nhal_i2c_address;

struct nhal_i2c_config{
    uint32_t clock_speed_hz;
    struct nhal_i2c_impl_config * impl_config;
};

/**
 * @brief Base I2C context - always present, minimal footprint
 */
struct nhal_i2c_context{
    nhal_i2c_bus_id      i2c_bus_id;

    struct nhal_i2c_impl_ctx * impl_ctx;

    // Async extensions handled separately in async context
};


typedef enum {
    NHAL_I2C_TRANSFER_MSG_WRITE        = 1, /**< Message is a write operation (default). */
    NHAL_I2C_TRANSFER_MSG_READ         = 1<<1, /**< Message is a read operation. */
    NHAL_I2C_TRANSFER_MSG_TEN_BIT_ADDR = 1<<2, /**< Use 10-bit addressing for this message. */
    NHAL_I2C_TRANSFER_MSG_NO_START     = 1<<3, /**< Do not send a START condition before this message.
                                                                *   Useful for subsequent messages in a combined transaction (e.g., after a repeated start). */
    NHAL_I2C_TRANSFER_MSG_NO_STOP      = 1<<4, /**< Do not send a STOP condition after this message.
                                                                *   Essential for creating repeated START conditions before the next message. */
    NHAL_I2C_TRANSFER_MSG_NO_ADDR      = 1<<5  /**< Do not write the address first in this op */
} nhal_i2c_transfer_bit_flags_t;

/**
 * @brief Structure describing a single I2C message segment within a transaction.
 *
 * A full I2C transaction can consist of one or more such messages.
 */
typedef struct {
    nhal_i2c_address address;             /**< 7-bit or 10-bit address for this message segment.
                                    *   The high bit (0x80) is not used for 7-bit addresses here;
                                    *   it's strictly the 7-bit address (0-127). */
    uint16_t flags;            /**< Combination of #nhal_i2c_transfer_bit_flags_t for this segment. */
    /**
     * @brief Union to hold data specific to either a read or a write operation.
     *
     * Only one of these members should be accessed based on the #flags.
     */
    union {
        /**
         * @brief Parameters for I2C read operations.
         */
        struct {
            uint8_t *buffer;           /**< Pointer to buffer for received data (must be writable). */
            size_t length;             /**< Number of bytes to read into the buffer. */
        } read;
        /**
         * @brief Parameters for I2C write operations.
         */
        struct {
            const uint8_t *bytes;      /**< Pointer to data to send (must be readable). */
            size_t length;             /**< Number of bytes to write from the bytes. */
        } write;
    };
} nhal_i2c_transfer_op_t;

#endif /* NHAL_I2C_TYPES_H */
