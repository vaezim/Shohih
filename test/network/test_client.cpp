/**************************************************
 * @date    2024-07-20
 * @brief   Test client.h & client.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "client.h"

using namespace Shohih;

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestShohihClient, GetAndPostRequests)
{
    Client client("localhost:8080");

    // Server should return NULL move at first
    Move move = client.GetMove();
    EXPECT_EQ(move.first, NULL_SQUARE);
    EXPECT_EQ(move.second, NULL_SQUARE);

    // Client send the first move to the server
    move = Move {
        Square::GetSquareByName("e2"),
        Square::GetSquareByName("e4"),
    };
    client.SendMove(move);

    // We should be getting the same move from the server
    move = client.GetMove();
    EXPECT_EQ(move.first, Square::GetSquareByName("e2"));
    EXPECT_EQ(move.second, Square::GetSquareByName("e4"));
}