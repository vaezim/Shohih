/**************************************************
 * @date    2024-06-08
 * @brief   Tests for pawn.h & pawn.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "pawn.h"

using namespace Shohih;

TEST(TestPawn, PieceType)
{
    Pawn pawn{};
    EXPECT_EQ(pawn.GetPieceType(), PieceType::PAWN);
}