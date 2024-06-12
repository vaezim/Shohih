/**************************************************
 * @date    2024-06-06
 * @brief   King
 **************************************************/

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

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // KING_H