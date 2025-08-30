# Nexus HAL Interface

## Overview

The NHAL Interface is a pure C header-only component that aims to define hardware abstraction layer interfaces for embedded systems. This component provides no implementation - only interface definitions, types, and contracts that implementation layers must fulfill. 

It's part of [nexus-embedded-ecosystem](https://github.com/Fo-Zi/nexus-embedded-ecosystem) ← You can find more documentation and references to other components here

## Goals
My main goal is simply to provide a set of interfaces **for myself**, and ease the pain points I mentioned before. That said, if someone else 
finds it useful is most welcomed to use it, collaborate, ask for some functionality or interface not yet contemplated, etc.

The goals as an interface are the following:
- To provide a set of interfaces isolated from their actual implementation:
  - Do you want to use your own implementation instead of some other provided by me? Go ahead!
  - Do you want to still use drivers implemented using the interface? You can!
- The HAL serves merely as **a contract** between drivers and the interfaces they depend on.
- To provide easy testability for higher layers.
- To be as clear as possible on separating the parts of the interface that are truly generic, from the ones that may depend on the platform you will be working with.
- If the functionality of the same peripheral may vary a lot depending on configuration (i.e.: async/DMA vs blocking), a **separate interface** will be defined exposing these.
  Forcing a consumer to initializa DMA data when only wanting to use a simple I2C blocking operation, breaks SOLID principles. 

## Design Philosophy

### Context-Based Architecture
The interface is built around the concept of "contexts" rather than direct peripheral addressing. Instead of passing bus numbers or channel IDs, all operations work with context structures that encapsulate:
- Peripheral identification and configuration
- Runtime state management  
- Platform-specific implementation details (opaque to consumers)

### State Management
All peripherals follow a the following lifecycle:
1. **Uninitialized** → **Initialized** (via `*_init()`)
2. **Initialized** → **Configured** (via `*_set_config()`)  
3. **Configured** → **Operational** (ready for data operations)

Operations will fail with appropriate error codes if attempted in wrong states.
Why do I follow this pattern? Because depending on the platform, the initialization phase follows a different flow than
the configuration step, and sometimes you may want to update peripheral configuration **at runtime**.

### Unified Error Handling
All operations return `nhal_result_t` with standardized error categories:
- **Argument/validation errors**: `NHAL_ERR_INVALID_ARG`, `NHAL_ERR_INVALID_CONFIG`
- **State errors**: `NHAL_ERR_NOT_INITIALIZED`, `NHAL_ERR_NOT_CONFIGURED`, `NHAL_ERR_BUSY`
- **Operation errors**: `NHAL_ERR_TIMEOUT`, `NHAL_ERR_HW_FAILURE`, `NHAL_ERR_UNSUPPORTED`
- **Communication errors**: `NHAL_ERR_NO_RESPONSE`, `NHAL_ERR_TRANSMISSION_ERROR`
- **Resource errors**: `NHAL_ERR_BUFFER_FULL`, `NHAL_ERR_OUT_OF_MEMORY`

The kind of errors the hal defines are up for debate and extension, of course.

## Supported Peripherals

### I2C Master
- **Basic Operations**: `nhal_i2c_master.h` - Read/write operations
- **Advanced Transfers**: `nhal_i2c_transfer.h` - Complex transaction support
- **Async Operations**: `nhal_i2c_master_async.h` - Non-blocking operations
- **Types**: `nhal_i2c_types.h`

### SPI Master  
- **Synchronous Operations**: `nhal_spi_master.h` - Blocking read/write/exchange
- **Async Operations**: `nhal_spi_master_async.h` - DMA-based operations
- **Daisy Chain**: `nhal_spi_daisy_chain.h` - Multi-device chaining
- **Types**: `nhal_spi_types.h`

### UART
- **Basic Operations**: `nhal_uart_basic.h` - Synchronous read/write
- **Async Operations**: `nhal_uart_async.h` - Buffered, non-blocking I/O
- **Types**: `nhal_uart_types.h`

### GPIO/Pin Control
- **Pin Operations**: `nhal_pin.h` - State control, interrupts, configuration
- **Types**: `nhal_pin_types.h`

### Watchdog Timer
- **WDT Control**: `nhal_wdt.h` - Initialization, feeding, enable/disable
- **Types**: `nhal_wdt_types.h`

### Common
- **Core Types**: `nhal_common.h` - Result types, delays, common definitions

## Interface Design Patterns

### Configuration Separation
Public interfaces expose only commonly-needed configuration parameters. Platform-specific configuration is handled through opaque `impl_config` pointers, allowing implementations to extend functionality without interface changes.

### Operation Modes
Many peripherals support multiple operation modes:
- **Sync-Only**: Minimal footprint, blocking operations only
- **Sync-and-Async**: Full feature set with both blocking and non-blocking operations

### Timeout Handling
All blocking operations accept timeout parameters (`nhal_timeout_ms`) for predictable behavior in real-time systems.

### Memory Management
The interface assumes:
- Context structures are allocated and managed by the application
- Implementation-specific data is managed internally by the implementation layer
- No dynamic allocation requirements imposed on applications

## Repository Contents

This repository contains:

### Interface Definitions
- **`include/`** - Pure C header files defining hardware abstraction interfaces
  - Peripheral interfaces (I2C, SPI, UART, GPIO, WDT)
  - Common types and error handling
  - No implementation dependencies

### West Extension Commands  
- **`scripts/`** - West build system integration for the Nexus Ecosystem
  - `west-commands.yml` - Command definitions
  - `nexus_commands/` - Python command implementations
  - Unified build/flash workflow across project types
  - Extensible runner system for custom flash tools

### Testing Support
- **`testing/`** - GoogleTest mock implementations for unit testing
- Mock classes for all peripheral interfaces

### Documentation Tools
- **`docs-utils/`** - Doxygen configuration and build scripts
- **`build-docs.sh`** - Automated documentation generation

## Dependencies

This interface component only depends on std C headers - it consists entirely of headers files defining:
- Function signatures
- Type definitions  
- Enumeration values
- Structure layouts (with opaque implementation-specific members)

## Integration

Include the appropriate headers for your peripheral needs:

```c
#include "nhal_common.h"     // Always required
#include "nhal_i2c_master.h" // For I2C operations
#include "nhal_spi_master.h" // For SPI operations  
#include "nhal_uart_basic.h" // For UART operations
#include "nhal_pin.h"        // For GPIO operations
#include "nhal_wdt.h"        // For watchdog operations
```

## Implementation Requirements

Any implementation of these interfaces must:
1. Provide concrete definitions for all `impl_*` structures (Empty if not needed)
2. Implement all declared functions with documented behavior
3. Follow the state management lifecycle
4. Return appropriate error codes for all failure conditions
5. Handle context validation (NULL checks, state checks)
The interface will be versioned to allow drivers to depend on a fixed "snapshot" of the contract, in case of
wanting to expand or modify it. Ideally, this HAL will be long-term stable, but since at the beggining I will
need to experiment a lot in order to reach an API that's comfortable to use while portable, versioning will move
fast until I reach v1.0.0.
