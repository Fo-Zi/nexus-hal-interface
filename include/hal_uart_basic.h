/**
 * @file hal_uart_basic.h
 * @brief Hardware Abstraction Layer (HAL) for UART communication.
 *
 * This header defines the public interface for interacting with Universal Asynchronous Receiver-Transmitter (UART)
 * peripherals through a Hardware Abstraction Layer. It provides common data types, configuration structures,
 * and functions for initializing, deinitializing, configuring, writing to, and reading from UART instances.
 *
 * The HAL aims to abstract away the underlying hardware specifics, allowing application code to be
 * portable across different microcontroller platforms while providing a consistent API for UART operations.
 *
 * @note Implementation-specific details are handled via opaque pointers within context and configuration
 *       structures, allowing for flexible hardware integration.
 */

#ifndef HAL_UART_H
#define HAL_UART_H

#include <stddef.h>
#include <stdint.h>

#include "hal_uart_types.h"

hal_uart_result_t hal_uart_init(hal_uart_context_t * uart_ctxt);
hal_uart_result_t hal_uart_deinit(hal_uart_context_t * uart_ctxt);
hal_uart_result_t hal_uart_set_config(hal_uart_context_t * uart_ctxt, hal_uart_config_t *cfg);
hal_uart_result_t hal_uart_get_config(hal_uart_context_t * uart_ctxt, hal_uart_config_t *cfg);
hal_uart_result_t hal_uart_write(hal_uart_context_t * uart_ctxt, const uint8_t *data, size_t len);
hal_uart_result_t hal_uart_read(hal_uart_context_t * uart_ctxt, uint8_t *data, size_t len);

#endif
