/**************************************************
 * @date    2024-07-20
 * @brief   Shohih Server
 **************************************************/

#pragma once
#ifndef SERVER_H
#define SERVER_H

#include "httplib.h"
#include "shohih_defs.h"

namespace Shohih {

class Server : public httplib::Server {
public:
    Server();
    ~Server() = default;

    //--------------------------------------------------
    // Main server API
    //--------------------------------------------------
    void Listen();

private:
    //--------------------------------------------------
    // Manage clients
    //--------------------------------------------------
    void RemoveClient(const httplib::Request &req);
    void RegisterClient(const httplib::Request &req, httplib::Response &);

    //--------------------------------------------------
    // Send the last move to clients
    //--------------------------------------------------
    void SendMove(httplib::Response &);

    //--------------------------------------------------
    // Receive a move from clients
    //--------------------------------------------------
    void ReceiveMove(const httplib::Request &);

    //--------------------------------------------------
    // Last received move by the server
    //--------------------------------------------------
    Move m_lastMove = NULL_MOVE;

    //--------------------------------------------------
    // Number of connected clients (max = 2)
    // First client gets white, Second client get black
    //--------------------------------------------------
    uint8_t m_numConnectedClients{ 0 };
};

} // namespace Shohih

#endif // SERVER_H