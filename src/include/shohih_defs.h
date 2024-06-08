/**************************************************
 * @date    2024-06-05
 * @brief   Shohih definitions and constexpr variables
 **************************************************/

#ifndef SHOHIH_DEFS_H
#define SHOHIH_DEFS_H

#include <string>
#include <cstdint>
#include <iostream>

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
// Structs
//--------------------------------------------------
struct Square {
    uint8_t x{}; // 0 - 7
    uint8_t y{}; // 0 - 7

    // (y) __ __ __ __ __ __ __ __
    //  0 |_8|_9|17|25|33|41|49|57|
    //  1 |_7|__|__|__|__|__|__|__|
    //  2 |_6|__|__|__|__|__|__|__|
    //  3 |_5|__|__|__|__|__|__|__|
    //  4 |_4|__|__|__|__|__|__|__|
    //  5 |_3|__|__|__|__|__|__|__|
    //  6 |_2|__|__|__|__|__|__|__|
    //  7 |_1|__|__|__|__|__|__|64|
    // (x)  0  1  2  3  4  5  6  7
    SquareId GetSquareId() const
    {
        return x*8 + y + 1;
    }
    std::string GetSquareName() const
    {
        std::string name = std::string("a"+x) + std::to_string(y+1);
        return name;
    }
    bool IsValid() const
    {
        return std::max(x, y) < BOARD_SIZE;
    }
    bool operator==(const Square &other) const
    {
        return (x == other.x) && (y == other.y);
    }
};

// Move from <src> Square to <dst> Square
struct Move {
    Square src{};
    Square dst{};
    bool operator==(const Move &other) const
    {
        return (src == other.src) && (dst == other.dst);
    }
};


//--------------------------------------------------
// Enums
//--------------------------------------------------
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
    INVALID_PARAMETER       = 1 << 0,
    SQUARE_NOT_EMPTY        = 1 << 1,
};

} // namespace Shohih

#endif // SHOHIH_DEFS_H