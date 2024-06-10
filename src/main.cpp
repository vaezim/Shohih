/**************************************************
 * @date    2024-06-06
 * @brief   Shohih (CXX Chess program)
 **************************************************/

#include <iostream>
#include "pawn.h"
#include "board.h"

using namespace Shohih;

int main()
{
    auto board = std::make_shared<Board>();
    Pawn pawn(Square{ 0, 1 }, PieceColor::WHITE, board);

    auto moves = pawn.GetAvailableMoves();
    std::cout << moves.size() << std::endl;
}