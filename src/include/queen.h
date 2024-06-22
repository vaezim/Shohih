/**************************************************
 * @date    2024-06-06
 * @brief   Queen
 **************************************************/

#pragma once
#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class Queen : public Piece {
public:
    Queen(
        Square square=Square{},
        PieceColor color=PieceColor::UNKNOWN,
        std::shared_ptr<const Board> board=nullptr) : 
        Piece(square, color), m_board(board) { m_type = PieceType::QUEEN; }
    virtual ~Queen() = default;

    std::vector<Square> GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // QUEEN_H