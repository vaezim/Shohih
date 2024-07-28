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
    Client(const std::string &addr) : httplib::Client(addr), m_addr(addr) {}
    ~Client() = default;

    //--------------------------------------------------
    // Get the last move from the server
    //--------------------------------------------------
    Move GetMove();

    //--------------------------------------------------
    // Send the last move to the server
    //--------------------------------------------------
    void SendMove(const Move &move);

private:
    std::string m_addr;
};

} // namespace Shohih

#endif // CLIENT_H