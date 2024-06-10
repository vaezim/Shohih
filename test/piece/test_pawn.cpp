/**************************************************
 * @date    2024-06-08
 * @brief   Tests for pawn.h & pawn.cpp
 **************************************************/

#include <gtest/gtest.h>
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
    // FEN: 8/8/8/8/8/8/4P3/8

}