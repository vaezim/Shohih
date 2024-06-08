/**************************************************
 * @date    2024-06-06
 * @brief   Rook
 **************************************************/

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

namespace Shohih {

class Rook : public Piece {
public:
    Rook(std::shared_ptr<const Board> board=nullptr) : 
        Piece(board) { m_pieceType = PieceType::ROOK; }
    virtual ~Rook() = default;

    std::vector<Move> GetAvailableMoves() const override;
};

} // namespace Shohih

#endif // ROOK_H