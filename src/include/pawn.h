/**************************************************
 * @date    2024-06-06
 * @brief   Pawn
 **************************************************/

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

namespace Shohih {

class Pawn : public Piece {
public:
    Pawn(std::shared_ptr<const Board> board=nullptr) : 
        Piece(board) { m_pieceType = PieceType::PAWN; }
    virtual ~Pawn() = default;

    std::vector<Move> GetAvailableMoves() const override;
};

} // namespace Shohih

#endif // PAWN_H