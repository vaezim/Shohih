/**************************************************
 * @date    2024-06-07
 * @brief   Pawn Implementation
 **************************************************/

#include "pawn.h"

namespace Shohih {

SquareSet Pawn::GetAvailableMoves() const
{
    if (UNLIKELY(m_board == nullptr)) {
        ERROR_LOG("Board is NULL.");
        return {};
    }

    // Output
    SquareSet moves{};

    // Check player turn (turned off in test mode)
    if (UNLIKELY(m_board->GetPlayerTurn() != m_color && !TEST_MODE)) {
        return moves;
    }

    // Pawns cannot be on 1st and 8th rank
    if (UNLIKELY(m_square.y == 0 || m_square.y == 7)) {
        ERROR_LOG("Pawns cannot be on Rank 1 & 8");
        return moves;
    }

    // White/Black pawns can move 
    // forward by 2 squares on rank 2/7
    if ((m_color == PieceColor::WHITE && m_square.y == 1) || 
        (m_color == PieceColor::BLACK && m_square.y == 6)) {
        // Middle square must be empty
        Square mid = m_square;
        mid.y += (m_color == PieceColor::WHITE) ? 1 : -1;
        // Destination square
        Square dst = m_square;
        dst.y += (m_color == PieceColor::WHITE) ? 2 : -2;
        if (m_board->IsEmptySquare(mid) && m_board->IsEmptySquare(dst)) {
            moves.emplace(dst);
        }
    }

    // Pawns can move forward by 1 square
    Square dst = m_square;
    dst.y += (m_color == PieceColor::WHITE) ? 1 : -1;
    if (m_board->IsEmptySquare(dst)) {
        moves.emplace(dst);
    }

    // Pawns can take a piece diagonally
    std::vector<uint8_t> diagonalSquares{};
    if (m_square.x < (BOARD_SIZE - 1)) diagonalSquares.push_back(m_square.x + 1);
    if (m_square.x > 0) diagonalSquares.push_back(m_square.x - 1);
    for (const uint8_t &x : diagonalSquares) {
        dst.x = x;
        bool canTake = (m_color == PieceColor::WHITE)
            ? m_board->IsBlackPieceOnSquare(dst)
            : m_board->IsWhitePieceOnSquare(dst);
        if (canTake) {
            moves.emplace(dst);
        }
    }

    // En Passant
    Square enPassant = GetEnPassantMove();
    if (enPassant != NULL_SQUARE) {
        moves.emplace(enPassant);
    }

    return moves;
}

/**************************************************
 * @details
 *      - Check if this pawn has an en passant move.
 *      - @return NULL_SQUARE if it doesn't.
 **************************************************/
Square Pawn::GetEnPassantMove() const
{
    auto lastMove = m_board->GetLastMove();
    if (lastMove.second == NULL_SQUARE) {
        return NULL_SQUARE;
    }
    auto lastMovedPiece = m_board->GetPieceBySquare(lastMove.second);
    if (lastMovedPiece != nullptr && 
        lastMovedPiece->GetPieceType() == PieceType::PAWN &&
        lastMovedPiece->GetPieceColor() != m_color &&
        std::abs(lastMove.first.y - lastMove.second.y) == 2 &&
        lastMovedPiece->GetPieceSquare().y == m_square.y &&
        std::abs(lastMovedPiece->GetPieceSquare().x - m_square.x) == 1) {
            Square enPassant = m_square;
            enPassant.y += (m_color == PieceColor::WHITE) ? 1 : -1;
            enPassant.x = lastMovedPiece->GetPieceSquare().x;
            return enPassant;
    }
    return NULL_SQUARE;
}

} // namespace Shohih