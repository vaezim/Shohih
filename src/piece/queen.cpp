/**************************************************
 * @date    2024-06-07
 * @brief   Queen Implementation
 **************************************************/

#include "queen.h"

namespace Shohih {

MoveSet Queen::GetAvailableMoves() const
{
    if (UNLIKELY(m_board == nullptr)) {
        ERROR_LOG("Board is NULL.");
        return {};
    }

    // Check player turn (turned off in test mode)
    if (UNLIKELY(m_board->GetPlayerTurn() != m_color && !TEST_MODE)) {
        return MoveSet{};
    }

    // Queen = Bishop + Rook
    MoveSet possibleMoves {};

    /********************************
     * Bishop Moves @ref bishop.cpp
     ********************************/
    Square sq{
        static_cast<uint8_t>(m_square.x - 1),
        static_cast<uint8_t>(m_square.y - 1)
    };
    while (sq.IsValid()) {
        possibleMoves.emplace(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x--; sq.y--;
    }
    // NorthEast
    sq.x = m_square.x + 1;
    sq.y = m_square.y + 1;
    while (sq.IsValid()) {
        possibleMoves.emplace(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x++; sq.y++;
    }
    // SouthEast
    sq.x = m_square.x - 1;
    sq.y = m_square.y + 1;
    while (sq.IsValid()) {
        possibleMoves.emplace(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x--; sq.y++;
    }
    // NorthWest
    sq.x = m_square.x + 1;
    sq.y = m_square.y - 1;
    while (sq.IsValid()) {
        possibleMoves.emplace(sq);
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
        possibleMoves.emplace(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x++;
    }
    // Down
    sq.x = m_square.x - 1;
    while (sq.IsValid()) {
        possibleMoves.emplace(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.x--;
    }
    // Right
    sq.x = m_square.x;
    sq.y = m_square.y + 1;
    while (sq.IsValid()) {
        possibleMoves.emplace(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.y++;
    }
    // Left
    sq.y = m_square.y - 1;
    while (sq.IsValid()) {
        possibleMoves.emplace(sq);
        if (!m_board->IsEmptySquare(sq)) break;
        sq.y--;
    }

    // Output
    MoveSet moves{};

    // Is valid move if square is empty or
    // it is occupied by a piece with opposite color
    for (const Square &square : possibleMoves) {
        if ( m_board->IsEmptySquare(square) ||
            (m_color == PieceColor::WHITE && m_board->IsBlackPieceOnSquare(square)) ||
            (m_color == PieceColor::BLACK && m_board->IsWhitePieceOnSquare(square))) {
            moves.emplace(square);
        }
    }

    return moves;
}

} // namespace Shohih