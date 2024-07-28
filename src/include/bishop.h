/**************************************************
 * @date    2024-06-06
 * @brief   Bishop
 **************************************************/

#pragma once
#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class Bishop : public Piece {
public:
    Bishop(
        Square square=Square{},
        PieceColor color=PieceColor::UNKNOWN,
        std::shared_ptr<const Board> board=nullptr) : 
        Piece(square, color), m_board(board) { m_type = PieceType::BISHOP; }
    virtual ~Bishop() = default;

    SquareSet GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // BISHOP_H