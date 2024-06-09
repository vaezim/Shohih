/**************************************************
 * @date    2024-06-06
 * @brief   Queen
 **************************************************/

#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class Queen : public Piece {
public:
    Queen(std::shared_ptr<const Board> board=nullptr, PieceColor color=PieceColor::UNKNOWN) : 
        Piece(color), m_board(board) { m_pieceType = PieceType::QUEEN; }
    virtual ~Queen() = default;

    std::vector<Move> GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // QUEEN_H