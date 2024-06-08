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
    Board board{};

    // Check all squares are empty
    for (uint8_t x{ 0 }; x < BOARD_SIZE; x++) {
        for (uint8_t y{ 0 }; y < BOARD_SIZE; y++) {
            Square sq{ x, y };
            ASSERT_EQ(board.GetPieceBySquare(sq), nullptr);
        }
    }

    // Invalid parameters
    EXPECT_EQ(board.SetPieceOnSquare(
        nullptr, Square{ 0, 0 }), INVALID_PARAMETER);
    EXPECT_EQ(board.SetPieceOnSquare(
        std::make_shared<Pawn>(), Square{ 0, 8 }), INVALID_PARAMETER);

    // Place a pawn on Square a1
    Square sq{ 0, 0 };
    EXPECT_EQ(sq.GetSquareId(), 1);
    EXPECT_EQ(sq.GetSquareName(), "a1");
    auto pawn = std::make_shared<Pawn>();
    EXPECT_EQ(board.SetPieceOnSquare(pawn, sq), SUCCESS);
}