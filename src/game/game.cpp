/**************************************************
 * @date    2024-06-25
 * @brief   Game manager implementation
 **************************************************/

#include "game.h"
#include "raylib.h"

namespace Shohih {

/**************************************************
 * Initialize Game's global isRunning variable.
 * This variable is shared among all Game classes
 * to prevent multiple games from starting simultaneously.
 **************************************************/
bool Game::g_isRunning = false;

/**************************************************
 * @details
 *      Game's main API. Sets up board to 
 *          the standard starting position.
 *      - If game is already started, @return GAME_ALREADY_STARTED
 **************************************************/
ErrorCode Game::Play()
{
    // Check if another game is running.
    if (UNLIKELY(g_isRunning)) {
        ERROR_LOG("Can't start a new game. Another one is already running.");
        return GAME_ALREADY_STARTED;
    }
    g_isRunning = true;

    // Standard chess starting position
    Board::BuildBoardByFEN(m_board, STANDARD_POSITION_FEN);

    // GUI
    RunGUI();

    // Play() only returns if game window
    // is closed and program is terminated.
    g_isRunning = false;
    return SUCCESS;
}

/**************************************************
 * @details
 *      Game's Graphical UI handler.
 **************************************************/
void Game::RunGUI()
{
    // Window size
    constexpr int WINDOW_WIDTH = 500;
    constexpr int WINDOW_HEIGHT = 500;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shohih!");

    // Board texture
    Image board_img = LoadImage("resources/board.png");
    ImageResize(&board_img, WINDOW_WIDTH, WINDOW_HEIGHT);
    Texture2D board_texture = LoadTextureFromImage(board_img);

    // Window drawing loop. Exit loop with
    // ESC key | Closing window | Ctrl+C
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);

            // Board texture
            DrawTexture(board_texture, 0, 0, WHITE);

            // Pieces
            
        EndDrawing();
    }

    CloseWindow();
}

} // namespace Shohih