/**************************************************
 * @date    2024-06-08
 * @brief   Chess board Implementation
 **************************************************/

#include <vector>
#include "board.h"
#include "pawn.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "king.h"

namespace Shohih {

/**************************************************
 * @details
 *      - @param board: passed-by-reference pointer 
 *          will be initialized by the built board
 *      - @param fen: FEN notation of board position
 * 
 * Visualize FEN notation:
 *  https://lichess.org/analysis
 * 
 * About:
 *  https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
 * 
 **************************************************/
ErrorCode Board::BuildBoardByFEN(
    std::shared_ptr<Board> &board, std::string fen)
{
    // Split the first token by space
    // e.g. "8/8/8/8/8/8/8/8 w - - 0 1" => "8/8/8/8/8/8/8/8"
    size_t first_space = fen.find_first_of(' ');
    if (UNLIKELY(first_space == std::string::npos)) {
        ERROR_LOG("Failed to build board. Invalid FEN.");
        return INVALID_FEN;
    }
    fen = fen.substr(0, first_space);

    // Parse rows from fen
    // e.g. "8/8/8/8/8/8/8/8" => { "8", "8", "8", "8", "8", "8", "8", "8" }
    std::vector<std::string> rows{};
    std::string row{};
    for (const char &c : fen) {
        if (c != '/') {
            row += c;
            continue;
        }
        rows.push_back(row);
        row.clear();
    }
    if (LIKELY(!row.empty())) {
        rows.push_back(row);
    }

    // Check rows
    if (UNLIKELY(rows.size() != BOARD_SIZE)) {
        ERROR_LOG("Failed to build board. Invalid FEN.");
        return INVALID_FEN;
    }
    for (const auto &_row : rows) {
        if (UNLIKELY(_row.empty())) {
            ERROR_LOG("Failed to build board. Invalid FEN.");
            return INVALID_FEN;
        }
    }

    // Set pieces on board
    board = std::make_shared<Board>();
    for (uint8_t y{ 0 }; y < BOARD_SIZE; y++) {
        // First row in FEN corresponds to the 8th rank
        const auto &_row = rows[BOARD_SIZE - 1 - y];

        uint8_t x{ 0 };
        for (const auto &c : _row) {
            // If a number is hit, shift x by that number
            if (isdigit(c)) {
                x += std::atoi(&c);
                continue;
            }
            // Get piece type & color for FEN notation
            auto fenItr = FenMap.find(c);
            if (UNLIKELY(fenItr == FenMap.end())) {
                ERROR_LOG("Failed to build board. Invalid FEN notation.");
                return INVALID_FEN;
            }
            // Set piece on square
            auto error = board->SetPieceOnSquare(
                fenItr->second.type, fenItr->second.color, Square{ x, y });
            if (UNLIKELY(error != SUCCESS)) {
                return INVALID_FEN;
            }
            // Move 1 square to the right
            x++;
        }
    }
    return SUCCESS;
}

/**************************************************
 * @details
 *      - Check @param src square is not empty.
 *              @return SQUARE_EMPTY
 *      - Check @param dst square is in available moves
 *              of the piece @return SQUARE_NOT_AVAILABLE
 *      - Move piece from @param src square
 *              to @param dst square. @return SUCCESS
 **************************************************/
ErrorCode Board::MovePiece(Square src, Square dst)
{
    // Get the piece on <src> square
    auto piece = GetPieceBySquare(src);
    if (UNLIKELY(piece == nullptr)) {
        ERROR_LOG("Source square " << src.GetSquareName() << " is empty.");
        return SQUARE_EMPTY;
    }

    // Get available moves of piece
    auto moves = piece->GetAvailableMoves();
    if (UNLIKELY(moves.count(dst) == 0)) {
        ERROR_LOG("Square " << dst.GetSquareName() << " is not in the available moves.");
        return SQUARE_NOT_AVAILABLE;
    }

    // In case of En Passant, remove the other pawn
    if (piece->GetPieceType() == PieceType::PAWN) {
        auto pawn = std::dynamic_pointer_cast<Pawn>(piece);
        Square enPassant = pawn->GetEnPassantMove();
        if (enPassant == dst) {
            m_pieceSet.erase(m_pieces[dst.x][src.y]);
            m_pieces[dst.x][src.y] = nullptr;
        }
    }

    // Move the piece to <dst> square
    m_pieceSet.erase(m_pieces[dst.x][dst.y]);
    m_pieces[dst.x][dst.y] = piece;
    piece->SetPieceOnSquare(dst);

    // Update last move
    m_lastMove.first = src;
    m_lastMove.second = dst;

    return SUCCESS;
}

/**************************************************
 * @details
 *      - Check @param square is empty
 *              @return SQUARE_NOT_EMPTY
 *      - Save piece ptr in m_pieces
 *              @return SUCCESS
 **************************************************/
ErrorCode Board::SetPieceOnSquare(
    PieceType type, PieceColor color, Square square)
{
    // Validate input parameters
    if (UNLIKELY(!square.IsValid())) {
        ERROR_LOG("Failed to set piece on board: Invalid parameters.");
        return INVALID_SQUARE;
    }

    // Check if square is empty
    if (m_pieces[square.x][square.y] != nullptr) {
        ERROR_LOG("Failed to set piece on board: Square "
            << square.GetSquareName() << " is not empty.");
        return SQUARE_NOT_EMPTY;
    }

    // Build piece
    std::shared_ptr<Piece> piece;
    switch (type) {
    case PieceType::PAWN:
        piece = std::make_shared<Pawn>(square, color, shared_from_this());
        break;
    case PieceType::KNIGHT:
        piece = std::make_shared<Knight>(square, color, shared_from_this());
        break;
    case PieceType::BISHOP:
        piece = std::make_shared<Bishop>(square, color, shared_from_this());
        break;
    case PieceType::ROOK:
        piece = std::make_shared<Rook>(square, color, shared_from_this());
        break;
    case PieceType::QUEEN:
        piece = std::make_shared<Queen>(square, color, shared_from_this());
        break;
    case PieceType::KING:
        piece = std::make_shared<King>(square, color, shared_from_this());
        break;
    default:
        ERROR_LOG("Failed to set piece on board: Invalid piece type.");
        return INVALID_PIECE_TYPE;
    }

    m_pieces[square.x][square.y] = piece;
    m_pieceSet.emplace(piece);
    return SUCCESS;
}

/**************************************************
 * @details
 *      - Validate @param square
 *              @return nullptr
 *      - Return piece at @param square
 **************************************************/
std::shared_ptr<Piece> Board::GetPieceBySquare(Square square) const
{
    if (UNLIKELY(!square.IsValid())) {
        ERROR_LOG("Failed to get piece: Invalid square.");
        return nullptr;
    }
    return m_pieces[square.x][square.y];
}

bool Board::IsWhitePieceOnSquare(Square square) const
{
    return !IsEmptySquare(square) &&
        m_pieces[square.x][square.y]->GetPieceColor() == PieceColor::WHITE;
}

bool Board::IsBlackPieceOnSquare(Square square) const
{
    return !IsEmptySquare(square) &&
        m_pieces[square.x][square.y]->GetPieceColor() == PieceColor::BLACK;
}

} // Shohih