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
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

## Used by clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The Library
add_library(libfpr INTERFACE)
target_include_directories(libfpr INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Test
add_executable(test
    src/test.cpp
)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(test
    PRIVATE
        -Wall
        -fno-exceptions
        -fno-rtti
        -g3
        -O3
)

# Packaging
export(TARGETS libfpr FILE ${CMAKE_CURRENT_BINARY_DIR}/libfprConfig.cmake)