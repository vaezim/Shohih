# Build gtest static library
set(GTEST_TARGET gtest)
add_library(${GTEST_TARGET} gtest-all.cc)

target_include_directories(
    ${GTEST_TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)