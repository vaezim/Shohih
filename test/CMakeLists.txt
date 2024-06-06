# Executable path: ../output/exe/test
set(TEST_TARGET test)
add_executable(${TEST_TARGET} main.cpp)

# Add include directories
target_include_directories(
    ${TEST_TARGET}
    PUBLIC ${CMAKE_SOURCE_DIR}/src/include
)