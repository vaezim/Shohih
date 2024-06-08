/**************************************************
 * @date    2024-06-06
 * @brief   Shohih (CXX Chess program)
 **************************************************/

#include <iostream>
#include "pawn.h"
#include "board.h"

int main()
{
    auto board = std::make_shared<Shohih::Board>();
    Shohih::Pawn pawn(board);

    auto moves = pawn.GetAvailableMoves();
    std::cout << moves.size() << std::endl;
}