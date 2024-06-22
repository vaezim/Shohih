/**************************************************
 * @date    2024-06-22
 * @brief   Tests for queen.h & queen.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "queen.h"
#include "test_piece_utils.h"

using namespace Shohih;

/**************************************************
 * Visualize FEN position at https://lichess.org/analysis
 **************************************************/
TEST(TestQueen, AvailableMoves)
{
    const std::string fen{ "2B5/5Q2/1q4P1/8/3P4/6q1/R1Q5/4N3 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    std::unordered_map<std::string, PieceTypeAndColor> pieces {
        // Queen on c2
        { "c2", { PieceType::QUEEN, PieceColor::WHITE } },
        // Queen on g3
        { "g3", { PieceType::QUEEN, PieceColor::BLACK } },
        // Queen on b6
        { "b6", { PieceType::QUEEN, PieceColor::BLACK } },
        // Queen on f7
        { "f7", { PieceType::QUEEN, PieceColor::WHITE } },
    };
    std::unordered_map<std::string, std::vector<std::string>> expected_moves_map {
        { "c2", { "c1", "b2", "d2", "e2", "f2", "g2", "h2", "c3", "c4", "c5", "c6", "c7", "b1", "d1", "b3", "a4", "d3", "e4", "f5" } },
        { "g3", { "g2", "g1", "f3", "e3", "d3", "c3", "b3", "a3", "h3", "g4", "g5", "g6", "h2", "f2", "e1", "h4", "f4", "e5", "d6", "c7", "b8" } },
        { "b6", { "b1", "b2", "b3", "b4", "b5", "a6", "c6", "d6", "e6", "f6", "g6", "b7", "b8", "a7", "a5", "c5", "d4", "c7", "d8" } },
        { "f7", { "f8", "f6", "f5", "f4", "f3", "f2", "f1", "g7", "h7", "e7", "d7", "c7", "b7", "a7", "g8", "e8", "e6", "d5", "c4", "b3" } },
    };

    CheckAvailableMoves(board, pieces, expected_moves_map);
}