/**************************************************
 * @date    2024-06-22
 * @brief   Piece test utilities
 **************************************************/

#pragma once
#ifndef TEST_PIECE_UTILS
#define TEST_PIECE_UTILS

#include <gtest/gtest.h>
#include "piece.h"
#include "board.h"
#include "shohih_defs.h"

namespace Shohih {

void CheckAvailableMoves(
    const std::shared_ptr<Board> board,
    const std::unordered_map<std::string, PieceTypeAndColor> &pieces,
    const std::unordered_map<std::string, std::vector<std::string>> &expected_moves_map);

} // namespace Shohih

#endif // TEST_PIECE_UTILS