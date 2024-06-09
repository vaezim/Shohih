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
    Pawn(std::shared_ptr<const Board> board=nullptr, PieceColor color=PieceColor::UNKNOWN) : 
        Piece(color), m_board(board) { m_pieceType = PieceType::PAWN; }
    virtual ~Pawn() = default;

    std::vector<Move> GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // PAWN_H