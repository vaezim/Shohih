/**************************************************
 * @date    2024-06-05
 * @brief   Chess board
 **************************************************/

#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "piece.h"

namespace Shohih {

class Board : public std::enable_shared_from_this<Board> {
public:
    Board() {}
    ~Board() = default;

    //--------------------------------------------------
    // Board static APIs
    //--------------------------------------------------
    // Build board by FEN notation
    static ErrorCode BuildBoardByFEN(
        std::shared_ptr<Board> &board, std::string fen);

    //--------------------------------------------------
    // Player APIs
    //--------------------------------------------------
    ErrorCode MovePiece(Square src, Square dst);

    //--------------------------------------------------
    // Getters
    //--------------------------------------------------
    PieceColor GetPlayerTurn() const { return m_playerTurn; }
    std::shared_ptr<Piece> GetPieceBySquare(Square square) const;
    Move GetLastMove() const { return m_lastMove; }
    std::unordered_set<std::shared_ptr<Piece>> GetPieceSet() const { return m_pieceSet; }

    //--------------------------------------------------
    // Square info
    //--------------------------------------------------
    bool IsEmptySquare(Square square) const
        { return GetPieceBySquare(square) == nullptr; }
    bool IsWhitePieceOnSquare(Square square) const;
    bool IsBlackPieceOnSquare(Square square) const;

protected:
    //--------------------------------------------------
    // Protected API used in setting up the board
    //--------------------------------------------------
    ErrorCode SetPieceOnSquare(PieceType type, PieceColor color, Square square);

private:
    // Player turn (WHITE or BLACK)
    PieceColor m_playerTurn{ PieceColor::WHITE };

    // 8x8 array of pieces representing a real board
    std::array<std::array<
        std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> m_pieces{};

    // Hashset of active pieces currently on board
    std::unordered_set<std::shared_ptr<Piece>> m_pieceSet{};

    // Keep track of the last move (used for En-Passant)
    Move m_lastMove{ NULL_SQUARE, NULL_SQUARE };
};

} // namespace Shohih

#endif // BOARD_H