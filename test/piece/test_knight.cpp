/**************************************************
 * @date    2024-06-18
 * @brief   Tests for knight.h & knight.cpp
 **************************************************/

#include <gtest/gtest.h>
#include <algorithm>
#include "knight.h"

using namespace Shohih;

/**************************************************
 * Visualize FEN position at https://lichess.org/analysis
 **************************************************/
TEST(TestKnight, AvailableMoves)
{
    const std::string fen{ "6N1/2N5/P4R2/1n4p1/4n3/2N5/5B2/n5N1 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    std::unordered_map<std::string, PieceTypeAndColor> pieces {
        // Knight on a1
        { "a1", { PieceType::KNIGHT, PieceColor::BLACK } },
        // Knight on g1
        { "g1", { PieceType::KNIGHT, PieceColor::WHITE } },
        // Knight on c3
        { "c3", { PieceType::KNIGHT, PieceColor::WHITE } },
        // Knight on e4
        { "e4", { PieceType::KNIGHT, PieceColor::BLACK } },
        // Knight on b5
        { "b5", { PieceType::KNIGHT, PieceColor::BLACK } },
        // Knight on c7
        { "c7", { PieceType::KNIGHT, PieceColor::WHITE } },
        // Knight on g8
        { "g8", { PieceType::KNIGHT, PieceColor::WHITE } },
    };
    std::unordered_map<std::string, std::vector<std::string>> expected_moves_map {
        { "a1", { "b3", "c2" } },
        { "g1", { "e2", "f3", "h3" } },
        { "c3", { "a2", "b1", "d1", "e2", "e4", "d5", "b5", "a4" } },
        { "e4", { "c3", "d2", "f2", "g3", "f6", "d6", "c5" } },
        { "b5", { "a3", "c3", "d4", "d6", "c7", "a7" } },
        { "c7", { "b5", "d5", "e6", "e8", "a8" } },
        { "g8", { "h6", "e7" } },
    };

    // Check available moves for each piece
    for (const auto &item : pieces) {
        // Get knight from board
        auto piece_square = item.first;
        auto knight = board->GetPieceBySquare(Square::GetSquareByName(piece_square));
        ASSERT_NE(knight, nullptr);
        EXPECT_EQ(knight->GetPieceType(), item.second.type);
        EXPECT_EQ(knight->GetPieceColor(), item.second.color);

        // Compare available moves with expected moves
        auto moves = knight->GetAvailableMoves();
        auto &expected_moves = expected_moves_map[piece_square];
        EXPECT_EQ(moves.size(), expected_moves.size());
        for (const auto &square : expected_moves) {
            auto moveItr = std::find(moves.begin(), moves.end(), Square::GetSquareByName(square));
            ASSERT_NE(moveItr, moves.end());
            EXPECT_EQ(*moveItr, Square::GetSquareByName(square));
        }
    }
}