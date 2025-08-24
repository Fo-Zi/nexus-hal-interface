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

typedef uint8_t nhal_spi_bus_id;


typedef enum {
    NHAL_SPI_MODE_0 = 0,    /**< CPOL=0, CPHA=0: Clock idle low, data sampled on rising edge */
    NHAL_SPI_MODE_1,        /**< CPOL=0, CPHA=1: Clock idle low, data sampled on falling edge */
    NHAL_SPI_MODE_2,        /**< CPOL=1, CPHA=0: Clock idle high, data sampled on falling edge */
    NHAL_SPI_MODE_3,        /**< CPOL=1, CPHA=1: Clock idle high, data sampled on rising edge */
} nhal_spi_mode_t;

typedef enum {
    NHAL_SPI_BIT_ORDER_MSB_FIRST = 0,    /**< Most significant bit first */
    NHAL_SPI_BIT_ORDER_LSB_FIRST,        /**< Least significant bit first */
} nhal_spi_bit_order_t;

struct nhal_spi_config{
    uint32_t frequency_hz;
    nhal_spi_mode_t mode;
    nhal_spi_bit_order_t bit_order;
    struct nhal_spi_impl_config * impl_config;
};

/**
 * @brief Configuration for asynchronous operations with DMA support
 */
struct nhal_spi_async_dma_config{
    struct nhal_spi_config basic_config;       /**< Basic SPI configuration */
    uint16_t max_transfer_sz;                  /**< Maximum transfer size in bytes for DMA */
    uint8_t dma_chan;                          /**< DMA channel to use (0 for auto-select) */
    uint8_t queue_size;                        /**< Transaction queue size for async operations */
};

typedef enum {
    NHAL_SPI_OP_MODE_SYNC_ONLY,        /**< Synchronous blocking operations only. */
    NHAL_SPI_OP_MODE_SYNC_AND_ASYNC    /**< Both synchronous and asynchronous operations with DMA support. */
} nhal_spi_operation_mode_t;

/**
 * @brief Base SPI context - always present, minimal footprint
 */
struct nhal_spi_context{
    nhal_spi_bus_id spi_bus_id;
    nhal_spi_operation_mode_t current_mode;
    uint32_t actual_frequency_hz;           /**< Actual configured frequency (may differ from requested) */
    
    struct nhal_spi_impl_ctx * impl_ctx;

    // Conditional extensions - only included if support is compiled in
#if defined(NHAL_SPI_ASYNC_DMA_SUPPORT)
    struct nhal_spi_async_dma_extension {
        uint16_t max_transfer_sz;
        uint8_t dma_chan;
        uint8_t queue_size;
        uint8_t tx_operations_queued;
        uint8_t rx_operations_available;
        bool is_async_initialized;
    } async_dma;
#endif
};

struct nhal_spi_daisy_device {
    const uint8_t *data;        /**< Data buffer for this device */
    size_t data_size;           /**< Size of data for this device in bytes */
    uint8_t bits_per_device;    /**< Number of bits per device (typically 8, 16, or 32) */
};

struct nhal_spi_daisy_config{
    uint8_t num_devices;                    /**< Number of devices in the daisy chain */
    uint8_t bits_per_device;                /**< Bits per device (must be same for all devices in chain) */
    struct nhal_spi_config basic_config;
};

struct nhal_spi_daisy_context{
    struct nhal_spi_context basic_ctx;
    uint8_t num_devices;                    /**< Number of devices in the daisy chain */
    uint8_t bits_per_device;                /**< Bits per device */
    size_t total_chain_bits;                /**< Total bits in the entire chain */
};

#endif /* NHAL_SPI_TYPES_H */
