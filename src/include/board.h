/**************************************************
 * @date    2024-06-05
 * @brief   Chess board
 **************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "piece.h"
#include "shohih_defs.h"

namespace Shohih {

class Board {
public:
    Board() {}
    ~Board() = default;

    // Piece setter
    ErrorCode SetPieceOnSquare(
        std::shared_ptr<Piece> piece, Square suquare);
    // Piece getter
    std::shared_ptr<Piece> GetPieceBySquare(Square square);

private:
    std::array<std::array<
        std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> m_pieces{};
};

} // namespace Shohih

#endif // BOARD_H