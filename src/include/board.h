/**************************************************
 * @date    2024-06-05
 * @brief   Chess board
 **************************************************/

#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "piece.h"
#include "client.h"

namespace Shohih {

class Board : public std::enable_shared_from_this<Board> {
public:
    Board(GameMode mode=GameMode::OFFLINE, std::shared_ptr<Client> client=nullptr)
        : m_gameMode(mode), m_client(client) {}
    ~Board() = default;

    //--------------------------------------------------
    // Board static APIs
    //--------------------------------------------------
    // Build board by FEN notation
    static ErrorCode BuildBoardByFEN(
        std::shared_ptr<Board> &board, std::string fen);
    static ErrorCode BuildBoardByFEN(
        std::shared_ptr<Board> &board, std::string fen,
        GameMode mode, std::shared_ptr<Client> client);

    //--------------------------------------------------
    // Player APIs
    //--------------------------------------------------
    ErrorCode MovePiece(Move move);
    ErrorCode MovePiece(Square src, Square dst);

    //--------------------------------------------------
    // Getters
    //--------------------------------------------------
    Move GetLastMove() const { return m_lastMove; }
    PieceColor GetPlayerTurn() const { return m_playerTurn; }
    std::shared_ptr<Piece> GetPieceBySquare(Square square) const;
    std::unordered_set<std::shared_ptr<Piece>> GetPieceSet() const { return m_pieceSet; }

    //--------------------------------------------------
    // Square info
    //--------------------------------------------------
    bool IsEmptySquare(Square square) const
        { return GetPieceBySquare(square) == nullptr; }
    bool IsWhitePieceOnSquare(Square square) const;
    bool IsBlackPieceOnSquare(Square square) const;

    //--------------------------------------------------
    // Online mode utilities
    //--------------------------------------------------
    GameMode GetGameMode() const { return m_gameMode; }
    std::shared_ptr<Client> GetClient() const { return m_client; }
    PieceColor GetClientPieceColor() const { return m_client->GetPlayerColor(); }

protected:
    //--------------------------------------------------
    // Protected API used in setting up the board
    //--------------------------------------------------
    ErrorCode SetPieceOnSquare(PieceType type, PieceColor color, Square square);

private:
    //--------------------------------------------------
    // Game mode: Offline/Online
    // In online mode, <m_client> is initialized.
    //--------------------------------------------------
    GameMode m_gameMode{ GameMode::OFFLINE };
    std::shared_ptr<Client> m_client { nullptr };

    // Player turn (WHITE or BLACK)
    PieceColor m_playerTurn{ PieceColor::WHITE };

    // 8x8 array of pieces representing a real board
    std::array<std::array<
        std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> m_pieces{};

    // Hashset of active pieces currently on board
    std::unordered_set<std::shared_ptr<Piece>> m_pieceSet{};

    // Keep track of the last move (used for En-Passant)
    Move m_lastMove = NULL_MOVE;
};

} // namespace Shohih

#endif // BOARD_H