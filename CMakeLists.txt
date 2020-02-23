cmake_minimum_required(VERSION 3.16)

# Information
project(
    libfpr
    VERSION 0.1
    LANGUAGES CXX
    DESCRIPTION "FPR's C++ library for personal use."
)

# Settings
## C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)

## Used by clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The Library
add_library(fprlog STATIC)
add_subdirectory(src)
set_target_properties(fprlog PROPERTIES
    VERSION 0.1
)
target_include_directories(fprlog
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(fprlog
    PRIVATE
        -Wall
        -fno-exceptions
        -fno-rtti
)

# Packaging
export(TARGETS fprlog FILE ${CMAKE_CURRENT_BINARY_DIR}/libfprConfig.cmake)