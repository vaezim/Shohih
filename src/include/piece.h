/**************************************************
 * @date    2024-06-05
 * @brief   Interface for chess pieces
 **************************************************/

#pragma once
#ifndef PIECE_H
#define PIECE_H

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

    //--------------------------------------------------
    // Get a list of playable moves for this piece
    // (Must be implemented for each piece type!)
    //--------------------------------------------------
    virtual SquareSet GetAvailableMoves() const = 0;

    //--------------------------------------------------
    // Piece attribute getter
    //--------------------------------------------------
    inline PieceType GetPieceType() const { return m_type; }
    inline Square GetPieceSquare() const { return m_square; }
    inline PieceColor GetPieceColor() const { return m_color; }

    inline bool HasMoved() const { return !m_squareHistory.empty(); }

protected:
    // Only Board can change the square of a piece
    friend class Board;
    void SetPieceOnSquare(Square square);

    // Piece attributes (square, type, color)
    Square m_square{ NULL_SQUARE };
    PieceType m_type{ PieceType::UNKNOWN };
    PieceColor m_color{ PieceColor::UNKNOWN };

    // History of piece's previous squares
    std::vector<Square> m_squareHistory{};
};

} // namespace Shohih

#endif // PIECE_H