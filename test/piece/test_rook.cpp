/**************************************************
 * @date    2024-06-22
 * @brief   Tests for rook.h & rook.cpp
 **************************************************/

#include <gtest/gtest.h>
#include "rook.h"
#include "test_piece_utils.h"

using namespace Shohih;

/**************************************************
 * Visualize FEN position at https://lichess.org/analysis
 **************************************************/
TEST(TestRook, AvailableMoves)
{
    const std::string fen{ "P2r2N1/8/1R2P3/8/4r3/2K3R1/r7/2R1B3 w - - 0 1" };

    // Build board by FEN
    std::shared_ptr<Board> board{ nullptr };
    auto err = Board::BuildBoardByFEN(board, fen);
    ASSERT_EQ(err, SUCCESS);
    ASSERT_NE(board, nullptr);

    std::unordered_map<std::string, PieceTypeAndColor> pieces {
        // Rook on c1
        { "c1", { PieceType::ROOK, PieceColor::WHITE } },
        // Rook on a2
        { "a2", { PieceType::ROOK, PieceColor::BLACK } },
        // Rook on g3
        { "g3", { PieceType::ROOK, PieceColor::WHITE } },
        // Rook on e4
        { "e4", { PieceType::ROOK, PieceColor::BLACK } },
        // Rook on b6
        { "b6", { PieceType::ROOK, PieceColor::WHITE } },
        // Rook on d8
        { "d8", { PieceType::ROOK, PieceColor::BLACK } },
    };
    std::unordered_map<std::string, std::vector<std::string>> expected_moves_map {
        { "c1", { "c2", "b1", "a1", "d1" } },
        { "a2", { "a1", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "a3", "a4", "a5", "a6", "a7", "a8" } },
        { "g3", { "g2", "g1", "h3", "f3", "e3", "d3", "g4", "g5", "g6", "g7" } },
        { "e4", { "e3", "e2", "e1", "d4", "c4", "b4", "a4", "f4", "g4", "h4", "e5", "e6" } },
        { "b6", { "b5", "b4", "b3", "b2", "b1", "a6", "c6", "d6", "b7", "b8" } },
        { "d8", { "c8", "b8", "a8", "e8", "f8", "g8", "d7", "d6", "d5", "d4", "d3", "d2", "d1" } },
    };

    CheckAvailableMoves(board, pieces, expected_moves_map);
}