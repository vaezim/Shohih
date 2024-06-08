/**************************************************
 * @date    2024-06-06
 * @brief   Bishop
 **************************************************/

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

namespace Shohih {

class Bishop : public Piece {
public:
    Bishop(std::shared_ptr<const Board> board=nullptr) : 
        Piece(board) { m_pieceType = PieceType::BISHOP; }
    virtual ~Bishop() = default;

    std::vector<Move> GetAvailableMoves() const override;
};

} // namespace Shohih

#endif // BISHOP_H