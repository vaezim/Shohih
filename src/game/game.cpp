/**************************************************
 * @date    2024-06-25
 * @brief   Game manager implementation
 **************************************************/

#include "game.h"

namespace Shohih {

/**************************************************
 * @details
 *      Game's main API. Sets up board to 
 *          the standard starting position.
 *      - If game is already started, @return GAME_ALREADY_STARTED
 **************************************************/
ErrorCode Game::Play()
{
    if (UNLIKELY(gameStarted)) {
        ERROR_LOG("A game is already started. \
            Finish that game before starting a new one.");
        return GAME_ALREADY_STARTED;
    }
    static const std::string stdPosition {
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
    };
    Board::BuildBoardByFEN(m_board, stdPosition);
    gameStarted = true;
    return SUCCESS;
}

} // namespace Shohih