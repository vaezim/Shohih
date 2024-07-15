/**************************************************
 * @date    2024-06-07
 * @brief   Knight Implementation
 **************************************************/

#include "knight.h"

namespace Shohih {

MoveSet Knight::GetAvailableMoves() const
{
    if (UNLIKELY(m_board == nullptr)) {
        ERROR_LOG("Board is NULL.");
        return {};
    }

    // Check player turn (turned off in test mode)
    if (UNLIKELY(m_board->GetPlayerTurn() != m_color && !TEST_MODE)) {
        return MoveSet{};
    }

    // There are 8 possible squares for the Knight
    uint8_t x{ m_square.x }, y{ m_square.y };
    MoveSet possibleMoves {
        Square{ static_cast<uint8_t>(x - 1), static_cast<uint8_t>(y - 2) },
        Square{ static_cast<uint8_t>(x - 1), static_cast<uint8_t>(y + 2) },
        Square{ static_cast<uint8_t>(x - 2), static_cast<uint8_t>(y - 1) },
        Square{ static_cast<uint8_t>(x - 2), static_cast<uint8_t>(y + 1) },
        Square{ static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y + 2) },
        Square{ static_cast<uint8_t>(x + 1), static_cast<uint8_t>(y - 2) },
        Square{ static_cast<uint8_t>(x + 2), static_cast<uint8_t>(y + 1) },
        Square{ static_cast<uint8_t>(x + 2), static_cast<uint8_t>(y - 1) },
    };

    // Output
    MoveSet moves{};

    for (const auto &sq : possibleMoves) {
        // Ignore invalid squares
        if (!sq.IsValid()) { continue; }
        // If the square is empty or not occupied
        // by the piece with the same color...
        bool canTake = (m_color == PieceColor::WHITE)
            ? m_board->IsBlackPieceOnSquare(sq)
            : m_board->IsWhitePieceOnSquare(sq);
        if (m_board->IsEmptySquare(sq) || canTake) {
            moves.emplace(sq);
        }
    }

    return moves;
}

} // namespace Shohih