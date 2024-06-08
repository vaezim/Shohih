# Executable path: ../output/exe/shohih
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(piece)
add_subdirectory(board)

target_link_libraries(
    ${PROJECT_NAME}
    piece
    board
)