/**************************************************
 * @date    2024-06-05
 * @brief   Interface for chess pieces
 **************************************************/

#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "shohih_defs.h"

namespace Shohih {

class Piece {
public:
    Piece(
        Square square=Square{},
        PieceColor color=PieceColor::UNKNOWN) : 
        m_square(square), m_color(color) {}
    virtual ~Piece() = default;

    // Get a list of playable moves for this piece
    // (Must be implemented for each piece type!)
    virtual std::vector<Square> GetAvailableMoves() const = 0;

    // Piece square getter
    Square GetPieceSquare() const { return m_square; }
    // Piece color getter
    PieceColor GetPieceColor() const { return m_color; }
    // Piece type getter
    PieceType GetPieceType() const { return m_type; }

protected:
    // Only Board can change the square of a piece
    friend class Board;
    void SetPieceOnSquare(Square square) { m_square = square; }

    Square m_square{};
    PieceType m_type{ PieceType::UNKNOWN };
    PieceColor m_color{ PieceColor::UNKNOWN };
};

} // namespace Shohih

#endif // PIECE_H