/**************************************************
 * @date    2024-07-07
 * @brief   Tests for gui_manager.h & gui_manager.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "gui_manager.h"

using namespace Shohih;

class TestGuiManager : public GuiManager {
public:
    TestGuiManager() : GuiManager(nullptr) {}

    static GuiWindowPos ConvertSquareToWindowPos(Square sq)
    { return GuiManager::ConvertSquareToWindowPos(sq); }

    static Square ConvertWindowPosToSquare(GuiWindowPos pos)
    { return GuiManager::ConvertWindowPosToSquare(pos); }
};

TEST(TestGuiManager, SquareToWindowPos)
{
    // Test cases
    static const std::vector<Square> squares {
        { 0, 0 }, { 0, 7 }, { 7, 0 }, { 7, 7 },
        { 1, 2 }, { 2, 3 }, { 4, 5 }, { 6, 3 },
        { 5, 1 }, { 3, 6 }, { 2, 1 }, { 5, 6 },
    };
    static const std::vector<GuiWindowPos> positions {
        { 0, 7*SQUARE_SIZE }, { 0, 0 },
        { 7*SQUARE_SIZE, 7*SQUARE_SIZE },
        { 7*SQUARE_SIZE, 0 }, { SQUARE_SIZE, 5*SQUARE_SIZE },
        { 2*SQUARE_SIZE, 4*SQUARE_SIZE }, { 4*SQUARE_SIZE, 2*SQUARE_SIZE },
        { 6*SQUARE_SIZE, 4*SQUARE_SIZE }, { 5*SQUARE_SIZE, 6*SQUARE_SIZE },
        { 3*SQUARE_SIZE, 1*SQUARE_SIZE }, { 2*SQUARE_SIZE, 6*SQUARE_SIZE },
        { 5*SQUARE_SIZE, 1*SQUARE_SIZE },
    };

    for (size_t i{ 0 }; i < squares.size(); i++) {
        GuiWindowPos pos =
            TestGuiManager::ConvertSquareToWindowPos(squares[i]);
        EXPECT_EQ(pos, positions[i]);
    }
}

TEST(TestGuiManager, WindowPosToSquare)
{
    // Test cases
    static const std::vector<GuiWindowPos> positions {
        { 10, 10 }, { 12, 42 }, { 123, 342 }, { 289, 411 },
        { 312, 178 }, { 89, 351 }, { 213, 123 }, { 64, 179 },
    };
    static const std::vector<Square> squares {
        { 0, 7 }, { 0, 7 }, { 2, 2 }, { 4, 1 },
        { 5, 5 }, { 1, 2 }, { 3, 5 }, { 1, 5 },
    };

    for (size_t i{ 0 }; i < positions.size(); i++) {
        Square sq =
            TestGuiManager::ConvertWindowPosToSquare(positions[i]);
        EXPECT_EQ(sq, squares[i]);
    }
}