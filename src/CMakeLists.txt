# Executable: shohih
add_executable(${PROJECT_NAME} shohih.cpp)

# Add include directories
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)