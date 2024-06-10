/**************************************************
 * @date    2024-06-08
 * @brief   Tests for board.h & board.cpp
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

    // Place a pawn on Square a2
    EXPECT_EQ(board->SetPieceOnSquare(
        PieceType::PAWN, PieceColor::WHITE, Square{ 0, 1 }), SUCCESS);

    // Place another piece on a2
    EXPECT_EQ(board->SetPieceOnSquare(
        PieceType::KNIGHT, PieceColor::WHITE, Square{ 0, 1 }), SQUARE_NOT_EMPTY);

    // Get the piece on a2
    auto piece = board->GetPieceBySquare(Square{ 0, 1 });
    ASSERT_NE(piece, nullptr);
    EXPECT_EQ(piece->GetPieceType(), PieceType::PAWN);
    EXPECT_EQ(piece->GetPieceColor(), PieceColor::WHITE);
    EXPECT_EQ(piece->GetPieceSquare().GetSquareName(), "a2");
}

TEST(TestBoard, BuildBoardByFEN)
{
    /**************************************************
     * Visualize FEN position at https://lichess.org/analysis
     **************************************************/
    const std::string fen{ "6n1/2b5/8/7k/1K6/8/4P3/Q7 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    // Check if pieces are at correct squares
    struct PieceAttributes {
        PieceType type;
        PieceColor color;
    };
    std::unordered_map<std::string, PieceAttributes> cases {
        // Queen on a1
        { "a1", { PieceType::QUEEN, PieceColor::WHITE } },
        // King on b4
        { "b4", { PieceType::KING, PieceColor::WHITE } },
        // Bishop on c7
        { "c7", { PieceType::BISHOP, PieceColor::BLACK } },
        // Pawn on e2
        { "e2", { PieceType::PAWN, PieceColor::WHITE } },
        // Knight on g8
        { "g8", { PieceType::KNIGHT, PieceColor::BLACK } },
        // King on h5
        { "a1", { PieceType::KING, PieceColor::BLACK } },
    };
    for (const auto &_case : cases) {
        Square sq = Square::GetSquareByName(_case.first);
        auto piece = board->GetPieceBySquare(sq);
        ASSERT_NE(piece, nullptr);
        EXPECT_EQ(piece->GetPieceType(), _case.second.type);
        EXPECT_EQ(piece->GetPieceColor(), _case.second.color);
        EXPECT_EQ(piece->GetPieceSquare(), sq);
    }
}