/**************************************************
 * @date    2024-06-06
 * @brief   Knight
 **************************************************/

#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class Knight : public Piece {
public:
    Knight(
        Square square=Square{},
        PieceColor color=PieceColor::UNKNOWN,
        std::shared_ptr<const Board> board=nullptr) : 
        Piece(square, color), m_board(board) { m_type = PieceType::KNIGHT; }
    virtual ~Knight() = default;

    std::vector<Move> GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // KNIGHT_H