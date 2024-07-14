# Add gtest headers
include_directories(
    ${GTEST_INCLUDE}
    ${RAYLIB_INCLUDE}
)

# Add test source files
file(
    GLOB TEST_SRC
    "./board/*.cpp"
    "./common/*.cpp"
    "./game/*.cpp"
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
    raylib
)