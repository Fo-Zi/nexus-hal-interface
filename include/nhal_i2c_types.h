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

/**
 * @brief I2C address type enumeration
 */
typedef enum {
    NHAL_I2C_7BIT_ADDR = 0,
    NHAL_I2C_10BIT_ADDR = 1
}nhal_i2c_addr_type;

/**
 * @brief I2C device address structure
 */
typedef struct nhal_i2c_address{
    nhal_i2c_addr_type type;
    union{
        uint8_t address_7bit;
        uint16_t address_10bit;
    };
}nhal_i2c_address_t;

/**
 * @brief I2C configuration structure
 */
struct nhal_i2c_config{
    struct nhal_i2c_impl_config * impl_config;
};

/**
 * @brief I2C context structure (implementation-defined)
 *
 * Contains platform-specific I2C identification and runtime state.
 * Must include unique bus identification and any shared resources.
 *
 * @par Example content:
 * @code
 * struct nhal_i2c_context {
 *     // Bus identification: I2C index OR peripheral name OR base address
 *     uint8_t i2c_id;
 *     // Shared resources: mutex for bus access, multi-master arbitration, etc.
 *     mutex_t *bus_lock;
 * };
 * @endcode
 */
struct nhal_i2c_context;

/**
 * @brief I2C operation type enumeration
 */
typedef enum {
    NHAL_I2C_WRITE_OP,
    NHAL_I2C_READ_OP
}nhal_i2c_op_t;

/**
 * @brief I2C transfer operation flags
 *
 * These flags control I2C bus conditions and addressing behavior for individual transfer operations.
 */
typedef enum {
    NHAL_I2C_TRANSFER_MSG_NO_START     = 1, /**< Do not send a START condition before this message.
                                                                *   Useful for subsequent messages in a combined transaction (e.g., after a repeated start). */
    NHAL_I2C_TRANSFER_MSG_NO_STOP      = 1<<1, /**< Do not send a STOP condition after this message.
                                                                *   Essential for creating repeated START conditions before the next message. */
    NHAL_I2C_TRANSFER_MSG_NO_ADDR      = 1<<2  /**< Do not write the address first in this op */
} nhal_i2c_transfer_bit_flags_t;

/**
 * @brief I2C transfer operation structure
 *
 * Structure describing a single I2C message segment within a transaction.
 * A full I2C transaction can consist of one or more such messages.
 */
typedef struct {
    nhal_i2c_op_t type;
    nhal_i2c_address_t address;             /**< 7-bit or 10-bit address for this message segment.
                                    *   The high bit (0x80) is not used for 7-bit addresses here;
                                    *   it's strictly the 7-bit address (0-127). */
    uint16_t flags;            /**< Combination of #nhal_i2c_transfer_bit_flags_t for this segment. */
    /**
     * @brief Union to hold data specific to either a read or a write operation.
     *
     * Only one of these members should be accessed based on the type field.
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
