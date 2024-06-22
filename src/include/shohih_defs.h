/**************************************************
 * @date    2024-06-05
 * @brief   Shohih definitions and constexpr variables
 **************************************************/

#pragma once
#ifndef SHOHIH_DEFS_H
#define SHOHIH_DEFS_H

#include <string>
#include <cstdint>
#include <iostream>
#include <unordered_map>

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
// Type aliases
//--------------------------------------------------
using SquareId = uint8_t;


//--------------------------------------------------
// constexpr
//--------------------------------------------------
constexpr uint8_t BOARD_SIZE{ 8 };
constexpr SquareId INVALID_SQUARE_ID{ UINT8_MAX };


//--------------------------------------------------
// Enums
//--------------------------------------------------
// Piece colors
enum class PieceColor : uint8_t {
    UNKNOWN,
    WHITE,
    BLACK
};

// Piece types
enum class PieceType : uint8_t {
    UNKNOWN = 0,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

// Shohih error codes
enum ErrorCode : uint64_t {
    SUCCESS                 = 0,
    INVALID_SQUARE          = 1 << 0,
    SQUARE_NOT_EMPTY        = 1 << 1,
    INVALID_FEN             = 1 << 2,
    INVALID_PIECE_TYPE      = 1 << 3,
};


//--------------------------------------------------
// Structs
//--------------------------------------------------
struct Square {
    uint8_t x{}; // 0 - 7
    uint8_t y{}; // 0 - 7

    // (y) __ __ __ __ __ __ __ __
    //  7 |_8|16|24|32|40|48|56|64|
    //  6 |_7|__|__|__|__|__|__|__|
    //  5 |_6|__|__|__|__|__|__|__|
    //  4 |_5|__|__|__|__|__|__|__|
    //  3 |_4|__|__|__|__|__|__|__|
    //  2 |_3|__|__|__|__|__|__|__|
    //  1 |_2|__|__|__|__|__|__|__|
    //  0 |_1|__|__|__|__|__|__|57|
    // (x)  0  1  2  3  4  5  6  7
    SquareId GetSquareId() const
    {
        return x*8 + y + 1;
    }
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

// Piece color & type
struct PieceTypeAndColor {
    PieceType type{ PieceType::UNKNOWN };
    PieceColor color { PieceColor::UNKNOWN };
};


//--------------------------------------------------
// Maps
//--------------------------------------------------
// FEN notation to <PieceType, PieceColor>
static const std::unordered_map<char, PieceTypeAndColor> fenMap {
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