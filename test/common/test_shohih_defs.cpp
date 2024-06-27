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
    EXPECT_EQ(sq.GetSquareName(), "a1");
    EXPECT_TRUE(sq.IsValid());

    Square sq2{ 4, 4 };
    EXPECT_EQ(sq2.x, 4);
    EXPECT_EQ(sq2.y, 4);
    EXPECT_EQ(sq2.GetSquareName(), "e5");
    EXPECT_TRUE(sq2.IsValid());

    Square sq3{ 6, 5 };
    EXPECT_EQ(sq3.x, 6);
    EXPECT_EQ(sq3.y, 5);
    EXPECT_EQ(sq3.GetSquareName(), "g6");
    EXPECT_TRUE(sq3.IsValid());

    Square sq4{ 7, 7 };
    EXPECT_EQ(sq4.x, 7);
    EXPECT_EQ(sq4.y, 7);
    EXPECT_EQ(sq4.GetSquareName(), "h8");
    EXPECT_TRUE(sq4.IsValid());

    Square sq5{ 8, 5 };
    EXPECT_FALSE(sq5.IsValid());
}

TEST(TestShohihDefs, GetSquareByName)
{
    static const std::unordered_map<std::string, Square> cases {
        { "a1", Square{ 0, 0 } },
        { "a4", Square{ 0, 3 } },
        { "b7", Square{ 1, 6 } },
        { "c6", Square{ 2, 5 } },
        { "d8", Square{ 3, 7 } },
        { "e4", Square{ 4, 3 } },
        { "f3", Square{ 5, 2 } },
        { "g7", Square{ 6, 6 } },
        { "h8", Square{ 7, 7 } },
    };
    for (const auto &_case : cases) {
        EXPECT_EQ(Square::GetSquareByName(_case.first), _case.second);
    }
}