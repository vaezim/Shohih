/**************************************************
 * @date    2024-06-08
 * @brief   Tests for board->h & board->cpp
 **************************************************/

#include <gtest/gtest.h>
#include "board.h"
#include "pawn.h"

using namespace Shohih;

TEST(TestBoard, PieceSetterAndGetter)
{
    auto board = std::make_shared<Board>();

    // Check all squares are empty
    for (uint8_t x{ 0 }; x < BOARD_SIZE; x++) {
        for (uint8_t y{ 0 }; y < BOARD_SIZE; y++) {
            Square sq{ x, y };
            ASSERT_EQ(board->GetPieceBySquare(sq), nullptr);
        }
    }

    // Invalid square
    EXPECT_EQ(board->SetPieceOnSquare(
        PieceType::PAWN, PieceColor::WHITE, Square{ 0, 8 }), INVALID_SQUARE);

    // Invalid piece type
    EXPECT_EQ(board->SetPieceOnSquare(
        PieceType::UNKNOWN, PieceColor::WHITE, Square{ 0, 0 }), INVALID_PIECE_TYPE);

    // Place a pawn on Square a1
    EXPECT_EQ(board->SetPieceOnSquare(
        PieceType::PAWN, PieceColor::WHITE, Square{ 0, 0 }), SUCCESS);

    // Place another piece on a1
    EXPECT_EQ(board->SetPieceOnSquare(
        PieceType::KNIGHT, PieceColor::WHITE, Square{ 0, 0 }), SQUARE_NOT_EMPTY);
}

TEST(TestBoard, BuildBoardByFEN)
{
    // Sample game position in FEN notation
    // Visualize at https://lichess.org/analysis
    const std::string fen{ "6n1/2b5/8/7k/1K6/8/4P3/Q7 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    // Check if pieces are at correct squares
    auto piece = board->GetPieceBySquare(Square{ 0, 0 });
    ASSERT_NE(piece, nullptr);
    EXPECT_EQ(piece->GetPieceType(), PieceType::QUEEN);
    EXPECT_EQ(piece->GetPieceColor(), PieceColor::WHITE);
}