# Define the path to the include directory
set(HAL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# 1. Create an interface library for the HAL headers
# This makes it easy for other targets to consume the headers without
# needing to specify include directories individually.
add_library(my_basic_HAL INTERFACE)

# Specify the include directories for the interface library
target_include_directories(my_basic_HAL INTERFACE
    ${HAL_INCLUDE_DIR}
)
