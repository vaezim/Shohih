/**************************************************
 * @date    2024-06-25
 * @brief   Game manager (Standard starting position)
 **************************************************/

#pragma once
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "client.h"

namespace Shohih {

class Game {
public:
    Game(GameMode mode=GameMode::OFFLINE, std::string addr="");
    ~Game();

    //--------------------------------------------------
    // Game's main API
    //--------------------------------------------------
    ErrorCode Play();

private:
    static bool g_isRunning;
    std::shared_ptr<Board> m_board{ nullptr };

    //--------------------------------------------------
    // Game mode: Offline/Online
    // In online mode, <m_client> is initialized.
    //--------------------------------------------------
    GameMode m_gameMode{ GameMode::OFFLINE };
    std::shared_ptr<Client> m_client { nullptr };
};

} // namespace Shohih

#endif // GAME_H