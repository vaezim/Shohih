/**************************************************
 * @date    2024-06-25
 * @brief   Game manager implementation
 **************************************************/

#include "game.h"
#include "gui_manager.h"

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

    // Standard chess starting position
    ErrorCode err = Board::BuildBoardByFEN(m_board, STANDARD_POSITION_FEN);
    if (UNLIKELY(err != SUCCESS || m_board == nullptr)) {
        return err;
    }
    g_isRunning = true;

    // GUI manager
    GuiManager guiMgr(m_board);
    guiMgr.Run();

    // Play() only returns if game window
    // is closed and program is terminated.
    g_isRunning = false;
    return SUCCESS;
}

} // namespace Shohih