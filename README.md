# NHAL Interface

## Overview

The NHAL Interface is a pure C header-only component that aims to define hardware abstraction layer interfaces for embedded systems. This component provides no implementation - only interface definitions, types, and contracts that implementation layers must fulfill.

## Motivation
My motivation is centered around issues I've faced in my experience when working with Embedded Projects:
- Many HALs are not designed to ease testability -> I'd end up creating my own shim abstraction layer for every project, just to allow me to unit-test a complex driver or other components.
- Most HALs tie you to a specific MCU family/Framework/SDK -> Porting efforts if I want to for example use the same peripheral but in some other platform
- Some HALs try to abstract everything, creating huge complex dependencies -> An overkill for many projects
- HALs for RTOS and Bare metal are radically different, but **usually** the functionality most drivers need remains the same

## Goals
My main goal is simply to provide a set of interfaces **for myself**, and ease the pain points I mentioned before. That said, if someone else 
finds it useful is most welcomed to use it, collaborate, ask for some functionality or interface not yet contemplated, etc.

The goals as an interface are the following:
- To provide a set of interfaces isolated from their actual implementation:
  - Do you want to use your own implementation instead of some other provided by me? Go ahead!
  - Do you want to still use drivers implemented using the interface? You can!
- The HAL serves merely as **a contract** between drivers and the interfaces they depend on
- To provide easy testability for higher layers
- To be as clear as possible on separating the parts of the interface that are truly generic, from the ones that may depend on the platform you will be working with
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

## Dependencies

This interface component has **no dependencies** - it consists entirely of C header files defining:
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
1. Provide concrete definitions for all `impl_*` structures
2. Implement all declared functions with documented behavior
3. Follow the state management lifecycle
4. Return appropriate error codes for all failure conditions
5. Handle context validation (NULL checks, state checks)
6. Support the timeout semantics for blocking operations

The interface will be versioned to allow drivers to depend on a fixed "snapshot" of the contract, in case of
wanting to expand or modify it. Ideally, this HAL will be long-term stable, but since at the beggining I will
need to experiment a lot in order to reach an API that's comfortable to use while portable, versioning will move
fast until I reach v1.0.0.
