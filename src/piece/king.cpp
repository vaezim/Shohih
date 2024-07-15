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
    MoveSet surroundingSquares {
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

MoveSet King::GetAvailableMoves() const
{
    if (UNLIKELY(m_board == nullptr)) {
        ERROR_LOG("Board is NULL.");
        return {};
    }

    // Check player turn (turned off in test mode)
    if (UNLIKELY(m_board->GetPlayerTurn() != m_color && !TEST_MODE)) {
        return MoveSet{};
    }

    // King can move 1 square in 8 directions
    uint8_t x{ m_square.x }, y{ m_square.y };
    MoveSet possibleMoves {
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
    MoveSet moves{};

    // If an empty square is not hit by opponent's pieces, king can move there
    for (const Square &sq : possibleMoves) {
        if (sq.IsValid() && m_board->IsEmptySquare(sq) &&
            !IsKingOnSurroundingSquares(sq) && !IsSquareChecked(sq)) {
            moves.emplace(sq);
        }
    }

    // Castling: If king and rook have not moved yet and the squares
    // between them are not hit by opponent's pieces, king can castle
    if (m_squareHistory.empty() &&
        ((m_color == PieceColor::WHITE && m_square == Square::GetSquareByName("e1")) ||
         (m_color == PieceColor::BLACK && m_square == Square::GetSquareByName("e8")))) {

        // Short castle (rook on 'h' file)
        auto rook = (m_color == PieceColor::WHITE)
            ? m_board->GetPieceBySquare(Square::GetSquareByName("h1"))
            : m_board->GetPieceBySquare(Square::GetSquareByName("h8"));
        Square sq1 = Square{ static_cast<uint8_t>(m_square.x + 1), m_square.y };
        Square sq2 = Square{ static_cast<uint8_t>(m_square.x + 2), m_square.y };
        if (rook != nullptr && !rook->HasMoved() &&
            m_board->IsEmptySquare(sq1) && m_board->IsEmptySquare(sq2) &&
            !IsSquareChecked(sq1) && !IsSquareChecked(sq2)) {
            moves.emplace(sq2);
        }

        // Long castle (rook on 'a' file)
        rook = (m_color == PieceColor::WHITE)
            ? m_board->GetPieceBySquare(Square::GetSquareByName("a1"))
            : m_board->GetPieceBySquare(Square::GetSquareByName("a8"));
        sq1 = Square{ static_cast<uint8_t>(m_square.x - 1), m_square.y };
        sq2 = Square{ static_cast<uint8_t>(m_square.x - 2), m_square.y };
        if (rook != nullptr && !rook->HasMoved() &&
            m_board->IsEmptySquare(sq1) && m_board->IsEmptySquare(sq2) &&
            !IsSquareChecked(sq1) && !IsSquareChecked(sq2)) {
            moves.emplace(sq2);
        }
    }

    return moves;
}

} // namespace Shohih