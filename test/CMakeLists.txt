# Add third-party library headers
include_directories(
    ${GTEST_INCLUDE}
    ${RAYLIB_INCLUDE}
    ${HTTPLIB_INCLUDE}
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

# Link with Shohih and third-party libraries
target_link_libraries(
    ${TEST_TARGET}
    ${SHOHIH_LIB}
    gtest
    raylib
)

# Executables for test_server and test_client
add_executable(test_server ./network/test_server.cpp)
add_executable(test_client ./network/test_client.cpp)
target_link_libraries(test_server ${SHOHIH_LIB})
target_link_libraries(test_client ${SHOHIH_LIB} gtest)
