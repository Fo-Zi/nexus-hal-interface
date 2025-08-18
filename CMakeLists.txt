# Define the path to the include directory
set(NHAL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# 1. Create an interface library for the NHAL headers
# This makes it easy for other targets to consume the headers without
# needing to specify include directories individually.
add_library(my_basic_NHAL INTERFACE)

# Specify the include directories for the interface library
target_include_directories(my_basic_NHAL INTERFACE
    ${NHAL_INCLUDE_DIR}
)
