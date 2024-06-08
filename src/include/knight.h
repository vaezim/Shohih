/**************************************************
 * @date    2024-06-06
 * @brief   Knight
 **************************************************/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

namespace Shohih {

class Knight : public Piece {
public:
    Knight(std::shared_ptr<const Board> board=nullptr) : 
        Piece(board) { m_pieceType = PieceType::KNIGHT; }
    virtual ~Knight() = default;

    std::vector<Move> GetAvailableMoves() const override;
};

} // namespace Shohih

#endif // KNIGHT_H