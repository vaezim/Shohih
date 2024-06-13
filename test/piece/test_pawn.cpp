/**************************************************
 * @date    2024-06-08
 * @brief   Tests for pawn.h & pawn.cpp
 **************************************************/

#include <gtest/gtest.h>
#include <algorithm>
#include "pawn.h"

using namespace Shohih;

TEST(TestPawn, Attributes)
{
    Pawn pawn{};
    Square sq{ 0, 0 };
    EXPECT_EQ(pawn.GetPieceSquare(), sq);
    EXPECT_EQ(pawn.GetPieceColor(), PieceColor::UNKNOWN);
    EXPECT_EQ(pawn.GetPieceType(), PieceType::PAWN);

    Pawn pawn2(Square{ 0, 6 }, PieceColor::BLACK);
    Square sq2{ 0, 6 };
    EXPECT_EQ(pawn2.GetPieceSquare(), sq2);
    EXPECT_EQ(pawn2.GetPieceColor(), PieceColor::BLACK);
    EXPECT_EQ(pawn2.GetPieceType(), PieceType::PAWN);
}

/**************************************************
 * Visualize FEN position at https://lichess.org/analysis
 **************************************************/
TEST(TestPawn, AvailableMoves)
{
    const std::string fen{ "8/8/8/8/8/8/4P3/8 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    // Pawn on e2
    auto pawn = board->GetPieceBySquare(Square::GetSquareByName("e2"));
    ASSERT_NE(pawn, nullptr);
    EXPECT_EQ(pawn->GetPieceColor(), PieceColor::WHITE);

    // Available Moves
    auto moves = pawn->GetAvailableMoves();
    std::vector<std::string> expected_moves{ "e3", "e4" };
    EXPECT_EQ(moves.size(), expected_moves.size());
    for (const auto &square : expected_moves) {
        auto moveItr = std::find(moves.begin(), moves.end(), Square::GetSquareByName(square));
        ASSERT_NE(moveItr, moves.end());
        EXPECT_EQ(*moveItr, Square::GetSquareByName(square));
    }
}

TEST(TestPawn, AvailableMoves2)
{
    const std::string fen{ "8/p3pP2/3B1N2/8/6P1/N1b3qr/1P5P/8 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    std::unordered_map<std::string, PieceTypeAndColor> pieces {
        // Pawn on b2
        { "b2", { PieceType::PAWN, PieceColor::WHITE } },
        // Pawn on h2
        { "h2", { PieceType::PAWN, PieceColor::WHITE } },
        // Pawn on a7
        { "a7", { PieceType::PAWN, PieceColor::BLACK } },
        // Pawn on e7
        { "e7", { PieceType::PAWN, PieceColor::BLACK } },
        // Pawn on f7
        { "f7", { PieceType::PAWN, PieceColor::WHITE } },
        // Pawn on g4
        { "g4", { PieceType::PAWN, PieceColor::WHITE } },
    };
    std::unordered_map<std::string, std::vector<std::string>> expected_moves_map {
        { "b2", { "c3", "b3", "b4" } },
        { "h2", { "g3" } },
        { "a7", { "a6", "a5" } },
        { "e7", { "d6", "f6", "e6", "e5" } },
        { "f7", { "f8" } },
        { "g4", { "g5" } },
    };

    // Check available moves for each piece
    for (const auto &item : pieces) {
        // Get pawn from board
        auto piece_square = item.first;
        auto pawn = board->GetPieceBySquare(Square::GetSquareByName(piece_square));
        ASSERT_NE(pawn, nullptr);
        EXPECT_EQ(pawn->GetPieceType(), item.second.type);
        EXPECT_EQ(pawn->GetPieceColor(), item.second.color);

        // Compare available moves with expected moves
        auto moves = pawn->GetAvailableMoves();
        auto &expected_moves = expected_moves_map[piece_square];
        EXPECT_EQ(moves.size(), expected_moves.size());
        for (const auto &square : expected_moves) {
            auto moveItr = std::find(moves.begin(), moves.end(), Square::GetSquareByName(square));
            ASSERT_NE(moveItr, moves.end());
            EXPECT_EQ(*moveItr, Square::GetSquareByName(square));
        }
    }
}