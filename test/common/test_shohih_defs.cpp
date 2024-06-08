/**************************************************
 * @date    2024-06-05
 * @brief   Tests for shohih_defs.h
 **************************************************/

#include <gtest/gtest.h>
#include "shohih_defs.h"

using namespace Shohih;

TEST(TestShohihDefs, Square)
{
    Square sq{};
    EXPECT_EQ(sq.x, 0);
    EXPECT_EQ(sq.y, 0);
}