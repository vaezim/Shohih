/**************************************************
 * @date    2024-07-14
 * @brief   Piece Implementation
 **************************************************/

#include "piece.h"

namespace Shohih {

void Piece::SetPieceOnSquare(Square square)
{
    m_squareHistory.emplace_back(square);
    m_square = square;
}

} // namespace Shohih