/**************************************************
 * @date    2024-06-05
 * @brief   Shohih types and variables
 **************************************************/

#pragma once
#ifndef SHOHIH_DEFS_H
#define SHOHIH_DEFS_H

#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

namespace Shohih {

//--------------------------------------------------
// Macro definitions
//--------------------------------------------------
// Console colors
#define COLOR_RED       "\x1B[91m"
#define COLOR_GREEN     "\x1B[92m"
#define COLOR_YELLOW    "\x1B[93m"
#define COLOR_DEFAULT   "\x1B[0m"

// Logger macros
#define LOCATION __FILE__ << ":" << \
    __LINE__ << " (" << __FUNCTION__ << ")\n"

#define ERROR_LOG(msg)                                          \
    do {                                                        \
        std::cout << LOCATION << COLOR_RED                      \
        "[-] Error: " << msg << COLOR_DEFAULT << std::endl;     \
    } while(0)

#define WARNING_LOG(msg)                                        \
    do {                                                        \
        std::cout << LOCATION << COLOR_YELLOW                   \
        "[*] Warning: " << msg << COLOR_DEFAULT << std::endl;   \
    } while(0)

// Branch prediction
#define LIKELY(x) __builtin_expect (x, 1)
#define UNLIKELY(x) __builtin_expect (x, 0)


//--------------------------------------------------
// constexpr & static consts
//--------------------------------------------------
constexpr uint8_t BOARD_SIZE{ 8 };
constexpr uint8_t NUM_PIECE_TYPES{ 6 };
constexpr uint8_t NUM_PIECE_COLORS{ 2 };

// FEN for standard starting position
static const std::string STANDARD_POSITION_FEN {
 "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1" };

// GUI window size (multiple of 8)
constexpr int WINDOW_WIDTH = BOARD_SIZE * 60;
constexpr int WINDOW_HEIGHT = WINDOW_WIDTH;


//--------------------------------------------------
// Enums
//--------------------------------------------------
// Piece colors
enum class PieceColor : uint8_t {
    WHITE,
    BLACK,
    UNKNOWN
};

// Piece types
enum class PieceType : uint8_t {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    UNKNOWN
};

// Shohih error codes
enum ErrorCode : uint8_t {
    SUCCESS,
    SQUARE_EMPTY,
    SQUARE_NOT_EMPTY,
    SQUARE_NOT_AVAILABLE,
    INVALID_FEN,
    INVALID_SQUARE,
    INVALID_PIECE_TYPE,
    GAME_ALREADY_STARTED,
};


//--------------------------------------------------
// Structs
//--------------------------------------------------
struct Square {
    uint8_t x{}; // 0 - 7
    uint8_t y{}; // 0 - 7

    // (y) __ __ __ __ __ __ __ __
    //  7 |__|XX|__|XX|__|XX|__|XX|
    //  6 |XX|__|XX|__|XX|__|XX|__|
    //  5 |__|XX|__|XX|__|XX|__|XX|
    //  4 |XX|__|XX|__|XX|__|XX|__|
    //  3 |__|XX|__|XX|__|XX|__|XX|
    //  2 |XX|__|XX|__|XX|__|XX|__|
    //  1 |__|XX|__|XX|__|XX|__|XX|
    //  0 |XX|__|XX|__|XX|__|XX|__|
    // (x)  0  1  2  3  4  5  6  7
    std::string GetSquareName() const
    {
        std::string name { static_cast<char>('a' + x) };
        return name + std::to_string(y+1);
    }
    bool IsValid() const
    {
        // Since x and y are unsigned,
        // they are always non-negative.
        return std::max(x, y) < BOARD_SIZE;
    }
    bool operator==(const Square &other) const
    {
        return (x == other.x) && (y == other.y);
    }
    bool operator!=(const Square &other) const
    {
        return !(*this == other);
    }
    static Square GetSquareByName(const std::string &name)
    {
        if (UNLIKELY(name.length() != 2)) {
            WARNING_LOG("Invalid square name.");
            return Square{};
        }
        if (UNLIKELY(!isalpha(name[0]) || !isdigit(name[1]))) {
            WARNING_LOG("Invalid square name.");
            return Square{};
        }
        Square sq{};
        sq.x = static_cast<uint8_t>(name[0] - 'a');
        sq.y = static_cast<uint8_t>(name[1] - '1');
        return sq;
    }
};

// Invalid Square
constexpr Square NULL_SQUARE { UINT8_MAX, UINT8_MAX };

// Hash function for Square struct
struct SquareHash {
    uint16_t operator() (const Square &sq) const {
        return (static_cast<uint16_t>(sq.x) << 8) +
                static_cast<uint16_t>(sq.y); };
};

// Piece color & type
struct PieceTypeAndColor {
    PieceType type{ PieceType::UNKNOWN };
    PieceColor color { PieceColor::UNKNOWN };
};


//--------------------------------------------------
// Type aliases
//--------------------------------------------------
using SquareId = uint8_t;
using MoveSet = std::unordered_set<Square, SquareHash>;


//--------------------------------------------------
// Maps
//--------------------------------------------------
// FEN notation to <PieceType, PieceColor>
static const std::unordered_map<char, PieceTypeAndColor> FenMap {
    { 'P', PieceTypeAndColor{ PieceType::PAWN,   PieceColor::WHITE } },
    { 'N', PieceTypeAndColor{ PieceType::KNIGHT, PieceColor::WHITE } },
    { 'B', PieceTypeAndColor{ PieceType::BISHOP, PieceColor::WHITE } },
    { 'R', PieceTypeAndColor{ PieceType::ROOK,   PieceColor::WHITE } },
    { 'Q', PieceTypeAndColor{ PieceType::QUEEN,  PieceColor::WHITE } },
    { 'K', PieceTypeAndColor{ PieceType::KING,   PieceColor::WHITE } },
    { 'p', PieceTypeAndColor{ PieceType::PAWN,   PieceColor::BLACK } },
    { 'n', PieceTypeAndColor{ PieceType::KNIGHT, PieceColor::BLACK } },
    { 'b', PieceTypeAndColor{ PieceType::BISHOP, PieceColor::BLACK } },
    { 'r', PieceTypeAndColor{ PieceType::ROOK,   PieceColor::BLACK } },
    { 'q', PieceTypeAndColor{ PieceType::QUEEN,  PieceColor::BLACK } },
    { 'k', PieceTypeAndColor{ PieceType::KING,   PieceColor::BLACK } },
};

} // namespace Shohih

#endif // SHOHIH_DEFS_H