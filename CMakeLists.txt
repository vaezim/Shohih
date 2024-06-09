cmake_minimum_required(VERSION 3.0)
project(shohih)

# Shohih lib & executable
set(SHOHIH_LIB shohih)
set(SHOHIH_MAIN shohih_main)

# Executables at ./output/exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/exe)

# Libraries at ./output/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    PUBLIC ${CMAKE_SOURCE_DIR}/src/include
)

# Link directories
link_directories(
    PUBLIC ${CMAKE_SOURCE_DIR}/output/lib
)

# Source files
add_subdirectory(src)

# Test cases
add_subdirectory(test)