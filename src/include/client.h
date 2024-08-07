/**************************************************
 * @date    2024-07-20
 * @brief   Shohih Client
 **************************************************/

#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include "httplib.h"
#include "shohih_defs.h"

namespace Shohih {

class Client : public httplib::Client {
public:
    Client(const std::string &addr);
    ~Client() = default;

    //--------------------------------------------------
    // Get the last move from the server
    //--------------------------------------------------
    Move GetMove();

    //--------------------------------------------------
    // Send the last move to the server
    //--------------------------------------------------
    void SendMove(const Move &move);

    //--------------------------------------------------
    // Leave the server
    //--------------------------------------------------
    void Exit();

    //--------------------------------------------------
    // Get player's piece color from server
    //--------------------------------------------------
    PieceColor GetPlayerColor() const { return m_playerColor; }

private:
    std::string m_addr;
    PieceColor m_playerColor;
    Move m_lastMove = NULL_MOVE;
};

} // namespace Shohih

#endif // CLIENT_H