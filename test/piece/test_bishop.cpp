/**************************************************
 * @date    2024-06-22
 * @brief   Tests for bishop.h & bishop.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "bishop.h"
#include "test_piece_utils.h"

using namespace Shohih;

/**************************************************
 * Visualize FEN position at https://lichess.org/analysis
 **************************************************/
TEST(TestBishop, AvailableMoves)
{
    const std::string fen{ "1B5b/5K2/4b3/b2N2B1/2P5/2BR4/6B1/1b6 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    std::unordered_map<std::string, PieceTypeAndColor> pieces {
        // Bishop on b1
        { "b1", { PieceType::BISHOP, PieceColor::BLACK } },
        // Bishop on g2
        { "g2", { PieceType::BISHOP, PieceColor::WHITE } },
        // Bishop on c3
        { "c3", { PieceType::BISHOP, PieceColor::WHITE } },
        // Bishop on a5
        { "a5", { PieceType::BISHOP, PieceColor::BLACK } },
        // Bishop on g5
        { "g5", { PieceType::BISHOP, PieceColor::WHITE } },
        // Bishop on e6
        { "e6", { PieceType::BISHOP, PieceColor::BLACK } },
        // Bishop on b8
        { "b8", { PieceType::BISHOP, PieceColor::WHITE } },
        // Bishop on h8
        { "h8", { PieceType::BISHOP, PieceColor::BLACK } },
    };
    std::unordered_map<std::string, std::vector<std::string>> expected_moves_map {
        { "b1", { "a2", "c2", "d3" } },
        { "g2", { "h1", "f1", "h3", "f3", "e4" } },
        { "c3", { "a1", "b2", "d2", "e1", "b4", "a5", "d4", "e5", "f6", "g7", "h8" } },
        { "a5", { "b4", "c3", "b6", "c7", "d8" } },
        { "g5", { "h4", "f4", "e3", "d2", "c1", "h6", "f6", "e7", "d8" } },
        { "e6", { "d5", "f5", "g4", "h3", "f7", "d7", "c8" } },
        { "b8", { "a7", "c7", "d6", "e5", "f4", "g3", "h2" } },
        { "h8", { "g7", "f6", "e5", "d4", "c3" } },
    };

    CheckAvailableMoves(board, pieces, expected_moves_map);
}