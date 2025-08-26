# Google Test Mocks for NHAL Interface
cmake_minimum_required(VERSION 3.10)
project(nhal_mocks_lib)

# Find required packages
find_package(GTest REQUIRED)

# Create the nhal_mocks library
add_library(nhal_mocks
    # Mock implementations
    src/nhal_uart_mock.cpp
    src/nhal_spi_mock.cpp
    src/nhal_i2c_mock.cpp
    src/nhal_pin_mock.cpp
    src/nhal_wdt_mock.cpp
)

# Set target properties
target_include_directories(nhal_mocks
    PUBLIC
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)

target_link_libraries(nhal_mocks
    PUBLIC
        GTest::gmock
        GTest::gtest
)

# Set C++ standard
target_compile_features(nhal_mocks PUBLIC cxx_std_11)

# Add compiler definitions for C linkage
target_compile_definitions(nhal_mocks PRIVATE
    NHAL_MOCK_ENABLED=1
    NHAL_SPI_ASYNC_SUPPORT=1
)

# Export the target for use by applications
add_library(nhal::mocks ALIAS nhal_mocks)