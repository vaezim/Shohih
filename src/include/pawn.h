/**************************************************
 * @date    2024-06-06
 * @brief   Pawn
 **************************************************/

#pragma once
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

    MoveSet GetAvailableMoves() const override;

private:
    friend class Board;
    Square GetEnPassantMove() const;

    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // PAWN_H