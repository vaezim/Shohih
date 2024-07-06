/**************************************************
 * @date    2024-07-01
 * @brief   Graphical UI manager Implementation
 **************************************************/

#include "gui_manager.h"

namespace Shohih {

/**************************************************
 * Initialize paths to piece image files.
 **************************************************/
const std::array<const char*, NUM_PIECE_TYPES * NUM_PIECE_COLORS>
    GuiManager::m_pieceImgPaths {
    "resources/white_pawn.png",
    "resources/white_knight.png",
    "resources/white_bishop.png",
    "resources/white_rook.png",
    "resources/white_queen.png",
    "resources/white_king.png",
    "resources/black_pawn.png",
    "resources/black_knight.png",
    "resources/black_bishop.png",
    "resources/black_rook.png",
    "resources/black_queen.png",
    "resources/black_king.png",
};

/**************************************************
 * @details
 *      GUI manager's constructor.
 *      - @param board is a pointer to the underlying
 *          board object which contains the pieces and
 *          game logic. All updates that are recieved
 *          through GUI are sent to this object.
 **************************************************/
GuiManager::GuiManager(std::shared_ptr<Board> board) : m_board(board)
{
    // Initialize Raylib (must be called before other raylib functions)
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shohih!");

    // Board texture
    Image boardImg = LoadImage("resources/board.png");
    ImageResize(&boardImg, WINDOW_WIDTH, WINDOW_HEIGHT);
    m_boardTexture = LoadTextureFromImage(boardImg);

    // Piece Textures
    for (uint8_t pieceIdx{ 0 }; pieceIdx < NUM_PIECE_TYPES * NUM_PIECE_COLORS; pieceIdx++) {
        // Load PNG image from disk
        m_pieceImages[pieceIdx] = LoadImage(m_pieceImgPaths[pieceIdx]);
        // Resize it to 1/8 of window size
        ImageResize(&m_pieceImages[pieceIdx], WINDOW_WIDTH / BOARD_SIZE, WINDOW_HEIGHT / BOARD_SIZE);
        // Load piece texture from image
        m_pieceTextures[pieceIdx] = LoadTextureFromImage(m_pieceImages[pieceIdx]);
    }
}

/**************************************************
 * @details
 *      Game's Graphical UI handler.
 **************************************************/
void GuiManager::Run()
{
    // Window drawing loop. Exit loop with
    // ESC key | Closing window | Ctrl+C
    while (!WindowShouldClose()) {

        //---------------- GPU Access ----------------
        BeginDrawing();
            ClearBackground(BLACK);

            // Board texture
            DrawTexture(m_boardTexture, 0, 0, WHITE);

            // Pieces
            for (const auto &piece : m_board->GetPieceSet()) {
                if (UNLIKELY(piece == nullptr)) { continue; }
                Texture2D pieceTexture = GetPieceTexture(
                    piece->GetPieceColor(), piece->GetPieceType());
                auto pos = ConvertSquareToWindowPos(piece->GetPieceSquare());
                DrawTexture(pieceTexture, pos.first, pos.second, WHITE);
            }
        EndDrawing();
        //---------------- GPU Access ----------------
    }

    CloseWindow();
}

/**************************************************
 * @details
 *      Piece texture index = Color * 6 + type
 **************************************************/
Texture2D GuiManager::GetPieceTexture(PieceColor color, PieceType type)
{
    if (UNLIKELY(color == PieceColor::UNKNOWN || type == PieceType::UNKNOWN)) {
        ERROR_LOG("Failed to get piece texture. Piece type or color is unknown.");
        return Texture2D{};
    }
    uint8_t pieceIdx = 
        static_cast<uint8_t>(color) * NUM_PIECE_TYPES + static_cast<uint8_t>(type);
    return m_pieceTextures[pieceIdx];
}

/**************************************************
 * @details
 *      Convert square coordinates to gui window positions
 **************************************************/
std::pair<int, int> GuiManager::ConvertSquareToWindowPos(Square sq) const
{
    int posX = sq.x * WINDOW_WIDTH / BOARD_SIZE;
    int posY = (BOARD_SIZE - sq.y - 1) * WINDOW_HEIGHT / BOARD_SIZE;
    return { posX, posY };
}

} // namespace Shohih