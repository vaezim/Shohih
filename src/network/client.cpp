/**************************************************
 * @date    2024-07-20
 * @brief   Shohih Client Implementation
 **************************************************/

#include <sstream>
#include "client.h"

namespace Shohih {

/**************************************************
 * @details
 *      Client sends an http request to /getmove dir
 *      of server. Parses the move from the response body.
 **************************************************/
Move Client::GetMove()
{
    auto resp = Get("/getmove");
    std::string move_str = resp->body;
    auto separator = move_str.find('-');
    if (UNLIKELY(separator == std::string::npos)) {
        return Move{ NULL_SQUARE, NULL_SQUARE };
    }
    std::string sq1_str = move_str.substr(0, separator);
    std::string sq2_str = move_str.substr(separator + 1);
    if (UNLIKELY(sq1_str == "null" || sq2_str == "null")) {
        return Move { NULL_SQUARE, NULL_SQUARE };
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
    std::stringstream move_ss;
    move_ss << move.first.GetSquareName() << "-"
            << move.second.GetSquareName();
    Post("/sendmove", move_ss.str(), "text/plain");
}

} // namespace Shohih