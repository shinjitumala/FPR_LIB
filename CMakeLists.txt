cmake_minimum_required(VERSION 3.16)

# Information
project(
  libfpr
  VERSION 0.1
  LANGUAGES CXX
  DESCRIPTION "FPR's C++ library for personal use.")

# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# The Library
add_library(libfpr STATIC)
target_compile_features(libfpr PRIVATE cxx_std_20)
target_include_directories(libfpr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(libfpr PRIVATE -Wall -fno-exceptions -fno-rtti -g3 -O3)

# Test
add_executable(test src/test.cpp)
target_compile_features(test PRIVATE cxx_std_20)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(test PRIVATE -Wall -fno-exceptions -fno-rtti -g3 -O3)

# Packaging
export(TARGETS libfpr FILE ${CMAKE_CURRENT_BINARY_DIR}/libfprConfig.cmake)

# sources
target_sources(libfpr PUBLIC src/util/fdstreambuf.cpp)
