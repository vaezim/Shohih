file(
    GLOB board_SRC
    "*.cpp"
)

add_library(board ${board_SRC})