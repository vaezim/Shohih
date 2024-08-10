/**************************************************
 * @date    2024-07-01
 * @brief   Graphical UI manager Implementation
 **************************************************/

#include <cmath>
#include "gui_manager.h"

namespace Shohih {

/**************************************************
 * Initialize paths to image files.
 **************************************************/
const char *GuiManager::g_boardImgPath = "resources/board.png";
const std::array<const char*, NUM_PIECE_TYPES * NUM_PIECE_COLORS>
    GuiManager::g_pieceImgPaths {
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
    // Set Raylib log level to warnings, errors & fatal only
    SetTraceLogLevel(LOG_WARNING);

    // Initialize Raylib (must be called before other raylib functions)
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shohih!");

    // Board texture
    Image boardImg = LoadImage(g_boardImgPath);
    ImageResize(&boardImg, WINDOW_WIDTH, WINDOW_HEIGHT);
    m_boardTexture = LoadTextureFromImage(boardImg);

    // Piece Textures
    for (uint8_t pieceIdx{ 0 }; pieceIdx < NUM_PIECE_TYPES * NUM_PIECE_COLORS; pieceIdx++) {
        // Load PNG image from disk
        m_pieceImages[pieceIdx] = LoadImage(g_pieceImgPaths[pieceIdx]);
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
    // Client/Server communication handler
    std::shared_ptr<std::thread> serverHandler;
    if (m_board->GetGameMode() == GameMode::ONLINE) {
        serverHandler = std::make_shared<std::thread>(&GuiManager::SyncWithServer, this);
    }

    // Window drawing loop. Exit loop with
    // ESC key | Closing window | Ctrl+C
    while (!WindowShouldClose()) {
        //---------------- GPU Access ----------------
        BeginDrawing();
            ClearBackground(BLACK);

            // Board texture
            DrawTexture(m_boardTexture, 0, 0, WHITE);

            // Piece textures
            DrawPieceTextures();

            // Handle mouse clicks
            HandleMouseClicks();

            // Draw circles on marked squares
            DrawMarkedSquareCircles();

        EndDrawing();
        //---------------- GPU Access ----------------
    }

    CloseWindow();
    if (serverHandler != nullptr) {
        serverHandler->join();
    }
}

/**************************************************
 * @details
 *      Handle mouse clicks.
 *      - Show available moves of a piece when mouse
 *          clicks on it.
 *      - If one of the available moves was selected,
 *          Move the piece to that square.
 **************************************************/
void GuiManager::HandleMouseClicks()
{
    // Return if mouse click is not detected.
    if (!IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) { return; }

    // Get mouse position and convert it to a Square
    GuiWindowPos mousePos { GetMouseX(), GetMouseY() };
    Square sq = ConvertWindowPosToSquare(mousePos);

    // If clicked square is a marked square and last clicked
    // square has a piece on it, move the piece to the clicked square
    if (m_markedSquares.count(sq) != 0 &&
        !m_board->IsEmptySquare(m_lastClickedSquare)) {
        m_board->MovePiece(m_lastClickedSquare, sq);
        m_markedSquares.clear();
        m_lastClickedSquare = sq;
        return;
    }

    // Update last clicked square
    m_lastClickedSquare = sq;

    // Clear the previously marked squares
    m_markedSquares.clear();

    // Get the piece on the clicked square
    if (m_board->IsEmptySquare(sq)) { return; }
    auto piece = m_board->GetPieceBySquare(sq);

    // Do not draw opponent's available squares (Online mode only)
    if (m_board->GetGameMode() == GameMode::ONLINE &&
        piece->GetPieceColor() != m_board->GetClientPieceColor()) { return; }

    // Mark available moves of <piece>
    for (const Square &avail_sq : piece->GetAvailableMoves()) {
        m_markedSquares.emplace(avail_sq);
    }
}

/**************************************************
 * @details
 *      Constantly checks the server for new moves
 *          and sends clients moves to the server.
 **************************************************/
void GuiManager::SyncWithServer() const
{
    auto client = m_board->GetClient();
    if (UNLIKELY(client == nullptr)) {
        ERROR_LOG("Failed to sync with server. Client is nullptr.");
        return;
    }
    while (!WindowShouldClose()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(threadSleepTime));
        // Send player's move to server
        // (we have made our move and its now opponent's turn)
        if (m_board->GetClientPieceColor() != m_board->GetPlayerTurn()) {
            client->SendMove(m_board->GetLastMove());
        }
        // Get opponent's move from server
        Move opponentMove = client->GetMove();
        // Update board
        if (LIKELY(opponentMove != NULL_MOVE) &&
            opponentMove != m_board->GetLastMove()) {
            m_board->MovePiece(opponentMove);
        }
    }
}

/**************************************************
 * @details
 *      Iterate marked squares and draw
 *          mini circles on them
 **************************************************/
void GuiManager::DrawMarkedSquareCircles() const
{
    // Dark green with 60% opacity
    static const Color circleColor { 0, 117, 44, 150 };
    for (const Square &sq : m_markedSquares) {
        GuiWindowPos pos = GetSquareCentrePosition(sq);
        DrawCircle(pos.x, pos.y, CIRCLE_RADIUS, circleColor);
    }
}

/**************************************************
 * @details
 *      Draw textures of pieces
 **************************************************/
void GuiManager::DrawPieceTextures() const
{
    for (const auto &piece : m_board->GetPieceSet()) {
        if (UNLIKELY(piece == nullptr)) { continue; }
        Texture2D pieceTexture = GetPieceTexture(
            piece->GetPieceColor(), piece->GetPieceType());
        auto pos = ConvertSquareToWindowPos(piece->GetPieceSquare());
        DrawTexture(pieceTexture, pos.x, pos.y, WHITE);
    }
}

/**************************************************
 * @details
 *      Piece texture index = Color * 6 + type
 **************************************************/
Texture2D GuiManager::GetPieceTexture(PieceColor color, PieceType type) const
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
 *      Calculate the position of the square's centre
 **************************************************/
GuiWindowPos GuiManager::GetSquareCentrePosition(Square sq)
{
    GuiWindowPos pos = ConvertSquareToWindowPos(sq);
    pos.x += SQUARE_SIZE / 2;
    pos.y += SQUARE_SIZE / 2;
    return pos;
}

/**************************************************
 * @details
 *      Convert square coordinates to gui window positions
 *      Returns the position of the top left corner 
 **************************************************/
GuiWindowPos GuiManager::ConvertSquareToWindowPos(Square sq)
{
    int posX = sq.x * WINDOW_WIDTH / BOARD_SIZE;
    int posY = (BOARD_SIZE - sq.y - 1) * WINDOW_HEIGHT / BOARD_SIZE;
    return GuiWindowPos{ posX, posY };
}

/**************************************************
 * @details
 *      Convert gui window positions to square coordinates
 **************************************************/
Square GuiManager::ConvertWindowPosToSquare(GuiWindowPos pos)
{
    uint8_t x = static_cast<uint8_t>(std::floor(
        static_cast<float>(pos.x) / (WINDOW_WIDTH / BOARD_SIZE)));
    uint8_t y = static_cast<uint8_t>(std::floor(
        static_cast<float>(pos.y) / (WINDOW_HEIGHT / BOARD_SIZE)));
    y = BOARD_SIZE - y - 1;
    return Square{ x, y };
}

} // namespace Shohih