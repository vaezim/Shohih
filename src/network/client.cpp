/**************************************************
 * @date    2024-07-20
 * @brief   Shohih Client Implementation
 **************************************************/

#include <sstream>
#include "client.h"

namespace Shohih {

/**************************************************
 * @details
 *      Client constructor. Registers to the server
 *      gets the player's color
 **************************************************/
Client::Client(const std::string &addr) : httplib::Client(addr), m_addr(addr)
{
    // Register to the server
    auto resp = Get("/register");
    // Check connection status
    if (resp.error() == httplib::Error::Connection) {
        ERROR_LOG("Failed to connect to Shohih server (" << addr << ")");
        assert(resp.error() != httplib::Error::Connection);
    }
    // Check status code
    if (resp->status == 200) {
        INFO_LOG("Successfully connected to Shohih server (" << addr << ")");
    } else {
        ERROR_LOG("Failed to register to Shohih server (" << addr << ")");
        ERROR_LOG("Server returned status code " << resp->status);
    }
    // Set player's color
    std::string playerColor = resp->body;
    if (UNLIKELY(playerColor == "fail")) {
        ERROR_LOG("Failed to register to the server. Server is already serving 2 clients");
    } else if (playerColor == "white") {
        m_playerColor = PieceColor::WHITE;
    } else if (playerColor == "black") {
        m_playerColor = PieceColor::BLACK;
    }
}

/**************************************************
 * @details
 *      Sends /exit request to server.
 **************************************************/
void Client::Exit()
{
    Get("/exit");
}

/**************************************************
 * @details
 *      Client sends an http request to /getmove directory
 *      of server. If an invalid or previous move is returned,
 *      client waits for 0.1 seconds and send another request.
 **************************************************/
Move Client::GetMove()
{
    auto resp = Get("/getmove");
    std::string move_str = resp->body;
    auto separator = move_str.find('-');
    // move_str does not contain separator '-'
    if (UNLIKELY(separator == std::string::npos)) {
        return NULL_MOVE;
    }
    // server returned "null-null"
    std::string sq1_str = move_str.substr(0, separator);
    std::string sq2_str = move_str.substr(separator + 1);
    if (UNLIKELY(sq1_str == "null" || sq2_str == "null")) {
        return NULL_MOVE;
    }
    return Move {
        Square::GetSquareByName(sq1_str),
        Square::GetSquareByName(sq2_str)
    };
}

/**************************************************
 * @details
 *      Client posts the move to /sendmove dir of
 *      server inside request body with plain text format.
 **************************************************/
void Client::SendMove(const Move &move)
{
    if (move == m_lastMove) {
        return;
    }
    std::stringstream move_ss;
    if (UNLIKELY(!move.first.IsValid() || !move.second.IsValid())) {
        move_ss << "null-null";
    } else {
        move_ss << move.first.GetSquareName() << "-"
                << move.second.GetSquareName();
    }
    Post("/sendmove", move_ss.str(), "text/plain");
    m_lastMove = move;
}

} // namespace Shohih