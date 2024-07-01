/**************************************************
 * @date    2024-06-25
 * @brief   Game manager (Standard starting position)
 **************************************************/

#pragma once
#ifndef GAME_H
#define GAME_H

#include "board.h"

namespace Shohih {

class Game {
public:
    Game() = default;
    ~Game() = default;

    //--------------------------------------------------
    // Game main API
    //--------------------------------------------------
    ErrorCode Play();

private:
    void RunGUI();

    static bool g_isRunning;
    std::shared_ptr<Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // GAME_H