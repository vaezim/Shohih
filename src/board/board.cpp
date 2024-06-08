/**************************************************
 * @date    2024-06-08
 * @brief   Chess board Implementation
 **************************************************/

#include "board.h"

namespace Shohih {

/**************************************************
 * @details
 *      - Validate @param piece and @param square
 *              @return INVALID_PARAMETER
 *      - Check @param square is empty
 *              @return SQUARE_NOT_EMPTY
 *      - Save piece ptr in m_pieces
 *              @return SUCCESS
 **************************************************/
ErrorCode Board::SetPieceOnSquare(
    std::shared_ptr<Piece> piece, Square square)
{
    // Validate input parameters
    if (UNLIKELY(piece == nullptr || !square.IsValid())) {
        ERROR_LOG("Failed to set piece on board: Invalid parameters.");
        return INVALID_PARAMETER;
    }

    // Check if square is empty
    if (m_pieces[square.x][square.y] != nullptr) {
        ERROR_LOG("Failed to set piece on board: Square is not empty.");
        return SQUARE_NOT_EMPTY;
    }

    m_pieces[square.x][square.y] = piece;
    return SUCCESS;
}

/**************************************************
 * @details
 *      - Validate @param square
 *              @return nullptr
 *      - Return piece at @param square
 **************************************************/
std::shared_ptr<Piece> Board::GetPieceBySquare(Square square)
{
    if (UNLIKELY(!square.IsValid())) {
        ERROR_LOG("Failed to get piece: Invalid parameters.");
        return nullptr;
    }
    return m_pieces[square.x][square.y];
}

} // Shohih