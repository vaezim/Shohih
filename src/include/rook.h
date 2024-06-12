/**************************************************
 * @date    2024-06-06
 * @brief   Rook
 **************************************************/

#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class Rook : public Piece {
public:
    Rook(
        Square square=Square{},
        PieceColor color=PieceColor::UNKNOWN,
        std::shared_ptr<const Board> board=nullptr) : 
        Piece(square, color), m_board(board) { m_type = PieceType::ROOK; }
    virtual ~Rook() = default;

    std::vector<Square> GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // ROOK_H