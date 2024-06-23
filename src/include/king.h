/**************************************************
 * @date    2024-06-06
 * @brief   King
 **************************************************/

#pragma once
#ifndef KING_H
#define KING_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class King : public Piece {
public:
    King(
        Square square=Square{},
        PieceColor color=PieceColor::UNKNOWN,
        std::shared_ptr<const Board> board=nullptr) : 
        Piece(square, color), m_board(board) { m_type = PieceType::KING; }
    virtual ~King() = default;

    std::vector<Square> GetAvailableMoves() const override;

protected: /* For inheriting in gtest */
    //--------------------------------------------------
    // Check surrounding squares for King piece
    //--------------------------------------------------
    bool IsKingOnSurroundingSquares(Square square) const;

    //--------------------------------------------------
    // Can King move to this square. (true -> No | false -> Yes)
    // The square should not be in the available moves
    //  of other pieces with opposite color.
    //--------------------------------------------------
    bool IsSquareChecked(Square square) const;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // KING_H