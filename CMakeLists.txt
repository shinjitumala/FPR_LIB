cmake_minimum_required(VERSION 3.16)

# Information
project(
    FPR_LIB
    VERSION 0.1
    LANGUAGES CXX
    DESCRIPTION "FPR's C++ library for personal use."
)

# Settings
## C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## Used by clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
   -Wall
   -fno-exceptions
   -fno-rtti
)

add_library(FPR)
add_definitions(-DDEBUG)
target_include_directories(FPR
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_property(TARGET FPR PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)