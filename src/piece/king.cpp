/**************************************************
 * @date    2024-06-07
 * @brief   King Implementation
 **************************************************/

#include <algorithm>
#include "king.h"

namespace Shohih {

bool King::IsKingOnSurroundingSquares(Square square) const
{
    uint8_t x{ square.x }, y{ square.y };
    std::vector<Square> surroundingSquares {
        Square{ x, static_cast<uint8_t>(y - 1) },
        Square{ x, static_cast<uint8_t>(y + 1) },
        Square{ static_cast<uint8_t>(x - 1), y },
        Square{ static_cast<uint8_t>(x + 1), y },
        Square{ static_cast<uint8_t>(x - 1), static_cast<uint8_t>(y - 1) },
        Square{ static_cast<uint8_t>(x - 1), static_cast<uint8_t>(y + 1) },
        Square{ static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y - 1) },
        Square{ static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y + 1) },
    };
    for (const Square &sq : surroundingSquares) {
        if (!sq.IsValid() || m_board->IsEmptySquare(sq)) { continue; }
        auto piece = m_board->GetPieceBySquare(sq);
        if (piece->GetPieceType() == PieceType::KING &&
            piece->GetPieceColor() != m_color) {
            return true;
        }
    }
    return false;
}

bool King::IsSquareChecked(Square target) const
{
    for (uint8_t x{ 0 }; x < BOARD_SIZE; x++) {
        for (uint8_t y{ 0 }; y < BOARD_SIZE; y++) {
            Square square{ x, y };
            // Ignore king's current square
            if (square == m_square) { continue; }
            // Ignore empty squares
            if (m_board->IsEmptySquare(square)) { continue; }
            // Ignore squares that are occupied by pieces with the same color
            if ((m_color == PieceColor::WHITE && m_board->IsWhitePieceOnSquare(square)) ||
                (m_color == PieceColor::BLACK && m_board->IsBlackPieceOnSquare(square))) { continue; }
            // Ignore opponent's King (causes infinite recursion!)
            auto piece = m_board->GetPieceBySquare(square);
            if (piece->GetPieceType() == PieceType::KING) { continue; }
            // Check available moves of opponent's pieces
            auto availableMoves = piece->GetAvailableMoves();
            if (std::find(availableMoves.begin(), availableMoves.end(), target) != availableMoves.end()) {
                return true;
            }
        }
    }
    return false;
}

std::vector<Square> King::GetAvailableMoves() const
{
    if (UNLIKELY(m_board == nullptr)) {
        ERROR_LOG("Board is NULL.");
        return {};
    }

    // King can move 1 square in 8 directions
    uint8_t x{ m_square.x }, y{ m_square.y };
    std::vector<Square> possibleMoves {
        Square{ x, static_cast<uint8_t>(y - 1) },
        Square{ x, static_cast<uint8_t>(y + 1) },
        Square{ static_cast<uint8_t>(x - 1), y },
        Square{ static_cast<uint8_t>(x + 1), y },
        Square{ static_cast<uint8_t>(x - 1), static_cast<uint8_t>(y - 1) },
        Square{ static_cast<uint8_t>(x - 1), static_cast<uint8_t>(y + 1) },
        Square{ static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y - 1) },
        Square{ static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y + 1) },
    };

    // Output
    std::vector<Square> moves{};

    // If an empty square is not checked by opponent's pieces, king can move there
    for (const Square &sq : possibleMoves) {
        if (m_board->IsEmptySquare(sq) &&
            !IsKingOnSurroundingSquares(sq) && !IsSquareChecked(sq)) {
            moves.emplace_back(sq);
        }
    }

    return moves;
}

} // namespace Shohih