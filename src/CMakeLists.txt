# Executable path: ../output/exe/shohih
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(piece)

# Add include directories
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${CMAKE_SOURCE_DIR}/src/include
)