/**************************************************
 * @date    2024-07-20
 * @brief   Shohih Server Implementation
 **************************************************/

#include <sstream>
#include "server.h"

namespace Shohih {

/**************************************************
 * @details
 *      Server constructor: Registers handler functions
 *      for different HTTP request types (Get, Post, ...)
 **************************************************/
Server::Server() : httplib::Server()
{
    Get("/getmove",     // client "gets" the move
        [this](const httplib::Request &req, httplib::Response &resp) {
            this->SendMove(req, resp);
        }
    );

    Post("/sendmove",   // client "sends" the move
        [this](const httplib::Request &req, httplib::Response &resp) {
            this->ReceiveMove(req, resp);
        }
    );
}

/**************************************************
 * @details
 *      Server sends the last move in response body.
 *      Format: <square str>-<square str> (separated by a dash)
 **************************************************/
void Server::SendMove(const httplib::Request &, httplib::Response &resp)
{
    if (UNLIKELY(m_lastMove.first == NULL_SQUARE ||
                 m_lastMove.second == NULL_SQUARE)) {
        resp.body = "null-null";
        return;
    }
    std::stringstream move;
    move << m_lastMove.first.GetSquareName() << "-"
         << m_lastMove.second.GetSquareName();
    resp.body = move.str();
}

/**************************************************
 * @details
 *      Clients put their moves in request body.
 *      Format: <square str>-<square str> (separated by a dash)
 **************************************************/
void Server::ReceiveMove(const httplib::Request &req, httplib::Response &)
{
    std::string move = req.body;
    auto separator = move.find('-');
    if (UNLIKELY(separator == std::string::npos)) {
        return;
    }
    m_lastMove.first = Square::GetSquareByName(move.substr(0, separator));
    m_lastMove.second = Square::GetSquareByName(move.substr(separator + 1));
}

} // namespace Shohih