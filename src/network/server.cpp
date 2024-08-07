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
    Get("/register",
        [this](const httplib::Request &req, httplib::Response &resp) {
            this->RegisterClient(req, resp);
        }
    );

    Get("/exit",
        [this](const httplib::Request &req, httplib::Response &) {
            this->RemoveClient(req);
        }
    );

    Get("/getmove",     // client "gets" the move
        [this](const httplib::Request &, httplib::Response &resp) {
            this->SendMove(resp);
        }
    );

    Post("/sendmove",   // client "sends" the move
        [this](const httplib::Request &req, httplib::Response &) {
            this->ReceiveMove(req);
        }
    );
}

void Server::Listen()
{
    const std::string addr{ "0.0.0.0" };
    constexpr int port{ 8080 };
    INFO_LOG("Server is listening on " << addr << ":" << port);
    listen(addr, port);
}

/**************************************************
 * @details
 *      Register the client and choose its piece color
 **************************************************/
void Server::RegisterClient(const httplib::Request &req, httplib::Response &resp)
{
    if (UNLIKELY(m_numConnectedClients >= 2)) {
        ERROR_LOG("Server cannot serve more than 2 clients.");
        resp.body = "fail";
        return;
    }
    resp.body = (m_numConnectedClients == 0) ? "white" : "black";
    m_numConnectedClients++;
    INFO_LOG("Client with address " << req.remote_addr
        << " joined Shohih server [" << resp.body << "]");
}

/**************************************************
 * @details
 *      Decrement number of connected clients
 **************************************************/
void Server::RemoveClient(const httplib::Request &req)
{
    if (m_numConnectedClients > 0) {
        m_numConnectedClients--;
    }
    m_lastMove = NULL_MOVE;
    RED_INFO_LOG("Client with address "
        << req.remote_addr << " left Shohih server.");
}

/**************************************************
 * @details
 *      Server sends the last move in response body.
 *      Format: <square str>-<square str> (separated by a dash)
 **************************************************/
void Server::SendMove(httplib::Response &resp)
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
void Server::ReceiveMove(const httplib::Request &req)
{
    std::string move = req.body;
    auto separator = move.find('-');
    if (UNLIKELY(separator == std::string::npos)) {
        return;
    }
    auto src_sq_str = move.substr(0, separator);
    auto dst_sq_str = move.substr(separator + 1);
    if (UNLIKELY(src_sq_str == "null" || dst_sq_str == "null")) {
        return;
    }
    m_lastMove.first = Square::GetSquareByName(src_sq_str);
    m_lastMove.second = Square::GetSquareByName(dst_sq_str);
}

} // namespace Shohih