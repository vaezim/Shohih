cmake_minimum_required(VERSION 3.0)
project(shohih)

# Executables at ./output/exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/exe)

# Libraries at ./output/lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)

# Source files
add_subdirectory(src)

# Test cases
add_subdirectory(test)