cmake_minimum_required(VERSION 3.16)

# Project info
project(FPR_LIB VERSION 0.0)

# Settings
set(LLVM_BUILD_DIR /home/shinjitumala/E_DRIVE/TiTech/tools/build/llvm/11-init)
set(LLVM_SRC_DIR /home/shinjitumala/E_DRIVE/TiTech/tools/llvm-project)

set(CMAKE_C_COMPILER ${LLVM_BUILD_DIR}/bin/clang)
set(CMAKE_CXX_COMPILER ${LLVM_BUILD_DIR}/bin/clang++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
   -Wall
)

add_library(FPR)
add_definitions(-DDEBUG)
target_include_directories(FPR
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
set_property(TARGET FPR PROPERTY POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)