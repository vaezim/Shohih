/**************************************************
 * @date    2024-06-06
 * @brief   Queen
 **************************************************/

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

namespace Shohih {

class Queen : public Piece {
public:
    Queen(std::shared_ptr<const Board> board=nullptr) : 
        Piece(board) { m_pieceType = PieceType::QUEEN; }
    virtual ~Queen() = default;

    std::vector<Move> GetAvailableMoves() const override;
};

} // namespace Shohih

#endif // QUEEN_H