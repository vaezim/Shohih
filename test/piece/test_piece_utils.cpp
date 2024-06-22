/**************************************************
 * @date    2024-06-22
 * @brief   Piece test utilities
 **************************************************/

#include <algorithm>
#include "test_piece_utils.h"

namespace Shohih {

void CheckAvailableMoves(
    const std::shared_ptr<Board> board,
    const std::unordered_map<std::string, PieceTypeAndColor> &pieces,
    const std::unordered_map<std::string, std::vector<std::string>> &expected_moves_map)
{
    // Check available moves for each piece
    for (const auto &item : pieces) {
        // Get piece from board
        auto piece_square = item.first;
        auto piece = board->GetPieceBySquare(Square::GetSquareByName(piece_square));
        ASSERT_NE(piece, nullptr);
        EXPECT_EQ(piece->GetPieceType(), item.second.type);
        EXPECT_EQ(piece->GetPieceColor(), item.second.color);

        // Get expected moves for this piece
        auto itr = expected_moves_map.find(piece_square);
        if (UNLIKELY(itr == expected_moves_map.end())) {
            ERROR_LOG("Square " << piece_square << " was not found in expected moves map.");
            return;
        }

        // Compare available moves with expected moves
        auto &expected_moves = itr->second;
        auto moves = piece->GetAvailableMoves();
        EXPECT_EQ(moves.size(), expected_moves.size());
        for (const auto &square : expected_moves) {
            auto moveItr = std::find(moves.begin(), moves.end(), Square::GetSquareByName(square));
            ASSERT_NE(moveItr, moves.end());
            EXPECT_EQ(*moveItr, Square::GetSquareByName(square));
        }
    }
}

} // namespace Shohih