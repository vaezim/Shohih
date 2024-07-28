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
    void Listen() { listen("0.0.0.0", 8080); }

private:
    //--------------------------------------------------
    // Send the last move to clients
    //--------------------------------------------------
    void SendMove(const httplib::Request &, httplib::Response &);

    //--------------------------------------------------
    // Receive a move from clients
    //--------------------------------------------------
    void ReceiveMove(const httplib::Request &, httplib::Response &);

    //--------------------------------------------------
    // Last received move by the server
    //--------------------------------------------------
    Move m_lastMove{ NULL_SQUARE, NULL_SQUARE };
};

} // namespace Shohih

#endif // SERVER_H