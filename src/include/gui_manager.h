/**************************************************
 * @date    2024-07-01
 * @brief   Graphical UI manager
 **************************************************/

#pragma once
#ifndef GUI_MGR_H
#define GUI_MGR_H

#include <array>
#include "board.h"
#include "raylib.h"

namespace Shohih {

class GuiManager {
public:
    GuiManager(std::shared_ptr<Board> board);
    ~GuiManager() = default;

    void Run();

private:
    std::shared_ptr<Board> m_board{ nullptr };

    // Board texture
    Texture2D m_boardTexture;

    // Array of Piece images & textures
    // size: 12 (six piece type per piece color)
    std::array<Image,
        NUM_PIECE_TYPES * NUM_PIECE_COLORS> m_pieceImages{};
    std::array<Texture2D,
        NUM_PIECE_TYPES * NUM_PIECE_COLORS> m_pieceTextures{};

    // Path to piece image files
    static const std::array<const char*,
        NUM_PIECE_TYPES * NUM_PIECE_COLORS> m_pieceImgPaths;

    // Get piece texture by piece type and color
    Texture2D GetPieceTexture(PieceColor color, PieceType type);

    // Piece square coordinates to window coordinates
    std::pair<int, int> ConvertSquareToWindowPos(Square sq) const;
};

} // namespace Shohih

#endif // GUI_MGR_H