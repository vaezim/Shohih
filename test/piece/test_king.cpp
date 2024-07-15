/**************************************************
 * @date    2024-06-23
 * @brief   Tests for king.h & king.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "king.h"
#include "test_piece_utils.h"

using namespace Shohih;

/**************************************************
 * Visualize FEN position at https://lichess.org/analysis
 **************************************************/
TEST(TestKing, AvailableMoves)
{
    const std::string fen{ "3B2q1/1k6/6k1/4K3/n7/3P4/2K5/7R w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    std::unordered_map<std::string, PieceTypeAndColor> pieces {
        // King on c2
        { "c2", { PieceType::KING, PieceColor::WHITE } },
        // King on e5
        { "e5", { PieceType::KING, PieceColor::WHITE } },
        // King on g6
        { "g6", { PieceType::KING, PieceColor::BLACK } },
        // King on b7
        { "b7", { PieceType::KING, PieceColor::BLACK } },
    };
    std::unordered_map<std::string, std::vector<std::string>> expected_moves_map {
        { "c2", { "b1", "c1", "d1", "d2" } },
        { "e5", { "e4", "d4", "f4", "d6" } },
        { "g6", { "g7", "f7" } },
        { "b7", { "a6", "a7", "a8", "b8", "c8", "c6" } },
    };

    CheckAvailableMoves(board, pieces, expected_moves_map);
}

TEST(TestKing, Castling)
{
    const std::string fen{ "r3k2r/8/8/1b6/6B1/8/8/R3K2R w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    std::unordered_map<std::string, PieceTypeAndColor> pieces {
        // King on e1
        { "e1", { PieceType::KING, PieceColor::WHITE } },
        // King on e8
        { "e8", { PieceType::KING, PieceColor::BLACK } },
    };
    std::unordered_map<std::string, std::vector<std::string>> expected_moves_map {
        { "e1", { "f2", "d2", "d1", "c1" } },
        { "e8", { "d8", "e7", "f8", "f7", "g8" } },
    };

    CheckAvailableMoves(board, pieces, expected_moves_map);
}