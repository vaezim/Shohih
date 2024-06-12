/**************************************************
 * @date    2024-06-06
 * @brief   Pawn
 **************************************************/

#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class Pawn : public Piece {
public:
    Pawn(
        Square square=Square{},
        PieceColor color=PieceColor::UNKNOWN,
        std::shared_ptr<const Board> board=nullptr) : 
        Piece(square, color), m_board(board) { m_type = PieceType::PAWN; }
    virtual ~Pawn() = default;

    std::vector<Square> GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // PAWN_H