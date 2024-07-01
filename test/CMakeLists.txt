# Add gtest headers
include_directories(
    PUBLIC
    ${CMAKE_SOURCE_DIR}/third_party/googletest/googletest/include
)

# Add test source files
file(
    GLOB TEST_SRC
    "./board/*.cpp"
    "./common/*.cpp"
    "./piece/*.cpp"
)

# Executable path: ../output/exe/test
set(TEST_TARGET test)
add_executable(${TEST_TARGET} main.cpp ${TEST_SRC})

# Link with Shohih library and gtest
target_link_libraries(
    ${TEST_TARGET}
    ${SHOHIH_LIB}
    gtest
)