/**************************************************
 * @date    2024-06-05
 * @brief   Interface for chess pieces
 **************************************************/

#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "shohih_defs.h"

namespace Shohih {

class Piece {
public:
    Piece() {}
    ~Piece() = default;

    // Get a list of playable moves for this piece
    // (Must be implemented for each piece type)
    virtual std::vector<Move> GetAvailableMoves() const = 0;

    // Piece type getter
    PieceType GetPieceType() const { return m_pieceType; }
    // Piece square getter
    Square GetPieceSquare() const { return m_square; }

protected:
    Square m_square{};
    PieceType m_pieceType{ PieceType::UNKNOWN };
};

} // namespace Shohih

#endif // PIECE_H