/**************************************************
 * @date    2024-06-05
 * @brief   Interface for chess pieces
 **************************************************/

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "board.h"
#include "shohih_defs.h"

namespace Shohih {

class Piece {
public:
    Piece(std::shared_ptr<const Board> board) : m_board(board) {}

    // Get a list of playable moves for this piece
    // (Must be implemented for each piece type)
    virtual std::vector<Move> GetAvailableMoves() const = 0;

    // Piece type getter
    PieceType GetPieceType() const { return m_pieceType; }

protected:
    PieceType m_pieceType{ PieceType::UNKNOWN };
    std::shared_ptr<const Board> m_board{ nullptr };
};

} // namespace Shohih

#endif // PIECE_H