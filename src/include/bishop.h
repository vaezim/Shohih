/**************************************************
 * @date    2024-06-06
 * @brief   Bishop
 **************************************************/

#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "board.h"

namespace Shohih {

class Bishop : public Piece {
public:
    Bishop(std::shared_ptr<const Board> board=nullptr) : 
        m_board(board) { m_pieceType = PieceType::BISHOP; }
    virtual ~Bishop() = default;

    std::vector<Move> GetAvailableMoves() const override;

private:
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // BISHOP_H