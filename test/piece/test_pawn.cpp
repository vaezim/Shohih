/**************************************************
 * @date    2024-06-08
 * @brief   Tests for pawn.h & pawn.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "pawn.h"
#include "test_piece_utils.h"

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

    CheckAvailableMoves(board, pieces, expected_moves_map);
}

/**************************************************
 * Visualize FEN position at https://lichess.org/analysis
 **************************************************/
TEST(TestPawn, EnPassant)
{
    const std::string fen{ "8/5p2/7n/6P1/3p4/2R5/4P3/8 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    // Move the white pawn on e2 to e4
    ASSERT_EQ(SUCCESS,
        board->MovePiece(Square::GetSquareByName("e2"), Square::GetSquareByName("e4")));

    // Get available moves of the black pawn on d4 
    auto pawn = board->GetPieceBySquare(Square::GetSquareByName("d4"));
    ASSERT_NE(pawn, nullptr);
    EXPECT_EQ(pawn->GetPieceType(), PieceType::PAWN);
    EXPECT_EQ(pawn->GetPieceColor(), PieceColor::BLACK);
    auto moves = pawn->GetAvailableMoves();
    EXPECT_EQ(moves.size(), 3u);
    for (const auto &move : std::vector<std::string>{ "c3", "d3", "e3" }) {
        EXPECT_NE(moves.count(Square::GetSquareByName(move)), 0u);
    }

    // Move the black pawn on f7 to f5
    ASSERT_EQ(SUCCESS,
        board->MovePiece(Square::GetSquareByName("f7"), Square::GetSquareByName("f5")));

    // Get available moves of the black pawn on g5 
    pawn = board->GetPieceBySquare(Square::GetSquareByName("g5"));
    ASSERT_NE(pawn, nullptr);
    EXPECT_EQ(pawn->GetPieceType(), PieceType::PAWN);
    EXPECT_EQ(pawn->GetPieceColor(), PieceColor::WHITE);
    moves = pawn->GetAvailableMoves();
    EXPECT_EQ(moves.size(), 3u);
    for (const auto &move : std::vector<std::string>{ "f6", "g6", "h6" }) {
        EXPECT_NE(moves.count(Square::GetSquareByName(move)), 0u);
    }
}