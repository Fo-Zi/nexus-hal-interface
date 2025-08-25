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

# Get version from git tags
find_package(Git QUIET)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --always --dirty
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE PROJECT_VERSION_FULL
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    # Use full git describe output, preserving vX.Y.Z format
    if(PROJECT_VERSION_FULL)
        set(PROJECT_VERSION "${PROJECT_VERSION_FULL}")
    else()
        set(PROJECT_VERSION "unknown")
        set(PROJECT_VERSION_FULL "unknown")
    endif()
else()
    set(PROJECT_VERSION "unknown")
    set(PROJECT_VERSION_FULL "unknown")
endif()

message(STATUS "Project version: ${PROJECT_VERSION} (${PROJECT_VERSION_FULL})")

# Documentation generation with Doxygen
option(BUILD_DOCS "Build API documentation with Doxygen" OFF)

if(BUILD_DOCS)
    find_package(Doxygen)
    
    if(DOXYGEN_FOUND)
        message(STATUS "Doxygen found: ${DOXYGEN_EXECUTABLE}")
        
        # Set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs-utils/Doxyfile)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        set(DOCS_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)
        
        # Configure the Doxyfile with CMake variables (including PROJECT_VERSION)
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        
        # Add the docs target
        add_custom_target(docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen (version ${PROJECT_VERSION})"
            VERBATIM
        )
        
        message(STATUS "Documentation target 'docs' configured with version ${PROJECT_VERSION}")
        message(STATUS "Run 'make docs' or 'cmake --build . --target docs' to generate documentation")
    else()
        message(WARNING "Doxygen not found. Documentation will not be available.")
        message(STATUS "Install doxygen to enable documentation generation")
    endif()
else()
    message(STATUS "Documentation generation disabled. Use -DBUILD_DOCS=ON to enable.")
endif()
