/**
 * @file nhal_spi_types.h
 * @brief Defines common types and structures for the SPI Hardware Abstraction Layer (HAL).
 *
 * This header file provides opaque types, enumerations, and structures used across
 * the SPI HAL API to facilitate communication over SPI buses.
 */
#ifndef NHAL_SPI_TYPES_H
#define NHAL_SPI_TYPES_H

#include <stddef.h>
#include <stdint.h>

#include "nhal_common.h"

/**
 * @brief SPI context structure (implementation-defined)
 *
 * Contains platform-specific SPI identification and runtime state.
 * Must include unique bus identification and any shared resources.
 *
 * @par Example content:
 * @code
 * struct nhal_spi_context {
 *     // Bus identification: SPI index OR peripheral name OR base address
 *     uint8_t spi_id;
 *     // Shared resources: mutex for bus access, chip select management, etc.
 *     mutex_t *bus_lock;
 * };
 * @endcode
 */
struct nhal_spi_context;

/**
 * @brief SPI duplex mode configuration
 */
typedef enum {
    NHAL_SPI_FULL_DUPLEX = 0, /**< Most platforms use FULL by default, but they also expose HALF */
    NHAL_SPI_HALF_DUPLEX,
} nhal_spi_duplex_t;

/**
 * @brief SPI clock polarity and phase mode configuration
 */
typedef enum {
    NHAL_SPI_MODE_0 = 0,    /**< CPOL=0, CPHA=0: Clock idle low, data sampled on rising edge */
    NHAL_SPI_MODE_1,        /**< CPOL=0, CPHA=1: Clock idle low, data sampled on falling edge */
    NHAL_SPI_MODE_2,        /**< CPOL=1, CPHA=0: Clock idle high, data sampled on falling edge */
    NHAL_SPI_MODE_3,        /**< CPOL=1, CPHA=1: Clock idle high, data sampled on rising edge */
} nhal_spi_mode_t;

/**
 * @brief SPI bit transmission order configuration
 */
typedef enum {
    NHAL_SPI_BIT_ORDER_MSB_FIRST = 0,    /**< Most significant bit first */
    NHAL_SPI_BIT_ORDER_LSB_FIRST,        /**< Least significant bit first */
} nhal_spi_bit_order_t;

/**
 * @brief SPI configuration structure
 */
struct nhal_spi_config{
    nhal_spi_duplex_t duplex;
    nhal_spi_mode_t mode;
    nhal_spi_bit_order_t bit_order;
    struct nhal_spi_impl_config * impl_config;
};

#endif /* NHAL_SPI_TYPES_H */
