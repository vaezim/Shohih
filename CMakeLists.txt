cmake_minimum_required(VERSION 3.0)
project(shohih)

# Flag for building tests (OFF by default)
option(BUILD_TEST "Turn ON/OFF building test files" OFF)

# Shohih lib & executable
set(SHOHIH_LIB shohih)
set(SHOHIH_MAIN shohih_main)

# Executables at ./output/exe
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/exe)

# Libraries at ./output/lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/output/lib)

# GoogleTest requires >=C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GCC flags
set(CMAKE_CXX_FLAGS 
    "-Wall -Werror -Wextra -Wshadow -Wnon-virtual-dtor -Wunused -pedantic"
)

# Third-party libraries
set(RAYLIB_INCLUDE ${CMAKE_SOURCE_DIR}/third_party/raylib/src)
set(HTTPLIB_INCLUDE ${CMAKE_SOURCE_DIR}/third_party/cpp-httplib)
set(GTEST_INCLUDE ${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include)

# Include directories
include_directories(
    PUBLIC ${CMAKE_SOURCE_DIR}/src/include
)

# Link directories
link_directories(
    PUBLIC ${CMAKE_SOURCE_DIR}/output/lib
)

# Test cases
if(BUILD_TEST)
    add_subdirectory(test)
    add_compile_definitions(BUILD_TEST)
endif(BUILD_TEST)

# Source files
add_subdirectory(src)

# Third-party libraries
add_subdirectory(third_party)