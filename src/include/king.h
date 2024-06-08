/**************************************************
 * @date    2024-06-06
 * @brief   King
 **************************************************/

#ifndef KING_H
#define KING_H

#include "piece.h"

namespace Shohih {

class King : public Piece {
public:
    King(std::shared_ptr<const Board> board=nullptr) : 
        Piece(board) { m_pieceType = PieceType::KING; }
    virtual ~King() = default;

    std::vector<Move> GetAvailableMoves() const override;
};

} // namespace Shohih

#endif // KING_H