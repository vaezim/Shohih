/**************************************************
 * @date    2024-06-05
 * @brief   Chess board
 **************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <array>
#include "piece.h"
#include "shohih_defs.h"

namespace Shohih {

class Board : public std::enable_shared_from_this<Board> {
public:
    Board() {}
    ~Board() = default;

    //--------------------------------------------------
    // Board static APIs
    //--------------------------------------------------
    // Build board by FEN notation (static API)
    static ErrorCode BuildBoardByFEN(
        std::shared_ptr<Board> &board, std::string fen);

    //--------------------------------------------------
    // Piece Getter/Setter
    //--------------------------------------------------
    // Piece setter
    ErrorCode SetPieceOnSquare(
        PieceType type, PieceColor color, Square square);
    // Piece getter
    std::shared_ptr<Piece> GetPieceBySquare(Square square);

private:
    std::array<std::array<
        std::shared_ptr<Piece>, BOARD_SIZE>, BOARD_SIZE> m_pieces{};
};

} // namespace Shohih

#endif // BOARD_H