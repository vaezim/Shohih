# Executable path: ../output/exe/shohih
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(piece)

target_link_libraries(
    ${PROJECT_NAME}
    piece
)