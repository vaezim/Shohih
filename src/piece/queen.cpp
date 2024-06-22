/**************************************************
 * @date    2024-06-07
 * @brief   Queen Implementation
 **************************************************/

#include "queen.h"

namespace Shohih {

std::vector<Square> Queen::GetAvailableMoves() const
{
    if (UNLIKELY(m_board == nullptr)) {
        ERROR_LOG("Board is NULL.");
        return {};
    }

    // Queen = Bishop + Rook
    std::vector<Square> possibleMoves {};

    /********************************
     * Bishop Moves @ref bishop.cpp
     ********************************/
    Square sq{
        static_cast<uint8_t>(m_square.x - 1),
        static_cast<uint8_t>(m_square.y - 1)
    };
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x--; sq.y--;
    }
    // NorthEast
    sq.x = m_square.x + 1;
    sq.y = m_square.y + 1;
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x++; sq.y++;
    }
    // SouthEast
    sq.x = m_square.x - 1;
    sq.y = m_square.y + 1;
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x--; sq.y++;
    }
    // NorthWest
    sq.x = m_square.x + 1;
    sq.y = m_square.y - 1;
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x++; sq.y--;
    }

    /********************************
     * Rook Moves @ref rook.cpp
     ********************************/
    // Up
    sq.x = static_cast<uint8_t>(m_square.x + 1),
    sq.y = static_cast<uint8_t>(m_square.y);
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x++;
    }
    // Down
    sq.x = m_square.x - 1;
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x--;
    }
    // Right
    sq.x = m_square.x;
    sq.y = m_square.y + 1;
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.y++;
    }
    // Left
    sq.y = m_square.y - 1;
    while (sq.IsValid()) {
        possibleMoves.emplace_back(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.y--;
    }

    // Output
    std::vector<Square> moves{};

    // Is valid move if square is empty or
    // it is occupied by a piece with opposite color
    for (const Square &square : possibleMoves) {
        if ( m_board->IsEmptySquare(square) ||
            (m_color == PieceColor::WHITE && m_board->IsBlackPieceOnSquare(square)) ||
            (m_color == PieceColor::BLACK && m_board->IsWhitePieceOnSquare(square))) {
            moves.push_back(square);
        }
    }

    return moves;
}

} // namespace Shohih